/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_HCITYPES_H__
#define __QAPI_BLE_HCITYPES_H__

#include "qapi_ble_btapityp.h"
#include "qapi_ble_bttypes.h"   /* Bluetooth Type Definitions.                */
#include "qapi_ble_hcicommt.h"  /* HCI COMM Driver Types/Constants.           */
#include "qapi_ble_hciusbt.h"   /* HCI USB Driver Types/Constants.            */

   /* The following Type Declaration defines the currently supported    */
   /* Physical Bluetooth HCI Device Interfaces that are supported by    */
   /* the HCI Packet Driver.                                            */
typedef enum
{
   QAPI_BLE_COMM_DRIVER_E,              /* COM/Serial Port HCI          */
                                        /* Connection Type.             */
   QAPI_BLE_USB_DRIVER_E                /* USB HCI Connection Type.     */
} qapi_BLE_HCI_DriverType_t;

   /* The following structure encapsulates a generic mechanism for      */
   /* Opening Bluetooth HCI Drivers for different Physical Bluetooth    */
   /* HCI Connection types.  This structure is used by the              */
   /* HCI_OpenDriver() function to inform the HCI Driver of what type   */
   /* (and configuration parameters specific to the specified type) of  */
   /* HCI Physical Driver to open.                                      */
typedef struct qapi_BLE_HCI_DriverInformation_s
{
   qapi_BLE_HCI_DriverType_t DriverType;
   union
   {
     qapi_BLE_HCI_COMMDriverInformation_t COMMDriverInformation;
     qapi_BLE_HCI_USBDriverInformation_t  USBDriverInformation;
   } DriverInformation;
} qapi_BLE_HCI_DriverInformation_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set COM/Serial Driver Information in an            */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure, the*/
   /* second, third and fourth parameters are the COM Port Number, Baud */
   /* Rate, and HCI Protocol to use, respectively.  When this MACRO is  */
   /* complete, the pointer that is used as the first argument to this  */
   /* MACRO will be able to be passed to the HCI_OpenDriver() function  */
   /* without any further processing.                                   */
#define QAPI_BLE_HCI_DRIVER_SET_COMM_INFORMATION(_w, _x, _y, _z)                                                                \
{                                                                                                                               \
   (_w)->DriverType                                                    = QAPI_BLE_COMM_DRIVER_E;                                \
   (_w)->DriverInformation.COMMDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.COMMDriverInformation); \
   (_w)->DriverInformation.COMMDriverInformation.COMPortNumber         = (uint32_t)(_x);                                        \
   (_w)->DriverInformation.COMMDriverInformation.BaudRate              = (unsigned long)(_y);                                   \
   (_w)->DriverInformation.COMMDriverInformation.Protocol              = (_z);                                                  \
   (_w)->DriverInformation.COMMDriverInformation.InitializationDelay   = (uint32_t)0;                                           \
   (_w)->DriverInformation.COMMDriverInformation.COMDeviceName         = NULL;                                                  \
   (_w)->DriverInformation.COMMDriverInformation.Flags                 = 0;                                                     \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set COM/Serial Driver Information in an            */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure, the*/
   /* second, third and fourth parameters are the COM Port Number, Baud */
   /* Rate, and HCI Protocol to use, respectively.  The fifth parameter */
   /* specifies the Initialization Delay Time (in Milliseconds) to wait */
   /* before sending any data to the Port.  When this MACRO is complete,*/
   /* the pointer that is used as the first argument to this MACRO will */
   /* be able to be passed to the HCI_OpenDriver() function without any */
   /* further processing.                                               */
#define QAPI_BLE_HCI_DRIVER_SET_EXTENDED_COMM_INFORMATION_DELAY(_w, _x, _y, _z, _a)                                             \
{                                                                                                                               \
   (_w)->DriverType                                                    = QAPI_BLE_COMM_DRIVER_E;                                \
   (_w)->DriverInformation.COMMDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.COMMDriverInformation); \
   (_w)->DriverInformation.COMMDriverInformation.COMPortNumber         = (uint32_t)(_x);                                        \
   (_w)->DriverInformation.COMMDriverInformation.BaudRate              = (unsigned long)(_y);                                   \
   (_w)->DriverInformation.COMMDriverInformation.Protocol              = (_z);                                                  \
   (_w)->DriverInformation.COMMDriverInformation.InitializationDelay   = (uint32_t)(_a);                                        \
   (_w)->DriverInformation.COMMDriverInformation.COMDeviceName         = NULL;                                                  \
   (_w)->DriverInformation.COMMDriverInformation.Flags                 = 0;                                                     \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set COM/Serial Driver Information in an            */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure, the*/
   /* second, third and fourth parameters are the COM Port Number, Baud */
   /* Rate, and HCI Protocol, Initialization Delay Time (in             */
   /* Milliseconds), and the Physical Device Name to use to override the*/
   /* default compiled device name.  When this MACRO is complete, the   */
   /* pointer that is used as the first argument to this MACRO will be  */
   /* able to be passed to the HCI_OpenDriver() function without any    */
   /* further processing.                                               */
   /* * NOTE * If the COMDeviceName member is specified (NON-NULL) then */
   /*          then this value becomes the Physical Device Name of the  */
   /*          COM Device that is to be opened.  The COMPortNumber is   */
   /* simply appended to the end (see next NOTE for the the only        */
   /*          exception).                                              */
   /* * NOTE * If the COMPortNumber member is specified as negative 1   */
   /*          (-1), then the COMDeviceName is assumed to be an absolute*/
   /*          name and the COMPortNumber field is does not affect the  */
   /*          device name in any way (the device name is used as-is).  */
   /*          Examples: Example 1: COMPortNumber: 1 COMDeviceName: NULL*/
   /*          -> COM1 (for Windows) /dev/ttyS0 (for Linux) Example 2:  */
   /*          COMPortNumber: 1 COMDeviceName: "\\\\DEVICE$\\Device" -> */
   /*          \\DEVICE$\Device1 Example 3: COMPortNumber: (-1)         */
   /*          COMDeviceName: "/dev/ttyHS0" -> /dev/ttyHS0              */
#define QAPI_BLE_HCI_DRIVER_SET_EXTENDED_COMM_INFORMATION_DEVICE_NAME(_w, _x, _y, _z, _a, _b)                                   \
{                                                                                                                               \
   (_w)->DriverType                                                    = QAPI_BLE_COMM_DRIVER_E;                                \
   (_w)->DriverInformation.COMMDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.COMMDriverInformation); \
   (_w)->DriverInformation.COMMDriverInformation.COMPortNumber         = (uint32_t)(_x);                                        \
   (_w)->DriverInformation.COMMDriverInformation.BaudRate              = (unsigned long)(_y);                                   \
   (_w)->DriverInformation.COMMDriverInformation.Protocol              = (_z);                                                  \
   (_w)->DriverInformation.COMMDriverInformation.InitializationDelay   = (uint32_t)(_a);                                        \
   (_w)->DriverInformation.COMMDriverInformation.COMDeviceName         = (_b);                                                  \
   (_w)->DriverInformation.COMMDriverInformation.Flags                 = 0;                                                     \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set COM/Serial Driver Information in an            */
   /* qapi_BLE_HCI_DriverInformation_t structure with the even parity   */
   /* flag set.  The first parameter is a pointer to an                 */
   /* qapi_BLE_HCI_DriverInformation_t structure, the second, third and */
   /* fourth parameters are the COM Port Number, Baud Rate, and HCI     */
   /* Protocol, Initialization Delay Time (in Milliseconds), and the    */
   /* Physical Device Name to use to override the default compiled      */
   /* device name.  The seventh parameter specifies the flags for the   */
   /* com port as defined in HCICommT.h.  When this MACRO is complete,  */
   /* the pointer that is used as the first argument to this MACRO will */
   /* be able to be passed to the HCI_OpenDriver() function without any */
   /* further processing.                                               */
   /* * NOTE * If the COMDeviceName member is specified (NON-NULL) then */
   /*          then this value becomes the Physical Device Name of the  */
   /*          COM Device that is to be opened.  The COMPortNumber is   */
   /* simply appended to the end (see next NOTE for the the only        */
   /*          exception).                                              */
   /* * NOTE * If the COMPortNumber member is specified as negative 1   */
   /*          (-1), then the COMDeviceName is assumed to be an absolute*/
   /*          name and the COMPortNumber field is does not affect the  */
   /*          device name in any way (the device name is used as-is).  */
   /*          Examples: Example 1: COMPortNumber: 1 COMDeviceName: NULL*/
   /*          -> COM1 (for Windows) /dev/ttyS0 (for Linux) Example 2:  */
   /*          COMPortNumber: 1 COMDeviceName: "\\\\DEVICE$\\Device" -> */
   /*          \\DEVICE$\Device1 Example 3: COMPortNumber: (-1)         */
   /*          COMDeviceName: "/dev/ttyHS0" -> /dev/ttyHS0              */
#define QAPI_BLE_HCI_DRIVER_SET_EXTENDED_COMM_INFORMATION_FLAGS(_w, _x, _y, _z, _a, _b, _c)                                      \
{                                                                                                                                \
   (_w)->DriverType                                                    = QAPI_BLE_COMM_DRIVER_E;                                 \
   (_w)->DriverInformation.COMMDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.COMMDriverInformation);  \
   (_w)->DriverInformation.COMMDriverInformation.COMPortNumber         = (uint32_t)(_x);                                         \
   (_w)->DriverInformation.COMMDriverInformation.BaudRate              = (unsigned long)(_y);                                    \
   (_w)->DriverInformation.COMMDriverInformation.Protocol              = (_z);                                                   \
   (_w)->DriverInformation.COMMDriverInformation.InitializationDelay   = (uint32_t)(_a);                                         \
   (_w)->DriverInformation.COMMDriverInformation.COMDeviceName         = (_b);                                                   \
   (_w)->DriverInformation.COMMDriverInformation.Flags                 = (_c);                                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set USB Driver Information in an                   */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure.    */
   /* Currently there are NO parameters that can be specified for an HCI*/
   /* USB Driver.  When this MACRO is complete, the pointer that is used*/
   /* as the first argument to this MACRO will be able to be passed to  */
   /* the HCI_OpenDriver() function without any further processing.     */
#define QAPI_BLE_HCI_DRIVER_SET_USB_INFORMATION(_w)                                                                           \
{                                                                                                                             \
   (_w)->DriverType                                                   = QAPI_BLE_USB_DRIVER_E;                                \
   (_w)->DriverInformation.USBDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.USBDriverInformation); \
   (_w)->DriverInformation.USBDriverInformation.DriverType            = QAPI_BLE_USB_DRIVER_SS1_E;                            \
   (_w)->DriverInformation.USBDriverInformation.InitializationDelay   = 0;                                                    \
   (_w)->DriverInformation.USBDriverInformation.Flags                 = 0;                                                    \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set USB Driver Information in an                   */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure.    */
   /* The second parameter represents the USB Driver type of the HCI USB*/
   /* Driver to open.  When this MACRO is complete, the pointer that is */
   /* used as the first argument to this MACRO will be able to be passed*/
   /* to the HCI_OpenDriver() function without any further processing.  */
#define QAPI_BLE_HCI_DRIVER_SET_EXTENDED_USB_INFORMATION(_w, _x)                                                              \
{                                                                                                                             \
   (_w)->DriverType                                                   = QAPI_BLE_USB_DRIVER_E;                                \
   (_w)->DriverInformation.USBDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.USBDriverInformation); \
   (_w)->DriverInformation.USBDriverInformation.DriverType            = (_x);                                                 \
   (_w)->DriverInformation.USBDriverInformation.InitializationDelay   = 0;                                                    \
   (_w)->DriverInformation.USBDriverInformation.Flags                 = 0;                                                    \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set USB Driver Information in an                   */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure.    */
   /* The second parameter represents the USB Driver type of the HCI USB*/
   /* Driver to open.  The third parameter specifies the Initialization */
   /* Delay Time (in Milliseconds) to wait before sending any data to   */
   /* the Port.  When this MACRO is complete, the pointer that is used  */
   /* as the first argument to this MACRO will be able to be passed to  */
   /* the HCI_OpenDriver() function without any further processing.     */
#define QAPI_BLE_HCI_DRIVER_SET_EXTENDED_USB_INFORMATION_DELAY(_w, _x, _y)                                           \
{                                                                                                                             \
   (_w)->DriverType                                                   = QAPI_BLE_USB_DRIVER_E;                                \
   (_w)->DriverInformation.USBDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.USBDriverInformation); \
   (_w)->DriverInformation.USBDriverInformation.DriverType            = (_x);                                                 \
   (_w)->DriverInformation.USBDriverInformation.InitializationDelay   = (_y);                                                 \
   (_w)->DriverInformation.USBDriverInformation.Flags                 = 0;                                                    \
}

   /* The following MACRO is a utility MACRO that exists to             */
   /* aid code readability to Set USB Driver Information in an          */
   /* qapi_BLE_HCI_DriverInformation_t structure.  The first parameter  */
   /* is a pointer to an qapi_BLE_HCI_DriverInformation_t structure.    */
   /* The second parameter represents the USB Driver type of the HCI USB*/
   /* Driver to open.  The third parameter specifies the Initialization */
   /* Delay Time (in Milliseconds) to wait before sending any data to   */
   /* the Port.  When this MACRO is complete, the pointer that is used  */
   /* as the first argument to this MACRO will be able to be passed to  */
   /* the HCI_OpenDriver() function without any further processing.     */
#define HCI_DRIVER_SET_EXTENDED_USB_INFORMATION_FLAGS(_w, _x, _y, _z)                                                         \
{                                                                                                                             \
   (_w)->DriverType                                                   = hdtUSB;                                               \
   (_w)->DriverInformation.USBDriverInformation.DriverInformationSize = sizeof((_w)->DriverInformation.USBDriverInformation); \
   (_w)->DriverInformation.USBDriverInformation.DriverType            = (_x);                                                 \
   (_w)->DriverInformation.USBDriverInformation.InitializationDelay   = (_y);                                                 \
   (_w)->DriverInformation.USBDriverInformation.Flags                 = (_z);                                                 \

   /* The following structure is used with the HCI_ReconfigureDriver()  */
   /* function to pass Reconfiguration data to the actual lower level   */
   /* HCI Driver.                                                       */
   /* * NOTE * ReconfigureCommand values between 0x00000000 - 0x0000FFFF*/
   /*          are reserved for the HCI Driver itself.  Values of       */
   /*          0x00010000 - 0xFFFF0000 are for the lower layer transport*/
   /*          drivers and the data is passed untouched to the lower    */
   /*          driver.                                                  */
typedef struct qapi_BLE_HCI_Driver_Reconfigure_Data_s
{
   uint32_t  ReconfigureCommand;
   void    *ReconfigureData;
} qapi_BLE_HCI_Driver_Reconfigure_Data_t;

#define QAPI_BLE_HCI_DRIVER_RECONFIGURE_DATA_SIZE                          (sizeof(qapi_BLE_HCI_Driver_Reconfigure_Data_t))

   /* The following prototype is for a callback function to receive     */
   /* indications when data is written to the COMM or USB driver.       */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_HCI_Driver_Packet_Write_Callback_t)(unsigned long CallbackParameter);

   /* The following structure is used in conjunction with the           */
   /* HCI_DRIVER_RECONFIGURE_DATA_RECONFIGURE_COMMAND_REGISTER_PACKET_  */
   /* WRITE_CALLBACK reconfigure command in order to register for a     */
   /* callback that will be invoked when an HCI packet is sent.  The    */
   /* members include the function to be called and the callback        */
   /* parameter that will be provided when the callback is invoked.     */
   /* * NOTE * This callback is invoked before the actual packet is     */
   /*          delivered to the lower layer transport.                  */
   /* * NOTE * Only one callback may be registered at a time.  If a     */
   /*          callback is already registered, the new callback function*/
   /*          will replace any previously registered function.  A value*/
   /*          of NULL may be used for the callback function to         */
   /*          un-register a previously registered callback.            */
typedef struct qapi_BLE_HCI_Driver_Register_Packet_Write_Callback_s
{
   qapi_BLE_HCI_Driver_Packet_Write_Callback_t PacketWriteCallback;
   unsigned long                               CallbackParameter;
} qapi_BLE_HCI_Driver_Register_Packet_Write_Callback_t;

   /* The following constant may be used as the value for the           */
   /* ReconfigureCommand in the qapi_BLE_HCI_Driver_Reconfigure_Data_t  */
   /* structure in order to register for a callback when data is written*/
   /* to the COMM or USB interfaces.  When this value is used, The      */
   /* ReconfigureData should be a pointer to a                          */
   /* qapi_BLE_HCI_Driver_Register_Packet_Write_Callback_t structure.   */
#define QAPI_BLE_HCI_DRIVER_RECONFIGURE_DATA_RECONFIGURE_COMMAND_REGISTER_PACKET_WRITE_CALLBACK    0x00000001

   /* The following constant represents the starting Command value that */
   /* is used to specify lower layer transport reconfigure commands.    */
   /* Any Reconfigure Commands less than this value are destined for the*/
   /* HCI Driver itself.                                                */
#define QAPI_BLE_HCI_DRIVER_RECONFIGURE_DATA_RECONFIGURE_COMMAND_TRANSPORT_START                   0x00010000

   /* The following enumerated type represents Possible SCO             */
   /* Configurations that might have to be configured for a specific    */
   /* Bluetooth HCI Driver.  For example, the USB Bluetooth HCI         */
   /* Interface defines different USB Interfaces (dynamically scales    */
   /* required Bandwidth on the USB Bus) depending upon the required SCO*/
   /* functionality required.                                           */
typedef enum
{
   QAPI_BLE_HCI_SCO_NO_CHANNELS_E,
   QAPI_BLE_HCI_SCO_ONE_8_BIT_VOICE_CHANNEL_E,
   QAPI_BLE_HCI_SCO_ONE_16_BIT_VOICE_CHANNEL_E,
   QAPI_BLE_HCI_SCO_TWO_8_BIT_VOICE_CHANNELS_E,
   QAPI_BLE_HCI_SCO_TWO_16_BIT_VOICE_CHANNELS_E,
   QAPI_BLE_HCI_SCO_THREE_8_BIT_VOICE_CHANNELS_E,
   QAPI_BLE_HCI_SCO_THREE_16_BIT_VOICE_CHANNELS_E
} qapi_BLE_HCI_SCOConfiguration_t;

   /* The following Type Definition represents ALL HCI Packet Types that*/
   /* can be passed into and out of the Lower Level HCI Driver Layer    */
   /* Interface.                                                        */
   /* * NOTE * This module does NOT define any HCI Transport Specific   */
   /*          HCI Packet Types.  This module simply defines the        */
   /*          Starting Point for these Additional HCI Commands, and    */
   /*          allows these to be used if the implementation requires   */
   /*          these additional HCI Packet Types.                       */
   /* * NOTE * These Types are the actual HCI Packet Data Type ID's     */
   /*          defined in the Bluetooth Specification Version 1.0b.  If */
   /*          these values change (or more are added/deleted) then     */
   /*          a mapping from these Types to these types will be needed.*/
   /* * NOTE * While the Types are the same numerical value, the size   */
   /*          of the Type MAY NOT be the same as the Size of the       */
   /*          type required in an HCI Packet.                          */
typedef enum
{
   QAPI_BLE_HCI_COMMAND_PACKET_E    = 0x01,         /* Simple HCI Command Packet    */
                                                    /* Type.                        */
   QAPI_BLE_HCI_ACL_DATA_PACKET_E   = 0x02,         /* HCI ACL Data Packet Type.    */
   QAPI_BLE_HCI_SCO_DATA_PACKET_E   = 0x03,         /* HCI SCO Data Packet Type.    */
   QAPI_BLE_HCI_ESCO_DATA_PACKET_E  = 0x03,         /* HCI eSCO Data Packet Type.   */
   QAPI_BLE_HCI_EVENT_PACKET_E      = 0x04,         /* HCI Event Packet Type.       */
   QAPI_BLE_HCI_ADDITIONAL_PACKET_E = 0x05          /* Starting Point for Additional*/
                                                    /* HCI Packet Types that are    */
                                                    /* Implementation Specific (for */
                                                    /* example RS-232 HCI defines   */
                                                    /* two Additional HCI Packet    */
                                                    /* Types which are numbered     */
                                                    /* 0x05 and 0x06 for RS-232 HCI.*/
} qapi_BLE_HCI_PacketType_t;

   /* The following structure represents the Data structure that holds  */
   /* the information for a Raw HCI Packet that is to be transmitted or */
   /* that has been received.  The only detail to note is that the      */
   /* Packet Data field is an array of unsigned char's, and NOT a       */
   /* Pointer to an array of unsigned char's.  This is very important,  */
   /* because this mechanism will allow an arbitrary memory buffer to be*/
   /* typecast to this structure and all elements will be accessible in */
   /* the same memory block (i.e.  NO other Pointer operation is        */
   /* required).  The side effect of this is that when the memory for a */
   /* Raw HCI Packet is to be allocated, the allocated size required    */
   /* will be (sizeof(qapi_BLE_HCI_Packet_t)-1) + length of the Packet  */
   /* Data.  After this is completed, the data elements in the Packet   */
   /* Data array can be accessed by simply Array Logic, aiding code     */
   /* readability.  It might appear confusing to the user because array */
   /* elements greater than zero will be indexed, however, as long as   */
   /* the programmer is aware of this design decision, the code should  */
   /* be much more simple to read.  MACRO's and Definitions will be     */
   /* provided following this structure definition to alleviate the     */
   /* programmer from having to remember the above formula when         */
   /* allocating memory of the correct size.                            */
   /* * NOTE * If the Most Significant Bit (MSB) of the HCIPacketLength */
   /*          member is set, then the HCIPacketData will contain a     */
   /*          pointer to the actual data (instead of the actual data   */
   /*          immediately following the HCIPacketLength member).  For  */
   /*          ease of programming, a new structure named               */
   /*          qapi_BLE_HCI_Packet_Header_t has been defined that has   */
   /*          this format.  The following constants exist to aid in    */
   /*          processing the HCIPacketLength member: -                 */
   /*          QAPI_BLE_HCI_PACKET_PACKET_LENGTH_HCI_PACKET_HEADER_MASK */
   /*          - HCI_PACKET_PACKET_LENGTH_HCI_PACKET_DATA_LENGTH The    */
   /*          first constant is used determine if the HCI Packet data  */
   /*          is a pointer (i.e.  the qapi_BLE_HCI_Packet_Header_t type*/
   /*          should be used to process the packet).  The second       */
   /*          constant can be used to determine the actual length of   */
   /*          the packet data (regardless if the packet is of type     */
   /*          qapi_BLE_HCI_Packet_t or qapi_BLE_HCI_Packet_Header_t.   */
typedef struct qapi_BLE_HCI_Packet_s
{
   qapi_BLE_HCI_PacketType_t HCIPacketType;
   uint32_t                  HCIPacketLength;
   unsigned char             HCIPacketData[1];
} qapi_BLE_HCI_Packet_t;

   /* The following definitions are used with the HCIPacketLength member*/
   /* of the qapi_BLE_HCI_Packet_t structure when determining           */
   /* (programaticly if the HCI Packet is represented via the           */
   /* qapi_BLE_HCI_Packet_t structure or the                            */
   /* qapi_BLE_HCI_Packet_Header_t structure.                           */
   /* * NOTE * See the description of the qapi_BLE_HCI_Packet_t         */
   /*          structure for more information on the usage of these     */
   /*          definitions.                                             */
#define QAPI_BLE_HCI_PACKET_PACKET_LENGTH_HCI_PACKET_DATA_LENGTH_MASK   (((uint32_t)(-1)) >> 1)
#define QAPI_BLE_HCI_PACKET_PACKET_LENGTH_HCI_PACKET_HEADER_MASK        (~QAPI_BLE_HCI_PACKET_PACKET_LENGTH_HCI_PACKET_DATA_LENGTH_MASK)

   /* The following Constant represents the actual size of the HCI      */
   /* Packet Header Information.  This Constant is to be used instead of*/
   /* simply using sizeof(qapi_BLE_HCI_Packet_t) to get the size.  The  */
   /* reason for this was explained above, and is primarily to aid in   */
   /* code readability and efficiency.                                  */
#define QAPI_BLE_HCI_PACKET_HEADER_SIZE                           (sizeof(qapi_BLE_HCI_Packet_t)-sizeof(unsigned char))

   /* The following MACRO is provided to allow the programmer a very    */
   /* simple means of quickly determining the number of Data Bytes that */
   /* will be required to hold a HCI Packet Information Header and the  */
   /* Raw HCI Packet Data (of the specified length).  See notes and     */
   /* discussion above for the reason for this MACRO definition.        */
#define QAPI_BLE_HCI_CALCULATE_PACKET_SIZE(_x)                    (QAPI_BLE_HCI_PACKET_HEADER_SIZE+(uint32_t)(_x))

   /* The following declaration represents the container structure for  */
   /* an HCI Packet that does NOT have the data immediately following   */
   /* the PacketLength member (like the qapi_BLE_HCI_Packet_t           */
   /* structure).  This structure can be overlaid over an               */
   /* qapi_BLE_HCI_Packet_t structure *ONLY* when the Most Significant  */
   /* Bit (MSB) of the HCIPacketLength member is set (i.e.  when        */
   /* processing qapi_BLE_HCI_Packet_t data, if the MSB of the          */
   /* HCIPacketLength bit is set, then the data is to be treated like   */
   /* the following).                                                   */
   /* * NOTE * See the description of the qapi_BLE_HCI_Packet_t         */
   /*          structure for more information on the usage of this      */
   /*          structure.                                               */
typedef struct qapi_BLE_HCI_Packet_Header_s
{
   qapi_BLE_HCI_PacketType_t  HCIPacketType;
   uint32_t                   HCIPacketLength;
   unsigned char             *HCIPacketData;
} qapi_BLE_HCI_Packet_Header_t;

#define QAPI_BLE_HCI_PACKET_HEADER_HEADER_SIZE                    (sizeof(qapi_BLE_HCI_Packet_Header_t))

   /* HCI Command Declarations/Types/Constants.                         */

   /* The following MACRO is provided to allow the programmer a very    */
   /* simple means of making an HCI Command Packet OpCode.  The OpCode  */
   /* Generated can be directly assigned to the OpCode field, so that   */
   /* the programmer does NOT have to translate Big Endian/Little       */
   /* Endian.  The OpCode itself NEEDS to be stored in the OpCode field */
   /* in Little Endian Format.  The first parameter is the OGF and the  */
   /* second parameter of the MACRO is the OCF of the Command.          */
#define QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(_x, _y) (((((uint16_t)(_x)) << 10) & 0xFC00) | (((uint16_t)(_y)) & 0x03FF))

   /* HCI Command Code OGF Definitions.                                 */
#define QAPI_BLE_HCI_COMMAND_CODE_NULL_OGF                                       0x00
#define QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF                               0x01
#define QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF                                0x02
#define QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF                           0x03
#define QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF                   0x04
#define QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF                          0x05
#define QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF                           0x06
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF                     0x08

#define QAPI_BLE_HCI_COMMAND_CODE_BLUETOOTH_LOGO_TESTING_OGF                     0x3E
#define QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF                      0x3F

   /* HCI Command Code OCF Definitions (NULL OpCode).                   */
#define QAPI_BLE_HCI_COMMAND_CODE_NULL_OCF                                       0x0000

   /* HCI Command Code OCF Definitions (Link Control).                  */
#define QAPI_BLE_HCI_COMMAND_CODE_INQUIRY_OCF                                    0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_INQUIRY_CANCEL_OCF                             0x0002
#define QAPI_BLE_HCI_COMMAND_CODE_PERIODIC_INQUIRY_MODE_OCF                      0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_EXIT_PERIODIC_INQUIRY_MODE_OCF                 0x0004
#define QAPI_BLE_HCI_COMMAND_CODE_CREATE_CONNECTION_OCF                          0x0005
#define QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_OCF                                 0x0006
#define QAPI_BLE_HCI_COMMAND_CODE_ADD_SCO_CONNECTION_OCF                         0x0007
#define QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_CONNECTION_REQUEST_OCF                  0x0009
#define QAPI_BLE_HCI_COMMAND_CODE_REJECT_CONNECTION_REQUEST_OCF                  0x000A
#define QAPI_BLE_HCI_COMMAND_CODE_LINK_KEY_REQUEST_REPLY_OCF                     0x000B
#define QAPI_BLE_HCI_COMMAND_CODE_LINK_KEY_REQUEST_NEGATIVE_REPLY_OCF            0x000C
#define QAPI_BLE_HCI_COMMAND_CODE_PIN_CODE_REQUEST_REPLY_OCF                     0x000D
#define QAPI_BLE_HCI_COMMAND_CODE_PIN_CODE_REQUEST_NEGATIVE_REPLY_OCF            0x000E
#define QAPI_BLE_HCI_COMMAND_CODE_CHANGE_CONNECTION_PACKET_TYPE_OCF              0x000F
#define QAPI_BLE_HCI_COMMAND_CODE_AUTHENTICATION_REQUESTED_OCF                   0x0011
#define QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTION_ENCRYPTION_OCF                  0x0013
#define QAPI_BLE_HCI_COMMAND_CODE_CHANGE_CONNECTION_LINK_KEY_OCF                 0x0015
#define QAPI_BLE_HCI_COMMAND_CODE_MASTER_LINK_KEY_OCF                            0x0017
#define QAPI_BLE_HCI_COMMAND_CODE_REMOTE_NAME_REQUEST_OCF                        0x0019
#define QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_SUPPORTED_FEATURES_OCF             0x001B
#define QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_VERSION_INFORMATION_OCF            0x001D
#define QAPI_BLE_HCI_COMMAND_CODE_READ_CLOCK_OFFSET_OCF                          0x001F

   /* HCI Command Code OCF Definitions (Link Control - Version 1.2).    */
#define QAPI_BLE_HCI_COMMAND_CODE_CREATE_CONNECTION_CANCEL_OCF                   0x0008
#define QAPI_BLE_HCI_COMMAND_CODE_REMOTE_NAME_REQUEST_CANCEL_OCF                 0x001A
#define QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_EXTENDED_FEATURES_OCF              0x001C
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LMP_HANDLE_OCF                            0x0020
#define QAPI_BLE_HCI_COMMAND_CODE_SETUP_SYNCHRONOUS_CONNECTION_OCF               0x0028
#define QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_SYNCHRONOUS_CONNECTION_OCF              0x0029
#define QAPI_BLE_HCI_COMMAND_CODE_REJECT_SYNCHRONOUS_CONNECTION_OCF              0x002A

   /* HCI Command Code OCF Definitions (Link Control - Version 2.1 +    */
   /* EDR).                                                             */
#define QAPI_BLE_HCI_COMMAND_CODE_IO_CAPABILITY_REQUEST_REPLY_OCF                0x002B
#define QAPI_BLE_HCI_COMMAND_CODE_USER_CONFIRMATION_REQUEST_REPLY_OCF            0x002C
#define QAPI_BLE_HCI_COMMAND_CODE_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY_OCF   0x002D
#define QAPI_BLE_HCI_COMMAND_CODE_USER_PASSKEY_REQUEST_REPLY_OCF                 0x002E
#define QAPI_BLE_HCI_COMMAND_CODE_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_OCF        0x002F
#define QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_DATA_REQUEST_REPLY_OCF              0x0030
#define QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY_OCF     0x0033
#define QAPI_BLE_HCI_COMMAND_CODE_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY_OCF       0x0034

   /* HCI Command Code OCF Definitions (Link Control - Version 3.0 +    */
   /* HS).                                                              */
#define QAPI_BLE_HCI_COMMAND_CODE_CREATE_PHYSICAL_LINK_OCF                       0x0035
#define QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_PHYSICAL_LINK_REQUEST_OCF               0x0036
#define QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_PHYSICAL_LINK_OCF                   0x0037
#define QAPI_BLE_HCI_COMMAND_CODE_CREATE_LOGICAL_LINK_OCF                        0x0038
#define QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_LOGICAL_LINK_OCF                        0x0039
#define QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_LOGICAL_LINK_OCF                    0x003A
#define QAPI_BLE_HCI_COMMAND_CODE_LOGICAL_LINK_CANCEL_OCF                        0x003B
#define QAPI_BLE_HCI_COMMAND_CODE_FLOW_SPEC_MODIFY_OCF                           0x003C

   /* HCI Command Code OCF Definitions (Link Control - Version 4.0 +    */
   /* CSA2).                                                            */
#define QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION_OCF            0x003D
#define QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST_OCF   0x003E

   /* HCI Command Code OCF Definitions (Link Control - Version 4.0 +    */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_COMMAND_CODE_TRUNCATED_PAGE_OCF                             0x003F
#define QAPI_BLE_HCI_COMMAND_CODE_TRUNCATED_PAGE_CANCEL_OCF                      0x0040
#define QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_OCF         0x0041
#define QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_OCF 0x0042
#define QAPI_BLE_HCI_COMMAND_CODE_START_SYNCHRONIZATION_TRAIN_OCF                0x0043
#define QAPI_BLE_HCI_COMMAND_CODE_RECEIVE_SYNCHRONIZATION_TRAIN_OCF              0x0044

   /* HCI Command Code OCF Definitions (Link Control - Version 4.1).    */
#define QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY_OCF     0x0045

   /* HCI Command Code OCF Definitions (Link Policy).                   */
#define QAPI_BLE_HCI_COMMAND_CODE_HOLD_MODE_OCF                                  0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_SNIFF_MODE_OCF                                 0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_EXIT_SNIFF_MODE_OCF                            0x0004
#define QAPI_BLE_HCI_COMMAND_CODE_PARK_MODE_OCF                                  0x0005
#define QAPI_BLE_HCI_COMMAND_CODE_EXIT_PARK_MODE_OCF                             0x0006
#define QAPI_BLE_HCI_COMMAND_CODE_QOS_SETUP_OCF                                  0x0007
#define QAPI_BLE_HCI_COMMAND_CODE_ROLE_DISCOVERY_OCF                             0x0009
#define QAPI_BLE_HCI_COMMAND_CODE_SWITCH_ROLE_OCF                                0x000B
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LINK_POLICY_SETTINGS_OCF                  0x000C
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LINK_POLICY_SETTINGS_OCF                 0x000D

   /* HCI Command Code OCF Definitions (Link Policy - Version 1.2).     */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_DEFAULT_LINK_POLICY_SETTINGS_OCF          0x000E
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_DEFAULT_LINK_POLICY_SETTINGS_OCF         0x000F
#define QAPI_BLE_HCI_COMMAND_CODE_FLOW_SPECIFICATION_OCF                         0x0010

   /* HCI Command Code OCF Definitions (Link Policy - Version 2.1 +     */
   /* EDR).                                                             */
#define QAPI_BLE_HCI_COMMAND_CODE_SNIFF_SUBRATING_OCF                            0x0011

   /* HCI Command Code OCF Definitions (Host Control and Baseband).     */
#define QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_MASK_OCF                             0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_RESET_OCF                                      0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_FILTER_OCF                           0x0005
#define QAPI_BLE_HCI_COMMAND_CODE_FLUSH_OCF                                      0x0008
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PIN_TYPE_OCF                              0x0009
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PIN_TYPE_OCF                             0x000A
#define QAPI_BLE_HCI_COMMAND_CODE_CREATE_NEW_UNIT_KEY_OCF                        0x000B
#define QAPI_BLE_HCI_COMMAND_CODE_READ_STORED_LINK_KEY_OCF                       0x000D
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_STORED_LINK_KEY_OCF                      0x0011
#define QAPI_BLE_HCI_COMMAND_CODE_DELETE_STORED_LINK_KEY_OCF                     0x0012
#define QAPI_BLE_HCI_COMMAND_CODE_CHANGE_LOCAL_NAME_OCF                          0x0013
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOCAL_NAME_OCF                           0x0013
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_NAME_OCF                            0x0014
#define QAPI_BLE_HCI_COMMAND_CODE_READ_CONNECTION_ACCEPT_TIMEOUT_OCF             0x0015
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_CONNECTION_ACCEPT_TIMEOUT_OCF            0x0016
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_TIMEOUT_OCF                          0x0017
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_TIMEOUT_OCF                         0x0018
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SCAN_ENABLE_OCF                           0x0019
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SCAN_ENABLE_OCF                          0x001A
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_ACTIVITY_OCF                    0x001B
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_ACTIVITY_OCF                   0x001C
#define QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_SCAN_ACTIVITY_OCF                 0x001D
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_SCAN_ACTIVITY_OCF                0x001E
#define QAPI_BLE_HCI_COMMAND_CODE_READ_AUTHENTICATION_ENABLE_OCF                 0x001F
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTHENTICATION_ENABLE_OCF                0x0020
#define QAPI_BLE_HCI_COMMAND_CODE_READ_ENCRYPTION_MODE_OCF                       0x0021
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_ENCRYPTION_MODE_OCF                      0x0022
#define QAPI_BLE_HCI_COMMAND_CODE_READ_CLASS_OF_DEVICE_OCF                       0x0023
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_CLASS_OF_DEVICE_OCF                      0x0024
#define QAPI_BLE_HCI_COMMAND_CODE_READ_VOICE_SETTING_OCF                         0x0025
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_VOICE_SETTING_OCF                        0x0026
#define QAPI_BLE_HCI_COMMAND_CODE_READ_AUTOMATIC_FLUSH_TIMEOUT_OCF               0x0027
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTOMATIC_FLUSH_TIMEOUT_OCF              0x0028
#define QAPI_BLE_HCI_COMMAND_CODE_READ_NUM_BROADCAST_RETRANSMISSIONS_OCF         0x0029
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_NUM_BROADCAST_RETRANSMISSIONS_OCF        0x002A
#define QAPI_BLE_HCI_COMMAND_CODE_READ_HOLD_MODE_ACTIVITY_OCF                    0x002B
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_HOLD_MODE_ACTIVITY_OCF                   0x002C
#define QAPI_BLE_HCI_COMMAND_CODE_READ_TRANSMIT_POWER_LEVEL_OCF                  0x002D
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SCO_FLOW_CONTROL_ENABLE_OCF               0x002E
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE_OCF       0x002E
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SCO_FLOW_CONTROL_ENABLE_OCF              0x002F
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE_OCF      0x002F
#define QAPI_BLE_HCI_COMMAND_CODE_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL_OCF   0x0031
#define QAPI_BLE_HCI_COMMAND_CODE_HOST_BUFFER_SIZE_OCF                           0x0033
#define QAPI_BLE_HCI_COMMAND_CODE_HOST_NUMBER_OF_COMPLETED_PACKETS_OCF           0x0035
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LINK_SUPERVISION_TIMEOUT_OCF              0x0036
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LINK_SUPERVISION_TIMEOUT_OCF             0x0037
#define QAPI_BLE_HCI_COMMAND_CODE_READ_NUMBER_OF_SUPPORTED_IAC_OCF               0x0038
#define QAPI_BLE_HCI_COMMAND_CODE_READ_CURRENT_IAC_LAP_OCF                       0x0039
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_CURRENT_IAC_LAP_OCF                      0x003A
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_PERIOD_MODE_OCF                 0x003B
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_PERIOD_MODE_OCF                0x003C
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_MODE_OCF                        0x003D
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_MODE_OCF                       0x003E

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 1.2).                                                     */
#define QAPI_BLE_HCI_COMMAND_CODE_SET_AFH_HOST_CHANNEL_CLASSIFICATION_OCF        0x003F
#define QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_SCAN_TYPE_OCF                     0x0042
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_SCAN_TYPE_OCF                    0x0043
#define QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_MODE_OCF                          0x0044
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_MODE_OCF                         0x0045
#define QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_TYPE_OCF                        0x0046
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_TYPE_OCF                       0x0047
#define QAPI_BLE_HCI_COMMAND_CODE_READ_AFH_CHANNEL_ASSESSMENT_MODE_OCF           0x0048
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_AFH_CHANNEL_ASSESSMENT_MODE_OCF          0x0049

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 2.1 + EDR).                                               */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_INQUIRY_RESPONSE_OCF             0x0051
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_INQUIRY_RESPONSE_OCF            0x0052
#define QAPI_BLE_HCI_COMMAND_CODE_REFRESH_ENCRYPTION_KEY_OCF                     0x0053
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SIMPLE_PAIRING_MODE_OCF                   0x0055
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SIMPLE_PAIRING_MODE_OCF                  0x0056
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_OOB_DATA_OCF                        0x0057
#define QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL_OCF 0x0058
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL_OCF         0x0059
#define QAPI_BLE_HCI_COMMAND_CODE_READ_DEFAULT_ERRONEOUS_DATA_REPORTING_OCF      0x005A
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING_OCF     0x005B
#define QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_FLUSH_OCF                             0x005F
#define QAPI_BLE_HCI_COMMAND_CODE_SEND_KEYPRESS_NOTIFICATION_OCF                 0x0060

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 3.0 + HS).                                                */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_OCF           0x0061
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_OCF          0x0062
#define QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_MASK_PAGE_2_OCF                      0x0063
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCATION_DATA_OCF                         0x0064
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOCATION_DATA_OCF                        0x0065
#define QAPI_BLE_HCI_COMMAND_CODE_READ_FLOW_CONTROL_MODE_OCF                     0x0066
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_FLOW_CONTROL_MODE_OCF                    0x0067
#define QAPI_BLE_HCI_COMMAND_CODE_READ_ENHANCED_TRANSMIT_POWER_LEVEL_OCF         0x0068
#define QAPI_BLE_HCI_COMMAND_CODE_READ_BEST_EFFORT_FLUSH_TIMEOUT_OCF             0x0069
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_OCF            0x006A
#define QAPI_BLE_HCI_COMMAND_CODE_SHORT_RANGE_MODE_OCF                           0x006B

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 4.0 + LE).                                                */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LE_HOST_SUPPORTED_OCF                     0x006C
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LE_HOST_SUPPORTED_OCF                    0x006D

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 4.0 + CSA3).                                              */
#define QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_CHANNEL_PARAMETERS_OCF                 0x006E
#define QAPI_BLE_HCI_COMMAND_CODE_SET_EXTERNAL_FRAME_CONFIGURATION_OCF           0x006F
#define QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_SIGNALING_OCF                          0x0070
#define QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_TRANSPORT_LAYER_OCF                    0x0071
#define QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_SCAN_FREQUENCY_TABLE_OCF               0x0072
#define QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_PATTERN_CONFIGURATION_OCF              0x0073

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 4.0 + CSA4).                                              */
#define QAPI_BLE_HCI_COMMAND_CODE_SET_RESERVED_LT_ADDR_OCF                       0x0074
#define QAPI_BLE_HCI_COMMAND_CODE_DELETE_RESERVED_LT_ADDR_OCF                    0x0075
#define QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_OCF    0x0076
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SYNCHRONIZATION_TRAIN_PARAMETERS_OCF      0x0077
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS_OCF     0x0078

   /* HCI Command Code OCF Definitions (Host Control and Baseband -     */
   /* Version 4.1).                                                     */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_SECURE_CONNECTIONS_HOST_SUPPORT_OCF       0x0079
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT_OCF      0x007A
#define QAPI_BLE_HCI_COMMAND_CODE_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_OCF         0x007B
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_OCF        0x007C
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_OOB_EXTENDED_DATA_OCF               0x007D
#define QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_PAGE_TIMEOUT_OCF                 0x007E
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_PAGE_TIMEOUT_OCF                0x007F
#define QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_INQUIRY_LENGTH_OCF               0x0080
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_INQUIRY_LENGTH_OCF              0x0081

   /* HCI Command Code OCF Definitions (Informational Parameters).      */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_VERSION_INFORMATION_OCF             0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_FEATURES_OCF              0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_READ_BUFFER_SIZE_OCF                           0x0005
#define QAPI_BLE_HCI_COMMAND_CODE_READ_COUNTRY_CODE_OCF                          0x0007
#define QAPI_BLE_HCI_COMMAND_CODE_READ_BD_ADDR_OCF                               0x0009

   /* HCI Command Code OCF Definitions (Informational Parameters -      */
   /* Version 1.2)                                                      */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_COMMANDS_OCF              0x0002
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_EXTENDED_FEATURES_OCF               0x0004

   /* HCI Command Code OCF Definitions (Informational Parameters -      */
   /* Version 3.0 + HS).                                                */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_DATA_BLOCK_SIZE_OCF                       0x000A

   /* HCI Command Code OCF Definitions (Informational Parameters -      */
   /* Version 4.0 + CSA2).                                              */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_CODECS_OCF                0x000B

   /* HCI Command Code OCF Definitions (Status Parameters).             */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_FAILED_CONTACT_COUNTER_OCF                0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_RESET_FAILED_CONTACT_COUNTER_OCF               0x0002
#define QAPI_BLE_HCI_COMMAND_CODE_GET_LINK_QUALITY_OCF                           0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_READ_RSSI_OCF                                  0x0005

   /* HCI Command Code OCF Definitions (Status Parameters - Version     */
   /* 1.2).                                                             */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_AFH_CHANNEL_MAP_OCF                       0x0006
#define QAPI_BLE_HCI_COMMAND_CODE_READ_CLOCK_OCF                                 0x0007

   /* HCI Command Code OCF Definitions (Status Parameters - Version 3.0 */
   /* + HS).                                                            */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_ENCRYPTION_KEY_SIZE_OCF                   0x0008
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_AMP_INFO_OCF                        0x0009
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_AMP_ASSOC_OCF                       0x000A
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_REMOTE_AMP_ASSOC_OCF                     0x000B

   /* HCI Command Code OCF Definitions (Status Parameters - Version 4.0 */
   /* + CSA3).                                                          */
#define QAPI_BLE_HCI_COMMAND_CODE_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_OCF      0x000C

   /* HCI Command Code OCF Definitions (Status Parameters - Version 4.0 */
   /* + CSA4).                                                          */
#define QAPI_BLE_HCI_COMMAND_CODE_SET_TRIGGERED_CLOCK_CAPTURE_OCF                0x000D

   /* HCI Command Code OCF Definitions (Testing Commands).              */
#define QAPI_BLE_HCI_COMMAND_CODE_READ_LOOPBACK_MODE_OCF                         0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOOPBACK_MODE_OCF                        0x0002
#define QAPI_BLE_HCI_COMMAND_CODE_ENABLE_DEVICE_UNDER_TEST_MODE_OCF              0x0003

   /* HCI Command Code OCF Definitions (Testing Commands - Version 2.1 +*/
   /* EDR).                                                             */
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SIMPLE_PAIRING_DEBUG_MODE_OCF            0x0004

   /* HCI Command Code OCF Definitions (Testing Commands - Version 3.0 +*/
   /* HS).                                                              */
#define QAPI_BLE_HCI_COMMAND_CODE_ENABLE_AMP_RECEIVER_REPORTS_OCF                0x0007
#define QAPI_BLE_HCI_COMMAND_CODE_AMP_TEST_END_OCF                               0x0008
#define QAPI_BLE_HCI_COMMAND_CODE_AMP_TEST_OCF                                   0x0009

   /* HCI Command Code OCF Definitions (Testing Commands - Version 4.1).*/
#define QAPI_BLE_HCI_COMMAND_CODE_WRITE_SECURE_CONNECTIONS_TEST_MODE_OCF         0x000A

   /* HCI Command Code OCF Definitions (LE Commands - Version 4.0 + LE).*/
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EVENT_MASK_OCF                          0x0001
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_BUFFER_SIZE_OCF                        0x0002
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_SUPPORTED_FEATURES_OCF           0x0003
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_RANDOM_ADDRESS_OCF                      0x0005
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_PARAMETERS_OCF              0x0006
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ADVERTISING_CHANNEL_TX_POWER_OCF       0x0007
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_DATA_OCF                    0x0008
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_RESPONSE_DATA_OCF                  0x0009
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISE_ENABLE_OCF                    0x000A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_PARAMETERS_OCF                     0x000B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_ENABLE_OCF                         0x000C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CONNECTION_OCF                       0x000D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CONNECTION_CANCEL_OCF                0x000E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_WHITE_LIST_SIZE_OCF                    0x000F
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_WHITE_LIST_OCF                        0x0010
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_WHITE_LIST_OCF                0x0011
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_WHITE_LIST_OCF           0x0012
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_UPDATE_OCF                       0x0013
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_HOST_CHANNEL_CLASSIFICATION_OCF         0x0014
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_CHANNEL_MAP_OCF                        0x0015
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_REMOTE_USED_FEATURES_OCF               0x0016
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ENCRYPT_OCF                                 0x0017
#define QAPI_BLE_HCI_COMMAND_CODE_LE_RAND_OCF                                    0x0018
#define QAPI_BLE_HCI_COMMAND_CODE_LE_START_ENCRYPTION_OCF                        0x0019
#define QAPI_BLE_HCI_COMMAND_CODE_LE_LONG_TERM_KEY_REQUEST_REPLY_OCF             0x001A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_OCF    0x001B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_SUPPORTED_STATES_OCF                   0x001C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_RECEIVER_TEST_OCF                           0x001D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_OCF                        0x001E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_TEST_END_OCF                                0x001F

   /* HCI Command Code OCF Definitions (LE Commands - Version 4.1).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_OCF            0x0020
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_OCF   0x0021

   /* HCI Command Code OCF Definitions (LE Commands - Version 4.2).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DATA_LENGTH_OCF                         0x0022
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_OCF      0x0023
#define QAPI_BLE_HCI_COMMAND_CODE_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_OCF     0x0024
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_P256_PUBLIC_KEY_OCF              0x0025
#define QAPI_BLE_HCI_COMMAND_CODE_LE_GENERATE_DHKEY_OCF                          0x0026
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_RESOLVING_LIST_OCF            0x0027
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_OCF       0x0028
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_RESOLVING_LIST_OCF                    0x0029
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_RESOLVING_LIST_SIZE_OCF                0x002A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PEER_RESOLVABLE_ADDRESS_OCF            0x002B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_RESOLVABLE_ADDRESS_OCF           0x002C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADDRESS_RESOLUTION_ENABLE_OCF           0x002D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_OCF  0x002E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_MAXIMUM_DATA_LENGTH_OCF                0x002F

   /* HCI Command Code OCF Definitions (LE Commands - Version 5.0).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PHY_OCF                                     0x0030
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_PHY_OCF                              0x0031
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PHY_OCF                                      0x0032
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_RECEIVER_TEST_OCF                       0x0033
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_TRANSMITTER_TEST_OCF                    0x0034
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_OCF           0x0035
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_OCF          0x0036
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_DATA_OCF                0x0037
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_OCF              0x0038
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_ENABLE_OCF              0x0039
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH_OCF         0x003A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_OCF    0x003B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_ADVERTISING_SET_OCF                       0x003C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_ADVERTISING_SETS_OCF                       0x003D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_OCF          0x003E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_DATA_OCF                0x003F
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_ENABLE_OCF              0x0040
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_PARAMETERS_OCF                 0x0041
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_ENABLE_OCF                     0x0042
#define QAPI_BLE_HCI_COMMAND_CODE_LE_EXTENDED_CREATE_CONNECTION_OCF                   0x0043
#define QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC_OCF             0x0044
#define QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL_OCF      0x0045
#define QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC_OCF          0x0046
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST_OCF       0x0047
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST_OCF  0x0048
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_PERIODIC_ADVERTISER_LIST_OCF               0x0049
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PERIODIC_ADVERTISER_LIST_SIZE_OCF           0x004A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_TRANSMIT_POWER_OCF                          0x004B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_RF_PATH_COMPENSATION_OCF                    0x004C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_WRITE_RF_PATH_COMPENSATION_OCF                   0x004D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PRIVACY_MODE_OCF                             0x004E

   /* HCI Command Code OCF Definitions (LE Commands - Version 5.1).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_RECEIVER_TEST_V3_OCF                                           0x004F
#define QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_V3_OCF                                        0x0050
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS_OCF                 0x0051
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE_OCF                     0x0052
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE_OCF                      0x0053
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS_OCF                      0x0054
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS_OCF                     0x0055
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_CTE_REQUEST_ENABLE_OCF                              0x0056
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_CTE_RESPONSE_ENABLE_OCF                             0x0057
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ANTENNA_INFORMATION_OCF                                   0x0058
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE_OCF                    0x0059
#define QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_OCF                         0x005A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER_OCF                     0x005B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_OCF          0x005C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_OCF  0x005D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_GENERATE_DHKEY_V2_OCF                                          0x005E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_MODIFY_SLEEP_CLOCK_ACCURACY_OCF                                0x005F

   /* HCI Command Code OCF Definitions (LE Commands - Version 5.2).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_BUFFER_SIZE_V2_OCF                                        0x0060
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ISO_TX_SYNC_OCF                                           0x0061
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CIG_PARAMETERS_OCF                                         0x0062
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CIG_PARAMETERS_TEST_OCF                                    0x0063
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CIS_OCF                                                 0x0064
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_CIS_OCF                                                 0x0065
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ACCEPT_CIS_REQUEST_OCF                                         0x0066
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REJECT_CIS_REQUEST_OCF                                         0x0067
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_BIG_OCF                                                 0x0068
#define QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_BIG_TEST_OCF                                            0x0069
#define QAPI_BLE_HCI_COMMAND_CODE_LE_TERMINATE_BIG_OCF                                              0x006A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_BIG_CREATE_SYNC_OCF                                            0x006B
#define QAPI_BLE_HCI_COMMAND_CODE_LE_BIG_TERMINATE_SYNC_OCF                                         0x006C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REQUEST_PEER_SCA_OCF                                           0x006D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SETUP_ISO_DATA_PATH_OCF                                        0x006E
#define QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_ISO_DATA_PATH_OCF                                       0x006F
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_TRANSMIT_TEST_OCF                                          0x0070
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_RECEIVE_TEST_OCF                                           0x0071
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_READ_TEST_COUNTERS_OCF                                     0x0072
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_TEST_END_OCF                                               0x0073
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_HOST_FEATURE_OCF                                           0x0074
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ISO_LINK_QUALITY_OCF                                      0x0075
#define QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL_OCF                         0x0076
#define QAPI_BLE_HCI_COMMAND_CODE_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL_OCF                           0x0077
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PATH_LOSS_REPORTING_PARAMETERS_OCF                         0x0078
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PATH_LOSS_REPORTING_ENABLE_OCF                             0x0079
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE_OCF                        0x007A
#define QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_V4_OCF                                        0x007B

   /* HCI Command Code OCF Definitions (LE Commands - Version 5.3).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DATA_RELATED_ADDRESS_CHANGES_OCF                           0x007C
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_SUBRATE_OCF                                        0x007D
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SUBRATE_REQUEST_OCF                                            0x007E

   /* HCI Command Code OCF Definitions (LE Commands - Version 5.4).     */
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_OCF                     0x0086
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_OCF                     0x0082
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_OCF                     0x0083
#define QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_SYNC_SUBEVENT_OCF                                 0x0084
#define QAPI_BLE_HCI_COMMAND_CODE_LE_EXTENDED_CREATE_CONNECTION_V2_OCF                              0x0085

   /* HCI Command Code OpCode Definitions (NULL OpCode).                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_NULL                                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_NULL_OGF, QAPI_BLE_HCI_COMMAND_CODE_NULL_OCF))

   /* HCI Command Code OpCode Definitions (Link Control).               */
#define QAPI_BLE_HCI_COMMAND_OPCODE_INQUIRY                                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_INQUIRY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_INQUIRY_CANCEL                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_INQUIRY_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_PERIODIC_INQUIRY_MODE                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_PERIODIC_INQUIRY_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_EXIT_PERIODIC_INQUIRY_MODE                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_EXIT_PERIODIC_INQUIRY_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CREATE_CONNECTION                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CREATE_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_DISCONNECT                                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ADD_SCO_CONNECTION                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ADD_SCO_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ACCEPT_CONNECTION_REQUEST                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_CONNECTION_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REJECT_CONNECTION_REQUEST                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REJECT_CONNECTION_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LINK_KEY_REQUEST_REPLY                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_LINK_KEY_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LINK_KEY_REQUEST_NEGATIVE_REPLY              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_LINK_KEY_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_PIN_CODE_REQUEST_REPLY                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_PIN_CODE_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_PIN_CODE_REQUEST_NEGATIVE_REPLY              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_PIN_CODE_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CHANGE_CONNECTION_PACKET_TYPE                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CHANGE_CONNECTION_PACKET_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_AUTHENTICATION_REQUESTED                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_AUTHENTICATION_REQUESTED_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_CONNECTION_ENCRYPTION                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTION_ENCRYPTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CHANGE_CONNECTION_LINK_KEY                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CHANGE_CONNECTION_LINK_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_MASTER_LINK_KEY                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_MASTER_LINK_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REMOTE_NAME_REQUEST                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REMOTE_NAME_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_REMOTE_SUPPORTED_FEATURES               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_SUPPORTED_FEATURES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_REMOTE_VERSION_INFORMATION              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_VERSION_INFORMATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_CLOCK_OFFSET                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_CLOCK_OFFSET_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 1.2). */
#define QAPI_BLE_HCI_COMMAND_OPCODE_CREATE_CONNECTION_CANCEL                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CREATE_CONNECTION_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REMOTE_NAME_REQUEST_CANCEL                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REMOTE_NAME_REQUEST_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_REMOTE_EXTENDED_FEATURES                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_REMOTE_EXTENDED_FEATURES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LMP_HANDLE                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LMP_HANDLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SETUP_SYNCHRONOUS_CONNECTION                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_SETUP_SYNCHRONOUS_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ACCEPT_SYNCHRONOUS_CONNECTION                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_SYNCHRONOUS_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REJECT_SYNCHRONOUS_CONNECTION                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REJECT_SYNCHRONOUS_CONNECTION_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 2.1 + */
   /* EDR).                                                             */
#define QAPI_BLE_HCI_COMMAND_OPCODE_IO_CAPABILITY_REQUEST_REPLY                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_IO_CAPABILITY_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_USER_CONFIRMATION_REQUEST_REPLY              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_USER_CONFIRMATION_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_USER_PASSKEY_REQUEST_REPLY                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_USER_PASSKEY_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_USER_PASSKEY_REQUEST_NEGATIVE_REPLY          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REMOTE_OOB_DATA_REQUEST_REPLY                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_DATA_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 3.0 + */
   /* HS).                                                              */
#define QAPI_BLE_HCI_COMMAND_OPCODE_CREATE_PHYSICAL_LINK                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CREATE_PHYSICAL_LINK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ACCEPT_PHYSICAL_LINK_REQUEST                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_PHYSICAL_LINK_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_DISCONNECT_PHYSICAL_LINK                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_PHYSICAL_LINK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CREATE_LOGICAL_LINK                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_CREATE_LOGICAL_LINK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ACCEPT_LOGICAL_LINK                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ACCEPT_LOGICAL_LINK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_DISCONNECT_LOGICAL_LINK                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_DISCONNECT_LOGICAL_LINK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LOGICAL_LINK_CANCEL                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_LOGICAL_LINK_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_FLOW_SPEC_MODIFY                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_FLOW_SPEC_MODIFY_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 4.0 + */
   /* CSA2).                                                            */
#define QAPI_BLE_HCI_COMMAND_OPCODE_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 4.0 + */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_COMMAND_OPCODE_TRUNCATED_PAGE                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_TRUNCATED_PAGE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_TRUNCATED_PAGE_CANCEL                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_TRUNCATED_PAGE_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_CONNECTIONLESS_SLAVE_BROADCAST           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_START_SYNCHRONIZATION_TRAIN                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_START_SYNCHRONIZATION_TRAIN_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_RECEIVE_SYNCHRONIZATION_TRAIN                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_RECEIVE_SYNCHRONIZATION_TRAIN_OCF))

   /* HCI Command Code OpCode Definitions (Link Control - Version 4.1). */
#define QAPI_BLE_HCI_COMMAND_OPCODE_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_CONTROL_OGF, QAPI_BLE_HCI_COMMAND_CODE_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY_OCF))

   /* HCI Command Code OpCode Definitions (Link Policy).                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_HOLD_MODE                                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_HOLD_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SNIFF_MODE                                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_SNIFF_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_EXIT_SNIFF_MODE                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_EXIT_SNIFF_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_PARK_MODE                                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_PARK_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_EXIT_PARK_MODE                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_EXIT_PARK_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_QOS_SETUP                                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_QOS_SETUP_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ROLE_DISCOVERY                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_ROLE_DISCOVERY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SWITCH_ROLE                                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_SWITCH_ROLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LINK_POLICY_SETTINGS                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LINK_POLICY_SETTINGS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LINK_POLICY_SETTINGS                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LINK_POLICY_SETTINGS_OCF))

   /* HCI Command Code OpCode Definitions (Link Policy - Version 1.2).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_DEFAULT_LINK_POLICY_SETTINGS            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_DEFAULT_LINK_POLICY_SETTINGS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_DEFAULT_LINK_POLICY_SETTINGS           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_DEFAULT_LINK_POLICY_SETTINGS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_FLOW_SPECIFICATION                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_FLOW_SPECIFICATION_OCF))

   /* HCI Command Code OpCode Definitions (Link Policy - Version 2.1 +  */
   /* EDR).                                                             */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SNIFF_SUBRATING                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LINK_POLICY_OGF, QAPI_BLE_HCI_COMMAND_CODE_SNIFF_SUBRATING_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_EVENT_MASK                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_MASK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_RESET                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_RESET_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_EVENT_FILTER                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_FILTER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_FLUSH                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_FLUSH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PIN_TYPE                                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PIN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PIN_TYPE                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PIN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CREATE_NEW_UNIT_KEY                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_CREATE_NEW_UNIT_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_STORED_LINK_KEY                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_STORED_LINK_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_STORED_LINK_KEY                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_STORED_LINK_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_DELETE_STORED_LINK_KEY                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_DELETE_STORED_LINK_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_CHANGE_LOCAL_NAME                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_CHANGE_LOCAL_NAME_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LOCAL_NAME                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOCAL_NAME_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_NAME                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_NAME_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_CONNECTION_ACCEPT_TIMEOUT               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_CONNECTION_ACCEPT_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_CONNECTION_ACCEPT_TIMEOUT              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_CONNECTION_ACCEPT_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PAGE_TIMEOUT                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PAGE_TIMEOUT                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SCAN_ENABLE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SCAN_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SCAN_ENABLE                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SCAN_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PAGE_SCAN_ACTIVITY                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PAGE_SCAN_ACTIVITY                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_INQUIRY_SCAN_ACTIVITY                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_SCAN_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_INQUIRY_SCAN_ACTIVITY                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_SCAN_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_AUTHENTICATION_ENABLE                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_AUTHENTICATION_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_AUTHENTICATION_ENABLE                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTHENTICATION_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_ENCRYPTION_MODE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_ENCRYPTION_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_ENCRYPTION_MODE                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_ENCRYPTION_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_CLASS_OF_DEVICE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_CLASS_OF_DEVICE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_CLASS_OF_DEVICE                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_CLASS_OF_DEVICE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_VOICE_SETTING                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_VOICE_SETTING_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_VOICE_SETTING                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_VOICE_SETTING_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_AUTOMATIC_FLUSH_TIMEOUT                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_AUTOMATIC_FLUSH_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_AUTOMATIC_FLUSH_TIMEOUT                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTOMATIC_FLUSH_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_NUM_BROADCAST_RETRANSMISSIONS           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_NUM_BROADCAST_RETRANSMISSIONS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_NUM_BROADCAST_RETRANSMISSIONS          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_NUM_BROADCAST_RETRANSMISSIONS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_HOLD_MODE_ACTIVITY                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_HOLD_MODE_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_HOLD_MODE_ACTIVITY                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_HOLD_MODE_ACTIVITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_TRANSMIT_POWER_LEVEL                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SCO_FLOW_CONTROL_ENABLE                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SCO_FLOW_CONTROL_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SCO_FLOW_CONTROL_ENABLE                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SCO_FLOW_CONTROL_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_HOST_BUFFER_SIZE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_HOST_BUFFER_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_HOST_NUMBER_OF_COMPLETED_PACKETS             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_HOST_NUMBER_OF_COMPLETED_PACKETS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LINK_SUPERVISION_TIMEOUT                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LINK_SUPERVISION_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LINK_SUPERVISION_TIMEOUT               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LINK_SUPERVISION_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_NUMBER_OF_SUPPORTED_IAC                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_NUMBER_OF_SUPPORTED_IAC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_CURRENT_IAC_LAP                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_CURRENT_IAC_LAP_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_CURRENT_IAC_LAP                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_CURRENT_IAC_LAP_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PAGE_SCAN_PERIOD_MODE                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_PERIOD_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PAGE_SCAN_PERIOD_MODE                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_PERIOD_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PAGE_SCAN_MODE                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PAGE_SCAN_MODE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_MODE_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 1.2).                                                     */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_AFH_HOST_CHANNEL_CLASSIFICATION          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_AFH_HOST_CHANNEL_CLASSIFICATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_INQUIRY_SCAN_TYPE                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_SCAN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_INQUIRY_SCAN_TYPE                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_SCAN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_INQUIRY_MODE                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_INQUIRY_MODE                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_PAGE_SCAN_TYPE                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_PAGE_SCAN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_PAGE_SCAN_TYPE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_PAGE_SCAN_TYPE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_AFH_CHANNEL_ASSESSMENT_MODE             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_AFH_CHANNEL_ASSESSMENT_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_AFH_CHANNEL_ASSESSMENT_MODE            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_AFH_CHANNEL_ASSESSMENT_MODE_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 2.1 + EDR).                                               */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_EXTENDED_INQUIRY_RESPONSE               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_INQUIRY_RESPONSE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_EXTENDED_INQUIRY_RESPONSE              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_INQUIRY_RESPONSE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_REFRESH_ENCRYPTION_KEY                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_REFRESH_ENCRYPTION_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SIMPLE_PAIRING_MODE                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SIMPLE_PAIRING_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SIMPLE_PAIRING_MODE                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SIMPLE_PAIRING_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_OOB_DATA                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_OOB_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_DEFAULT_ERRONEOUS_DATA_REPORTING        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_DEFAULT_ERRONEOUS_DATA_REPORTING_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ENHANCED_FLUSH                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_ENHANCED_FLUSH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SEND_KEYPRESS_NOTIFICATION                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SEND_KEYPRESS_NOTIFICATION_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 3.0 + HS).                                                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOGICAL_LINK_ACCEPT_TIMEOUT             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_EVENT_MASK_PAGE_2                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_EVENT_MASK_PAGE_2_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCATION_DATA                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCATION_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LOCATION_DATA                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOCATION_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_FLOW_CONTROL_MODE                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_FLOW_CONTROL_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_FLOW_CONTROL_MODE                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_FLOW_CONTROL_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_ENHANCED_TRANSMIT_POWER_LEVEL           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_ENHANCED_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_BEST_EFFORT_FLUSH_TIMEOUT               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_BEST_EFFORT_FLUSH_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_BEST_EFFORT_FLUSH_TIMEOUT              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SHORT_RANGE_MODE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SHORT_RANGE_MODE_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 4.0 + LE).                                                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LE_HOST_SUPPORTED                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LE_HOST_SUPPORTED_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LE_HOST_SUPPORTED                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LE_HOST_SUPPORTED_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 4.0 + CSA3).                                              */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_MWS_CHANNEL_PARAMETERS                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_CHANNEL_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_EXTERNAL_FRAME_CONFIGURATION             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_EXTERNAL_FRAME_CONFIGURATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_MWS_SIGNALING                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_SIGNALING_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_MWS_TRANSPORT_LAYER                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_TRANSPORT_LAYER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_MWS_SCAN_FREQUENCY_TABLE                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_SCAN_FREQUENCY_TABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_MWS_PATTERN_CONFIGURATION                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_MWS_PATTERN_CONFIGURATION_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 4.0 + CSA4).                                              */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_RESERVED_LT_ADDR                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_RESERVED_LT_ADDR_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_DELETE_RESERVED_LT_ADDR                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_DELETE_RESERVED_LT_ADDR_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SYNCHRONIZATION_TRAIN_PARAMETERS        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SYNCHRONIZATION_TRAIN_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS_OCF))

   /* HCI Command Code OpCode Definitions (Host Control and Baseband -  */
   /* Version 4.1).                                                     */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_SECURE_CONNECTIONS_HOST_SUPPORT         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_SECURE_CONNECTIONS_HOST_SUPPORT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_AUTHENTICATED_PAYLOAD_TIMEOUT           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_OOB_EXTENDED_DATA                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_OOB_EXTENDED_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_EXTENDED_PAGE_TIMEOUT                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_PAGE_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_EXTENDED_PAGE_TIMEOUT                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_PAGE_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_EXTENDED_INQUIRY_LENGTH                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_EXTENDED_INQUIRY_LENGTH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_EXTENDED_INQUIRY_LENGTH                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_CONTROL_BASEBAND_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_EXTENDED_INQUIRY_LENGTH_OCF))

   /* HCI Command Code OpCode Definitions (Informational Parameters).   */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_VERSION_INFORMATION               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_VERSION_INFORMATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_SUPPORTED_FEATURES                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_FEATURES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_BUFFER_SIZE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_BUFFER_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_COUNTRY_CODE                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_COUNTRY_CODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_BD_ADDR                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_BD_ADDR_OCF))

   /* HCI Command Code OpCode Definitions (Informational Parameters -   */
   /* Version 1.2).                                                     */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_SUPPORTED_COMMANDS                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_COMMANDS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_EXTENDED_FEATURES                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_EXTENDED_FEATURES_OCF))

   /* HCI Command Code OpCode Definitions (Informational Parameters -   */
   /* Version 3.0 + HS).                                                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_DATA_BLOCK_SIZE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_DATA_BLOCK_SIZE_OCF))

   /* HCI Command Code OpCode Definitions (Informational Parameters -   */
   /* Version 4.0 + CSA2).                                              */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_SUPPORTED_CODECS                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_SUPPORTED_CODECS_OCF))

   /* HCI Command Code OpCode Definitions (Status Parameters).          */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_FAILED_CONTACT_COUNTER                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_FAILED_CONTACT_COUNTER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_RESET_FAILED_CONTACT_COUNTER                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_RESET_FAILED_CONTACT_COUNTER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_GET_LINK_QUALITY                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_GET_LINK_QUALITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_RSSI                                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_RSSI_OCF))

   /* HCI Command Code OpCode Definitions (Status Parameters - Version  */
   /* 1.2).                                                             */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_AFH_CHANNEL_MAP                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_AFH_CHANNEL_MAP_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_CLOCK                                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_CLOCK_OCF))

   /* HCI Command Code OpCode Definitions (Status Parameters - Version  */
   /* 3.0 + HS).                                                        */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_ENCRYPTION_KEY_SIZE                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_ENCRYPTION_KEY_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_AMP_INFO                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_AMP_INFO_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOCAL_AMP_ASSOC                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOCAL_AMP_ASSOC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_REMOTE_AMP_ASSOC                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_REMOTE_AMP_ASSOC_OCF))

   /* HCI Command Code OpCode Definitions (Status Parameters - Version  */
   /* 4.0 + CSA3).                                                      */
#define QAPI_BLE_HCI_COMMAND_OPCODE_GET_MWS_TRANSPORT_LAYER_CONFIGURATION        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_OCF))

   /* HCI Command Code OpCode Definitions (Status Parameters - Version  */
   /* 4.0 + CSA4).                                                      */
#define QAPI_BLE_HCI_COMMAND_OPCODE_SET_TRIGGERED_CLOCK_CAPTURE                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_STATUS_PARAMETERS_OGF, QAPI_BLE_HCI_COMMAND_CODE_SET_TRIGGERED_CLOCK_CAPTURE_OCF))

   /* HCI Command Code OpCode Definitions (Testing Commands).           */
#define QAPI_BLE_HCI_COMMAND_OPCODE_READ_LOOPBACK_MODE                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_READ_LOOPBACK_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_LOOPBACK_MODE                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_LOOPBACK_MODE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_ENABLE_DEVICE_UNDER_TEST_MODE                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_ENABLE_DEVICE_UNDER_TEST_MODE_OCF))

   /* HCI Command Code OpCode Definitions (Testing Commands - Version   */
   /* 2.1 + EDR).                                                       */
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SIMPLE_PAIRING_DEBUG_MODE              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SIMPLE_PAIRING_DEBUG_MODE_OCF))

   /* HCI Command Code OpCode Definitions (Testing Commands - Version   */
   /* 3.0 + HS).                                                        */
#define QAPI_BLE_HCI_COMMAND_OPCODE_ENABLE_AMP_RECEIVER_REPORTS                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_ENABLE_AMP_RECEIVER_REPORTS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_AMP_TEST_END                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_AMP_TEST_END_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_AMP_TEST                                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_AMP_TEST_OCF))

   /* HCI Command Code OpCode Definitions (Testing Commands - Version   */
   /* 4.1).                                                             */
#define QAPI_BLE_HCI_COMMAND_OPCODE_WRITE_SECURE_CONNECTIONS_TEST_MODE           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_TESTING_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_WRITE_SECURE_CONNECTIONS_TEST_MODE_OCF))

   /* HCI Command Code OpCode Definitions (LE Controller Commands -     */
   /* Version 4.0 + LE).                                                */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EVENT_MASK                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EVENT_MASK_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_BUFFER_SIZE                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_BUFFER_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_LOCAL_SUPPORTED_FEATURES             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_SUPPORTED_FEATURES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_RANDOM_ADDRESS                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_RANDOM_ADDRESS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_ADVERTISING_PARAMETERS                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_ADVERTISING_CHANNEL_TX_POWER         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ADVERTISING_CHANNEL_TX_POWER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_ADVERTISING_DATA                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_SCAN_RESPONSE_DATA                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_RESPONSE_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_ADVERTISE_ENABLE                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISE_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_SCAN_PARAMETERS                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_SCAN_ENABLE                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_SCAN_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CREATE_CONNECTION                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CREATE_CONNECTION_CANCEL                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CONNECTION_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_WHITE_LIST_SIZE                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_WHITE_LIST_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CLEAR_WHITE_LIST                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_WHITE_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ADD_DEVICE_TO_WHITE_LIST                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_WHITE_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_DEVICE_FROM_WHITE_LIST             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_WHITE_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CONNECTION_UPDATE                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_UPDATE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_HOST_CHANNEL_CLASSIFICATION           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_HOST_CHANNEL_CLASSIFICATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_CHANNEL_MAP                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_CHANNEL_MAP_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_REMOTE_USED_FEATURES                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_REMOTE_USED_FEATURES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENCRYPT                                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ENCRYPT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_RAND                                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_RAND_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_START_ENCRYPTION                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_START_ENCRYPTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_LONG_TERM_KEY_REQUEST_REPLY               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_LONG_TERM_KEY_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_SUPPORTED_STATES                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_SUPPORTED_STATES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_RECEIVER_TEST                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_RECEIVER_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_TEST_END                                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_TEST_END_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 4.1).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 4.2).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_DATA_LENGTH                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DATA_LENGTH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_LOCAL_P256_PUBLIC_KEY                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_P256_PUBLIC_KEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_GENERATE_DHKEY                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_GENERATE_DHKEY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ADD_DEVICE_TO_RESOLVING_LIST              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_RESOLVING_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CLEAR_RESOLVING_LIST                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_RESOLVING_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_RESOLVING_LIST_SIZE                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_RESOLVING_LIST_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_PEER_RESOLVABLE_ADDRESS              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PEER_RESOLVABLE_ADDRESS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_LOCAL_RESOLVABLE_ADDRESS             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_LOCAL_RESOLVABLE_ADDRESS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_ADDRESS_RESOLUTION_ENABLE             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADDRESS_RESOLUTION_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_MAXIMUM_DATA_LENGTH                  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_MAXIMUM_DATA_LENGTH_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 5.0).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_PHY                                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PHY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_DEFAULT_PHY                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_PHY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PHY                                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PHY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENHANCED_RECEIVER_TEST                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_RECEIVER_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENHANCED_TRANSMITTER_TEST                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_TRANSMITTER_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_ADVERTISING_PARAMETERS          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_ADVERTISING_DATA                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_SCAN_RESPONSE_DATA              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_ADVERTISING_ENABLE              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_ADVERTISING_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_ADVERTISING_SET                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_ADVERTISING_SET_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CLEAR_ADVERTISING_SETS                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_ADVERTISING_SETS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_DATA                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_ENABLE              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_SCAN_PARAMETERS                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EXTENDED_SCAN_ENABLE                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_EXTENDED_SCAN_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_EXTENDED_CREATE_CONNECTION                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_EXTENDED_CREATE_CONNECTION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CLEAR_PERIODIC_ADVERTISER_LIST               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CLEAR_PERIODIC_ADVERTISER_LIST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_PERIODIC_ADVERTISER_LIST_SIZE           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_PERIODIC_ADVERTISER_LIST_SIZE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_TRANSMIT_POWER                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_TRANSMIT_POWER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_RF_PATH_COMPENSATION                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_RF_PATH_COMPENSATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_WRITE_RF_PATH_COMPENSATION                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_WRITE_RF_PATH_COMPENSATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PRIVACY_MODE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PRIVACY_MODE_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 5.1).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_RECEIVER_TEST_V3                                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_RECEIVER_TEST_V3_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST_V3                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_V3_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CONNECTION_CTE_REQUEST_ENABLE                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_CTE_REQUEST_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CONNECTION_CTE_RESPONSE_ENABLE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CONNECTION_CTE_RESPONSE_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_ANTENNA_INFORMATION                                   (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ANTENNA_INFORMATION_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS  (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_GENERATE_DHKEY_V2                                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_GENERATE_DHKEY_V2_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_MODIFY_SLEEP_CLOCK_ACCURACY                                (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_MODIFY_SLEEP_CLOCK_ACCURACY_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 5.2).     */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_BUFFER_SIZE_V2                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_BUFFER_SIZE_V2_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_ISO_TX_SYNC                                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ISO_TX_SYNC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CIG_PARAMETERS                                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CIG_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_CIG_PARAMETERS_TEST                                    (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_CIG_PARAMETERS_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CREATE_CIS                                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_CIS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_CIS                                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_CIS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ACCEPT_CIS_REQUEST                                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ACCEPT_CIS_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REJECT_CIS_REQUEST                                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REJECT_CIS_REQUEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CREATE_BIG                                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_BIG_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_CREATE_BIG_TEST                                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_CREATE_BIG_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_TERMINATE_BIG                                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_TERMINATE_BIG_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_BIG_CREATE_SYNC                                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_BIG_CREATE_SYNC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_BIG_TERMINATE_SYNC                                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_BIG_TERMINATE_SYNC_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REQUEST_PEER_SCA                                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REQUEST_PEER_SCA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SETUP_ISO_DATA_PATH                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SETUP_ISO_DATA_PATH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_REMOVE_ISO_DATA_PATH                                       (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_REMOVE_ISO_DATA_PATH_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ISO_TRANSMIT_TEST                                          (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_TRANSMIT_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ISO_RECEIVE_TEST                                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_RECEIVE_TEST_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ISO_READ_TEST_COUNTERS                                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_READ_TEST_COUNTERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ISO_TEST_END                                               (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ISO_TEST_END_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_HOST_FEATURE                                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_HOST_FEATURE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_ISO_LINK_QUALITY                                      (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_ISO_LINK_QUALITY_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_ENHANCED_READ_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_READ_REMOTE_TRANSMIT_POWER_LEVEL_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PATH_LOSS_REPORTING_PARAMETERS                         (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PATH_LOSS_REPORTING_PARAMETERS_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PATH_LOSS_REPORTING_ENABLE                             (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PATH_LOSS_REPORTING_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_TRANSMIT_POWER_REPORTING_ENABLE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST_V4                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_TRANSMITTER_TEST_V4_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 5.3).     */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_DATA_RELATED_ADDRESS_CHANGES                           (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OFG, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DATA_RELATED_ADDRESS_CHANGES_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_DEFAULT_SUBRATE                                        (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OFG, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_DEFAULT_SUBRATE_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SUBRATE_REQUEST                                            (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OFG, QAPI_BLE_HCI_COMMAND_CODE_LE_SUBRATE_REQUEST_OCF))

   /* HCI Command Code OpCode Definitions (LE Commands - Version 5.4).  */
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_v2                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA                     (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_PERIODIC_SYNC_SUBEVENT                                 (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_SET_PERIODIC_SYNC_SUBEVENT_OCF))
#define QAPI_BLE_HCI_COMMAND_OPCODE_LE_EXTENDED_CREATE_CONNECTION_V2                              (QAPI_BLE_HCI_MAKE_COMMAND_OPCODE(QAPI_BLE_HCI_COMMAND_CODE_LE_CONTROLLER_COMMANDS_OGF, QAPI_BLE_HCI_COMMAND_CODE_LE_EXTENDED_CREATE_CONNECTION_V2_OCF))

   /* HCI Event Declarations/Types/Constants.                           */
#define QAPI_BLE_HCI_EVENT_CODE_INQUIRY_COMPLETE                                 0x01
#define QAPI_BLE_HCI_EVENT_CODE_INQUIRY_RESULT                                   0x02
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTION_COMPLETE                              0x03
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTION_REQUEST                               0x04
#define QAPI_BLE_HCI_EVENT_CODE_DISCONNECTION_COMPLETE                           0x05
#define QAPI_BLE_HCI_EVENT_CODE_AUTHENTICATION_COMPLETE                          0x06
#define QAPI_BLE_HCI_EVENT_CODE_REMOTE_NAME_REQUEST_COMPLETE                     0x07
#define QAPI_BLE_HCI_EVENT_CODE_ENCRYPTION_CHANGE_EVENT                          0x08
#define QAPI_BLE_HCI_EVENT_CODE_CHANGE_CONNECTION_LINK_KEY_COMPLETE              0x09
#define QAPI_BLE_HCI_EVENT_CODE_MASTER_LINK_KEY_COMPLETE                         0x0A
#define QAPI_BLE_HCI_EVENT_CODE_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE          0x0B
#define QAPI_BLE_HCI_EVENT_CODE_READ_REMOTE_VERSION_INFORMATION_COMPLETE         0x0C
#define QAPI_BLE_HCI_EVENT_CODE_QOS_SETUP_COMPLETE                               0x0D
#define QAPI_BLE_HCI_EVENT_CODE_COMMAND_COMPLETE                                 0x0E
#define QAPI_BLE_HCI_EVENT_CODE_COMMAND_STATUS                                   0x0F
#define QAPI_BLE_HCI_EVENT_CODE_HARDWARE_ERROR                                   0x10
#define QAPI_BLE_HCI_EVENT_CODE_FLUSH_OCCURRED                                   0x11
#define QAPI_BLE_HCI_EVENT_CODE_ROLE_CHANGE                                      0x12
#define QAPI_BLE_HCI_EVENT_CODE_NUMBER_OF_COMPLETED_PACKETS                      0x13
#define QAPI_BLE_HCI_EVENT_CODE_MODE_CHANGE                                      0x14
#define QAPI_BLE_HCI_EVENT_CODE_RETURN_LINK_KEYS                                 0x15
#define QAPI_BLE_HCI_EVENT_CODE_PIN_CODE_REQUEST                                 0x16
#define QAPI_BLE_HCI_EVENT_CODE_LINK_KEY_REQUEST                                 0x17
#define QAPI_BLE_HCI_EVENT_CODE_LINK_KEY_NOTIFICATION                            0x18
#define QAPI_BLE_HCI_EVENT_CODE_LOOPBACK_COMMAND                                 0x19
#define QAPI_BLE_HCI_EVENT_CODE_DATA_BUFFER_OVERFLOW                             0x1A
#define QAPI_BLE_HCI_EVENT_CODE_MAX_SLOTS_CHANGE_EVENT                           0x1B
#define QAPI_BLE_HCI_EVENT_CODE_READ_CLOCK_OFFSET_COMPLETE                       0x1C
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTION_PACKET_TYPE_CHANGED                   0x1D
#define QAPI_BLE_HCI_EVENT_CODE_QOS_VIOLATION                                    0x1E
#define QAPI_BLE_HCI_EVENT_CODE_PAGE_SCAN_MODE_CHANGE                            0x1F
#define QAPI_BLE_HCI_EVENT_CODE_PAGE_SCAN_REPETITION_MODE_CHANGE                 0x20

#define QAPI_BLE_HCI_EVENT_CODE_BLUETOOTH_LOGO_TESTING                           0xFE
#define QAPI_BLE_HCI_EVENT_CODE_VENDOR_SPECIFIC_DEBUG                            0xFF

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 1.2.                                                  */
#define QAPI_BLE_HCI_EVENT_CODE_FLOW_SPECIFICATION_COMPLETE                      0x21
#define QAPI_BLE_HCI_EVENT_CODE_INQUIRY_RESULT_WITH_RSSI                         0x22
#define QAPI_BLE_HCI_EVENT_CODE_READ_REMOTE_EXTENDED_FEATURES_COMPLETE           0x23
#define QAPI_BLE_HCI_EVENT_CODE_SYNCHRONOUS_CONNECTION_COMPLETE                  0x2C
#define QAPI_BLE_HCI_EVENT_CODE_SYNCHRONOUS_CONNECTION_CHANGED                   0x2D

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 2.1 + EDR.                                            */
#define QAPI_BLE_HCI_EVENT_CODE_SNIFF_SUBRATING                                  0x2E
#define QAPI_BLE_HCI_EVENT_CODE_EXTENDED_INQUIRY_RESULT                          0x2F
#define QAPI_BLE_HCI_EVENT_CODE_ENCRYPTION_KEY_REFRESH_COMPLETE                  0x30
#define QAPI_BLE_HCI_EVENT_CODE_IO_CAPABILITY_REQUEST                            0x31
#define QAPI_BLE_HCI_EVENT_CODE_IO_CAPABILITY_RESPONSE                           0x32
#define QAPI_BLE_HCI_EVENT_CODE_USER_CONFIRMATION_REQUEST                        0x33
#define QAPI_BLE_HCI_EVENT_CODE_USER_PASSKEY_REQUEST                             0x34
#define QAPI_BLE_HCI_EVENT_CODE_REMOTE_OOB_DATA_REQUEST                          0x35
#define QAPI_BLE_HCI_EVENT_CODE_SIMPLE_PAIRING_COMPLETE                          0x36
#define QAPI_BLE_HCI_EVENT_CODE_LINK_SUPERVISION_TIMEOUT_CHANGED                 0x38
#define QAPI_BLE_HCI_EVENT_CODE_ENHANCED_FLUSH_COMPLETE                          0x39
#define QAPI_BLE_HCI_EVENT_CODE_USER_PASSKEY_NOTIFICATION                        0x3B
#define QAPI_BLE_HCI_EVENT_CODE_KEYPRESS_NOTIFICATION                            0x3C
#define QAPI_BLE_HCI_EVENT_CODE_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION      0x3D

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 3.0 + HS.                                             */
#define QAPI_BLE_HCI_EVENT_CODE_PHYSICAL_LINK_COMPLETE                           0x40
#define QAPI_BLE_HCI_EVENT_CODE_CHANNEL_SELECTED                                 0x41
#define QAPI_BLE_HCI_EVENT_CODE_DISCONNECTION_PHYSICAL_LINK_COMPLETE             0x42
#define QAPI_BLE_HCI_EVENT_CODE_PHYSICAL_LINK_LOSS_EARLY_WARNING                 0x43
#define QAPI_BLE_HCI_EVENT_CODE_PHYSICAL_LINK_RECOVERY                           0x44
#define QAPI_BLE_HCI_EVENT_CODE_LOGICAL_LINK_COMPLETE                            0x45
#define QAPI_BLE_HCI_EVENT_CODE_DISCONNECTION_LOGICAL_LINK_COMPLETE              0x46
#define QAPI_BLE_HCI_EVENT_CODE_FLOW_SPEC_MODIFY_COMPLETE                        0x47
#define QAPI_BLE_HCI_EVENT_CODE_NUMBER_OF_COMPLETED_DATA_BLOCKS                  0x48
#define QAPI_BLE_HCI_EVENT_CODE_AMP_START_TEST                                   0x49
#define QAPI_BLE_HCI_EVENT_CODE_AMP_TEST_END                                     0x4A
#define QAPI_BLE_HCI_EVENT_CODE_AMP_RECEIVER_REPORT                              0x4B
#define QAPI_BLE_HCI_EVENT_CODE_SHORT_RANGE_MODE_CHANGE_COMPLETE                 0x4C
#define QAPI_BLE_HCI_EVENT_CODE_AMP_STATUS_CHANGE                                0x4D

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 4.0 + LE.                                             */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event.  The Meta event      */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_EVENT_CODE_LE_META                                          0x3E

   /* The following block of HCI Sub Event Declarations/Type/Constants  */
   /* are for Version 4.0 + LE.                                         */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event.  The Meta event      */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_CONNECTION_COMPLETE                        0x01
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_ADVERTISING_REPORT                         0x02
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_CONNECTION_UPDATE_COMPLETE                 0x03
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_READ_REMOTE_USED_FEATURES_COMPLETE         0x04
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_LONG_TERM_KEY_REQUEST                      0x05

   /* The following block of HCI Sub Event Declarations/Type/Constants  */
   /* are for Version 4.1.                                              */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event.  The Meta event      */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_REMOTE_CONNECTION_PARAMETER_REQUEST        0x06

   /* The following block of HCI Sub Event Declarations/Type/Constants  */
   /* are for Version 4.2.                                              */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event.  The Meta event      */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_DATA_LENGTH_CHANGE                         0x07
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE        0x08
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_GENERATE_DHKEY_COMPLETE                    0x09
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_ENHANCED_CONNECTION_COMPLETE               0x0A
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_DIRECT_ADVERTISING_REPORT                  0x0B

   /* The following block of HCI Sub Event Declarations/Type/Constants  */
   /* are for Version 5.0.                                              */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event. The Meta event       */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PHY_UPDATE_COMPLETE                        0x0C
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_EXTENDED_ADVERTISING_REPORT                0x0D
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED      0x0E
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_REPORT                0x0F
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_SYNC_LOST             0x10
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_SCAN_TIMEOUT                               0x11
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_ADVERTISING_SET_TERMINATED                 0x12
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_SCAN_REQUEST_RECEIVED                      0x13
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_CHANNEL_SELECTION_ALGORITHM                0x14

   /* The following block of HCI Sub Event Declarations/Type/Constants  */
   /* are for Core - Version 5.4.                                       */
   /* * NOTE * All Bluetooth Low Energy (LE) events are grouped under a */
   /*          single event called the Meta event.  The Meta event      */
   /*          contains a Sub Event Code that actually specifies the    */
   /*          Bluetooth Low Energy (LE) event code.                    */
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST     0x27
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT           0x28
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2       0x24
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_REPORT_V2                 0x25
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2 0x26
#define QAPI_BLE_HCI_SUBEVENT_CODE_LE_ENHANCED_CONNECTION_COMPLETE_V2                0x29

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 4.0 + CSA4.                                           */
#define QAPI_BLE_HCI_EVENT_CODE_TRIGGERED_CLOCK_CAPTURE                             0x4E
#define QAPI_BLE_HCI_EVENT_CODE_SYCHRONIZATION_TRAIN_COMPLETE                       0x4F
#define QAPI_BLE_HCI_EVENT_CODE_SYCHRONIZATION_TRAIN_RECEIVED                       0x50
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE              0x51
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTIONLESS_SLAVE_BROADCAST_TIMEOUT              0x52
#define QAPI_BLE_HCI_EVENT_CODE_TRUNCATED_PAGE_COMPLETE                             0x53
#define QAPI_BLE_HCI_EVENT_CODE_SLAVE_PAGE_RESPONSE_TIMEOUT                         0x54
#define QAPI_BLE_HCI_EVENT_CODE_CONNECTIONLESS_SLAVE_BROADCAST_CHANNEL_MAP_CHANGE   0x55
#define QAPI_BLE_HCI_EVENT_CODE_INQUIRY_RESPONSE_NOTIFICATION                       0x56

   /* The following block of HCI Event Declarations/Type/Constants are  */
   /* for Version 4.1.                                                  */
#define QAPI_BLE_HCI_EVENT_CODE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED               0x57

   /* HCI Error Code Definitions/Constants.                             */
#define QAPI_BLE_HCI_ERROR_CODE_NO_ERROR                                           0x00
#define QAPI_BLE_HCI_ERROR_CODE_UNKNOWN_HCI_COMMAND                                0x01
#define QAPI_BLE_HCI_ERROR_CODE_NO_CONNECTION                                      0x02
#define QAPI_BLE_HCI_ERROR_CODE_HARDWARE_FAILURE                                   0x03
#define QAPI_BLE_HCI_ERROR_CODE_PAGE_TIMEOUT                                       0x04
#define QAPI_BLE_HCI_ERROR_CODE_AUTHENTICATION_FAILURE                             0x05
#define QAPI_BLE_HCI_ERROR_CODE_KEY_MISSING                                        0x06
#define QAPI_BLE_HCI_ERROR_CODE_MEMORY_FULL                                        0x07
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_TIMEOUT                                 0x08
#define QAPI_BLE_HCI_ERROR_CODE_MAX_NUMBER_OF_CONNECTIONS                          0x09
#define QAPI_BLE_HCI_ERROR_CODE_MAX_NUMBER_OF_SCO_CONNECTIONS_TO_A_DEVICE          0x0A
#define QAPI_BLE_HCI_ERROR_CODE_ACL_CONNECTION_ALREADY_EXISTS                      0x0B
#define QAPI_BLE_HCI_ERROR_CODE_COMMAND_DISALLOWED                                 0x0C
#define QAPI_BLE_HCI_ERROR_CODE_HOST_REJECTED_DUE_TO_LIMITED_RESOURCES             0x0D
#define QAPI_BLE_HCI_ERROR_CODE_HOST_REJECTED_DUE_TO_SECURITY_REASONS              0x0E
#define QAPI_BLE_HCI_ERROR_CODE_HOST_REJECTED_DUE_TO_REMOTE_DEVICE_IS_PERSONAL     0x0F
#define QAPI_BLE_HCI_ERROR_CODE_HOST_TIMEOUT                                       0x10
#define QAPI_BLE_HCI_ERROR_CODE_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE             0x11
#define QAPI_BLE_HCI_ERROR_CODE_INVALID_HCI_COMMAND_PARAMETERS                     0x12
#define QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_USER_ENDED         0x13
#define QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_LOW_RESOURCES      0x14
#define QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_ABOUT_TO_PWR_OFF   0x15
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_TERMINATED_BY_LOCAL_HOST                0x16
#define QAPI_BLE_HCI_ERROR_CODE_REPEATED_ATTEMPTS                                  0x17
#define QAPI_BLE_HCI_ERROR_CODE_PAIRING_NOT_ALLOWED                                0x18
#define QAPI_BLE_HCI_ERROR_CODE_UNKNOWN_LMP_PDU                                    0x19
#define QAPI_BLE_HCI_ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE                         0x1A
#define QAPI_BLE_HCI_ERROR_CODE_SCO_OFFSET_REJECTED                                0x1B
#define QAPI_BLE_HCI_ERROR_CODE_SCO_INTERVAL_REJECTED                              0x1C
#define QAPI_BLE_HCI_ERROR_CODE_SCO_AIR_MODE_REJECTED                              0x1D
#define QAPI_BLE_HCI_ERROR_CODE_INVALID_LMP_PARAMETERS                             0x1E
#define QAPI_BLE_HCI_ERROR_CODE_UNSPECIFIED_ERROR                                  0x1F
#define QAPI_BLE_HCI_ERROR_CODE_UNSUPPORTED_LMP_PARAMETER_VALUE                    0x20
#define QAPI_BLE_HCI_ERROR_CODE_ROLE_CHANGE_NOT_ALLOWED                            0x21
#define QAPI_BLE_HCI_ERROR_CODE_LMP_RESPONSE_TIMEOUT                               0x22
#define QAPI_BLE_HCI_ERROR_CODE_LMP_ERROR_TRANSACTION_COLLISION                    0x23

   /* HCI Error Code Definitions/Constants (Version 1.1).               */
#define QAPI_BLE_HCI_ERROR_CODE_LMP_PDU_NOT_ALLOWED                                0x24
#define QAPI_BLE_HCI_ERROR_CODE_ENCRYPTION_MODE_NOT_ACCEPTABLE                     0x25
#define QAPI_BLE_HCI_ERROR_CODE_UNIT_KEY_USED                                      0x26
#define QAPI_BLE_HCI_ERROR_CODE_QOS_NOT_SUPPORTED                                  0x27
#define QAPI_BLE_HCI_ERROR_CODE_INSTANT_PASSED                                     0x28
#define QAPI_BLE_HCI_ERROR_CODE_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                0x29

   /* HCI Error Code Definitions/Constants (Version 1.2).               */
#define QAPI_BLE_HCI_ERROR_CODE_SUCCESS                                            0x00
#define QAPI_BLE_HCI_ERROR_CODE_UNKNOWN_CONNECTION_IDENTIFIER                      0x02
#define QAPI_BLE_HCI_ERROR_CODE_PIN_MISSING                                        0x06
#define QAPI_BLE_HCI_ERROR_CODE_MEMORY_CAPACITY_EXCEEDED                           0x07
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_LIMIT_EXCEEDED                          0x09
#define QAPI_BLE_HCI_ERROR_CODE_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED  0x0A
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES       0x0D
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS        0x0E
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR    0x0F
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED                 0x10
#define QAPI_BLE_HCI_ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION                  0x13
#define QAPI_BLE_HCI_ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_LOW_RESOURCES  0x14
#define QAPI_BLE_HCI_ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_PWR_OFF 0x15
#define QAPI_BLE_HCI_ERROR_CODE_LINK_KEY_CANNOT_BE_CHANGED                         0x26
#define QAPI_BLE_HCI_ERROR_CODE_REQUESTED_QOS_NOT_SUPPORTED                        0x27
#define QAPI_BLE_HCI_ERROR_CODE_DIFFERENT_TRANSACTION_COLLISION                    0x2A
#define QAPI_BLE_HCI_ERROR_CODE_QOS_UNACCEPTABLE_PARAMETER                         0x2C
#define QAPI_BLE_HCI_ERROR_CODE_QOS_REJECTED                                       0x2D
#define QAPI_BLE_HCI_ERROR_CODE_CHANNEL_CLASSIFICATION_NOT_SUPPORTED               0x2E
#define QAPI_BLE_HCI_ERROR_CODE_INSUFFICIENT_SECURITY                              0x2F
#define QAPI_BLE_HCI_ERROR_CODE_PARAMETER_OUT_OF_MANDATORY_RANGE                   0x30
#define QAPI_BLE_HCI_ERROR_CODE_ROLE_SWITCH_PENDING                                0x32
#define QAPI_BLE_HCI_ERROR_CODE_RESERVED_SLOT_VIOLATION                            0x34
#define QAPI_BLE_HCI_ERROR_CODE_ROLE_SWITCH_FAILED                                 0x35

   /* HCI Error Code Definitions/Constants (Version 2.1 + EDR).         */
#define QAPI_BLE_HCI_ERROR_CODE_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE                0x36
#define QAPI_BLE_HCI_ERROR_CODE_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST        0x37
#define QAPI_BLE_HCI_ERROR_CODE_HOST_BUSY_PAIRING                                  0x38

   /* HCI Error Code Definitions/Constants (Version 3.0 + HS).          */
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_REJECTED_NO_SUITABLE_CHANNEL_FOUND      0x39

   /* HCI Error Code Definitions/Constants (Version 4.0 + LE).          */
#define QAPI_BLE_HCI_ERROR_CODE_CONTROLLER_BUSY                                    0x3A
#define QAPI_BLE_HCI_ERROR_CODE_UNACCEPTABLE_CONNECTION_INTERVAL                   0x3B
#define QAPI_BLE_HCI_ERROR_CODE_DIRECTED_ADVERTISING_TIMEOUT                       0x3C
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_FAILED_DUE_TO_MIC_FAILURE               0x3D
#define QAPI_BLE_HCI_ERROR_CODE_CONNECTION_FAILED_TO_BE_ESTABLISHED                0x3E
#define QAPI_BLE_HCI_ERROR_CODE_MAC_CONNECTION_FAILED                              0x3F

   /* HCI Error Code Definitions/Constants (Version 4.1).               */
#define QAPI_BLE_HCI_ERROR_CODE_COARSE_CLOCK_ADJUST_REJECTED_USING_CLOCK_DRAGGING  0x40

   /* HCI Error Code Definitions/Constants (Version 5.0).               */
#define QAPI_BLE_HCI_ERROR_CODE_TYPE0_SUBMAP_NOT_DEFINED                           0x41
#define QAPI_BLE_HCI_ERROR_CODE_UNKNOWN_ADVERTISING_IDENTIFIER                     0x42
#define QAPI_BLE_HCI_ERROR_CODE_LIMIT_REACHED                                      0x43
#define QAPI_BLE_HCI_ERROR_CODE_OPERATION_CANCELLED_BY_HOST                        0x44

   /* HCI Command Definitions/Constants.                                */

   /* The following type declaration represents the structure of the    */
   /* Header of an HCI Command Packet.  This Header Information is      */
   /* contained in Every Defined HCI Command Packet.  This structure    */
   /* forms the basis of additional defined HCI Command Packets.  Since */
   /* this structure is present at the begining of Every Defined HCI    */
   /* Command Packet, this structure will be the first element of Every */
   /* Defined HCI Command Packet in this file.                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Command_Header_s
{
   qapi_BLE_NonAlignedWord_t Command_OpCode;
   qapi_BLE_NonAlignedByte_t Parameter_Total_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Command_Header_t;

#define QAPI_BLE_HCI_COMMAND_HEADER_SIZE                          (sizeof(qapi_BLE_HCI_Command_Header_t))

#define QAPI_BLE_HCI_COMMAND_MAX_SIZE                             (sizeof(qapi_BLE_HCI_Command_Header_t) + (sizeof(uint8_t)*256))

   /* HCI Command Definitions (Link Control).                           */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_LAP_t                LAP;
   uint8_t                       Inquiry_Length;
   uint8_t                       Num_Responses;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Command_t;

#define QAPI_BLE_HCI_INQUIRY_COMMAND_SIZE                         (sizeof(qapi_BLE_HCI_Inquiry_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Cancel_Command_t;

#define QAPI_BLE_HCI_INQUIRY_CANCEL_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Inquiry_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Max_Period_Length;
   qapi_BLE_NonAlignedWord_t     Min_Period_Length;
   qapi_BLE_LAP_t                LAP;
   uint8_t                       Inquiry_Length;
   uint8_t                       Num_Responses;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_t;

#define QAPI_BLE_HCI_PERIODIC_INQUIRY_MODE_COMMAND_SIZE           (sizeof(qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_t;

#define QAPI_BLE_HCI_EXIT_PERIODIC_INQUIRY_MODE_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
   uint8_t                       Page_Scan_Repetition_Mode;
   uint8_t                       Page_Scan_Mode;
   qapi_BLE_NonAlignedWord_t     Clock_Offset;
   uint8_t                       Allow_Role_Switch;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Connection_Command_t;

#define QAPI_BLE_HCI_CREATE_CONNECTION_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Create_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Command_t;

#define QAPI_BLE_HCI_DISCONNECT_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_Disconnect_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Add_SCO_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Add_SCO_Connection_Command_t;

#define QAPI_BLE_HCI_ADD_SCO_CONNECTION_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Add_SCO_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Connection_Request_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Role;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Connection_Request_Command_t;

#define QAPI_BLE_HCI_ACCEPT_CONNECTION_REQUEST_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Accept_Connection_Request_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reject_Connection_Request_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reject_Connection_Request_Command_t;

#define QAPI_BLE_HCI_REJECT_CONNECTION_REQUEST_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Reject_Connection_Request_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_Link_Key_t           Link_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Request_Reply_Command_t;

#define QAPI_BLE_HCI_LINK_KEY_REQUEST_REPLY_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Link_Key_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_LINK_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_PIN_Code_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       PIN_Code_Length;
   qapi_BLE_PIN_Code_t           PIN_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_PIN_Code_Request_Reply_Command_t;

#define QAPI_BLE_HCI_PIN_CODE_REQUEST_REPLY_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_PIN_Code_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_PIN_CODE_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE (sizeof(qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Connection_Packet_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Connection_Packet_Type_Command_t;

#define QAPI_BLE_HCI_CHANGE_CONNECTION_PACKET_TYPE_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Change_Connection_Packet_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Authentication_Requested_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Authentication_Requested_Command_t;

#define QAPI_BLE_HCI_AUTHENTICATION_REQUESTED_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Authentication_Requested_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connection_Encryption_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Encryption_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connection_Encryption_Command_t;

#define QAPI_BLE_HCI_SET_CONNECTION_ENCRYPTION_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Set_Connection_Encryption_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Connection_Link_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Connection_Link_Key_Command_t;

#define QAPI_BLE_HCI_CHANGE_CONNECTION_LINK_KEY_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Change_Connection_Link_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Master_Link_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Key_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Master_Link_Key_Command_t;

#define QAPI_BLE_HCI_MASTER_LINK_KEY_COMMAND_SIZE                 (sizeof(qapi_BLE_HCI_Master_Link_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Name_Request_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Page_Scan_Repetition_Mode;
   uint8_t                       Page_Scan_Mode;
   qapi_BLE_NonAlignedWord_t     Clock_Offset;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Name_Request_Command_t;

#define QAPI_BLE_HCI_REMOTE_NAME_REQUEST_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Remote_Name_Request_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Supported_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Supported_Features_Command_t;

#define QAPI_BLE_HCI_READ_REMOTE_SUPPORTED_FEATURES_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Remote_Supported_Features_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Version_Information_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Version_Information_Command_t;

#define QAPI_BLE_HCI_READ_REMOTE_VERSION_INFORMATION_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Version_Information_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Clock_Offset_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Clock_Offset_Command_t;

#define QAPI_BLE_HCI_READ_CLOCK_OFFSET_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Read_Clock_Offset_Command_t))

   /* HCI Command Definitions (Link Control - Version 1.2).             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Connection_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Connection_Cancel_Command_t;

#define QAPI_BLE_HCI_CREATE_CONNECTION_CANCEL_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Create_Connection_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_t;

#define QAPI_BLE_HCI_REMOTE_NAME_REQUEST_CANCEL_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Extended_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Page_Number;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Extended_Features_Command_t;

#define QAPI_BLE_HCI_READ_REMOTE_EXTENDED_FEATURES_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Remote_Extended_Features_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_LMP_Handle_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_LMP_Handle_Command_t;

#define QAPI_BLE_HCI_READ_LMP_HANDLE_COMMAND_SIZE                 (sizeof(qapi_BLE_HCI_Read_LMP_Handle_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Setup_Synchronous_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedDWord_t    Transmit_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Receive_Bandwidth;
   qapi_BLE_NonAlignedWord_t     Max_Latency;
   qapi_BLE_NonAlignedWord_t     Voice_Setting;
   uint8_t                       Retransmission_Effort;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Setup_Synchronous_Connection_Command_t;

#define QAPI_BLE_HCI_SETUP_SYNCHRONOUS_CONNECTION_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Setup_Synchronous_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Synchronous_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_NonAlignedDWord_t    Transmit_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Receive_Bandwidth;
   qapi_BLE_NonAlignedWord_t     Max_Latency;
   qapi_BLE_NonAlignedWord_t     Content_Format;
   uint8_t                       Retransmission_Effort;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Synchronous_Connection_Command_t;

#define QAPI_BLE_HCI_ACCEPT_SYNCHRONOUS_CONNECTION_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Accept_Synchronous_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reject_Synchronous_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reject_Synchronous_Connection_Command_t;

#define QAPI_BLE_HCI_REJECT_SYNCHRONOUS_CONNECTION_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Reject_Synchronous_Connection_Command_t))

   /* HCI Command Definitions (Link Control - Version 2.1 + EDR).       */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       IO_Capability;
   uint8_t                       OOB_Data_Present;
   uint8_t                       Authentication_Requirements;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Request_Reply_Command_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_REQUEST_REPLY_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_IO_Capability_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_t;

#define QAPI_BLE_HCI_USER_CONFIRMATION_REQUEST_REPLY_COMMAND_SIZE (sizeof(qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE (sizeof(qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_NonAlignedDWord_t    Numeric_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Request_Reply_Command_t;

#define QAPI_BLE_HCI_USER_PASSKEY_REQUEST_REPLY_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_User_Passkey_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t        HCI_Command_Header;
   qapi_BLE_BD_ADDR_t                   BD_ADDR;
   qapi_BLE_Simple_Pairing_Hash_t       Simple_Pairing_Hash;
   qapi_BLE_Simple_Pairing_Randomizer_t Simple_Pairing_Randomizer;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_t;

#define QAPI_BLE_HCI_REMOTE_OOB_DATA_REQUEST_REPLY_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_t))

   /* HCI Command Definitions (Link Control - Version 3.0 + HS).        */

   /* Note that the Link_Key[] parameter is a variable length field that*/
   /* contains zero or more bytes.                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Physical_Link_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   uint8_t                       Dedicated_AMP_Key_Length;
   uint8_t                       Dedicated_AMP_Key_Type;
   uint8_t                       Dedicated_AMP_Key[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Physical_Link_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Create     */
   /* Physical Link Command Data Structure based upon the number of     */
   /* individual AMP Key bytes associated with the Command.  The first  */
   /* parameter to this MACRO is the size (in Bytes) of the Dedicated   */
   /* AMP Key Data that is to be part of the Create Physical Link       */
   /* Command.                                                          */
#define QAPI_BLE_HCI_CREATE_PHYSICAL_LINK_COMMAND_SIZE(_x)        (sizeof(qapi_BLE_HCI_Create_Physical_Link_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* Note that the Dedicate_AMP_Key[] parameter is a variable length   */
   /* field that contains zero or more bytes.                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Physical_Link_Request_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   uint8_t                       Dedicated_AMP_Key_Length;
   uint8_t                       Dedicated_AMP_Key_Type;
   uint8_t                       Dedicated_AMP_Key[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Physical_Link_Request_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Accept     */
   /* Physical Link Request Command Data Structure based upon the number*/
   /* of individual AMP Key bytes associated with the Command.  The     */
   /* first parameter to this MACRO is the size (in Bytes) of the       */
   /* Dedicated AMP Key Data that is to be part of the Accept Physical  */
   /* Link Request Command.                                             */
#define QAPI_BLE_HCI_ACCEPT_PHYSICAL_LINK_REQUEST_COMMAND_SIZE(_x)   (sizeof(qapi_BLE_HCI_Accept_Physical_Link_Request_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Physical_Link_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Physical_Link_Command_t;

#define QAPI_BLE_HCI_DISCONNECT_PHYSICAL_LINK_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Disconnect_Physical_Link_Command_t))

    /* The following structure represents the format of an Extended Flow*/
    /* Spec container.  The Extended Flow Spec is used with various HCI */
    /* Commands/Events (Version 3.0 + HS).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Extended_Flow_Spec_s
{
   uint8_t                       Identifier;
   uint8_t                       Service_Type;
   qapi_BLE_NonAlignedWord_t     Maximum_SDU_Size;
   qapi_BLE_NonAlignedDWord_t    SDU_Inter_Arrival_Time;
   qapi_BLE_NonAlignedDWord_t    Access_Latency;
   qapi_BLE_NonAlignedDWord_t    Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Extended_Flow_Spec_t;

#define QAPI_BLE_HCI_EXTENDED_FLOW_SPEC_SIZE                      (sizeof(qapi_BLE_HCI_Extended_Flow_Spec_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Logical_Link_Command_s
{
   qapi_BLE_HCI_Command_Header_t     HCI_Command_Header;
   uint8_t                           Physical_Link_Handle;
   qapi_BLE_HCI_Extended_Flow_Spec_t Tx_Flow_Spec;
   qapi_BLE_HCI_Extended_Flow_Spec_t Rx_Flow_Spec;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Logical_Link_Command_t;

#define QAPI_BLE_HCI_CREATE_LOGICAL_LINK_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Create_Logical_Link_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Logical_Link_Command_s
{
   qapi_BLE_HCI_Command_Header_t     HCI_Command_Header;
   uint8_t                           Physical_Link_Handle;
   qapi_BLE_HCI_Extended_Flow_Spec_t Tx_Flow_Spec;
   qapi_BLE_HCI_Extended_Flow_Spec_t Rx_Flow_Spec;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Logical_Link_Command_t;

#define QAPI_BLE_HCI_ACCEPT_LOGICAL_LINK_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Accept_Logical_Link_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Logical_Link_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Logical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Logical_Link_Command_t;

#define QAPI_BLE_HCI_DISCONNECT_LOGICAL_LINK_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Disconnect_Logical_Link_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Logical_Link_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   uint8_t                       Tx_Flow_Spec_ID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Logical_Link_Cancel_Command_t;

#define QAPI_BLE_HCI_LOGICAL_LINK_CANCEL_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Logical_Link_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Spec_Modify_Command_s
{
   qapi_BLE_HCI_Command_Header_t     HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t         Handle;
   qapi_BLE_HCI_Extended_Flow_Spec_t Tx_Flow_Spec;
   qapi_BLE_HCI_Extended_Flow_Spec_t Rx_Flow_Spec;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Spec_Modify_Command_t;

#define QAPI_BLE_HCI_FLOW_SPEC_MODIFY_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Flow_Spec_Modify_Command_t))

   /* HCI Command Definitions (Link Control - Version 4.0 + CSA2).      */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedDWord_t    Transmit_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Receive_Bandwidth;
   qapi_BLE_SCO_Coding_Format_t  Transmit_Coding_Format;
   qapi_BLE_SCO_Coding_Format_t  Receive_Coding_Format;
   qapi_BLE_NonAlignedWord_t     Transmit_Codec_Frame_Size;
   qapi_BLE_NonAlignedWord_t     Receive_Codec_Frame_Size;
   qapi_BLE_NonAlignedDWord_t    Input_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Output_Bandwidth;
   qapi_BLE_SCO_Coding_Format_t  Input_Coding_Format;
   qapi_BLE_SCO_Coding_Format_t  Output_Coding_Format;
   qapi_BLE_NonAlignedWord_t     Input_Coded_Data_Size;
   qapi_BLE_NonAlignedWord_t     Output_Coded_Data_Size;
   qapi_BLE_NonAlignedByte_t     Input_PCM_Data_Format;
   qapi_BLE_NonAlignedByte_t     Output_PCM_Data_Format;
   qapi_BLE_NonAlignedByte_t     Input_PCM_Sample_Payload_MSB_Position;
   qapi_BLE_NonAlignedByte_t     Output_PCM_Sample_Payload_MSB_Position;
   qapi_BLE_NonAlignedByte_t     Input_Data_Path;
   qapi_BLE_NonAlignedByte_t     Output_Data_Path;
   qapi_BLE_NonAlignedByte_t     Input_Transport_Unit_Size;
   qapi_BLE_NonAlignedByte_t     Output_Transport_Unit_Size;
   qapi_BLE_NonAlignedWord_t     Max_Latency;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
   qapi_BLE_NonAlignedByte_t     Retransmission_Effort;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_t;

#define QAPI_BLE_HCI_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_NonAlignedDWord_t    Transmit_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Receive_Bandwidth;
   qapi_BLE_SCO_Coding_Format_t  Transmit_Coding_Format;
   qapi_BLE_SCO_Coding_Format_t  Receive_Coding_Format;
   qapi_BLE_NonAlignedWord_t     Transmit_Codec_Frame_Size;
   qapi_BLE_NonAlignedWord_t     Receive_Codec_Frame_Size;
   qapi_BLE_NonAlignedDWord_t    Input_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Output_Bandwidth;
   qapi_BLE_SCO_Coding_Format_t  Input_Coding_Format;
   qapi_BLE_SCO_Coding_Format_t  Output_Coding_Format;
   qapi_BLE_NonAlignedWord_t     Input_Coded_Data_Size;
   qapi_BLE_NonAlignedWord_t     Output_Coded_Data_Size;
   qapi_BLE_NonAlignedByte_t     Input_PCM_Data_Format;
   qapi_BLE_NonAlignedByte_t     Output_PCM_Data_Format;
   qapi_BLE_NonAlignedByte_t     Input_PCM_Sample_Payload_MSB_Position;
   qapi_BLE_NonAlignedByte_t     Output_PCM_Sample_Payload_MSB_Position;
   qapi_BLE_NonAlignedByte_t     Input_Data_Path;
   qapi_BLE_NonAlignedByte_t     Output_Data_Path;
   qapi_BLE_NonAlignedByte_t     Input_Transport_Unit_Size;
   qapi_BLE_NonAlignedByte_t     Output_Transport_Unit_Size;
   qapi_BLE_NonAlignedWord_t     Max_Latency;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
   qapi_BLE_NonAlignedByte_t     Retransmission_Effort;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_t;

#define QAPI_BLE_HCI_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_t))

   /* HCI Command Definitions (Link Control - Version 4.0 + CSA4).      */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Truncated_Page_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Page_Scan_Repetition_Mode;
   qapi_BLE_NonAlignedWord_t     Clock_Offset;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Truncated_Page_Command_t;

#define QAPI_BLE_HCI_TRUNCATED_PAGE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Truncated_Page_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Truncated_Page_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Truncated_Page_Cancel_Command_t;

#define QAPI_BLE_HCI_TRUNCATED_PAGE_CANCEL_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Truncated_Page_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Enable;
   uint8_t                       LT_ADDR;
   uint8_t                       LPO_Allowed;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
   qapi_BLE_NonAlignedWord_t     Interval_Min;
   qapi_BLE_NonAlignedWord_t     Interval_Max;
   qapi_BLE_NonAlignedWord_t     CSB_Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_t;

#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Enable;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       LT_ADDR;
   qapi_BLE_NonAlignedWord_t     Interval;
   qapi_BLE_NonAlignedDWord_t    Clock_Offset;
   qapi_BLE_NonAlignedDWord_t    Next_CSB_Clock;
   qapi_BLE_NonAlignedWord_t     CSB_Supervision_Timeout;
   uint8_t                       Remote_Timing_Accuracy;
   uint8_t                       Skip;
   qapi_BLE_NonAlignedWord_t     Packet_Type;
   qapi_BLE_AFH_Channel_Map_t    AFH_Channel_Map;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_t;

#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Start_Synchronization_Train_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Start_Synchronization_Train_Command_t;

#define QAPI_BLE_HCI_START_SYNCHRONIZATION_TRAIN_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Start_Synchronization_Train_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Receive_Synchronization_Train_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   qapi_BLE_NonAlignedWord_t     Sync_Scan_Timeout;
   qapi_BLE_NonAlignedWord_t     Sync_Scan_Window;
   qapi_BLE_NonAlignedWord_t     Sync_Scan_Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Receive_Synchronization_Train_Command_t;

#define QAPI_BLE_HCI_RECEIVE_SYNCHRONIZATION_TRAIN_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Receive_Synchronization_Train_Command_t))

   /* HCI Command Definitions (Link Control - Version 4.1).             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t        HCI_Command_Header;
   qapi_BLE_BD_ADDR_t                   BD_ADDR;
   qapi_BLE_Simple_Pairing_Hash_t       C_192;
   qapi_BLE_Simple_Pairing_Randomizer_t R_192;
   qapi_BLE_Simple_Pairing_Hash_t       C_256;
   qapi_BLE_Simple_Pairing_Randomizer_t R_256;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_t;

#define QAPI_BLE_HCI_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_t))

   /* HCI Command Definitions (Link Policy).                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Hold_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Hold_Mode_Max_Interval;
   qapi_BLE_NonAlignedWord_t     Hold_Mode_Min_Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Hold_Mode_Command_t;

#define QAPI_BLE_HCI_HOLD_MODE_COMMAND_SIZE                       (sizeof(qapi_BLE_HCI_Hold_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Sniff_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Sniff_Max_Interval;
   qapi_BLE_NonAlignedWord_t     Sniff_Min_Interval;
   qapi_BLE_NonAlignedWord_t     Sniff_Attempt;
   qapi_BLE_NonAlignedWord_t     Sniff_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Sniff_Mode_Command_t;

#define QAPI_BLE_HCI_SNIFF_MODE_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_Sniff_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Sniff_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Sniff_Mode_Command_t;

#define QAPI_BLE_HCI_EXIT_SNIFF_MODE_COMMAND_SIZE                 (sizeof(qapi_BLE_HCI_Exit_Sniff_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Park_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Beacon_Max_Interval;
   qapi_BLE_NonAlignedWord_t     Beacon_Min_Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Park_Mode_Command_t;

#define QAPI_BLE_HCI_PARK_MODE_COMMAND_SIZE                       (sizeof(qapi_BLE_HCI_Park_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Park_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Park_Mode_Command_t;

#define QAPI_BLE_HCI_EXIT_PARK_MODE_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Exit_Park_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_QoS_Setup_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Flags;
   uint8_t                       Service_Type;
   qapi_BLE_NonAlignedDWord_t    Token_Rate;
   qapi_BLE_NonAlignedDWord_t    Peak_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Latency;
   qapi_BLE_NonAlignedDWord_t    Delay_Variation;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_QoS_Setup_Command_t;

#define QAPI_BLE_HCI_QOS_SETUP_COMMAND_SIZE                       (sizeof(qapi_BLE_HCI_QoS_Setup_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Role_Discovery_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Role_Discovery_Command_t;

#define QAPI_BLE_HCI_ROLE_DISCOVERY_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Role_Discovery_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Switch_Role_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Role;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Switch_Role_Command_t;

#define QAPI_BLE_HCI_SWITCH_ROLE_COMMAND_SIZE                     (sizeof(qapi_BLE_HCI_Switch_Role_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Link_Policy_Settings_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Link_Policy_Settings_Command_t;

#define QAPI_BLE_HCI_READ_LINK_POLICY_SETTINGS_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Read_Link_Policy_Settings_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Link_Policy_Settings_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Link_Policy_Settings;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Link_Policy_Settings_Command_t;

#define QAPI_BLE_HCI_WRITE_LINK_POLICY_SETTINGS_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Write_Link_Policy_Settings_Command_t))

   /* HCI Command Definitions (Link Policy - Version 1.2).              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_t;

#define QAPI_BLE_HCI_READ_DEFAULT_LINK_POLICY_SETTINGS_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Link_Policy_Settings;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_t;

#define QAPI_BLE_HCI_WRITE_DEFAULT_LINK_POLICY_SETTINGS_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Specification_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Flags;
   uint8_t                       Flow_Direction;
   uint8_t                       Service_Type;
   qapi_BLE_NonAlignedDWord_t    Token_Rate;
   qapi_BLE_NonAlignedDWord_t    Token_Bucket_Size;
   qapi_BLE_NonAlignedDWord_t    Peak_Bandwidth;
   qapi_BLE_NonAlignedDWord_t    Access_Latency;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Specification_Command_t;

#define QAPI_BLE_HCI_FLOW_SPECIFICATION_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Flow_Specification_Command_t))

   /* HCI Command Definitions (Link Policy - Version 2.1 + EDR).        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Sniff_Subrating_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Maximum_Latency;
   qapi_BLE_NonAlignedWord_t     Minimum_Remote_Timeout;
   qapi_BLE_NonAlignedWord_t     Minimum_Local_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Sniff_Subrating_Command_t;

#define QAPI_BLE_HCI_SNIFF_SUBRATING_COMMAND_SIZE                 (sizeof(qapi_BLE_HCI_Sniff_Subrating_Command_t))

   /* HCI Command Definitions (Host Control and Baseband).              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Mask_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_Event_Mask_t         Event_Mask;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Mask_Command_t;

#define QAPI_BLE_HCI_SET_EVENT_MASK_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Set_Event_Mask_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reset_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reset_Command_t;

#define QAPI_BLE_HCI_RESET_COMMAND_SIZE                           (sizeof(qapi_BLE_HCI_Reset_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Filter_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Filter_Type;
   uint8_t                       Filter_Condition_Type;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Filter_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Set Event Filter Command Data Structure based upon the size of*/
   /* the Condition Information associated with the Command. The first  */
   /* parameter to this MACRO is the size (in Bytes) of the Condition   */
   /* Data that is to be part of the Set Event Filter Command.          */
#define QAPI_BLE_HCI_SET_EVENT_FILTER_COMMAND_SIZE(_x)            (sizeof(qapi_BLE_HCI_Set_Event_Filter_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flush_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flush_Command_t;

#define QAPI_BLE_HCI_FLUSH_COMMAND_SIZE                           (sizeof(qapi_BLE_HCI_Flush_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_PIN_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_PIN_Type_Command_t;

#define QAPI_BLE_HCI_READ_PIN_TYPE_COMMAND_SIZE                   (sizeof(qapi_BLE_HCI_Read_PIN_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_PIN_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               PIN_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_PIN_Type_Command_t;

#define QAPI_BLE_HCI_WRITE_PIN_TYPE_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Write_PIN_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_New_Unit_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_New_Unit_Key_Command_t;

#define QAPI_BLE_HCI_CREATE_NEW_UNIT_KEY_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Create_New_Unit_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Stored_Link_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Read_All_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Stored_Link_Key_Command_t;

#define QAPI_BLE_HCI_READ_STORED_LINK_KEY_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Stored_Link_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Stored_Link_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Num_Keys_To_Write;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Stored_Link_Key_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Write Stored Link Key Command Data Structure based upon the   */
   /* Number of BD_ADDR/Link Key Pairs that are required.  The first    */
   /* parameter to this MACRO is the Number of BD_ADDR/Link Key Pairs.  */
#define QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_SIZE(_x)       ((sizeof(qapi_BLE_HCI_Write_Stored_Link_Key_Command_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_BD_ADDR_t)+sizeof(qapi_BLE_Link_Key_t))))

   /* The following definition exists to define the Total Number of     */
   /* Stored Link Key's that can be supported by a single               */
   /* qapi_BLE_HCI_Write_Stored_Link_Key_Command_t Command Packet.      */
#define QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_MAX_KEYS       (((sizeof(uint8_t)*256) - QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_SIZE(0))/(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(qapi_BLE_Link_Key_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified BD_ADDR in the HCI Write Stored    */
   /* Link Key Command Data.  The first parameter is a pointer to a Data*/
   /* Buffer that is an qapi_BLE_HCI_Write_Stored_Link_Key_Command_t.   */
   /* The Second parameter is the Index of the BD_ADDR to Set, and the  */
   /* Third parameter is the BD_ADDR value to set.                      */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_SET_BD_ADDR(_x, _y, _z)                                                                           \
{                                                                                                                                           \
   ASSIGN_UNALIGNED_GENERIC_TYPE(((qapi_BLE_BD_ADDR_t *)(((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(qapi_BLE_Link_Key_t)))), (_z)); \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Link Key in the HCI Write Stored   */
   /* Link Key Command Data.  The first parameter is a pointer to a Data*/
   /* Buffer that is an qapi_BLE_HCI_Write_Stored_Link_Key_Command_t.   */
   /* The Second parameter is the Index of the Link Key to Set, and the */
   /* Third parameter is the Link Key value to set.                     */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_SET_LINK_KEY(_x, _y, _z)                                                                                                 \
{                                                                                                                                                                  \
   ASSIGN_UNALIGNED_GENERIC_TYPE(((qapi_BLE_Link_Key_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(qapi_BLE_Link_Key_t))) + sizeof(qapi_BLE_BD_ADDR_t))), (_z)); \
}

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Delete_Stored_Link_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Delete_All_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Delete_Stored_Link_Key_Command_t;

#define QAPI_BLE_HCI_DELETE_STORED_LINK_KEY_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Delete_Stored_Link_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Local_Name_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Local_Name_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Change Local Name Command Data Structure based upon the       */
   /* Length (in Bytes) of the Name that is required.  The first        */
   /* parameter to this MACRO is the Length (in Bytes) of the Name.     */
#define QAPI_BLE_HCI_CHANGE_LOCAL_NAME_COMMAND_SIZE(_x)           ((sizeof(qapi_BLE_HCI_Change_Local_Name_Command_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Name_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Name_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_NAME_COMMAND_SIZE                 (sizeof(qapi_BLE_HCI_Read_Local_Name_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_CONNECTION_ACCEPT_TIMEOUT_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Conn_Accept_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_PAGE_TIMEOUT_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Read_Page_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Page_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_PAGE_TIMEOUT_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Write_Page_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Scan_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Scan_Enable_Command_t;

#define QAPI_BLE_HCI_READ_SCAN_ENABLE_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Read_Scan_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Scan_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Scan_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Scan_Enable_Command_t;

#define QAPI_BLE_HCI_WRITE_SCAN_ENABLE_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Write_Scan_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Activity_Command_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_ACTIVITY_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Read_Page_Scan_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Page_Scan_Interval;
   qapi_BLE_NonAlignedWord_t     Page_Scan_Window;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Activity_Command_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_ACTIVITY_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Write_Page_Scan_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_t;

#define QAPI_BLE_HCI_READ_INQUIRY_SCAN_ACTIVITY_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Inquiry_Scan_Interval;
   qapi_BLE_NonAlignedWord_t     Inquiry_Scan_Window;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_SCAN_ACTIVITY_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Authentication_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Authentication_Enable_Command_t;

#define QAPI_BLE_HCI_READ_AUTHENTICATION_ENABLE_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Read_Authentication_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Authentication_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Authentication_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Authentication_Enable_Command_t;

#define QAPI_BLE_HCI_WRITE_AUTHENTICATION_ENABLE_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Write_Authentication_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Encryption_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Encryption_Mode_Command_t;

#define QAPI_BLE_HCI_READ_ENCRYPTION_MODE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Encryption_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Encryption_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Encryption_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Encryption_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_ENCRYPTION_MODE_COMMAND_SIZE           (sizeof(qapi_BLE_HCI_Write_Encryption_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Class_of_Device_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Class_of_Device_Command_t;

#define QAPI_BLE_HCI_READ_CLASS_OF_DEVICE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Class_of_Device_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Class_of_Device_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_Class_of_Device_t    Class_of_Device;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Class_of_Device_Command_t;

#define QAPI_BLE_HCI_WRITE_CLASS_OF_DEVICE_COMMAND_SIZE           (sizeof(qapi_BLE_HCI_Write_Class_of_Device_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Voice_Setting_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Voice_Setting_Command_t;

#define QAPI_BLE_HCI_READ_VOICE_SETTING_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Read_Voice_Setting_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Voice_Setting_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Voice_Setting;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Voice_Setting_Command_t;

#define QAPI_BLE_HCI_WRITE_VOICE_SETTING_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Write_Voice_Setting_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_AUTOMATIC_FLUSH_TIMEOUT_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_AUTOMATIC_FLUSH_TIMEOUT_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_t;

#define QAPI_BLE_HCI_READ_NUM_BROADCAST_RETRANSMISSIONS_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Num_Broadcast_Retran;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_t;

#define QAPI_BLE_HCI_WRITE_NUM_BROADCAST_RETRANSMISSIONS_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_t;

#define QAPI_BLE_HCI_READ_HOLD_MODE_ACTIVITY_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Hold_Mode_Activity;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_t;

#define QAPI_BLE_HCI_WRITE_HOLD_MODE_ACTIVITY_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Transmit_Power_Level_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Transmit_Power_Level_Command_t;

#define QAPI_BLE_HCI_READ_TRANSMIT_POWER_LEVEL_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Read_Transmit_Power_Level_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_t;

#define QAPI_BLE_HCI_READ_SCO_FLOW_CONTROL_ENABLE_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       SCO_Flow_Control_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_t;

#define QAPI_BLE_HCI_WRITE_SCO_FLOW_CONTROL_ENABLE_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Flow_Control_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_t;

#define QAPI_BLE_HCI_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Host_Buffer_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Host_ACL_Data_Packet_Length;
   uint8_t                       Host_SCO_Data_Packet_Length;
   qapi_BLE_NonAlignedWord_t     Host_Total_Num_ACL_Data_Packets;
   qapi_BLE_NonAlignedWord_t     Host_Total_Num_SCO_Data_Packets;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Host_Buffer_Size_Command_t;

#define QAPI_BLE_HCI_HOST_BUFFER_SIZE_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Host_Buffer_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Number_Of_Handles;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Host Number of Completed Packets Command Data Structure       */
   /* based upon the Number of Connection Handle/Number of Completed    */
   /* Packet Pairs that are required.  The first parameter to this MACRO*/
   /* is the Number of Connection Handle/Number of Completed Packet     */
   /* Pairs.                                                            */
#define QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_SIZE(_x) ((sizeof(qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_t) - sizeof(uint8_t)) + ((uint8_t)(_x)*(sizeof(qapi_BLE_NonAlignedWord_t)+sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following definition exists to define the Total Number of     */
   /* Connection Handle/Number of Completed Packets that can be         */
   /* supported by a single HCI_Host_Number_Of_Completed_Packets        */
   /* Command Packet.                                                   */
#define QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_MAX_HANDLES (((sizeof(uint8_t)*256) - QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_SIZE(0))/(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Connection Handle in the Host      */
   /* Number of Completed Packets Command Data.  The first parameter is */
   /* a pointer to a Data Buffer that is an                             */
   /* qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_t.  The     */
   /* Second parameter is the Index of the Connection Handle to Set, and*/
   /* the Third parameter is the Connection Handle value to Set.        */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_SET_HANDLE(_x, _y, _z)                                                                                  \
{                                                                                                                                                            \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD((((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))), (_z)); \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Number of Completed Packets in the */
   /* Host Number of Completed Packets Command Data.  The first         */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_t.  The     */
   /* Second parameter is the Index of the Number of Completed Packets  */
   /* to Set, and the Third parameter is the Connection Handle value to */
   /* Set.                                                              */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_SET_NUM_PACKETS(_x, _y, _z)                                                                                                          \
{                                                                                                                                                                                         \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_NonAlignedWord_t)), (_z)); \
}

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_LINK_SUPERVISION_TIMEOUT_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Link_Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_LINK_SUPERVISION_TIMEOUT_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_t;

#define QAPI_BLE_HCI_READ_NUMBER_OF_SUPPORTED_IAC_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Current_IAC_LAP_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Current_IAC_LAP_Command_t;

#define QAPI_BLE_HCI_READ_CURRENT_IAC_LAP_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Current_IAC_LAP_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Current_IAC_LAP_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Num_Current_IAC;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Current_IAC_LAP_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Write Current IAC LAP Command Data Structure based upon the   */
   /* Number of Connection IACs that are required.  The first parameter */
   /* to this MACRO is the Number of IAC's.                             */
#define QAPI_BLE_HCI_WRITE_CURRENT_IAC_LAP_COMMAND_SIZE(_x)       ((sizeof(qapi_BLE_HCI_Write_Current_IAC_LAP_Command_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_LAP_t))))

   /* The following definition exists to define the Total Number of IAC */
   /* LAP's that can be supported by a single                           */
   /* qapi_BLE_HCI_Write_Current_IAC_LAP_Command_t Command Packet.      */
#define QAPI_BLE_HCI_WRITE_CURRENT_IAC_LAP_COMMAND_MAX_IAC_LAPS   (((sizeof(uint8_t)*256) - QAPI_BLE_HCI_WRITE_CURRENT_IAC_LAP_COMMAND_SIZE(0))/(sizeof(qapi_BLE_LAP_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified IAC LAP in the Write Current IAC   */
   /* LAP Command Data.  The first parameter is a pointer to a Data     */
   /* Buffer that is an qapi_BLE_HCI_Write_Current_IAC_LAP_Command_t.   */
   /* The second parameter is the Index of the IAC LAP to Set, and the  */
   /* third parameter is the IAC LAP value to Set.                      */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_WRITE_CURRENT_IAC_LAP_COMMAND_SET_IAC_LAP(_x, _y, _z)                                              \
{                                                                                                              \
   ASSIGN_UNALIGNED_GENERIC_TYPE(((qapi_BLE_LAP_t *)(((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_LAP_t)))), (_z)); \
}

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_PERIOD_MODE_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Page_Scan_Period_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_PERIOD_MODE_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Mode_Command_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_MODE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Page_Scan_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Page_Scan_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_MODE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Write_Page_Scan_Mode_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version 1.2) */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_AFH_Channel_Map_t    AFH_Host_Channel_Classification;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_t;

#define QAPI_BLE_HCI_SET_AFH_HOST_CHANNEL_CLASSIFICATION_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_t;

#define QAPI_BLE_HCI_READ_INQUIRY_SCAN_TYPE_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Scan_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_SCAN_TYPE_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Mode_Command_t;

#define QAPI_BLE_HCI_READ_INQUIRY_MODE_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Read_Inquiry_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Inquiry_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_MODE_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Write_Inquiry_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Type_Command_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_TYPE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Page_Scan_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Type_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Page_Scan_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Type_Command_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_TYPE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Write_Page_Scan_Type_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_t;

#define QAPI_BLE_HCI_READ_AFH_CHANNEL_ASSESSMENT_MODE_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       AFH_Channel_Assessment_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_AFH_CHANNEL_ASSESSMENT_MODE_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version 2.1 +*/
   /* EDR)                                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_t;

#define QAPI_BLE_HCI_READ_EXTENDED_INQUIRY_RESPONSE_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_s
{
   qapi_BLE_HCI_Command_Header_t             HCI_Command_Header;
   uint8_t                                   FEC_Required;
   qapi_BLE_Extended_Inquiry_Response_Data_t Extended_Inquiry_Response;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_INQUIRY_RESPONSE_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Refresh_Encryption_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Refresh_Encryption_Key_Command_t;

#define QAPI_BLE_HCI_REFRESH_ENCRYPTION_KEY_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Refresh_Encryption_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_t;

#define QAPI_BLE_HCI_READ_SIMPLE_PAIRING_MODE_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t               Simple_Pairing_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_SIMPLE_PAIRING_MODE_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_OOB_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_OOB_Data_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_OOB_DATA_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Local_OOB_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_t;

#define QAPI_BLE_HCI_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   int8_t                        TX_Power;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Send_Keypress_Notification_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            BD_ADDR;
   uint8_t                       Notification_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Send_Keypress_Notification_Command_t;

#define QAPI_BLE_HCI_SEND_KEYPRESS_NOTIFICATION_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Send_Keypress_Notification_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_t;

#define QAPI_BLE_HCI_READ_DEFAULT_ERRONEOUS_DATA_REPORTING_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Erroneous_Data_Reporting;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_t;

#define QAPI_BLE_HCI_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Flush_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Flush_Command_t;

#define QAPI_BLE_HCI_ENHANCED_FLUSH_COMMAND_SIZE                  (sizeof(qapi_BLE_HCI_Enhanced_Flush_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version 3.0 +*/
   /* HS)                                                               */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Logical_Link_Accept_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Logical_Link_Accept_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Logical_Link_Accept_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Write_Logical_Link_Accept_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_Event_Mask_t         Event_Mask;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_t;

#define QAPI_BLE_HCI_SET_EVENT_MASK_PAGE_2_COMMAND_SIZE           (sizeof(qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Location_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Location_Data_Command_t;

#define QAPI_BLE_HCI_READ_LOCATION_DATA_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Read_Location_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Location_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Location_Domain_Aware;
   qapi_BLE_NonAlignedWord_t     Location_Domain;
   uint8_t                       Location_Domain_Options;
   uint8_t                       Location_Options;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Location_Data_Command_t;

#define QAPI_BLE_HCI_WRITE_LOCATION_DATA_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Write_Location_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Flow_Control_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Flow_Control_Mode_Command_t;

#define QAPI_BLE_HCI_READ_FLOW_CONTROL_MODE_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Read_Flow_Control_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Flow_Control_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Flow_Control_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Flow_Control_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_FLOW_CONTROL_MODE_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Write_Flow_Control_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_t;

#define QAPI_BLE_HCI_READ_ENHANCED_TRANSMIT_POWER_LEVEL_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Logical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_BEST_EFFORT_FLUSH_TIMEOUT_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Logical_Link_Handle;
   qapi_BLE_NonAlignedDWord_t    Best_Effort_Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Short_Range_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   uint8_t                       Short_Range_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Short_Range_Mode_Command_t;

#define QAPI_BLE_HCI_SHORT_RANGE_MODE_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Short_Range_Mode_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version      */
   /* 4.0 + LE).                                                        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_LE_Host_Supported_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_LE_Host_Supported_Command_t;

#define QAPI_BLE_HCI_READ_LE_HOST_SUPPORTED_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_Read_LE_Host_Supported_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_LE_Host_Supported_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       LE_Supported_Host;
   uint8_t                       Simultaneous_LE_Host;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_LE_Host_Supported_Command_t;

#define QAPI_BLE_HCI_WRITE_LE_HOST_SUPPORTED_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Write_LE_Host_Supported_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version 4.0 +*/
   /* CSA3).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       MWS_Channel_Enable;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Center_Frequency;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Center_Frequency;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Channel_Bandwidth;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Channel_Bandwidth;
   uint8_t                       MWS_Channel_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_t;

#define QAPI_BLE_HCI_SET_MWS_CHANNEL_PARAMETERS_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_External_Frame_Configuration_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Ext_Frame_Duration;
   qapi_BLE_NonAlignedWord_t     Ext_Frame_Sync_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     Ext_Frame_Sync_Assert_Jitter;
   uint8_t                       Ext_Num_Periods;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_External_Frame_Configuration_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Set        */
   /* External Frame Configuration Command Data Structure based upon the*/
   /* number of periods (Ext_Num_Periods) associated with the Command.  */
   /* The first parameter to this MACRO is the number of periods in an  */
   /* external frame (Ext_Num_Periods) of the Data that is to be part of*/
   /* the Set External Frame Configuration Command.                     */
#define QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_SIZE(_x)     (sizeof(qapi_BLE_HCI_Set_External_Frame_Configuration_Command_t) - sizeof(uint8_t) + (uint32_t)(((uint32_t)(_x)) * (QAPI_BLE_NON_ALIGNED_WORD_SIZE + QAPI_BLE_NON_ALIGNED_BYTE_SIZE)))

   /* The following definition exists to define the Total Number of     */
   /* Period's that can be supported by a single                        */
   /* qapi_BLE_HCI_Set_External_Frame_Configuration_Command_t Command   */
   /* Packet.                                                           */
#define QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_MAX_PERIODS  32

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Period_Duration in the HCI Set     */
   /* External Frame Configuration Command Data.  The first parameter is*/
   /* a pointer to a Data Buffer that is an                             */
   /* qapi_BLE_HCI_Set_External_Frame_Configuration_Command_t.  The     */
   /* Second parameter is the Index of the Period_Duration to Set, and  */
   /* the Third parameter is the Period_Duration value to set.          */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_SET_PERIOD_DURATION(_x, _y, _z)                                         \
{                                                                                                                            \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&(((uint8_t *)((_x)->Variable_Data))[(_y)*QAPI_BLE_NON_ALIGNED_WORD_SIZE]), (_z)); \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Period_Type in the HCI Set External*/
   /* Frame Configuration Command Data.  The first parameter is a       */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Set_External_Frame_Configuration_Command_t.  The     */
   /* Second parameter is the total number of periods (Ext_Num_Periods).*/
   /* The third parameter is the index of the Period_Type to set and the*/
   /* fourth parameter is the Period_Type value to set.                 */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_SET_PERIOD_TYPE(_a, _b, _c, _d)                                                                          \
{                                                                                                                                                             \
   ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((uint8_t *)((_a)->Variable_Data))[((_b)*QAPI_BLE_NON_ALIGNED_WORD_SIZE) + ((_c)*QAPI_BLE_NON_ALIGNED_BYTE_SIZE)]), (_d)); \
}

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Signaling_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_RX_Deassert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_TX_Deassert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_Pattern_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_Pattern_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_Inactivity_Duration_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_Inactivity_Duration_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_Scan_Frequency_Assert_Offset;
   qapi_BLE_NonAlignedWord_t     MWS_Scan_Frequency_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t     MWS_Priority_Assert_Offset_Request;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Signaling_Command_t;

#define QAPI_BLE_HCI_SET_MWS_SIGNALING_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Transport_Layer;
   qapi_BLE_NonAlignedDWord_t    To_MWS_Baud_Rate;
   qapi_BLE_NonAlignedDWord_t    From_MWS_Baud_Rate;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_t;

#define QAPI_BLE_HCI_SET_MWS_TRANSPORT_LAYER_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Num_Scan_Frequencies;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Set MWS    */
   /* Scan Frequency Table Command Data Structure based upon the number */
   /* of scan frequencies associated with the Command.  The first       */
   /* parameter to this MACRO is the number of scan frequencies         */
   /* (Num_Scan_Frequencies) of the Data that is to be part of the Set  */
   /* MWS Scan Frequency Table Command.                                 */
#define QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_SIZE(_x)     (sizeof(qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_t) - sizeof(uint8_t) + (uint32_t)(((uint32_t)(_x)) * (QAPI_BLE_NON_ALIGNED_WORD_SIZE*2)))

   /* The following definition exists to define the Total Number of Scan*/
   /* Frequencies's that can be supported by a single                   */
   /* qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_t Command       */
   /* Packet.                                                           */
#define QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_MAX_SCAN_FREQUENCIES   (((sizeof(uint8_t)*255) - QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_SIZE(0))/(QAPI_BLE_NON_ALIGNED_WORD_SIZE*2))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to set a specified Scan_Frequency_Low in the HCI Set  */
   /* MWS Scan Frequency Table Command.  The first parameter is a       */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_t.  The Second  */
   /* parameter is the Index of the Scan_Frequency_Low to Set, and the  */
   /* Third parameter is the Scan_Frequency_Low value to set.           */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_SET_SCAN_FREQUENCY_LOW(_x, _y, _z)                                           \
{                                                                                                                                      \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&(((uint8_t *)((_x)->Variable_Data))[(_y)*QAPI_BLE_NON_ALIGNED_WORD_SIZE]), (_z)); \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to set a specified Scan_Frequency_High in the HCI Set */
   /* MWS Scan Frequency Table Command Data.  The first parameter is a  */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_t.  The Second  */
   /* parameter is the total number of scan frequencies                 */
   /* (Num_Scan_Frequencies).  The third parameter is the index of the  */
   /* Scan_Frequency_High to set and the fourth parameter is the        */
   /* Scan_Frequency_High value to set.                                 */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_SET_SCAN_FREQUENCY_HIGH(_a, _b, _c, _d)                                     \
{                                                                                                                                     \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&(((uint8_t *)((_a)->Variable_Data))[((_b)*QAPI_BLE_NON_ALIGNED_WORD_SIZE) + ((_c)*QAPI_BLE_NON_ALIGNED_WORD_SIZE)]), (_d)); \
}

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       MWS_PATTERN_Index;
   uint8_t                       MWS_PATTERN_NumIntervals;
   uint8_t                       Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Set MWS    */
   /* PATTERN Configuration Command Data Structure based upon the number*/
   /* of pattern intervals associated with the Command.  The first      */
   /* parameter to this MACRO is the number of intervals                */
   /* (MWS_PATTERN_NumIntervals) of the Data that is to be part of the  */
   /* Set MWS PATTERN Configuration Command.                            */
#define QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_SIZE(_x)              (sizeof(qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_t) - sizeof(uint8_t) + (uint32_t)(((uint32_t)(_x)) * (QAPI_BLE_NON_ALIGNED_WORD_SIZE + QAPI_BLE_NON_ALIGNED_BYTE_SIZE)))

   /* The following definition exists to define the Total Number of     */
   /* Pattern Interval's that can be supported by a single              */
   /* qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_t Command      */
   /* Packet.                                                           */
#define QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_MAX_PATTERN_INTERVALS (((sizeof(uint8_t)*255) - QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_SIZE(0))/(QAPI_BLE_NON_ALIGNED_WORD_SIZE + QAPI_BLE_NON_ALIGNED_BYTE_SIZE))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to set a specified IntervalDuration in the HCI Set MWS*/
   /* PATTERN Configuration Command Data.  The first parameter is a     */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_t.  The Second */
   /* parameter is the Index of the IntervalDuration to Set, and the    */
   /* Third parameter is the IntervalDuration value to set.             */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_SET_INTERVAL_DURATION(_x, _y, _z)                                           \
{                                                                                                                                      \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&(((uint8_t *)((_x)->Variable_Data))[(_y)*QAPI_BLE_NON_ALIGNED_WORD_SIZE]), (_z)); \
}

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to set a specified IntervalType in the HCI Set MWS    */
   /* PATTERN Configuration Command Data.  The first parameter is a     */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_t.  The Second */
   /* parameter is the total number of intervals                        */
   /* (MWS_PATTERN_NumIntervals).  The third parameter is the index of  */
   /* the IntervalType to set and the fourth parameter is the           */
   /* IntervalType value to set.                                        */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_SET_INTERVAL_TYPE(_a, _b, _c, _d)                                                                  \
{                                                                                                                                                             \
   ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((uint8_t *)((_a)->Variable_Data))[((_b)*QAPI_BLE_NON_ALIGNED_WORD_SIZE) + ((_c)*QAPI_BLE_NON_ALIGNED_BYTE_SIZE)]), (_d)); \
}

   /* HCI Command Definitions (Host Control and Baseband - Version 4.0 +*/
   /* CSA4).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_t;

#define QAPI_BLE_HCI_SET_RESERVED_LT_ADDR_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_t;

#define QAPI_BLE_HCI_DELETE_RESERVED_LT_ADDR_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       LT_ADDR;
   uint8_t                       Fragment;
   uint8_t                       Data_Length;
   uint8_t                       Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Set        */
   /* Connectionless Slave Broadcast Command Data Structure based upon  */
   /* the number of individual Data bytes associated with the Command.  */
   /* The first parameter to this MACRO is the size (in Bytes) of the   */
   /* Data that is to be part of the Set Connectionless Slave Broadcast */
   /* Command.                                                          */
#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_COMMAND_SIZE(_x)        (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* The following definition exists to define the Total Number of data*/
   /* that can be supported by a single                                 */
   /* qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_t    */
   /* Command Packet.                                                   */
#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_COMMAND_MAX_DATA         (((sizeof(uint8_t)*255) - QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_COMMAND_SIZE(0))/(sizeof(uint8_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_t;

#define QAPI_BLE_HCI_READ_SYNCHRONIZATION_TRAIN_PARAMETERS_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Interval_Min;
   qapi_BLE_NonAlignedWord_t     Interval_Max;
   qapi_BLE_NonAlignedDWord_t    Sync_Train_Timeout;
   uint8_t                       Service_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_t;

#define QAPI_BLE_HCI_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_t))

   /* HCI Command Definitions (Host Control and Baseband - Version 4.1).*/

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_t;

#define QAPI_BLE_HCI_READ_SECURE_CONNECTIONS_HOST_SUPPORT_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Secure_Connections_Host_Support;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_t;

#define QAPI_BLE_HCI_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Authenticated_Payload_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_OOB_EXTENDED_DATA_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_t;

#define QAPI_BLE_HCI_READ_EXTENDED_PAGE_TIMEOUT_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Extended_Page_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_PAGE_TIMEOUT_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_t;

#define QAPI_BLE_HCI_READ_EXTENDED_INQUIRY_LENGTH_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Extended_Inquiry_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_INQUIRY_LENGTH_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_t))

   /* HCI Command Definitions (Informational Parameters).               */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Version_Information_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Version_Information_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_VERSION_INFORMATION_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_Read_Local_Version_Information_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Features_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_FEATURES_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Local_Supported_Features_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Buffer_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Buffer_Size_Command_t;

#define QAPI_BLE_HCI_READ_BUFFER_SIZE_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Read_Buffer_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Country_Code_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Country_Code_Command_t;

#define QAPI_BLE_HCI_READ_COUNTRY_CODE_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_Read_Country_Code_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_BD_ADDR_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_BD_ADDR_Command_t;

#define QAPI_BLE_HCI_READ_BD_ADDR_COMMAND_SIZE                    (sizeof(qapi_BLE_HCI_Read_BD_ADDR_Command_t))

   /* HCI Command Definitions (Informational Parameters - Version 1.2). */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Commands_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Commands_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_COMMANDS_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Read_Local_Supported_Commands_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Extended_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Page_Number;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Extended_Features_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_EXTENDED_FEATURES_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Read_Local_Extended_Features_Command_t))

   /* HCI Command Definitions (Informational Parameters - Version 3.0 + */
   /* HS).                                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Data_Block_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Data_Block_Size_Command_t;

#define QAPI_BLE_HCI_READ_DATA_BLOCK_SIZE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Data_Block_Size_Command_t))

   /* HCI Command Definitions (Informational Parameters - Version 4.0 + */
   /* CSA2).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_CODECS_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_t))

   /* HCI Command Definitions (Status Parameters).                      */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_t;

#define QAPI_BLE_HCI_READ_FAILED_CONTACT_COUNTER_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_t;

#define QAPI_BLE_HCI_RESET_FAILED_CONTACT_COUNTER_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Get_Link_Quality_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Get_Link_Quality_Command_t;

#define QAPI_BLE_HCI_GET_LINK_QUALITY_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_Get_Link_Quality_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_RSSI_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_RSSI_Command_t;

#define QAPI_BLE_HCI_READ_RSSI_COMMAND_SIZE                       (sizeof(qapi_BLE_HCI_Read_RSSI_Command_t))

   /* HCI Command Definitions (Status Parameters - Version 1.2).        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_AFH_Channel_Map_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_AFH_Channel_Map_Command_t;

#define QAPI_BLE_HCI_READ_AFH_CHANNEL_MAP_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_AFH_Channel_Map_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Clock_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Which_Clock;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Clock_Command_t;

#define QAPI_BLE_HCI_READ_CLOCK_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_Read_Clock_Command_t))

   /* HCI Command Definitions (Status Parameters - Version 3.0 + HS).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Encryption_Key_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Encryption_Key_Size_Command_t;

#define QAPI_BLE_HCI_READ_QAPI_BLE_ENCRYPTION_KEY_SIZE_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Read_Encryption_Key_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_AMP_Info_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_AMP_Info_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_AMP_INFO_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Read_Local_AMP_Info_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   qapi_BLE_NonAlignedWord_t     Length_So_Far;
   qapi_BLE_NonAlignedWord_t     Max_Remote_AMP_ASSOC_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_t;

#define QAPI_BLE_HCI_READ_LOCAL_AMP_ASSOC_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_t))

   /* Note that the AMP_ASSOC_Fragment[] parameter is a variable length */
   /* field that contains zero or more bytes.                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Physical_Link_Handle;
   qapi_BLE_NonAlignedWord_t     Length_So_Far;
   qapi_BLE_NonAlignedWord_t     AMP_ASSOC_Remaining_Length;
   uint8_t                       AMP_ASSOC_Fragment[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Write      */
   /* Remote AMP ASSOC Command Data Structure based upon the number of  */
   /* individual Assocation Fragment bytes included with the Command.   */
   /* The first parameter to this MACRO is the size (in Bytes) of the   */
   /* Association Fragment Data that is to be part of the Write Remote  */
   /* AMP ASSOC Command.                                                */
#define QAPI_BLE_HCI_WRITE_REMOTE_AMP_ASSOC_COMMAND_SIZE(_x)      (sizeof(qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* HCI Command Definitions (Status Parameters - Version 4.0 + CSA3). */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_t;

#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_t))

   /* HCI Command Definitions (Status Parameters - Version 4.0 + CSA4). */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Enable;
   uint8_t                       Which_Clock;
   uint8_t                       LPO_Allowed;
   uint8_t                       Num_Clock_Captures_To_Filter;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_t;

#define QAPI_BLE_HCI_SET_TRIGGERED_CLOCK_CAPTURE_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_t))

   /* HCI Command Definitions (Testing Commands).                       */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Loopback_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Loopback_Mode_Command_t;

#define QAPI_BLE_HCI_READ_LOOPBACK_MODE_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_Read_Loopback_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Loopback_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Loopback_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Loopback_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_LOOPBACK_MODE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_Write_Loopback_Mode_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_t;

#define QAPI_BLE_HCI_ENABLE_DEVICE_UNDER_TEST_MODE_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_t))

   /* HCI Command Definitions (Testing Commands - Version 2.1 + EDR).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Simple_Pairing_Debug_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_SIMPLE_PAIRING_DEBUG_MODE_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_t))

   /* HCI Command Definitions (Testing Commands - Version 3.0 + HS).    */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Enable;
   uint8_t                       Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_t;

#define QAPI_BLE_HCI_ENABLE_AMP_RECEIVER_REPORTS_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Test_End_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Test_End_Command_t;

#define QAPI_BLE_HCI_AMP_TEST_END_COMMAND_SIZE                    (sizeof(qapi_BLE_HCI_AMP_Test_End_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Test_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Test_Parameters[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Test_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI AMP Command*/
   /* Data Structure based upon the number of individual Test Parameter */
   /* bytes included with the Command.  The first parameter to this     */
   /* MACRO is the size (in Bytes) of the Test Parameters Data that is  */
   /* to be part of the HCI AMP Command.                                */
#define QAPI_BLE_HCI_AMP_TEST_COMMAND_SIZE(_x)                    (sizeof(qapi_BLE_HCI_AMP_Test_Command_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* HCI Command Definitions (Testing Commands - Version 4.1).         */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       DM1_ACLU_Mode;
   uint8_t                       ESCO_Loopback_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_t;

#define QAPI_BLE_HCI_WRITE_SECURE_CONNECTIONS_TEST_MODE_COMMAND_SIZE (sizeof(qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_t))

   /* HCI Command Definitions (LE Controller Commands - Version 4.0 +   */
   /* LE).                                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Event_Mask_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_Event_Mask_t         LE_Event_Mask;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Event_Mask_Command_t;

#define QAPI_BLE_HCI_LE_SET_EVENT_MASK_COMMAND_SIZE               (sizeof(qapi_BLE_HCI_LE_Set_Event_Mask_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Buffer_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Buffer_Size_Command_t;

#define QAPI_BLE_HCI_LE_READ_BUFFER_SIZE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Read_Buffer_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Random_Address_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_BD_ADDR_t            Random_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Random_Address_Command_t;

#define QAPI_BLE_HCI_LE_SET_RANDOM_ADDRESS_COMMAND_SIZE           (sizeof(qapi_BLE_HCI_LE_Set_Random_Address_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Advertising_Interval_Min;
   qapi_BLE_NonAlignedWord_t     Advertising_Interval_Max;
   qapi_BLE_NonAlignedByte_t     Advertising_Type;
   qapi_BLE_NonAlignedByte_t     Own_Address_Type;
   qapi_BLE_NonAlignedByte_t     Direct_Address_Type;
   qapi_BLE_BD_ADDR_t            Direct_Address;
   qapi_BLE_NonAlignedByte_t     Advertising_Channel_Map;
   qapi_BLE_NonAlignedByte_t     Advertising_Filter_Policy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_PARAMETERS_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_t;

#define QAPI_BLE_HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Data_Length;
   qapi_BLE_Advertising_Data_t   Advertising_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Data_Command_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_DATA_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Scan_Response_Data_Length;
   qapi_BLE_Scan_Response_Data_t Scan_Response_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_RESPONSE_DATA_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISE_ENABLE_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     LE_Scan_Type;
   qapi_BLE_NonAlignedWord_t     LE_Scan_Interval;
   qapi_BLE_NonAlignedWord_t     LE_Scan_Window;
   qapi_BLE_NonAlignedByte_t     Own_Address_Type;
   qapi_BLE_NonAlignedByte_t     Scanning_Filter_Policy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_PARAMETERS_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     LE_Scan_Enable;
   qapi_BLE_NonAlignedByte_t     Filter_Duplicates;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Enable_Command_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_ENABLE_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_LE_Set_Scan_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Create_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     LE_Scan_Interval;
   qapi_BLE_NonAlignedWord_t     LE_Scan_Window;
   qapi_BLE_NonAlignedByte_t     Initiator_Filter_Policy;
   qapi_BLE_NonAlignedByte_t     Peer_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Address;
   qapi_BLE_NonAlignedByte_t     Own_Address_Type;
   qapi_BLE_NonAlignedWord_t     Conn_Interval_Min;
   qapi_BLE_NonAlignedWord_t     Conn_Interval_Max;
   qapi_BLE_NonAlignedWord_t     Conn_Latency;
   qapi_BLE_NonAlignedWord_t     Supervision_Timeout;
   qapi_BLE_NonAlignedWord_t     Minimum_CE_Length;
   qapi_BLE_NonAlignedWord_t     Maximum_CE_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Create_Connection_Command_t;

#define QAPI_BLE_HCI_LE_CREATE_CONNECTION_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_LE_Create_Connection_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_t;

#define QAPI_BLE_HCI_LE_CREATE_CONNECTION_CANCEL_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_White_List_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_White_List_Size_Command_t;

#define QAPI_BLE_HCI_LE_READ_WHITE_LIST_SIZE_COMMAND_SIZE         (sizeof(qapi_BLE_HCI_LE_Read_White_List_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_White_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_White_List_Command_t;

#define QAPI_BLE_HCI_LE_CLEAR_WHITE_LIST_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Clear_White_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Address_Type;
   qapi_BLE_BD_ADDR_t            Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_SIZE     (sizeof(qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Address_Type;
   qapi_BLE_BD_ADDR_t            Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Connection_Update_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Conn_Interval_Min;
   qapi_BLE_NonAlignedWord_t     Conn_Interval_Max;
   qapi_BLE_NonAlignedWord_t     Conn_Latency;
   qapi_BLE_NonAlignedWord_t     Supervision_Timeout;
   qapi_BLE_NonAlignedWord_t     Minimum_CE_Length;
   qapi_BLE_NonAlignedWord_t     Maximum_CE_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Connection_Update_Command_t;

#define QAPI_BLE_HCI_LE_CONNECTION_UPDATE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_LE_Connection_Update_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_LE_Channel_Map_t     Channel_Map;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_t;

#define QAPI_BLE_HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Channel_Map_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Channel_Map_Command_t;

#define QAPI_BLE_HCI_LE_READ_CHANNEL_MAP_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Read_Channel_Map_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_t;

#define QAPI_BLE_HCI_LE_READ_REMOTE_USED_FEATURES_COMMAND_SIZE    (sizeof(qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Encrypt_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_Encryption_Key_t     Key;
   qapi_BLE_Plain_Text_Data_t    Plain_Text_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Encrypt_Command_t;

#define QAPI_BLE_HCI_LE_ENCRYPT_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_LE_Encrypt_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Rand_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Rand_Command_t;

#define QAPI_BLE_HCI_LE_RAND_COMMAND_SIZE                         (sizeof(qapi_BLE_HCI_LE_Rand_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Start_Encryption_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_Random_Number_t      Random_Number;
   qapi_BLE_NonAlignedWord_t     Encrypted_Diversifier;
   qapi_BLE_Long_Term_Key_t      Long_Term_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Start_Encryption_Command_t;

#define QAPI_BLE_HCI_LE_START_ENCRYPTION_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Start_Encryption_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_Long_Term_Key_t      Long_Term_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_t;

#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_REPLY_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Supported_States_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Supported_States_Command_t;

#define QAPI_BLE_HCI_LE_READ_SUPPORTED_STATES_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_LE_Read_Supported_States_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Receiver_Test_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     RX_Frequency;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Receiver_Test_Command_t;

#define QAPI_BLE_HCI_LE_RECEIVER_TEST_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_LE_Receiver_Test_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Transmitter_Test_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     TX_Frequency;
   qapi_BLE_NonAlignedByte_t     Length_Of_Test_Data;
   qapi_BLE_NonAlignedByte_t     Packet_Payload;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Transmitter_Test_Command_t;

#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Transmitter_Test_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Test_End_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Test_End_Command_t;

#define QAPI_BLE_HCI_LE_TEST_END_COMMAND_SIZE                     (sizeof(qapi_BLE_HCI_LE_Test_End_Command_t))

   /* HCI Command Definitions (LE Controller Commands - Version 4.1).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     Interval_Min;
   qapi_BLE_NonAlignedWord_t     Interval_Max;
   qapi_BLE_NonAlignedWord_t     Latency;
   qapi_BLE_NonAlignedWord_t     Timeout;
   qapi_BLE_NonAlignedWord_t     Minimum_CE_Length;
   qapi_BLE_NonAlignedWord_t     Maximum_CE_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_t;

#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   uint8_t                       Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_t;

#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_t))

   /* HCI Command Definitions (LE Controller Commands - Version 4.2).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Data_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedWord_t     TxOctets;
   qapi_BLE_NonAlignedWord_t     TxTime;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Data_Length_Command_t;

#define QAPI_BLE_HCI_LE_SET_DATA_LENGTH_COMMAND_SIZE                     (sizeof(qapi_BLE_HCI_LE_Set_Data_Length_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_t;

#define QAPI_BLE_HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     SuggestedMaxTxOctets;
   qapi_BLE_NonAlignedWord_t     SuggestedMaxTxTime;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_t;

#define QAPI_BLE_HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_COMMAND_SIZE (sizeof(qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_COMMAND_SIZE          (sizeof(qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Generate_DHKey_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_P256_Public_Key_t    Remote_P256_Public_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Generate_DHKey_Command_t;

#define QAPI_BLE_HCI_LE_GENERATE_DHKEY_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_LE_Generate_DHKey_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Peer_Identity_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Identity_Address;
   qapi_BLE_Encryption_Key_t     Peer_IRK;
   qapi_BLE_Encryption_Key_t     Local_IRK;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Peer_Identity_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Identity_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_Resolving_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_Resolving_List_Command_t;

#define QAPI_BLE_HCI_LE_CLEAR_RESOLVING_LIST_COMMAND_SIZE                (sizeof(qapi_BLE_HCI_LE_Clear_Resolving_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_t;

#define QAPI_BLE_HCI_LE_READ_RESOLVING_LIST_SIZE_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Peer_Identity_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Identity_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_t;

#define QAPI_BLE_HCI_LE_READ_PEER_RESOLVABLE_ADDRESS_COMMAND_SIZE        (sizeof(qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Peer_Identity_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Identity_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_RESOLVABLE_ADDRESS_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   uint8_t                       Address_Resolution_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_t;

#define QAPI_BLE_HCI_LE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     RPA_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_t;

#define QAPI_BLE_HCI_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_COMMAND_SIZE (sizeof(qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_t;

#define QAPI_BLE_HCI_LE_READ_MAXIMUM_DATA_LENGTH_COMMAND_SIZE            (sizeof(qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_t))

   /* HCI Command Definitions (LE Controller Commands - Version 5.0).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_PHY_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_PHY_Command_t;

#define QAPI_BLE_HCI_LE_READ_PHY_COMMAND_SIZE                     (sizeof(qapi_BLE_HCI_LE_Read_PHY_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Default_PHY_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     ALL_PHYS;
   qapi_BLE_NonAlignedByte_t     TX_PHYS;
   qapi_BLE_NonAlignedByte_t     RX_PHYS;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Default_PHY_Command_t;

#define QAPI_BLE_HCI_LE_SET_DEFAULT_PHY_COMMAND_SIZE              (sizeof(qapi_BLE_HCI_LE_Set_Default_PHY_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_PHY_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Connection_Handle;
   qapi_BLE_NonAlignedByte_t     ALL_PHYS;
   qapi_BLE_NonAlignedByte_t     TX_PHYS;
   qapi_BLE_NonAlignedByte_t     RX_PHYS;
   qapi_BLE_NonAlignedWord_t     PHY_Options;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_PHY_Command_t;

#define QAPI_BLE_HCI_LE_SET_PHY_COMMAND_SIZE                      (sizeof(qapi_BLE_HCI_LE_Set_PHY_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     RX_Channel;
   qapi_BLE_NonAlignedByte_t     PHY;
   qapi_BLE_NonAlignedByte_t     Modulation_Index;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_t;

#define QAPI_BLE_HCI_LE_ENHANCED_RECEIVER_TEST_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     TX_Channel;
   qapi_BLE_NonAlignedByte_t     Length_Of_Test_Data;
   qapi_BLE_NonAlignedByte_t     Packet_Payload;
   qapi_BLE_NonAlignedByte_t     PHY;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_t;

#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_COMMAND_SIZE       (sizeof(qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_BD_ADDR_t            Advertising_Random_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedWord_t     Advertising_Event_Properties;
   qapi_BLE_NonAlignedByte_t     Primary_Advertising_Interval_Min[3];
   qapi_BLE_NonAlignedByte_t     Primary_Advertising_Interval_Max[3];
   qapi_BLE_NonAlignedByte_t     Primary_Advertising_Channel_Map;
   qapi_BLE_NonAlignedByte_t     Own_Address_Type;
   qapi_BLE_NonAlignedByte_t     Peer_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Address;
   qapi_BLE_NonAlignedByte_t     Advertising_Filter_Policy;
   qapi_BLE_NonAlignedSByte_t    Advertising_TX_Power;
   qapi_BLE_NonAlignedByte_t     Primary_Advertising_PHY;
   qapi_BLE_NonAlignedByte_t     Secondary_Advertising_Max_Skip;
   qapi_BLE_NonAlignedByte_t     Secondary_Advertising_PHY;
   qapi_BLE_NonAlignedByte_t     Advertising_SID;
   qapi_BLE_NonAlignedByte_t     Scan_Request_Notification_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedByte_t     Operation;
   qapi_BLE_NonAlignedByte_t     Fragment_Preference;
   qapi_BLE_NonAlignedByte_t     Advertising_Data_Length;
   qapi_BLE_NonAlignedByte_t     Advertising_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_t structure.*/
   /* The only parameter to this MACRO is the Advertising_Data_Length.  */
#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_DATA_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_t, Advertising_Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedByte_t     Operation;
   qapi_BLE_NonAlignedByte_t     Fragment_Preference;
   qapi_BLE_NonAlignedByte_t     Scan_Response_Data_Length;
   qapi_BLE_NonAlignedByte_t     Scan_Response_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_t         */
   /* structure. The only parameter to this MACRO is the                */
   /* Scan_Response_Data_Length.                                        */
#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_t, Scan_Response_Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Data_s
{
   qapi_BLE_NonAlignedByte_t Advertising_Handle;
   qapi_BLE_NonAlignedWord_t Duration;
   qapi_BLE_NonAlignedByte_t Max_Extended_Advertising_Events;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Data_t;

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t                          HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t                              Enable;
   qapi_BLE_NonAlignedByte_t                              Number_of_Sets;
   qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Data_t Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_t         */
   /* structure. The only parameter to this MACRO is the Number_of_Sets.*/
#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_t, Data) + ((_x) * sizeof(HCI_LE_Set_Extended_Advertising_Enable_Data_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Interval_Min;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Interval_Max;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Properties;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedByte_t     Operation;
   qapi_BLE_NonAlignedByte_t     Advertising_Data_Length;
   qapi_BLE_NonAlignedByte_t     Advertising_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_t structure.*/
   /* The only parameter to this MACRO is the Advertising_Data_Length.  */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_DATA_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_t, Advertising_Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Enable;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_ENABLE_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Data_s
{
   qapi_BLE_NonAlignedByte_t Scan_Type;
   qapi_BLE_NonAlignedWord_t Scan_Interval;
   qapi_BLE_NonAlignedWord_t Scan_Window;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Data_t;

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_s
{
   qapi_BLE_HCI_Command_Header_t                       HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t                           Own_Address_Type;
   qapi_BLE_NonAlignedByte_t                           Scanning_Filter_Policy;
   qapi_BLE_NonAlignedByte_t                           Scanning_PHYS;
   qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Data_t Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_t structure. */
   /* The only parameter to this MACRO is the number of bits set in the */
   /* Scanning_PHYS field.                                              */
#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_PARAMETERS_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_t, Data) + ((_x) * sizeof(qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Data_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Enable;
   qapi_BLE_NonAlignedByte_t     Filter_Duplicates;
   qapi_BLE_NonAlignedWord_t     Duration;
   qapi_BLE_NonAlignedWord_t     Period;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_ENABLE_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Create_Connection_Data_s
{
   qapi_BLE_NonAlignedWord_t Scan_Interval;
   qapi_BLE_NonAlignedWord_t Scan_Window;
   qapi_BLE_NonAlignedWord_t Conn_Interval_Min;
   qapi_BLE_NonAlignedWord_t Conn_Interval_Max;
   qapi_BLE_NonAlignedWord_t Conn_Latency;
   qapi_BLE_NonAlignedWord_t Supervision_Timeout;
   qapi_BLE_NonAlignedWord_t Minimum_CE_Length;
   qapi_BLE_NonAlignedWord_t Maximum_CE_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Create_Connection_Data_t;

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Create_Connection_Command_s
{
   qapi_BLE_HCI_Command_Header_t                     HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t                         Initiating_Filter_Policy;
   qapi_BLE_NonAlignedByte_t                         Own_Address_Type;
   qapi_BLE_NonAlignedByte_t                         Peer_Address_Type;
   qapi_BLE_BD_ADDR_t                                Peer_Address;
   qapi_BLE_NonAlignedByte_t                         Initiating_PHYS;
   qapi_BLE_HCI_LE_Extended_Create_Connection_Data_t Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Create_Connection_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_t structure. */
   /* The only parameter to this MACRO is the number of bits set in the */
   /* Initiating_PHYS field.                                            */
#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Extended_Create_Connection_Command_t, Data) + ((_x) * sizeof(qapi_BLE_HCI_LE_Extended_Create_Connection_Data_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Create_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Filter_Policy;
   qapi_BLE_NonAlignedByte_t     Advertising_SID;
   qapi_BLE_NonAlignedByte_t     Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t            Advertiser_Address;
   qapi_BLE_NonAlignedWord_t     Skip;
   qapi_BLE_NonAlignedWord_t     Sync_Timeout;
   qapi_BLE_NonAlignedByte_t     Unused;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Create_Command_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Create_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t            Advertiser_Address;
   qapi_BLE_NonAlignedByte_t     Advertising_SID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t            Advertiser_Address;
   qapi_BLE_NonAlignedByte_t     Advertising_SID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedSWord_t    RF_TX_Path_Compensation_Value;
   qapi_BLE_NonAlignedSWord_t    RF_RX_Path_Compensation_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_t;

#define QAPI_BLE_HCI_LE_WRITE_RF_PATH_COMPENSATION_COMMAND_SIZE   (sizeof(qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Peer_Identity_Address_Type;
   qapi_BLE_BD_ADDR_t            Peer_Identity_Address;
   qapi_BLE_NonAlignedByte_t     Privacy_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_t;

#define QAPI_BLE_HCI_LE_SET_PRIVACY_MODE_COMMAND_SIZE             (sizeof(qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_t))

   /* HCI Command Definitions (LE Controller Commands - Version 5.4).   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t     Advertising_Handle;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Interval_Min;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Interval_Max;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Properties;
   qapi_BLE_NonAlignedByte_t     Num_Subevents;
   qapi_BLE_NonAlignedByte_t     Subevent_Interval;
   qapi_BLE_NonAlignedByte_t     Response_Slot_Delay;
   qapi_BLE_NonAlignedByte_t     Response_Slot_Spacing;
   qapi_BLE_NonAlignedByte_t     Num_Response_Slots;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_s
{
   qapi_BLE_NonAlignedByte_t Subevent;
   qapi_BLE_NonAlignedByte_t Response_Slot_Start;
   qapi_BLE_NonAlignedByte_t Response_Slot_Count;
   qapi_BLE_NonAlignedByte_t Subevent_Data_Length;
   qapi_BLE_NonAlignedByte_t Subevent_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* HCI_LE_Set_Periodic_Advertising_Subevent_Data_t structure.  The   */
   /* only parameter to this MACRO is the number of bytes in the        */
   /* Subevent_Data field (Subevent_Data_Length contains the length of  */
   /* this field).                                                      */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_t, Subevent_Data)) + ((_x) * QAPI_BLE_NON_ALIGNED_BYTE_SIZE))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t                            HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t                                Advertising_Handle;
   qapi_BLE_NonAlignedByte_t                                Num_Subevents;
   qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_t HCI_LE_Set_Periodic_Advertising_Subevent_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_t structure.*/
   /* This MACRO takes two parameters:                                  */
   /*       1. Number of Subevents in the command (_x = Num_Subevents)  */
   /*       2. TOTAL number of bytes of Subevent data for all of the    */
   /*          subevents combined (_y parameter).                       */
   /* The total size of this command must be less than or equal to      */
   /* HCI_COMMAND_MAX_SIZE.                                             */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_COMMAND_SIZE(_x, _y) (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_t, HCI_LE_Set_Periodic_Advertising_Subevent_Data) + ((_x) * QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_SIZE(0)) + ((_y) * QAPI_BLE_NON_ALIGNED_BYTE_SIZE))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Sync_Handle;
   qapi_BLE_NonAlignedWord_t     Request_Event;
   qapi_BLE_NonAlignedByte_t     Request_Subevent;
   qapi_BLE_NonAlignedByte_t     Response_Subevent;
   qapi_BLE_NonAlignedByte_t     Response_Slot;
   qapi_BLE_NonAlignedByte_t     Response_Data_Length;
   qapi_BLE_NonAlignedByte_t     Response_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* HCI_LE_Set_Periodic_Advertising_Response_Data_Command_t structure.*/
   /* The only parameter to this MACRO is the number of bytes in the    */
   /* Advertising_Data field (Advertising_Data_Length contains the      */
   /* length of this field).                                            */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_COMMAND_SIZE(_x)  (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_t, Response_Data) + ((_x) * QAPI_BLE_NON_ALIGNED_BYTE_SIZE))

   /* The following contains the maximum amount of data that can be     */
   /* contained in the Advertising_Data field of the                    */
   /* HCI_LE_Set_Periodic_Advertising_Response_Data_Command_t structure.*/
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_MAX_ADVERTISING_DATA (QAPI_BLE_HCI_COMMAND_MAX_SIZE - QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_COMMAND_SIZE(0))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_s
{
   qapi_BLE_HCI_Command_Header_t HCI_Command_Header;
   qapi_BLE_NonAlignedWord_t     Sync_Handle;
   qapi_BLE_NonAlignedWord_t     Periodic_Advertising_Properties;
   qapi_BLE_NonAlignedByte_t     Num_Subevents;
   qapi_BLE_NonAlignedByte_t     Subevents[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* HCI_LE_Set_Periodic_Sync_Subevent_Command_t structure.  The only  */
   /* parameter to this MACRO is the number of Subevents in the         */
   /* Subevents field (Num_Subevents contains the length of this field).*/
#define QAPI_BLE_HCI_LE_SET_PERIODIC_SYNC_SUBEVENT_COMMAND_SIZE(_x)  (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_t, Subevents) + ((_x) * QAPI_BLE_NON_ALIGNED_BYTE_SIZE))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_s
{
   qapi_BLE_HCI_Command_Header_t                     HCI_Command_Header;
   qapi_BLE_NonAlignedByte_t                         Advertising_Handle;
   qapi_BLE_NonAlignedByte_t                         Subevent;
   qapi_BLE_NonAlignedByte_t                         Initiating_Filter_Policy;
   qapi_BLE_NonAlignedByte_t                         Own_Address_Type;
   qapi_BLE_NonAlignedByte_t                         Peer_Address_Type;
   qapi_BLE_BD_ADDR_t                                Peer_Address;
   qapi_BLE_NonAlignedByte_t                         Initiating_PHYS;
   qapi_BLE_HCI_LE_Extended_Create_Connection_Data_t Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_t;

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* calculating the size of the                                       */
   /* HCI_LE_Set_Extended_Scan_Parameters_Command_t structure. The only */
   /* parameter to this MACRO is the number of bits set in the          */
   /* Initiating_PHYS field.                                            */
#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_V2_COMMAND_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_t, Data) + ((_x) * sizeof(qapi_BLE_HCI_LE_Extended_Create_Connection_Data_t))))

   /* HCI Event Definitions.                                            */

   /* The following type declaration represents the structure of the    */
   /* Header of an HCI Event Packet.  This Header Information is        */
   /* contained in Every Defined HCI Event Packet.  This structure      */
   /* forms the basis of additional defined HCI Event Packets.  Since   */
   /* this structure is present at the begining of Every Defined HCI    */
   /* Event Packet, this structure will be the first element of Every   */
   /* Defined HCI Event Packet in this file.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Event_Header_s
{
   qapi_BLE_NonAlignedByte_t Event_Code;
   qapi_BLE_NonAlignedByte_t Parameter_Total_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Event_Header_t;

#define QAPI_BLE_HCI_EVENT_HEADER_SIZE                            (sizeof(qapi_BLE_HCI_Event_Header_t))

#define QAPI_BLE_HCI_EVENT_MAX_SIZE                               (sizeof(qapi_BLE_HCI_Event_Header_t) + (sizeof(uint8_t)*256))

   /* The following MACRO Exists to determine the Size (in Bytes) of    */
   /* the buffer that would be required to satisfy an HCI Event packet  */
   /* of the specified Parameter Total Length (in Bytes).  The first    */
   /* parameter of this MACRO is the size (in Bytes) of the total       */
   /* number of Parameter Bytes required for the HCI Event Packet.      */
#define QAPI_BLE_HCI_EVENT_SIZE(_x)                               (sizeof(qapi_BLE_HCI_Event_Header_t) + (uint32_t)(_x))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Num_Responses;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Complete_Event_t;

#define QAPI_BLE_HCI_INQUIRY_COMPLETE_EVENT_SIZE                  (sizeof(qapi_BLE_HCI_Inquiry_Complete_Event_t))

   /* Below is the HCI Inquiry Complete Event for the Bluetooth HCI 1.1 */
   /* Specification (Version 1.1).                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Complete_Event_1_1_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Complete_Event_1_1_t;

#define QAPI_BLE_HCI_INQUIRY_COMPLETE_EVENT_1_1_SIZE              (sizeof(qapi_BLE_HCI_Inquiry_Complete_Event_1_1_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Result_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Num_Responses;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Result_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Inquiry Result Event Data Structure based upon the Number of  */
   /* Responses.  The first parameter of this MACRO is the Number of    */
   /* Responses.                                                        */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_SIZE(_x)                ((sizeof(qapi_BLE_HCI_Inquiry_Result_Event_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_BD_ADDR_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(qapi_BLE_Class_of_Device_t)+sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified BD_ADDR in the HCI Inquiry Result */
   /* Event Data.  The first parameter is a pointer to a Data Buffer    */
   /* that is an HCI_Inquiry Result_Event_t.  The Second parameter is   */
   /* the Index of the BD_ADDR to Read.                                 */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_BD_ADDR(_x, _y)          \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_BD_ADDR_t *)(((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t)))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Page Scan Repetition Mode value in*/
   /* the HCI Inquiry Result Event Data.  The first parameter is a      */
   /* pointer to a Data Buffer that is an HCI_Inquiry Result_Event_t.   */
   /* The Second parameter is the Index of the Page Scan Repetition Mode*/
   /* Value to Read.                                                    */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_REPETITION_MODE(_x, _y)  \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Page Scan Period Mode value in    */
   /* the HCI Inquiry Result Event Data.  The first parameter is a      */
   /* pointer to a Data Buffer that is an HCI_Inquiry Result_Event_t.   */
   /* The Second parameter is the Index of the Page Scan Period Mode    */
   /* Value to Read.                                                    */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_PERIOD_MODE(_x, _y)      \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Page Scan Mode value in the HCI   */
   /* Inquiry Result Event Data.  The first parameter is a pointer to   */
   /* a Data Buffer that is an HCI_Inquiry Result_Event_t.  The second  */
   /* parameter is the Index of the Page Scan Mode value to read.       */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_SCAN_MODE(_x, _y)        \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*2)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Class of Device value in the HCI  */
   /* Inquiry Result Event Data.  The first parameter is a pointer to   */
   /* a Data Buffer that is an HCI_Inquiry Result_Event_t.  The second  */
   /* parameter is the Index of the Class of Device value to read.      */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_CLASS_OF_DEVICE(_x, _y)  \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_Class_of_Device_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Clock Offset value in the HCI     */
   /* Inquiry Result Event Data.  The first parameter is a pointer to   */
   /* a Data Buffer that is an HCI_Inquiry Result_Event_t.  The second  */
   /* parameter is the Index of the Clock Offset value to read.         */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_EVENT_READ_CLOCK_OFFSET(_x, _y)     \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connection_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Link_Type;
   uint8_t                     Encryption_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connection_Complete_Event_t;

#define QAPI_BLE_HCI_CONNECTION_COMPLETE_EVENT_SIZE               (sizeof(qapi_BLE_HCI_Connection_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connection_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_Class_of_Device_t  Class_of_Device;
   uint8_t                     Link_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connection_Request_Event_t;

#define QAPI_BLE_HCI_CONNECTION_REQUEST_EVENT_SIZE                (sizeof(qapi_BLE_HCI_Connection_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnection_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnection_Complete_Event_t;

#define QAPI_BLE_HCI_DISCONNECTION_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Disconnection_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Authentication_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Authentication_Complete_Event_t;

#define QAPI_BLE_HCI_AUTHENTICATION_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Authentication_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Name_Request_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Name_Request_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Remote     */
   /* Name Request Complete Event Data Structure based upon the Length  */
   /* of the Name String (in bytes, including the NULL terminating      */
   /* character).  The first parameter to this MACRO is the Length of   */
   /* the Name String (in bytes, including the NULL terminating         */
   /* character).                                                       */
#define QAPI_BLE_HCI_REMOTE_NAME_REQUEST_COMPLETE_EVENT_SIZE(_x)  ((sizeof(qapi_BLE_HCI_Remote_Name_Request_Complete_Event_t) - sizeof(uint8_t)) + ((uint8_t)(_x)*(sizeof(uint8_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Encryption_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Encryption_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Encryption_Change_Event_t;

#define QAPI_BLE_HCI_ENCRYPTION_CHANGE_EVENT_SIZE                 (sizeof(qapi_BLE_HCI_Encryption_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Connection_Link_Key_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Connection_Link_Key_Complete_Event_t;

#define QAPI_BLE_HCI_CHANGE_CONNECTION_LINK_KEY_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Change_Connection_Link_Key_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Master_Link_Key_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Key_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Master_Link_Key_Complete_Event_t;

#define QAPI_BLE_HCI_MASTER_LINK_KEY_COMPLETE_EVENT_SIZE          (sizeof(qapi_BLE_HCI_Master_Link_Key_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Supported_Features_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_LMP_Features_t     LMP_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Supported_Features_Complete_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Supported_Features_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     LMP_Version;
   qapi_BLE_NonAlignedWord_t   Manufacturer_Name;
   qapi_BLE_NonAlignedWord_t   LMP_Subversion;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_QoS_Setup_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Flags;
   uint8_t                     Service_Type;
   qapi_BLE_NonAlignedDWord_t  Token_Rate;
   qapi_BLE_NonAlignedDWord_t  Peak_Bandwidth;
   qapi_BLE_NonAlignedDWord_t  Latency;
   qapi_BLE_NonAlignedDWord_t  Delay_Variation;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_QoS_Setup_Complete_Event_t;

#define QAPI_BLE_HCI_QOS_SETUP_COMPLETE_EVENT_SIZE                (sizeof(qapi_BLE_HCI_QoS_Setup_Complete_Event_t))

   /* The following type declaration represents the structure of an HCI */
   /* Command Complete Event Header.  This structure will be present    */
   /* at the beginning of ALL HCI Command Complete Event Packets.       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Command_Complete_Event_Header_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Num_HCI_Command_Packets;
   qapi_BLE_NonAlignedWord_t   Command_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Command_Complete_Event_Header_t;

#define QAPI_BLE_HCI_COMMAND_COMPLETE_EVENT_HEADER_SIZE           (sizeof(qapi_BLE_HCI_Command_Complete_Event_Header_t))

   /* The following type declaration represents the structure of an HCI */
   /* Command Status Event.  The first element of this structure is     */
   /* the HCI Event Header (see description above), followed by the     */
   /* data that is unique to this HCI Event Type Structure.             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Command_Status_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Num_HCI_Command_Packets;
   qapi_BLE_NonAlignedWord_t   Command_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Command_Status_Event_t;

#define QAPI_BLE_HCI_COMMAND_STATUS_EVENT_SIZE                    (sizeof(qapi_BLE_HCI_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Hardware_Error_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Hardware_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Hardware_Error_Event_t;

#define QAPI_BLE_HCI_HARDWARE_ERROR_EVENT_SIZE                    (sizeof(qapi_BLE_HCI_Hardware_Error_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flush_Occurred_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flush_Occurred_Event_t;

#define QAPI_BLE_HCI_FLUSH_OCCURRED_EVENT_SIZE                    (sizeof(qapi_BLE_HCI_Flush_Occurred_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Role_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     New_Role;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Role_Change_Event_t;

#define QAPI_BLE_HCI_ROLE_CHANGE_EVENT_SIZE                       (sizeof(qapi_BLE_HCI_Role_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Number_Of_Completed_Packets_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Number_of_Handles;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Number_Of_Completed_Packets_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Number of Completed Packets Event Data Structure based        */
   /* upon the Number of Connection Handle/Number of Completed Packet   */
   /* Pairs that are specified.  The first parameter to this MACRO is   */
   /* the Number of Connection Handle/Number of Completed Packet Pairs. */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_SIZE(_x)   ((sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Event_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_NonAlignedWord_t)+sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Connection Handle in the Number of*/
   /* Completed Packets Event Data.  The first parameter is a pointer to*/
   /* a Data Buffer that is an                                          */
   /* qapi_BLE_HCI_Number_Of_Completed_Packets_Event_t.  The second     */
   /* parameter is the Index of the Connection Handle to Read.          */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_READ_HANDLE(_x, _y)      \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read the specified Number of Completed Packets in  */
   /* the Number of Completed Packets Event Data.  The first parameter  */
   /* is a pointer to a Data Buffer that is an                          */
   /* qapi_BLE_HCI_Number_Of_Completed_Packets_Event_t.  The second     */
   /* parameter is the Index of the Number of Completed Packets to Read.*/
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_READ_NUM_PACKETS(_x, _y) \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_NonAlignedWord_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Mode_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Current_Mode;
   qapi_BLE_NonAlignedWord_t   Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Mode_Change_Event_t;

#define QAPI_BLE_HCI_MODE_CHANGE_EVENT_SIZE                       (sizeof(qapi_BLE_HCI_Mode_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Return_Link_Keys_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Num_Keys;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Return_Link_Keys_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Return Link Keys Event Data Structure based upon the Number   */
   /* of BD_ADDR/Link Key Pairs that are specified.  The first          */
   /* parameter to this MACRO is the Number of BD_ADDR/Link Key Pairs.  */
#define QAPI_BLE_HCI_RETURN_LINK_KEYS_EVENT_SIZE(_x)              ((sizeof(qapi_BLE_HCI_Return_Link_Keys_Event_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_BD_ADDR_t)+sizeof(qapi_BLE_Link_Key_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified BD_ADDR in the Return Link Keys   */
   /* Event Data.  The first parameter is a pointer to a Data Buffer    */
   /* that is a qapi_BLE_HCI_Return_Link_Keys_Event_t.  The second      */
   /* parameter is the Index of the BD_ADDR to Read.                    */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_RETURN_LINK_KEYS_EVENT_READ_BD_ADDR(_x, _y)  \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_BD_ADDR_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(qapi_BLE_Link_Key_t))))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read the specified Link Key in the Return Link Keys*/
   /* Event Data.of Completed Packets Event Data.  The first parameter  */
   /* Event Data.  The first parameter is a pointer to a Data Buffer    */
   /* that is a qapi_BLE_HCI_Return_Link_Keys_Event_t.  The second      */
   /* parameter is the Index of the Link Key to Read.                   */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_RETURN_LINK_KEYS_EVENT_READ_LINK_KEY(_x, _y) \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_Link_Key_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(qapi_BLE_Link_Key_t))) + sizeof(qapi_BLE_BD_ADDR_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_PIN_Code_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_PIN_Code_Request_Event_t;

#define QAPI_BLE_HCI_PIN_CODE_REQUEST_EVENT_SIZE                  (sizeof(qapi_BLE_HCI_PIN_Code_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Request_Event_t;

#define QAPI_BLE_HCI_LINK_KEY_REQUEST_EVENT_SIZE                  (sizeof(qapi_BLE_HCI_Link_Key_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Notification_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_Link_Key_t         Link_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Notification_Event_t;

#define QAPI_BLE_HCI_LINK_KEY_NOTIFICATION_EVENT_SIZE             (sizeof(qapi_BLE_HCI_Link_Key_Notification_Event_t))

   /* Below is the HCI Link Key Notification Event for the Bluetooth    */
   /* HCI 1.1 Specification (Version 1.1).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Notification_Event_1_1_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_Link_Key_t         Link_Key;
   uint8_t                     Key_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Notification_Event_1_1_t;

#define QAPI_BLE_HCI_LINK_KEY_NOTIFICATION_EVENT_1_1_SIZE         (sizeof(qapi_BLE_HCI_Link_Key_Notification_Event_1_1_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Loopback_Command_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Loopback_Command_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Loopback Command Event Data Structure based upon the size of  */
   /* the HCI Command Data Packet Required.  The first parameter to     */
   /* this MACRO is the Size of the HCI Command Data Packet (in bytes). */
#define QAPI_BLE_HCI_LOOPBACK_COMMAND_EVENT_SIZE(_x)              ((sizeof(qapi_BLE_HCI_Loopback_Command_Event_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Data_Buffer_Overflow_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Link_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Data_Buffer_Overflow_Event_t;

#define QAPI_BLE_HCI_DATA_BUFFER_OVERFLOW_EVENT_SIZE              (sizeof(qapi_BLE_HCI_Data_Buffer_Overflow_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Max_Slots_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     LMP_Max_Slots;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Max_Slots_Change_Event_t;

#define QAPI_BLE_HCI_MAX_SLOTS_CHANGE_EVENT_SIZE                  (sizeof(qapi_BLE_HCI_Max_Slots_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Clock_Offset_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_NonAlignedWord_t   Clock_Offset;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Clock_Offset_Complete_Event_t;

#define QAPI_BLE_HCI_READ_CLOCK_OFFSET_COMPLETE_EVENT_SIZE        (sizeof(qapi_BLE_HCI_Read_Clock_Offset_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connection_Packet_Type_Changed_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_NonAlignedWord_t   Packet_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connection_Packet_Type_Changed_Event_t;

#define QAPI_BLE_HCI_CONNECTION_PACKET_TYPE_CHANGED_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Connection_Packet_Type_Changed_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_QoS_Violation_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_QoS_Violation_Event_t;

#define QAPI_BLE_HCI_QOS_VIOLATION_EVENT_SIZE                     (sizeof(qapi_BLE_HCI_QoS_Violation_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Page_Scan_Mode_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Page_Scan_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Page_Scan_Mode_Change_Event_t;

#define QAPI_BLE_HCI_PAGE_SCAN_MODE_CHANGE_EVENT_SIZE             (sizeof(qapi_BLE_HCI_Page_Scan_Mode_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Page_Scan_Repetition_Mode_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Page_Scan_Repetition_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Page_Scan_Repetition_Mode_Change_Event_t;

#define QAPI_BLE_HCI_PAGE_SCAN_REPETITION_MODE_CHANGE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Page_Scan_Repetition_Mode_Change_Event_t))

   /* The following events represent the new Events that are part of    */
   /* Bluetooth Version 1.2.                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Specification_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Flags;
   uint8_t                     Flow_Direction;
   uint8_t                     Service_Type;
   qapi_BLE_NonAlignedDWord_t  Token_Rate;
   qapi_BLE_NonAlignedDWord_t  Token_Bucket_Size;
   qapi_BLE_NonAlignedDWord_t  Peak_Bandwidth;
   qapi_BLE_NonAlignedDWord_t  Access_Latency;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Specification_Complete_Event_t;

#define QAPI_BLE_HCI_FLOW_SPECIFICATION_COMPLETE_EVENT_SIZE       (sizeof(qapi_BLE_HCI_Flow_Specification_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Num_Responses;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Inquiry    */
   /* Result With RSSI Event Data Structure based upon the Number of    */
   /* Responses.  The first parameter of this MACRO is the Number of    */
   /* Responses.                                                        */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_SIZE(_x)      ((sizeof(qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_BD_ADDR_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(qapi_BLE_Class_of_Device_t)+sizeof(qapi_BLE_NonAlignedWord_t)+sizeof(uint8_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified BD_ADDR in the HCI Inquiry Result */
   /* With RSSI Event Data.  The first parameter is a pointer to a Data */
   /* Buffer that is an qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  */
   /* The Second parameter is the Index of the BD_ADDR to Read.         */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_BD_ADDR(_x, _y)          \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_BD_ADDR_t *)(((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t)))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Page Scan Repetition Mode value in*/
   /* the HCI Inquiry Result With RSSI Event Data.  The first parameter */
   /* is a pointer to a Data Buffer that is an                          */
   /* qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  The Second        */
   /* parameter is the Index of the Page Scan Repetition Mode Value to  */
   /* Read.                                                             */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_REPETITION_MODE(_x, _y)  \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Page Scan Period Mode value in the*/
   /* HCI Inquiry Result With RSSI Event Data.  The first parameter is a*/
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  The Second        */
   /* parameter is the Index of the Page Scan Period Mode Value to Read.*/
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_PERIOD_MODE(_x, _y)      \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Class of Device value in the HCI  */
   /* Inquiry Result With RSSI Event Data.  The first parameter is a    */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  The second        */
   /* parameter is the Index of the Class of Device value to read.      */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_CLASS_OF_DEVICE(_x, _y)  \
   READ_UNALIGNED_GENERIC_TYPE(((qapi_BLE_Class_of_Device_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*2)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Clock Offset value in the HCI     */
   /* Inquiry Result With RSSI Event Data.  The first parameter is a    */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  The second        */
   /* parameter is the Index of the Clock Offset value to read.         */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_CLOCK_OFFSET(_x, _y)     \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*2 + sizeof(qapi_BLE_Class_of_Device_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified RSSI value in the HCI Inquiry     */
   /* Result With RSSI Event Data.  The first parameter is a pointer to */
   /* a Data Buffer that is an                                          */
   /* qapi_BLE_HCI_Inquiry_Result_With_RSSI_Event_t.  The second        */
   /* parameter is the Index of the RSSI value to read.                 */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_READ_RSSI(_x, _y)     \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*3 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_BD_ADDR_t) + sizeof(uint8_t)*2 + sizeof(qapi_BLE_Class_of_Device_t) + sizeof(qapi_BLE_NonAlignedWord_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Extended_Features_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Page_Number;
   uint8_t                     Maximum_Page_Number;
   qapi_BLE_LMP_Features_t     Extended_LMP_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Extended_Features_Complete_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Remote_Extended_Features_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Synchronous_Connection_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Link_Type;
   uint8_t                     Transmission_Interval;
   uint8_t                     Retransmission_Window;
   qapi_BLE_NonAlignedWord_t   Rx_Packet_Length;
   qapi_BLE_NonAlignedWord_t   Tx_Packet_Length;
   uint8_t                     Air_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Synchronous_Connection_Complete_Event_t;

#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Synchronous_Connection_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Synchronous_Connection_Changed_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Transmission_Interval;
   uint8_t                     Retransmission_Window;
   qapi_BLE_NonAlignedWord_t   Rx_Packet_Length;
   qapi_BLE_NonAlignedWord_t   Tx_Packet_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Synchronous_Connection_Changed_Event_t;

#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_CHANGED_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Synchronous_Connection_Changed_Event_t))

   /* The following events represent the new Events that are part of    */
   /* Bluetooth Version 2.1 + EDR.                                      */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Sniff_Subrating_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_NonAlignedWord_t   Maximum_Transmit_Latency;
   qapi_BLE_NonAlignedWord_t   Maximum_Receive_Latency;
   qapi_BLE_NonAlignedWord_t   Minimum_Remote_Timeout;
   qapi_BLE_NonAlignedWord_t   Minimum_Local_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Sniff_Subrating_Event_t;

#define QAPI_BLE_HCI_SNIFF_SUBRATING_EVENT_SIZE                   (sizeof(qapi_BLE_HCI_Sniff_Subrating_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Extended_Inquiry_Result_Event_s
{
   qapi_BLE_HCI_Event_Header_t               HCI_Event_Header;
   uint8_t                                   Num_Responses;
   qapi_BLE_BD_ADDR_t                        BD_ADDR;
   uint8_t                                   Page_Scan_Repetition_Mode;
   uint8_t                                   Reserved;
   qapi_BLE_Class_of_Device_t                Class_of_Device;
   qapi_BLE_NonAlignedWord_t                 Clock_Offset;
   uint8_t                                   RSSI;
   qapi_BLE_Extended_Inquiry_Response_Data_t Extended_Inquiry_Response;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Extended_Inquiry_Result_Event_t;

#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESULT_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Extended_Inquiry_Result_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_t;

#define QAPI_BLE_HCI_ENCRYPTION_KEY_REFRESH_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Request_Event_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_REQUEST_EVENT_SIZE             (sizeof(qapi_BLE_HCI_IO_Capability_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Response_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     IO_Capability;
   uint8_t                     OOB_Data_Present;
   uint8_t                     Authentication_Requirements;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Response_Event_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_RESPONSE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_IO_Capability_Response_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Confirmation_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_NonAlignedDWord_t  Numeric_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Confirmation_Request_Event_t;

#define QAPI_BLE_HCI_USER_CONFIRMATION_REQUEST_EVENT_SIZE         (sizeof(qapi_BLE_HCI_User_Confirmation_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Request_Event_t;

#define QAPI_BLE_HCI_USER_PASSKEY_REQUEST_EVENT_SIZE              (sizeof(qapi_BLE_HCI_User_Passkey_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Data_Request_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Data_Request_Event_t;

#define QAPI_BLE_HCI_REMOTE_OOB_DATA_REQUEST_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Remote_OOB_Data_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Simple_Pairing_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Simple_Pairing_Complete_Event_t;

#define QAPI_BLE_HCI_SIMPLE_PAIRING_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Simple_Pairing_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Supervision_Timeout_Changed_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   qapi_BLE_NonAlignedWord_t   Link_Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Supervision_Timeout_Changed_Event_t;

#define QAPI_BLE_HCI_LINK_SUPERVISION_TIMEOUT_CHANGED_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Link_Supervision_Timeout_Changed_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Flush_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Flush_Complete_Event_t;

#define QAPI_BLE_HCI_ENHANCED_FLUSH_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Enhanced_Flush_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Notification_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_NonAlignedDWord_t  Passkey;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Notification_Event_t;

#define QAPI_BLE_HCI_USER_PASSKEY_NOTIFICATION_EVENT_SIZE         (sizeof(qapi_BLE_HCI_User_Passkey_Notification_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Keypress_Notification_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     Notification_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Keypress_Notification_Event_t;

#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_EVENT_SIZE             (sizeof(qapi_BLE_HCI_Keypress_Notification_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Host_Supported_Features_Notification_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_LMP_Features_t     Host_Supported_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Host_Supported_Features_Notification_Event_t;

#define QAPI_BLE_HCI_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Remote_Host_Supported_Features_Notification_Event_t))

   /* The following events represent the new Events that are part of    */
   /* Bluetooth Version 3.0 + HS.                                       */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Physical_Link_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Physical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Physical_Link_Complete_Event_t;

#define QAPI_BLE_HCI_PHYSICAL_LINK_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Physical_Link_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Channel_Selected_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Physical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Channel_Selected_Event_t;

#define QAPI_BLE_HCI_CHANNEL_SELECTED_EVENT_SIZE                  (sizeof(qapi_BLE_HCI_Channel_Selected_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnection_Physical_Link_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Physical_Link_Handle;
   uint8_t                     Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnection_Physical_Link_Complete_Event_t;

#define QAPI_BLE_HCI_DISCONNECTION_PHYSICAL_LINK_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Disconnection_Physical_Link_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Physical_Link_Loss_Early_Warning_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Physical_Link_Handle;
   uint8_t                     Link_Loss_Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Physical_Link_Loss_Early_Warning_Event_t;

#define QAPI_BLE_HCI_PHYSICAL_LINK_LOSS_EARLY_WARNING_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Physical_Link_Loss_Early_Warning_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Physical_Link_Recovery_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Physical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Physical_Link_Recovery_Event_t;

#define QAPI_BLE_HCI_PHYSICAL_LINK_RECOVERY_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Physical_Link_Recovery_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Logical_Link_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Logical_Link_Handle;
   uint8_t                     Physical_Link_Handle;
   uint8_t                     Tx_Flow_Spec_ID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Logical_Link_Complete_Event_t;

#define QAPI_BLE_HCI_LOGICAL_LINK_COMPLETE_EVENT_SIZE             (sizeof(qapi_BLE_HCI_Logical_Link_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnection_Logical_Link_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Logical_Link_Handle;
   uint8_t                     Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnection_Logical_Link_Complete_Event_t;

#define QAPI_BLE_HCI_DISCONNECTION_LOGICAL_LINK_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Disconnection_Logical_Link_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Spec_Modify_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_NonAlignedWord_t   Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Spec_Modify_Complete_Event_t;

#define QAPI_BLE_HCI_FLOW_SPEC_MODIFY_COMPLETE_EVENT_SIZE         (sizeof(qapi_BLE_HCI_Flow_Spec_Modify_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Total_Num_Data_Blocks;
   uint8_t                     Number_of_Handles;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Number of  */
   /* Completed Data Packets Event Data Structure based upon the Number */
   /* of Connection Handle/Number of Completed Packets/Number of        */
   /* Completed Blocks triplets that are specified.  The first parameter*/
   /* to this MACRO is the Number of Connection Handle/Number of        */
   /* Completed Packet/Number of Completed Blocks triplets.             */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_SIZE(_x)  ((sizeof(qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_t) - sizeof(uint8_t)) + ((_x)*(sizeof(qapi_BLE_NonAlignedWord_t)+sizeof(qapi_BLE_NonAlignedWord_t)+sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Connection Handle in the Number of*/
   /* Completed Data Blocks Event Data.  The first parameter is a       */
   /* pointer to a Data Buffer that is an                               */
   /* qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_t.  The second */
   /* parameter is the Index of the Connection Handle to Read.          */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_READ_HANDLE(_x, _y)      \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + (_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read the specified Number of Completed Packets in  */
   /* the Number of Completed Data Blocks Event Data.  The first        */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_t.  The second */
   /* parameter is the Index of the Number of Completed Packets to Read.*/
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_READ_NUM_PACKETS(_x, _y) \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + sizeof(qapi_BLE_NonAlignedWord_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read the specified Number of Completed Blocks in   */
   /* the Number of Completed Data Blocks Event Data.  The first        */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Number_Of_Completed_Data_Blocks_Event_t.  The second */
   /* parameter is the Index of the Number of Completed Blocks to Read. */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_READ_NUM_BLOCKS(_x, _y) \
   READ_UNALIGNED_WORD_LITTLE_ENDIAN((((uint8_t *)((_x)->Variable_Data)) + ((_y)*(sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))) + (sizeof(qapi_BLE_NonAlignedWord_t) + sizeof(qapi_BLE_NonAlignedWord_t))))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Short_Range_Mode_Change_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Physical_Link_Handle;
   uint8_t                     Short_Range_Mode_State;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Short_Range_Mode_Change_Complete_Event_t;

#define QAPI_BLE_HCI_SHORT_RANGE_MODE_CHANGE_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Short_Range_Mode_Change_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Status_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     AMP_Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Status_Change_Event_t;

#define QAPI_BLE_HCI_AMP_STATUS_CHANGE_EVENT_SIZE                 (sizeof(qapi_BLE_HCI_AMP_Status_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Start_Test_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Test_Scenario;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Start_Test_Event_t;

#define QAPI_BLE_HCI_AMP_START_TEST_EVENT_SIZE                    (sizeof(qapi_BLE_HCI_AMP_Start_Test_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Test_End_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   uint8_t                     Test_Scenario;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Test_End_Event_t;

#define QAPI_BLE_HCI_AMP_TEST_END_EVENT_SIZE                      (sizeof(qapi_BLE_HCI_AMP_Test_End_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Receiver_Report_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Controller_Type;
   uint8_t                     Reason;
   qapi_BLE_NonAlignedDWord_t  Event_Type;
   qapi_BLE_NonAlignedWord_t   Number_Of_Frames;
   qapi_BLE_NonAlignedWord_t   Number_Of_Error_Frames;
   qapi_BLE_NonAlignedDWord_t  Number_Of_Bits;
   qapi_BLE_NonAlignedDWord_t  Number_Of_Error_Bits;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Receiver_Report_Event_t;

#define QAPI_BLE_HCI_AMP_RECEIVER_REPORT_EVENT_SIZE               (sizeof(qapi_BLE_HCI_AMP_Receiver_Report_Event_t))

   /* Miscellaneous Event Types (Version 1.1).                          */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Bluetooth_Logo_Testing_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Bluetooth_Logo_Testing_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Bluetooth Logo Testing Event Data Structure based upon the    */
   /* size of Total Number of Bytes required for the Parameters.  The   */
   /* first parameter to this MACRO is the Size (in Bytes) of the       */
   /* Bluetooth Logo Testing Event Packet Parameters (total).           */
#define QAPI_BLE_HCI_BLUETOOTH_LOGO_TESTING_EVENT_SIZE(_x)        ((sizeof(qapi_BLE_HCI_Bluetooth_Logo_Testing_Event_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Vendor_Specific_Debug_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Vendor_Specific_Debug_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Vendor Specific Debug Event Data Structure based upon the     */
   /* size of Total Number of Bytes required for the Parameters.  The   */
   /* first parameter to this MACRO is the Size (in Bytes) of the       */
   /* Vendor Specific Debug Event Packet Parameters (total).            */
#define QAPI_BLE_HCI_VENDOR_SPECIFIC_DEBUG_EVENT_SIZE(_x)         ((sizeof(qapi_BLE_HCI_Vendor_Specific_Debug_Event_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

   /* The following events represent the new LE Meta Events that are    */
   /* part of Bluetooth Version 4.0 + LE.                               */

   /* The following type declaration represents the structure of the    */
   /* Header of an HCI LE Meta Event Packet.  This Header Information is*/
   /* contained in every defined HCI LE Meta Event Packet.  This        */
   /* structure forms the basis of additional defined HCI LE Event      */
   /* Packets.  Since this structure is present at the begining of every*/
   /* defined HCI LE Meta Event Packet, this structure will be the first*/
   /* element of every defined HCI LE Event Packet in this file (Version*/
   /* 4.0 + LE).                                                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Meta_Event_Header_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Subevent_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Meta_Event_Header_t;

#define QAPI_BLE_HCI_LE_META_EVENT_HEADER_SIZE                    (sizeof(qapi_BLE_HCI_LE_Meta_Event_Header_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Meta_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Meta_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI LE Meta    */
   /* Event Data Structure based upon the number of bytes that are      */
   /* contained in the Subevent.  The first parameter to this MACRO is  */
   /* the size (in Bytes) of all of the Subevent data that is to be part*/
   /* of the HCI LE Meta Event.                                         */
#define QAPI_BLE_HCI_LE_META_EVENT_SIZE(_x)                       (sizeof(qapi_BLE_HCI_LE_Meta_Event_t) - sizeof(uint8_t) + (uint32_t)(_x))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Connection_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   uint8_t                             Role;
   uint8_t                             Peer_Address_Type;
   qapi_BLE_BD_ADDR_t                  Peer_Address;
   qapi_BLE_NonAlignedWord_t           Conn_Interval;
   qapi_BLE_NonAlignedWord_t           Conn_Latency;
   qapi_BLE_NonAlignedWord_t           Supervision_Timeout;
   uint8_t                             Master_Clock_Accuracy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Connection_Complete_Event_t;

#define QAPI_BLE_HCI_LE_CONNECTION_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_LE_Connection_Complete_Event_t))

   /* The following structure is used with the                          */
   /* qapi_BLE_HCI_LE_Advertising_Report_Event_t event to define an     */
   /* individual report entry.  An individual report entry contains zero*/
   /* or more bytes of Advertising Data (in the Variable_Data member)   */
   /* and will always contain the RSSI value (byte value) in the        */
   /* Variable_Data member as well.  This means that the Variable_Data  */
   /* member *MUST* be at least a single byte long.                     */
   /* * NOTE * The RSSI value is *ALWAYS* contained in the Variable_Data*/
   /*          member as it is *ALWAYS* present in a report entry.  This*/
   /*          means that the Variable_Data member will be a single byte*/
   /*          long when the Length_Data member is zero (it will be two */
   /*          bytes when the Length_Data member is one, etc).          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Advertising_Report_Entry_s
{
   uint8_t            Event_Type;
   uint8_t            Address_Type;
   qapi_BLE_BD_ADDR_t Address;
   uint8_t            Length_Data;
   uint8_t            Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Advertising_Report_Entry_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an individual HCI */
   /* LE Advertising Report Entry based upon the length of the report (0*/
   /* to QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE).  The first parameter  */
   /* of this MACRO is the Number of advertising report bytes.          */
   /* * NOTE * The RSSI member that is present in each entry is ALREADY */
   /*          accounted for in this calculation and the length of the  */
   /*          RSSI field (1 byte) SHOULD NOT be specified in this      */
   /*          MACRO.  The parameter to this MACRO should ONLY specify  */
   /*          the number of advertising bytes !!!!!!!!!!!!!!!!!!!!!!!! */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_ENTRY_SIZE(_x)         (sizeof(qapi_BLE_HCI_LE_Advertising_Report_Entry_t) + ((uint32_t)(_x)))

   /* Advertising Report Event.  Note that the Report_Entries member    */
   /* contains zero (or more                                            */
   /* qapi_BLE_HCI_LE_Advertising_Report_Entry_t's).                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Advertising_Report_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Num_Reports;
   uint8_t                             Report_Entries[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Advertising_Report_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI LE         */
   /* Advertising Report Event Data Structure based upon the Number of  */
   /* total Report Entry bytes (not individual reports).  The first     */
   /* parameter of this MACRO is the Number of total Report Entry bytes */
   /* (for ALL reports).  This MACRO will return the total size of the  */
   /* entire HCI LE Advertising Report Event (in bytes).                */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_SIZE(_x)         (sizeof(qapi_BLE_HCI_LE_Advertising_Report_Event_t) - sizeof(uint8_t) + ((uint32_t)(_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Connection_Update_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedWord_t           Conn_Interval;
   qapi_BLE_NonAlignedWord_t           Conn_Latency;
   qapi_BLE_NonAlignedWord_t           Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Connection_Update_Complete_Event_t;

#define QAPI_BLE_HCI_LE_CONNECTION_UPDATE_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_LE_Connection_Update_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_LE_Features_t              LE_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_REMOTE_USED_FEATURES_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_Random_Number_t            Random_Number;
   qapi_BLE_NonAlignedWord_t           Encrypted_Diversifier;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_t;

#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_EVENT_SIZE                (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_t))

   /* The following events represent the new LE Meta Events that are    */
   /* part of Bluetooth Version 4.1.                                    */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedWord_t           Conn_Interval_Min;
   qapi_BLE_NonAlignedWord_t           Conn_Interval_Max;
   qapi_BLE_NonAlignedWord_t           Conn_Latency;
   qapi_BLE_NonAlignedWord_t           Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_t;

#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_t))

   /* The following events represent the new LE Meta Events that are    */
   /* part of Bluetooth Version 4.2.                                    */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Data_Length_Change_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedWord_t           MaxTxOctets;
   qapi_BLE_NonAlignedWord_t           MaxTxTime;
   qapi_BLE_NonAlignedWord_t           MaxRxOctets;
   qapi_BLE_NonAlignedWord_t           MaxRxTime;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Data_Length_Change_Event_t;

#define QAPI_BLE_HCI_LE_DATA_LENGTH_CHANGE_EVENT_SIZE                   (sizeof(qapi_BLE_HCI_LE_Data_Length_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_P256_Public_Key_t          P256_Public_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_Diffie_Hellman_Key_t       DHKey;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_t;

#define QAPI_BLE_HCI_LE_GENERATE_DHKEY_COMPLETE_EVENT_SIZE               (sizeof(qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   uint8_t                             Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   uint8_t                             Role;
   uint8_t                             Peer_Address_Type;
   qapi_BLE_BD_ADDR_t                  Peer_Address;
   qapi_BLE_BD_ADDR_t                  Local_Resolvable_Private_Address;
   qapi_BLE_BD_ADDR_t                  Peer_Resolvable_Private_Address;
   qapi_BLE_NonAlignedWord_t           Conn_Interval;
   qapi_BLE_NonAlignedWord_t           Conn_Latency;
   qapi_BLE_NonAlignedWord_t           Supervision_Timeout;
   uint8_t                             Master_Clock_Accuracy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_t;

#define QAPI_BLE_HCI_LE_ENHANCED_CONNECTION_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_t))

   /* The following structure is used with the                          */
   /* qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_t event to define */
   /* an individual report entry.                                       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Direct_Advertising_Report_Entry_s
{
   uint8_t            Event_Type;
   uint8_t            Direct_Address_Type;
   qapi_BLE_BD_ADDR_t Direct_Address;
   uint8_t            Address_Type;
   qapi_BLE_BD_ADDR_t Address;
   int8_t             RSSI;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Direct_Advertising_Report_Entry_t;

#define QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_ENTRY_SIZE             (sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Entry_t))

   /* Direct_Advertising Report Event.  Note that the Report_Entries    */
   /* member contains zero (or more                                     */
   /* qapi_BLE_HCI_LE_Direct_Advertising_Report_Entry_t's).             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t               HCI_LE_Meta_Event_Header;
   uint8_t                                           Num_Reports;
   qapi_BLE_HCI_LE_Direct_Advertising_Report_Entry_t Report_Entries[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI LE         */
   /* Direct Advertising Report Event Data Structure based upon the     */
   /* number of total individual reports.  The first parameter of this  */
   /* MACRO is the number of total individual reports. This MACRO will  */
   /* return the total size of the entire HCI_LE Direct_Advertising     */
   /* Report Event (in bytes).                                          */
#define QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_EVENT_SIZE(_x)         ((sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_t) - QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_ENTRY_SIZE) + (((uint32_t)(_x))*QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_ENTRY_SIZE))

   /* The following events represent the new LE Meta Events that are    */
   /* part of Bluetooth Version 5.0.                                    */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_PHY_Update_Complete_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedByte_t           TX_PHY;
   qapi_BLE_NonAlignedByte_t           RX_PHY;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_PHY_Update_Complete_Event_t;

#define QAPI_BLE_HCI_LE_PHY_UPDATE_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_LE_PHY_Update_Complete_Event_t))

   /* The following structure is used with the                          */
   /* HCI_LE_Extended_Advertising_Report_Event_t event to define an     */
   /* individual report entry.                                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Advertising_Report_Entry_s
{
   qapi_BLE_NonAlignedWord_t  Event_Type;
   qapi_BLE_NonAlignedByte_t  Address_Type;
   qapi_BLE_BD_ADDR_t         Address;
   qapi_BLE_NonAlignedByte_t  Primary_PHY;
   qapi_BLE_NonAlignedByte_t  Secondary_PHY;
   qapi_BLE_NonAlignedByte_t  Advertising_SID;
   qapi_BLE_NonAlignedSByte_t TX_Power;
   qapi_BLE_NonAlignedSByte_t RSSI;
   qapi_BLE_NonAlignedWord_t  Periodic_Advertising_Interval;
   qapi_BLE_NonAlignedByte_t  Direct_Address_Type;
   qapi_BLE_BD_ADDR_t         Direct_Address;
   qapi_BLE_NonAlignedByte_t  Data_Length;
   qapi_BLE_NonAlignedByte_t  Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Advertising_Report_Entry_t;

   /* The following MACRO is a utility MACRO that exists to determine   */
   /* the size (in Bytes) of an individual HCI LE Extended Advertising  */
   /* Report Entry based upon the length of the Data field (0 to        */
   /* EXTENDED_ADVERTISING_DATA_MAXIMUM_SIZE). The first parameter of   */
   /* this MACRO is the Data_Length, which represents the length of the */
   /* Data field.                                                       */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_ENTRY_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Extended_Advertising_Report_Entry_t, Data) + (_x)))

   /* Extended Advertising Report Event. Note that the Report_Entries   */
   /* member contains zero (or more                                     */
   /* HCI_LE_Extended_Advertising_Report_Entry_t's).                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Num_Reports;
   qapi_BLE_NonAlignedByte_t           Report_Entries[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_t;

   /* The following MACRO is a utility MACRO that exists to determine   */
   /* the size (in Bytes) of an HCI LE Extended Advertising Report Event*/
   /* Data structure based upon the length of the Report_Entries field  */
   /* (This is the total size of all extended advertising report entries*/
   /* including the each entry's variable advertising data). The first  */
   /* parameter of this MACRO is the length of the Report_Entries field.*/
   /* This MACRO will return the total size of the entire HCI LE        */
   /* Extended Advertising Report Event (in bytes).                     */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_t, Report_Entries) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
   qapi_BLE_NonAlignedByte_t           Advertising_SID;
   qapi_BLE_NonAlignedByte_t           Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t                  Advertiser_Address;
   qapi_BLE_NonAlignedByte_t           Advertiser_PHY;
   qapi_BLE_NonAlignedWord_t           Periodic_Advertising_Interval;
   qapi_BLE_NonAlignedByte_t           Advertiser_Clock_Accuracy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
   qapi_BLE_NonAlignedSByte_t          TX_Power;
   qapi_BLE_NonAlignedSByte_t          RSSI;
   qapi_BLE_NonAlignedByte_t           Unused;
   qapi_BLE_NonAlignedByte_t           Data_Status;
   qapi_BLE_NonAlignedByte_t           Data_Length;
   qapi_BLE_NonAlignedByte_t           Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_EVENT_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_t, Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedByte_t           Advertising_Handle;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedByte_t           Num_Completed_Extended_Advertising_Events;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_t;

#define QAPI_BLE_HCI_LE_ADVERTISING_SET_TERMINATED_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Scan_Request_Received_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Advertising_Handle;
   qapi_BLE_NonAlignedByte_t           Scanner_Address_Type;
   qapi_BLE_BD_ADDR_t                  Scanner_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Scan_Request_Received_Event_t;

#define QAPI_BLE_HCI_LE_SCAN_REQUEST_RECEIVED_EVENT_SIZE          (sizeof(qapi_BLE_HCI_LE_Scan_Request_Received_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedByte_t           Channel_Selection_Algorithm;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_t;

#define qapi_BLE_HCI_LE_CHANNEL_SELECTION_ALGORITHM_EVENT_SIZE    (sizeof(qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_V2_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
   qapi_BLE_NonAlignedByte_t           Advertising_SID;
   qapi_BLE_NonAlignedByte_t           Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t                  Advertiser_Address;
   qapi_BLE_NonAlignedByte_t           Advertiser_PHY;
   qapi_BLE_NonAlignedWord_t           Periodic_Advertising_Interval;
   qapi_BLE_NonAlignedByte_t           Advertiser_Clock_Accuracy;
   qapi_BLE_NonAlignedByte_t           Num_Subevents;
   qapi_BLE_NonAlignedByte_t           Subevent_Interval;
   qapi_BLE_NonAlignedByte_t           Response_Slot_Delay;
   qapi_BLE_NonAlignedByte_t           Response_Slot_Duration;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_V2_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_V2_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Report_V2_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
   qapi_BLE_NonAlignedSByte_t          TX_Power;
   qapi_BLE_NonAlignedSByte_t          RSSI;
   qapi_BLE_NonAlignedByte_t           CTE_Type;
   qapi_BLE_NonAlignedWord_t           Periodic_Event_Counter;
   qapi_BLE_NonAlignedByte_t           Subevent;
   qapi_BLE_NonAlignedByte_t           Data_Status;
   qapi_BLE_NonAlignedByte_t           Data_Length;
   qapi_BLE_NonAlignedByte_t           Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Report_V2_Event_t;

   /* The following MACRO is a utility MACRO that exists to calculated  */
   /* the size of the HCI_LE_Periodic_Advertising_Report_V2_Event_t     */
   /* structure.  The first parameter is the Data_Length field.         */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_V2_EVENT_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Periodic_Advertising_Report_V2_Event_t, Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_V2_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedWord_t           Service_Data;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
   qapi_BLE_NonAlignedByte_t           Advertising_SID;
   qapi_BLE_NonAlignedByte_t           Advertiser_Address_Type;
   qapi_BLE_BD_ADDR_t                  Advertiser_Address;
   qapi_BLE_NonAlignedByte_t           Advertiser_PHY;
   qapi_BLE_NonAlignedWord_t           Periodic_Advertising_Interval;
   qapi_BLE_NonAlignedByte_t           Advertiser_Clock_Accuracy;
   qapi_BLE_NonAlignedByte_t           Number_Subevents;
   qapi_BLE_NonAlignedByte_t           Subevent_Interval;
   qapi_BLE_NonAlignedByte_t           Response_Slot_Delay;
   qapi_BLE_NonAlignedByte_t           Response_Slot_Duration;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_V2_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_V2_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Subevent_Data_Request_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Advertising_Handle;
   qapi_BLE_NonAlignedByte_t           Subevent_Start;
   qapi_BLE_NonAlignedByte_t           Subevent_Data_Count;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Subevent_Data_Request_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Subevent_Data_Request_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_s
{
   qapi_BLE_NonAlignedSByte_t TX_Power;
   qapi_BLE_NonAlignedSByte_t RSSI;
   qapi_BLE_NonAlignedByte_t  CTE_Type;
   qapi_BLE_NonAlignedByte_t  Response_Slot;
   qapi_BLE_NonAlignedByte_t  Data_Status;
   qapi_BLE_NonAlignedByte_t  Data_Length;
   qapi_BLE_NonAlignedByte_t  Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_t;

   /* The following MACRO is a utility MACRO that exists to calculated  */
   /* the size of the HCI_LE_Periodic_Advertising_Response_Report_t     */
   /* structure. The first parameter is the Data_Length field.          */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_SIZE(_x) ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(HCI_LE_Periodic_Advertising_Response_Report_t, Data) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t                    HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t                              Advertising_Handle;
   qapi_BLE_NonAlignedByte_t                              Subevent;
   qapi_BLE_NonAlignedByte_t                              Tx_Status;
   qapi_BLE_NonAlignedByte_t                              Num_Responses;
   qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_t Responses[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_Event_t;

   /* The following MACRO is a utility MACRO that exists to calculated  */
   /* the size of the                                                   */
   /* HCI_LE_Periodic_Advertising_Response_Report_Event_t structure. The*/
   /* first parameter is the sum of all                                 */
   /* HCI_LE_Periodic_Advertising_Response_Report_t structures.         */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_EVENT_SIZE(_x)  ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Periodic_Advertising_Response_Report_Event_t, Responses) + (_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Connection_Complete_V2_Event_s
{
   qapi_BLE_HCI_LE_Meta_Event_Header_t HCI_LE_Meta_Event_Header;
   qapi_BLE_NonAlignedByte_t           Status;
   qapi_BLE_NonAlignedWord_t           Connection_Handle;
   qapi_BLE_NonAlignedByte_t           Role;
   qapi_BLE_NonAlignedByte_t           Peer_Address_Type;
   qapi_BLE_BD_ADDR_t                  Peer_Address;
   qapi_BLE_BD_ADDR_t                  Local_Resolvable_Private_Address;
   qapi_BLE_BD_ADDR_t                  Peer_Resolvable_Private_Address;
   qapi_BLE_NonAlignedWord_t           Conn_Interval;
   qapi_BLE_NonAlignedWord_t           Conn_Latency;
   qapi_BLE_NonAlignedWord_t           Supervision_Timeout;
   qapi_BLE_NonAlignedByte_t           Master_Clock_Accuracy;
   qapi_BLE_NonAlignedByte_t           Advertising_Handle;
   qapi_BLE_NonAlignedWord_t           Sync_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Connection_Complete_V2_Event_t;

#define QAPI_BLE_HCI_LE_ENHANCED_CONNECTION_COMPLETE_V2_EVENT_SIZE         (sizeof(qapi_BLE_HCI_LE_Enhanced_Connection_Complete_V2_Event_t))

   /* The following events represent the new Events that are part of    */
   /* Bluetooth Version 4.0 + CSA4.                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Triggered_Clock_Capture_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
   uint8_t                     Which_Clock;
   qapi_BLE_NonAlignedDWord_t  Clock;
   qapi_BLE_NonAlignedWord_t   Slot_Offset;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Triggered_Clock_Capture_Event_t;

#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Triggered_Clock_Capture_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Synchronization_Train_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Synchronization_Train_Complete_Event_t;

#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Synchronization_Train_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Synchronization_Train_Received_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   qapi_BLE_NonAlignedDWord_t  Clock_Offset;
   qapi_BLE_AFH_Channel_Map_t  AFH_Channel_Map;
   uint8_t                     LT_ADDR;
   qapi_BLE_NonAlignedDWord_t  Next_Broadcast_Instant;
   qapi_BLE_NonAlignedWord_t   Connectionless_Slave_Broadcast_Interval;
   uint8_t                     Service_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Synchronization_Train_Received_Event_t;

#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_RECEIVED_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Synchronization_Train_Received_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connectionless_Slave_Broadcast_Receive_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     LT_ADDR;
   qapi_BLE_NonAlignedDWord_t  CLK;
   qapi_BLE_NonAlignedDWord_t  Offset;
   uint8_t                     Receive_Status;
   uint8_t                     Fragment;
   uint8_t                     Data_Length;
   uint8_t                     Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connectionless_Slave_Broadcast_Receive_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI            */
   /* Connectionless Slave Broadcast Receive Event Data Structure based */
   /* upon the number of individual Data bytes associated with the      */
   /* event.  The first parameter to this MACRO is the size (in Bytes)  */
   /* of the Data that is part of the Connectionless Slave Broadcast    */
   /* Receive Event.                                                    */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT_SIZE(_x) (sizeof(qapi_BLE_HCI_Connectionless_Slave_Broadcast_Receive_Event_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* The following definition exists to define the Total Number of Data*/
   /* Bytes that can be supported by a single                           */
   /* qapi_BLE_HCI_Connectionless_Slave_Broadcast_Receive_Event_t       */
   /* Command Packet.                                                   */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT_MAX_DATA (((sizeof(uint8_t)*255) - QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT_SIZE(0))/(sizeof(uint8_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connectionless_Slave_Broadcast_Timeout_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
   uint8_t                     LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connectionless_Slave_Broadcast_Timeout_Event_t;

#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_TIMEOUT_EVENT_SIZE (sizeof(qapi_BLE_HCI_Connectionless_Slave_Broadcast_Timeout_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Truncated_Page_Complete_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   uint8_t                     Status;
   qapi_BLE_BD_ADDR_t          BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Truncated_Page_Complete_Event_t;

#define QAPI_BLE_HCI_TRUNCATED_PAGE_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Truncated_Page_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Connectionless_Slave_Broadcast_Channel_Map_Change_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_AFH_Channel_Map_t  Channel_Map;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Connectionless_Slave_Broadcast_Channel_Map_Change_Event_t;

#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_CHANNEL_MAP_CHANGE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Connectionless_Slave_Broadcast_Channel_Map_Change_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Response_Notification_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_LAP_t              LAP;
   uint8_t                     RSSI;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Response_Notification_Event_t;

#define QAPI_BLE_HCI_INQUIRY_RESPONSE_NOTIFICATION_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Inquiry_Response_Notification_Event_t))

   /* The following events represent the new Events that are part of    */
   /* Bluetooth Version 4.1.                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_s
{
   qapi_BLE_HCI_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedWord_t   Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_t;

#define QAPI_BLE_HCI_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_t))

   /* HCI Command Complete Event Definitions (Link Control).            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_INQUIRY_CANCEL_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Inquiry_Cancel_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_PERIODIC_INQUIRY_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Periodic_Inquiry_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_EXIT_PERIODIC_INQUIRY_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Exit_Periodic_Inquiry_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LINK_KEY_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Link_Key_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LINK_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Link_Key_Request_Negative_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_PIN_Code_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_PIN_Code_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_PIN_CODE_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_PIN_Code_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_PIN_CODE_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_PIN_Code_Request_Negative_Reply_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Control - Version    */
   /* 1.2).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Connection_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Connection_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_CREATE_CONNECTION_CANCEL_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Create_Connection_Cancel_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_REMOTE_NAME_REQUEST_CANCEL_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Remote_Name_Request_Cancel_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_LMP_Handle_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      LMP_Handle;
   qapi_BLE_NonAlignedDWord_t                   Reserved;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_LMP_Handle_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LMP_HANDLE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_LMP_Handle_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Control - Version 2.1*/
   /* + EDR).                                                           */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_IO_Capability_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_USER_CONFIRMATION_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_User_Confirmation_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_User_Confirmation_Request_Negative_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_USER_PASSKEY_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_User_Passkey_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_User_Passkey_Request_Negative_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_REMOTE_OOB_DATA_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Remote_OOB_Data_Request_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Remote_OOB_Data_Request_Negative_Reply_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_IO_CAPABILITY_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_IO_Capability_Request_Negative_Reply_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Control - Version 3.0*/
   /* + HS).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Logical_Link_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Physical_Link_Handle;
   uint8_t                                      Tx_Flow_Spec_ID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Logical_Link_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LOGICAL_LINK_CANCEL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Logical_Link_Cancel_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Control - Version 4.0*/
   /* + CSA4).                                                          */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Truncated_Page_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Truncated_Page_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_TRUNCATED_PAGE_CANCEL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Truncated_Page_Cancel_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      LT_ADDR;
   qapi_BLE_NonAlignedWord_t                    Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
   uint8_t                                      LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Receive_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Control - Version    */
   /* 4.1).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_Complete_Event_t;

#define QAPI_BLE_HCI_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Remote_OOB_Extended_Data_Request_Reply_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Policy).             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Role_Discovery_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      Current_Role;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Role_Discovery_Command_Complete_Event_t;

#define QAPI_BLE_HCI_ROLE_DISCOVERY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Role_Discovery_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Link_Policy_Settings_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedWord_t                    Link_Policy_Settings;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Link_Policy_Settings_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LINK_POLICY_SETTINGS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Link_Policy_Settings_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Link_Policy_Settings_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Link_Policy_Settings_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LINK_POLICY_SETTINGS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Link_Policy_Settings_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Policy - Version     */
   /* 1.2).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Link_Policy_Settings;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_DEFAULT_LINK_POLICY_SETTINGS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Default_Link_Policy_Settings_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_DEFAULT_LINK_POLICY_SETTINGS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Default_Link_Policy_Settings_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Link Policy - Version 2.1 */
   /* + EDR ).                                                          */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Sniff_Subrating_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Sniff_Subrating_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SNIFF_SUBRATING_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Sniff_Subrating_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and          */
   /* Baseband).                                                        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Mask_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Mask_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_EVENT_MASK_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Set_Event_Mask_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reset_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reset_Command_Complete_Event_t;

#define QAPI_BLE_HCI_RESET_COMMAND_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Reset_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Filter_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Filter_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_EVENT_FILTER_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_Event_Filter_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flush_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flush_Command_Complete_Event_t;

#define QAPI_BLE_HCI_FLUSH_COMMAND_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Flush_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_PIN_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      PIN_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_PIN_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PIN_TYPE_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Read_PIN_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_PIN_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_PIN_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PIN_TYPE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Write_PIN_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_New_Unit_Key_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_New_Unit_Key_Command_Complete_Event_t;

#define QAPI_BLE_HCI_CREATE_NEW_UNIT_KEY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Create_New_Unit_Key_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Stored_Link_Key_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Max_Num_Keys;
   qapi_BLE_NonAlignedWord_t                    Num_Keys_Read;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Stored_Link_Key_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_STORED_LINK_KEY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Stored_Link_Key_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Stored_Link_Key_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Num_Keys_Written;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Stored_Link_Key_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_STORED_LINK_KEY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Stored_Link_Key_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Delete_Stored_Link_Key_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Num_Keys_Deleted;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Delete_Stored_Link_Key_Command_Complete_Event_t;

#define QAPI_BLE_HCI_DELETE_STORED_LINK_KEY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Delete_Stored_Link_Key_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Local_Name_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Local_Name_Command_Complete_Event_t;

#define QAPI_BLE_HCI_CHANGE_LOCAL_NAME_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Change_Local_Name_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Name_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Name_Command_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Read       */
   /* Local Name Command Complete Event Data Structure based upon the   */
   /* Length of the Name String (in bytes, including the NULL           */
   /* terminating character).  The first parameter to this MACRO is the */
   /* Length of the Name String (in bytes, including the NULL           */
   /* terminating character).                                           */
#define QAPI_BLE_HCI_READ_LOCAL_NAME_COMMAND_COMPLETE_EVENT_SIZE(_x) ((sizeof(qapi_BLE_HCI_Read_Local_Name_Command_Complete_Event_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Conn_Accept_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_CONNECTION_ACCEPT_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Connection_Accept_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Connection_Accept_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Page_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PAGE_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Page_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PAGE_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Page_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Scan_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Scan_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Scan_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_SCAN_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Scan_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Scan_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Scan_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SCAN_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Scan_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Page_Scan_Interval;
   qapi_BLE_NonAlignedWord_t                    Page_Scan_Window;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Page_Scan_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Page_Scan_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Inquiry_Scan_Interval;
   qapi_BLE_NonAlignedWord_t                    Inquiry_Scan_Window;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_INQUIRY_SCAN_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Inquiry_Scan_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_SCAN_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Inquiry_Scan_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Authentication_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Authentication_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Authentication_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_AUTHENTICATION_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Authentication_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Authentication_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Authentication_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_AUTHENTICATION_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Authentication_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Encryption_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Encryption_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Encryption_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_ENCRYPTION_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Encryption_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Encryption_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Encryption_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_ENCRYPTION_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Encryption_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Class_of_Device_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Class_of_Device_t                   Class_of_Device;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Class_of_Device_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_CLASS_OF_DEVICE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Class_of_Device_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Class_of_Device_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Class_of_Device_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_CLASS_OF_DEVICE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Class_of_Device_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Voice_Setting_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Voice_Setting;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Voice_Setting_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_VOICE_SETTING_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Voice_Setting_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Voice_Setting_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Voice_Setting_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_VOICE_SETTING_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Voice_Setting_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedWord_t                    Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_AUTOMATIC_FLUSH_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Automatic_Flush_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_AUTOMATIC_FLUSH_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Automatic_Flush_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Num_Broadcast_Retran;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_NUM_BROADCAST_RETRANSMISSIONS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Num_Broadcast_Retransmissions_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_NUM_BROADCAST_RETRANSMISSIONS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Num_Broadcast_Retransmissions_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Hold_Mode_Activity;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_HOLD_MODE_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Hold_Mode_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_HOLD_MODE_ACTIVITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Hold_Mode_Activity_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Transmit_Power_Level_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   int8_t                                       Transmit_Power_Level;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Transmit_Power_Level_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_TRANSMIT_POWER_LEVEL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Transmit_Power_Level_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      SCO_Flow_Control_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_SCO_FLOW_CONTROL_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_SCO_Flow_Control_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SCO_FLOW_CONTROL_ENABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_SCO_Flow_Control_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_Host_Controller_To_Host_Flow_Control_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Host_Buffer_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Host_Buffer_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_HOST_BUFFER_SIZE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Host_Buffer_Size_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_Complete_Event_t;

#define QAPI_BLE_HCI_HOST_NUMBER_OF_COMPLETED_PACKETS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Host_Number_Of_Completed_Packets_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedWord_t                    Link_Supervision_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LINK_SUPERVISION_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Link_Supervision_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LINK_SUPERVISION_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Link_Supervision_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Num_Support_IAC;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_NUMBER_OF_SUPPORTED_IAC_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Number_Of_Supported_IAC_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Current_IAC_LAP_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Num_Current_IAC;
   uint8_t                                      Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Current_IAC_LAP_Command_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Read       */
   /* Current IAC LAP Command Complete Event Data Structure based upon  */
   /* the Number of Connection IACs that are required.  The first       */
   /* parameter to this MACRO is the Number of IAC's.                   */
#define QAPI_BLE_HCI_READ_CURRENT_IAC_LAP_COMMAND_COMPLETE_EVENT_SIZE(_x) ((sizeof(qapi_BLE_HCI_Read_Current_IAC_LAP_Command_Complete_Event_t) - sizeof(uint8_t)) + (((uint8_t)(_x))*(sizeof(qapi_BLE_LAP_t))))

   /* The following definition exists to define the Total Number of     */
   /* Stored IAC LAP's that can be supported by a single                */
   /* qapi_BLE_HCI_Read_Current_IAC_LAP_Command_t Command Packet.       */
#define QAPI_BLE_HCI_READ_CURRENT_IAC_LAP_COMMAND_MAX_IAC_LAPS    (((sizeof(uint8_t)*256) - QAPI_BLE_HCI_READ_CURRENT_IAC_LAP_COMMAND_COMPLETE_EVENT_SIZE(0))/(sizeof(qapi_BLE_LAP_t)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified IAC LAP in the Read Current IAC   */
   /* LAP Command Complete Event Data.  The first parameter is a pointer*/
   /* to a Data Buffer that is an                                       */
   /* qapi_BLE_HCI_Read_Current_IAC_LAP_Command_Complete_Event_t.  The  */
   /* second parameter is the Index of the IAC LAP to Read.             */
   /* * NOTE * This MACRO assumes that the Num_Current_IAC field of the */
   /*          qapi_BLE_HCI_Read_Current_IAC_LAP_Command_Complete_Event_*/
   /*          is valid and this value IS USED by this MACRO to         */
   /*          calculate the correct offset into the structure !        */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_READ_CURRENT_IAC_LAP_COMMAND_COMPLETE_EVENT_READ_IAC_LAP(_x, _y) \
   READ_UNALIGNED_GENERIC_TYPE(&(((qapi_BLE_LAP_t *)((_x)->Variable_Data))[(_y)]))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Current_IAC_LAP_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Current_IAC_LAP_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_CURRENT_IAC_LAP_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Current_IAC_LAP_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Page_Scan_Period_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_PERIOD_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Page_Scan_Period_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_PERIOD_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Page_Scan_Period_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Page_Scan_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Page_Scan_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Page_Scan_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 1.2).                                                   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_AFH_HOST_CHANNEL_CLASSIFICATION_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_AFH_Host_Channel_Classification_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Inquiry_Scan_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_INQUIRY_SCAN_TYPE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Inquiry_Scan_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_SCAN_TYPE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Inquiry_Scan_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Inquiry_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_INQUIRY_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Inquiry_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Inquiry_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Page_Scan_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Page_Scan_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Page_Scan_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_PAGE_SCAN_TYPE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Page_Scan_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Page_Scan_Type_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Page_Scan_Type_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_PAGE_SCAN_TYPE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Page_Scan_Type_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      AFH_Channel_Assessment_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_AFH_CHANNEL_ASSESSMENT_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_AFH_Channel_Assessment_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_AFH_CHANNEL_ASSESSMENT_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_AFH_Channel_Assessment_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 2.1 + EDR).                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      FEC_Required;
   qapi_BLE_Extended_Inquiry_Response_Data_t    Extended_Inquiry_Response;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_EXTENDED_INQUIRY_RESPONSE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Extended_Inquiry_Response_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_INQUIRY_RESPONSE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Extended_Inquiry_Response_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Refresh_Encryption_Key_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Refresh_Encryption_Key_Command_Complete_Event_t;

#define QAPI_BLE_HCI_REFRESH_ENCRYPTION_KEY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Refresh_Encryption_Key_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Simple_Pairing_Enable;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_SIMPLE_PAIRING_MODE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Simple_Pairing_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SIMPLE_PAIRING_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Simple_Pairing_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_OOB_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Simple_Pairing_Hash_t               Simple_Pairing_Hash;
   qapi_BLE_Simple_Pairing_Randomizer_t         Simple_Pairing_Randomizer;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_OOB_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_OOB_DATA_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Local_OOB_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   int8_t                                       TX_Power;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Inquiry_Response_Transmit_Power_Level_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Inquiry_Transmit_Power_Level_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Send_Keypress_Notification_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Send_Keypress_Notification_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SEND_KEYPRESS_NOTIFICATION_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Send_Keypress_Notification_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Erroneous_Data_Reporting;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_DEFAULT_ERRONEOUS_DATA_REPORTING_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Default_Erroneous_Data_Reporting_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Write_Default_Erroneous_Data_Reporting_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 3.0 + HS).                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Logical_Link_Accept_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Read_Logical_Link_Accept_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Logical_Link_Accept_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Logical_Link_Accept_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Write_Logical_Link_Accept_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_EVENT_MASK_PAGE_2_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Set_Event_Mask_Page_2_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Location_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Location_Domain_Aware;
   qapi_BLE_NonAlignedWord_t                    Location_Domain;
   uint8_t                                      Location_Domain_Options;
   uint8_t                                      Location_Options;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Location_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCATION_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Location_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Location_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Location_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LOCATION_DATA_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Location_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Flow_Control_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Flow_Control_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Flow_Control_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_FLOW_CONTROL_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Flow_Control_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Flow_Control_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Flow_Control_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_FLOW_CONTROL_MODE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Write_Flow_Control_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   int8_t                                       Transmit_Power_Level_GFSK;
   int8_t                                       Transmit_Power_Level_DQPSK;
   int8_t                                       Transmit_Power_Level_8DPSK;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_ENHANCED_TRANSMIT_POWER_LEVEL_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Enhanced_Transmit_Power_Level_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedDWord_t                   Best_Effort_Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_BEST_EFFORT_FLUSH_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Best_Effort_Flush_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Best_Effort_Flush_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Short_Range_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Short_Range_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SHORT_RANGE_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Short_Range_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 4.0 + LE).                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_LE_Host_Supported_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      LE_Supported_Host;
   uint8_t                                      Simultaneous_LE_Host;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_LE_Host_Supported_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LE_HOST_SUPPORTED_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_LE_Host_Supported_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_LE_Host_Supported_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_LE_Host_Supported_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LE_HOST_SUPPORTED_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_LE_Host_Supported_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 4.0 + CSA3).                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_MWS_CHANNEL_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Set_MWS_Channel_Parameters_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_External_Frame_Configuration_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_External_Frame_Configuration_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Set_External_Frame_Configuration_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Signaling_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_RX_Priority_Assert_Offset;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_RX_Priority_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_RX_Priority_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_RX_Priority_Deassert_Jitter;
   qapi_BLE_NonAlignedWord_t                    _802_RX_Priority_Assert_Offset;
   qapi_BLE_NonAlignedWord_t                    _802_RX_Priority_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t                    _802_RX_Priority_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t                    _802_RX_Priority_Deassert_Jitter;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_TX_On_Assert_Offset;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_TX_On_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_TX_On_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t                    Bluetooth_TX_On_Deassert_Jitter;
   qapi_BLE_NonAlignedWord_t                    _802_TX_On_Assert_Offset;
   qapi_BLE_NonAlignedWord_t                    _802_TX_On_Assert_Jitter;
   qapi_BLE_NonAlignedWord_t                    _802_TX_On_Deassert_Offset;
   qapi_BLE_NonAlignedWord_t                    _802_TX_On_Deassert_Jitter;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Signaling_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_MWS_SIGNALING_COMMAND_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_MWS_TRANSPORT_LAYER_COMMAND_COMPLETE_EVENT_SIZE      (sizeof(qapi_BLE_HCI_Set_MWS_Transport_Layer_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_MWS_PATTERN_CONFIGURATION_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_MWS_PATTERN_Configuration_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 4.0 + CSA4).                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_RESERVED_LT_ADDR_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Set_Reserved_LT_ADDR_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_Complete_Event_t;

#define QAPI_BLE_HCI_DELETE_RESERVED_LT_ADDR_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Delete_Reserved_LT_ADDR_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      LT_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Set_Connectionless_Slave_Broadcast_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Sync_Train_Interval;
   qapi_BLE_NonAlignedDWord_t                   Sync_Train_Timeout;
   uint8_t                                      Service_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_SYNCHRONIZATION_TRAIN_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Read_Synchronization_Train_Parameters_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Sync_Train_Interval;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Write_Synchronization_Train_Parameters_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Host Control and Baseband */
   /* - Version 4.1).                                                   */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Secure_Connections_Host_Support;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_SECURE_CONNECTIONS_HOST_SUPPORT_COMMAND_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Read_Secure_Connections_Host_Support_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Write_Secure_Connections_Host_Support_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedWord_t                    Authenticated_Payload_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Read_Authenticated_Payload_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Write_Authenticated_Payload_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Simple_Pairing_Hash_t               C_192;
   qapi_BLE_Simple_Pairing_Randomizer_t         R_192;
   qapi_BLE_Simple_Pairing_Hash_t               C_256;
   qapi_BLE_Simple_Pairing_Randomizer_t         R_256;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_OOB_EXTENDED_DATA_COMMAND_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Read_Local_OOB_Extended_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Extended_Page_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_EXTENDED_PAGE_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE             (sizeof(qapi_BLE_HCI_Read_Extended_Page_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_PAGE_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Write_Extended_Page_Timeout_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Extended_Inquiry_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_EXTENDED_INQUIRY_LENGTH_COMMAND_COMPLETE_EVENT_SIZE           (sizeof(qapi_BLE_HCI_Read_Extended_Inquiry_Length_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_EXTENDED_INQUIRY_LENGTH_COMMAND_COMPLETE_EVENT_SIZE          (sizeof(qapi_BLE_HCI_Write_Extended_Inquiry_Length_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Informational Parameters).*/

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Version_Information_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      HCI_Version;
   qapi_BLE_NonAlignedWord_t                    HCI_Revision;
   uint8_t                                      LMP_Version;
   qapi_BLE_NonAlignedWord_t                    Manufacturer_Name;
   qapi_BLE_NonAlignedWord_t                    LMP_Subversion;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Version_Information_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_VERSION_INFORMATION_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Local_Version_Information_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Features_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_LMP_Features_t                      LMP_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Features_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_FEATURES_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Local_Supported_Features_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Buffer_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    HC_ACL_Data_Packet_Length;
   uint8_t                                      HC_SCO_Data_Packet_Length;
   qapi_BLE_NonAlignedWord_t                    HC_Total_Num_ACL_Data_Packets;
   qapi_BLE_NonAlignedWord_t                    HC_Total_Num_SCO_Data_Packets;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Buffer_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_BUFFER_SIZE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Buffer_Size_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Country_Code_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Country_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Country_Code_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_COUNTRY_CODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Country_Code_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_BD_ADDR_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_BD_ADDR_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_BD_ADDR_COMMAND_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Read_BD_ADDR_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Informational Parameters -*/
   /* Version 1.2).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Commands_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Supported_Commands_t                Supported_Commands;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Commands_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_COMMANDS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Read_Local_Supported_Commands_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Extended_Features_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Page_Number;
   uint8_t                                      Maximum_Page_Number;
   qapi_BLE_LMP_Features_t                      Extended_LMP_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Extended_Features_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_EXTENDED_FEATURES_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Read_Local_Extended_Features_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Informational Parameters -*/
   /* Version 3.0 + HS).                                                */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Data_Block_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Max_ACL_Data_Packet_Length;
   qapi_BLE_NonAlignedWord_t                    Data_Block_Length;
   qapi_BLE_NonAlignedWord_t                    Total_Num_Data_Blocks;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Data_Block_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_DATA_BLOCK_SIZE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Read_Data_Block_Size_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Informational Parameters -*/
   /* Version 4.0 + CSA2).                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Number_of_Supported_Codecs;
   uint8_t                                      Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Read Local */
   /* Supported Codecs Command Complete Event Data Structure based upon */
   /* the Number of total variable data bytes.  The first parameter of  */
   /* this MACRO is the Number of variable bytes.  This MACRO will      */
   /* return the total size of the entire HCI Read Local Supported      */
   /* Codecs Command Complete Event (in bytes).                         */
#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_CODECS_COMMAND_COMPLETE_EVENT_SIZE(_x) (sizeof(qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_t) - sizeof(uint8_t) + ((uint32_t)(_x)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Supported Codec in the HCI Read   */
   /* Local Supported Codecs Command Complete Event Data.  The first    */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_t */
   /* structure.  The Second parameter is the Index of the Supported    */
   /* Codec to Read.                                                    */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_CODECS_COMMAND_COMPLETE_EVENT_READ_SUPPORTED_CODEC(_x, _y)          \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE)))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Supported Codec in the HCI Read   */
   /* Local Supported Codecs Command Complete Event Data.  The first    */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_t */
   /* structure.  The Second parameter is the number of supported codecs*/
   /* (Number_of_Supported_Codecs).                                     */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_CODECS_COMMAND_COMPLETE_EVENT_READ_NUMBER_VENDOR_CODECS(_x, _y)          \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE)))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Supported Codec in the HCI Read   */
   /* Local Supported Codecs Command Complete Event Data.  The first    */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Read_Local_Supported_Codecs_Command_Complete_Event_t */
   /* structure.  The Second parameter is the number of supported codecs*/
   /* (Number_of_Supported_Codecs).  The third parameter is the index of*/
   /* the Vendor Specific Codec to read.                                */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_READ_LOCAL_SUPPORTED_CODECS_COMMAND_COMPLETE_EVENT_READ_VENDOR_SPECIFIC_CODEC(_x, _y, _z)          \
   READ_UNALIGNED_DWORD_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + (((_y)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE)) + QAPI_BLE_NON_ALIGNED_BYTE_SIZE + ((_z) * QAPI_BLE_NON_ALIGNED_DWORD_SIZE)))))

   /* HCI Command Complete Event Definitions (Status Parameters).       */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedWord_t                    Failed_Contact_Counter;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_FAILED_CONTACT_COUNTER_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Failed_Contact_Counter_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_Complete_Event_t;

#define QAPI_BLE_HCI_RESET_FAILED_CONTACT_COUNTER_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Reset_Failed_Contact_Counter_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Get_Link_Quality_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      Link_Quality;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Get_Link_Quality_Command_Complete_Event_t;

#define QAPI_BLE_HCI_GET_LINK_QUALITY_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Get_Link_Quality_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_RSSI_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      RSSI;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_RSSI_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_RSSI_COMMAND_COMPLETE_EVENT_SIZE        (sizeof(qapi_BLE_HCI_Read_RSSI_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Status Parameters -       */
   /* Version 1.2).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_AFH_Channel_Map_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      AFH_Mode;
   qapi_BLE_AFH_Channel_Map_t                   AFH_Channel_Map;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_AFH_Channel_Map_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_AFH_CHANNEL_MAP_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Read_AFH_Channel_Map_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Clock_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedDWord_t                   Clock;
   qapi_BLE_NonAlignedWord_t                    Accuracy;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Clock_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_CLOCK_COMMAND_COMPLETE_EVENT_SIZE       (sizeof(qapi_BLE_HCI_Read_Clock_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Status Parameters -       */
   /* Version 3.0 + HS).                                                */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Encryption_Key_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   uint8_t                                      Key_Size;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Encryption_Key_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_QAPI_BLE_ENCRYPTION_KEY_SIZE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Encryption_Key_Size_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_AMP_Info_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      AMP_Status;
   qapi_BLE_NonAlignedDWord_t                   Total_Bandwidth;
   qapi_BLE_NonAlignedDWord_t                   Max_Guaranteed_Bandwidth;
   qapi_BLE_NonAlignedDWord_t                   Min_Latency;
   qapi_BLE_NonAlignedDWord_t                   Max_PDU_Size;
   uint8_t                                      Controller_Type;
   qapi_BLE_NonAlignedWord_t                    PAL_Capabilities;
   qapi_BLE_NonAlignedWord_t                    Max_AMP_ASSOC_Length;
   qapi_BLE_NonAlignedDWord_t                   Max_Flush_Timeout;
   qapi_BLE_NonAlignedDWord_t                   Best_Effort_Flush_Timeout;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_AMP_Info_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOCAL_AMP_INFO_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Read_Local_AMP_Info_Command_Complete_Event_t))

   /* Note that the AMP_ASSOC_Fragment[] parameter is a variable length */
   /* field that contains zero or more bytes.                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Physical_Link_Handle;
   qapi_BLE_NonAlignedWord_t                    AMP_ASSOC_Remaining_Length;
   uint8_t                                      AMP_ASSOC_Fragment[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Read Local */
   /* AMP ASSOC Command Complete Data Structure based upon the number of*/
   /* individual Assocation Fragment bytes included within the Command  */
   /* Complete Event.  The first parameter to this MACRO is the size (in*/
   /* Bytes) of the Association Fragment Data that is to be part of the */
   /* AMP ASSOC Command Complete Event.                                 */
#define QAPI_BLE_HCI_READ_LOCAL_AMP_ASSOC_COMMAND_COMPLETE_EVENT_SIZE(_x)  (sizeof(qapi_BLE_HCI_Read_Local_AMP_ASSOC_Command_Complete_Event_t) - sizeof(uint8_t) + (uint32_t)(_x))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Physical_Link_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_REMOTE_AMP_ASSOC_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Remote_AMP_ASSOC_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Status Parameters -       */
   /* Version 4.0 + CSA3).                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Num_Transports;
   uint8_t                                      Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complete_Event_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Get MWS    */
   /* Transport Layer Configuration Command Complete Data Structure     */
   /* based upon the number of individual bytes included within the     */
   /* Command Complete Event.  The first parameter to this MACRO is the */
   /* size (in Bytes) of the Data that is to be part of the Get MWS     */
   /* Transport Layer Configuration Command Complete Event.             */
#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_COMPLETE_EVENT_SIZE(_x)   (sizeof(qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complete_Event_t) - sizeof(uint8_t) + (uint32_t)(_x))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a Transport_Layer in the HCI Get MWS Transport*/
   /* Layer Configuration Command Complete Data.  The first parameter is*/
   /* a pointer to a Data Buffer that is an                             */
   /* qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complet*/
   /* structure.  The Second parameter is the Index of the Transport    */
   /* Layer to Read.                                                    */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_COMPLETE_EVENT_READ_TRANSPORT_LAYER(_x, _y)          \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE)))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a Number of Baud Rates member in the HCI Get  */
   /* MWS Transport Layer Configuration Command Complete Data.  The     */
   /* first parameter is a pointer to a Data Buffer that is an          */
   /* qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complet*/
   /* structure.  The Second parameter is the total number of transports*/
   /* (Num_Transports) in the event.  The third parameter is the Index  */
   /* of the Number of Baud Rates member to read.                       */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_COMPLETE_EVENT_READ_NUMBER_BAUD_RATES(_x, _y, _z)          \
   READ_UNALIGNED_BYTE_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*QAPI_BLE_NON_ALIGNED_BYTE_SIZE) + ((_z)*QAPI_BLE_NON_ALIGNED_BYTE_SIZE))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a To_MWS_Baud_Rate member in the HCI Get MWS  */
   /* Transport Layer Configuration Command Complete Data.  The first   */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complet*/
   /* structure.  The Second parameter is the total number of transports*/
   /* (Num_Transports) in the event.  The third parameter is the Index  */
   /* of the To_MWS_Baud_Rate member to read.                           */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_COMPLETE_EVENT_READ_TO_MWS_BAUD_RATE(_x, _y, _z)          \
   READ_UNALIGNED_DWORD_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_x)->Variable_Data)) + ((_y)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE + QAPI_BLE_NON_ALIGNED_BYTE_SIZE)) + ((_z)*QAPI_BLE_NON_ALIGNED_DWORD_SIZE))))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a From_MWS_Baud_Rate member in the HCI Get MWS*/
   /* Transport Layer Configuration Command Complete Data.  The first   */
   /* parameter is a pointer to a Data Buffer that is an                */
   /* qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration_Command_Complet*/
   /* structure.  The Second parameter is the total number of transports*/
   /* (Num_Transports) in the event.  The third parameter is the total  */
   /* number of baud rates (Sum(Num_Baud_Rates)).  The fourth parameter */
   /* is the Index of the From_MWS_Baud_Rate member to read.            */
   /* * NOTE * No Check of any of the input data is performed !         */
#define QAPI_BLE_HCI_GET_MWS_TRANSPORT_LAYER_CONFIGURATION_COMMAND_COMPLETE_EVENT_READ_FROM_MWS_BAUD_RATE(_a, _b, _c, _d)          \
   READ_UNALIGNED_DWORD_LITTLE_ENDIAN(((uint8_t *)(((uint8_t *)((_a)->Variable_Data)) + ((_b)*(QAPI_BLE_NON_ALIGNED_BYTE_SIZE + QAPI_BLE_NON_ALIGNED_BYTE_SIZE)) + (((_c)+(_d))*QAPI_BLE_NON_ALIGNED_DWORD_SIZE))))

   /* HCI Command Complete Event Definitions (Status Parameters -       */
   /* Version 4.0 + CSA4).                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_Complete_Event_t;

#define QAPI_BLE_HCI_SET_TRIGGERED_CLOCK_CAPTURE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Set_Triggered_Clock_Capture_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Testing Commands).        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Loopback_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Loopback_Mode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Loopback_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_READ_LOOPBACK_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Loopback_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Loopback_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Loopback_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_LOOPBACK_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Loopback_Mode_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_ENABLE_DEVICE_UNDER_TEST_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Enable_Device_Under_Test_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Testing Commands - Version*/
   /* 2.1 + EDR).                                                       */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SIMPLE_PAIRING_DEBUG_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Simple_Pairing_Debug_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Testing Commands - Version*/
   /* 3.0 + HS).                                                        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_Complete_Event_t;

#define QAPI_BLE_HCI_ENABLE_AMP_RECEIVER_REPORTS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Enable_AMP_Receiver_Reports_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Test_End_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Test_End_Command_Complete_Event_t;

#define QAPI_BLE_HCI_AMP_TEST_END_COMMAND_COMPLETE_EVENT_SIZE     (sizeof(qapi_BLE_HCI_AMP_Test_End_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_AMP_Test_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_AMP_Test_Command_Complete_Event_t;

#define QAPI_BLE_HCI_AMP_TEST_COMMAND_COMPLETE_EVENT_SIZE         (sizeof(qapi_BLE_HCI_AMP_Test_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (Testing Commands - Version*/
   /* 4.1).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_Complete_Event_t;

#define QAPI_BLE_HCI_WRITE_SECURE_CONNECTIONS_TEST_MODE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_Write_Secure_Connections_Test_Mode_Command_Complete_Event_t))

   /* HCI Command Complete Event Definitions (LE Controller Commands -  */
   /* Version 4.0 + LE).                                                */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Event_Mask_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Event_Mask_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_EVENT_MASK_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Event_Mask_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Buffer_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    HC_LE_ACL_Data_Packet_Length;
   uint8_t                                      HC_Total_Num_LE_ACL_Data_Packets;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Buffer_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_BUFFER_SIZE_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Read_Buffer_Size_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_LE_Features_t                       LE_Features;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_SUPPORTED_FEATURES_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_Local_Supported_Features_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Random_Address_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Random_Address_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_RANDOM_ADDRESS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Random_Address_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Parameters_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Transmit_Power_Level;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_ADVERTISING_CHANNEL_TX_POWER_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_DATA_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_RESPONSE_DATA_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Set_Scan_Response_Data_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISE_ENABLE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Advertise_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Set_Scan_Parameters_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Scan_Enable_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Scan_Enable_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_SET_SCAN_ENABLE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Scan_Enable_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_CREATE_CONNECTION_CANCEL_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Create_Connection_Cancel_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_White_List_Size_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      White_List_Size;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_White_List_Size_Command_Complete_Event_t;

#define QAPI_BLE_HCI_LE_READ_WHITE_LIST_SIZE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_White_List_Size_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_White_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_White_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_CLEAR_WHITE_LIST_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Clear_White_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Add_Device_To_White_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_White_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_HOST_CHANNEL_CLASSIFICATION_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Host_Channel_Classification_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Channel_Map_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_LE_Channel_Map_t                    Channel_Map;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Channel_Map_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_CHANNEL_MAP_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Read_Channel_Map_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Encrypt_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Encrypted_Data_t                    Encrypted_Data;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Encrypt_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ENCRYPT_COMMAND_COMPLETE_EVENT_SIZE       (sizeof(qapi_BLE_HCI_LE_Encrypt_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Rand_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_Random_Number_t                     Random_Number;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Rand_Command_Complete_t;

#define QAPI_BLE_HCI_LE_RAND_COMMAND_COMPLETE_EVENT_SIZE          (sizeof(qapi_BLE_HCI_LE_Rand_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_Complete_t;

#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_Complete_t;

#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Supported_States_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_LE_States_t                         LE_States;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Supported_States_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_SUPPORTED_STATES_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Supported_States_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Receiver_Test_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Receiver_Test_Command_Complete_t;

#define QAPI_BLE_HCI_LE_RECEIVER_TEST_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Receiver_Test_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Transmitter_Test_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Transmitter_Test_Command_Complete_t;

#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Transmitter_Test_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Test_End_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Number_Of_Packets;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Test_End_Command_Complete_t;

#define QAPI_BLE_HCI_LE_TEST_END_COMMAND_COMPLETE_EVENT_SIZE      (sizeof(qapi_BLE_HCI_LE_Test_End_Command_Complete_t))

   /* HCI Command Complete Event Definitions (LE Controller Commands -  */
   /* Version 4.1).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply_Command_Complete_t))

   /* HCI Command Complete Event Definitions (LE Controller Commands -  */
   /* Version 4.2).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Data_Length_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Data_Length_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_DATA_LENGTH_COMMAND_COMPLETE_EVENT_SIZE      (sizeof(qapi_BLE_HCI_LE_Set_Data_Length_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    SuggestedMaxTxOctets;
   qapi_BLE_NonAlignedWord_t                    SuggestedMaxTxTime;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_Complete_t;

#define QAPI_BLE_HCI_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_LE_Add_Device_To_Resolving_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_Resolving_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_Resolving_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_CLEAR_RESOLVING_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Clear_Resolving_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   uint8_t                                      Resolving_List_Size;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_RESOLVING_LIST_SIZE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Resolving_List_Size_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           Peer_Resolvable_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_PEER_RESOLVABLE_ADDRESS_COMMAND_COMPLETE_EVENT_SIZE    (sizeof(qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_BD_ADDR_t                           Local_Resolvable_Address;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_RESOLVABLE_ADDRESS_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_Local_Resolvable_Address_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_COMPLETE_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Set_Address_Resolution_Enable_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_COMMAND_COMPLETE_EVENT_SIZE (sizeof(qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   uint8_t                                      Status;
   qapi_BLE_NonAlignedWord_t                    SupportedMaxTxOctets;
   qapi_BLE_NonAlignedWord_t                    SupportedMaxTxTime;
   qapi_BLE_NonAlignedWord_t                    SupportedMaxRxOctets;
   qapi_BLE_NonAlignedWord_t                    SupportedMaxRxTime;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_MAXIMUM_DATA_LENGTH_COMMAND_COMPLETE_EVENT_SIZE        (sizeof(qapi_BLE_HCI_LE_Read_Maximum_Data_Length_Command_Complete_t))

   /* HCI Command Complete Event Definitions (LE Controller Commands -  */
   /* Version 5.0).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_PHY_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedWord_t                    Connection_Handle;
   qapi_BLE_NonAlignedByte_t                    TX_PHY;
   qapi_BLE_NonAlignedByte_t                    RX_PHY;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_PHY_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_PHY_COMMAND_COMPLETE_EVENT_SIZE      (sizeof(qapi_BLE_HCI_LE_Read_PHY_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Default_PHY_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Default_PHY_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_DEFAULT_PHY_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Default_PHY_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ENHANCED_RECEIVER_TEST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Enhanced_Receiver_Test_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedSByte_t                   Selected_Tx_Power;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Advertising_Data_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedWord_t                    Maximum_Advertising_Data_Length;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedByte_t                    Num_Supported_Advertising_Sets;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Advertising_Set_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Advertising_Set_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOVE_ADVERTISING_SET_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Advertising_Set_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_Advertising_Sets_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_Advertising_Sets_Command_Complete_t;

#define QAPI_BLE_HCI_LE_CLEAR_ADVERTISING_SETS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Clear_Advertising_Sets_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_ENABLE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_PARAMETERS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_EXTENDED_SCAN_ENABLE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Extended_Scan_Enable_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Cancel_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Cancel_Command_Complete_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Cancel_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Terminate_Sync_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Terminate_Sync_Command_Complete_t;

#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Terminate_Sync_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Clear_Periodic_Advertiser_List_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Clear_Periodic_Advertiser_List_Command_Complete_t;

#define QAPI_BLE_HCI_LE_CLEAR_PERIODIC_ADVERTISER_LIST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Clear_Periodic_Advertiser_List_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Periodic_Advertiser_List_Size_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedByte_t                    Periodic_Advertiser_List_Size;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Periodic_Advertiser_List_Size_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_PERIODIC_ADVERTISER_LIST_SIZE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Periodic_Advertiser_List_Size_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Transmit_Power_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedSByte_t                   Min_TX_Power;
   qapi_BLE_NonAlignedSByte_t                   Max_TX_Power;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Transmit_Power_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_TRANSMIT_POWER_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Transmit_Power_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_RF_Path_Compensation_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedSWord_t                   RF_TX_Path_Compensation_Value;
   qapi_BLE_NonAlignedSWord_t                   RF_RX_Path_Compensation_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_RF_Path_Compensation_Command_Complete_t;

#define QAPI_BLE_HCI_LE_READ_RF_PATH_COMPENSATION_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_RF_Path_Compensation_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_Complete_t;

#define QAPI_BLE_HCI_LE_WRITE_RF_PATH_COMPENSATION_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Write_RF_Path_Compensation_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PRIVACY_MODE_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Privacy_Mode_Command_Complete_t))

   /* HCI Command Complete Event Definitions (LE Controller Commands -  */
   /* Version 5.4).                                                     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedByte_t                    Advertising_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedByte_t                    Advertising_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Subevent_Data_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedWord_t                    Sync_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Advertising_Response_Data_Command_Complete_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_Complete_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedWord_t                    Sync_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_Complete_t;

#define QAPI_BLE_HCI_LE_SET_PERIODIC_SYNC_SUBEVENT_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Set_Periodic_Sync_Subevent_Command_Complete_t))

   /* HCI Command Status Event Definitions (Link Control).              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Inquiry_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Inquiry_Command_Status_Event_t;

#define QAPI_BLE_HCI_INQUIRY_COMMAND_STATUS_EVENT_SIZE            (sizeof(qapi_BLE_HCI_Inquiry_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_CREATE_CONNECTION_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Create_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Command_Status_Event_t;

#define QAPI_BLE_HCI_DISCONNECT_COMMAND_STATUS_EVENT_SIZE         (sizeof(qapi_BLE_HCI_Disconnect_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Add_SCO_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Add_SCO_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_ADD_SCO_CONNECTION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Add_SCO_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Connection_Request_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Connection_Request_Command_Status_Event_t;

#define QAPI_BLE_HCI_ACCEPT_CONNECTION_REQUEST_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Accept_Connection_Request_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reject_Connection_Request_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reject_Connection_Request_Command_Status_Event_t;

#define QAPI_BLE_HCI_REJECT_CONNECTION_REQUEST_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Reject_Connection_Request_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Connection_Packet_Type_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Connection_Packet_Type_Command_Status_Event_t;

#define QAPI_BLE_HCI_CHANGE_CONNECTION_PACKET_TYPE_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Change_Connection_Packet_Type_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Authentication_Requested_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Authentication_Requested_Command_Status_Event_t;

#define QAPI_BLE_HCI_AUTHENTICATION_REQUESTED_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Authentication_Requested_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Set_Connection_Encryption_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Set_Connection_Encryption_Command_Status_Event_t;

#define QAPI_BLE_HCI_SET_CONNECTION_ENCRYPTION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Set_Connection_Encryption_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Change_Connection_Link_Key_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Change_Connection_Link_Key_Command_Status_Event_t;

#define QAPI_BLE_HCI_CHANGE_CONNECTION_LINK_KEY_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Change_Connection_Link_Key_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Master_Link_Key_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Master_Link_Key_Command_Status_Event_t;

#define QAPI_BLE_HCI_MASTER_LINK_KEY_COMMAND_STATUS_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Master_Link_Key_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Remote_Name_Request_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Remote_Name_Request_Command_Status_Event_t;

#define QAPI_BLE_HCI_REMOTE_NAME_REQUEST_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Remote_Name_Request_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Supported_Features_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Supported_Features_Command_Status_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_SUPPORTED_FEATURES_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Supported_Features_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Version_Information_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Version_Information_Command_Status_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_VERSION_INFORMATION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Version_Information_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Clock_Offset_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Clock_Offset_Command_Status_Event_t;

#define QAPI_BLE_HCI_READ_CLOCK_OFFSET_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Read_Clock_Offset_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Control - Version 1.2).*/

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Read_Remote_Extended_Features_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Read_Remote_Extended_Features_Command_Status_Event_t;

#define QAPI_BLE_HCI_READ_REMOTE_EXTENDED_FEATURES_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Extended_Features_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Setup_Synchronous_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Setup_Synchronous_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_SETUP_SYNCHRONOUS_CONNECTION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Setup_Synchronous_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Synchronous_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Synchronous_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_ACCEPT_SYNCHRONOUS_CONNECTION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Accept_Synchronous_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Reject_Synchronous_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Reject_Synchronous_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_REJECT_SYNCHRONOUS_CONNECTION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Reject_Synchronous_Connection_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Control - Version 3.0 +*/
   /* HS).                                                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Physical_Link_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Physical_Link_Command_Status_Event_t;

#define QAPI_BLE_HCI_CREATE_PHYSICAL_LINK_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Create_Physical_Link_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Physical_Link_Request_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Physical_Link_Request_Command_Status_Event_t;

#define QAPI_BLE_HCI_ACCEPT_PHYSICAL_LINK_REQUEST_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Accept_Physical_Link_Request_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Physical_Link_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Physical_Link_Command_Status_Event_t;

#define QAPI_BLE_HCI_DISCONNECT_PHYSICAL_LINK_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Disconnect_Physical_Link_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Create_Logical_Link_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Create_Logical_Link_Command_Status_Event_t;

#define QAPI_BLE_HCI_CREATE_LOGICAL_LINK_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Create_Logical_Link_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Accept_Logical_Link_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Accept_Logical_Link_Command_Status_Event_t;

#define QAPI_BLE_HCI_ACCEPT_LOGICAL_LINK_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Accept_Logical_Link_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Disconnect_Logical_Link_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Disconnect_Logical_Link_Command_Status_Event_t;

#define QAPI_BLE_HCI_DISCONNECT_LOGICAL_LINK_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_Disconnect_Logical_Link_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Spec_Modify_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Spec_Modify_Command_Status_Event_t;

#define QAPI_BLE_HCI_FLOW_SPEC_MODIFY_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Flow_Spec_Modify_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Control - Version 4.0 +*/
   /* CSA2).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Enhanced_Setup_Synchronous_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_Status_Event_t;

#define QAPI_BLE_HCI_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_Enhanced_Accept_Synchronous_Connection_Request_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Control - Version 4.0 +*/
   /* CSA4).                                                            */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Truncated_Page_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Truncated_Page_Command_Status_Event_t;

#define QAPI_BLE_HCI_TRUNCATED_PAGE_COMMAND_STATUS_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Truncated_Page_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Start_Synchronization_Train_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Start_Synchronization_Train_Command_Status_Event_t;

#define QAPI_BLE_HCI_START_SYNCHRONIZATION_TRAIN_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Start_Synchronization_Train_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Receive_Synchronization_Train_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Receive_Synchronization_Train_Command_Status_Event_t;

#define QAPI_BLE_HCI_RECEIVE_SYNCHRONIZATION_TRAIN_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Receive_Synchronization_Train_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Policy).               */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Hold_Mode_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Hold_Mode_Command_Status_Event_t;

#define QAPI_BLE_HCI_HOLD_MODE_COMMAND_STATUS_EVENT_SIZE          (sizeof(qapi_BLE_HCI_Hold_Mode_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Sniff_Mode_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Sniff_Mode_Command_Status_Event_t;

#define QAPI_BLE_HCI_SNIFF_MODE_COMMAND_STATUS_EVENT_SIZE         (sizeof(qapi_BLE_HCI_Sniff_Mode_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Sniff_Mode_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Sniff_Mode_Command_Status_Event_t;

#define QAPI_BLE_HCI_EXIT_SNIFF_MODE_COMMAND_STATUS_EVENT_SIZE    (sizeof(qapi_BLE_HCI_Exit_Sniff_Mode_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Park_Mode_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Park_Mode_Command_Status_Event_t;

#define QAPI_BLE_HCI_PARK_MODE_COMMAND_STATUS_EVENT_SIZE          (sizeof(qapi_BLE_HCI_Park_Mode_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Exit_Park_Mode_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Exit_Park_Mode_Command_Status_Event_t;

#define QAPI_BLE_HCI_EXIT_PARK_MODE_COMMAND_STATUS_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Exit_Park_Mode_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_QoS_Setup_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_QoS_Setup_Command_Status_Event_t;

#define QAPI_BLE_HCI_QOS_SETUP_COMMAND_STATUS_EVENT_SIZE          (sizeof(qapi_BLE_HCI_QoS_Setup_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Switch_Role_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Switch_Role_Command_Status_Event_t;

#define QAPI_BLE_HCI_SWITCH_ROLE_COMMAND_STATUS_EVENT_SIZE        (sizeof(qapi_BLE_HCI_Switch_Role_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Link Policy - Version 1.2). */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Flow_Specification_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Flow_Specification_Command_Status_Event_t;

#define QAPI_BLE_HCI_FLOW_SPECIFICATION_COMMAND_STATUS_EVENT_SIZE (sizeof(qapi_BLE_HCI_Flow_Specification_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Host Control and Baseband). */

   /* HCI Command Status Event Definitions (Host Controller and Baseband*/
   /* - Version 2.1 + EDR).                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_Enhanced_Flush_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_Enhanced_Flush_Command_Status_Event_t;

#define QAPI_BLE_HCI_ENHANCED_FLUSH_COMMAND_STATUS_EVENT_SIZE     (sizeof(qapi_BLE_HCI_Enhanced_Flush_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (Informational Parameters).  */

   /* HCI Command Status Event Definitions (Status Parameters).         */

   /* HCI Command Status Event Definitions (Testing Commands).          */

   /* HCI Command Status Event Definitions (LE Controller Commands -    */
   /* 4.0 + LE).                                                        */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Create_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Create_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_CREATE_CONNECTION_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Create_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Connection_Update_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Connection_Update_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_CONNECTION_UPDATE_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Connection_Update_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_READ_REMOTE_USED_FEATURES_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Read_Remote_Used_Features_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Start_Encryption_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Start_Encryption_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_START_ENCRYPTION_COMMAND_STATUS_EVENT_SIZE   (sizeof(qapi_BLE_HCI_LE_Start_Encryption_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (LE Controller Commands -    */
   /* 4.2).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Generate_DHKey_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Generate_DHKey_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_GENERATE_DHKEY_COMMAND_STATUS_EVENT_SIZE         (sizeof(qapi_BLE_HCI_LE_Generate_DHKey_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (LE Controller Commands -    */
   /* 5.0).                                                             */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Set_PHY_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Set_PHY_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_SET_PHY_COMMAND_STATUS_EVENT_SIZE         (sizeof(qapi_BLE_HCI_LE_Set_PHY_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Create_Connection_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Create_Connection_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Extended_Create_Connection_Command_Status_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_PERIODIC_CREATE_SYNC_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Command_Status_Event_t))

   /* HCI Command Status Event Definitions (LE Controller Commands -    */
   /* Version 5.4).                                                     */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_Status_Event_s
{
   qapi_BLE_HCI_Command_Status_Event_t HCI_Command_Status_Event;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_Status_Event_t;

#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_V2_COMMAND_STATUS_EVENT_SIZE  (sizeof(qapi_BLE_HCI_LE_Extended_Create_Connection_V2_Command_Status_Event_t))

   /* The following type declaration represents the structure of the an */
   /* HCI ACL Data Packet.  The only detail to note is that the ACL Data*/
   /* field is an array of uint8_t's, and NOT a Pointer to an array of  */
   /* uint8_t's.  This is very important, because this mechanism will   */
   /* allow an arbitrary memory buffer to be typecast to this structure */
   /* and all elements will be accessible in the same memory block (i.e.*/
   /* NO other pointer operation is required).  The side effect of this */
   /* is that when the memory for a Raw ACL Data Packet is to be        */
   /* allocated, the allocated size is required will be                 */
   /* (sizeof(qapi_BLE_HCI_ACL_Data_t)-1) + length of the Packet Data.  */
   /* After this is completed, the data elements in the Packet Data     */
   /* array can be accessed by simply Array Logic, aiding code          */
   /* readability.  It might appear confusing to the user because array */
   /* elements greater than zero will be indexed, however, as long as   */
   /* the programmer is aware of this design decision, the code should  */
   /* be much more simple to read.  MACRO's and Definitions will be     */
   /* provided following this structure definition to alleviate the     */
   /* programmer from having to remember the above formula when         */
   /* allocating memory of the correct size.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_ACL_Data_s
{
   qapi_BLE_NonAlignedWord_t Connection_Handle_And_Flags;
   qapi_BLE_NonAlignedWord_t Data_Total_Length;
   uint8_t                   ACL_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_ACL_Data_t;

   /* The following Constant represents the actual size of the HCI ACL  */
   /* Data Packet Header Information.  This Constant is to be used      */
   /* instead of simply using sizeof(qapi_BLE_HCI_ACL_Data_t) to get the*/
   /* size.  The reason for this was explained above, and is primarily  */
   /* to aid in code readability and efficiency.                        */
#define QAPI_BLE_HCI_ACL_DATA_HEADER_SIZE                         (sizeof(qapi_BLE_HCI_ACL_Data_t)-sizeof(uint8_t))

   /* The following MACRO is provided to allow the programmer a very    */
   /* simple means of quickly determining the number of Data Bytes that */
   /* will be required to hold a HCI ACL Data Information Header and the*/
   /* Raw HCI ACL Data (of the specified length).  See notes and        */
   /* discussion above for the reason for this MACRO definition.        */
#define QAPI_BLE_HCI_CALCULATE_ACL_DATA_SIZE(_x)                  (QAPI_BLE_HCI_ACL_DATA_HEADER_SIZE+(uint32_t)(_x))

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Mask's to apply to the Bluetooth HCI ACL Packet Flags.  These     */
   /* Masks are applied to the Connection_Handle_And_Flags member of the*/
   /* HCI ACL Data Packet member.  After the correct Mask is applied,   */
   /* the Data can then be tested and/or set with the bit definition    */
   /* values that follow.                                               */
#define QAPI_BLE_HCI_ACL_FLAGS_CONNECTION_HANDLE_MASK                            0x0FFF
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_MASK                              0x3000
#define QAPI_BLE_HCI_ACL_FLAGS_BROADCAST_MASK                                    0xC000

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_MASK*/
   /* Bit Mask) that specify a specific Bluetooth HCI ACL Packet        */
   /* Boundary Setting.                                                 */
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET_NON_FLUSHABLE        0x0000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_CONTINUE_PACKET                   0x1000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET                      0x2000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET_AUTO_FLUSHABLE       0x2000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_COMPLETE_L2CAP_PDU_AUTO_FLUSHABLE 0x3000

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the QAPI_BLE_HCI_ACL_FLAGS_BROADCAST_MASK Bit  */
   /* Mask) that specify a specific Bluetooth HCI ACL Packet Broadcast  */
   /* Setting.                                                          */
   /* * NOTE * These definitions are for Packets from Host to Host      */
   /*          Controller.                                              */
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_NO_BROADCAST                     0x0000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_BROADCAST                 0x4000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_SLAVE_BROADCAST           0x4000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PICONET_BROADCAST                0x8000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PARKED_SLAVE_BROADCAST           0x8000

   /* Bluetooth Version 1.2 HCI ACL Packet Broadcast Settings.          */
   /* * NOTE * These definitions are for Packets from Host to Host      */
   /*          Controller.                                              */
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_NO_BROADCAST                     0x0000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_SLAVE_BROADCAST           0x4000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PARKED_SLAVE_BROADCAST           0x8000

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the QAPI_BLE_HCI_ACL_FLAGS_BROADCAST_MASK Bit  */
   /* Mask) that specify a specific Bluetooth HCI ACL Packet Broadcast  */
   /* Setting.                                                          */
   /* * NOTE * These definitions are for Packets from Host Controller to*/
   /*          Host.                                                    */
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_POINT_TO_POINT                   0x0000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_SLAVE                     0x4000
#define QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PARKED_SLAVE                     0x8000

   /* The following type declaration represents the structure of the an */
   /* HCI SCO Data Packet.  The only detail to note is that the SCO Data*/
   /* field is an array of uint8_t's, and NOT a Pointer to an array of  */
   /* uint8_t's.  This is very important, because this mechanism will   */
   /* allow an arbitrary memory buffer to be typecast to this structure */
   /* and all elements will be accessible in the same memory block (i.e.*/
   /* NO other pointer operation is required).  The side effect of this */
   /* is that when the memory for a Raw SCO Data Packet is to be        */
   /* allocated, the allocated size is required will be                 */
   /* (sizeof(qapi_BLE_HCI_SCO_Data_t)-1) + length of the Packet Data.  */
   /* After this is completed, the data elements in the Packet Data     */
   /* array can be accessed by simply Array Logic, aiding code          */
   /* readability.  It might appear confusing to the user because array */
   /* elements greater than zero will be indexed, however, as long as   */
   /* the programmer is aware of this design decision, the code should  */
   /* be much more simple to read.  MACRO's and Definitions will be     */
   /* provided following this structure definition to alleviate the     */
   /* programmer from having to remember the above formula when         */
   /* allocating memory of the correct size.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_SCO_Data_s
{
   qapi_BLE_NonAlignedWord_t Connection_Handle_And_Flags;
   uint8_t                   Data_Total_Length;
   uint8_t                   SCO_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_SCO_Data_t;

   /* The following Constant represents the actual size of the HCI SCO  */
   /* Data Packet Header Information.  This Constant is to be used      */
   /* instead of simply using sizeof(qapi_BLE_HCI_SCO_Data_t) to get the*/
   /* size.  The reason for this was explained above, and is primarily  */
   /* to aid in code readability and efficiency.                        */
#define QAPI_BLE_HCI_SCO_DATA_HEADER_SIZE                         (sizeof(qapi_BLE_HCI_SCO_Data_t)-sizeof(uint8_t))

   /* The following MACRO is provided to allow the programmer a very    */
   /* simple means of quickly determining the number of Data Bytes that */
   /* will be required to hold a HCI SCO Data Information Header and the*/
   /* Raw HCI SCO Data (of the specified length).  See notes and        */
   /* discussion above for the reason for this MACRO definition.        */
#define QAPI_BLE_HCI_CALCULATE_SCO_DATA_SIZE(_x)                  (QAPI_BLE_HCI_SCO_DATA_HEADER_SIZE+(uint32_t)(_x))

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Mask's to apply to the Bluetooth HCI SCO Packet Flags.  These     */
   /* Masks are applied to the Connection_Handle_And_Flags member of the*/
   /* HCI SCO Data Packet member.                                       */
#define QAPI_BLE_HCI_SCO_FLAGS_CONNECTION_HANDLE_MASK                            0x0FFF
#define QAPI_BLE_HCI_SCO_FLAGS_PACKET_STATUS_MASK_MASK                           0x3000

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the HCI_SCO_FLAGS_PACKET_STATUS_MASK Bit Mask) */
   /* that specify a specific Bluetooth HCI SCO Packet Status Flags     */
   /* Value.                                                            */
   /* * NOTE * These definitions are for Packets from Host Controller   */
   /*          to Host.                                                 */
#define QAPI_BLE_HCI_SCO_FLAGS_PACKET_STATUS_MASK_CORRECTLY_RECEIVED_DATA        0x0000
#define QAPI_BLE_HCI_SCO_FLAGS_PACKET_STATUS_MASK_POSSIBLY_INVALID_DATA          0x1000
#define QAPI_BLE_HCI_SCO_FLAGS_PACKET_STATUS_MASK_NO_DATA_RECEIVED               0x2000
#define QAPI_BLE_HCI_SCO_FLAGS_PACKET_STATUS_MASK_DATA_PARTIALLY_LOST            0x3000

   /* The following type declaration represents the structure of the an */
   /* HCI eSCO Data Packet.  The only detail to note is that the eSCO   */
   /* Data field is an array of uint8_t's, and NOT a Pointer to an array*/
   /* of uint8_t's.  This is very important, because this mechanism will*/
   /* allow an arbitrary memory buffer to be typecast to this structure */
   /* and all elements will be accessible in the same memory block (i.e.*/
   /* NO other pointer operation is required).  The side effect of this */
   /* is that when the memory for a Raw eSCO Data Packet is to be       */
   /* allocated, the allocated size is required will be                 */
   /* (sizeof(qapi_BLE_HCI_eSCO_Data_t)-1) + length of the Packet Data. */
   /* After this is completed, the data elements in the Packet Data     */
   /* array can be accessed by simply Array Logic, aiding code          */
   /* readability.  It might appear confusing to the user because array */
   /* elements greater than zero will be indexed, however, as long as   */
   /* the programmer is aware of this design decision, the code should  */
   /* be much more simple to read.  MACRO's and Definitions will be     */
   /* provided following this structure definition to alleviate the     */
   /* programmer from having to remember the above formula when         */
   /* allocating memory of the correct size.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_eSCO_Data_s
{
   qapi_BLE_NonAlignedWord_t Connection_Handle_And_Flags;
   uint8_t                   Data_Total_Length;
   uint8_t                   eSCO_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_eSCO_Data_t;

   /* The following Constant represents the actual size of the HCI eSCO */
   /* Data Packet Header Information.  This Constant is to be used      */
   /* instead of simply using sizeof(qapi_BLE_HCI_eSCO_Data_t) to get   */
   /* the size.  The reason for this was explained above, and is        */
   /* primarily to aid in code readability and efficiency.              */
#define QAPI_BLE_HCI_ESCO_DATA_HEADER_SIZE                        (sizeof(HCI_ESCO_Data_t)-sizeof(uint8_t))

   /* The following MACRO is provided to allow the programmer a very    */
   /* simple means of quickly determining the number of Data Bytes that */
   /* will be required to hold a HCI eSCO Data Information Header and   */
   /* the Raw HCI eSCO Data (of the specified length).  See notes and   */
   /* discussion above for the reason for this MACRO definition.        */
#define QAPI_BLE_HCI_CALCULATE_ESCO_DATA_SIZE(_x)                 (QAPI_BLE_HCI_ESCO_DATA_HEADER_SIZE+(uint32_t)(_x))

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Mask's to apply to the Bluetooth HCI eSCO Packet Flags.  These    */
   /* Masks are applied to the Connection_Handle_And_Flags member of the*/
   /* HCI eSCO Data Packet member.                                      */
#define QAPI_BLE_HCI_ESCO_FLAGS_CONNECTION_HANDLE_MASK                            0x0FFF

   /* Generic HCI Type Definitions/Constants.                           */

   /* The following MACRO is a utility MACRO that assigns the HCI       */
   /* General/Unlimited Inquiry Access Code (GIAC) to a specified       */
   /* qapi_BLE_LAP_t variable.  This MACRO accepts one parameter which  */
   /* is the qapi_BLE_LAP_t variable that is to receive the GIAC LAP    */
   /* Constant value.                                                   */
#define QAPI_BLE_HCI_ASSIGN_GIAC_LAP(_x)   QAPI_BLE_ASSIGN_LAP((_x), 0x9E, 0x8B, 0x33)

   /* The following MACRO is a utility MACRO that assigns the HCI       */
   /* Limited Dedicated Inquiry Access Code (LIAC) to a specified       */
   /* qapi_BLE_LAP_t variable.  This MACRO accepts one parameter which  */
   /* is the qapi_BLE_LAP_t variable that is to receive the LIAC LAP    */
   /* Constant value.                                                   */
#define QAPI_BLE_HCI_ASSIGN_LIAC_LAP(_x)   QAPI_BLE_ASSIGN_LAP((_x), 0x9E, 0x8B, 0x00)

   /* The following Constants represent Bit Number Constants that are   */
   /* to be used with the EVENT_MASK MACRO's (Set/Reset/Test).  These   */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth Event in the Event Mask.        */
#define QAPI_BLE_HCI_EVENT_MASK_INQUIRY_COMPLETE_BIT_NUMBER                         0x00
#define QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_BIT_NUMBER                           0x01
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER                      0x02
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTION_REQUEST_BIT_NUMBER                       0x03
#define QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_COMPLETE_BIT_NUMBER                   0x04
#define QAPI_BLE_HCI_EVENT_MASK_AUTHENTICAITION_COMPLETE_BIT_NUMBER                 0x05
#define QAPI_BLE_HCI_EVENT_MASK_REMOTE_NAME_REQUEST_COMPLETE_BIT_NUMBER             0x06
#define QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_CHANGE_BIT_NUMBER                        0x07
#define QAPI_BLE_HCI_EVENT_MASK_CHANGE_CONNECTION_LINK_KEY_COMPLETE_BIT_NUMBER      0x08
#define QAPI_BLE_HCI_EVENT_MASK_MASTER_LINK_KEY_COMPLETE_BIT_NUMBER                 0x09
#define QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_BIT_NUMBER  0x0A
#define QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_VERSION_INFORMATION_COMPLETE_BIT_NUMBER 0x0B
#define QAPI_BLE_HCI_EVENT_MASK_QOS_SETUP_COMPLETE_BIT_NUMBER                       0x0C
#define QAPI_BLE_HCI_EVENT_MASK_COMMAND_COMPLETE_BIT_NUMBER                         0x0D
#define QAPI_BLE_HCI_EVENT_MASK_STATUS_COMMAND_BIT_NUMBER                           0x0E
#define QAPI_BLE_HCI_EVENT_MASK_HARDWARE_ERROR_BIT_NUMBER                           0x0F
#define QAPI_BLE_HCI_EVENT_MASK_FLUSH_OCCURRED_BIT_NUMBER                           0x10
#define QAPI_BLE_HCI_EVENT_MASK_ROLE_CHANGE_BIT_NUMBER                              0x11
#define QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_PACKETS_BIT_NUMBER              0x12
#define QAPI_BLE_HCI_EVENT_MASK_MODE_CHANGE_BIT_NUMBER                              0x13
#define QAPI_BLE_HCI_EVENT_MASK_RETURN_LINK_KEYS_BIT_NUMBER                         0x14
#define QAPI_BLE_HCI_EVENT_MASK_PIN_CODE_REQUEST_BIT_NUMBER                         0x15
#define QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_REQUEST_BIT_NUMBER                         0x16
#define QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_NOTIFICATION_BIT_NUMBER                    0x17
#define QAPI_BLE_HCI_EVENT_MASK_LOOPBACK_COMMAND_BIT_NUMBER                         0x18
#define QAPI_BLE_HCI_EVENT_MASK_DATA_BUFFER_OVERFLOW_BIT_NUMBER                     0x19
#define QAPI_BLE_HCI_EVENT_MASK_MAX_SLOTS_CHANGE_BIT_NUMBER                         0x1A
#define QAPI_BLE_HCI_EVENT_MASK_READ_CLOCK_OFFSET_COMPLETE_BIT_NUMBER               0x1B
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTION_PACKET_TYPE_CHANGED_BIT_NUMBER           0x1C
#define QAPI_BLE_HCI_EVENT_MASK_QOS_VIOLATION_BIT_NUMBER                            0x1D
#define QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_MODE_CHANGE_BIT_NUMBER                    0x1E
#define QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_REPETITION_MODE_CHANGE_BIT_NUMBER         0x1F

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the EVENT_MASK MACRO's (Set/Reset/Test).  These      */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth Event in the Event Mask (Version*/
   /* 1.2).                                                             */
#define QAPI_BLE_HCI_EVENT_MASK_FLOW_SPECIFICATION_BIT_NUMBER                     0x20
#define QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_WITH_RSSI_BIT_NUMBER               0x21
#define QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_BIT_NUMBER 0x22
#define QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_COMPLETE_BIT_NUMBER        0x2B
#define QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_CHANGED_BIT_NUMBER         0x2C

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the EVENT_MASK MACRO's (Set/Reset/Test).  These      */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth Event in the Event Mask (Version*/
   /* 2.1 + EDR).                                                       */
#define QAPI_BLE_HCI_EVENT_MASK_SNIFF_SUBRATING_BIT_NUMBER                             0x2D
#define QAPI_BLE_HCI_EVENT_MASK_EXTENDED_INQUIRY_RESULT_BIT_NUMBER                     0x2E
#define QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_REFRESH_COMPLETE_BIT_NUMBER                 0x2F
#define QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_BIT_NUMBER                       0x30
#define QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_REPLY_BIT_NUMBER                 0x31
#define QAPI_BLE_HCI_EVENT_MASK_USER_CONFIRMATION_REQUEST_BIT_NUMBER                   0x32
#define QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_REQUEST_BIT_NUMBER                        0x33
#define QAPI_BLE_HCI_EVENT_MASK_REMOTE_OOB_DATA_REQUEST_BIT_NUMBER                     0x34
#define QAPI_BLE_HCI_EVENT_MASK_SIMPLE_PAIRING_COMPLETE_BIT_NUMBER                     0x35
#define QAPI_BLE_HCI_EVENT_MASK_LINK_SUPERVISION_TIMEOUT_CHANGED_BIT_NUMBER            0x37
#define QAPI_BLE_HCI_EVENT_MASK_ENHANCED_FLUSH_COMPLETE_BIT_NUMBER                     0x38
#define QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_NOTIFICATION_BIT_NUMBER                   0x3A
#define QAPI_BLE_HCI_EVENT_MASK_USER_KEYPRESS_NOTIFICATION_BIT_NUMBER                  0x3B
#define QAPI_BLE_HCI_EVENT_MASK_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_BIT_NUMBER 0x3C

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the EVENT_MASK MACRO's (Set/Reset/Test).  These      */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth Event in the Event Mask (Version*/
   /* 4.0 + LE).                                                        */
#define QAPI_BLE_HCI_EVENT_MASK_LE_META_BIT_NUMBER                               0x3D

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Enabling ALL defined HCI Events in the HCI Event Mask.  This   */
   /* MACRO accepts as input the Event Mask (of type                    */
   /* qapi_BLE_Event_Mask_t) to enable all defined Events for.          */
   /* * NOTE * This MACRO is only valid for Events located in the Page 1*/
   /*          Event Mask NOT the Page 2 Event Mask !!!!!!!!!!!!!!!!!   */
#define QAPI_BLE_HCI_ENABLE_ALL_HCI_EVENTS_IN_EVENT_MASK(_x)                                                 \
{                                                                                                   \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_REQUEST_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_COMPLETE_BIT_NUMBER);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AUTHENTICAITION_COMPLETE_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_NAME_REQUEST_COMPLETE_BIT_NUMBER);                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_CHANGE_BIT_NUMBER);                           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CHANGE_CONNECTION_LINK_KEY_COMPLETE_BIT_NUMBER);         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MASTER_LINK_KEY_COMPLETE_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_BIT_NUMBER);     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_VERSION_INFORMATION_COMPLETE_BIT_NUMBER);    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_QOS_SETUP_COMPLETE_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_COMMAND_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_STATUS_COMMAND_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_HARDWARE_ERROR_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLUSH_OCCURRED_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ROLE_CHANGE_BIT_NUMBER);                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_PACKETS_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MODE_CHANGE_BIT_NUMBER);                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_RETURN_LINK_KEYS_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PIN_CODE_REQUEST_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_REQUEST_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_NOTIFICATION_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LOOPBACK_COMMAND_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DATA_BUFFER_OVERFLOW_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MAX_SLOTS_CHANGE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_CLOCK_OFFSET_COMPLETE_BIT_NUMBER);                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_PACKET_TYPE_CHANGED_BIT_NUMBER);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_QOS_VIOLATION_BIT_NUMBER);                               \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_MODE_CHANGE_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_REPETITION_MODE_CHANGE_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLOW_SPECIFICATION_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_WITH_RSSI_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_BIT_NUMBER);      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_COMPLETE_BIT_NUMBER);             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_CHANGED_BIT_NUMBER);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SNIFF_SUBRATING_BIT_NUMBER);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_EXTENDED_INQUIRY_RESULT_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_REFRESH_COMPLETE_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_REPLY_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_CONFIRMATION_REQUEST_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_REQUEST_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_OOB_DATA_REQUEST_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SIMPLE_PAIRING_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_SUPERVISION_TIMEOUT_CHANGED_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENHANCED_FLUSH_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_NOTIFICATION_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_KEYPRESS_NOTIFICATION_BIT_NUMBER);                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_BIT_NUMBER); \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LE_META_BIT_NUMBER);                                     \
}

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Disabling ALL defined HCI Events in the HCI Event Mask.  This  */
   /* MACRO accepts as input the Event Mask (of type                    */
   /* qapi_BLE_Event_Mask_t) to disable all defined Events for.         */
   /* * NOTE * This MACRO is only valid for Events located in the Page 1*/
   /*          Event Mask NOT the Page 2 Event Mask !!!!!!!!!!!!!!!!!   */
#define QAPI_BLE_HCI_DISABLE_ALL_HCI_EVENTS_IN_EVENT_MASK(_x)                                                  \
{                                                                                                     \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_REQUEST_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_COMPLETE_BIT_NUMBER);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AUTHENTICAITION_COMPLETE_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_NAME_REQUEST_COMPLETE_BIT_NUMBER);                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_CHANGE_BIT_NUMBER);                           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CHANGE_CONNECTION_LINK_KEY_COMPLETE_BIT_NUMBER);         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MASTER_LINK_KEY_COMPLETE_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_BIT_NUMBER);     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_VERSION_INFORMATION_COMPLETE_BIT_NUMBER);    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_QOS_SETUP_COMPLETE_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_COMMAND_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_STATUS_COMMAND_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_HARDWARE_ERROR_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLUSH_OCCURRED_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ROLE_CHANGE_BIT_NUMBER);                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_PACKETS_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MODE_CHANGE_BIT_NUMBER);                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_RETURN_LINK_KEYS_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PIN_CODE_REQUEST_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_REQUEST_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_NOTIFICATION_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LOOPBACK_COMMAND_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DATA_BUFFER_OVERFLOW_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_MAX_SLOTS_CHANGE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_CLOCK_OFFSET_COMPLETE_BIT_NUMBER);                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTION_PACKET_TYPE_CHANGED_BIT_NUMBER);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_QOS_VIOLATION_BIT_NUMBER);                               \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_MODE_CHANGE_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_REPETITION_MODE_CHANGE_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLOW_SPECIFICATION_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_WITH_RSSI_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_BIT_NUMBER);      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_COMPLETE_BIT_NUMBER);             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_CHANGED_BIT_NUMBER);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SNIFF_SUBRATING_BIT_NUMBER);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_EXTENDED_INQUIRY_RESULT_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_REFRESH_COMPLETE_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_BIT_NUMBER);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_REPLY_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_CONFIRMATION_REQUEST_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_REQUEST_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_OOB_DATA_REQUEST_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SIMPLE_PAIRING_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LINK_SUPERVISION_TIMEOUT_CHANGED_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_ENHANCED_FLUSH_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_NOTIFICATION_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_USER_KEYPRESS_NOTIFICATION_BIT_NUMBER);                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_BIT_NUMBER); \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LE_META_BIT_NUMBER);                                     \
}

   /* The following Constants represent Bit Number Constants that are   */
   /* to be used with the EVENT_MASK MACRO's (Set/Reset/Test).  These   */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth Event in the Event Mask.        */
   /* * NOTE * All of the constants specify Bit Numbers located in the  */
   /*          Page 2 of the Event Mask.  This Event Mask is set with   */
   /*          the HCI_Set_Event_Mask_Page_2 command (Version 3.0 + HS).*/
#define QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_COMPLETE_BIT_NUMBER                         0x00
#define QAPI_BLE_HCI_EVENT_MASK_CHANNEL_SELECTED_BIT_NUMBER                               0x01
#define QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_PHYSICAL_LINK_COMPLETE_BIT_NUMBER           0x02
#define QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_LOSS_EARLY_WARNING_BIT_NUMBER               0x03
#define QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_RECOVERY_BIT_NUMBER                         0x04
#define QAPI_BLE_HCI_EVENT_MASK_LOGICAL_LINK_COMPLETE_BIT_NUMBER                          0x05
#define QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_LOGICAL_LINK_COMPLETE_BIT_NUMBER            0x06
#define QAPI_BLE_HCI_EVENT_MASK_FLOW_SPEC_MODIFY_COMPLETE_BIT_NUMBER                      0x07
#define QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_DATA_BLOCKS_BIT_NUMBER                0x08
#define QAPI_BLE_HCI_EVENT_MASK_AMP_START_TEST_BIT_NUMBER                                 0x09
#define QAPI_BLE_HCI_EVENT_MASK_AMP_TEST_END_BIT_NUMBER                                   0x0A
#define QAPI_BLE_HCI_EVENT_MASK_AMP_RECEIVER_REPORT_BIT_NUMBER                            0x0B
#define QAPI_BLE_HCI_EVENT_MASK_SHORT_RANGE_MODE_CHANGE_COMPLETE_BIT_NUMBER               0x0C
#define QAPI_BLE_HCI_EVENT_MASK_AMP_STATUS_CHANGE_BIT_NUMBER                              0x0D
#define QAPI_BLE_HCI_EVENT_MASK_TRIGGERED_CLOCK_CAPTURE_EVENT                             0x0E
#define QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_COMPLETE_EVENT                      0x0F
#define QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_RECEIVED_EVENT                      0x10
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT              0x11
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_TIMEOUT_EVENT              0x12
#define QAPI_BLE_HCI_EVENT_MASK_TRUNCATED_PAGE_COMPLETE_EVENT                             0x13
#define QAPI_BLE_HCI_EVENT_MASK_SLAVE_PAGE_RESPONSE_TIMEOUT_EVENT                         0x14
#define QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_CHANNEL_MAP_CHANGE_EVENT   0x15
#define QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESPONSE_NOTIFICATION_EVENT                       0x16
#define QAPI_BLE_HCI_EVENT_MASK_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT               0x17

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Enabling ALL defined HCI Events in the HCI Event Mask Page 2   */
   /* Only.  This MACRO accepts as input the Event Mask (of type        */
   /* qapi_BLE_Event_Mask_t) to enable all defined Events for (Version  */
   /* 3.0 + HS).                                                        */
   /* * NOTE * This MACRO is only valid for Events located in the Page 2*/
   /*          Event Mask NOT the Page 1 Event Mask !!!!!!!!!!!!!!!!!   */
#define QAPI_BLE_HCI_ENABLE_ALL_HCI_EVENTS_IN_EVENT_MASK_PAGE_2(_x)                                            \
{                                                                                                     \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_COMPLETE_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CHANNEL_SELECTED_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_PHYSICAL_LINK_COMPLETE_BIT_NUMBER);          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_LOSS_EARLY_WARNING_BIT_NUMBER );             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_RECOVERY_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LOGICAL_LINK_COMPLETE_BIT_NUMBER);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_LOGICAL_LINK_COMPLETE_BIT_NUMBER);           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLOW_SPEC_MODIFY_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_DATA_BLOCKS_BIT_NUMBER);               \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_START_TEST_BIT_NUMBER);                                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_TEST_END_BIT_NUMBER);                                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_RECEIVER_REPORT_BIT_NUMBER);                           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SHORT_RANGE_MODE_CHANGE_COMPLETE_BIT_NUMBER);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_STATUS_CHANGE_BIT_NUMBER);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_TRIGGERED_CLOCK_CAPTURE_EVENT);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_COMPLETE_EVENT);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_RECEIVED_EVENT);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT);             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_TIMEOUT_EVENT);             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_TRUNCATED_PAGE_COMPLETE_EVENT);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SLAVE_PAGE_RESPONSE_TIMEOUT_EVENT);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_CHANNEL_MAP_CHANGE_EVENT);  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESPONSE_NOTIFICATION_EVENT);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT);              \
}

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Disabling ALL defined HCI Events in the HCI Event Mask Page 2  */
   /* Only.  This MACRO accepts as input the Event Mask (of type        */
   /* qapi_BLE_Event_Mask_t) to disable all defined Events for (Version */
   /* 3.0 + HS).                                                        */
   /* * NOTE * This MACRO is only valid for Events located in the Page 2*/
   /*          Event Mask NOT the Page 1 Event Mask !!!!!!!!!!!!!!!!!   */
#define QAPI_BLE_HCI_DISABLE_ALL_HCI_EVENTS_IN_EVENT_MASK_PAGE_2(_x)                                              \
{                                                                                                        \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_COMPLETE_BIT_NUMBER);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CHANNEL_SELECTED_BIT_NUMBER);                               \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_PHYSICAL_LINK_COMPLETE_BIT_NUMBER);           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_LOSS_EARLY_WARNING_BIT_NUMBER );              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_RECOVERY_BIT_NUMBER);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_LOGICAL_LINK_COMPLETE_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_LOGICAL_LINK_COMPLETE_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_FLOW_SPEC_MODIFY_COMPLETE_BIT_NUMBER);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_DATA_BLOCKS_BIT_NUMBER);                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_START_TEST_BIT_NUMBER);                                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_TEST_END_BIT_NUMBER);                                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_RECEIVER_REPORT_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SHORT_RANGE_MODE_CHANGE_COMPLETE_BIT_NUMBER);               \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AMP_STATUS_CHANGE_BIT_NUMBER);                              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_TRIGGERED_CLOCK_CAPTURE_EVENT);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_COMPLETE_EVENT);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SYNCHRONIZATION_TRAIN_RECEIVED_EVENT);                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_EVENT);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_TIMEOUT_EVENT);              \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_TRUNCATED_PAGE_COMPLETE_EVENT);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_SLAVE_PAGE_RESPONSE_TIMEOUT_EVENT);                         \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_CONNECTIONLESS_SLAVE_BROADCAST_CHANNEL_MAP_CHANGE_EVENT);   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESPONSE_NOTIFICATION_EVENT);                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_EVENT_MASK_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT);               \
}

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Minimum and Maximum Acceptable Values for Connection Handles.     */
#define QAPI_BLE_HCI_CONNECTION_HANDLE_MINIMUM_VALUE                             0x0000
#define QAPI_BLE_HCI_CONNECTION_HANDLE_MAXIMUM_VALUE                             0x0EFF

   /* The following Constant represents a Bluetooth HCI Connection      */
   /* Handle value that is guaranteed to be invalid.                    */
#define QAPI_BLE_HCI_CONNECTION_HANDLE_INVALID_VALUE                             0xF000

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Connection      */
   /* Handle is valid.  The first parameter to this MACRO is the        */
   /* Connection Handle Value to verify.  This MACRO returns a          */
   /* boolean value based upon whether or not the specified Connection  */
   /* Handle value is valid.  This MACRO returns a boolean TRUE if the  */
   /* specified Connection Handle is valid, or a boolean FALSE if the   */
   /* specified Connection Handle value is invalid.                     */
#define QAPI_BLE_HCI_CONNECTION_HANDLE_VALID_CONNECTION_HANDLE(_x)               (((_x) >= QAPI_BLE_HCI_CONNECTION_HANDLE_MINIMUM_VALUE) && ((_x) <= QAPI_BLE_HCI_CONNECTION_HANDLE_MAXIMUM_VALUE))

   /* The following constants represent the maximum palyload sizes that */
   /* are possible for each packet type.                                */
#define QAPI_BLE_HCI_PACKET_TYPE_DM1_MAXIMUM_PAYLOAD_SIZE                          17
#define QAPI_BLE_HCI_PACKET_TYPE_DH1_MAXIMUM_PAYLOAD_SIZE                          27
#define QAPI_BLE_HCI_PACKET_TYPE_DM3_MAXIMUM_PAYLOAD_SIZE                         121
#define QAPI_BLE_HCI_PACKET_TYPE_DH3_MAXIMUM_PAYLOAD_SIZE                         183
#define QAPI_BLE_HCI_PACKET_TYPE_DM5_MAXIMUM_PAYLOAD_SIZE                         224
#define QAPI_BLE_HCI_PACKET_TYPE_DH5_MAXIMUM_PAYLOAD_SIZE                         339
#define QAPI_BLE_HCI_PACKET_TYPE_AUX1_MAXIMUM_PAYLOAD_SIZE                         29
#define QAPI_BLE_HCI_PACKET_TYPE_2_DH1_MAXIMUM_PAYLOAD_SIZE                        54
#define QAPI_BLE_HCI_PACKET_TYPE_2_DH3_MAXIMUM_PAYLOAD_SIZE                       367
#define QAPI_BLE_HCI_PACKET_TYPE_2_DH5_MAXIMUM_PAYLOAD_SIZE                       679
#define QAPI_BLE_HCI_PACKET_TYPE_3_DH1_MAXIMUM_PAYLOAD_SIZE                        83
#define QAPI_BLE_HCI_PACKET_TYPE_3_DH3_MAXIMUM_PAYLOAD_SIZE                       552
#define QAPI_BLE_HCI_PACKET_TYPE_3_DH5_MAXIMUM_PAYLOAD_SIZE                      1021

#define QAPI_BLE_HCI_PACKET_TYPE_HV1_MAXIMUM_PAYLOAD_SIZE                          10
#define QAPI_BLE_HCI_PACKET_TYPE_HV2_MAXIMUM_PAYLOAD_SIZE                          20
#define QAPI_BLE_HCI_PACKET_TYPE_HV3_MAXIMUM_PAYLOAD_SIZE                          30
#define QAPI_BLE_HCI_PACKET_TYPE_DV_MAXIMUM_PAYLOAD_SIZE                           29
#define QAPI_BLE_HCI_PACKET_TYPE_EV3_MAXIMUM_PAYLOAD_SIZE                          30
#define QAPI_BLE_HCI_PACKET_TYPE_EV4_MAXIMUM_PAYLOAD_SIZE                         120
#define QAPI_BLE_HCI_PACKET_TYPE_EV5_MAXIMUM_PAYLOAD_SIZE                         180
#define QAPI_BLE_HCI_PACKET_TYPE_2_EV3_MAXIMUM_PAYLOAD_SIZE                       192
#define QAPI_BLE_HCI_PACKET_TYPE_2_EV5_MAXIMUM_PAYLOAD_SIZE                       576
#define QAPI_BLE_HCI_PACKET_TYPE_3_EV3_MAXIMUM_PAYLOAD_SIZE                       288
#define QAPI_BLE_HCI_PACKET_TYPE_3_EV5_MAXIMUM_PAYLOAD_SIZE                       864

   /* The following constants represent the defined Bluetooth HCI ACL   */
   /* Packet Types.                                                     */
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DM1                                         0x0008
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DH1                                         0x0010
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DM3                                         0x0400
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DH3                                         0x0800
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DM5                                         0x4000
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_DH5                                         0x8000

   /* The following constants represent the defined Bluetooth HCI ACL   */
   /* extended packet types (Version 2.0).                              */
   /* * NOTE * These types are different in that they specify packet    */
   /*          type that MAY NOT be used (rather than packet types that */
   /*          MAY be used).                                            */
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_2_DH1_MAY_NOT_BE_USED                       0x0002
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_3_DH1_MAY_NOT_BE_USED                       0x0004

#define QAPI_BLE_HCI_PACKET_ACL_TYPE_2_DH3_MAY_NOT_BE_USED                       0x0100
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_3_DH3_MAY_NOT_BE_USED                       0x0200

#define QAPI_BLE_HCI_PACKET_ACL_TYPE_2_DH5_MAY_NOT_BE_USED                       0x1000
#define QAPI_BLE_HCI_PACKET_ACL_TYPE_3_DH5_MAY_NOT_BE_USED                       0x2000

   /* The following Constants represent the defined Bluetooth HCI Page  */
   /* Scan Repetition Mode Types.                                       */
#define QAPI_BLE_HCI_PAGE_SCAN_REPETITION_MODE_R0                                0x00
#define QAPI_BLE_HCI_PAGE_SCAN_REPETITION_MODE_R1                                0x01
#define QAPI_BLE_HCI_PAGE_SCAN_REPETITION_MODE_R2                                0x02

   /* The following Constants represent the defined Bluetooth HCI Page  */
   /* Scan Mode Types.                                                  */
#define QAPI_BLE_HCI_PAGE_SCAN_MODE_MANDATORY                                    0x00
#define QAPI_BLE_HCI_PAGE_SCAN_MODE_OPTIONAL_I                                   0x01
#define QAPI_BLE_HCI_PAGE_SCAN_MODE_OPTIONAL_II                                  0x02
#define QAPI_BLE_HCI_PAGE_SCAN_MODE_OPTIONAL_III                                 0x03

   /* The following Constants represent the defined Bluetooth HCI Page  */
   /* Scan Types (Version 1.2).                                         */
#define QAPI_BLE_HCI_PAGE_SCAN_TYPE_MANDATORY_STANDARD_SCAN                      0x00
#define QAPI_BLE_HCI_PAGE_SCAN_TYPE_OPTIONAL_INTERLACED_SCAN                     0x01

   /* The following Constants represent the defined Bluetooth HCI Clock */
   /* Offset Bit Mask values.                                           */
#define QAPI_BLE_HCI_CLOCK_OFFSET_CLK_SLAVE_CLK_MASTER_MASK                      0x7FFF
#define QAPI_BLE_HCI_CLOCK_OFFSET_VALID_FLAG_MASK                                0x8000

   /* The following Constants represent the defined Bluetooth HCI Role  */
   /* Switch Options.                                                   */
#define QAPI_BLE_HCI_ROLE_SWITCH_LOCAL_MASTER_NO_ROLE_SWITCH                     0x00
#define QAPI_BLE_HCI_ROLE_SWITCH_LOCAL_MASTER_ACCEPT_ROLE_SWITCH                 0x01

   /* The following Constants represent the defined Bluetooth HCI SCO   */
   /* Packet Types.                                                     */
#define QAPI_BLE_HCI_PACKET_SCO_TYPE_HV1                                         0x0020
#define QAPI_BLE_HCI_PACKET_SCO_TYPE_HV2                                         0x0040
#define QAPI_BLE_HCI_PACKET_SCO_TYPE_HV3                                         0x0080

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Synchronous Connection Packet Types (SCO and eSCO in Version 1.2  */
   /* ).                                                                */
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_HV1                      0x0001
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_HV2                      0x0002
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_HV3                      0x0004
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_EV3                      0x0008
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_EV4                      0x0010
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_EV5                      0x0020

   /* The following constants represent the defined Bluetooth HCI eSCO  */
   /* extended packet types (Version 2.0).                              */
   /* * NOTE * These types are different in that they specify packet    */
   /*          type that MAY NOT be used (rather than packet types that */
   /*          MAY be used).                                            */
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_2_EV3_MAY_NOT_BE_USED    0x0040
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_3_EV3_MAY_NOT_BE_USED    0x0080

#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_2_EV5_MAY_NOT_BE_USED    0x0100
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_3_EV5_MAY_NOT_BE_USED    0x0200

   /* The following constants are placeholders for the reserved bits    */
   /* in the packet type field.                                         */
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED0                0x0400
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED1                0x0800
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED2                0x1000
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED3                0x2000
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED4                0x4000
#define QAPI_BLE_HCI_PACKET_SYNCHRONOUS_CONNECTION_TYPE_RESERVED5                0x8000

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Synchronous Connecton Maximum Latency Type values (Version 1.2).  */
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_MAX_LATENCY_MINIMUM                  0x0004
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_MAX_LATENCY_MAXIMUM                  0xFFFE
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_MAX_LATENCY_DONT_CARE                0xFFFF

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Synchronous Connection Retransmission Effort Type values (Version */
   /* 1.2).                                                             */
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_RETRANSMISSION_EFFORT_NONE                 0x00
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_RETRANSMISSION_EFFORT_ONE_OPTIMIZE_POWER   0x01
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_RETRANSMISSION_EFFORT_ONE_OPTIMIZE_QUALITY 0x02
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_RETRANSMISSION_EFFORT_DONT_CARE            0xFF

   /* The following Constants represent the defined Bluetooth Values    */
   /* that specify specific Bluetooth HCI Transmit and Receive Bandwidth*/
   /* values when Accepting Synchronous Connections (Version 1.2).      */
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_TRANSMIT_BANDWIDTH_MINIMUM    0x00000000L
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_TRANSMIT_BANDWIDTH_MAXIMUM    0xFFFFFFFEL
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_TRANSMIT_BANDWIDTH_DONT_CARE  0xFFFFFFFFL

#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_RECEIVE_BANDWIDTH_MINIMUM     0x00000000L
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_RECEIVE_BANDWIDTH_MAXIMUM     0xFFFFFFFEL
#define QAPI_BLE_HCI_SYNCHRONOUS_CONNECTION_ACCEPT_RECEIVE_BANDWIDTH_DONT_CARE   0xFFFFFFFFL

   /* The following constants represent the defined Bluetooth Values    */
   /* that specify the specific Bluetooth HCI Extended Inquiry Response */
   /* Data values used with the Extended Inquiry Response (Version 2.1 +*/
   /* EDR).                                                             */
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_FLAGS                               0x01
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_16_BIT_SERVICE_CLASS_UUID_PARTIAL   0x02
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_16_BIT_SERVICE_CLASS_UUID_COMPLETE  0x03
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_32_BIT_SERVICE_CLASS_UUID_PARTIAL   0x04
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_32_BIT_SERVICE_CLASS_UUID_COMPLETE  0x05
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_128_BIT_SERVICE_CLASS_UUID_PARTIAL  0x06
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_128_BIT_SERVICE_CLASS_UUID_COMPLETE 0x07
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_LOCAL_NAME                          0x08
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_LOCAL_NAME_SHORTENED                0x08
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_LOCAL_NAME_COMPLETE                 0x09
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_TX_POWER_LEVEL                      0x0A
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_CLASS_OF_DEVICE                     0x0D
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_SIMPLE_PAIRING_HASH_C               0x0E
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_SIMPLE_PAIRING_RANDOMIZER_R         0x0F
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_DEVICE_ID                           0x10
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_SIMPLE_PAIRING_HASH_C_256           0x1D
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_SIMPLE_PAIRING_RANDOMIZER_R_256     0x1E
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_3D_INFORMATION_DATA                 0x3D
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_DATA_TYPE_MANUFACTURER_SPECIFIC               0xFF

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Minimum and Maximum Acceptable Values for Physical Link Handles   */
   /* (Version 3.0 + HS).                                               */
#define QAPI_BLE_HCI_PHYSICAL_LINK_HANDLE_MINIMUM_VALUE                          0x01
#define QAPI_BLE_HCI_PHYSICAL_LINK_HANDLE_MAXIMUM_VALUE                          0xFF

   /* The following Constant represents a Bluetooth HCI Physical Link   */
   /* Handle value that is guaranteed to be invalid.                    */
#define QAPI_BLE_HCI_PHYSICAL_LINK_HANDLE_INVALID_VALUE                          0x00

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Minimum and Maximum Acceptable Values for Logical Link Handles    */
   /* (Version 3.0 + HS).                                               */
#define QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_MINIMUM_VALUE                           0x0000
#define QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_MAXIMUM_VALUE                           0x0EFF

   /* The following Constant represents a Bluetooth HCI Logical Link    */
   /* Handle value that is guaranteed to be invalid.                    */
#define QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_INVALID_VALUE                           0xF000

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Logical Link    */
   /* Handle is valid.  The first parameter to this MACRO is the Logical*/
   /* Link Handle Value to verify.  This MACRO returns a boolean value  */
   /* based upon whether or not the specified Logical Link Handle value */
   /* is valid.  This MACRO returns a boolean TRUE if the specified     */
   /* Logical Link is valid, or a boolean FALSE if the specified Logical*/
   /* Link value is invalid.                                            */
#define QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_VALID_LOGICAL_LINK_HANDLE(_x)           (((_x) >= QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_MINIMUM_VALUE) && ((_x) <= QAPI_BLE_HCI_LOGICAL_LINK_HANDLE_MAXIMUM_VALUE))

   /* The following constants represent the defined Bluetooth Values    */
   /* that specify the specific Bluetooth HCI I/O Capabilities values   */
   /* used with I/O Capability commands (Version 2.1 + EDR).            */
#define QAPI_BLE_HCI_IO_CAPABILITY_DISPLAY_ONLY                                  0x00
#define QAPI_BLE_HCI_IO_CAPABILITY_DISPLAY_YES_NO                                0x01
#define QAPI_BLE_HCI_IO_CAPABILITY_KEYBOARD_ONLY                                 0x02
#define QAPI_BLE_HCI_IO_CAPABILITY_NO_INPUT_NO_OUTPUT                            0x03

   /* The following constants are used with the HCI I/O Capabilities    */
   /* values used with the I/O Capability Events (Version 2.1 + EDR).   */
#define QAPI_BLE_HCI_IO_CAPABILITY_OOB_AUTHENTICATION_DATA_NOT_PRESENT           0x00
#define QAPI_BLE_HCI_IO_CAPABILITY_OOB_AUTHENTICATION_DATA_PRESENT               0x01

   /* The following constants are used with the additional HCI I/O      */
   /* Capabilities values used with the I/O Capability Events (Version  */
   /* 4.1).                                                             */
#define QAPI_BLE_HCI_IO_CAPABILITY_OOB_AUTHENTICATION_DATA_P192_PRESENT          0x01
#define QAPI_BLE_HCI_IO_CAPABILITY_OOB_AUTHENTICATION_DATA_P256_PRESENT          0x02
#define QAPI_BLE_HCI_IO_CAPABILITY_OOB_AUTHENTICATION_DATA_P192_P256_PRESENT     0x03

   /* The following constants are used with the HCI I/O Capabilities    */
   /* values with the I/O Capability Events (Version 2.1 + EDR).        */
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_NOT_REQUIRED_NO_BONDING        0x00
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_REQUIRED_NO_BONDING            0x01
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_NOT_REQUIRED_DEDICATED_BONDING 0x02
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_REQUIRED_DEDICATED_BONDING     0x03
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_NOT_REQUIRED_GENERAL_BONDING   0x04
#define QAPI_BLE_HCI_AUTHENTICATION_REQUIREMENTS_MITM_PROTECTION_REQUIRED_GENERAL_BONDING       0x05

   /* The following constant represents the defined maximum number of   */
   /* digits that can be specified for a Bluetooth Passkey used during  */
   /* Simple Pairing (Version 2.1 + EDR).                               */
#define QAPI_BLE_HCI_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS                            6

   /* The following constants represent the defined Bluetooth Values    */
   /* that specify the specific Bluetooth HCI minimum and maximum       */
   /* Passkey values used during Simple Pairing (Version 2.1 + EDR).    */
#define QAPI_BLE_HCI_PASSKEY_NUMERIC_VALUE_MINIMUM                               0x00000000L
#define QAPI_BLE_HCI_PASSKEY_NUMERIC_VALUE_MAXIMUM                               0x000F423FL

   /* The following constants represent the defined minimum and maximum */
   /* timeout values that are used with the Bluetooth Sniff Subrating   */
   /* HCI commands (Version 2.1 + EDR).                                 */
#define QAPI_BLE_HCI_SNIFF_SUBRATING_TIMEOUT_MINIMUM                             0x0000
#define QAPI_BLE_HCI_SNIFF_SUBRATING_TIMEOUT_MAXIMUM                             0xFFFE

   /* The following Constants represent the defined Bluetooth Values    */
   /* that specify a specific Bluetooth HCI Air Mode Format for         */
   /* Synchronous Connections (Version 1.2)                             */
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_U_LAW                                       0x00
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_A_LAW                                       0x01
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_CVSD                                        0x02
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_TRANSPARENT_DATA                            0x03

   /* The following Constants represent the defined Bluetooth Values    */
   /* that specify a specific Bluetooth HCI Air Mode Format for         */
   /* Synchronous Connections (Version 4.0 + CSA2)                      */
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_LINEAR_PCM                                  0x04
#define QAPI_BLE_HCI_AIR_MODE_FORMAT_MODIFIED_SBC                                0x05

   /* The following Constants represent the defined Bluetooth HCI Role  */
   /* Change Types.                                                     */
#define QAPI_BLE_HCI_ROLE_SWITCH_BECOME_MASTER                                   0x00
#define QAPI_BLE_HCI_ROLE_SWITCH_REMAIN_SLAVE                                    0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Encryption Enable (Link Level) Types.                             */
#define QAPI_BLE_HCI_ENCRYPTION_ENABLE_LINK_LEVEL_OFF                            0x00
#define QAPI_BLE_HCI_ENCRYPTION_ENABLE_LINK_LEVEL_ON                             0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Master Link Key Key Flag Types.                                   */
#define QAPI_BLE_HCI_MASTER_LINK_KEY_USE_SEMI_PERMANENT_LINK_KEYS                0x00
#define QAPI_BLE_HCI_MASTER_LINK_KEY_USE_TEMPORARY_LINK_KEYS                     0x01

   /* The following Constants represent the defined Bluetooth HCI QoS   */
   /* Service Types.                                                    */
#define QAPI_BLE_HCI_QOS_SERVICE_TYPE_NO_TRAFFIC                                 0x00
#define QAPI_BLE_HCI_QOS_SERVICE_TYPE_BEST_EFFORT                                0x01
#define QAPI_BLE_HCI_QOS_SERVICE_TYPE_GUARANTEED                                 0x02

   /* The following Constants represent the defined Bluetooth HCI Flow  */
   /* Specification Flow Direction (Version 1.2).                       */
#define QAPI_BLE_HCI_FLOW_SPECIFICATION_FLOW_DIRECTION_OUTGOING_FLOW             0x00
#define QAPI_BLE_HCI_FLOW_SPECIFICATION_FLOW_DIRECTION_INCOMING_FLOW             0x01

   /* The following Constants represent the defined Bluetooth HCI Flow  */
   /* Specification Service Types (Version 1.2).                        */
#define QAPI_BLE_HCI_FLOW_SPECIFICATION_SERVICE_TYPE_NO_TRAFFIC                  0x00
#define QAPI_BLE_HCI_FLOW_SPECIFICATION_SERVICE_TYPE_BEST_EFFORT                 0x01
#define QAPI_BLE_HCI_FLOW_SPECIFICATION_SERVICE_TYPE_GUARANTEED                  0x02

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Current Role Types.                                               */
#define QAPI_BLE_HCI_CURRENT_ROLE_MASTER                                         0x00
#define QAPI_BLE_HCI_CURRENT_ROLE_SLAVE                                          0x01

   /* The following Constants represent the defined Bluetooth HCI Link  */
   /* Policy Settings Flag Types.                                       */
#define QAPI_BLE_HCI_LINK_POLICY_SETTINGS_DISABLE_ALL_LM_MODES                   0x0000
#define QAPI_BLE_HCI_LINK_POLICY_SETTINGS_ENABLE_MASTER_SLAVE_SWITCH             0x0001
#define QAPI_BLE_HCI_LINK_POLICY_SETTINGS_ENABLE_HOLD_MODE                       0x0002
#define QAPI_BLE_HCI_LINK_POLICY_SETTINGS_ENABLE_SNIFF_MODE                      0x0004
#define QAPI_BLE_HCI_LINK_POLICY_SETTINGS_ENABLE_PARK_MODE                       0x0008

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Country Code Types (Version 1.0B)                                 */
#define QAPI_BLE_HCI_COUNTRY_CODE_NORTH_AMERICA_AND_EUROPE                       0x00
#define QAPI_BLE_HCI_COUNTRY_CODE_FRANCE                                         0x01
#define QAPI_BLE_HCI_COUNTRY_CODE_SPAIN                                          0x02
#define QAPI_BLE_HCI_COUNTRY_CODE_JAPAN                                          0x03

   /* The following Constants represent additional defined Bluetooth HCI*/
   /* Country Code Types (Version 1.1).  The only other Country Code    */
   /* listed above that is valid is QAPI_BLE_HCI_COUNTRY_CODE_FRANCE.   */
#define QAPI_BLE_HCI_COUNTRY_CODE_NORTH_AMERICA_EUROPE_JAPAN_NOT_FRANCE          0x00

   /* The following Constants represent the various Clocks that can be  */
   /* queried via the defined HCI Commands/Events (Version 1.2).        */
#define QAPI_BLE_HCI_CLOCK_LOCAL_CLOCK                                           0x00
#define QAPI_BLE_HCI_CLOCK_PICONET_CLOCK                                         0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Loopback Code Types.                                              */
#define QAPI_BLE_HCI_LOOPBACK_MODE_NO_LOOPBACK_MODE                              0x00
#define QAPI_BLE_HCI_LOOPBACK_MODE_ENABLE_LOCAL_LOOPBACK                         0x01
#define QAPI_BLE_HCI_LOOPBACK_MODE_ENABLE_REMOTE_LOOPBACK                        0x02

   /* The following Constants represent the defined Bluetooth HCI Simple*/
   /* Debug Mode Enable Modes (Version 2.1 + EDR).                      */
#define QAPI_BLE_HCI_SIMPLE_PAIRING_DEBUG_MODE_DISABLED                          0x00
#define QAPI_BLE_HCI_SIMPLE_PAIRING_DEBUG_MODE_ENABLED                           0x01

   /* The following Constants represent the defined Bluetooth HCI Filter*/
   /* Types.                                                            */
#define QAPI_BLE_HCI_FILTER_TYPE_CLEAR                                           0x00
#define QAPI_BLE_HCI_FILTER_TYPE_INQUIRY_RESULT                                  0x01
#define QAPI_BLE_HCI_FILTER_TYPE_CONNECTION_SETUP                                0x02

   /* The following Constants represent the defined Bluetooth HCI Filter*/
   /* Condition Types for the QAPI_BLE_HCI_FILTER_TYPE_INQUIRY_RESULT   */
   /* Type.                                                             */
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_RESULT_FILTER_NEW_DEVICE              0x00
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_RESULT_FILTER_CLASS_OF_DEVICE         0x01
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_RESULT_FILTER_BD_ADDR                 0x02

   /* The following Constants represent the defined Bluetooth HCI Filter*/
   /* Condition Types for the QAPI_BLE_HCI_FILTER_TYPE_CONNECTION_SETUP */
   /* Type.                                                             */
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_CONNECTION_SETUP_ALL_DEVICES          0x00
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_CONNECTION_SETUP_CLASS_OF_DEVICE      0x01
#define QAPI_BLE_HCI_FILTER_CONDITION_TYPE_CONNECTION_SETUP_BD_ADDR              0x02

   /* The following Constants represent the defined Bluetooth HCI Auto  */
   /* Accept Flag Types.                                                */
#define QAPI_BLE_HCI_AUTO_ACCEPT_FLAG_DO_NOT_AUTO_ACCEPT                         0x01
#define QAPI_BLE_HCI_AUTO_ACCEPT_FLAG_DO_AUTO_ACCEPT                             0x02

   /* The following Constants represent additional defined Bluetooth    */
   /* HCI Auto Accept Flag Types (Version 1.1).                         */
#define QAPI_BLE_HCI_AUTO_ACCEPT_FLAG_DO_AUTO_ACCEPT_ROLE_SWITCH_DISABLED        0x02
#define QAPI_BLE_HCI_AUTO_ACCEPT_FLAG_DO_AUTO_ACCEPT_ROLE_SWITCH_ENABLED         0x03

   /* The following Constants represent the defined Bluetooth HCI PIN   */
   /* Types.                                                            */
#define QAPI_BLE_HCI_PIN_TYPE_VARIABLE                                           0x00
#define QAPI_BLE_HCI_PIN_TYPE_FIXED                                              0x01

   /* The following Constants represent the defined Bluetooth HCI Read  */
   /* Link Key Flag Types.                                              */
#define QAPI_BLE_HCI_READ_LINK_KEY_BD_ADDR                                       0x00
#define QAPI_BLE_HCI_READ_LINK_KEY_ALL_STORED                                    0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Delete Link Key Flag Types.                                       */
#define QAPI_BLE_HCI_DELETE_LINK_KEY_BD_ADDR                                     0x00
#define QAPI_BLE_HCI_DELETE_LINK_KEY_ALL_STORED                                  0x01

   /* The following Constants represent the defined Bluetooth HCI Scan  */
   /* Enable Types.                                                     */
#define QAPI_BLE_HCI_SCAN_ENABLE_NO_SCANS_ENABLED                                0x00
#define QAPI_BLE_HCI_SCAN_ENABLE_INQUIRY_SCAN_ENABLED_PAGE_SCAN_DISABLED         0x01
#define QAPI_BLE_HCI_SCAN_ENABLE_INQUIRY_SCAN_DISABLED_PAGE_SCAN_ENABLED         0x02
#define QAPI_BLE_HCI_SCAN_ENABLE_INQUIRY_SCAN_ENABLED_PAGE_SCAN_ENABLED          0x03

#define QAPI_BLE_HCI_SCAN_ENABLE_INQUIRY_SCAN_ENABLED_BIT_MASK                   0x01
#define QAPI_BLE_HCI_SCAN_ENABLE_PAGE_SCAN_ENABLED_BIT_MASK                      0x02

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Authentication Enable Types.                                      */
#define QAPI_BLE_HCI_AUTHENTICATION_ENABLE_AUTHENTICATION_DISABLED                0x00
#define QAPI_BLE_HCI_AUTHENTICATION_ENABLE_AUTHENTICATION_ENABLED_ALL_CONNECTIONS 0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Encryption Mode Types (legacy).                                   */
#define QAPI_BLE_HCI_ENCRYPTION_MODE_ENCRYPTION_DISABLED                         0x00
#define QAPI_BLE_HCI_ENCRYPTION_MODE_ENCRYPTION_POINT_TO_POINT_PACKETS           0x01
#define QAPI_BLE_HCI_ENCRYPTION_MODE_ENCRYPTION_POINT_TO_POINT_BROADCAST_PACKETS 0x02

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Encryption Mode Types (Version 4.1).                              */
#define QAPI_BLE_HCI_ENCRYPTION_MODE_ENCRYPTION_ENABLED                          0x01
#define QAPI_BLE_HCI_ENCRYPTION_MODE_ENCRYPTION_ENABLED_AES_CCM_BR_EDR           0x02

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Mask's to apply to the Bluetooth HCI Voice Setting Values.        */
   /* After the correct Mask is applied, the Data can then be tested    */
   /* and/or set with the bit definition values that follow.            */
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_CODING_MASK                             0x0300
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_MASK                        0x00C0
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_SAMPLE_SIZE_MASK                        0x0020
#define QAPI_BLE_HCI_VOICE_SETTING_LINEAR_PCM_BIT_POS_NUM_MASK                   0x001C
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_MASK                        0x0003

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the                                            */
   /* QAPI_BLE_HCI_VOICE_SETTING_INPUT_CODING_MASK Bit Mask) that       */
   /* specify a specific Bluetooth HCI Input Coding Voice Setting.      */
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_CODING_LINEAR                           0x0000
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_CODING_U_LAW                            0x0100
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_CODING_A_LAW                            0x0200

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the                                            */
   /* QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_MASK Bit Mask) that  */
   /* specify a specific Bluetooth HCI Input Data Format Voice Setting. */
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_1_COMPLEMENT                0x0000
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_2_COMPLEMENT                0x0040
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_SIGN_MAGNITUDE              0x0080
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_DATA_FORMAT_UNSIGNED                    0x00C0

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the                                            */
   /* QAPI_BLE_HCI_VOICE_SETTING_INPUT_SAMPLE_SIZE_MASK Bit Mask) that  */
   /* specify a specific Bluetooth HCI Input Sample Size Voice Setting. */
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_SAMPLE_SIZE_8_BIT                       0x0000
#define QAPI_BLE_HCI_VOICE_SETTING_INPUT_SAMPLE_SIZE_16_BIT                      0x0020

   /* The following Constant represents the defined Bluetooth HCI       */
   /* Linear PCM Bit Position Number Shift Value.  This value represents*/
   /* the Number of Bit Positions that a value must be shifted into the */
   /* (or out of) Voice Setting Parameter to get a numerical value of   */
   /* the Number of Linear PCM Bit Positions                            */
#define QAPI_BLE_HCI_VOICE_SETTING_LINEAR_PCM_BIT_POS_NUM_SHIFT_VALUE            0x0002

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the                                            */
   /* QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_MASK Bit Mask) that  */
   /* specify a specific Bluetooth HCI Air Coding Format Voice Setting. */
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_CVSD                        0x0000
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_U_LAW                       0x0001
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_A_LAW                       0x0002
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_NONE                        0x0003

   /* The following Constants represent the defined Bluetooth HCI Bit   */
   /* Values (based upon the                                            */
   /* QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_MASK Bit Mask) that  */
   /* specify a specific Bluetooth HCI Air Coding Format Voice Setting  */
   /* (Version 1.2)                                                     */
#define QAPI_BLE_HCI_VOICE_SETTING_AIR_CODING_FORMAT_TRANSPARENT_DATA            0x0003

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Hold Mode Activity Bit Value Types.                               */
#define QAPI_BLE_HCI_HOLD_MODE_ACTIVITY_MAINTAIN_CURRENT_POWER_STATE             0x00
#define QAPI_BLE_HCI_HOLD_MODE_ACTIVITY_SUSPEND_PAGE_STATE                       0x01
#define QAPI_BLE_HCI_HOLD_MODE_ACTIVITY_SUSPEND_INQUIRY_STATE                    0x02
#define QAPI_BLE_HCI_HOLD_MODE_ACTIVITY_SUSPEND_PERIODIC_INQUIRIES               0x04

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Transmit Power Level Types.                                       */
#define QAPI_BLE_HCI_TRANSMIT_POWER_LEVEL_TYPE_CURRENT                           0x00
#define QAPI_BLE_HCI_TRANSMIT_POWER_LEVEL_TYPE_MAXIMUM                           0x01

   /* The following Constants represent the defined Bluetooth HCI SCO   */
   /* Flow Control Enable Types.                                        */
#define QAPI_BLE_HCI_SCO_FLOW_CONTROL_DISABLE                                    0x00
#define QAPI_BLE_HCI_SCO_FLOW_CONTROL_ENABLE                                     0x01

   /* The following Constants represent the defined Bluetooth HCI Host  */
   /* Flow Control Enable Types.                                        */
#define QAPI_BLE_HCI_HOST_FLOW_CONTROL_ENABLE_OFF                                0x00
#define QAPI_BLE_HCI_HOST_FLOW_CONTROL_ENABLE_ON                                 0x01

   /* The following Constants represent additional defined Bluetooth    */
   /* HCI Host Flow Control Enable Types (Version 1.1).                 */
#define QAPI_BLE_HCI_HOST_FLOW_CONTROL_ENABLE_ACL_ON_SCO_OFF                     0x01
#define QAPI_BLE_HCI_HOST_FLOW_CONTROL_ENABLE_ACL_OFF_SCO_ON                     0x02
#define QAPI_BLE_HCI_HOST_FLOW_CONTROL_ENABLE_ACL_ON_SCO_ON                      0x03

   /* The following Constants represent the defined Bluetooth HCI Page  */
   /* Scan Period Mode Types.                                           */
#define QAPI_BLE_HCI_PAGE_SCAN_PERIOD_MODE_P0                                    0x00
#define QAPI_BLE_HCI_PAGE_SCAN_PERIOD_MODE_P1                                    0x01
#define QAPI_BLE_HCI_PAGE_SCAN_PERIOD_MODE_P2                                    0x02

   /* The following Constants represent the defined Bluetooth HCI Link  */
   /* Type Types.                                                       */
#define QAPI_BLE_HCI_LINK_TYPE_SCO_CONNECTION                                    0x00
#define QAPI_BLE_HCI_LINK_TYPE_ACL_CONNECTION                                    0x01

   /* The following Constants represent the defined Bluetooth HCI Link  */
   /* Type Types (Version 1.2).                                         */
#define QAPI_BLE_HCI_LINK_TYPE_ESCO_CONNECTION                                   0x02

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Current Mode Types.                                               */
#define QAPI_BLE_HCI_CURRENT_MODE_ACTIVE_MODE                                    0x00
#define QAPI_BLE_HCI_CURRENT_MODE_HOLD_MODE                                      0x01
#define QAPI_BLE_HCI_CURRENT_MODE_SNIFF_MODE                                     0x02
#define QAPI_BLE_HCI_CURRENT_MODE_PARK_MODE                                      0x03

   /* The following Constants represent the defined Bluetooth HCI       */
   /* SCO Link Number of Connections.                                   */
#define QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_SAME_MASTER                          0x03
#define QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_DIFFERENT_MASTER                     0x02

#define QAPI_BLE_HCI_MAX_NUMBER_SCO_CONNECTIONS  ((QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_SAME_MASTER>QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_DIFFERENT_MASTER)?QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_SAME_MASTER:QAPI_BLE_HCI_NUMBER_SCO_CONNECTIONS_DIFFERENT_MASTER)

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Inquiry Scan Types (Version 1.2).                                 */
#define QAPI_BLE_HCI_INQUIRY_SCAN_TYPE_MANDATORY_STANDARD_SCAN                   0x00
#define QAPI_BLE_HCI_INQUIRY_SCAN_TYPE_OPTIONAL_INTERLACED_SCAN                  0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Inquiry Scan Modes (Version 1.2).                                 */
#define QAPI_BLE_HCI_INQUIRY_MODE_STANDARD_INQUIRY_RESULT                        0x00
#define QAPI_BLE_HCI_INQUIRY_MODE_INQUIRY_RESULT_FORMAT_WITH_RSSI                0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Inquiry Scan Modes (Version 2.1 + EDR).                           */
#define QAPI_BLE_HCI_INQUIRY_MODE_INQUIRY_RESULT_WITH_RSSI_OR_EXTENDED_RESULT    0x02

   /* The following Constants represent the defined Bluetooth HCI AFH   */
   /* Channel Assessment Mode Types (Version 1.2).                      */
#define QAPI_BLE_HCI_AFH_CHANNEL_ASSESSMENT_MODE_CONTROLLER_ASSESSMENT_DISABLED  0x00
#define QAPI_BLE_HCI_AFH_CHANNEL_ASSESSMENT_MODE_CONTROLLER_ASSESSMENT_ENABLED   0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Extended Inquiry Response FEC_Required defined values (Version 2.1*/
   /* + EDR).                                                           */
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_FEC_NOT_REQUIRED                  0x00
#define QAPI_BLE_HCI_EXTENDED_INQUIRY_RESPONSE_FEC_REQUIRED                      0x01

   /* The following Constants represent the defined Bluetooth HCI Simple*/
   /* Pairing Modes (Version 2.1 + EDR).                                */
#define QAPI_BLE_HCI_SIMPLE_PAIRING_MODE_NOT_ENABLED                             0x00
#define QAPI_BLE_HCI_SIMPLE_PAIRING_MODE_ENABLED                                 0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* minimum and maximum Inquiry Transmit Power values - TX_Power in   */
   /* dBm (Version 2.1 + EDR).                                          */
#define QAPI_BLE_HCI_INQUIRY_TRANSMIT_POWER_MINIMUM                              (-70)
#define QAPI_BLE_HCI_INQUIRY_TRANSMIT_POWER_MAXIMUM                              (20)

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Keypress Notification Types that are used with Keypress           */
   /* Notification (Version 2.1 + EDR).                                 */
#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_ENTRY_STARTED            0x00
#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_DIGIT_ENTERED            0x01
#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_DIGIT_ERASED             0x02
#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_CLEARED                  0x03
#define QAPI_BLE_HCI_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_ENTRY_COMPLETED          0x04

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Erroneous Data Reporting Flags (Version 2.1 + EDR).               */
#define QAPI_BLE_HCI_ERRONEOUS_DATA_REPORTING_NOT_ENABLED                        0x00
#define QAPI_BLE_HCI_ERRONEOUS_DATA_REPORTING_ENABLED                            0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Enhanced Flush Packet Types (Version 2.1 + EDR).                  */
#define QAPI_BLE_HCI_ENHANCED_FLUSH_PACKET_TYPE_AUTOMATICALLY_FLUSHABLE          0x00

   /* The following constants represent the defined Bluetooth HCI       */
   /* Regulation Location Domain Aware options that are used with the   */
   /* Location Domain HCI Commands/Events (Version 3.0 + HS).           */
#define QAPI_BLE_HCI_LOCATION_DOMAIN_REGULATORY_DOMAIN_UNKNOWN                   0x00
#define QAPI_BLE_HCI_LOCATION_DOMAIN_REGULATORY_DOMAIN_KNOWN                     0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Location Domain Country Code Suffixes (Version 3.0 + HS).         */
   /* * NOTE * Country Codes are defined in the in ISO 3166-1           */
   /*          specification.                                           */
#define QAPI_BLE_HCI_LOCATION_DOMAIN_COUNTRY_CODE_SUFFIX_ENTIRE_COUNTRY          0x20
#define QAPI_BLE_HCI_LOCATION_DOMAIN_COUNTRY_CODE_SUFFIX_OUTDOORS_ONLY           0x4F
#define QAPI_BLE_HCI_LOCATION_DOMAIN_COUNTRY_CODE_SUFFIX_INDOORS_ONLY            0x49
#define QAPI_BLE_HCI_LOCATION_DOMAIN_COUNTRY_CODE_SUFFIX_NON_COUNTRY_ENTITY      0x58

   /* The following constants represent the defined Bluetooth HCI       */
   /* Location Domaing Options that are used with the Regulation Domain */
   /* HCI Commands/Events (Version 3.0 + HS).                           */
#define QAPI_BLE_HCI_LOCATION_DOMAIN_OPTIONS_NOT_MAINS_POWERED                   0x00
#define QAPI_BLE_HCI_LOCATION_DOMAIN_OPTIONS_MAINS_POWERED                       0x01

   /* The following constants represent the defined Bluetooth HCI Data  */
   /* Flow Control mechanisms (BR/EDR/AMP) that are used with the       */
   /* various HCI commands/events (Version 3.0 + HS).                   */
#define QAPI_BLE_HCI_FLOW_CONTROL_MODE_PACKET_BASED_DATA_FLOW_CONTROL            0x00
#define QAPI_BLE_HCI_FLOW_CONTROL_MODE_DATA_BLOCK_BASED_DATA_FLOW_CONTROL        0x01

   /* The following constants represent the defined Bluetooth HCI       */
   /* Enhanced Transmit Power Level Types (BR/EDR/AMP) that are used    */
   /* with the various HCI commands/events (Version 3.0 + HS).          */
#define QAPI_BLE_HCI_ENHANCED_TRANSMIT_POWER_LEVEL_TYPE_CURRENT_LEVEL            0x00
#define QAPI_BLE_HCI_ENHANCED_TRANSMIT_POWER_LEVEL_TYPE_MAXIMUM__LEVEL           0x01

   /* The following Constants represent the defined Bluetooth HCI       */
   /* minimum and maximum Enhanced Transmit Power values in dBm (Version*/
   /* 3.0 + HS).                                                        */
#define QAPI_BLE_HCI_ENHANCED_TRANSMIT_POWER_LEVEL_MINIMUM                      (-100)
#define QAPI_BLE_HCI_ENHANCED_TRANSMIT_POWER_LEVEL_MAXIMUM                      (20

   /* The following Constants represent the defined Bluetooth HCI       */
   /* minimum and maximum Best Effort Flush Timeout values in           */
   /* microseconds (Version 3.0 + HS).                                  */
#define QAPI_BLE_HCI_BEST_EFFORT_FLUSH_TIMEOUT_MINIMUM                          0x00000000L
#define QAPI_BLE_HCI_BEST_EFFORT_FLUSH_TIMEOUT_MAXIMUM                          0xFFFFFFFFL

   /* The following constants represent the minimum and maxium size (in */
   /* bytes) of a valid Link Key for a Physical Link (Version 3.0 + HS).*/
#define QAPI_BLE_HCI_PHYSICAL_LINK_QAPI_BLE_LINK_KEY_SIZE_MINIMUM                         0x01
#define QAPI_BLE_HCI_PHYSICAL_LINK_QAPI_BLE_LINK_KEY_SIZE_MAXIMUM                         0x20

   /* The following constants represent the valid Physical Link Link Key*/
   /* types that are valid for Physical Link Keys (Version 3.0 + HS).   */
#define QAPI_BLE_HCI_PHYSICAL_LINK_LINK_KEY_TYPE_DEBUG_COMBINATION_KEY           0x03
#define QAPI_BLE_HCI_PHYSICAL_LINK_LINK_KEY_TYPE_UNAUTHENTICATED_COMBINATION_KEY 0x04
#define QAPI_BLE_HCI_PHYSICAL_LINK_LINK_KEY_TYPE_AUTHENTICATED_COMBINATION_KEY   0x05

   /* The following constants represent the valid values for enabling   */
   /* and disabling Short Range Mode (Version 3.0 + HS).                */
#define QAPI_BLE_HCI_SHORT_RANGE_MODE_DISABLED                                   0x00
#define QAPI_BLE_HCI_SHORT_RANGE_MODE_ENABLED                                    0x01

   /* The following constants represent the valid AMP Status's used with*/
   /* the HCI_Read_Local_AMP_Info command (Version 3.0 + HS).           */
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_AVAILABLE_RADIO_POWERED_DOWN             0x00
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_AVAILABLE_BLUETOOTH_TECHNOLOGY_ONLY      0x01
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_NO_CAPICITY_FOR_BLUETOOTH_OPERATION      0x02
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_LOW_CAPICITY_FOR_BLUETOOTH_OPERATION     0x03
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_MEDIUM_CAPICITY_FOR_BLUETOOTH_OPERATION  0x04
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_HIGH_CAPICITY_FOR_BLUETOOTH_OPERATION    0x05
#define QAPI_BLE_HCI_AMP_STATUS_AMP_STATUS_FULL_CAPICITY_FOR_BLUETOOTH_OPERATION    0x06

   /* The following constants represent the valid AMP Controller types  */
   /* used with the HCI_Read_Local_AMP_Info command (Version 3.0 + HS). */
#define QAPI_BLE_HCI_AMP_CONTROLLER_TYPE_CONTROLLER_TYPE_BR_EDR                  0x00
#define QAPI_BLE_HCI_AMP_CONTROLLER_TYPE_CONTROLLER_TYPE_802_11                  0x01

   /* The following constants represent the currently defined PAL       */
   /* Capabilities Bit Mask values used with the PAL Capabilities with  */
   /* the HCI_Read_Local_AMP_Info command (Version 3.0 + HS).           */
#define QAPI_BLE_HCI_AMP_PAL_CAPABILITIES_SERVICE_TYPE_NOT_GUARANTEED_BIT_VALUE  0x00
#define QAPI_BLE_HCI_AMP_PAL_CAPABILITIES_SERVICE_TYPE_GUARANTEED_BIT_VALUE      0x01

   /* The following constant represents the maximum fragment size that  */
   /* can be specified when reading/writing ASSOC Fragments that are    */
   /* part of the entire ASSOC information.                             */
#define QAPI_BLE_HCI_AMP_ASSOC_FRAGMENT_SIZE_MAXIMUM_FRAGMENT_SIZE               0xF8

   /* The following constants represent the Enable values that can be   */
   /* specified when Enabling AMP Receiver Reports (Version 3.0 + HS).  */
#define QAPI_BLE_HCI_AMP_ENABLE_RECEIVER_REPORTS_DISABLED                        0x00
#define QAPI_BLE_HCI_AMP_ENABLE_RECEIVER_REPORTS_ENABLED                         0x01

   /* The following constants represent the Reason values that can be   */
   /* specified with the AMP Receiver Report Event (Version 3.0 + HS).  */
#define QAPI_BLE_HCI_AMP_RECEIVER_REPORT_REASON_CONFIGURED_INTERVAL_REPORT       0x00
#define QAPI_BLE_HCI_AMP_RECEIVER_REPORT_REASON_TEST_ENDED_REPORT                0x01

   /* The following constants represent the Event_Type values that can  */
   /* be specified with the AMP Receiver Report Event (Version 3.0 +    */
   /* HS).                                                              */
#define QAPI_BLE_HCI_AMP_RECEIVER_REPORT_EVENT_TYPE_FRAMES_RECEIVED_REPORT             0x00
#define QAPI_BLE_HCI_AMP_RECEIVER_REPORT_EVENT_TYPE_FRAMES_RECEIVED_BIT_ERRORS_REPORT  0x01

   /* The following constant represents the minumum fragment size that  */
   /* is to be used to specify an ASSOC Fragment of the entire ASSOC    */
   /* information.  This value is the minumum required size for ALL but */
   /* the Last fragment.  The last fragment can be any size.  In other  */
   /* words all fragments must be greater than or equal to this size    */
   /* except for the last fragement.                                    */
#define QAPI_BLE_HCI_AMP_ASSOC_FRAGMENT_SIZE_MINUMUM_ALL_BUT_LAST_FRAGEMENT      0xF8

   /* The following constants represent the Bluetooth Low Energy (LE)   */
   /* Host supported values that are used to inform the Host Controller */
   /* whether or not a Bluetooth Low Energy (LE) Host is supported      */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_SUPPORTED_HOST_LE_SUPPORTED_HOST_DISABLED                0x00
#define QAPI_BLE_HCI_LE_SUPPORTED_HOST_LE_SUPPORTED_HOST_ENABLED                 0x01

   /* The following constants represent the Bluetooth Low Energy (LE)   */
   /* Host Simultaneous supported values that are used to inform the    */
   /* Host Controller whether or not a Bluetooth Low Energy (LE) Host   */
   /* and Bluetooth BR/EDR is supported simulatenously (Version 4.0 +   */
   /* LE).                                                              */
#define QAPI_BLE_HCI_SIMULTANEOUS_LE_HOST_SUPPORTED_DISABLED                     0x00
#define QAPI_BLE_HCI_SIMULTANEOUS_LE_HOST_SUPPORTED_ENABLED                      0x01

   /* The following constants represent the MWS Channel Enables values  */
   /* that can be specified with the Set MWS Channel Parameters command */
   /* (Version 4.0 + CSA3).                                             */
#define QAPI_BLE_HCI_MWS_CHANNEL_ENABLE_CHANNEL_DISABLED                         0x00
#define QAPI_BLE_HCI_MWS_CHANNEL_ENABLE_CHANNEL_ENABLED                          0x01

   /* The following constants represent the MWS Period Type values that */
   /* can be specified with the Set External Frame Configuration command*/
   /* (Version 4.0 + CSA3).                                             */
#define QAPI_BLE_HCI_MWS_PERIOD_TYPE_DOWNLINK                                    0x00
#define QAPI_BLE_HCI_MWS_PERIOD_TYPE_UPLINK                                      0x01
#define QAPI_BLE_HCI_MWS_PERIOD_TYPE_BIDIRECTIONAL                               0x02
#define QAPI_BLE_HCI_MWS_PERIOD_TYPE_GUARD_PERIOD                                0x03

   /* The following constants represent the MWS PATTERN Interval Type   */
   /* values that can be specified with the Set MWS PATTERN             */
   /* Configuration command (Version 4.0 + CSA3).                       */
#define QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_RX_NOT_ALLOWED                 0x00
#define QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_ALLOWED                        0x01
#define QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_RX_ALLOWED                        0x02
#define QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_RX_ALLOWED                     0x03
#define QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_INTERVAL_FOR_MWS_FRAME            0x04

   /* The following constants represents the MWS Transport Layer values */
   /* that can be specified with the Set MWS Transport Layer command    */
   /* (Version 4.0 + CSA3).                                             */
#define QAPI_BLE_HCI_MWS_TRANSPORT_LAYER_DISABLED                                0x00
#define QAPI_BLE_HCI_MWS_TRANSPORT_LAYER_WCI_1_TRANSPORT                         0x01
#define QAPI_BLE_HCI_MWS_TRANSPORT_LAYER_WCI_2_TRANSPORT                         0x02

   /* The following constants represents the MWS Channel Type values    */
   /* that can be specified with the Set MWS Channel Parameters command */
   /* (Version 4.0 + CSA3).                                             */
#define QAPI_BLE_HCI_MWS_CHANNEL_TYPE_TDD                                        0x00
#define QAPI_BLE_HCI_MWS_CHANNEL_TYPE_FDD                                        0x01

   /* The following constants represents the enable values that may be  */
   /* used with the Set Connectionless Slave Broadcoast and Set         */
   /* Connectionless Slave Broadcast Receive commands (Version 4.0 +    */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_DISABLED                     0x00
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_ENABLED                      0x01

   /* The following constants represents the LPO_Allowed values that may*/
   /* be used with the Set Connectionless Slave Broadcoast and Set      */
   /* Connectionless Slave Broadcast Receive commands (Version 4.0 +    */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_LPO_NOT_ALLOWED              0x00
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_LPO_ALLOWED                  0x01

   /* The following contstants represent the minimum and maximum values */
   /* that may be used with the Interval values that can be specified   */
   /* with the Set Connectionless Slave Broadcast and Set Connectionless*/
   /* Slave Broadcast Receive commands (Version 4.0 + CSA4).            */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_INTERVAL_MINIMUM             0x0002
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_INTERVAL_MAXIMUM             0xFFFE

   /* The following MACRO is a utility MACRO that is used to determine  */
   /* if the specified Interval value (used with the Set Connectionless */
   /* Slave Broadcast and Set Connectionless Slave Broadcast Receive    */
   /* commands) is valid (Version 4.0 + CSA4).                          */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_INTERVAL_VALID(_x)           ((((_x) >= QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_INTERVAL_MINIMUM) && ((_x) <= QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_INTERVAL_MAXIMUM)) && (!((_x) & 0x0001)))

   /* The following contstants represent the minimum and maximum values */
   /* that may be used with the CSB Supervision Timeout value that can  */
   /* be specified with the Set Connectionless Slave Broadcast and Set  */
   /* Connectionless Slave Broadcast Receive commands (Version 4.0 +    */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_SUPERVISION_TIMEOUT_MINIMUM  0x0002
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_SUPERVISION_TIMEOUT_MAXIMUM  0xFFFE

   /* The following MACRO is a utility MACRO that is used to determine  */
   /* if the specified CSB Supervision Timeout value (used with the Set */
   /* Connectionless Slave Broadcast and Set Connectionless Slave       */
   /* Broadcast Receive commands) is valid (Version 4.0 + CSA4).        */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_SUPERVISION_TIMEOUT_VALID(_x) ((((_x) >= QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_SUPERVISION_TIMEOUT_MINIMUM) && ((_x) <= QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_BROADCAST_SUPERVISION_TIMEOUT_MAXIMUM)) && (!((_x) & 0x00000001)))

   /* The following contstants represent the minimum and maximum values */
   /* that may be used with the LT_ADDR value that can be specified with*/
   /* various HCI Commands (Version 4.0 + CSA4).                        */
#define QAPI_BLE_HCI_LT_ADDR_MINIMUM                                             0x01
#define QAPI_BLE_HCI_LT_ADDR_MAXIMUM                                             0x07

   /* The following constants represent the Fragment values that can be */
   /* specified with the Set Connectionlesss Slave Broadcast Data       */
   /* command (Version 4.0 + CSA4).                                     */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_CONTINUATION_FRAGMENT             0x00
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_STARTING_FRAGMENT                 0x01
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_ENDING_FRAGMENT                   0x02
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_SINGLE_FRAGMENT                   0x03

   /* The following contstants represent the minimum and maximum values */
   /* that may be used with the Sync Train Interval values that can be  */
   /* specified with the Read and Write Synchronization Train Parameters*/
   /* commands (Version 4.0 + CSA4).                                    */
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_INTERVAL_MINIMUM                      0x0020
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_INTERVAL_MAXIMUM                      0xFFFE

   /* The following MACRO is a utility MACRO that is used to determine  */
   /* if the specified Synchronization Train Interval value (used with  */
   /* the Read and Write Synchronization Train Parameters commands) is  */
   /* valid (Version 4.0 + CSA4).                                       */
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_INTERVAL_VALID(_x)                   ((((_x) >= QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_INTERVAL_MINIMUM) && ((_x) <= QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_INTERVAL_MAXIMUM)) && (!((_x) & 0x0001)))

   /* The following contstants represent the minimum and maximum values */
   /* that may be used with the Synchronization Train Timeout values    */
   /* that can be specified with the Read and Write Synchronization     */
   /* Train Parameters commands (Version 4.0 + CSA4).                   */
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_TIMEOUT_MINIMUM                       0x00000002
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_TIMEOUT_MAXIMUM                       0x07FFFFFE

   /* The following MACRO is a utility MACRO that is used to determine  */
   /* if the specified Synchronization Train Timeout value (used with   */
   /* the Read and Write Synchronization Train Parameters commands) is  */
   /* valid (Version 4.0 + CSA4).                                       */
#define QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_TIMEOUT_VALID(_x)                     ((((_x) >= QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_TIMEOUT_MINIMUM) && ((_x) <= QAPI_BLE_HCI_SYNCHRONIZATION_TRAIN_TIMEOUT_MAXIMUM)) && (!((_x) & 0x00000001)))

   /* The following constants represent the Enable values that can be   */
   /* specified with the Set Triggered Clock Capture command (Version   */
   /* 4.0 + CSA4).                                                      */
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_DISABLED                            0x00
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_ENABLED                             0x01

   /* The following constants represent the LPO_Allowed values that can */
   /* be specified with the Set Triggered Clock Capture command (Version*/
   /* 4.0 + CSA4).                                                      */
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_LPO_NOT_ALLOWED                     0x00
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_LPO_ALLOWED                         0x01

   /* The following contants represent the minimum and maximum value of */
   /* the Slot_Offset member of the Triggered Clock Capture Event.      */
   /* (Version 4.0 + CSA4).                                             */
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_EVENT_SLOT_OFFSET_MINIMUM           0
#define QAPI_BLE_HCI_TRIGGERED_CLOCK_CAPTURE_EVENT_SLOT_OFFSET_MAXIMUM           1249

   /* The following contants represent the possile Receive Status of the*/
   /* Connectionless Slave Broadcast Receive Event.  (Version 4.0 +     */
   /* CSA4).                                                            */
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_RECEIVE_STATUS_SUCCESS            0x00
#define QAPI_BLE_HCI_CONNECTIONLESS_SLAVE_DATA_RECEIVE_STATUS_RECEIVE_ERROR      0x01

   /* The following constants represent the Bluetooth Host supported    */
   /* values that are used to inform the Host Controller whether or not */
   /* a Bluetooth Host supports the Secure Connections feature for      */
   /* BR/EDR (Version 4.1).                                             */
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_HOST_SUPPORTED_DISABLED                  0x00
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_HOST_SUPPORTED_ENABLED                   0x01

   /* The following Constants represent the defined Bluetooth HCI Secure*/
   /* Connections Modes (Version 4.1).                                  */
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_NOT_ENABLED                              0x00
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_ENABLED                                  0x01

   /* The following constants represent the DM1 ACL-U Mode values that  */
   /* can be specified with the Write Secure Connections Test Mode      */
   /* command (Version 4.1).                                            */
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_DM1_ACLU_MODE_DISABLED                   0x00
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_DM1_ACLU_MODE_ENABLED                    0x01

   /* The following constants represent the eSCO Loopback Mode values   */
   /* that can be specified with the Write Secure Connections Test Mode */
   /* command (Version 4.1).                                            */
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_ESCO_LOOPBACK_MODE_DISABLED              0x00
#define QAPI_BLE_HCI_SECURE_CONNECTIONS_ESCO_LOOPBACK_MODE_ENABLED               0x01

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the SUPPORTED_COMMANDS MACRO's (Set/Reset/Test).     */
   /* These Constants are used as the second parameter in those MACRO's */
   /* to specify the correct Supported Command in the Supported_Commands*/
   /* Mask (Version 4.2).                                               */
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_INQUIRY_BIT_NUMBER                                                0x0000
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_INQUIRY_CANCEL_BIT_NUMBER                                         0x0001
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_PERIODIC_INQUIRY_MODE_BIT_NUMBER                                  0x0002
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_EXIT_PERIODIC_INQUIRY_MODE_BIT_NUMBER                             0x0003
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CREATE_CONNECTION_BIT_NUMBER                                      0x0004
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_DISCONNECT_BIT_NUMBER                                             0x0005
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ADD_SCO_CONNECTION_BIT_NUMBER                                     0x0006
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CANCEL_CREATE_CONNECTION_BIT_NUMBER                               0x0007
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ACCEPT_CONNECTION_REQUEST_BIT_NUMBER                              0x0008
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REJECT_CONNECTION_REQUEST_BIT_NUMBER                              0x0009
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LINK_KEY_REQUEST_BIT_NUMBER                                       0x000A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LINK_KEY_REQUEST_NEGATIVE_REPLY_BIT_NUMBER                        0x000B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_PIN_CODE_REQUEST_BIT_NUMBER                                       0x000C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_PIN_CODE_REQUEST_NEGATIVE_REPLY_BIT_NUMBER                        0x000D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CHANGE_CONNECTION_PACKET_TYPE_BIT_NUMBER                          0x000E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_AUTHENTICATION_REQUEST_BIT_NUMBER                                 0x000F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_CONNECTION_ENCRYPTION_BIT_NUMBER                              0x0010
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CHANGE_CONNECTION_LINK_KEY_BIT_NUMBER                             0x0011
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_MASTER_LINK_KEY_BIT_NUMBER                                        0x0012
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REMOTE_NAME_REQUEST_BIT_NUMBER                                    0x0013
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CANCEL_REMOTE_NAME_REQUEST_BIT_NUMBER                             0x0014
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_REMOTE_SUPPORTED_FEATURES_BIT_NUMBER                         0x0015
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_REMOTE_EXTENDED_FEATURES_BIT_NUMBER                          0x0016
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_REMOTE_VERSION_INFORMATION_BIT_NUMBER                        0x0017
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_CLOCK_OFFSET_BIT_NUMBER                                      0x0018
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LMP_HANDLE_BIT_NUMBER                                        0x0019
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_HOLD_MODE_BIT_NUMBER                                              0x0021
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SNIFF_MODE_BIT_NUMBER                                             0x0022
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_EXIT_SNIFF_MODE_BIT_NUMBER                                        0x0023
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_PARK_STATE_BIT_NUMBER                                             0x0024
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_EXIT_PARK_STATE_BIT_NUMBER                                        0x0025
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_QOS_SETUP_BIT_NUMBER                                              0x0026
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ROLE_DISCOVERY_BIT_NUMBER                                         0x0027
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SWITCH_ROLE_BIT_NUMBER                                            0x0028
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LINK_POLICY_BIT_NUMBER                                       0x0029
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LINK_POLICY_BIT_NUMBER                                      0x002A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_DEFAULT_LINK_POLICY_BIT_NUMBER                               0x002B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_DEFAULT_LINK_POLICY_BIT_NUMBER                              0x002C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_FLOW_SPECIFICATION_BIT_NUMBER                                     0x002D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_EVENT_MASK_BIT_NUMBER                                         0x002E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_RESET_BIT_NUMBER                                                  0x002F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_EVENT_FILTER_BIT_NUMBER                                       0x0030
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_FLUSH_BIT_NUMBER                                                  0x0031
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PIN_TYPE_BIT_NUMBER                                          0x0032
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PIN_TYPE_BIT_NUMBER                                         0x0033
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CREATE_NEW_UNIT_KEY_BIT_NUMBER                                    0x0034
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_STORED_LINK_KEY_BIT_NUMBER                                   0x0035
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_STORED_LINK_KEY_BIT_NUMBER                                  0x0036
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_DELETE_STORED_LINK_KEY_BIT_NUMBER                                 0x0037
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LOCAL_NAME_BIT_NUMBER                                       0x0038
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_NAME_BIT_NUMBER                                        0x0039
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_CONNECTION_ACCEPT_TIMEOUT_BIT_NUMBER                         0x003A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_CONNECTION_ACCEPT_TIMEOUT_BIT_NUMBER                        0x003B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PAGE_TIMEOUT_BIT_NUMBER                                      0x003C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PAGE_TIMEOUT_BIT_NUMBER                                     0x003D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_SCAN_ENABLE_BIT_NUMBER                                       0x003E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SCAN_ENABLE_BIT_NUMBER                                      0x003F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PAGE_SCAN_ACTIVITY_BIT_NUMBER                                0x0040
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PAGE_SCAN_ACTIVITY_BIT_NUMBER                               0x0041
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_INQUIRY_SCAN_ACTIVITY_BIT_NUMBER                             0x0042
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_INQUIRY_SCAN_ACTIVITY_BIT_NUMBER                            0x0043
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_AUTHENTICATION_ENABLE_BIT_NUMBER                             0x0044
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_AUTHENTICATION_ENABLE_BIT_NUMBER                            0x0045
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_ENCRYPTION_MODE_BIT_NUMBER                                   0x0046
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_ENCRYPTION_MODE_BIT_NUMBER                                  0x0047
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_CLASS_OF_DEVICE_BIT_NUMBER                                   0x0048
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_CLASS_OF_DEVICE_BIT_NUMBER                                  0x0049
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_VOICE_SETTING_BIT_NUMBER                                     0x004A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_VOICE_SETTING_BIT_NUMBER                                    0x004B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_AUTOMATIC_FLUSH_TIMEOUT_BIT_NUMBER                           0x004C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_AUTOMATIC_FLUSH_TIMEOUT_BIT_NUMBER                          0x004D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_NUM_BROADCAST_RETRANSMISSIONS_BIT_NUMBER                     0x004E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_NUM_BROADCAST_RETRANSMISSIONS_BIT_NUMBER                    0x004F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_HOLD_MODE_ACTIVITY_BIT_NUMBER                                0x0050
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_HOLD_MODE_ACTIVITY_BIT_NUMBER                               0x0051
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_TRANSMIT_POWER_LEVEL_BIT_NUMBER                              0x0052
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE_BIT_NUMBER                   0x0053
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE_BIT_NUMBER                  0x0054
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL_BIT_NUMBER               0x0055
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_HOST_BUFFER_SIZE_BIT_NUMBER                                       0x0056
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_HOST_NUMBER_OF_COMPLETED_PACKETS_BIT_NUMBER                       0x0057
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LINK_SUPERVISION_TIMEOUT_BIT_NUMBER                          0x0058
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LINK_SUPERVISION_TIMEOUT_BIT_NUMBER                         0x0059
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_NUMBER_SUPPORTED_IAC_BIT_NUMBER                              0x005A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_CURRENT_IAC_LAP_BIT_NUMBER                                   0x005B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_CURRENT_IAC_LAP_BIT_NUMBER                                  0x005C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PAGE_SCAN_PERIOD_MODE_BIT_NUMBER                             0x005D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PAGE_SCAN_PERIOD_MODE_BIT_NUMBER                            0x005E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PAGE_SCAN_MODE_BIT_NUMBER                                    0x005F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PAGE_SCAN_MODE_BIT_NUMBER                                   0x0060
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_AFH_CHANNEL_CLASSIFICATION_BIT_NUMBER                         0x0061
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_INQUIRY_SCAN_TYPE_BIT_NUMBER                                 0x0064
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_INQUIRY_SCAN_TYPE_BIT_NUMBER                                0x0065
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_INQUIRY_MODE_BIT_NUMBER                                      0x0066
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_INQUIRY_MODE_BIT_NUMBER                                     0x0067
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_PAGE_SCAN_TYPE_BIT_NUMBER                                    0x0068
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_PAGE_SCAN_TYPE_BIT_NUMBER                                   0x0069
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_AFH_CHANNEL_ASSESSMENT_MODE_BIT_NUMBER                       0x006A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_AFH_CHANNEL_ASSESSMENT_MODE_BIT_NUMBER                      0x006B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_VERSION_INFORMATION_BIT_NUMBER                         0x0073
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_SUPPORTED_FEATURES_BIT_NUMBER                          0x0075
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_EXTENDED_FEATURES_BIT_NUMBER                           0x0076
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_BUFFER_SIZE_BIT_NUMBER                                       0x0077
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_COUNTRY_CODE_BIT_NUMBER                                      0x0078
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_BD_ADDR_BIT_NUMBER                                           0x0079
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_FAILED_CONTACT_COUNT_BIT_NUMBER                              0x007A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_RESET_FAILED_CONTACT_COUNT_BIT_NUMBER                             0x007B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_GET_LINK_QUALITY_BIT_NUMBER                                       0x007C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_RSSI_BIT_NUMBER                                              0x007D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_AFH_CHANNEL_MAP_BIT_NUMBER                                   0x007E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_CLOCK_BIT_NUMBER                                             0x007F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOOPBACK_MODE_BIT_NUMBER                                     0x0080
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LOOPBACK_MODE_BIT_NUMBER                                    0x0081
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ENABLE_DEVICE_UNDER_TEST_MODE_BIT_NUMBER                          0x0082
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SETUP_SYNCHRONOUS_CONNECTION_BIT_NUMBER                           0x0083
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ACCEPT_SYNCHRONOUS_CONNECTION_BIT_NUMBER                          0x0084
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REJECT_SYNCHRONOUS_CONNECTION_BIT_NUMBER                          0x0085
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_EXTENDED_INQUIRY_RESPONSE_BIT_NUMBER                         0x0088
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_EXTENDED_INQUIRY_RESPONSE_BIT_NUMBER                        0x0089
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REFRESH_ENCRYPTION_KEY_BIT_NUMBER                                 0x008A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SNIFF_SUBRATING_BIT_NUMBER                                        0x008C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_SIMPLE_PAIRING_MODE_BIT_NUMBER                               0x008D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SIMPLE_PAIRING_MODE_BIT_NUMBER                              0x008E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_OOB_DATA_BIT_NUMBER                                    0x008F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_BIT_NUMBER                   0x0090
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_INQUIRY_TRANSMIT_POWER_LEVEL_BIT_NUMBER                     0x0091
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_DEFAULT_ERRONEOUS_DATA_REPORTING_BIT_NUMBER                  0x0092
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING_BIT_NUMBER                 0x0093
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_IO_CAPABILITY_REQUEST_REPLY_BIT_NUMBER                            0x0097
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_USER_CONFIRMATION_REQUEST_REPLY_BIT_NUMBER                        0x0098
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY_BIT_NUMBER               0x0099
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_USER_PASSKEY_REQUEST_REPLY_BIT_NUMBER                             0x009A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_USER_PASSKEY_REQUEST_NEGATIVE_REPLY_BIT_NUMBER                    0x009B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REMOTE_OOB_DATA_REQUEST_REPLY_BIT_NUMBER                          0x009C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SIMPLE_PAIRING_DEBUG_MODE_BIT_NUMBER                        0x009D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ENHANCED_FLUSH_BIT_NUMBER                                         0x009E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY_BIT_NUMBER                 0x009F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SEND_KEYPRESS_NOTIFICATION_BIT_NUMBER                             0x00A2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_IO_CAPABILITIES_RESPONSE_NEGATIVE_REPLY_BIT_NUMBER                0x00A3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_ENCRYPTION_KEY_SIZE_BIT_NUMBER                               0x00A4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CREATE_PHYSICAL_LINK_BIT_NUMBER                                   0x00A8
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ACCEPT_PHYSICAL_LINK_BIT_NUMBER                                   0x00A9
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_DISCONNECT_PHYSICAL_LINK_BIT_NUMBER                               0x00AA
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_CREATE_LOGICAL_LINK_BIT_NUMBER                                    0x00AB
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ACCEPT_LOGICAL_LINK_BIT_NUMBER                                    0x00AC
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_DISCONNECT_LOGICAL_LINK_BIT_NUMBER                                0x00AD
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LOGICAL_LINK_CANCEL_BIT_NUMBER                                    0x00AE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_FLOW_SPEC_MODIFY_BIT_NUMBER                                       0x00AF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_BIT_NUMBER                       0x00B0
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_BIT_NUMBER                      0x00B1
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_EVENT_MASK_PAGE_2_BIT_NUMBER                                  0x00B2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCATION_DATA_BIT_NUMBER                                     0x00B3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LOCATION_DATA_BIT_NUMBER                                    0x00B4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_AMP_INFO_BIT_NUMBER                                    0x00B5
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_AMP_ASSOC_BIT_NUMBER                                   0x00B6
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_REMOTE_AMP_ASSOC_BIT_NUMBER                                 0x00B7
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_FLOW_CONTROL_MODE_BIT_NUMBER                                 0x00B8
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_FLOW_CONTROL_MODE_BIT_NUMBER                                0x00B9
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_DATA_BLOCK_SIZE_BIT_NUMBER                                   0x00BA
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ENABLE_AMP_RECEIVER_REPORTS_BIT_NUMBER                            0x00BD
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_AMP_TEST_END_BIT_NUMBER                                           0x00BE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_AMP_TEST_COMMAND_BIT_NUMBER                                       0x00BF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_ENHANCED_TRANSMIT_POWER_LEVEL_BIT_NUMBER                     0x00C0
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_BEST_EFFORT_FLUSH_TIMEOUT_BIT_NUMBER                         0x00C2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_BIT_NUMBER                        0x00C3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SHORT_RANGE_MODE_BIT_NUMBER                                       0x00C4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LE_HOST_SUPPORT_BIT_NUMBER                                   0x00C5
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_LE_HOST_SUPPORT_BIT_NUMBER                                  0x00C6
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EVENT_MASK_BIT_NUMBER                                      0x00C8
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_BUFFER_SIZE_BIT_NUMBER                                    0x00C9
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_LOCAL_SUPPORTED_FEATURES_BIT_NUMBER                       0x00CA
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_RANDOM_ADDRESS_BIT_NUMBER                                  0x00CC
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_ADVERTISING_PARAMETERS_BIT_NUMBER                          0x00CD
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_ADVERTISING_CHANNEL_TX_POWER_BIT_NUMBER                   0x00CE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_ADVERTISING_DATA_BIT_NUMBER                                0x00CF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_SCAN_RESPONSE_DATA_BIT_NUMBER                              0x00D0
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_ADVERTISE_ENABLE_BIT_NUMBER                                0x00D1
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_SCAN_PARAMETERS_BIT_NUMBER                                 0x00D2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_SCAN_ENABLE_BIT_NUMBER                                     0x00D3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CREATE_CONNECTION_BIT_NUMBER                                   0x00D4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CREATE_CONNECTION_CANCEL_BIT_NUMBER                            0x00D5
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_WHITE_LIST_SIZE_BIT_NUMBER                                0x00D6
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CLEAR_WHITE_LIST_BIT_NUMBER                                    0x00D7
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ADD_DEVICE_TO_WHITE_LIST_BIT_NUMBER                            0x00D8
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOVE_DEVICE_FROM_WHITE_LIST_BIT_NUMBER                       0x00D9
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CONNECTION_UPDATE_BIT_NUMBER                                   0x00DA
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_HOST_CHANNEL_CLASSIFICATION_BIT_NUMBER                     0x00DB
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_CHANNEL_MAP_BIT_NUMBER                                    0x00DC
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_REMOTE_USED_FEATURES_BIT_NUMBER                           0x00DD
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ENCRYPT_BIT_NUMBER                                             0x00DE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_RAND_BIT_NUMBER                                                0x00DF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_START_ENCRYPTION_BIT_NUMBER                                    0x00E0
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_LONG_TERM_KEY_REQUEST_REPLY_BIT_NUMBER                         0x00E1
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_BIT_NUMBER                0x00E2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_SUPPORTED_STATES_BIT_NUMBER                               0x00E3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_RECEIVER_TEST_BIT_NUMBER                                       0x00E4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_TRANSMITTER_TEST_BIT_NUMBER                                    0x00E5
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_TEST_END_BIT_NUMBER                                            0x00E6
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ENHANCED_SETUP_SYNCHRONOUS_CONNECTION_BIT_NUMBER                  0x00EB
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_ENHANCED_ACCEPT_SYNCHRONOUS_CONNECTION_BIT_NUMBER                 0x00EC
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_SUPPORTED_CODECS_BIT_NUMBER                            0x00ED
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_MWS_CHANNEL_PARAMETERS_COMMAND_BIT_NUMBER                     0x00EE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_EXTERNAL_FRAME_CONFIGURATION_COMMAND_BIT_NUMBER               0x00EF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_MWS_SIGNALING_COMMAND_BIT_NUMBER                              0x00F0
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_MWS_TRANSPORT_LAYER_COMMAND_BIT_NUMBER                        0x00F1
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_MWS_SCAN_FREQUENCY_TABLE_COMMAND_BIT_NUMBER                   0x00F2
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_GET_TRANSPORT_LAYER_CONFIGURATION_COMMAND_BIT_NUMBER              0x00F3
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_MWS_PATTERN_CONFIGURATION_COMMAND_BIT_NUMBER                  0x00F4
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_TRIGGERED_CLOCK_CAPTURE_BIT_NUMBER                            0x00F5
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_TRUNCATED_PAGE_BIT_NUMBER                                         0x00F6
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_TRUNCATED_PAGE_CANCEL_BIT_NUMBER                                  0x00F7
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_CONNECTIONLESS_SLAVE_BROADCAST_BIT_NUMBER                     0x00F8
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_CONNECTIONLESS_SLAVE_BROADCAST_RECEIVE_BIT_NUMBER             0x00F9
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_START_SYNCHRONIZATION_TRAIN_BIT_NUMBER                            0x00FA
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_RECEIVE_SYNCHRONIZATION_TRAIN_BIT_NUMBER                          0x00FB
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_RESERVED_LT_ADDR_BIT_NUMBER                                   0x00FC
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_DELETE_RESERVED_LT_ADDR_BIT_NUMBER                                0x00FD
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_SET_CONNECTIONLESS_SLAVE_BROADCAST_DATA_BIT_NUMBER                0x00FE
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_SYNCHRONIZATION_TRAIN_PARAMETERS_BIT_NUMBER                  0x00FF
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SYNCHRONIZATION_TRAIN_PARAMETERS_BIT_NUMBER                 0x0100
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_REMOTE_OOB_EXTENDED_DATA_REQUEST_REPLY_BIT_NUMBER                 0x0101
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_SECURE_CONNECTIONS_HOST_SUPPORT_BIT_NUMBER                   0x0102
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SECURE_CONNECTIONS_HOST_SUPPORT_BIT_NUMBER                  0x0103
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_AUTHENTICATED_PAYLOAD_TIMEOUT_BIT_NUMBER                     0x0104
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_AUTHENTICATED_PAYLOAD_TIMEOUT_BIT_NUMBER                    0x0105
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_LOCAL_OOB_EXTENDED_DATA_BIT_NUMBER                           0x0106
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_SECURE_CONNECTIONS_TEST_MODE_BIT_NUMBER                     0x0107
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_EXTENDED_PAGE_TIMEOUT_BIT_NUMBER                             0x0108
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_EXTENDED_PAGE_TIMEOUT_BIT_NUMBER                            0x0109
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_READ_EXTENDED_INQUIRY_LENGTH_BIT_NUMBER                           0x010A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_WRITE_EXTENDED_INQUIRY_LENGTH_BIT_NUMBER                          0x010B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_REPLY_BIT_NUMBER           0x010C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_NEGATIVE_REPLY_BIT_NUMBER  0x010D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_DATA_LENGTH                                                0x010E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_SUGGESTED_DEFAULT_DATA_LENGTH                             0x010F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_WRITE_SUGGESTED_DEFAULT_DATA_LENGTH                            0x0110
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_LOCAL_P256_PUBLIC_KEY                                     0x0111
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_GENERATE_DH_KEY                                                0x0112
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ADD_DEVICE_TO_RESOLVING_LIST                                   0x0113
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST                              0x0114
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CLEAR_RESOLVING_LIST                                           0x0115
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_RESOLVING_LIST_SIZE                                       0x0116
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_PEER_RESOLVABLE_ADDRESS                                   0x0117
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_LOCAL_RESOLVABLE_ADDRESS                                  0x0118
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_ADDRESS_RESOLUTION_ENABLE                                  0x0119
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT                         0x011A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_MAXIMUM_DATA_LENGTH                                       0x011B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_PHY                                                       0x011C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_DEFAULT_PHY                                                0x011D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PHY                                                        0x011E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ENHANCED_RECEIVER_TEST                                         0x011F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ENHANCED_TRANSMITTER_TEST                                      0x0120
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_ADVERTISING_SET_RANDOM_ADDRESS                             0x0121
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_ADVERTISING_PARAMETERS                            0x0122
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_ADVERTISING_DATA                                  0x0123
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_SCAN_RESPONSE_DATA                                0x0124
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_ADVERTISING_ENABLE                                0x0125
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_MAXIMUM_ADVERTISING_DATA_LENGTH                           0x0126
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_NUMBER_OF_SUPPORTED_ADVERTISING_SETS                      0x0127
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOVE_ADVERTISING_SET                                         0x0128
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CLEAR_ADVERTISING_SETS                                         0x0129
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_PARAMETERS                            0x012A
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_DATA                                  0x012B
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_ENABLE                                0x012C
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_SCAN_PARAMETERS                                   0x012D
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_EXTENDED_SCAN_ENABLE                                       0x012E
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_EXTENDED_CREATE_CONNECTION                                     0x012F
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_PERIODIC_ADVERTISING_CREATE_SYNC                               0x0130
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_PERIODIC_ADVERTISING_CREATE_SYNC_CANCEL                        0x0131
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC                            0x0132
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISER_LIST                         0x0133
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISER_LIST                    0x0134
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_CLEAR_PERIODIC_ADVERTISER_LIST                                 0x0135
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_PERIODIC_ADVERTISER_LIST                                  0x0136
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_TRANSMIT_POWER                                            0x0137
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_READ_RF_PATH_COMPENSATION                                      0x0138
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_WRITE_RF_PATH_COMPENSATION                                     0x0139
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PRIVACY_MODE                                               0x013A

#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_BIT_NUMBER              0x0175
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_BIT_NUMBER              0x0176
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_SYNC_SUBEVENT_BIT_NUMBER                          0x0177
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_BIT_NUMBER              0x0179
#define QAPI_BLE_HCI_SUPPORTED_COMMAND_LE_EXTENDED_CREATE_CONNECTION_V2_BIT_NUMBER                       0x0178

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask.         */
   /* * NOTE * Each Page of the Features is 64 bits (0 - 0x3F).  If a   */
   /*          Feature Bit number is larger than 64 bits (0 - 0x3F) then*/
   /*          it exists as an "Extended Feature" and exists on a       */
   /*          non-zero page.  The Page can be found by dividing the bit*/
   /*          number by 64 (or (sizeof(LMP_Feature_t)*8).              */
   /* * NOTE * Constants are provided below to determine the actual Bit */
   /*          Number within a Page                                     */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) and the  */
   /*          divisor to apply to the bit numbers to determine the     */
   /*          correct Page                                             */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_NUMBER_DIVISOR).          */
#define QAPI_BLE_HCI_LMP_FEATURE_PAGE_NUMBER_DIVISOR                             (sizeof(qapi_BLE_LMP_Features_t)*8)
#define QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK                            ((sizeof(qapi_BLE_LMP_Features_t)*8) - 1)

#define QAPI_BLE_HCI_LMP_FEATURE_THREE_SLOT_PACKETS_BIT_NUMBER                   0x00
#define QAPI_BLE_HCI_LMP_FEATURE_FIVE_SLOT_PACKETS_BIT_NUMBER                    0x01
#define QAPI_BLE_HCI_LMP_FEATURE_ENCRYPTION_BIT_NUMBER                           0x02
#define QAPI_BLE_HCI_LMP_FEATURE_SLOT_OFFSET_BIT_NUMBER                          0x03
#define QAPI_BLE_HCI_LMP_FEATURE_TIMING_ACCURACY_BIT_NUMBER                      0x04
#define QAPI_BLE_HCI_LMP_FEATURE_SWITCH_BIT_NUMBER                               0x05
#define QAPI_BLE_HCI_LMP_FEATURE_HOLD_MODE_BIT_NUMBER                            0x06
#define QAPI_BLE_HCI_LMP_FEATURE_SNIFF_MODE_BIT_NUMBER                           0x07
#define QAPI_BLE_HCI_LMP_FEATURE_PARK_MODE_BIT_NUMBER                            0x08
#define QAPI_BLE_HCI_LMP_FEATURE_RSSI_BIT_NUMBER                                 0x09
#define QAPI_BLE_HCI_LMP_FEATURE_CHANNEL_QUALITY_DRIVEN_DATA_RATE_BIT_NUMBER     0x0A
#define QAPI_BLE_HCI_LMP_FEATURE_SCO_LINK_BIT_NUMBER                             0x0B
#define QAPI_BLE_HCI_LMP_FEATURE_HV2_PACKETS_BIT_NUMBER                          0x0C
#define QAPI_BLE_HCI_LMP_FEATURE_HV3_PACKETS_BIT_NUMBER                          0x0D
#define QAPI_BLE_HCI_LMP_FEATURE_U_LAW_LOG_BIT_NUMBER                            0x0E
#define QAPI_BLE_HCI_LMP_FEATURE_A_LAW_LOG_BIT_NUMBER                            0x0F
#define QAPI_BLE_HCI_LMP_FEATURE_CVSD_BIT_NUMBER                                 0x10
#define QAPI_BLE_HCI_LMP_FEATURE_PAGING_SCHEME_BIT_NUMBER                        0x11
#define QAPI_BLE_HCI_LMP_FEATURE_POWER_CONTROL_BIT_NUMBER                        0x12

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 1.2).                                                             */
#define QAPI_BLE_HCI_LMP_FEATURE_ROLE_SWITCH_BIT_NUMBER                            0x05
#define QAPI_BLE_HCI_LMP_FEATURE_PARK_STATE_BIT_NUMBER                             0x08
#define QAPI_BLE_HCI_LMP_FEATURE_POWER_CONTROL_REQUESTS_BIT_NUMBER                 0x09
#define QAPI_BLE_HCI_LMP_FEATURE_PAGING_PARAMETER_NEGOTIATION_BIT_NUMBER           0x11
#define QAPI_BLE_HCI_LMP_FEATURE_TRANSPARENT_SYNCHRONOUS_DATA_BIT_NUMBER           0x13
#define QAPI_BLE_HCI_LMP_FEATURE_FLOW_CONTROL_LAG_LEAST_SIGNIFICANT_BIT_BIT_NUMBER 0x14
#define QAPI_BLE_HCI_LMP_FEATURE_FLOW_CONTROL_LAG_MIDDLE_BIT_BIT_NUMBER            0x15
#define QAPI_BLE_HCI_LMP_FEATURE_FLOW_CONTROL_LAG_MOST_SIGNIFICANT_BIT_BIT_NUMBER  0x16
#define QAPI_BLE_HCI_LMP_FEATURE_BROADCAST_ENCRYPTION_BIT_NUMBER                   0x17
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_INQUIRY_SCAN_BIT_NUMBER                  0x1B
#define QAPI_BLE_HCI_LMP_FEATURE_INTERLACED_INQUIRY_SCAN_BIT_NUMBER                0x1C
#define QAPI_BLE_HCI_LMP_FEATURE_INTERLACED_PAGE_SCAN_BIT_NUMBER                   0x1D
#define QAPI_BLE_HCI_LMP_FEATURE_RSSI_WITH_INQUIRY_RESULTS_BIT_NUMBER              0x1E
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_SCO_LINKS_EV3_PACKETS_BIT_NUMBER         0x1F
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_EV4_PACKETS_BIT_NUMBER                   0x20
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_EV5_PACKETS_BIT_NUMBER                   0x21
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_AFH_CAPABLE_SLAVE_BIT_NUMBER             0x23
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_AFH_CLASSIFICATION_SLAVE_BIT_NUMBER      0x24
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_AFH_CAPABLE_MASTER_BIT_NUMBER            0x2B
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_AFH_CLASSIFICATION_MASTER_BIT_NUMBER     0x2C
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_FEATURES_BIT_NUMBER                      0x3F

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 2.0).                                                             */
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_DATA_RATE_ACL_2_MBPS_MODE_BIT_NUMBER     0x19
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_DATA_RATE_ACL_3_MBPS_MODE_BIT_NUMBER     0x1A
#define QAPI_BLE_HCI_LMP_FEATURE_3_SLOT_ENHANCED_DATA_RATE_ACL_PACKETS_BIT_NUMBER  0x27
#define QAPI_BLE_HCI_LMP_FEATURE_5_SLOT_ENHANCED_DATA_RATE_ACL_PACKETS_BIT_NUMBER  0x28
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_DATA_RATE_ESCO_2_MBPS_MODE_BIT_NUMBER    0x2D
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_DATA_RATE_ESCO_3_MBPS_MODE_BIT_NUMBER    0x2E
#define QAPI_BLE_HCI_LMP_FEATURE_3_SLOT_ENHANCED_DATA_RATE_ESCO_PACKETS_BIT_NUMBER 0x2F

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 2.1 + EDR).                                                       */
   /* * NOTE * See note (above) about how to determine the correct Page */
   /*          number for these bits (one of these is on Page 1) and the*/
   /*          actual BIT Number (within the Page) needs to be logical  */
   /*          AND'ed with the Page Bit Mask constant                   */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) to       */
   /*          determine the bit number within the Page.                */
#define QAPI_BLE_HCI_LMP_FEATURE_SNIFF_SUBRATING_BIT_NUMBER                         0x29
#define QAPI_BLE_HCI_LMP_FEATURE_PAUSE_ENCRYPTION_BIT_NUMBER                        0x2A
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_INQUIRY_RESPONSE_BIT_NUMBER               0x30
#define QAPI_BLE_HCI_LMP_FEATURE_SECURE_SIMPLE_PAIRING_BIT_NUMBER                   0x33
#define QAPI_BLE_HCI_LMP_FEATURE_ENCAPSULATED_PDU_BIT_NUMBER                        0x34
#define QAPI_BLE_HCI_LMP_FEATURE_ERRONEOUS_DATA_REPORTING_BIT_NUMBER                0x35
#define QAPI_BLE_HCI_LMP_FEATURE_NON_FLUSHABLE_PACKET_BOUNDARY_FLAG_BIT_NUMBER      0x36
#define QAPI_BLE_HCI_LMP_FEATURE_LINK_SUPERVISION_TIMEOUT_CHANGED_EVENT_BIT_NUMBER  0x38
#define QAPI_BLE_HCI_LMP_FEATURE_INQUIRY_RESPONSE_TX_POWER_LEVEL_BIT_NUMBER         0x39
#define QAPI_BLE_HCI_LMP_FEATURE_EXTENDED_FEATURES_BIT_NUMBER                       0x3F
#define QAPI_BLE_HCI_LMP_FEATURE_SECURE_SIMPLE_PAIRING_HOST_SUPPORT_BIT_NUMBER      0x40

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 3.0 + HS).                                                        */
#define QAPI_BLE_HCI_LMP_FEATURE_ENHANCED_POWER_CONTROL_BIT_NUMBER                  0x3A

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 4.0 + LE).                                                        */
   /* * NOTE * See note (above) about how to determine the correct Page */
   /*          number for these bits (two of these are on Page 1) and   */
   /*          the actual BIT Number (within the Page) needs to be      */
   /*          logical AND'ed with the Page Bit Mask constant           */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) to       */
   /*          determine the bit number within the Page.                */
#define QAPI_BLE_HCI_LMP_FEATURE_BR_EDR_NOT_SUPPORTED_BIT_NUMBER                                0x25
#define QAPI_BLE_HCI_LMP_FEATURE_LE_SUPPORTED_BIT_NUMBER                                        0x26
#define QAPI_BLE_HCI_LMP_FEATURE_SIMULTANEOUS_LE_BR_EDR_TO_SAME_DEVICE_SUPPORTED_BIT_NUMBER     0x31
#define QAPI_BLE_HCI_LMP_FEATURE_LE_SUPPORTED_HOST_BIT_NUMBER                                   0x41
#define QAPI_BLE_HCI_LMP_FEATURE_SIMULTANEOUS_LE_AND_BR_EDR_TO_SAME_DEVICE_CAPABLE_BIT_NUMBER   0x42

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 4.0 + Core Spec Addendum 4).                                      */
   /* * NOTE * See note (above) about how to determine the correct Page */
   /*          number for these bits (these are on Page 2) and the      */
   /*          actual BIT Number (within the Page) needs to be logical  */
   /*          AND'ed with the Page Bit Mask constant                   */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) to       */
   /*          determine the bit number within the Page.                */
#define QAPI_BLE_HCI_LMP_FEATURE_CONNECTIONLESS_SLAVE_BROADCAST_MASTER_OPERATION_BIT_NUMBER     0x80
#define QAPI_BLE_HCI_LMP_FEATURE_CONNECTIONLESS_SLAVE_BROADCAST_SLAVE_OPERATION_BIT_NUMBER      0x81
#define QAPI_BLE_HCI_LMP_FEATURE_SYNCHRONIZATION_TRAIN_BIT_NUMBER                               0x82
#define QAPI_BLE_HCI_LMP_FEATURE_SYNCHRONIZATION_SCAN_BIT_NUMBER                                0x83
#define QAPI_BLE_HCI_LMP_FEATURE_INQUIRY_RESPONSE_NOTIFICATION_EVENT_BIT_NUMBER                 0x84

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 4.1).                                                             */
   /* * NOTE * See note (above) about how to determine the correct Page */
   /*          number for these bits (1 of these is on Page 1, the      */
   /*          others on page 2) and the actual BIT Number (within the  */
   /*          Page) needs to be logical AND'ed with the Page Bit Mask  */
   /*          constant (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) */
   /*          to determine the bit number within the Page.             */
#define QAPI_BLE_HCI_LMP_FEATURE_SECURE_CONNECTIONS_HOST_SUPPORT                                0x43
#define QAPI_BLE_HCI_LMP_FEATURE_GENERALIZED_INTERLACED_SCAN                                    0x85
#define QAPI_BLE_HCI_LMP_FEATURE_COARSE_CLOCK_ADJUSTMENT                                        0x86
#define QAPI_BLE_HCI_LMP_FEATURE_SECURE_CONNECTIONS_CONTROLLER_SUPPORT                          0x88
#define QAPI_BLE_HCI_LMP_FEATURE_PING                                                           0x89
#define QAPI_BLE_HCI_LMP_FEATURE_TRAIN_NUDGING                                                  0x8B

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LMP Feature in the LMP_Features Mask (Version */
   /* 5.0).                                                             */
   /* * NOTE * See note (above) about how to determine the correct Page */
   /*          number for these bits (these are on Page 2) and the      */
   /*          actual BIT Number (within the Page) needs to be logical  */
   /*          AND'ed with the Page Bit Mask constant                   */
   /*          (QAPI_BLE_HCI_LMP_FEATURE_PAGE_BIT_NUMBER_MASK) to       */
   /*          determine the bit number within the Page.                */
#define QAPI_BLE_HCI_LMP_FEATURE_SLOT_AVAILABILITY_MASK                                         0x8A

   /* The following constants are used with the HCI Physical Link Loss  */
   /* Early Warning Event to denote the defined Logical Link Loss       */
   /* Reasons (Version 3.0 + HS).                                       */
#define QAPI_BLE_HCI_LINK_LOSS_REASON_UNKNOWN                                    0x00
#define QAPI_BLE_HCI_LINK_LOSS_REASON_RANGE_RELATED                              0x01
#define QAPI_BLE_HCI_LINK_LOSS_REASON_BANDWIDTH_RELATED                          0x02
#define QAPI_BLE_HCI_LINK_LOSS_REASON_RESOLVING_CONFLICT                         0x03
#define QAPI_BLE_HCI_LINK_LOSS_REASON_INTERFERENCE                               0x04

   /* The following Constants represent the defined Bluetooth HCI       */
   /* PIN Code Length Minimum and Maximum Length Values.                */
#define QAPI_BLE_HCI_PIN_CODE_LENGTH_MINIMUM                                     0x01
#define QAPI_BLE_HCI_PIN_CODE_LENGTH_MAXIMUM                                     0x10

   /* The following Constants represent the defined Bluetooth HCI       */
   /* Version Constants (which also dictates the version of the HCI     */
   /* Specification that this HCI Layer supports).                      */
   /* * NOTE * If a Bluetooth HCI Specification value is NOT listed in  */
   /*          this list then it is NOT supported by the HCI API        */
   /*          present in this file.                                    */
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_1_0B                                  0x00
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_1_1                                   0x01
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_1_2                                   0x02
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_2_0                                   0x03
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_2_1                                   0x04
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_3_0                                   0x05
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_4_0                                   0x06
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_4_1                                   0x07
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_4_2                                   0x08
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_5_0                                   0x09
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_5_1                                   0x0A
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_5_2                                   0x0B
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_5_3                                   0x0C
#define QAPI_BLE_HCI_VERSION_SPECIFICATION_5_4                                   0x0D

   /* The following Constants represent the defined Bluetooth Link      */
   /* Manager Protocol (LMP) Version values for the LMP Version HCI     */
   /* Commands.                                                         */
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_0                                   0x00
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_1                                   0x01
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_2                                   0x02
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_2_0                                   0x03
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_2_1                                   0x04
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_3_0                                   0x05
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_0                                   0x06
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_1                                   0x07
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_2                                   0x08
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_0                                   0x09
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_1                                   0x0A
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_2                                   0x0B
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_3                                   0x0C
#define QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_4                                   0x0D

   /* The following Constants represent the defined Bluetooth Link      */
   /* Manger Protocol LMP_CompID Codes (Manufacturer Names in HCI       */
   /* Command).                                                         */
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ERICSSON_MOBILE_COMMUNICATIONS    0x0000
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NOKIA_MOBILE_PHONES               0x0001
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INTEL_CORPORATION                 0x0002
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_IBM_CORPORATION                   0x0003
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TOSHIBA_CORPORATION               0x0004

   /* The following Constants represent the additional defined          */
   /* Bluetooth Link Manger Protocol LMP_CompID Codes (Manufacturer     */
   /* Names in HCI Command) for Bluetooth Specification after Version   */
   /* 1.1).                                                             */
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_3COM                              0x0005
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MICROSOFT                         0x0006
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LUCENT                            0x0007
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MOTOROLA                          0x0008
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INFINEON_TECHNOLOGIES_AG          0x0009
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CAMBRIDGE_SILICON_RADIO           0x000A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SILICON_WAVE                      0x000B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DIGIANSWER                        0x000C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TEXAS_INSTRUMENTS                 0x000D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PARTHUS_TECHNOLOGIES              0x000E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BROADCOM                          0x000F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MITEL_SEMICONDUCTOR               0x0010
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ZARLINK_SEMICONDUCTOR             0x0010
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WIDCOMM                           0x0011
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TELENCOMM                         0x0012
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ZEEVO                             0x0012
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ATMEL                             0x0013
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MITSUBISHI                        0x0014
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RTX_TELECOM                       0x0015
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KC_TECHNOLOGY                     0x0016
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NEWLOGIC                          0x0017
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TRANSILICA                        0x0018
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ROHDE_AND_SCHWARTZ                0x0019
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TTPCOM                            0x001A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SIGNIA_TECHNOLOGIES               0x001B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CONEXANT_SYSTEMS                  0x001C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM                          0x001D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INVENTEL                          0x001E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AVM_BERLIN                        0x001F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BANDSPEED                         0x0020
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MANSELLA                          0x0021
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NEC                               0x0022
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WAVEPLUS_TECHNOLOGY               0x0023
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ALCATEL                           0x0024
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PHILIPS_SEMICONDUCTORS            0x0025
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_C_TECHNOLOGIES                    0x0026
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_OPEN_INTERFACE                    0x0027
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RF_MICRO_DEVICES                  0x0028
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HITACHI                           0x0029
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SYMBOL_TECHNOLOGIES               0x002A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TENOVIS                           0x002B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MACRONIX_INTERNATIONAL            0x002C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GCT_SEMICONDUCTOR                 0x002D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NORWOOD_SYSTEMS                   0x002E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MEWTEL_TECHNOLOGY                 0x002F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ST_MICROELECTRONICS               0x0030
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SYNOPSYS                          0x0031
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RED_M_COMMUNICATIONS              0x0032
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_COMMIL_LTD                        0x0033
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CATC                              0x0034
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ECLIPSE_SL                        0x0035
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RENESAS_TECHNOLOGY_CORP           0x0036
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MOBILIAN_CORPORATION              0x0037
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TERAX                             0x0038
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INTEGRATED_SYSTEM_SOLUTION        0x0039
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MATSUSHITA                        0x003A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GENNUM_CORPORATION                0x003B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RESEARCH_IN_MOTION                0x003C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_IPEXTREME                         0x003D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SYSTEMS_AND_CHIPS                 0x003E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BLUETOOTH_SIG                     0x003F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SEIKO_EPSON_CORPORATION           0x0040
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INTEGRATED_SILICON_SOLUTION       0x0041
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CONWISE_TECHNOLOGY_CORPORATION    0x0042
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PARROT_SA                         0x0043
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SOCKET_MOBILE                     0x0044
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ATHEROS_COMMUNICATIONS            0x0045
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MEDIATEK_INCORPORATED             0x0046
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BLUEGIGA                          0x0047
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MARVELL_TECHNOLOGY_GROUP          0x0048
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_3DSP_CORPORATION                  0x0049
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ACCEL_SEMICONDUCTOR               0x004A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CONTINENTAL_AUTOMOTIVE_SYSTEMS    0x004B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_APPLE_INCORPORATED                0x004C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STACCATO_COMMUNICATIONS           0x004D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AVAGO_TECHONOLOGIES               0x004E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_APT_LIMITED                       0x004F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SIRF_TECHONOLIGY                  0x0050
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TZERO_TECHNOLOGIES                0x0051
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_J_AND_M_CORPORATION               0x0052
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FREE2MOVE_AB                      0x0053
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_3DIJOY_CORPORATION                0x0054
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PLANTRONICS_INCORPORATED          0x0055
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SONY_ERICSSON_MOBILE_COMM         0x0056
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HARMAN_INTERNATIONAL_IND          0x0057
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VIZIO_INC                         0x0058
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NORDIC_SEMICONDUCTOR_ASA          0x0059
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_EM_MICROELECTRONIC_MARIN_SA       0x005A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RALINK_TECHNOLOGY_CORPORATION     0x005B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BELKIN_INTERNATIONAL_INC          0x005C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_REALTEK_SEMICONDUCTOR_CORP        0x005D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STONESTREET_ONE_LLC               0x005E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WICENTRIC_INC                     0x005F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RIVIERA_WAVES_SAS                 0x0060
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RDA_MICROELECTRONICS              0x0061
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GIBSON_GUITARS                    0x0062
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MICOMMAND_INC                     0x0063
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BAND_XI_INTERNATIONAL_LLC         0x0064
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HEWLETT_PACKARD_COMPANY           0x0065
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_9SOLUTIONS_OY                     0x0066
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GN_NETCOM_AS                      0x0067
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GENERAL_MOTORS                    0x0068
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_A_AND_D_ENGINEERING_INC           0x0069
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MINDTREE_LTD                      0x006A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_POLAR_ELECTRO_OY                  0x006B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BEAUTIFUL_ENTERPRISE_COMPANY      0x006C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BRIARTEK_INC                      0x006D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SUMMIT_DATA_COMMUNICATIONS_INC    0x006E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SOUND_ID                          0x006F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MONSTER_LLC                       0x0070
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CONNECT_BLUE_AB                   0x0071
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SHANGHAI_SUPER_SMART_ELECTRON     0x0072
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GROUP_SENSE_LTD                   0x0073
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ZOMM_LLC                          0x0074
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SAMSUNG_ELECTRONICS_CO_LTD        0x0075
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CREATIVE_TECHNOLOGY_LTD           0x0076
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LAIRD_TECHNOLOGIES                0x0077
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NIKE_INC                          0x0078
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LESSWIRE_AG                       0x0079
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MSTAR_SEMICONDUCTOR_INC           0x007A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HANLYNN_TECHNOLOGIES              0x007B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_A_AND_R_CAMBRIDGE                 0x007C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SEERS_TECHNOLOGY_CO_LTD           0x007D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SPORTS_TRACKING_TECHNOLOGIES      0x007E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AUTONET_MOBILE                    0x007F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DELORME_PUBLISHING_COMPANY_INC    0x0080
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WUXI_VIMICRO                      0x0081
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SENNHEISER_COMMUNICATIONS_AS      0x0082
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TIMEKEEPING_SYSTEMS_INC           0x0083
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LUDUS_HELSINKI_LTD                0x0084
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BLUERADIOS_INC                    0x0085
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_EQUINUX_AG                        0x0086
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GARMIN_INTERNATIONAL_INC          0x0087
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ECOTEST                           0x0088
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GN_RESOUND_AS                     0x0089
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_JAWBONE                           0x008A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TOPCON_POSITIONING_SYSTEMS_LLC    0x008B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM_RETAIL_SOLUTIONS_INC     0x008C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ZSCAN_SOFTWARE                    0x008D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUINTIC_CORP                      0x008E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STOLLMANN_E_V_GMBH                0x008F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FUNAI_ELECTRIC_COMPANY_LTD        0x0090
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ADVANCED_PANMOBIL_SYSTEMS_GMBH    0x0091
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_THINKOPTICS_INC                   0x0092
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_UNIVERSAL_ELECTRONICS_INC         0x0093
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AIROHA_TECHNOLOGY_CORP            0x0094
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NEC_LIGHTING_LTD                  0x0095
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ODM_TECHNOLOGY_INC                0x0096
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BLUETREK_TECHNOLOGIES_LIMITED     0x0097
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ZERO_1_TV_GMBH                    0x0098
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_I_TECH_DYNAMIC_GLOBAL_DIST_LTD    0x0099
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ALPWISE                           0x009A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_JIANGSU_TOPPOWER_AUTOMOTIVE       0x009B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_COLORFY_INC                       0x009C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GEOFORCE_INC                      0x009D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BOSE_CORPORATION                  0x009E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SUUNTO_OY                         0x009F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KENSINGTON_COMPUTER_PROD_GROUP    0x00A0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SR_MEDIZINELEKTRONIK              0x00A1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VERTU_CORPORATION_LIMITED         0x00A2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_META_WATCH_LTD                    0x00A3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LINAK_A_S                         0x00A4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_OTL_DYNAMICS_LLC                  0x00A5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PANDA_OCEAN_INC                   0x00A6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VISTEON_CORPORATION               0x00A7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ARP_DEVICES_LIMITED               0x00A8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MAGNETI_MARELLI_S_P_A             0x00A9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CAEN_RFID_SRL                     0x00AA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INGENIEUR_SYSTEMGRUPPE_ZAHN       0x00AB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GREEN_THROTTLE_GAMES              0x00AC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PETER_SYSTEMTECHNIK_GMBH          0x00AD
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_OMEGAWAVE_OY                      0x00AE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CINETIX                           0x00AF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PASSIF_SEMICONDUCTOR_CORP         0x00B0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SARIS_CYCLING_GROUP_INC           0x00B1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BEKEY_AS                          0x00B2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CLARINOX_TECHNOLOGIES_PTY_LTD     0x00B3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BDE_TECHNOLOGY_CO_LTD             0x00B4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SWIRL_NETWORKS                    0x00B5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MESO_INTERNATIONAL                0x00B6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TRELAB_LTD                        0x00B7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM_INNOVATION_CENTER_INC    0x00B8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_JOHNSON_CONTROLS_INC              0x00B9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STARKEY_LABORATORIES_INC          0x00BA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_S_POWER_ELECTRONICS_LIMITED       0x00BB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ACE_SENSOR_INC                    0x00BC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_APLIX_CORPORATION                 0x00BD
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AAMP_OF_AMERICA                   0x00BE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STALMART_TECHNOLOGY_LIMITED       0x00BF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AMICCOM_ELECTRONICS_CORP          0x00C0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SHENZHEN_EXCELSECU_DATA_TECH      0x00C1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GENEQ_INC                         0x00C2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ADIDAS_AG                         0x00C3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LG_ELECTRONICS                    0x00C4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ONSET_COMPUTER_CORPORATION        0x00C5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SELFLY_BV                         0x00C6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUUPPA_OY                         0x00C7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GELO_INC                          0x00C8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_EVLUMA                            0x00C9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MC10                              0x00CA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BINAURIC_SE                       0x00CB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BEATS_ELECTRONICS                 0x00CC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MICROCHIP_TECHNOLOGY_INC          0x00CD
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ELGATO_SYSTEMS_GMBH               0x00CE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ARCHOS_SA                         0x00CF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DEXCOM_INC                        0x00D0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_POLAR_ELECTRO_EUROPE_BV           0x00D1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DIALOG_SEMICONDUCTOR_BV           0x00D2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TAIXINGBANG_TECHNOLOGY_HK_CO      0x00D3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KAWANTECH                         0x00D4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AUSTCO_COMMUNICATION_SYSTEMS      0x00D5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TIMEX_GROUP_USA_INC               0x00D6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM_TECHNOLOGIES_INC         0x00D7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM_CONNECTED_EXPERIENCES    0x00D8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VOYETRA_TURTLE_BEACH              0x00D9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TXTR_GMBH                         0x00DA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BIOSENTRONICS                     0x00DB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PROCTER_AND_GAMBLE                0x00DC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HOSIDEN_CORPORATION               0x00DD
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MUZIK_LLC                         0x00DE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MISFIT_WEARABLES_CORP             0x00DF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GOOGLE                            0x00E0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DANLERS_LTD                       0x00E1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SEMILINK_INC                      0x00E2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INMUSIC_BRANDS_INC                0x00E3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_LS_RESEARCH_INC                   0x00E4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_EDEN_SOFTWARE_CONSULTANTS_LTD     0x00E5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FRESHTEMP                         0x00E6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KS_TECHNOLOGIES                   0x00E7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ACTS_TECHNOLOGIES                 0x00E8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VTRACK_SYSTEMS                    0x00E9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NIELSEN_KELLERMAN_COMPANY         0x00EA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SERVER_TECHNOLOGY_INC             0x00EB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BIORESEARCH_ASSOCIATES            0x00EC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_JOLLY_LOGIC_LLC                   0x00ED
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ABOVE_AVERAGE_OUTCOMES_INC        0x00EE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BITSPLITTERS_GMBH                 0x00EF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PAYPAL_INC                        0x00F0
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WITRON_TECHNOLOGY_LIMITED         0x00F1
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MORSE_PROJECT_INC                 0x00F2
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KENT_DISPLAYS_INC                 0x00F3
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NAUTILUS_INC                      0x00F4
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SMARTIFIER_OY                     0x00F5
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ELCOMETER_LIMITED                 0x00F6
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VSN_TECHNOLOGIES_INC              0x00F7
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ACEUNI_CORP_LTD                   0x00F8
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STICKNFIND                        0x00F9
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CRYSTAL_CODE_AB                   0x00FA
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KOUKAAM_AS                        0x00FB
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_DELPHI_CORPORATION                0x00FC
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VALENCETECH_LIMITED               0x00FD
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RESERVED_1                        0x00FE
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TYPO_PRODUCTS_LLC                 0x00FF
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TOMTOM_INTERNATIONAL_BV           0x0100
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FUGOO_INC                         0x0101
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KEISER_CORPORATION                0x0102
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BANG_AND_OLUFSEN_AS               0x0103
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PLUS_LOCATIONS_SYSTEMS_PTY_LTD    0x0104
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_UBIQUITOUS_COMPUTING_TECH_CORP    0x0105
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_INNOVATIVE_YACHTTER_SOLUTIONS     0x0106
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WILLIAM_DEMANT_HOLDING_AS         0x0107
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CHICONY_ELECTRONICS_CO_LTD        0x0108
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ATUS_BV                           0x0109
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CODEGATE_LTD                      0x010A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ERI_INC                           0x010B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TRANSDUCERS_DIRECT_LLC            0x010C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FUJITSU_TEN_LIMITED               0x010D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AUDI_AG                           0x010E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HISILICON_TECHNOLOGIES_CO_LTD     0x010F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NIPPON_SEIKI_CO_LTD               0x0110
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_STEELSERIES_APS                   0x0111
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VYZYBL_INC                        0x0112
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_OPENBRAIN_TECHNOLOGIES_CO_LTD     0x0113
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_XENSR                             0x0114
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ESOLUTIONS                        0x0115
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_1OAK_TECHNOLOGIES                 0x0116
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WIMOTO_TECHNOLOGIES_INC           0x0117
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RADIUS_NETWORKS_INC               0x0118
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WIZE_TECHNOLOGY_CO_LTD            0x0119
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_QUALCOMM_LABS_INC                 0x011A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ARUBA_NETWORKS                    0x011B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BAIDU                             0x011C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ARENDI_AG                         0x011D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SKODA_AUTO_AS                     0x011E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_VOLKSWAGON_AG                     0x011F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PORSCHE_AG                        0x0120
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SINO_WEALTH_ELECTRONIC_LTD        0x0121
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AIRTURN_INC                       0x0122
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_KINSA_INC                         0x0123
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_HID_GLOBAL                        0x0124
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SEAT_ES                           0x0125
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PROMETHEAN_LTD                    0x0126
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SALUTICA_ALLIED_SOLUTIONS         0x0127
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GPSI_GROUP_PTY_LTD                0x0128
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NIMBLE_DEVICES_OY                 0x0129
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CHANGZHOU_YONGSE_INFOTECH_CO_LTD  0x012A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SPORTIQ                           0x012B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TEMEC_INSTRUMENTS_BV              0x012C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_SONY_CORPORATION                  0x012D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ASSA_ABLOY                        0x012E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CLARION_CO_LTD                    0x012F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WAREHOUSE_INNOVATIONS             0x0130
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_CYPRESS_SEMICONDUCTOR_CORPORATION 0x0131
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MADS_INC                          0x0132
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BLUE_MAESTRO_LIMITED              0x0133
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RESOLUTION_PRODUCTS_INC           0x0134
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_AIREWEAR_LLC                      0x0135
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ETC_SP_ZOO                        0x0136
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_PRESTIGIO_PLAZA_LTD               0x0137
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_NTEO_INC                          0x0138
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FOCUS_SYSTEMS_CORPORATION         0x0139
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_TENCENT_HOLDINGS_LIMITED          0x013A
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ALLEGION                          0x013B
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_MURATA_MANUFACURING_CO_LTD        0x013C
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_WIRELESSWERX                      0x013D
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ENIMAI                            0x013E
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_BANDB_MANUFACTURING_COMPANY       0x013F
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_ALPINE_ELECTRONICS_CHINA_CO_LTD   0x0140
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_FEDEX_SERVICES                    0x0141
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_GRAPE_SYSTEMS_INC                 0x0142

   /* The following Constant represents the defined COMP ID that is     */
   /* reserved for Interoperatiblity and Link Manager testing.          */
#define QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_RESERVED_FOR_LMP_TESTING       0xFFFF

   /* The following Constants represent the defined Bluetooth HCI Link  */
   /* Key Types (Version 2.1 + EDR).                                    */
#define QAPI_BLE_HCI_LINK_KEY_TYPE_COMBINATION_KEY                               0x00
#define QAPI_BLE_HCI_LINK_KEY_TYPE_LOCAL_UNIT_KEY                                0x01
#define QAPI_BLE_HCI_LINK_KEY_TYPE_REMOTE_UNIT_KEY                               0x02
#define QAPI_BLE_HCI_LINK_KEY_TYPE_DEBUG_COMBINATION_KEY                         0x03
#define QAPI_BLE_HCI_LINK_KEY_TYPE_UNAUTHENTICATED_COMBINATION_KEY               0x04
#define QAPI_BLE_HCI_LINK_KEY_TYPE_AUTHENTICATED_COMBINATION_KEY                 0x05
#define QAPI_BLE_HCI_LINK_KEY_TYPE_CHANGED_COMBINATION_KEY                       0x06
#define QAPI_BLE_HCI_LINK_KEY_TYPE_INVALID_KEY_TYPE                              0xFF

   /* The following Constants represent the additional defined Bluetooth*/
   /* HCI Link Key Types (Version 4.1).                                 */
#define QAPI_BLE_HCI_LINK_KEY_TYPE_UNAUTHENTICATED_COMBINATION_KEY_P192          0x04
#define QAPI_BLE_HCI_LINK_KEY_TYPE_AUTHENTICATED_COMBINATION_KEY_P192            0x05
#define QAPI_BLE_HCI_LINK_KEY_TYPE_UNAUTHENTICATED_COMBINATION_KEY_P256          0x07
#define QAPI_BLE_HCI_LINK_KEY_TYPE_AUTHENTICATED_COMBINATION_KEY_P256            0x08

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the LE_EVENT_MASK_BIT MACRO's (Set/Reset/Test). These*/
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth LE Event in the LE Event Mask   */
   /*(Version 4.0 + LE).                                                */
#define QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER                 0x00
#define QAPI_BLE_HCI_LE_EVENT_MASK_ADVERTISING_REPORT_BIT_NUMBER                  0x01
#define QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_UPDATE_COMPLETE_BIT_NUMBER          0x02
#define QAPI_BLE_HCI_LE_EVENT_MASK_READ_REMOTE_USED_FEATURES_COMPLETE_BIT_NUMBER  0x03
#define QAPI_BLE_HCI_LE_EVENT_MASK_LONG_TERM_KEY_REQUEST_BIT_NUMBER               0x04

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the LE_EVENT_MASK_BIT MACRO's (Set/Reset/Test).      */
   /* These Constants are used as the second parameter in those MACRO's */
   /* to specify the correct HCI Bluetooth LE Event in the LE Event Mask*/
   /* (Version 4.1).                                                    */
#define QAPI_BLE_HCI_LE_EVENT_MASK_REMOTE_CONNECTION_PARAMETER_REQUEST_BIT_NUMBER 0x05

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the LE_EVENT_MASK_BIT MACRO's (Set/Reset/Test).      */
   /* These Constants are used as the second parameter in those MACRO's */
   /* to specify the correct HCI Bluetooth LE Event in the LE Event Mask*/
   /* (Version 4.2).                                                    */
#define QAPI_BLE_HCI_LE_EVENT_MASK_DATA_LENGTH_CHANGE_BIT_NUMBER                  0x06
#define QAPI_BLE_HCI_LE_EVENT_MASK_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_BIT_NUMBER 0x07
#define QAPI_BLE_HCI_LE_EVENT_MASK_GENERATE_DHKEY_COMPLETE_BIT_NUMBER             0x08
#define QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_BIT_NUMBER        0x09
#define QAPI_BLE_HCI_LE_EVENT_MASK_DIRECT_ADVERTISING_REPORT_EVENT_BIT_NUMBER     0x0A

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the LE_EVENT_MASK_BIT MACRO's (Set/Reset/Test).      */
   /* These Constants are used as the second parameter in those MACRO's */
   /* to specify the correct HCI Bluetooth LE Event in the LE Event Mask*/
   /* (Version 5.4).                                                    */
#define QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_BIT_NUMBER     0x26
#define QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_RESPONSE_REPORT_BIT_NUMBER           0x27
#define QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_BIT_NUMBER       0x23
#define QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_REPORT_V2_BIT_NUMBER                 0x24
#define QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_BIT_NUMBER 0x25
#define QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_V2_BIT_NUMBER                0x28

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Enabling ALL defined HCI LE Events in the HCI LE Event Mask.   */
   /* This MACRO accepts as input the Event Mask (of type               */
   /* qapi_BLE_Event_Mask_t) to enable all defined Events for.          */
   /* * NOTE * This MACRO is only valid for LE Events in the LE Event   */
   /*          Mask and not the BR/EDR Page 1/2 Event Masks !!!!!!!!!!! */
   /* * NOTE * This only enables LE Events defined in the 4.0 and 4.1   */
   /*          specifications.                                          */
#define QAPI_BLE_HCI_ENABLE_ALL_HCI_LE_EVENTS_IN_EVENT_MASK_PRE_4_2(_x)                                           \
{                                                                                                                 \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                      \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                  \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ADVERTISING_REPORT_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_UPDATE_COMPLETE_BIT_NUMBER);           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_REMOTE_USED_FEATURES_COMPLETE_BIT_NUMBER);   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_LONG_TERM_KEY_REQUEST_BIT_NUMBER);                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_REMOTE_CONNECTION_PARAMETER_REQUEST_BIT_NUMBER);  \
}

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in disabling ALL defined HCI LE Events in the HCI LE Event Mask.  */
   /* This MACRO accepts as input the Event Mask (of type               */
   /* qapi_BLE_Event_Mask_t) to disable all defined Events for.         */
   /* * NOTE * This MACRO is only valid for LE Events in the LE Event   */
   /*          Mask and not the BR/EDR Page 1/2 Event Masks !!!!!!!!!!! */
   /* * NOTE * This only disables LE Events defined in the 4.0 and 4.1  */
   /*          specifications.                                          */
#define QAPI_BLE_HCI_DISABLE_ALL_HCI_LE_EVENTS_IN_EVENT_MASK_PRE_4_2(_x)                                           \
{                                                                                                                  \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ADVERTISING_REPORT_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_UPDATE_COMPLETE_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_REMOTE_USED_FEATURES_COMPLETE_BIT_NUMBER);    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_LONG_TERM_KEY_REQUEST_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_REMOTE_CONNECTION_PARAMETER_REQUEST_BIT_NUMBER);   \
}

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in Enabling ALL defined HCI LE Events in the HCI LE Event Mask.   */
   /* This MACRO accepts as input the Event Mask (of type               */
   /* qapi_BLE_Event_Mask_t) to enable all defined Events for.          */
   /* * NOTE * This MACRO is only valid for LE Events in the LE Event   */
   /*          Mask and not the BR/EDR Page 1/2 Event Masks !!!!!!!!!!! */
#define QAPI_BLE_HCI_ENABLE_ALL_HCI_LE_EVENTS_IN_EVENT_MASK(_x)                                                             \
{                                                                                                                           \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ADVERTISING_REPORT_BIT_NUMBER);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_UPDATE_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_REMOTE_USED_FEATURES_COMPLETE_BIT_NUMBER);             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_LONG_TERM_KEY_REQUEST_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_REMOTE_CONNECTION_PARAMETER_REQUEST_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_DATA_LENGTH_CHANGE_BIT_NUMBER);                             \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_GENERATE_DHKEY_COMPLETE_BIT_NUMBER);                        \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_BIT_NUMBER);                   \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_DIRECT_ADVERTISING_REPORT_EVENT_BIT_NUMBER);                \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PHY_UPDATE_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_ADVERTISING_REPORT_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_BIT_NUMBER);          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_REPORT_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_LOST_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_SCAN_TIMEOUT_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_ADVERTISING_SET_TERMINATED_BIT_NUMBER);            \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_SCAN_REQUEST_RECEIVED_BIT_NUMBER);                          \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CHANNEL_SELECTION_ALGORITHM_BIT_NUMBER);                    \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_BIT_NUMBER);       \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_REPORT_V2_BIT_NUMBER);                 \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_BIT_NUMBER); \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_BIT_NUMBER);     \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_RESPONSE_REPORT_BIT_NUMBER);           \
   QAPI_BLE_SET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_V2_BIT_NUMBER);                \
}

   /* The following MACRO is a utility MACRO that exists to aid the user*/
   /* in disabling ALL defined HCI LE Events in the HCI LE Event Mask.  */
   /* This MACRO accepts as input the Event Mask (of type               */
   /* qapi_BLE_Event_Mask_t) to disable all defined Events for.         */
   /* * NOTE * This MACRO is only valid for LE Events in the LE Event   */
   /*          Mask and not the BR/EDR Page 1/2 Event Masks !!!!!!!!!!! */
#define QAPI_BLE_HCI_DISABLE_ALL_HCI_LE_EVENTS_IN_EVENT_MASK(_x)                                                              \
{                                                                                                                             \
   QAPI_BLE_ASSIGN_EVENT_MASK((_x), 0, 0, 0, 0, 0, 0, 0, 0);                                                                  \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ADVERTISING_REPORT_BIT_NUMBER);                             \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CONNECTION_UPDATE_COMPLETE_BIT_NUMBER);                     \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_REMOTE_USED_FEATURES_COMPLETE_BIT_NUMBER);             \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_LONG_TERM_KEY_REQUEST_BIT_NUMBER);                          \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_REMOTE_CONNECTION_PARAMETER_REQUEST_BIT_NUMBER);            \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_DATA_LENGTH_CHANGE_BIT_NUMBER);                             \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_BIT_NUMBER);            \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_GENERATE_DHKEY_COMPLETE_BIT_NUMBER);                        \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_BIT_NUMBER);                   \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_DIRECT_ADVERTISING_REPORT_EVENT_BIT_NUMBER);                \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PHY_UPDATE_COMPLETE_BIT_NUMBER);                            \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_ADVERTISING_REPORT_BIT_NUMBER);                    \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_BIT_NUMBER);          \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_REPORT_BIT_NUMBER);                    \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_LOST_BIT_NUMBER);                 \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_SCAN_TIMEOUT_BIT_NUMBER);                          \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_EXTENDED_ADVERTISING_SET_TERMINATED_BIT_NUMBER);            \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_SCAN_REQUEST_RECEIVED_BIT_NUMBER);                          \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_CHANNEL_SELECTION_ALGORITHM_BIT_NUMBER);                    \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_BIT_NUMBER);       \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_REPORT_V2_BIT_NUMBER);                 \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_BIT_NUMBER); \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_BIT_NUMBER);     \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_PERIODIC_ADVERTISING_RESPONSE_REPORT_BIT_NUMBER);           \
   QAPI_BLE_RESET_EVENT_MASK_BIT((_x), QAPI_BLE_HCI_LE_EVENT_MASK_ENHANCED_CONNECTION_COMPLETE_V2_BIT_NUMBER);                \
}

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth LE Feature in the LE Feature    */
   /* Mask (Version 4.0 + LE).                                          */
#define QAPI_BLE_HCI_LE_FEATURE_LE_ENCRYPTION_BIT_NUMBER                               0x00

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth LE Feature in the LE Feature    */
   /* Mask (Version 4.1).                                               */
#define QAPI_BLE_HCI_LE_FEATURE_LE_CONNECTION_PARAMETER_REQUEST_PROCEDURE_BIT_NUMBER   0x01
#define QAPI_BLE_HCI_LE_FEATURE_LE_EXTENDED_REJECT_INDICATION_BIT_NUMBER               0x02
#define QAPI_BLE_HCI_LE_FEATURE_LE_SLAVE_INITIATED_FEATURES_EXCHANGE_BIT_NUMBER        0x03
#define QAPI_BLE_HCI_LE_FEATURE_LE_PING_BIT_NUMBER                                     0x04

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth LE Feature in the LE Feature    */
   /* Mask (Version 4.2).                                               */
#define QAPI_BLE_HCI_LE_FEATURE_LE_DATA_LENGTH_EXTENSION_BIT_NUMBER                    0x05
#define QAPI_BLE_HCI_LE_FEATURE_LE_LL_PRIVACY_BIT_NUMBER                               0x06
#define QAPI_BLE_HCI_LE_FEATURE_LE_EXTENDED_SCANNER_FILTER_POLICIES_BIT_NUMBER         0x07

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test). These Constants*/
   /* are used as the second parameter in those MACRO's to specify the  */
   /* correct HCI Bluetooth LE Feature in the LE Feature Mask (Version  */
   /* 5.0).                                                             */
#define QAPI_BLE_HCI_LE_FEATURE_LE_2M_PHY                                              0x08
#define QAPI_BLE_HCI_LE_FEATURE_STABLE_MODULATION_INDEX_TRANSMITTER                    0x09
#define QAPI_BLE_HCI_LE_FEATURE_STABLE_MODULATION_INDEX_RECEIVER                       0x0A
#define QAPI_BLE_HCI_LE_FEATURE_LE_CODED_PHY                                           0x0B
#define QAPI_BLE_HCI_LE_FEATURE_LE_EXTENDED_ADVERTISING                                0x0C
#define QAPI_BLE_HCI_LE_FEATURE_LE_PERIODIC_ADVERTISING                                0x0D
#define QAPI_BLE_HCI_LE_FEATURE_CHANNEL_SELECTION_ALGORITHM                            0x0E
#define QAPI_BLE_HCI_LE_FEATURE_LE_POWER_CLASS                                         0x0F
#define QAPI_BLE_HCI_LE_FEATURE_MINIMUM_NUMBER_OF_USED_CHANNELS_PROCEDURE              0x10

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the FEATURE MACRO's (Set/Reset/Test).  These         */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct HCI Bluetooth LE Feature in the LE Feature    */
   /* Mask (Version 5.4).                                               */
#define QAPI_BLE_HCI_LE_FEATURE_PERIODIC_ADVERTISING_WITH_RESPONSES_ADVERTISER         0x3E
#define QAPI_BLE_HCI_LE_FEATURE_PERIODIC_ADVERTISING_WITH_RESPONSES_SCANNER            0x3D

   /* The following constants represent some basic constants that define*/
   /* the number of channels and their indexes for Bluetooth LE         */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_NUMBER_DATA_CHANNELS                                     37
#define QAPI_BLE_HCI_LE_NUMBER_ADVERTISING_CHANNELS                              3

#define QAPI_BLE_HCI_LE_NUMBER_TOTAL_CHANNELS                                    (QAPI_BLE_HCI_LE_NUMBER_DATA_CHANNELS + QAPI_BLE_HCI_LE_NUMBER_ADVERTISING_CHANNELS)

#define QAPI_BLE_HCI_LE_MINIMUM_DATA_CHANNEL_INDEX                               0
#define QAPI_BLE_HCI_LE_MAXIMUM_DATA_CHANNEL_INDEX                              36

#define QAPI_BLE_HCI_LE_MINIMUM_ADVERTISING_CHANNEL_INDEX                       37
#define QAPI_BLE_HCI_LE_MAXIMUM_ADVERTISING_CHANNEL_INDEX                       39

   /* The following constants represent the minumum and maximum         */
   /* Advertising Intervals that can be specified (respectively).       */
   /* (Version 4.0 + LE).                                               */
   /* * NOTE * These values are specified in 0.625ms increments.        */
#define QAPI_BLE_HCI_LE_ADVERTISING_INTERVAL_MINIMUM                             0x0020
#define QAPI_BLE_HCI_LE_ADVERTISING_INTERVAL_MAXIMUM                             0x4000

   /* The following Constants represent the various types of LE         */
   /* Advertising Reports. (Version 4.0 + LE).                          */
#define QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_UNDIRECTED                  0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_DIRECTED                    0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_TYPE_SCANNABLE_UNDIRECTED                    0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_TYPE_NON_CONNECTABLE_UNDIRECTED              0x03

   /* The following Constants represent the various types of LE         */
   /* Advertising Reports.  (Version 4.1).                              */
#define QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_LOW_DUTY_CYCLE_DIRECTED     0x04

   /* The following constants represent the address type that is passed */
   /* to LE Controller Commands that take Address Type parameters       */
   /* (deprecated with Version 4.2 of the specification).  (Version 4.0 */
   /* + LE).                                                            */
#define QAPI_BLE_HCI_LE_ADDRESS_TYPE_PUBLIC                                      0x00
#define QAPI_BLE_HCI_LE_ADDRESS_TYPE_RANDOM                                      0x01

   /* The following constants represent the extended address type values*/
   /* that may be passed to LE HCI commands that take a                 */
   /* Peer_Address_Type parameter to controllers that support the LE    */
   /* Enhanced Privacy 1.2 feature (Version 4.2).                       */
   /* * NOTE * The following constants represent the Peer_Address_Type  */
   /*          or Peer_Identity_Address_Type parameter for the          */
   /*          qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(),   */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection(), and        */
   /*          qapi_BLE_HCI_LE_Set_Privacy_Mode() command. Only         */
   /*          QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC and             */
   /*          QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM may be used for */
   /*          the commands above. (Version 5.0 + LE).                  */
   /* * NOTE * These parameters may also be passed in LE Controller     */
   /*          events.                                                  */
#define QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC                                 0x00
#define QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM                                 0x01
#define QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY_ADDRESS                0x02
#define QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_STATIC_RANDOM_IDENTITY_ADDRESS         0x03

   /* The following constants represent the extended address type values*/
   /* that may be passed to LE HCI commands that take a Own_Address_Type*/
   /* parameter to controllers that support the LE Enhanced Privacy 1.2 */
   /* feature (Version 4.2).                                            */
   /* * NOTE * The meaning of the two                                   */
   /*          HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK*/
   /*          values is that the controller shall generate the         */
   /*          Resolvable Private Address (RPA) based on the Local IRK  */
   /*          found in the resolving list.  If the resolving list      */
   /*          contains no match the fallback is either the public      */
   /*          address of the controller or the random address that has */
   /*          been set via the HCI LE Set Random Address command.      */
   /*          These values will not be used in any event sent by the   */
   /*          controller.                                              */
   /* * NOTE * The following constants represent the Own_Address_Type   */
   /*          parameter for the                                        */
   /*          qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(),   */
   /*          qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(), and      */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection() commands.   */
   /*          (Version 5.0 + LE).                                      */
#define QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_PUBLIC                                   0x00
#define QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RANDOM                                   0x01
#define QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_PUBLIC 0x02
#define QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_RANDOM 0x03

   /* The following constants represent the constants that can be passed*/
   /* into Advertising_Channel_Map parameter of LE Set Advertising      */
   /* Parameters Command. (Version 4.0 + LE).                           */
   /* * NOTE * The following constants represent the                    */
   /*          Primary_Advertising_Channel_Map parameter for the        */
   /*          qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters()    */
   /*          command. (Version 5.0 + LE).                             */
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_37                0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_38                0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_39                0x04
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_ALL_CHANNELS              0x07

#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_DEFAULT                          (QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_ALL_CHANNELS)

   /* The following constants represent the constants that can be passed*/
   /* into Advertising_Filter_Policy parameter of LE Set Advertising    */
   /* Parameters Command. (Version 4.0 + LE).                           */
   /* * NOTE * The following constants represent the                    */
   /*          Advertising_Filter_Policy parameter for the              */
   /*          qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters()    */
   /*          command. (Version 5.0 + LE).                             */
#define QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_ANY_CONNECT_ANY                 0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_WHITE_LIST_CONNECT_ANY          0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_ANY_CONNECT_WHITE_LIST          0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_WHITE_LIST_CONNECT_WHITE_LIST   0x03

   /* The following Constants represent the defined Bluetooth HCI       */
   /* minimum and maximum Advertising Channel Transmit Power values -   */
   /* TX_Power in dBm (Version 4.0 + LE).                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_TRANSMIT_POWER_MINUMUM               (-20)
#define QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_TRANSMIT_POWER_MAXIMUM               (10)

   /* The following constants represent the values of Advertising_Enable*/
   /* parameter of HCI_LE_Set_Advertise_Enable command.  (Version 4.0 + */
   /* LE)                                                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_DISABLE                                      0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_ENABLE                                       0x01

   /* The following constants represent that are used to specify the    */
   /* type of Scan to perform while scanning (Version 4.0 + LE).        */
   /* * NOTE * The following constants represent the Scanning_Type      */
   /*          parameter for the                                        */
   /*          qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters() command.  */
   /*          (Version 5.0 + LE).                                      */
#define QAPI_BLE_HCI_LE_SCAN_TYPE_PASSIVE                                        0x00
#define QAPI_BLE_HCI_LE_SCAN_TYPE_ACTIVE                                         0x01

   /* The following constants represent the minumum and maximum         */
   /* Scanning Intervals that can be specified (respectively).          */
   /* (Version 4.0 + LE).                                               */
   /* * NOTE * These values are specified in 0.625ms increments.        */
#define QAPI_BLE_HCI_LE_SCAN_INTERVAL_MINIMUM                                    0x0004
#define QAPI_BLE_HCI_LE_SCAN_INTERVAL_MAXIMUM                                    0x4000

   /* The following constants represent the supported Scanning Filter   */
   /* Policies that are to be used while scanning (Version 4.0 + LE).   */
   /* * NOTE * The following constants represent the                    */
   /*          Scanning_Filter_Policy parameter for the                 */
   /*          qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters() command.  */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * The following constants represent the                    */
   /*          Initiating_Filter_Policy parameter for the               */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection() command.    */
   /*          (Version 5.0 + LE).                                      */
#define QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_ALL                        0x00
#define QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_WHITE_LIST_ONLY            0x01

   /* The following constants represent the extended Scanning Filter    */
   /* Policies that are supported by controllers supporting the LE      */
   /* Privacy 1.2 feature (Version 4.2).                                */
   /* * NOTE * The following constants represent the                    */
   /*          Scanning_Filter_Policy parameter for the                 */
   /*          qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters() command.  */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * If these values are used and the LE Directed Advertising */
   /*          Report Event is not masked then this LE event may be sent*/
   /*          by the controller to the host.                           */
#define QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_UNDIRECTED_DIRECTED_RPA    0x02
#define QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_WHITE_LIST_DIRECTED_RPA    0x03

   /* The following constants represent the defined values that can be  */
   /* used when setting the LE Scan Enable (Version 4.0 + LE).          */
#define QAPI_BLE_HCI_LE_SCAN_DISABLE                                             0x00
#define QAPI_BLE_HCI_LE_SCAN_ENABLE                                              0x01

   /* The following constants represent the defined values that can be  */
   /* used when setting the Filtering mechanism when Scanning is enabled*/
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_SCAN_FILTER_DUPLICATES_DISABLED                          0x00
#define QAPI_BLE_HCI_LE_SCAN_FILTER_DUPLICATES_ENABLED                           0x01

   /* The following constants represent the constants that can be passed*/
   /* into the Initiator Filter Policy of the HCI LE Create Connection  */
   /* Command.  (Version 4.0 + LE).                                     */
#define QAPI_BLE_HCI_LE_INITIATOR_FILTER_POLICY_WHITE_LIST_NOT_USED              0x00
#define QAPI_BLE_HCI_LE_INITIATOR_FILTER_POLICY_WHITE_LIST_IS_USED               0x01

   /* The following constants represent the constants that define the   */
   /* minimum and maximum Connection Interval (respectively). (Version  */
   /* 4.0 + LE).                                                        */
   /* * NOTE * The following constants represent the Conn_Interval_Min  */
   /*          and Conn_Interval_Max parameters for the                 */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection() command.    */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * These values are specified in 1.25ms increments.         */
#define QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINUMUM                              0x0006
#define QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM                              0x0C80

   /* The following constants represent the constants that define the   */
   /* minimum and maximum Connection Latency (respectively).            */
   /* (Version 4.0 + LE).                                               */
   /* * NOTE * These values are specified in Number of missed Connection*/
   /*          Events.                                                  */
#define QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MINIMUM                               0x0000
#define QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MAXIMUM                               0x01F3

   /* The following constants represent the constants that define the   */
   /* minimum and maximum Supervision Timeout (respectively). (Version  */
   /* 4.0 + LE).                                                        */
   /* * NOTE * The following constants represent the Supervision_Timeout*/
   /*          parameter for the                                        */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection() command.    */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * These values are specified in 10ms increments.           */
#define QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MINIMUM                              0x000A
#define QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MAXIMUM                              0x0C80

   /* The following constants represent the constants that define the   */
   /* minimum and maximum Length of Connection (respectively). (Version */
   /* 4.0 + LE).                                                        */
   /* * NOTE * The following constants represent the Minimum_CE_Length  */
   /*          and Maximum_CE_Length parameters for the                 */
   /*          qapi_BLE_HCI_LE_Extended_Create_Connection() command.    */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * These values are specified in 0.625ms increments.        */
#define QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM                             0x0000
#define QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM                             0xFFFF

   /* The following constants represent the constants that define the   */
   /* minimum and maximum size of the White List (respectively).        */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_WHITE_LIST_SIZE_MINUMUM                                  0x00
#define QAPI_BLE_HCI_LE_WHITE_LIST_SIZE_MAXIMUM                                  0xFF

   /* The following Constants represent Bit Number Constants that are to*/
   /* be used with the LE_STATES MACRO's (Set/Reset/Test).  These       */
   /* Constants are used as the second parameter in those MACRO's to    */
   /* specify the correct LE State in the LE States member.             */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_STATE_SUPPORTED_BIT_NUMBER                    0x00
#define QAPI_BLE_HCI_LE_STATES_SCANNABLE_ADVERTISING_STATE_SUPPORTED_BIT_NUMBER                          0x01
#define QAPI_BLE_HCI_LE_STATES_CONNECTABLE_ADVERTISING_STATE_SUPPORTED_BIT_NUMBER                        0x02
#define QAPI_BLE_HCI_LE_STATES_DIRECTED_ADVERTISING_STATE_SUPPORTED_BIT_NUMBER                           0x03
#define QAPI_BLE_HCI_LE_STATES_PASSIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER                               0x04
#define QAPI_BLE_HCI_LE_STATES_ACTIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER                                0x05
#define QAPI_BLE_HCI_LE_STATES_INITIATING_STATE_MASTER_ROLE_SUPPORTED_BIT_NUMBER                         0x06
#define QAPI_BLE_HCI_LE_STATES_CONNECTION_STATE_SLAVE_ROLE_SUPPORTED_BIT_NUMBER                          0x07
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_PASSIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER   0x08
#define QAPI_BLE_HCI_LE_STATES_SCANNABLE_ADVERTISING_PASSIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER         0x09
#define QAPI_BLE_HCI_LE_STATES_CONNECTABLE_ADVERTISING_PASSIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER       0x0A
#define QAPI_BLE_HCI_LE_STATES_DIRECTED_ADVERTISING_PASSIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER          0x0B
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_ACTIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER    0x0C
#define QAPI_BLE_HCI_LE_STATES_SCANNABLE_ADVERTISING_ACTIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER          0x0D
#define QAPI_BLE_HCI_LE_STATES_CONNECTABLE_ADVERTISING_ACTIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER        0x0E
#define QAPI_BLE_HCI_LE_STATES_DIRECTED_ADVERTISING_ACTIVE_SCANNING_STATE_SUPPORTED_BIT_NUMBER           0x0F
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_INITIATING_STATE_SUPPORTED_BIT_NUMBER         0x10
#define QAPI_BLE_HCI_LE_STATES_NON_SCANNABLE_ADVERTISING_INITIATING_STATE_SUPPORTED_BIT_NUMBER           0x11
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_STATE_MASTER_ROLE_SUPPORTED_BIT_NUMBER        0x12
#define QAPI_BLE_HCI_LE_STATES_SCANNABLE_ADVERTISING_STATE_MASTER_ROLE_SUPPORTED_BIT_NUMBER              0x13
#define QAPI_BLE_HCI_LE_STATES_NON_CONNECTABLE_ADVERTISING_STATE_SLAVE_ROLE_SUPPORTED_BIT_NUMBER         0x14
#define QAPI_BLE_HCI_LE_STATES_SCANNABLE_ADVERTISING_STATE_SLAVE_ROLE_SUPPORTED_BIT_NUMBER               0x15
#define QAPI_BLE_HCI_LE_STATES_PASSIVE_SCANNING_INITITIATING_STATE_SUPPORTED_BIT_NUMBER                  0x16
#define QAPI_BLE_HCI_LE_STATES_ACTIVE_SCANNING_INITITIATING_STATE_SUPPORTED_BIT_NUMBER                   0x17
#define QAPI_BLE_HCI_LE_STATES_PASSIVE_SCANNING_STATE_MASTER_ROLE_SUPPORTED_BIT_NUMBER                   0x18
#define QAPI_BLE_HCI_LE_STATES_ACTIVE_SCANNING_STATE_MASTER_ROLE_SUPPORTED_BIT_NUMBER                    0x19
#define QAPI_BLE_HCI_LE_STATES_PASSIVE_SCANNING_STATE_SLAVE_ROLE_SUPPORTED_BIT_NUMBER                    0x1A
#define QAPI_BLE_HCI_LE_STATES_ACTIVE_SCANNING_STATE_SLAVE_ROLE_SUPPORTED_BIT_NUMBER                     0x1B
#define QAPI_BLE_HCI_LE_STATES_INITIATING_STATE_MASTER_ROLE_MASTER_ROLE_MASTER_ROLE_SUPPORTED_BIT_NUMBER 0x1C

   /* The following constants represent the minimum and maximum         */
   /* frequencies that can be specified for the LE Receiver and         */
   /* Transmitter Tests (respectively). (Version 4.0 + LE).             */
   /* * NOTE * The following constants represent the RX_Channel and     */
   /*          TX_Channel parameters for the                            */
   /*          qapi_BLE_HCI_LE_Enhanced_Receiver_Test() and             */
   /*          qapi_BLE_HCI_LE_Enhanced_Transmitter_Test() commands.    */
   /*          (Version 5.0 + LE).                                      */
   /* * NOTE * These values correspond to N = (FX - 2402)/2.            */
#define QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM              0x00
#define QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM              0x27

   /* The following values represent the minimum and maximum number of  */
   /* bytes of test data payload that is to be transmitted when         */
   /* specifying a Transmitter Test (respectively).  (Version 4.0 + LE).*/
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MINIMUM_LENGTH      0x00
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MAXIMUM_LENGTH      0x25

   /* The following constants represent the defined payloads that can   */
   /* be specified when performing a Transmitter Test.                  */
   /* (Version 4.0 + LE).                                               */
   /* * NOTE * The following constants represent the Packet_Payload     */
   /*          parameter for the HCI_LE_Enhanced_Receiver_Test()        */
   /*          command. (Version 5.0 + LE).                             */
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_9    0x00
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0xF0   0x01
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0xAA   0x02
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_15   0x03
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALL_1_BITS              0x04
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALL_0_BITS              0x05
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x0F   0x06
#define QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x55   0x07

   /* The following constants represent the minimum and maximum Link    */
   /* Layer payload octets that may be included in a single Link Layer  */
   /* Data Channel PDU.  (Version 4.2).                                 */
#define QAPI_BLE_HCI_LE_MINIMUM_LINK_LAYER_DATA_CHANNEL_PACKET_PAYLOAD_OCTETS    0x001B
#define QAPI_BLE_HCI_LE_MAXIMUM_LINK_LAYER_DATA_CHANNEL_PACKET_PAYLOAD_OCTETS    0x00FB

   /* The following constants represent the minimum and maximum number  */
   /* of microseconds that the controller can use to send or receive a  */
   /* Link Layer Data Channel PDU.  (Version 4.2).                      */
#define QAPI_BLE_HCI_LE_MINIMUM_LINK_LAYER_DATA_CHANNEL_PACKET_MICROSECONDS      0x0148
#define QAPI_BLE_HCI_LE_MAXIMUM_LINK_LAYER_DATA_CHANNEL_PACKET_MICROSECONDS      0x0848

   /* The following constants represent the minimum and maximum number  */
   /* of seconds that can be set for the resolvable private address     */
   /* (RPA) timeout in the controller.  (Version 4.2).                  */
#define QAPI_BLE_HCI_LE_MINIMUM_RPA_TIMEOUT_SECONDS                              0x0001
#define QAPI_BLE_HCI_LE_MAXIMUM_RPA_TIMEOUT_SECONDS                              0xA1B8

   /* The following constants represent the defined values that can     */
   /* be used when sending the HCI LE Set Address Resolution Enabled    */
   /* command (Version 4.2).                                            */
#define QAPI_BLE_HCI_LE_CONTROLLER_ADDRESS_RESOLUTION_DISABLED                   0x00
#define QAPI_BLE_HCI_LE_CONTROLLER_ADDRESS_RESOLUTION_ENABLED                    0x01

   /* The following constants represent the possible                    */
   /* transmitter/receiver PHYs for an HCI LE command. (Version 5.0 +   */
   /* LE).                                                              */
   /* * NOTE * The following constants may NOT be used for the PHY      */
   /*          parameter of the                                         */
   /*          qapi_BLE_HCI_LE_Enhanced_Transmitter_Test() command. See */
   /*          qapi_BLE_HCI_LE_Enhanced_Transmitter_Test_XXX below for  */
   /*          possible values.                                         */
#define QAPI_BLE_HCI_LE_PHY_1M                                                   0x01
#define QAPI_BLE_HCI_LE_PHY_2M                                                   0x02
#define QAPI_BLE_HCI_LE_PHY_CODED                                                0x03

   /* The following bit masks represent the possible bit masks for      */
   /* Scanning PHYs that may be set in the Scanning_PHYs parameter for  */
   /* the qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters() command.       */
#define QAPI_BLE_HCI_LE_SCANNING_PHYS_1M_PHY                                     0x01
#define QAPI_BLE_HCI_LE_SCANNING_PHYS_CODED_PHY                                  0x04

   /* The following bit masks represent the possible bit masks for      */
   /* Scanning PHYs that may be set in the Initiating_PHYs parameter for*/
   /* the qapi_BLE_HCI_LE_Extended_Create_Connection() command.         */
#define QAPI_BLE_HCI_LE_INITIATING_PHY_1M_PHY                                    0x01
#define QAPI_BLE_HCI_LE_INITIATING_PHY_2M_PHY                                    0x02
#define QAPI_BLE_HCI_LE_INITIATING_PHY_CODED_PHY                                 0x04

   /* The following bit mask values represent the possible bit masks    */
   /* that may be set int he TX_PHYS and RX_PHYS parameters for the     */
   /* qapi_BLE_HCI_LE_Set_Default_PHY() and qapi_BLE_HCI_LE_Set_PHY()   */
   /* commands. (Version 5.0 + LE).                                     */
#define QAPI_BLE_HCI_LE_PHY_HOST_PREFERS_1M_PHY                                  0x01
#define QAPI_BLE_HCI_LE_PHY_HOST_PREFERS_2M_PHY                                  0x02
#define QAPI_BLE_HCI_LE_PHY_HOST_PREFERS_CODED_PHY                               0x04

   /* The following constants represent the bits that may be set in the */
   /* ALL_PHYS parameter for the qapi_BLE_HCI_LE_Set_Default_PHY() and  */
   /* qapi_BLE_HCI_LE_Set_PHY() commands. (Version 5.0 + LE).           */
#define QAPI_BLE_HCI_LE_PHY_HOST_HAS_NO_TRANSMITTER_PHY_PREFERENCE               0x01
#define QAPI_BLE_HCI_LE_PHY_HOST_HAS_NO_RECEIVER_PHY_PREFERENCE                  0x02

   /* The following constants represent the PHY_options parameter for   */
   /* the qapi_BLE_HCI_LE_Set_PHY() command. (Version 5.0 + LE).        */
#define QAPI_BLE_HCI_LE_PHY_OPTIONS_NO_PREFERENCE                                0x0000
#define QAPI_BLE_HCI_LE_PHY_OPTIONS_S2_CODING                                    0x0001
#define QAPI_BLE_HCI_LE_PHY_OPTIONS_S8_CODING                                    0x0002

   /* The following constants represent the Modulation_Index parameter  */
   /* for the qapi_BLE_HCI_LE_Enhanced_Receiver_Test() command. (Version*/
   /* 5.0 + LE).                                                        */
#define QAPI_BLE_HCI_LE_TRANSMITTER_MODULATION_INDEX_STANDARD                    0x00
#define QAPI_BLE_HCI_LE_TRANSMITTER_MODULATION_INDEX_STABLE                      0x01

   /* The following constants represent the Length_Of_Test_Data         */
   /* parameter for the qapi_BLE_HCI_LE_Enhanced_Transmitter_Test()     */
   /* command. (Version 5.0 + LE).                                      */
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MINIMUM_LENGTH  0x00
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MAXIMUM_LENGTH  0xFF

   /* The following constants represent the PHY parameter for the       */
   /* qapi_BLE_HCI_LE_Enhanced_Transmitter_Test() command. (Version 5.0 */
   /* + LE).                                                            */
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_1M                         0x01
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_2M                         0x02
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_CODED_S8                   0x03
#define QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_CODED_S2                   0x04

   /* The following constants represent the Advertising_Handle parameter*/
   /* for the HCI_LE_Set_Advertising_Set_Random_Address(),              */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(),            */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(),                  */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(),                */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable(),                */
   /* qapi_BLE_HCI_LE_Remove_Advertising_Set(),                         */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters(),            */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data(), and              */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable() commands.       */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_HANDLE_MINIMUM                               0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_HANDLE_MAXIMUM                               0xEF

   /* The following constants represent the Advertising_Handle parameter*/
   /* returned for an LE Enhanced Connection Complete v2 event to denote*/
   /* that the Advertising Handle is not valid.  This is also used in   */
   /* the HCI LE Extended Create Connection v2 command.                 */
#define QAPI_BLE_HCI_LE_ADVERTISING_HANDLE_NO_ADVERTISING_HANDLE                 0xFF

   /* The following constants represent the Advertising_Event_Properties*/
   /* parameter for the                                                 */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_CONNECTABLE_ADVERTISING     0x0001
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_SCANNABLE_ADVERTISING       0x0002
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_DIRECTED_ADVERTISING        0x0004
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_DIRECTED_ADVERTISING_HDC    0x0008
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_LEGACY_ADVERTISING          0x0010
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_ANONYMOUS_ADVERTISING       0x0020
#define QAPI_BLE_HCI_LE_ADVERTISING_EVENT_PROPERTIES_INCLUDE_TX_POWER            0x0040

   /* The following constants represent the                             */
   /* Primary_Advertising_Interval_Min and                              */
   /* Primary_Advertising_Interval_Max parameters for the               */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
   /* * NOTE * These values are specified in 0.625ms increments.        */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_INTERVAL_MINIMUM                    0x000020
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_INTERVAL_MAXIMUM                    0xFFFFFF

   /* The following constants represent the Peer_Address_Type parameter */
   /* for the qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters()     */
   /* command, and the Peer_Identity_Address_Type parameter for the     */
   /* qapi_BLE_HCI_LE_Set_Privacy_Mode() command. (Version 5.0 + LE).   */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_PEER_ADDRESS_TYPE_PUBLIC            0x00
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_PEER_ADDRESS_TYPE_RANDOM            0x01

   /* The following constants represent the Advertising_Tx_Power and    */
   /* Selected_Tx_Power parameters for the                              */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters() command, and*/
   /* the Min_Tx_Power and Max_Tx_Power parameters for the              */
   /* qapi_BLE_HCI_LE_Read_Transmit_Power() command. (Version 5.0 + LE).*/
   /* * NOTE * These values are specified in dBm.                       */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_TRANSMIT_POWER_MINIMUM              (-127)
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_TRANSMIT_POWER_MAXIMUM              (126)

   /* The following constants represent the                             */
   /* Secondary_Advertising_Max_Skip parameter for the                  */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_SECONDARY_ADVERTISING_MAX_SKIP_DISABLED                  0x00

   /* The following constants represent the                             */
   /* Scan_Request_Notification_Enable parameter for the                */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_SCAN_REQUEST_NOTIFICATIONS_DISABLED                      0x00
#define QAPI_BLE_HCI_LE_SCAN_REQUEST_NOTIFICATIONS_ENABLED                       0x01

   /* The following constants represent the Operation parameter for the */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(),                  */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(), and            */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data() commands. (Version*/
   /* 5.0 + LE).                                                        */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_OPERATION_INTERMEDIATE_FRAGMENT     0x00
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_OPERATION_FIRST_FRAGMENT            0x01
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_OPERATION_LAST_FRAGMENT             0x02
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_OPERATION_COMPLETE                  0x03
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_OPERATION_UNCHANGED                 0x04

   /* The following constants represent the Fragment Prference parameter*/
   /* for the qapi_BLE_HCI_LE_Set_Extended_Advertising_Data() and       */
   /* qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(), commands.      */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_FRAGMENT_PREFERENCE_PERMITTED       0x00
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_FRAGMENT_PREFERENCE_MINIMIZE        0x01

   /* The following constants represent the Number_of_Sets parameter for*/
   /* the qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable() command.    */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_NUMBER_OF_SETS_ALL                  0x00
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_NUMBER_OF_SETS_MINIMUM              0x01
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_NUMBER_OF_SETS_MAXIMUM              0x3F

   /* The following constants represent the Duration parameter for the  */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable() command.        */
   /* (Version 5.0 + LE).                                               */
   /* * NOTE * These values are specified in 10 ms increments.          */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_DURATION_DISABLED                   0x0000
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_DURATION_MINIMUM                    0x0001
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_DURATION_MAXIMUM                    0xFFFF

   /* The following constants represent the                             */
   /* Max_Extended_Advertising_Events parameter for the                 */
   /* qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable() command.        */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_MAX_EVENTS_DISABLE                  0x00

   /* The following constant represents the maximum amount of data      */
   /* specified per HCI Command (per call to                            */
   /* HCI_LE_Set_Extended_Advertising_Data(), or                        */
   /* HCI_LE_Set_Extended_Scan_Response_Data() or                       */
   /* HCI_LE_Set_Periodic_Advertising_Response_Data().  (Version 5.0 +  */
   /* LE).                                                              */
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_LENGTH_MAXIMUM_PER_HCI_COMMAND          251

   /* The following constants represent the                             */
   /* Maximum_Advertising_Data_Length parameter for the                 */
   /* qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length() command.   */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_LENGTH_MINIMUM                          0x001F
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_LENGTH_MAXIMUM                          0x0672

   /* The following constants represent the                             */
   /* Num_Supported_Advertising_Sets parameter for the                  */
   /* qapi_BLE_HCI_LE_Read_Number_of_Supported_Advertising_Sets()       */
   /* command. (Version 5.0 + LE).                                      */
#define QAPI_BLE_HCI_LE_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_MINIMUM             0x01
#define QAPI_BLE_HCI_LE_NUMBER_OF_SUPPORTED_ADVERTISING_SETS_MAXIMUM             0xF0

   /* The following constants represent the                             */
   /* Periodic_Advertising_Interval_Min and                             */
   /* Periodic_Advertising_Interval_Max parameters for the              */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
   /* * NOTE * These values are also used with the                      */
   /*          qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters_V2() */
   /*          command (PAWR feature).                                  */
   /* * NOTE * These values are specified in 1.25 ms increments.        */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_INTERVAL_MINIMUM                    0x0006
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_INTERVAL_MAXIMUM                    0xFFFF

   /* The following constants represent the                             */
   /* Periodic_Advertising_Properties parameter for the                 */
   /* qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters() command.    */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_INCLUDE_TX_POWER                    0x20

   /* The following constants represent the Scan_Interval parameter for */
   /* the qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters() and            */
   /* qapi_BLE_HCI_LE_Extended_Create_Connection() commands. (Version   */
   /* 5.0 + LE).                                                        */
   /* * NOTE * These values may also be used for the Scan_Window        */
   /*          parameter for the commands listed above.                 */
   /* * NOTE * These values are specified in 0.625ms increments.        */
#define QAPI_BLE_HCI_LE_EXTENDED_SCAN_INTERVAL_MINIMUM                           0x0004
#define QAPI_BLE_HCI_LE_EXTENDED_SCAN_INTERVAL_MAXIMUM                           0xFFFF

   /* The following constants represent the duration for enabling       */
   /* Extended Advertising. (Version 5.0 + LE).                         */
   /* * NOTE * These values are specified in 1.28 second increments.    */
#define QAPI_BLE_HCI_LE_EXTENDED_SCAN_PERIODIC_SCANNING_DISABLED                 0x0000
#define QAPI_BLE_HCI_LE_EXTENDED_SCAN_PERIODIC_SCANNING_MINIMUM                  0x0001
#define QAPI_BLE_HCI_LE_EXTENDED_SCAN_PERIODIC_SCANNING_MAXIMUM                  0xFFFF

   /* The following constants represent the Filter_Policy parameter for */
   /* the qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync() command.   */
   /* (Version 5.0 + LE).                                               */
   /* * NOTE *                                                          */
   /*          QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_FILTER_POLICY_PARAME*/
   /*          indicates that the Advertising_SID,                      */
   /*          Advertising_ADdress_Type, and Advertising_Address        */
   /*          parameters will be used to determine which advertising to*/
   /*          listen to.                                               */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_FILTER_POLICY_PARAMETERS                0x00
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_FILTER_POLICY_PERIODIC_ADVERTISER_LIST  0x01

   /* The following constants represent the Advertising_SID parameter   */
   /* for the qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync(),       */
   /* qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Cancel(),        */
   /* qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List(), and     */
   /* qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List()     */
   /* commands. (Version 5.0 + LE).                                     */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SID_MINIMUM                         0x00
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SID_MAXIMUM                         0x0F

   /* The following constants represent the Skip parameter for the      */
   /* qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync() command.       */
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SKIP_MINIMUM                        0x0000
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SKIP_MAXIMUM                        0x01F3

   /* The following constants represent the Sync_Timeout parameter for  */
   /* the qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync() command.   */
   /* (Version 5.0 + LE).                                               */
   /* * NOTE * These values are specified in 10ms increments.           */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_TIMEOUT_MINIMUM                0x000A
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_TIMEOUT_MAXIMUM                0x4000

   /* The following constants represent the Sync_Handle parameter for   */
   /* the qapi_BLE_HCI_LE_Periodic_Advertising_Terminate_Sync() command.*/
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_HANDLE_MINIMUM                 0x0000
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_HANDLE_MAXIMUM                 0x0EFF

   /* The following constants represent the Advertising_Handle parameter*/
   /* returned for an LE Enhanced Connection Complete v2 event to denote*/
   /* that the Sync Handle is not valid.                                */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_HANDLE_NO_SYNC_HANDLE          0xFFFF

   /* The following constants represent the                             */
   /* Periodic_Advertiser_List_Size parameter for the                   */
   /* HCI_LE_Read_Periodic_Advertiser_List_Size() command. (Version 5.0 */
   /* + LE).                                                            */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_LIST_SIZE_MINIMUM                   0x01
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_LIST_SIZE_MAXIMUM                   0xFF

   /* The following constants represent the                             */
   /* RF_Tx_Path_Compensation_Value and RF_Tx_Path_Compensation_Value   */
   /* parameters for the HCI_LE_Write_RF_Path_Compensation() and        */
   /* qapi_BLE_HCI_LE_Write_RF_Path_Compensation() commands. (Version   */
   /* 5.0 + LE).                                                        */
   /* * NOTE * These values are specified in .1dB increments.           */
#define QAPI_BLE_HCI_LE_RF_PATH_COMPENSATION_VALUE_MINIMUM                       0xFB00
#define QAPI_BLE_HCI_LE_RF_PATH_COMPENSATION_VALUE_MAXIMUM                       0x0500

   /* The following constants represent the Privacy_Mode parameter for  */
   /* the qapi_BLE_HCI_LE_Set_Privacy_Mode() command. (Version 5.0 +    */
   /* LE).                                                              */
#define QAPI_BLE_HCI_LE_PRIVACY_MODE_NETWORK_MODE                                0x00
#define QAPI_BLE_HCI_LE_PRIVACY_MODE_DEVICE_MODE                                 0x01

   /* The following constants indicate the valid bits that may be set in*/
   /* the Enable parameter to the HCI LE Set Periodic Advertising       */
   /* Receive enable command.  (Version 5.1 + LE).                      */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RECEIVE_ENABLE_REPORTING_ENABLED         0x01
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RECEIVE_ENABLE_DUPLICATE_FILTER_ENABLED  0x02

   /* The following constants indicate the periodic advertising sync    */
   /* transfer mode. (Version 5.1 + LE).                                */
#define QAPI_BLE_HCI_LE_PAST_MODE_DO_NOT_NOTIFY_HOST                                0x00
#define QAPI_BLE_HCI_LE_PAST_MODE_NOTIFY_HOST_AND_DISABLE_PAR_EVENTS                0x01
#define QAPI_BLE_HCI_LE_PAST_MODE_NOTIFY_HOST_AND_ENABLE_PAR_EVENTS                 0x02
#define QAPI_BLE_HCI_LE_PAST_MODE_NOTIFY_HOST_AND_ENABLE_PAR_EVENTS_WITH_DUP_FILT   0x03

   /* The following constants define the valid values bits that may be  */
   /* set in the Enable parameter of the HCI LE Set Periodic Advertising*/
   /* Enable command.  (Version 5.0 + LE).                              */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_ENABLE_ENABLED                      0x01
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_ENABLE_INCLUDE_ADI_FIELD            0x02

   /* The following constants represent the possible values that can be */
   /* returned in the Role member of LE Connection Complete Event.      */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_ROLE_IS_MASTER                                           0x00
#define QAPI_BLE_HCI_LE_ROLE_IS_SLAVE                                            0x01

   /* The following constants represent the possible values that can be */
   /* returned in Master Clock Accuracy member of LE Connection         */
   /* Complete Event.  (Version 4.0 + LE).                              */
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_500_PPM                            0x00
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_250_PPM                            0x01
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_150_PPM                            0x02
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_100_PPM                            0x03
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_75_PPM                             0x04
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_50_PPM                             0x05
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_30_PPM                             0x06
#define QAPI_BLE_HCI_LE_MASTER_CLOCK_ACCURACY_20_PPM                             0x07

   /* The following constants represent the possible values that can be */
   /* returned in an Advertiser_Clock_Accuracy field (LE Periodic       */
   /* Advertising Sync Transfer Received event and LE Periodic          */
   /* Advertising Sync Established event).  (Version 5.1 + LE).         */
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_500_PPM                        0x00
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_250_PPM                        0x01
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_150_PPM                        0x02
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_100_PPM                        0x03
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_75_PPM                         0x04
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_50_PPM                         0x05
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_30_PPM                         0x06
#define QAPI_BLE_HCI_LE_ADVERTISER_CLOCK_ACCURACY_20_PPM                         0x07

   /* The following contants represent the possible Event Type values   */
   /* for the Event Type member of the HCI LE Advertising Report Event. */
   /* (Version 4.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_TYPE_CONNECTABLE_UNDIRECTED     0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_TYPE_CONNECTABLE_DIRECTED       0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_TYPE_SCANNABLE_UNDIRECTED       0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_TYPE_NONCONNECTABLE_UNDIRECTED  0x03
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_TYPE_SCAN_RESPONSE              0x04

   /* The following define the valid bits that may be set in the        */
   /* Event_Type member of the HCI LE Extended Advertising Report Event.*/
   /* (Version 5.0 + LE).                                               */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_CONNECTABLE       0x0001
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_SCANNABLE         0x0002
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DIRECTED          0x0004
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_SCAN_RESPONSE     0x0008
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_LEGACY_PDUS_USED  0x0010
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_MASK              0x001F

   /* The following define the bit number and mask to use when reading  */
   /* the Data Status field that is part of the Event_Type member of the*/
   /* HCI LE Extended Advertising Report Event.  (Version 5.0 + LE).    */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_BIT   5
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_MASK  0x0060

   /* The following constants represent the valid Data Status values    */
   /* that may be returned in the Data Status field of the LE Extended  */
   /* Advertising Report Event and the LE Periodic Advertising Report   */
   /* Event.  (Version 5.0 + LE).                                       */
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_STATUS_COMPLETE                         0x00
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_STATUS_INCOMPLETE_MORE_DATA_TO_COME     0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_STATUS_INCOMPLETE_DATA_TRUNCATED        0x02

   /* The following represents a value that may be dispatched in the    */
   /* Data Status of a Periodic Advertising Report v2 event.            */
#define QAPI_BLE_HCI_LE_ADVERTISING_DATA_STATUS_FAILED_TO_RECEIVE_SUBEVENT_PDU   0xFF

   /* The following constants represent the valid Data Status values    */
   /* that may be returned in the Data Status field of the LE Periodic  */
   /* Advertising Response Report Event.                                */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_DATA_STATUS_COMPLETE                 0x00
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_DATA_STATUS_INCOMPLETE_MORE_TO_COME  0x01
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_DATA_STATUS_FAILED_TO_RECEIVE        0xFF

   /* The following constants represent the valid Tx Status values that */
   /* may be returned in the Tx Status field of the LE Periodic Response*/
   /* Report Event.  (Version 5.4).                                     */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_TX_STATUS_SUBEVENT_IND_PACKET_SENT     0x00
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_TX_STATUS_SUBEVENT_IND_PACKET_NOT_SENT 0x01

   /* The following represents the maximum total amount of data that may*/
   /* be returned in the LE Periodic Response Report Event.             */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_MAXIMUM_DATA_LENGTH ((255 + QAPI_BLE_HCI_EVENT_HEADER_SIZE) - QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_EVENT_SIZE(0) - QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_SIZE(0))

   /* The following constants represent the defined minimum and maximum */
   /* values for the RSSI member of the HCI LE Advertising Report Event */
   /* (respectively).  (Version 4.0 + LE).                              */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_RSSI_VALUE_MINIMUM                    (-127)
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_RSSI_VALUE_MAXIMUM                    (20)

   /* The following constant represents the value that signifies that   */
   /* the RSSI value was not available (RSSI member of the HCI LE       */
   /* Advertising Report Event).  (Version 4.0 + LE).                   */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_RSSI_VALUE_NOT_AVAILABLE              (127)

   /* The following constant represents the value that signifies that   */
   /* the Advertising SID value was not available (Advertising SID      */
   /* member of the HCI LE Extended Advertising Report Event).  (Version*/
   /* 5.0).                                                             */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_ADVERTISING_SID_NOT_AVAILABLE (0xFF)

   /* The following constant represents the value that signifies that   */
   /* the Tx Power value was not available (Tx Power member of the HCI  */
   /* LE Extended Advertising Report Event).  (Version 5.0).            */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_TX_POWER_NOT_AVAILABLE       (127)

   /* The following constant represents the value that signifies that   */
   /* the RSSI value was not available (RSSI member of the HCI LE       */
   /* Extended Advertising Report Event).  (Version 5.0).               */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_RSSI_VALUE_NOT_AVAILABLE     (127)

   /* The following constant represents the value that signifies that   */
   /* the Tx Power value was not available (Tx Power member of the HCI  */
   /* LE Periodic Advertising Report Event).  (Version 5.0).            */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_TX_POWER_NOT_AVAILABLE       (127)

   /* The following constant represents the value that signifies that   */
   /* the RSSI value was not available (RSSI member of the HCI LE       */
   /* Periodic Advertising Report Event).  (Version 5.0).               */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_RSSI_VALUE_NOT_AVAILABLE     (127)

   /* The following constants represent Channel Selection Algorithm     */
   /* values that may be returned in an HCI LE Channel Selection        */
   /* Algorithm Event.                                                  */
#define QAPI_BLE_HCI_LE_CHANNEL_SELECTION_ALGORITHM_EVENT_ALGORITHM_NUM1_USED    0x00
#define QAPI_BLE_HCI_LE_CHANNEL_SELECTION_ALGORITHM_EVENT_ALGORITHM_NUM2_USED    0x01

   /* The following represents the range for the number of subevents    */
   /* passed to the HCI_LE_Set_Periodic_Advertising_Parameters_V2       */
   /* command (Version 5.4).                                            */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_SUBEVENTS_MIN     0x00
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_SUBEVENTS_MAX     0x80

   /* The following represents the range for the subevent interval      */
   /* passed to the HCI_LE_Set_Periodic_Advertising_Parameters_V2       */
   /* command (Version 5.4).                                            */
   /* * NOTE * These values are specified in 1.25 ms increments.        */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_SUBEVENT_INTERVAL_MIN 0x06
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_SUBEVENT_INTERVAL_MAX 0xFF

   /* The following represents the range for the response slot delay    */
   /* passed to the HCI_LE_Set_Periodic_Advertising_Parameters_V2       */
   /* command (Version 5.4).                                            */
   /* * NOTE * These values are specified in 1.25 ms increments.        */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOT_DELAY_MIN 0x01
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOT_DELAY_MAX 0xFE

   /* The following represents the range for the periodic advertising   */
   /* response slot spacing passed to the                               */
   /* HCI_LE_Set_Periodic_Advertising_Parameters_V2 command (Version    */
   /* 5.4).                                                             */
   /* * NOTE * These values are specified in 0.125 ms increments.       */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOT_SPACING_MIN 0x02
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOT_SPACING_MAX 0xFF

   /* The following represents the range for the periodic advertising   */
   /* response slot spacing.                                            */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOTS_MIN    0x01
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_V2_RESP_SLOTS_MAX    0xFE

   /* The following represents the range for the periodic advertising   */
   /* response subevent index.                                          */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SUBEVENT_INDEX_MINIMUM              0x00
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SUBEVENT_INDEX_MAXIMUM              0x7F

   /* The following represents the range for the periodic advertising   */
   /* response slots passed to the                                      */
   /* HCI_LE_Set_Periodic_Advertising_Response_Data command (Version    */
   /* 5.4).                                                             */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_RESP_SLOT_MIN     0x00
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA_RESP_SLOT_MAX     0xFF

   /* The following represents the range for the number of subevents    */
   /* passed to the HCI_LE_Set_Periodic_Advertising_Subevent_Data       */
   /* command (Version 5.4).                                            */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_SUBEVENT_MIN      0x01
#define QAPI_BLE_HCI_LE_SET_PERIODIC_ADVERTISING_SUBEVENT_DATA_SUBEVENT_MAX      0x0F

   /* The following represents the range for the number of subevents    */
   /* passed to the HCI_LE_Set_Periodic_Sync_Subevent command (Version  */
   /* 5.4).                                                             */
#define QAPI_BLE_HCI_LE_SET_PERIODIC_SYNC_SUBEVENT_SUBEVENT_MIN                  0x01
#define QAPI_BLE_HCI_LE_SET_PERIODIC_SYNC_SUBEVENT_SUBEVENT_MAX                  0x80

   /* The following represents the range for the number of subevents    */
   /* passed to the HCI_LE_Extended_Create_Connection_V2 command        */
   /* (Version 5.4).                                                    */
#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_V2_SUBEVENT_MIN               0x01
#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_V2_SUBEVENT_MAX               0x7F
#define QAPI_BLE_HCI_LE_EXTENDED_CREATE_CONNECTION_V2_SUBEVENT_NOT_USED          0xFF

   /* The following represents the value returned in the LE Periodic    */
   /* Advertising Report v2 event to indicate that the subevent field is*/
   /* not valid.                                                        */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_V2_EVENT_SUBEVENT_NOT_USED   0xFF

   /* The following constants represent the defined Bluetooth Types that*/
   /* specify the specific Bluetooth HCI Advertising Report Event Data  */
   /* Types used with the Advertising Report Event (Version 4.0 + LE).  */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_FLAGS                                      0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_16_BIT_SERVICE_UUID_PARTIAL                0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_16_BIT_SERVICE_UUID_COMPLETE               0x03
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_32_BIT_SERVICE_UUID_PARTIAL                0x04
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_32_BIT_SERVICE_UUID_COMPLETE               0x05
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_128_BIT_SERVICE_UUID_PARTIAL               0x06
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_128_BIT_SERVICE_UUID_COMPLETE              0x07
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LOCAL_NAME_SHORTENED                       0x08
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LOCAL_NAME_COMPLETE                        0x09
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_TX_POWER_LEVEL                             0x0A
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_CLASS_OF_DEVICE                            0x0D
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SECURITY_MANAGER_TK_VALUE                  0x10
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SECURITY_MANAGER_OOB_FLAGS                 0x11
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE            0x12
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_SOLICITATION_16_BIT_SERVICE_UUID   0x14
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_SOLICITATION_128_BIT_SERVICE_UUID  0x15
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_DATA                               0x16
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_PUBLIC_TARGET_ADDRESS                      0x17
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_RANDOM_TARGET_ADDRESS                      0x18
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_APPEARANCE                                 0x19
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_ADVERTISING_INTERVAL                       0x1A
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS                0x1B
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LE_ROLE                                    0x1C
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_SOLICITATION_32_BIT_SERVICE_UUID   0x1F
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_DATA_32_BIT_UUID                   0x20
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_SERVICE_DATA_128_BIT_UUID                  0x21
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LE_SECURE_CONNECTIONS_CONFIRMATION_VALUE   0x22
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LE_SECURE_CONNECTIONS_RANDOM_VALUE         0x23
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_URI                                        0x24
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_INDOOR_POSITIONING                         0x25
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_TRANSPORT_DISCOVERY                        0x26
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LE_SUPPORTED_FEATURES                      0x27
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_CHANNEL_MAP_UPDATE_INDICATION              0x28
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_PB_ADV                                     0x29
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_MESH_MESSAGE                               0x2A
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_MESH_BEACON                                0x2B
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_BIG_INFO                                   0x2C
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_BROADCAST_INFO                             0x2D
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_RESOLVABLE_SET_IDENTIFER                   0x2E
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_ADVERTISING_INTERVAL_LONG                  0x2F
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_BROADCAST_NAME                             0x30
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_ENCRYPTED_DATA                             0x31
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_3D_INFORMATION_DATA                        0x3D
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_MANUFACTURER_SPECIFIC                      0xFF

   /* The following constants represent the defined Bit Mask values of  */
   /* the bit mask values in the Bluetooth HCI Advertising Report Data  */
   /* Flags Field (Version 4.0 + LE).                                   */
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_LIMITED_DISCOVERABLE_MODE_FLAGS_BIT_MASK                  0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_GENERAL_DISCOVERABLE_MODE_FLAGS_BIT_MASK                  0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_BR_EDR_NOT_SUPPORTED_FLAGS_BIT_MASK                       0x04
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SIMULTANEOUS_LE_BR_EDR_TO_SAME_DEVICE_CONTROLLER_BIT_MASK 0x08
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SIMULTANEOUS_LE_BR_EDR_TO_SAME_DEVICE_HOST_BIT_MASK       0x10

   /* The following constants represent the defined Bit Mask values of  */
   /* the bit mask values in the Bluetooth HCI Advertising Report Data  */
   /* Security Manager OOB Flags Field (Version 4.0 + LE).              */
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SECURITY_MANAGER_OOB_FLAGS_OOB_DATA_PRESENT_BIT_MASK       0x01
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SECURITY_MANAGER_OOB_FLAGS_LE_HOST_SUPPORT_BIT_MASK        0x02
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SECURITY_MANAGER_OOB_FLAGS_SIMULTANEOUS_LE_BR_EDR_BIT_MASK 0x04
#define QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_SECURITY_MANAGER_OOB_FLAGS_ADDRESS_TYPE_BIT_MASK           0x08

   /* The following constants represent the defined Bit Mask values of  */
   /* the bit mask values in the Bluetooth HCI Advertising Report Data  */
   /* LE Role Field (Version 4.0 + CSS v4).                             */
#define QAPI_BLE_HCI_LE_ROLE_ONLY_PERIPHERAL_SUPPORTED                           0x00
#define QAPI_BLE_HCI_LE_ROLE_ONLY_CENTRAL_SUPPORTED                              0x01
#define QAPI_BLE_HCI_LE_ROLE_PERIPHERAL_CENTRAL_SUPPORTED_PERIPHERAL_PREFERRED   0x02
#define QAPI_BLE_HCI_LE_ROLE_PERIPHERAL_CENTRAL_SUPPORTED_CENTRAL_PREFERRED      0x03

   /* The following constants represent the defined values that can be  */
   /* used in the Data_Path paramter to the Enhanced Setup/Accept       */
   /* Synchronous Connection Commands (Version 4.0 + CSA2).             */
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_DATA_PATH_HCI                          0x00
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_DATA_PATH_AUDIO_TEST_MODE              0xFF

   /* The following constants represent the defined values that can be  */
   /* used in the Coding_Format paramter to the Enhanced Setup/Accept   */
   /* Synchronous Connection Commands (Version 4.0 + CSA2).             */
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_ULAW_LOG                 0x00
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_ALAW_LOG                 0x01
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_CVSD                     0x02
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_TRANSPARENT              0x03
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_LINEAR_PCM               0x04
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_MSBC                     0x05
#define QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_VENDOR_SPECIFIC          0xFF

   /* The following Constants represent the defined Class of Device     */
   /* Format Type that can be used with the Class of Device Format      */
   /* Type MACRO's.                                                     */
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_FORMAT_TYPE_1                           0x00

  /* The following Constants represents the defined Class of Device     */
  /* Major Service Class Types that can be used with the Class of       */
  /* Device Major Service Class MACRO's.                                */
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_LIMITED_DISCOVER_MODE_BIT 0x0001
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_POSITIONING_BIT           0x0008
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_NETWORKING_BIT            0x0010
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_RENDERING_BIT             0x0020
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_CAPTURING_BIT             0x0040
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_OBJECT_TRANSFER_BIT       0x0080
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_AUDIO_BIT                 0x0100
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_TELEPHONY_BIT             0x0200
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_SERVICE_CLASS_INFORMATION_BIT           0x0400

  /* The following Constants represents the defined Class of Device     */
  /* Major Device Class Types that can be used with the Class of        */
  /* Device Major Device Class MACRO's.                                 */
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_MISCELLANEOUS        0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_COMPUTER             0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_PHONE                0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_LAN_ACCESS_POINT     0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_AUDIO_VIDEO          0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_PERIPHERAL           0x05
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_IMAGING              0x06
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_WEARABLE             0x07
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_TOY                  0x08
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_HEALTH               0x09
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MAJOR_DEVICE_CLASS_UNCLASSIFIED         0x1F

  /* The following Constants represents the defined Class of Device     */
  /* Minor Device Class Types that can be used with the Class of        */
  /* Device Minor Device Class MACRO's.                                 */
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_UNCLASSIFIED 0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_DESKTOP     0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_SERVER      0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_LAPTOP      0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_HANDHELD    0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_PALM_PC     0x05
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_COMPUTER_WEARABLE    0x06

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_UNCLASSIFIED   0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_CELLULAR       0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_CORDLESS       0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_SMARTPHONE     0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_WIRED_MODEM    0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_VOICE_GATEWAY  0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PHONE_ISDN_ACCESS    0x05

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_LOAD_FACTOR_MASK 0x38
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_SUB_FIELD_MASK   0x07

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_FULLY_AVAILABLE  0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_1_17_UTILIZED    0x08
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_17_33_UTILIZED   0x10
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_33_50_UTILIZED   0x18
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_50_67_UTILIZED   0x20
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_67_83_UTILIZED   0x28
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_83_99_UTILIZED   0x30
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_NO_SERVICE       0x38

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_LAN_SUB_FIELD_UNCLASSIFIED 0x00

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_UNCLASSIFIED              0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HEADSET                   0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HANDS_FREE                0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_MICROPHONE                0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_LOUD_SPEAKER              0x05
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HEADPHONES                0x06
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_PORTABLE_AUDIO            0x07
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_CAR_AUDIO                 0x08
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_SET_TOP_BOX               0x09
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HIFI_AUDIO_DEVICE         0x0A
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VCR                       0x0B
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_CAMERA              0x0C
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_CAMCORDER                 0x0D
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_MONITOR             0x0E
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_DISPLAY_LOUDSPEAKER 0x0F
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_VIDEO_CONFERENCING              0x10
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_AUDIO_GAMING_TOY                      0x12

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_UNCLASSIFIED               0x00
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_JOYSTICK                   0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_GAMEPAD                    0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_REMOTE_CONTROL             0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_SENSING_DEVICE             0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_DIGITIZER_TABLET           0x05
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_CARD_READER                0x06
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_DIGITAL_PEN                0x07
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_HANDHELD_SCANNER_RFID      0x08
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_HANDHELD_GESTURAL_INPUT    0x09

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_KEYBOARD_MASK                 0x10
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_POINTING_DEVICE_MASK          0x20
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_PERIPHERAL_KEYBOARD_POINTING_DEVICE_MASK 0x30

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_IMAGING_UNCLASSIFIED 0x00

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_IMAGING_DISPLAY_MASK 0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_IMAGING_CAMERA_MASK  0x08
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_IMAGING_SCANNER_MASK 0x10
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_IMAGING_PRINTER_MASK 0x20

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_UNCLASSIFIED   0x00

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_WRIST_WATCH    0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_PAGER          0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_JACKET         0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_HELMET         0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_WEARABLE_GLASSES        0x05

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_UNCLASSIFIED       0x00

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_ROBOT              0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_VEHICLE            0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_DOLL_ACTION_FIGURE 0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_CONTROLLER         0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_CLASS_TOY_GAME               0x05

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_UNCLASSIFIED              0x00

#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_BLOOD_PRESSURE_MONITOR    0x01
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_THERMOMETER               0x02
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_WEIGHING_SCALE            0x03
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_GLUCOSE_METER             0x04
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_PULSE_OXIMETER            0x05
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_HEART_PULSE_RATE_MONITOR  0x06
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_HEALTH_DATA_DISPLAY       0x07
#define QAPI_BLE_HCI_LMP_CLASS_OF_DEVICE_MINOR_DEVICE_HEALTH_STEP_COUNTER              0x08

#endif
