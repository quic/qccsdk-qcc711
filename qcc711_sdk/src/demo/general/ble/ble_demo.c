/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdio.h>

#include "ble_demo.h"
#include "bas_demo.h"

#include "qcli_api.h"
#include "qcli_util.h"
#include "qcli_pal.h"

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_task.h"
#include "qapi_heap.h"
#include "qapi_radio.h"

#include "qapi_ble_errors.h"
#include "qapi_ble_bsc.h"
#include "qapi_ble_hci.h"
#include "qapi_ble_hcitypes.h"
#include "qapi_ble_gap.h"
#include "qapi_ble_gatt.h"
#include "qapi_ble_gaps.h"

/* Macros to unpack unaligned data. */
#define READ_UNALIGNED_BYTE_LITTLE_ENDIAN(_x)                  (((uint8_t *)(_x))[0])
#define READ_UNALIGNED_WORD_LITTLE_ENDIAN(_x)                  ((uint16_t)((((uint16_t)(((uint8_t *)(_x))[1])) << 8) | ((uint16_t)(((uint8_t *)(_x))[0]))))

/* The device name of the QCLI BLE Qdemo. */
#define QCLI_BLE_DEMO_DEVICE_NAME                              "QCLIBLE"

/* The max length of the string used in main BLE demo. */
#define QCLI_BLE_DEMO_STRING_LEN                               (64)

/* The Encryption Root Key. */
static qapi_BLE_Encryption_Key_t ER = {0x28, 0xBA, 0xE1, 0x37, 0x13, 0xB2, 0x20, 0x45, 0x16, 0xB2, 0x19, 0xD0, 0x80, 0xEE, 0x4A, 0x51};

/* The Identity Root Key. */
static qapi_BLE_Encryption_Key_t IR = {0x41, 0x09, 0xA0, 0x88, 0x09, 0x6B, 0x70, 0xC0, 0x95, 0x23, 0x3C, 0x8C, 0x48, 0xFC, 0xC9, 0xFE};

/* Structure holds the mapping betwwen appearance and appearance string . */
typedef struct GAPS_Device_Appearance_Mapping_s
{
   uint16_t  Appearance;
   char     *String;
} GAPS_Device_Appearance_Mapping_t;

/* The appearance and appearacne string mapping table. */
static GAPS_Device_Appearance_Mapping_t AppearanceMappings[] =
{
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_UNKNOWN,                        "Unknown"                   },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_PHONE,                  "Generic Phone"             },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_COMPUTER,               "Generic Computer"          },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_WATCH,                  "Generic Watch"             },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_SPORTS_WATCH,                   "Sports Watch"              },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_CLOCK,                  "Generic Clock"             },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_DISPLAY,                "Generic Display"           },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_GENERIC_REMOTE_CONTROL, "Generic Remote Control"    },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_EYE_GLASSES,            "Eye Glasses"               },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_TAG,                    "Generic Tag"               },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_KEYRING,                "Generic Keyring"           },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_MEDIA_PLAYER,           "Generic Media Player"      },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_BARCODE_SCANNER,        "Generic Barcode Scanner"   },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_THERMOMETER,            "Generic Thermometer"       },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_THERMOMETER_EAR,                "Ear Thermometer"           },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_HEART_RATE_SENSOR,      "Generic Heart Rate Sensor" },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BELT_HEART_RATE_SENSOR,         "Belt Heart Rate Sensor"    },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_BLOOD_PRESSURE,         "Generic Blood Pressure"    },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BLOOD_PRESSURE_ARM,             "Blood Pressure: ARM"       },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BLOOD_PRESSURE_WRIST,           "Blood Pressure: Wrist"     },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HUMAN_INTERFACE_DEVICE,         "Human Interface Device"    },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_KEYBOARD,                   "HID Keyboard"              },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_MOUSE,                      "HID Mouse"                 },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_JOYSTICK,                   "HID Joystick"              },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_GAMEPAD,                    "HID Gamepad"               },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_DIGITIZER_TABLET,           "HID Digitizer Tablet"      },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_CARD_READER,                "HID Card Reader"           },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_DIGITAL_PEN,                "HID Digitizer Pen"         },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_BARCODE_SCANNER,            "HID Bardcode Scanner"      },
   { QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_GLUCOSE_METER,          "Generic Glucose Meter"     }
};

#define NUMBER_OF_APPEARANCE_MAPPINGS        (sizeof(AppearanceMappings)/sizeof(GAPS_Device_Appearance_Mapping_t))

/* Mapping table for ATT Error Codes to a printable string. */
static const char *ErrorCodeStr[] =
{
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_NO_ERROR",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_HANDLE",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_READ_NOT_PERMITTED",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_WRITE_NOT_PERMITTED",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_PDU",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_AUTHENTICATION",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_REQUEST_NOT_SUPPORTED",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_OFFSET",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_AUTHORIZATION",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_PREPARE_QUEUE_FULL",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_ATTRIBUTE_NOT_FOUND",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_ATTRIBUTE_NOT_LONG",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_ENCRYPTION_KEY_SIZE",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_ATTRIBUTE_VALUE_LENGTH",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_UNLIKELY_ERROR",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_ENCRYPTION",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_UNSUPPORTED_GROUP_TYPE",
   "QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_RESOURCES"
};

#define NUMBER_OF_ERROR_CODES                (sizeof(ErrorCodeStr)/sizeof(char *))

/* Structure represents the HCI version string. */
static const char *HCI_Version_Strings[] =
{
   "1.0b",
   "1.1",
   "1.2",
   "2.0",
   "2.1",
   "3.0",
   "4.0",
   "4.1",
   "4.2",
   "5.0",
   "5.1",
   "5.2",
   "5.3",
   "5.4",
   "Unknown"
};

#define NUMBER_OF_SUPPORTED_HCI_VERSIONS     (sizeof(HCI_Version_Strings)/sizeof(char *) - 1)

/* Mapping of address types to a printable string. */
static const char *Address_Type_Strings[] =
{
   "Public",
   "Random",
   "Public Identity",
   "Random Identity",
   "Resolvable Fallback Public",
   "Resolvable Fallback Private",
   "Anonymous",
   "Unknown"
};

#define NUMBER_OF_ADDRESS_TYPES              (sizeof(Address_Type_Strings)/sizeof(char *) - 1)

/* Mapping of filter policiy types to a printable string. */
static const char *Filter_Policy_Strings[] =
{
   "No Filter",
   "White List",
   "No White List Directed RPA",
   "White List Directed RPA",
   "Unknown"
};

#define NUMBER_OF_FILTER_POLICIES            (sizeof(Filter_Policy_Strings)/sizeof(char *) - 1)

/* Structure represents the scan parameters. */
typedef struct Scan_Parameters_s
{
   qapi_BLE_GAP_LE_Scan_Type_t     ScanType;
   uint32_t                        ScanInterval;
   uint32_t                        ScanWindow;
   qapi_BLE_GAP_LE_Address_Type_t  LocalAddressType;
   qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;
   qbool_t                         FilterDuplicates;
} Scan_Parameters_t;

/* Structure represents the pair parameters. */
typedef struct Pair_Parameters_s
{
   qapi_BLE_GAP_LE_IO_Capability_t IOCapability;
   qbool_t                         MITMProtection;
   qbool_t                         SecureConnections;
   qbool_t                         OOBDataPresent;
} Pair_Parameters_t;

/* Advertising configurations. */
typedef struct Advertising_Parameters_s
{
   qapi_BLE_GAP_LE_Advertising_Parameters_t Parameters;                             /*< The advertising paramters. */
   qbool_t                                  BREDRSupport;                           /*< The flag to configure BREDR support in advertising data. */
   qbool_t                                  ScanResponse;                           /*< The flag to configure if scan response should be enabled. */
} Advertising_Parameters_t;

/* Structure represents the main BLE demo context information. */
typedef struct BLE_Demo_Context_s
{
   QCLI_Group_Handle_t                          QCLI_Handle;                        /*< QCLI handle for the main BLE demo. */
   qapi_BLE_HCI_DriverInformation_t            *DriverInformation;                  /*< The HCI driver informaiton. */
   uint32_t                                     BluetoothStackID;                   /*< Bluetooth stack ID provided by the Bluetooth stack when initialized. */
   uint32_t                                     GAPInstanceID;                      /*< The ID for the GAP instance. */
   qapi_BLE_GAP_Discoverability_Mode_t          DiscoverabilityMode;                /*< The discoverability configuration. */
   qapi_BLE_GAP_LE_Connection_Parameters_t      ConnectionParamters;                /*< The connection parameters. */
   qapi_BLE_GAP_LE_Connectability_Parameters_t  AdvertiseConnectabilityParameters;  /*< The advertsing connectability parameters. */
   Advertising_Parameters_t                     AdvertisingParameters;              /*< The advertsing parameters. */
   Scan_Parameters_t                            ScanParameters;                     /*< The parameters used by the scan procedure. */
   qbool_t                                      ScanInProgress;                     /*< The flag indicates if a scanning is in progress. */
   Pair_Parameters_t                            PairParameters;                     /*< The parameters used by pairring procedure. */
   qbool_t                                      LocalDeviceIsMaster;                /*< The flag indicates if the local device is a master in a connection procedure. */
                                                                                    /*< It will be stored in the device info when connection is completed. */
   qapi_BLE_GAP_LE_Address_Type_t               ConnectingDeviceAddressType;        /*< The address type of the remote device in a conncetion procedure. */
                                                                                    /*< It will be stored in the device info when connection is completed. */
   qapi_BLE_BD_ADDR_t                           ActiveConnectionBD_ADDR;            /*< The BD ADDR of the current active connected remote device. */
   uint32_t                                     ActiveConnectionID;                 /*< The ID of the current active connection. */
   qapi_BLE_BD_ADDR_t                           SecurityRemoteBD_ADDR;              /*< The BD ADDR of the device currently being paied or authenticated. */
   qapi_BLE_Encryption_Key_t                    DHK;                                /*< The Diversifier hiding key. */
   qapi_BLE_Encryption_Key_t                    IRK;                                /*< The Identity resolving key. */
   uint32_t                                     ConnectedDeviceCounter;             /*< The number of connected devices. */
   Generic_Device_Info_t                       *DeviceInfoList;                     /*< The list of connected devices. */
   uint32_t                                     CustomServiceID;                    /*< Identifies the registered custom service. */
} BLE_Demo_Context_t;

   /* The following structure represents the TLV for advertising data   */
   /* and scan response data.                                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct _tagAdvertising_Data_TLV_t
{
   uint8_t Length;
   uint8_t Type;
   uint8_t Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ Advertising_Data_TLV_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to determine the size (in bytes) of an individual     */
   /* advertising data entry. The first parameter to this MACRO is the  */
   /* length (in bytes) of the variable data.                           */
#define ADVERTISING_DATA_TLV_SIZE(_x)           (sizeof(Advertising_Data_TLV_t) - sizeof(uint8_t) + ((unsigned int)(_x)))

   /* The following MACRO is a utility MACRO that assigns the CUSTOM    */
   /* Service 16 bit UUID to the specified UUID_128_t variable. This    */
   /* MACRO accepts one parameter which is a pointer to a UUID_128_t    */
   /* variable that is to receive the CUSTOM UUID Constant value.       */
   /* * NOTE * The UUID will be assigned into the UUID_128_t variable in*/
   /*          Little-Endian format.                                    */
#define CUSTOM_ASSIGN_SERVICE_UUID_128(_x)                     QAPI_BLE_ASSIGN_BLUETOOTH_UUID_128((_x), 0x64, 0x48, 0xF7, 0xF8, 0xEC, 0x36, 0x48, 0x8B, 0x90, 0xAA, 0xA3, 0x73, 0xD8, 0x0B, 0xF4, 0xF2)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CUSTOM Service UUID in UUID16 form. This   */
   /* MACRO only returns whether the UUID_128_t variable is equal to the*/
   /* CUSTOM Service UUID (MACRO returns boolean result) NOT less       */
   /* than/greater than. The first parameter is the UUID_128_t variable */
   /* to compare to the CUSTOM Service UUID.                            */
#define CUSTOM_COMPARE_CUSTOM_SERVICE_UUID_TO_UUID_128(_x)     QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), 0x64, 0x48, 0xF7, 0xF8, 0xEC, 0x36, 0x48, 0x8B, 0x90, 0xAA, 0xA3, 0x73, 0xD8, 0x0B, 0xF4, 0xF2)

   /* The following defines the CUSTOM Service UUID that is used when   */
   /* building the CUSTOM Service Table.                                */
#define CUSTOM_SERVICE_UUID_CONSTANT                           { 0xF2, 0xF4, 0x0B, 0xD8, 0x73, 0xA3, 0xAA, 0x90, 0x8B, 0x48, 0x36, 0xEC, 0xF8, 0xF7, 0x48, 0x64 }

   /* The following MACRO is a utility MACRO that assigns the CUSTOM    */
   /* Characteristic 16 bit UUID to the specified UUID_128_t variable.  */
   /* This MACRO accepts one parameter which is the UUID_128_t variable */
   /* that is to receive the CUSTOM TX UUID Constant value.             */
   /* * NOTE * The UUID will be assigned into the UUID_128_t variable in*/
   /*          Little-Endian format.                                    */
#define CUSTOM_READ_CHARACTERISTIC_ASSIGN_CHARACTERISTIC_UUID_128(_x)              QAPI_BLE_ASSIGN_BLUETOOTH_UUID_128((_x), 0xB7, 0x8D, 0xC7, 0xD5, 0xC6, 0xED, 0x47, 0x65, 0xB1, 0x6E, 0x48, 0x4B, 0xFC, 0x17, 0xC3, 0xE8)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CUSTOM TX UUID in UUID16 form. This MACRO  */
   /* only returns whether the UUID_128_t variable is equal to the UUID */
   /* (MACRO returns boolean result) NOT less than/greater than. The    */
   /* first parameter is the UUID_128_t variable to compare to the      */
   /* CUSTOM TX UUID.                                                   */
#define CUSTOM_READ_CHARACTERISTIC_COMPARE_CHARACTERISTIC_UUID_TO_UUID_128(_x)     QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), 0xB7, 0x8D, 0xC7, 0xD5, 0xC6, 0xED, 0x47, 0x65, 0xB1, 0x6E, 0x48, 0x4B, 0xFC, 0x17, 0xC3, 0xE8)

   /* The following defines the CUSTOM TX Characteristic UUID that is   */
   /* used when building the CUSTOM Service Table.                      */
#define CUSTOM_READ_CHARACTERISTIC_CHARACTERISTIC_UUID_CONSTANT                    { 0xE8, 0xC3, 0x17, 0xFC, 0x4B, 0x48, 0x6E, 0xB1, 0x65, 0x47, 0xED, 0xC6, 0xD5, 0xC7, 0x8D, 0xB7 }

   /* Custom service declaration.                                       */
static QAPI_BLE_CONST qapi_BLE_GATT_Primary_Service_128_Entry_t Custom_Service_UUID =
{
   CUSTOM_SERVICE_UUID_CONSTANT
} ;

   /* Custom read characteristic declaration.                           */
static QAPI_BLE_CONST qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t Custom_Read_Characteristic_Declaration =
{
   QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_READ,
   CUSTOM_READ_CHARACTERISTIC_CHARACTERISTIC_UUID_CONSTANT
} ;

   /* Custom read characteristic value.                                 */
static QAPI_BLE_CONST qapi_BLE_GATT_Characteristic_Value_128_Entry_t  Custom_Read_Characteristic_Value =
{
   CUSTOM_READ_CHARACTERISTIC_CHARACTERISTIC_UUID_CONSTANT,
   0,
   NULL
} ;

   /* Hold's custom service that is registered with the                 */
   /* GATT_Register_Service function call.                              */
QAPI_BLE_CONST qapi_BLE_GATT_Service_Attribute_Entry_t Custom_Service_Table[] =
{
   { QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE, QAPI_BLE_AET_PRIMARY_SERVICE_128_E,            (uint8_t *)&Custom_Service_UUID                    },
   { QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE, QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E, (uint8_t *)&Custom_Read_Characteristic_Declaration },
   { QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE, QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E,       (uint8_t *)&Custom_Read_Characteristic_Value       },
} ;

#define CUSTOM_SERVICE_ATTRIBUTE_COUNT                         (sizeof(Custom_Service_Table)/sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t))

   /* Hard coded offsets from the custom service table.                 */
#define CUSTOM_READ_CHARACTERISTIC_ATTRIBUTE_OFFSET            2

/* The main BLE demo context. */
static BLE_Demo_Context_t BLE_Demo_Context;

static QCLI_Command_Status_t cmd_BLE_Initialize(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_Shutdown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_GetLocalAddress(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetPairabilityMode(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_GetLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_AdvertiseLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_StartScanning(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_StopScanning(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ConnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_CancelConnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_DisconnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_PairLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_LEPassKeyResponse(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_LEQueryEncryption(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_LESetPasskey(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_DiscoverGAPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ReadLocalName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetLocalName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ReadRemoteName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ReadLocalAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetLocalAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ReadRemoteAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_GetGATTMTU(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetGATTMTU(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_RegisterRemoteAuth(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_SetMaxTxPower(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_DiscoverCustom(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_CustomRead(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_QueryStatistics(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BLE_ClearStatistics(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Callback functions. */
static void BLE_GAP_LE_Event_Callback(uint32_t BluetoothStackID , qapi_BLE_GAP_LE_Event_Data_t *GAP_LE_Event_Data, unsigned long CallbackParameter);
static void BLE_GATT_Connection_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Event_Data_t *GATT_Connection_Event_Data, unsigned long CallbackParameter);
static void BLE_GATT_Service_Discovery_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data, unsigned long CallbackParameter);
static void BLE_GATT_Client_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data, unsigned long CallbackParameter);
static void Custom_GATTServerEventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Server_Event_Data_t *GATT_ServerEventData, unsigned long CallbackParameter);

/* Internal help functions to get and set different LE parameters. */
static void GetDiscoverabilityMode(void);
static qbool_t SetDiscoverabilityMode(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void GetAdvertiseConnectabilityParameters(void);
static qbool_t SetAdvertiseConnectabilityParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void GetAdvertiseLEParameters(void);
static qbool_t SetAdvertiseLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void GetScanParameters(void);
static qbool_t SetScanParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void GetConnectionParameters(void);
static qbool_t SetConnectionParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void GetPairParameters(void);
static qbool_t SetPairParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Internal help functions. */
static void PopulateDefaultLEParameters(void);
static void PopulateExtendedCapabilities(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Capabilities);
static void DisplayAdvertiseData(uint32_t ResponseNumber, qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t *AdvertiseReportData);
static qapi_Status_t SendPairingRequest(qapi_BLE_BD_ADDR_t BD_ADDR, qbool_t LocalIsMaster);
static qapi_Status_t SlavePairingRequestResponse(qapi_BLE_BD_ADDR_t BD_ADDR);
static qapi_Status_t EncryptionInformationRequestResponse(qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t KeySize, qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Response_Information);
static void DisplayLegacyPairingInformation(qapi_BLE_GAP_LE_Pairing_Capabilities_t *Pairing_Capabilities);
static void DisplayPairingInformation(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Pairing_Capabilities);

/* Internal GAPS help functions. */
static void GAPSPopulateHandles(GAPS_Client_Info_t *ClientInfo, qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceInfo);
static qbool_t AppearanceToString(uint16_t Appearance, char **String);

/* Internal Custom service help functions. */
static void CustomPopulateHandles(Custom_Client_Info_t *ClientInfo, qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceInfo);

/* Internal helper functions for device list opeation. */
static Generic_Device_Info_t *CreateNewDeviceInfoEntry(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress);
static Generic_Device_Info_t *SearchDeviceInfoEntryByBD_ADDR(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress);
static Generic_Device_Info_t *SearchDeviceInfoEntryByConnectionID(Generic_Device_Info_t **ListHead, uint32_t ConnectionID);
static Generic_Device_Info_t *DeleteDeviceInfoEntry(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress);
static void FreeDeviceInfoEntryMemory(Generic_Device_Info_t *EntryToFree);
static void FreeDeviceInfoList(Generic_Device_Info_t **ListHead);

/* Internal function to shut down the demo. */
static void ShutDownBLEDemo(void);

/* Command list for the main BLE demo. */
const QCLI_Command_t BLE_CMD_List[] =
{
   /* cmd_function                 cmd_string                      usage_string                                                                                                                    description */
   {cmd_BLE_Initialize,            "Initialize",                   "",                                                                                                                             "Initialize the Bluetopia stack."},
   {cmd_BLE_Shutdown,              "Shutdown",                     "",                                                                                                                             "Shutdown the Bluetopia stack."},
   {cmd_BLE_GetLocalAddress,       "GetLocalAddress",              "",                                                                                                                             "Get local address."},
   {cmd_BLE_SetPairabilityMode,    "SetPairabilityMode",           "[Mode(0=Not Pairable,1=Pairable,2=Pairable(Secure Simple Pairing)]",                                                           "Set pairability mode."},
   {cmd_BLE_GetLEParameters,       "GetLEParameters",              "[Category(0=Discover,1=Connectability,2=Advertise,3=Scan,4=Connection,5=Pair)]",                                               "Get LE parameters."},
   {cmd_BLE_SetLEParameters,       "SetLEParameters",              "[Category(0=Discover,1=Connectability,2=Advertise,3=Scan,4=Connection,5=Pair)][...(Depends on category)]",                     "Set LE parameters."},
   {cmd_BLE_AdvertiseLE,           "AdvertiseLE",                  "[Advertise(0=Disable,1=Enable)]",                                                                                              "Advertise LE."},
   {cmd_BLE_StartScanning,         "StartScanning",                "",                                                                                                                             "Start a scanning operation."},
   {cmd_BLE_StopScanning,          "StopScanning",                 "",                                                                                                                             "Stop a scanning operation."},
   {cmd_BLE_ConnectLE,             "ConnectLE",                    "[Remote BD_ADDR][Remote BD_ADDR Type(0=Public,1=Random)][White List(0=Not use,1=Use)][Local BD_ADDR Type(0=Public,1=Random)]", "Establishes LE connection."},
   {cmd_BLE_CancelConnectLE,       "CancelConnectLE",              "",                                                                                                                             "Cancel LE connection."},
   {cmd_BLE_DisconnectLE,          "DisconnectLE",                 "",                                                                                                                             "Disconnects LE connection."},
   {cmd_BLE_PairLE,                "PairLE",                       "",                                                                                                                             "Pairs with a connected device."},
   {cmd_BLE_LEPassKeyResponse,     "LEPassKeyResponse",            "[Numeric Passkey(0-999999)]",                                                                                                  "Issues a GAP authentication response with a pass key value."},
   {cmd_BLE_LEQueryEncryption,     "LEQueryEncryption",            "",                                                                                                                             "Queries the encryption mode for a LE Connection."},
   {cmd_BLE_LESetPasskey,          "LESetPasskey",                 "[Set/Unset(0=UnSet Passkey,1=Set Fixed Passkey)][6 Digit Passkey(optional)]",                                                  "Sets LE pass key."},
   {cmd_BLE_DiscoverGAPS,          "DiscoverGAPS",                 "",                                                                                                                             "Performs a GAP service discovery."},
   {cmd_BLE_ReadLocalName,         "ReadLocalName",                "",                                                                                                                             "Reads the local name."},
   {cmd_BLE_SetLocalName,          "SetLocalName",                 "[NameString]",                                                                                                                 "Sets the local name."},
   {cmd_BLE_ReadRemoteName,        "ReadRemoteName",               "",                                                                                                                             "Reads the remote name."},
   {cmd_BLE_ReadLocalAppearance,   "ReadLocalAppearance",          "",                                                                                                                             "Reads local appearance."},
   {cmd_BLE_SetLocalAppearance,    "SetLocalAppearance",           "[Index]",                                                                                                                      "Sets local appearance."},
   {cmd_BLE_ReadRemoteAppearance,  "ReadRemoteAppearance",         "[ExtAddr][Key]",                                                                                                               "Reads remote appearance."},
   {cmd_BLE_GetGATTMTU,            "GetGATTMTU",                   "",                                                                                                                             "Gets GATT MTU."},
   {cmd_BLE_SetGATTMTU,            "SetGATTMTU",                   "[GATT MTU(>=%u, <=%u)]",                                                                                                       "sets GATT MTU."},
   {cmd_BLE_RegisterRemoteAuth,    "RegisterRemoteAuthentication", "[1 = Register, 0 = Un-Register]",                                                                                              "Registers for remote authentication"},
   {cmd_BLE_SetMaxTxPower,         "SetMaxTxPower",                "[MaxTxPower ([-31-7])]",                                                                                                       "Sets the maximum TX power for the radio"},
   {cmd_BLE_DiscoverCustom,        "DiscoverCustom",               "",                                                                                                                             "Performs service discover for custom service."},
   {cmd_BLE_CustomRead,            "CustomRead",                   "",                                                                                                                             "Reads the readable characteristic for the custom service."},
   {cmd_BLE_QueryStatistics,       "QueryStatistics",              "",                                                                                                                             "Queries Statistics from the Bluetooth Subsystem."},
   {cmd_BLE_ClearStatistics,       "ClearStatistics",              "[Flags (Optional)]",                                                                                                           "Clear Statistics on the Bluetooth Subsystem."},
};

static const QCLI_Command_Group_t BLE_CMD_Group = {"BLE", sizeof(BLE_CMD_List) / sizeof(QCLI_Command_t), BLE_CMD_List};

/**
   @brief Executes the "Initialize" command to shut down the BT stack.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BLE_Initialize(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qapi_Status_t                          Result;
   QCLI_Command_Status_t                  Ret_Val;
   qapi_BLE_HCI_Version_t                 HCI_Version;
   qapi_BLE_BD_ADDR_t                     BD_ADDR;
   BoardStr_t                             BoardStr;
   uint32_t                               ServiceID;
   qbool_t                                GATTInitialized;
   qapi_BLE_BSC_Version_Information_t     VersionInformation;
   qapi_BLE_GATT_Attribute_Handle_Group_t ServiceHandleGroup;

   if(BLE_Demo_Context.BluetoothStackID == 0)
   {
      GATTInitialized = false;

      /* Verify the BLE stack had not been initialized yet. */
      Result = qapi_BLE_BSC_Initialize(BLE_Demo_Context.DriverInformation, 0);

      if(Result > 0)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BSC layer has been initialized successfully.\r\n");
         BLE_Demo_Context.BluetoothStackID = (uint32_t)Result;
         Ret_Val = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to initialize BSC layer: %d.\r\n", Result);
         Ret_Val = QCLI_STATUS_ERROR_E;
      }

      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         /* Polulate defualt LE parameters. */
         PopulateDefaultLEParameters();

         /* Get the HCI version. */
         Result = qapi_BLE_HCI_Version_Supported(BLE_Demo_Context.BluetoothStackID, &HCI_Version);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "HCI Version: %s.\r\n", ((HCI_Version <= NUMBER_OF_SUPPORTED_HCI_VERSIONS) ? HCI_Version_Strings[HCI_Version]: HCI_Version_Strings[NUMBER_OF_SUPPORTED_HCI_VERSIONS]));
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to get HCI version.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         memset(&VersionInformation, 0, sizeof(qapi_BLE_BSC_Version_Information_t));

         Result = qapi_BLE_BSC_Query_Version_Information(BLE_Demo_Context.BluetoothStackID, &VersionInformation);
         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "ROM Version: 0x%04X\r\n", VersionInformation.ROM_Version);
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Patch Version: 0x%04X.\r\n", VersionInformation.Patch_Version);
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Config Version: 0x%04X.\r\n", VersionInformation.Config_Version);

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to get BSC version information: %d\r\n", Result);

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Set Pairability mode. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAP_LE_Set_Pairability_Mode(BLE_Demo_Context.BluetoothStackID, QAPI_BLE_LPM_PAIRABLE_MODE_ENABLE_EXTENDED_EVENTS_E);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Pairability_Mode", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Register Remote_Authentication. */
      if((Ret_Val == QCLI_STATUS_SUCCESS_E) && (HCI_Version >= QAPI_BLE_HV_SPECIFICATION_4_0_E))
      {
         Result = qapi_BLE_GAP_LE_Register_Remote_Authentication(BLE_Demo_Context.BluetoothStackID, BLE_GAP_LE_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Register_Remote_Authentication", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to register Remote Authentication.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Get the local BRADDR. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAP_Query_Local_BD_ADDR(BLE_Demo_Context.BluetoothStackID, &BD_ADDR);

         if(Result == QAPI_OK)
         {
            BD_ADDRToStr(BD_ADDR, BoardStr);

            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR: %s.\r\n", BoardStr);

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to get local BD_ADDR.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Generate IRK. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAP_LE_Diversify_Function(BLE_Demo_Context.BluetoothStackID, &IR, 1, 0, &(BLE_Demo_Context.IRK));

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Diversify_Function", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to generate IRK.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Generate DHK. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAP_LE_Diversify_Function(BLE_Demo_Context.BluetoothStackID, &IR, 3, 0, &(BLE_Demo_Context.DHK));

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Diversify_Function", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Initialize GATT service. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GATT_Initialize(BLE_Demo_Context.BluetoothStackID, (QAPI_BLE_GATT_INITIALIZATION_FLAGS_SUPPORT_LE | QAPI_BLE_GATT_INITIALIZATION_FLAGS_DISABLE_SERVICE_CHANGED_CHARACTERISTIC), BLE_GATT_Connection_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Initialize", Result);

         if(Result == QAPI_OK)
         {
            GATTInitialized = true;
            Ret_Val         = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            GATTInitialized = false;
            Ret_Val         = QCLI_STATUS_ERROR_E;
         }
      }

      /* Initialize GAPS service. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAPS_Initialize_Service(BLE_Demo_Context.BluetoothStackID, &ServiceID);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Initialize_Service", Result);

         if(Result > 0)
         {
            /* Save the GAP instance ID. */
            BLE_Demo_Context.GAPInstanceID = Result;
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Set device name. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAPS_Set_Device_Name(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, QCLI_BLE_DEMO_DEVICE_NAME);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Set_Device_Name", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Set device apperance. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         Result = qapi_BLE_GAPS_Set_Device_Appearance(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_COMPUTER);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Set_Device_Appearance", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Initialize custom service. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         /* Let GATT select the attribute range of the service in it's  */
         /* database.                                                   */
         ServiceHandleGroup.Starting_Handle = 0;
         ServiceHandleGroup.Ending_Handle   = 0;

         /* Register the custom service with GATT.                      */
         Result = qapi_BLE_GATT_Register_Service(BLE_Demo_Context.BluetoothStackID, QAPI_BLE_GATT_SERVICE_FLAGS_LE_SERVICE, CUSTOM_SERVICE_ATTRIBUTE_COUNT, (qapi_BLE_GATT_Service_Attribute_Entry_t *)Custom_Service_Table, &ServiceHandleGroup, Custom_GATTServerEventCallback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Register_Service", Result);

         if(Result > 0)
         {
            /* Save the service ID, which will be required to           */
            /* un-register the custom service with GATT.                */
            BLE_Demo_Context.CustomServiceID = Result;

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }

      /* Intialization is done and info user the result of initialization. */
      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Bluetooth stack has been initialized successfully.\r\n");
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Bluetooth stack ID: %d.\r\n", BLE_Demo_Context.BluetoothStackID);
      }
      else
      {
         /* Failed to initialize the Bluetooth stack, process to the clean up
            work. */
         if(BLE_Demo_Context.GAPInstanceID)
         {
            /* Clean up GAPS.*/
            qapi_BLE_GAPS_Cleanup_Service(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID);
            BLE_Demo_Context.GAPInstanceID = 0;
         }

         /* Cleanup GATT Module. */
         if(GATTInitialized)
         {
            qapi_BLE_GATT_Cleanup(BLE_Demo_Context.BluetoothStackID);
         }

         /* Shut down BSC layer. */
         if(BLE_Demo_Context.BluetoothStackID)
         {
            qapi_BLE_BSC_Shutdown(BLE_Demo_Context.BluetoothStackID);
            BLE_Demo_Context.BluetoothStackID = 0;
         }

         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to initialize Bluetooth stack.\r\n");
      }
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BLE stack had already been initialized.\r\n");

      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return (Ret_Val);
}

/**
   @brief Executes the "Shutdown" command to shut down the BT stack.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BLE_Shutdown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;

   /* Verify the BLE stack had already been initialized. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      ShutDownBLEDemo();

      Ret_Val = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "GetLocalAddress" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_GetLocalAddress(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   qapi_BLE_BD_ADDR_t    BD_ADDR;
   BoardStr_t            BoardStr;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Attempt to submit the command. */
      Result = qapi_BLE_GAP_Query_Local_BD_ADDR(BLE_Demo_Context.BluetoothStackID, &BD_ADDR);

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_Query_Local_BD_ADDR", Result);

      /* Check the return value of the submitted command for success. */
      if(Result == QAPI_OK)
      {
         BD_ADDRToStr(BD_ADDR, BoardStr);

         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR of Local Device is: %s.\r\n", BoardStr);

         Ret_Val = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetPairabilityMode" command.

   Parameter_List[0] (0-2) is a flag indicates the pair ability mode to be
                     set.
                     0 = Non Pairable
                     1 = Pairable
                     2 = Pairable (Secure Simple Pairing)

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetPairabilityMode(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   char                  *Mode;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Make sure that all of the parameters required for this function
         appear to be at least semi-valid. */
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_LPM_NON_PAIRABLEMODE_E, QAPI_BLE_LPM_PAIRABLE_MODE_ENABLE_EXTENDED_EVENTS_E)))
      {
         /* Parameters appear to be valid, map the specified parameters into
            the API specific parameters. */
         if(Parameter_List[0].Integer_Value == 0)
         {
            Mode = "NonPairableMode";
         }
         else if(Parameter_List[0].Integer_Value == 1)
         {
            Mode = "PairableMode";
         }
         else
         {
            Mode = "Pairable (Secure Simple Pairing)";
         }

         /* Parameters mapped, now set the Pairability Mode. */
         Result = qapi_BLE_GAP_LE_Set_Pairability_Mode(BLE_Demo_Context.BluetoothStackID, (qapi_BLE_GAP_LE_Pairability_Mode_t)(Parameter_List[0].Integer_Value));

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Pairability_Mode", Result);

         /* Check the return value to see if the command was issued
            successfully. */
         if(Result >= 0)
         {
            /* The Mode was changed successfully. */
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pairability mode changed to %s.\r\n", Mode);

            /* Flag success to the caller. */
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            /* Flag that an error occurred while submitting the command. */
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "GetLEParameters" command.

   Parameter_List[0] (0-5) is a flag indicates which LE parameters to get.
                  0 = Discover.
                  1 = Connectability.
                  2 = Advertise.
                  3 = Scan.
                  4 = Connection.
                  5 = Pair.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_GetLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 5)))
      {
         Ret_Val = QCLI_STATUS_SUCCESS_E;

         switch(Parameter_List[0].Integer_Value)
         {
            case 0:
               GetDiscoverabilityMode();
               break;

            case 1:
               GetAdvertiseConnectabilityParameters();
               break;

            case 2:
               GetAdvertiseLEParameters();
               break;

            case 3:
               GetScanParameters();
               break;

            case 4:
               GetConnectionParameters();
               break;

            case 5:
               GetPairParameters();
               break;

            default:
               break;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetLEParameters" command.

   Parameter_List[0] (0-5) is a flag indicates which LE parameters to set.
                  0 = Discover.
                  1 = Connectability.
                  2 = Advertise.
                  3 = Scan.
                  4 = Connection.
                  5 = Pair.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qbool_t                Result;
   uint32_t               UpdatedParameterCount;
   QCLI_Parameter_t      *UpdatedParameterList;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 5)))
      {
         UpdatedParameterCount = Parameter_Count - 1;

         UpdatedParameterList  = &(Parameter_List[1]);

         Result = true;

         switch(Parameter_List[0].Integer_Value)
         {
            case 0:
               Result = SetDiscoverabilityMode(UpdatedParameterCount, UpdatedParameterList);
               break;

            case 1:
               Result = SetAdvertiseConnectabilityParameters(UpdatedParameterCount, UpdatedParameterList);
               break;

            case 2:
               Result = SetAdvertiseLEParameters(UpdatedParameterCount, UpdatedParameterList);
               break;

            case 3:
               Result = SetScanParameters(UpdatedParameterCount, UpdatedParameterList);
               break;

            case 4:
               Result = SetConnectionParameters(UpdatedParameterCount, UpdatedParameterList);
               break;

            case 5:
               Result = SetPairParameters(UpdatedParameterCount, UpdatedParameterList);
               break;

            default:
               break;
         }

         if(Result)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "AdvertiseLE" command.

   Parameter_List[0] (0-1) is the flag indicates if the advertise should be
                     enabled.
                     0 = Disable
                     1 = Enable

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_AdvertiseLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                             Ret_Val = QCLI_STATUS_SUCCESS_E;
   qapi_Status_t                                     Result;
   uint8_t                                           Length;
   qbool_t                                           EnableAdvertiseLE;
   uint8_t                                           AdvertisingHandle = 1;
   uint32_t                                          Duration = 0;
   uint8_t                                           MaxAdvertisingEvents = 0;
   qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t ExtendedAdvertisingParameters;
   int8_t                                            TxPower;

   union
   {
      qapi_BLE_Advertising_Data_t   AdvertiseReportData;
      qapi_BLE_Scan_Response_Data_t ScanResponseData;
   } AdvertisementDataBuffer;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Make sure that Connectability_Mode and Own_Address_Type are provided
         at least and thery are in proper range. */
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 1)))
      {
         EnableAdvertiseLE  = (qbool_t)(Parameter_List[0].Integer_Value);

         if(!EnableAdvertiseLE)
         {
            /* Disable LE advertising. */
            Result = qapi_BLE_GAP_LE_Enable_Extended_Advertising(BLE_Demo_Context.BluetoothStackID, false, 1, &AdvertisingHandle, &Duration, &MaxAdvertisingEvents, BLE_GAP_LE_Event_Callback, 0);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Enable_Extended_Advertising", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "LE advertising had been disabled.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to disable LE advertising.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            /* Format extended advertising parameters. */
            memset(&ExtendedAdvertisingParameters, 0, sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t));

            ExtendedAdvertisingParameters.Advertising_Event_Properties     = QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_USE_LEGACY_PDUS;

            ExtendedAdvertisingParameters.Primary_Advertising_Interval_Min = BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Min;
            ExtendedAdvertisingParameters.Primary_Advertising_Interval_Max = BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Max;
            ExtendedAdvertisingParameters.Primary_Advertising_Channel_Map  = BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Channel_Map;
            ExtendedAdvertisingParameters.Connect_Request_Filter           = BLE_Demo_Context.AdvertisingParameters.Parameters.Connect_Request_Filter;
            ExtendedAdvertisingParameters.Scan_Request_Filter              = BLE_Demo_Context.AdvertisingParameters.Parameters.Scan_Request_Filter;
            ExtendedAdvertisingParameters.Advertising_Tx_Power             = QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_ADVERTISING_TX_POWER_NO_PREFERENCE;

            if(BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode > QAPI_BLE_LCM_NON_CONNECTABLE_E)
            {
               ExtendedAdvertisingParameters.Advertising_Event_Properties |= QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_CONNECTABLE | QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_SCANNABLE;

               if(BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode > QAPI_BLE_LCM_CONNECTABLE_E)
               {
                  ExtendedAdvertisingParameters.Advertising_Event_Properties |= QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_DIRECTED;
               }

               if(BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode > QAPI_BLE_LCM_DIRECT_CONNECTABLE_E)
               {
                  ExtendedAdvertisingParameters.Advertising_Event_Properties |= QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_HIGH_DUTY_CYCLE_DIRECTED;
               }
            }

            if(ExtendedAdvertisingParameters.Advertising_Event_Properties & QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_DIRECTED)
            {
               ExtendedAdvertisingParameters.Peer_Address      = BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address;
               ExtendedAdvertisingParameters.Peer_Address_Type = BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address_Type;
            }

            /* Set the advertising data.*/
            Result = qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(BLE_Demo_Context.BluetoothStackID, AdvertisingHandle, &ExtendedAdvertisingParameters, &TxPower);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters", Result);

            if(!Result)
            {
               /* Set up LE advertising data. */
               memset(&(AdvertisementDataBuffer.AdvertiseReportData), 0, sizeof(qapi_BLE_Advertising_Data_t));

               /* Set the Flags A/D Field (1 byte type and 1 byte Flags). */
               AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0] = 2;
               AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[1] = QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_FLAGS;
               AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[2] = 0;

               /* Configure the flags field based on the Discoverability mode. */
               if(BLE_Demo_Context.DiscoverabilityMode == QAPI_BLE_DM_LIMITED_DISCOVERABLE_MODE_E)
               {
                  AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[2] = QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_LIMITED_DISCOVERABLE_MODE_FLAGS_BIT_MASK;
               }

               if(BLE_Demo_Context.DiscoverabilityMode == QAPI_BLE_DM_GENERAL_DISCOVERABLE_MODE_E)
               {
                  AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[2] = QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_GENERAL_DISCOVERABLE_MODE_FLAGS_BIT_MASK;
               }

               /* Configure the flags field based on BREDR support flag. */
               if(!(BLE_Demo_Context.AdvertisingParameters.BREDRSupport))
               {
                  AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[2] = QAPI_BLE_HCI_LE_ADVERTISING_FLAGS_BR_EDR_NOT_SUPPORTED_FLAGS_BIT_MASK;
               }

               Length = (uint8_t)strlen(QCLI_BLE_DEMO_DEVICE_NAME);
               if(Length < (QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE - (AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0] + 1) - 2))
               {
                  AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[4] = QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LOCAL_NAME_COMPLETE;
               }
               else
               {
                  AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[4] = QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_TYPE_LOCAL_NAME_SHORTENED;
                  Length = (QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE - (AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0] + 1) - 2);
               }

               AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[3] = (uint8_t)(1 + Length);
               memscpy(&(AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[5]), ((QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE - (AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0] + 1) - 2)), QCLI_BLE_DEMO_DEVICE_NAME, Length);

               /* Set the advertising data.*/
               Result = qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(BLE_Demo_Context.BluetoothStackID, AdvertisingHandle, QAPI_BLE_AOT_SET_DATA_E, QAPI_BLE_PT_FRAGMENTATION_ALLOWED_E, (uint32_t)(AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0] + AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[3] + 2), (uint8_t *)&(AdvertisementDataBuffer.AdvertiseReportData.Advertising_Data[0]));

               /* Inform the user the result of BLE operation. */
               QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Extended_Advertising_Data", Result);

               if(Result == QAPI_OK)
               {
                  /* Finally, enable LE advertising. */
                  Result = qapi_BLE_GAP_LE_Enable_Extended_Advertising(BLE_Demo_Context.BluetoothStackID, true, 1, &AdvertisingHandle, &Duration, &MaxAdvertisingEvents, BLE_GAP_LE_Event_Callback, 0);

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Enable_Extended_Advertising", Result);

                  if(Result == QAPI_OK)
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "LE advertising is enabled.\r\n");
                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to enable LE advertising.\r\n");

                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  /* Failed to set advertising data. */
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to set advertising data.\r\n");
                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "StartScanning" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_StartScanning(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                              Ret_Val;
   qapi_Status_t                                      Result;
   qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t ExtendedScanningParameters;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a scan process has already been in process. */
      if(!BLE_Demo_Context.ScanInProgress)
      {
         ExtendedScanningParameters.Scan_PHY      = QAPI_BLE_LPT_PHY_LE_1M_E;
         ExtendedScanningParameters.Scan_Type     = BLE_Demo_Context.ScanParameters.ScanType;
         ExtendedScanningParameters.Scan_Interval = BLE_Demo_Context.ScanParameters.ScanInterval;
         ExtendedScanningParameters.Scan_Window   = BLE_Demo_Context.ScanParameters.ScanWindow;

         /* Set scanning parameters. */
         Result = qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ScanParameters.LocalAddressType, BLE_Demo_Context.ScanParameters.FilterPolicy, 1, &ExtendedScanningParameters);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters", Result);

         if(Result == QAPI_OK)
         {
            /* Try to start scan procedure. */
            Result = qapi_BLE_GAP_LE_Enable_Extended_Scan(BLE_Demo_Context.BluetoothStackID, true, (BLE_Demo_Context.ScanParameters.FilterDuplicates ? QAPI_BLE_FD_ENABLED_E : QAPI_BLE_FD_DISABLED_E), 0, 0, BLE_GAP_LE_Event_Callback, 0);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Enable_Extended_Scan", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan operation has been started successfully.\r\n");

               /* Mark the scan is in progress now. */
               BLE_Demo_Context.ScanInProgress = true;

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to start scan procedure.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan procedure has already started.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "StopScanning" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_StopScanning(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a scan process has already been in process. */
      if(BLE_Demo_Context.ScanInProgress)
      {
         /* Try to stop the scan procedure. */
         Result = qapi_BLE_GAP_LE_Enable_Extended_Scan(BLE_Demo_Context.BluetoothStackID, false, QAPI_BLE_FD_DISABLED_E, 0, 0, BLE_GAP_LE_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Enable_Extended_Scan", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan operation has been stopped successfully.\r\n");

            /* Mark the scan operation is stopped now. */
            BLE_Demo_Context.ScanInProgress = false;

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to stop scan procedure.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan procedure has not started.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ConnectLE" command.

   Parameter_List[0] is the BD address of the remote device.
   Parameter_List[1] is BD address type of the remote device.
   Parameter_List[2] is the flag indicates if the white list should be used.
                     0=Not use.
                     1=Use.
   Parameter_List[3] is the local BD_ADDR Type.
                     0=Public.
                     1=Random.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ConnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                            Ret_Val;
   qapi_Status_t                                    Result;
   qbool_t                                          UseWhiteList;
   qapi_BLE_BD_ADDR_t                               RemoteBDADDR;
   qapi_BLE_GAP_LE_Address_Type_t                   RemoteBDADDRType;
   qapi_BLE_GAP_LE_Address_Type_t                   LocalBDADDRType;
   qapi_BLE_GAP_LE_White_List_Entry_t               WhiteList;
   uint32_t                                         Count;
   qapi_BLE_GAP_LE_Filter_Policy_t                  FilterPolicy;
   qapi_BLE_GAP_LE_Extended_Connection_Parameters_t ExtendedConnectionParameters;

   /* First, check that valid Bluetooth Stack ID exists. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Make sure that Connectability_Mode and Own_Address_Type are provided
         at least and thery are in proper range. */
      if((Parameter_Count >= 4) && (Parameter_List[0].String_Value != NULL) && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_LAT_PUBLIC_E, QAPI_BLE_LAT_RANDOM_E))
         && (QCLI_Verify_Integer_Parameter(&Parameter_List[2], 0, 1)) && (QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_LAT_PUBLIC_E, QAPI_BLE_LAT_RANDOM_E)))
      {
         StrToBD_ADDR(Parameter_List[0].String_Value, &RemoteBDADDR);

         /* Make sure the remote BD ADDR is not NULL. */
         if(!(QAPI_BLE_COMPARE_NULL_BD_ADDR(RemoteBDADDR)))
         {
            if(!(QAPI_BLE_COMPARE_BD_ADDR(RemoteBDADDR, BLE_Demo_Context.ActiveConnectionBD_ADDR)))
            {
               RemoteBDADDRType = (qapi_BLE_GAP_LE_Address_Type_t)(Parameter_List[1].Integer_Value);
               UseWhiteList     = (qbool_t)(Parameter_List[2].Integer_Value);

               /* Remove any previous entries for this device from the white list. */
               Count = 0;
               memset(&WhiteList, 0, QAPI_BLE_GAP_LE_WHITE_LIST_ENTRY_SIZE);
               WhiteList.Address      = RemoteBDADDR;
               WhiteList.Address_Type = RemoteBDADDRType;
               qapi_BLE_GAP_LE_Remove_Device_From_White_List(BLE_Demo_Context.BluetoothStackID, 1, &WhiteList, &Count);

               if(UseWhiteList)
               {
                  /* Add the device to the white list. */
                  Count = 0;
                  Result = qapi_BLE_GAP_LE_Add_Device_To_White_List(BLE_Demo_Context.BluetoothStackID, 1, &WhiteList, &Count);

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Add_Device_To_White_List", Result);

                  if((Result == 0) && (Count == 1))
                  {
                     FilterPolicy = QAPI_BLE_FP_WHITE_LIST_E;
                     Ret_Val      = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to add remote device to white list.\r\n");
                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  FilterPolicy = QAPI_BLE_FP_NO_FILTER_E;
                  Ret_Val      = QCLI_STATUS_SUCCESS_E;
               }

               /* Now try to make the LE connection.*/
               if(Ret_Val == QCLI_STATUS_SUCCESS_E)
               {
                  LocalBDADDRType = (qapi_BLE_GAP_LE_Address_Type_t)(Parameter_List[3].Integer_Value);

                  /* Format the connection parameters for each PHY. */
                  ExtendedConnectionParameters.Initiating_PHY            = QAPI_BLE_LPT_PHY_LE_1M_E;
                  ExtendedConnectionParameters.Scan_Interval             = BLE_Demo_Context.ScanParameters.ScanInterval;
                  ExtendedConnectionParameters.Scan_Window               = BLE_Demo_Context.ScanParameters.ScanWindow;
                  ExtendedConnectionParameters.Connection_Interval_Min   = BLE_Demo_Context.ConnectionParamters.Connection_Interval_Min;
                  ExtendedConnectionParameters.Connection_Interval_Max   = BLE_Demo_Context.ConnectionParamters.Connection_Interval_Max;
                  ExtendedConnectionParameters.Slave_Latency             = BLE_Demo_Context.ConnectionParamters.Slave_Latency;
                  ExtendedConnectionParameters.Supervision_Timeout       = BLE_Demo_Context.ConnectionParamters.Supervision_Timeout;
                  ExtendedConnectionParameters.Minimum_Connection_Length = BLE_Demo_Context.ConnectionParamters.Minimum_Connection_Length;
                  ExtendedConnectionParameters.Maximum_Connection_Length = BLE_Demo_Context.ConnectionParamters.Maximum_Connection_Length;

                  Result = qapi_BLE_GAP_LE_Extended_Create_Connection(BLE_Demo_Context.BluetoothStackID, FilterPolicy, RemoteBDADDRType, &RemoteBDADDR, LocalBDADDRType, 1, &ExtendedConnectionParameters, BLE_GAP_LE_Event_Callback, 0);

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Extended_Create_Connection", Result);

                  if(Result == QAPI_OK)
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection requrest is issued successfully.\r\n");
                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to issue connection requrest.\r\n");

                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote device has already been connected.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid Remote BD ADDR.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "CancelConnectLE" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_CancelConnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Make sure there is connection exists. */
      if(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR))
      {
         /* Try to start disconnect procedure. */
         Result = qapi_BLE_GAP_LE_Cancel_Create_Connection(BLE_Demo_Context.BluetoothStackID);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Cancel_Create_Connection", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Successfully canceled LE connecting operaion.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to cancel connect request.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The device has been connected.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "DisconnectLE" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_DisconnectLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a connection exists. */
      if(!(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR)))
      {
         /* Try to start disconnect procedure. */
         Result = qapi_BLE_GAP_LE_Disconnect(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionBD_ADDR);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Disconnect", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Disconnect request is isssue successfully.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to issue disconnect request.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The device is not connected.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "PairLE" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_PairLE(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a connection exists. */
      if(!(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR)))
      {
         if(BLE_Demo_Context.LocalDeviceIsMaster)
         {
            /* Try to pair with the remote device. */
            Result = SendPairingRequest(BLE_Demo_Context.ActiveConnectionBD_ADDR, true);
         }
         else
         {
            /* Device is slave and it should request the master to start
               pairring procedure. */
            Result = SendPairingRequest(BLE_Demo_Context.ActiveConnectionBD_ADDR, false);
         }

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pair request is issued successfully.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to issue pair request.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The device is not connected.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "LEPassKeyResponse" command.

   Parameter_List[0] is the pass key.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_LEPassKeyResponse(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                                 Ret_Val;
   qapi_Status_t                                         Result;
   qapi_BLE_GAP_LE_Authentication_Response_Information_t ResponseInfo;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a connection exists. */
      if(!(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR)))
      {
         if((Parameter_Count >= 1) && (Parameter_List[0].String_Value != NULL))
         {
            if(strlen(Parameter_List[0].String_Value) <= QAPI_BLE_GAP_LE_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS)
            {
               /* Set up ResponseInfo. */
               memset(&ResponseInfo, 0, QAPI_BLE_GAP_LE_AUTHENTICATION_RESPONSE_INFORMATION_SIZE);

               ResponseInfo.GAP_LE_Authentication_Type  = QAPI_BLE_LAR_PASSKEY_E;
               ResponseInfo.Authentication_Data_Length  = sizeof(uint32_t);
               ResponseInfo.Authentication_Data.Passkey = (uint32_t)(Parameter_List[0].Integer_Value);

               /* Try to send pass key response. */
               Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionBD_ADDR, &ResponseInfo);

               /* Inform the user the result of BLE operation. */
               QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

               if(Result == QAPI_OK)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pass key response has been sent successfully.\r\n");

                  Ret_Val = QCLI_STATUS_SUCCESS_E;
               }
               else
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send pass key response.\r\n");

                  Ret_Val = QCLI_STATUS_SUCCESS_E;
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The maximum number of digits for pass key is %d.\r\n", QAPI_BLE_GAP_LE_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS);

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            Ret_Val = QCLI_STATUS_USAGE_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The device is not connected.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "LEQueryEncryption" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_LEQueryEncryption(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t          Ret_Val;
   qapi_Status_t                  Result;
   qapi_BLE_GAP_Encryption_Mode_t EncryptionMode;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Check if a connection exists. */
      if(!(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR)))
      {
         Result = qapi_BLE_GAP_LE_Query_Encryption_Mode(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionBD_ADDR, &EncryptionMode);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Query_Encryption_Mode", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Current Encryption Mode: %s.\r\n", (EncryptionMode == QAPI_BLE_EM_ENABLED_E) ? "Enabled" : "Disabled");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to get encryption mode.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The device is not connected.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "LESetPasskey" command.

   Parameter_List[0] is the flag indicates if the pass key should be set or
                     erased.
                     0=Set
                     1=Erase

   Parameter_List[1] is the pass key to be set. (Used when pass key is going
                     to be set.)

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_LESetPasskey(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0 , 1)))
      {
         if(Parameter_List[0].Integer_Value == 1)
         {
            /* Try to set the pass key. */
            if(Parameter_Count >= 2)
            {
               if(strlen(Parameter_List[1].String_Value) <= QAPI_BLE_GAP_LE_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS)
               {
                  Result = qapi_BLE_GAP_LE_Set_Fixed_Passkey(BLE_Demo_Context.BluetoothStackID, (uint32_t *)&(Parameter_List[1].Integer_Value));

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Fixed_Passkey", Result);

                  if(Result == QAPI_OK)
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pass key has been set successfully.\r\n");
                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to set pass key.\r\n");
                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The maximum number of digits for pass key is %d.\r\n", QAPI_BLE_GAP_LE_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS);

                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Missing pass key.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            /* Try to erase the pass key. */
            Result = qapi_BLE_GAP_LE_Set_Fixed_Passkey(BLE_Demo_Context.BluetoothStackID, NULL);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Set_Fixed_Passkey", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pass key has been erased successfully.\r\n");
               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to erase pass key.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "DiscoverGAPS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_DiscoverGAPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   qapi_BLE_GATT_UUID_t  GATTUUID;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.ActiveConnectionID)
      {
         GATTUUID.UUID_Type = QAPI_BLE_GU_UUID_16_E;
         QAPI_BLE_GAP_ASSIGN_GAP_SERVICE_UUID_16(GATTUUID.UUID.UUID_16);

         Result = qapi_BLE_GATT_Start_Service_Discovery(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionID, 1, &GATTUUID, BLE_GATT_Service_Discovery_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Start_Service_Discovery", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP service discovery request is sent successfully.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP service discovery request.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* There is no connected remote device. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ReadLocalName" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ReadLocalName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   char                  LocalDeviceName[QCLI_BLE_DEMO_STRING_LEN];

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.GAPInstanceID)
      {
         /* Get the local name. */
         Result = qapi_BLE_GAPS_Query_Device_Name(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, LocalDeviceName);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Start_Service_Discovery", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Local device name: %s\r\n", LocalDeviceName);

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to read local device name.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* GAP service is not instanced. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no instanced GAP service.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetLocalName" command.

   Parameter_List[0] is the name to be set on local device.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetLocalName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.GAPInstanceID)
      {
         if(Parameter_Count >= 1)
         {
            /* Set the local name. */
            Result = qapi_BLE_GAPS_Set_Device_Name(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, Parameter_List[0].String_Value);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Set_Device_Name", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Local device name is set to: %s\r\n", Parameter_List[0].String_Value);

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to set local device name.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            Ret_Val = QCLI_STATUS_USAGE_E;
         }
      }
      else
      {
         /* GAP service is not instanced. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no instanced GAP service.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ReadRemoteName" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ReadRemoteName(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   Generic_Device_Info_t *DeviceInfo;

   /* Check if the Bluetooth stack has been initialized. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Find the device info of the device with active connection. */
      DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);
      if(DeviceInfo != NULL)
      {
         if(DeviceInfo->GAPSClientInfo.DeviceNameHandle)
         {
            Result = qapi_BLE_GATT_Read_Value_Request(BLE_Demo_Context.BluetoothStackID, DeviceInfo->ConnectionID, DeviceInfo->GAPSClientInfo.DeviceNameHandle, BLE_GATT_Client_Event_Callback, DeviceInfo->GAPSClientInfo.DeviceNameHandle);

            if(Result)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Read remote name request is sent successfully.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send read remote name request.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAPS has not discovered.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ReadLocalAppearance" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ReadLocalAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   uint16_t               Appearance;
   char                  *AppearanceString;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.GAPInstanceID)
      {
         /* Get the local name. */
         Result = qapi_BLE_GAPS_Query_Device_Appearance(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, &Appearance);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Query_Device_Appearance", Result);

         if(Result == QAPI_OK)
         {
            if(AppearanceToString(Appearance, &AppearanceString))
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Local appearance is: %s\r\n", AppearanceString);
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Unknown appearance value: %d\r\n", Appearance);
            }

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to read local device name.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* GAP service is not instanced. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no instanced GAP service.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetLocalAppearance" command.

   Parameter_List[0] is the local apperance to be set on local device.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetLocalAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.GAPInstanceID)
      {
         if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_UNKNOWN , QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_OUTDOOR_SPORTS_ACTIVITY_LOCATION_AND_NAVIGATION_POD)))
         {
            /* Set the local name. */
            Result = qapi_BLE_GAPS_Set_Device_Appearance(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID, (uint16_t)(Parameter_List[0].Integer_Value));

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAPS_Set_Device_Appearance", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Local device apperance is set successfully.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to set local device apperance.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            Ret_Val = QCLI_STATUS_USAGE_E;
         }
      }
      else
      {
         /* GAP service is not instanced. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no instanced GAP service.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ReadRemoteAppearance" command.

   Parameter_List[0] is the local apperance to be set on local device.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ReadRemoteAppearance(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   Generic_Device_Info_t *DeviceInfo;

   /* Check if the Bluetooth stack has been initialized. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Find the device info of the device with active connection. */
      DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);
      if(DeviceInfo)
      {
         if(DeviceInfo->GAPSClientInfo.DeviceAppearanceHandle)
         {
            Result = qapi_BLE_GATT_Read_Value_Request(BLE_Demo_Context.BluetoothStackID, DeviceInfo->ConnectionID, DeviceInfo->GAPSClientInfo.DeviceAppearanceHandle, BLE_GATT_Client_Event_Callback, DeviceInfo->GAPSClientInfo.DeviceAppearanceHandle);
            if(Result)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Read remote appearance request is sent successfully.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send read remote appearance request.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAPS has not discovered.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "GetGATTMTU" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_GetGATTMTU(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   uint16_t              MTU;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Get the GATT MTU. */
      Result = qapi_BLE_GATT_Query_Maximum_Supported_MTU(BLE_Demo_Context.BluetoothStackID, &MTU);

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Query_Maximum_Supported_MTU", Result);

      if(Result == QAPI_OK)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT MTU: %d\r\n", MTU);

         Ret_Val = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to get local GATT MTU.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetGATTMTU" command.

   Parameter_List[0] is the GATT MTU to be set on local device.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetGATTMTU(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_ATT_PROTOCOL_MTU_MINIMUM_LE , QAPI_BLE_ATT_PROTOCOL_MTU_MAXIMUM)))
      {
         /* Set the GATT MTU. */
         Result = qapi_BLE_GATT_Change_Maximum_Supported_MTU(BLE_Demo_Context.BluetoothStackID, (uint16_t)(Parameter_List[0].Integer_Value));

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Change_Maximum_Supported_MTU", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT MTU is set successfully.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to set GATT MTU.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "RegisterRemoteAuthentication" command.

   Parameter_List[0] is the GATT MTU to be set on local device.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_RegisterRemoteAuth(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 1)))
      {
         /* Check to see if we are registering or un-registering the    */
         /* remote authentication callback.                             */
         if(Parameter_List[0].Integer_Value == 1)
         {
            /* Register remote-authentication.                          */
            Result = qapi_BLE_GAP_LE_Register_Remote_Authentication(BLE_Demo_Context.BluetoothStackID, BLE_GAP_LE_Event_Callback, 0);

            /* Inform the user the result of BLE operation.             */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Register_Remote_Authentication", Result);
         }
         else
         {
            /* UN-Register remote-authentication.                       */
            Result = qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(BLE_Demo_Context.BluetoothStackID);

            /* Inform the user the result of BLE operation.             */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Un_Register_Remote_Authentication", Result);
         }

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetMaxTxPower" command.

   Parameter_List[0] is the maximum TX power that will be set for the
                     radio.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_SetMaxTxPower(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   int8_t                MaxTxPower;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (Parameter_List[0].Integer_Is_Valid) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], -31, 7)))
      {
         MaxTxPower = (int8_t)Parameter_List[0].Integer_Value;

         /* Set the max tx power for the radio.                         */
         Result = qapi_Radio_Set_Max_Tx_Power(BLE_Demo_Context.BluetoothStackID, MaxTxPower);

         /* Inform the user the result of BLE operation.                */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_Radio_Set_Max_Tx_Power", Result);

         if(Result == QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "DiscoverCustom" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_DiscoverCustom(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   qapi_Status_t         Result;
   qapi_BLE_GATT_UUID_t  GATTUUID;

   if(BLE_Demo_Context.BluetoothStackID)
   {
      if(BLE_Demo_Context.ActiveConnectionID)
      {
         GATTUUID.UUID_Type = QAPI_BLE_GU_UUID_128_E;
         CUSTOM_ASSIGN_SERVICE_UUID_128(GATTUUID.UUID.UUID_128);

         Result = qapi_BLE_GATT_Start_Service_Discovery(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionID, 1, &GATTUUID, BLE_GATT_Service_Discovery_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Start_Service_Discovery", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP service discovery request is sent successfully.\r\n");

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP service discovery request.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* There is no connected remote device. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "CustomRead" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_CustomRead(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   Generic_Device_Info_t *DeviceInfo;

   /* Check if the Bluetooth stack has been initialized. */
   if(BLE_Demo_Context.BluetoothStackID)
   {
      /* Find the device info of the device with active connection. */
      DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);
      if(DeviceInfo != NULL)
      {
         if(DeviceInfo->CustomClientInfo.ReadHandle)
         {
            Result = qapi_BLE_GATT_Read_Value_Request(BLE_Demo_Context.BluetoothStackID, DeviceInfo->ConnectionID, DeviceInfo->CustomClientInfo.ReadHandle, BLE_GATT_Client_Event_Callback, DeviceInfo->CustomClientInfo.ReadHandle);

            if(Result)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Custom read request is sent successfully.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send read request.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Custom service has not discovered.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "QueryStatistics" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_QueryStatistics(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   int                       Result;
   QCLI_Command_Status_t     Ret_Val = QCLI_STATUS_SUCCESS_E;
   qapi_BLE_BSC_Statistics_t BTSS_Statistics;

   if(BLE_Demo_Context.BluetoothStackID != 0)
   {
      /* Query the BTSS Statistics.                                     */
      Result = qapi_BLE_BSC_QueryStatistics(BLE_Demo_Context.BluetoothStackID, &BTSS_Statistics);
      if(Result == 0)
      {
         /* Print the BTSS Statistics.                                  */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "ACL Bytes Transmitted : %u.\r\n", BTSS_Statistics.TxAclBytes);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "ACL Bytes Received    : %u.\r\n", BTSS_Statistics.RxAclBytes);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Tx Packets            : %u.\r\n", BTSS_Statistics.TxPackets);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Rx Packets No Errors  : %u.\r\n", BTSS_Statistics.RxPackets_NoError);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Rx Packets CRC Errors : %u.\r\n", BTSS_Statistics.RxPackets_CRCError);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Rx Packets MIC Errors : %u.\r\n", BTSS_Statistics.RxPackets_MICError);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Rx Timeouts           : %u.\r\n", BTSS_Statistics.RxTimeouts);
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Active Time (ms)      : %llu.\r\n\r\n", BTSS_Statistics.ActiveTimeMs);
      }
      else
      {
         /* Inform the user the result of BLE operation.                */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_BSC_QueryStatistics", Result);

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Bluetooth interface not initialized.\r\n");

      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ClearStatistics" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_BLE_ClearStatistics(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   int                   Result;
   uint32_t              BSC_ClearFlags;
   QCLI_Command_Status_t Ret_Val = QCLI_STATUS_SUCCESS_E;

   if(BLE_Demo_Context.BluetoothStackID != 0)
   {
      if((Parameter_Count >= 1) && (Parameter_List[0].Integer_Is_Valid))
         BSC_ClearFlags = Parameter_List[0].Integer_Value;
      else
         BSC_ClearFlags = QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_ALL;

      /* Clear the BTSS Statistics.                                     */
      Result = qapi_BLE_BSC_ClearStatistics(BLE_Demo_Context.BluetoothStackID, BSC_ClearFlags);
      if(Result != 0)
      {
         /* Inform the user the result of BLE operation.                */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_BSC_ClearStatistics", Result);

         Ret_Val = QCLI_STATUS_ERROR_E;
      }

      if(Ret_Val == QCLI_STATUS_SUCCESS_E)
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status Cleared.\r\n");
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Bluetooth interface not initialized.\r\n");

      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Callback function to handle GAP LE event.

   Parameter_List[0] is the Bluetooth stack ID.
   Parameter_List[1] is the GAP LE event.
   Parameter_List[2] is the callback parameter.
*/
static void BLE_GAP_LE_Event_Callback(uint32_t BluetoothStackID , qapi_BLE_GAP_LE_Event_Data_t *GAP_LE_Event_Data, unsigned long CallbackParameter)
{
   BoardStr_t                                             BoardStr;
   Generic_Device_Info_t                                 *DeviceInfo;
   uint32_t                                               Index;
   uint32_t                                               DataLength;
   uint16_t                                               EDIV;
   qapi_BLE_Long_Term_Key_t                               GeneratedLTK;
   qapi_BLE_Random_Number_t                               RandomNumber;
   qapi_BLE_GAP_LE_Security_Information_t                 GAP_LE_Security_Information;
   qapi_BLE_GAP_LE_Authentication_Response_Information_t  GAP_LE_Authentication_Response_Information;
   qapi_BLE_GAP_LE_Address_Type_t                         AddressType;
   qapi_Status_t                                          Result;

   union
   {
      qapi_BLE_GAP_LE_Extended_Advertising_Report_Event_Data_t           *AdvertisingReportEvent;
      qapi_BLE_GAP_LE_Connection_Complete_Event_Data_t                   *ConnectionCompleteEvent;
      qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_t                *DisconnectionCompleteEvent;
      qapi_BLE_GAP_LE_Encryption_Change_Event_Data_t                     *EncryptionChangeEvent;
      qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_t           *EncryptionRefreshCompleteEvent;
      qapi_BLE_GAP_LE_Authentication_Event_Data_t                        *AuthenticationEvent;
      qapi_BLE_GAP_LE_Remote_Features_Event_Data_t                       *RemoteFeaturesEvent;
      qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_t *LocalP256PublicKeyUpdateCompleteEvent;
      qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_t    *ChannelSelectAlgorithmUpdateEvent;
      qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_t            *AdvertisingSetTermiantedEvent;
   } EventData;

   if((BLE_Demo_Context.BluetoothStackID == BluetoothStackID) && (GAP_LE_Event_Data))
   {
      DataLength = GAP_LE_Event_Data->Event_Data_Size;
      DeviceInfo = NULL;

      switch(GAP_LE_Event_Data->Event_Data_Type)
      {
         /* GAP connection complete event. */
         case QAPI_BLE_ET_LE_CONNECTION_COMPLETE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE connection complete event with length: %d.\r\n", DataLength);

            EventData.ConnectionCompleteEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Connection_Complete_Event_Data;
            if(EventData.ConnectionCompleteEvent)
            {
               /* Display the connection info. */
               BD_ADDRToStr(EventData.ConnectionCompleteEvent->Peer_Address, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status: 0x%02X.\r\n", EventData.ConnectionCompleteEvent->Status);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Master: %s.\r\n", ((EventData.ConnectionCompleteEvent->Master == true) ? "Yes" : "No"));

               AddressType = EventData.ConnectionCompleteEvent->Peer_Address_Type;
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote device address type: %s.\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote device address: %s.\r\n", BoardStr);

               if(EventData.ConnectionCompleteEvent->Status == 0)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Interval: %u.\n", (unsigned int)(EventData.ConnectionCompleteEvent->Current_Connection_Parameters.Connection_Interval));
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Slave Latency: %u.\n", (unsigned int)(EventData.ConnectionCompleteEvent->Current_Connection_Parameters.Slave_Latency));

                  /* Save the master state and remote address type info. They */
                  /* will be stored in the device info entry when handling */
                  /* GATT_CONNECTION_DEVICE_CONNECTIOn event*/
                  BLE_Demo_Context.LocalDeviceIsMaster         = GAP_LE_Event_Data->Event_Data.GAP_LE_Connection_Complete_Event_Data->Master;
                  BLE_Demo_Context.ConnectingDeviceAddressType = GAP_LE_Event_Data->Event_Data.GAP_LE_Connection_Complete_Event_Data->Peer_Address_Type;

                  /* Check to see if a new device entry should be allocated. */
                  DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.ConnectionCompleteEvent->Peer_Address);

                  /* Note: A new device entry will be allocated in */
                  /* GATT_CONNECTION_DEVICE_CONNECTION event which will */
                  /* follow the GAP LE connection complete event. */
                  if(DeviceInfo != NULL)
                  {
                     /* The device has already been conncted if the local */
                     /* device is a master, then try to reestablish the   */
                     /* security. */
                     if(DeviceInfo->LocalDeviceIsMaster)
                     {
                        if((DeviceInfo->Flags) & (DEVICE_INFO_FLAGS_LTK_VALID))
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Try to re-establish security.\r\n");
                           GAP_LE_Security_Information.Local_Device_Is_Master                                      = true;
                           GAP_LE_Security_Information.Security_Information.Master_Information.EDIV                = DeviceInfo->EDIV;
                           GAP_LE_Security_Information.Security_Information.Master_Information.Encryption_Key_Size = DeviceInfo->EncryptionKeySize;

                           memscpy(&(GAP_LE_Security_Information.Security_Information.Master_Information.LTK), sizeof(GAP_LE_Security_Information.Security_Information.Master_Information.LTK), &(DeviceInfo->LTK), sizeof(DeviceInfo->LTK));
                           memscpy(&(GAP_LE_Security_Information.Security_Information.Master_Information.Rand), sizeof(GAP_LE_Security_Information.Security_Information.Master_Information.Rand), &(DeviceInfo->Rand), sizeof(DeviceInfo->Rand));

                           Result = qapi_BLE_GAP_LE_Reestablish_Security(BluetoothStackID, EventData.ConnectionCompleteEvent->Peer_Address, &GAP_LE_Security_Information, BLE_GAP_LE_Event_Callback, 0);

                           /* Inform the user the result of BLE operation. */
                           QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Reestablish_Security", Result);

                           if(Result != QAPI_OK)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to issue reestablish security request.\r\n");
                           }
                        }
                        else
                        {
                           /* This shouldn't occur, but we will inform the */
                           /* user if it does. */
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Can't re-establish security: LTK is missing.\n");
                        }
                     }
                  }
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP connection complete event data.\r\n");
            }

            break;

         /* GAP LE disconnection complete event. */
         case QAPI_BLE_ET_LE_DISCONNECTION_COMPLETE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE disconnection complete event with length: %d.\r\n", DataLength);

            EventData.DisconnectionCompleteEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Disconnection_Complete_Event_Data;
            if(EventData.DisconnectionCompleteEvent)
            {
               /* Display disconncetion complete info. */
               BD_ADDRToStr(EventData.DisconnectionCompleteEvent->Peer_Address, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status: 0x%02X.\r\n", EventData.DisconnectionCompleteEvent->Status);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Reason: 0x%02X.\r\n", EventData.DisconnectionCompleteEvent->Reason);

               AddressType = EventData.DisconnectionCompleteEvent->Peer_Address_Type;
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote device address type: %s.\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));

               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote device address: %s.\r\n", BoardStr);

               /* Update device info entry associated with the peer address. */
               DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.DisconnectionCompleteEvent->Peer_Address);
               if(DeviceInfo)
               {
                  /* Clear the flag indicating the LTK is valid. */
                  DeviceInfo->Flags &= ~DEVICE_INFO_FLAGS_LTK_VALID;
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP disconnection complete event data.\r\n");
            }
            break;

         /* GAP LE encryption change event. */
         case QAPI_BLE_ET_LE_ENCRYPTION_CHANGE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE encryption change event with length: %d.\r\n", DataLength);
            break;

         /* GAP LE encryption refresh event. */
         case QAPI_BLE_ET_LE_ENCRYPTION_REFRESH_COMPLETE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE encryption refresh event with length: %d.\r\n", DataLength);
            break;

         /* GAP LE authentication event. */
         case QAPI_BLE_ET_LE_AUTHENTICATION_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication event with length: %d.\r\n", DataLength);

            EventData.AuthenticationEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Authentication_Event_Data;
            if(EventData.AuthenticationEvent)
            {
               BD_ADDRToStr(EventData.AuthenticationEvent->BD_ADDR, BoardStr);

               switch(EventData.AuthenticationEvent->GAP_LE_Authentication_Event_Type)
               {
                  /* Long term key request. */
                  case QAPI_BLE_LAT_LONG_TERM_KEY_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LAT long term key request: \n");
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR: %s.\n", BoardStr);

                     /* Prepare authenticatoin response data.  */
                     GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_LONG_TERM_KEY_E;
                     GAP_LE_Authentication_Response_Information.Authentication_Data_Length = 0;

                     memset(&RandomNumber, 0, sizeof(RandomNumber));
                     EDIV = 0;

                     /* Check to see if this is a request for a SC      */
                     /* generated Long Term Key.                        */
                     if((EventData.AuthenticationEvent->Authentication_Event_Data.Long_Term_Key_Request.EDIV == EDIV) && (QAPI_BLE_COMPARE_RANDOM_NUMBER(EventData.AuthenticationEvent->Authentication_Event_Data.Long_Term_Key_Request.Rand, RandomNumber)))
                     {
                        /* Search for the entry for this slave to store */
                        /* the information into.                        */
                        if((DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.AuthenticationEvent->BD_ADDR)) != NULL)
                        {
                           /* Check to see if the LTK is valid.         */
                           if(DeviceInfo->Flags & DEVICE_INFO_FLAGS_LTK_VALID)
                           {
                              /* Respond with the stored Long Term Key. */
                              GAP_LE_Authentication_Response_Information.Authentication_Data_Length                                        = QAPI_BLE_GAP_LE_LONG_TERM_KEY_INFORMATION_DATA_SIZE;
                              GAP_LE_Authentication_Response_Information.Authentication_Data.Long_Term_Key_Information.Encryption_Key_Size = DeviceInfo->EncryptionKeySize;

                              memscpy(&(GAP_LE_Authentication_Response_Information.Authentication_Data.Long_Term_Key_Information.Long_Term_Key), sizeof(GAP_LE_Authentication_Response_Information.Authentication_Data.Long_Term_Key_Information.Long_Term_Key), &(DeviceInfo->LTK), QAPI_BLE_LONG_TERM_KEY_SIZE);
                           }
                        }
                     }
                     else
                     {
                        /* The other side of a connection is requesting */
                        /* that we start encryption.  Thus we should    */
                        /* regenerate LTK for this connection and send  */
                        /* it to the chip.                              */
                        Result = qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(BLE_Demo_Context.BluetoothStackID, (qapi_BLE_Encryption_Key_t *)(&(BLE_Demo_Context.DHK)), (qapi_BLE_Encryption_Key_t *)(&ER), EventData.AuthenticationEvent->Authentication_Event_Data.Long_Term_Key_Request.EDIV, &(EventData.AuthenticationEvent->Authentication_Event_Data.Long_Term_Key_Request.Rand), &GeneratedLTK);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Regenerate_Long_Term_Key", Result);

                        if(Result == QAPI_OK)
                        {
                           /* Respond with the Re-Generated Long Term   */
                           /* Key.                                      */
                           GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type                                        = QAPI_BLE_LAR_LONG_TERM_KEY_E;
                           GAP_LE_Authentication_Response_Information.Authentication_Data_Length                                        = QAPI_BLE_GAP_LE_LONG_TERM_KEY_INFORMATION_DATA_SIZE;
                           GAP_LE_Authentication_Response_Information.Authentication_Data.Long_Term_Key_Information.Encryption_Key_Size = QAPI_BLE_GAP_LE_MAXIMUM_ENCRYPTION_KEY_SIZE;
                           GAP_LE_Authentication_Response_Information.Authentication_Data.Long_Term_Key_Information.Long_Term_Key       = GeneratedLTK;
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to generate long term key returned.\r\n");
                        }
                     }

                     /* Send the Authentication Response. */
                     Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                     /* Inform the user the result of BLE operation. */
                     QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);
                     if(Result == QAPI_OK)
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                     }
                     else
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                     }
                     break;

                  /* LAT Security request. */
                  case QAPI_BLE_LAT_SECURITY_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LAT security request:\r\n");
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR: %s.\n", BoardStr);
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Bonding Type: %s.\n", ((EventData.AuthenticationEvent->Authentication_Event_Data.Security_Request.Bonding_Type == QAPI_BLE_LBT_BONDING_E)?"Bonding":"No Bonding"));
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "MITM: %s.\n", ((EventData.AuthenticationEvent->Authentication_Event_Data.Security_Request.MITM)?"YES":"NO"));

                     /* Try to start the pairing process. */
                     if(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.SecurityRemoteBD_ADDR))
                     {
                        /* Go ahead and store the address of the remote */
                        /* device we are currently pairing or           */
                        /* re-establishing security with.               */
                        BLE_Demo_Context.SecurityRemoteBD_ADDR = EventData.AuthenticationEvent->BD_ADDR;

                        /* Determine if we have previously paired with  */
                        /* the device.  If we have paired we will       */
                        /* attempt to re-establish security using a     */
                        /* previously exchanged LTK.                    */
                        if((DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.AuthenticationEvent->BD_ADDR)) != NULL)
                        {
                           /* Determine if a Valid Long Term Key is     */
                           /* stored for this device.                   */
                           if(DeviceInfo->Flags & DEVICE_INFO_FLAGS_LTK_VALID)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Attempting to Re-Establish Security.\r\n");

                              /* Attempt to re-establish security to    */
                              /* this device.                           */
                              GAP_LE_Security_Information.Local_Device_Is_Master                                      = TRUE;
                              GAP_LE_Security_Information.Security_Information.Master_Information.EDIV                = DeviceInfo->EDIV;
                              GAP_LE_Security_Information.Security_Information.Master_Information.Encryption_Key_Size = DeviceInfo->EncryptionKeySize;
                              memscpy(&(GAP_LE_Security_Information.Security_Information.Master_Information.LTK), sizeof(GAP_LE_Security_Information.Security_Information.Master_Information.LTK), &(DeviceInfo->LTK), sizeof(DeviceInfo->LTK));
                              memscpy(&(GAP_LE_Security_Information.Security_Information.Master_Information.Rand), sizeof(GAP_LE_Security_Information.Security_Information.Master_Information.Rand), &(DeviceInfo->Rand), sizeof(DeviceInfo->Rand));

                              Result = qapi_BLE_GAP_LE_Reestablish_Security(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.SecurityRemoteBD_ADDR, &GAP_LE_Security_Information, BLE_GAP_LE_Event_Callback, 0);

                              /* Inform the user the result of BLE operation. */
                              QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Reestablish_Security", Result);
                              if(Result == QAPI_OK)
                              {
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE reestablish security sent successfully.\r\n");
                              }
                              else
                              {
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE reestablish security.\r\n");
                              }
                           }
                           else
                           {
                              /* We do not have a stored Link Key for   */
                              /* this device so go ahead and pair to    */
                              /* this device.                           */
                              SendPairingRequest(BLE_Demo_Context.SecurityRemoteBD_ADDR, true);
                           }
                        }
                        else
                        {
                           /* There is no Key Info Entry for this device*/
                           /* so we will just treat this as a slave     */
                           /* request and initiate pairing.             */
                           SendPairingRequest(BLE_Demo_Context.SecurityRemoteBD_ADDR, true);
                        }
                     }
                     else
                     {
                        /* Inform the user that we cannot accept the    */
                        /* request at this time. */
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Security is already in progress with another remote device.\r\n");

                        /* We are currently pairing/re-establishing     */
                        /* security with another remote device so we    */
                        /* should send the negative authentication      */
                        /* response.                                    */
                        GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_ERROR_E;
                        GAP_LE_Authentication_Response_Information.Authentication_Data_Length = 0;

                        /* Submit the Authentication Response.          */
                        Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                        if(Result == QAPI_OK)
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                        }
                     }
                     break;

                  /* Pairing request. */
                  case QAPI_BLE_LAT_PAIRING_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LAT Pairing Request: %s.\r\n", BoardStr);

                     /* Display the legacy pairing request info. */
                     DisplayLegacyPairingInformation(&(EventData.AuthenticationEvent->Authentication_Event_Data.Pairing_Request));

                     /* Make sure we are NOT pairing or re-establishing */
                     /* security with another remote device.            */
                     if(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.SecurityRemoteBD_ADDR))
                     {
                        /* Go ahead and store the address of the remote */
                        /* device we are currently pairing or           */
                        /* re-establishing security with.               */
                        BLE_Demo_Context.SecurityRemoteBD_ADDR = EventData.AuthenticationEvent->BD_ADDR;

                        /* This is a pairing request.  Respond with a   */
                        /* Pairing Response.                            */
                        /* * NOTE * This is only sent from Master to    */
                        /*          Slave.  Thus we must be the Slave in*/
                        /*          this connection.                    */

                        /* Send the Pairing Response.                   */
                        SlavePairingRequestResponse(BLE_Demo_Context.SecurityRemoteBD_ADDR);
                     }
                     else
                     {
                        /* Inform the user that we cannot accept the    */
                        /* request at this time.                        */
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Security is already in progress with another remote device.\r\n");

                        /* We are currently pairing/re-establishing     */
                        /* security with another remote device so we    */
                        /* should send the negative authentication      */
                        /* response.                                    */
                        GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_ERROR_E;
                        GAP_LE_Authentication_Response_Information.Authentication_Data_Length = 0;

                        /* Submit the Authentication Response. */
                        Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                        if(Result == QAPI_OK)
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                        }
                     }
                     break;

                  /* Extended pairing request. */
                  case QAPI_BLE_LAT_EXTENDED_PAIRING_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LAT Extended Pairing Request: %s.\n", BoardStr);

                     /* Display the extended pairing request info. */
                     DisplayPairingInformation(&(EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Pairing_Request));

                     /* Make sure we are NOT pairing or re-establishing */
                     /* security with another remote device.            */
                     if(QAPI_BLE_COMPARE_NULL_BD_ADDR(BLE_Demo_Context.SecurityRemoteBD_ADDR))
                     {
                        /* Go ahead and store the address of the remote */
                        /* device we are currently pairing or           */
                        /* re-establishing security with.               */
                        BLE_Demo_Context.SecurityRemoteBD_ADDR = EventData.AuthenticationEvent->BD_ADDR;

                        /* This is a pairing request.  Respond with a   */
                        /* Pairing Response.                            */
                        /* * NOTE * This is only sent from Master to    */
                        /*          Slave.  Thus we must be the Slave in*/
                        /*          this connection.                    */

                        /* Send the Pairing Response.                   */
                        SlavePairingRequestResponse(EventData.AuthenticationEvent->BD_ADDR);
                     }
                     else
                     {
                        /* Inform the user that we cannot accept the    */
                        /* request at this time.                        */
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Security is already in progress with another remote device.\r\n");

                        /* We are currently pairing/re-establishing     */
                        /* security with another remote device so we    */
                        /* should send the negative authentication      */
                        /* response.                                    */
                        GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_ERROR_E;
                        GAP_LE_Authentication_Response_Information.Authentication_Data_Length = 0;

                        /* Submit the Authentication Response. */
                        Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                        if(Result == QAPI_OK)
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                        }
                     }
                     break;

                  /* GAP LE confirmation request.*/
                  case QAPI_BLE_LAT_CONFIRMATION_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LAT Confirmation Request:\n");

                     /* Check to see what type of confirmation request  */
                     /* this is.                                        */
                     switch(EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Request_Type)
                     {
                        case QAPI_BLE_CRT_NONE_E:
                           /* Handle the just works request.            */
                           GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_CONFIRMATION_E;

                           /* By setting the Authentication_Data_Length */
                           /* to any NON-ZERO value we are informing the*/
                           /* GAP LE Layer that we are accepting Just   */
                           /* Works Pairing.                            */
                           GAP_LE_Authentication_Response_Information.Authentication_Data_Length = sizeof(uint32_t);

                           /* Handle this differently based on the local*/
                           /* IO Caps.                                  */
                           switch(BLE_Demo_Context.PairParameters.IOCapability)
                           {
                              /* IO: no input no output. */
                              case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invoking Just Works.\n");

                                 /* By setting the                      */
                                 /* Authentication_Data_Length to any   */
                                 /* NON-ZERO value we are informing the */
                                 /* GAP LE Layer that we are accepting  */
                                 /* Just Works Pairing.                 */
                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                                 break;

                              /* IO: Display only. */
                              case QAPI_BLE_LIC_DISPLAY_ONLY_E:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation of Pairing.\n");

                                 GAP_LE_Authentication_Response_Information.Authentication_Data.Passkey = EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Display_Passkey;

                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);
                                 break;

                              default:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation of Pairing.\n");

                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                                 break;
                           }

                           /* Inform the user the result of BLE operation. */
                           QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                           if(Result == QAPI_OK)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                           }
                           break;

                        /* CRT passkey. */
                        case QAPI_BLE_CRT_PASSKEY_E:
                           /* Inform the user to call the appropriate   */
                           /* command.                                  */
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Call LEPasskeyResponse [PASSCODE].\n");
                           break;

                        /* CRT display. */
                        case QAPI_BLE_CRT_DISPLAY_E:
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Passkey: %06u.\n", (unsigned int)(EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Display_Passkey));
                           break;

                        default:
                           /* This application doesn't support OOB and  */
                           /* Secure Connections request types will be  */
                           /* handled by the ExtendedConfirmationRequest*/
                           /* event.  So we will simply inform the user.*/
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Authentication method not supported.\n");
                           break;
                     }
                     break;

                  /* GAP LE extended confirmation request. */
                  case QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE Extended Confirmation Request.\n");

                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Secure Connections:     %s.\n", (EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Flags & QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_SECURE_CONNECTIONS)?"YES":"NO");
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Just Works Pairing:     %s.\n", (EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Flags & QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_JUST_WORKS_PAIRING)?"YES":"NO");
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Keypress Notifications: %s.\n", (EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Flags & QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_KEYPRESS_NOTIFICATIONS_REQUESTED)?"YES":"NO");

                     /* Initialize result to valid value.               */
                     Result = 0;

                     /* Check to see what type of confirmation request  */
                     /* this is.                                        */
                     switch(EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Request_Type)
                     {
                        case QAPI_BLE_CRT_NONE_E:
                           /* Handle the just works request.            */
                           GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_CONFIRMATION_E;

                           /* By setting the Authentication_Data_Length */
                           /* to any NON-ZERO value we are informing the*/
                           /* GAP LE Layer that we are accepting Just   */
                           /* Works Pairing.                            */
                           GAP_LE_Authentication_Response_Information.Authentication_Data_Length = sizeof(uint32_t);

                           /* Handle this differently based on the local*/
                           /* IO Caps.                                  */
                           switch(BLE_Demo_Context.PairParameters.IOCapability)
                           {
                              case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invoking Just Works.\n");

                                 /* Just Accept Just Works Pairing.     */
                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                                 break;

                              case QAPI_BLE_LIC_DISPLAY_ONLY_E:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation of Pairing.\n");

                                 GAP_LE_Authentication_Response_Information.Authentication_Data.Passkey = EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Display_Passkey;

                                 /* Submit the Authentication Response. */
                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                                 break;

                              default:
                                 QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation of Pairing.\n");

                                 /* Submit the Authentication Response. */
                                 Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);
                                 break;
                           }

                           /* Inform the user the result of BLE operation. */
                           QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                           if(Result == QAPI_OK)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                           }
                           break;

                        case QAPI_BLE_CRT_PASSKEY_E:
                           /* Inform the user to call the appropriate   */
                           /* command.                                  */
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Call LEPasskeyResponse [PASSKEY].\n");
                           break;

                        case QAPI_BLE_CRT_DISPLAY_E:
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Passkey: %06u.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Display_Passkey);

                           GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type  = QAPI_BLE_LAR_PASSKEY_E;
                           GAP_LE_Authentication_Response_Information.Authentication_Data_Length  = (uint8_t)(sizeof(uint32_t));
                           GAP_LE_Authentication_Response_Information.Authentication_Data.Passkey = EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Display_Passkey;

                           /* Since this is in an extended confirmation */
                           /* request we need to respond to the display */
                           /* request.                                  */
                           Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                           /* Inform the user the result of BLE operation. */
                           QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                           if(Result == QAPI_OK)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                           }
                           break;

                        case QAPI_BLE_CRT_DISPLAY_YES_NO_E:
                           /* Handle the Display Yes/No request.        */
                           GAP_LE_Authentication_Response_Information.GAP_LE_Authentication_Type = QAPI_BLE_LAR_CONFIRMATION_E;

                           /* By setting the Authentication_Data_Length */
                           /* to any NON-ZERO value we are informing the*/
                           /* GAP LE Layer that we are accepting Just   */
                           /* Works Pairing.                            */
                           GAP_LE_Authentication_Response_Information.Authentication_Data_Length = sizeof(uint32_t);

                           /* Check to see if this is Just Works or     */
                           /* Numeric Comparison.                       */
                           if(EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Flags & QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_JUST_WORKS_PAIRING)
                           {
                              /* Handle this differently based on the   */
                              /* local IO Caps.                         */
                              switch(BLE_Demo_Context.PairParameters.IOCapability)
                              {
                                 case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
                                    QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invoking Just Works.\n");

                                    Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);

                                    break;

                                 case QAPI_BLE_LIC_DISPLAY_ONLY_E:
                                    QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Passkey: %06u.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Display_Passkey);

                                    GAP_LE_Authentication_Response_Information.Authentication_Data.Passkey = EventData.AuthenticationEvent->Authentication_Event_Data.Confirmation_Request.Display_Passkey;

                                    /* Submit the Authentication        */
                                    /* Response.                        */
                                    Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);
                                    break;

                                 default:
                                    QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation of Pairing.\n");

                                    /* Submit the Authentication        */
                                    /* Response.                        */
                                    Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);
                                    break;
                              }
                           }
                           else
                           {
                              /* This is numeric comparison so go ahead */
                              /* and display the numeric value to       */
                              /* confirm.                               */
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Confirmation Value: %ld\n", (unsigned long)(EventData.AuthenticationEvent->Authentication_Event_Data.Extended_Confirmation_Request.Display_Passkey));

                              /* Submit the Authentication        */
                              /* Response.                        */
                              Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR, &GAP_LE_Authentication_Response_Information);
                              break;
                           }

                           /* Inform the user the result of BLE operation. */
                           QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                           if(Result == QAPI_OK)
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                           }
                           break;

                        default:
                           /* This application doesn't support OOB so we*/
                           /* will simply inform the user.              */
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Authentication method not supported.\n");
                           break;
                     }

                     QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

                     if(Result == QAPI_OK)
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE authentication response sent successfully.\r\n");
                     }
                     else
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GAP LE authentication response.\r\n");
                     }
                     break;

                  case QAPI_BLE_LAT_SECURITY_ESTABLISHMENT_COMPLETE_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Security Re-Establishment Complete: %s.\n", BoardStr);
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status: 0x%02X.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Security_Establishment_Complete.Status);

                     /* If this failed due to a LTK issue then we should*/
                     /* delete the LTK.                                 */
                     if(EventData.AuthenticationEvent->Authentication_Event_Data.Security_Establishment_Complete.Status == QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_LONG_TERM_KEY_ERROR)
                     {
                        if((DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.AuthenticationEvent->BD_ADDR)) != NULL)
                        {
                           /* Clear the flag indicating the LTK is      */
                           /* valid.                                    */
                           DeviceInfo->Flags &= ~DEVICE_INFO_FLAGS_LTK_VALID;
                        }
                     }

                     /* Flag the we are no longer                       */
                     /* pairing/re-establishing security with a remote  */
                     /* device.                                         */
                     QAPI_BLE_ASSIGN_BD_ADDR(BLE_Demo_Context.SecurityRemoteBD_ADDR, 0, 0, 0, 0, 0, 0);
                     break;

                  case QAPI_BLE_LAT_PAIRING_STATUS_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pairing Status: %s.\n", BoardStr);
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status: 0x%02X.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Pairing_Status.Status);

                     if(EventData.AuthenticationEvent->Authentication_Event_Data.Pairing_Status.Status == QAPI_BLE_GAP_LE_PAIRING_STATUS_NO_ERROR)
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Key Size: %d.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Pairing_Status.Negotiated_Encryption_Key_Size);
                     }
                     else
                     {
                        /* Disconnect the Link.                         */
                        /* * NOTE * Since we failed to pair, the remote */
                        /*          device information will be deleted  */
                        /*          when the GATT Disconnection event is*/
                        /*          received.                           */
                        Result = qapi_BLE_GAP_LE_Disconnect(BLE_Demo_Context.BluetoothStackID, EventData.AuthenticationEvent->BD_ADDR);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Disconnect", Result);
                     }

                     /* Flag the we are no longer                       */
                     /* pairing/re-establishing security with a remote  */
                     /* device.                                         */
                     QAPI_BLE_ASSIGN_BD_ADDR(BLE_Demo_Context.SecurityRemoteBD_ADDR, 0, 0, 0, 0, 0, 0);

                     /* Regardless of pairing status we will request an */
                     /* update of the P256 Public Key after every LE    */
                     /* pairing operation.  This follows the suggestion */
                     /* from Erratum 10734 (Core Pairing Updates v1.0)  */
                     /* to prevent an attacker from retrieving useful   */
                     /* info about the local's device private key.      */
                     Result = qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(BLE_Demo_Context.BluetoothStackID);

                     /* Inform the user the result of BLE operation. */
                     QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Update_Local_P256_Public_Key", Result);
                     break;

                  case QAPI_BLE_LAT_ENCRYPTION_INFORMATION_REQUEST_E:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Encryption Information Request %s.\n", BoardStr);

                     /* Generate new LTK, EDIV and Rand and respond with*/
                     /* them.                                           */
                     EncryptionInformationRequestResponse(EventData.AuthenticationEvent->BD_ADDR, EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Request_Information.Encryption_Key_Size, &GAP_LE_Authentication_Response_Information);
                     break;

                  case QAPI_BLE_LAT_ENCRYPTION_INFORMATION_E:
                     /* Display the information from the event.         */
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Encryption Information from RemoteDevice: %s.\n", BoardStr);
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Key Size: %d.\n", EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Information.Encryption_Key_Size);

                     /* Search for the entry for this slave to store the*/
                     /* information into.                               */
                     if((DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), EventData.AuthenticationEvent->BD_ADDR)) != NULL)
                     {
                        DeviceInfo->EDIV               = EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Information.EDIV;
                        DeviceInfo->EncryptionKeySize  = EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Information.Encryption_Key_Size;
                        DeviceInfo->Flags             |= DEVICE_INFO_FLAGS_LTK_VALID;
                        memscpy(&(DeviceInfo->LTK), sizeof(DeviceInfo->LTK), &(EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Information.LTK), sizeof(DeviceInfo->LTK));
                        memscpy(&(DeviceInfo->Rand), sizeof(DeviceInfo->Rand), &(EventData.AuthenticationEvent->Authentication_Event_Data.Encryption_Information.Rand), sizeof(DeviceInfo->Rand));
                     }
                     else
                     {
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "No Key Info Entry for this device.\n");
                     }
                     break;

                  default:
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Unhandled GAP LE authentication event data.\r\n");
                     break;
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP authentication event data.\r\n");
            }
            break;

         case QAPI_BLE_ET_LE_REMOTE_FEATURES_RESULT_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE remote features result event with length: %d.\r\n", DataLength);
            EventData.RemoteFeaturesEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Remote_Features_Event_Data;
            if(EventData.RemoteFeaturesEvent)
            {
               BD_ADDRToStr(EventData.RemoteFeaturesEvent->BD_ADDR, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD Adress: %s.\r\n", BoardStr);
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP LE remote features result event data.\r\n");
            }
            break;

         case QAPI_BLE_ET_LE_LOCAL_P256_PUBLIC_KEY_UPDATE_COMPLETE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE local P256 public key update complete event with length: %d.\r\n", DataLength);
            EventData.LocalP256PublicKeyUpdateCompleteEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data;
            if(EventData.LocalP256PublicKeyUpdateCompleteEvent)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Status: %d.\r\n", EventData.LocalP256PublicKeyUpdateCompleteEvent->Status);
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP LE local P256 public key update complete event data.\r\n");
            }
            break;

         case QAPI_BLE_ET_LE_PHY_UPDATE_COMPLETE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE PHY update complete event with length: %d.\r\n", DataLength);
            break;

         case QAPI_BLE_ET_LE_EXTENDED_ADVERTISING_REPORT_E:

            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE extended advertising report event with length: %d.\r\n", DataLength);

            EventData.AdvertisingReportEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Extended_Advertising_Report_Event_Data;
            if(EventData.AdvertisingReportEvent)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "%u Responses\n", EventData.AdvertisingReportEvent->Number_Device_Entries);

               for(Index = 0; Index < EventData.AdvertisingReportEvent->Number_Device_Entries; ++Index)
               {
                  DisplayAdvertiseData((Index + 1), &((EventData.AdvertisingReportEvent->Extended_Advertising_Data)[Index]));
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid BLE advertising report event data.\r\n");
            }

            break;

         case QAPI_BLE_ET_LE_ADVERTISING_SET_TERMINATED_E:
            EventData.AdvertisingSetTermiantedEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Set_Terminated_Event_Data;
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE advertising set terminated event with length: %d.\r\n", DataLength);
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Handle: %u.\r\n", EventData.AdvertisingSetTermiantedEvent->Advertising_Handle);
            break;

         case QAPI_BLE_ET_LE_CHANNEL_SELECTION_ALGORITHM_UPDATE_E:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GAP LE channel select algorithm update event with length: %d.\r\n", DataLength);
            EventData.ChannelSelectAlgorithmUpdateEvent = GAP_LE_Event_Data->Event_Data.GAP_LE_Channel_Selection_Algorithm_Update_Event_Data;
            if(EventData.ChannelSelectAlgorithmUpdateEvent)
            {
               BD_ADDRToStr(EventData.ChannelSelectAlgorithmUpdateEvent->Connection_Address, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Adress: %s.\r\n", BoardStr);
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GAP LE channel select algorithm update event data.\r\n");
            }
            break;

         default:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Unhandled GAP LE event type: %d.\r\n", GAP_LE_Event_Data->Event_Data_Type);
            break;
      }
   }
}

/**
   @brief Callback function to handle GATT connection event.

   Parameter_List[0] is the Bluetooth stack ID.
   Parameter_List[1] is the GATT connection event.
   Parameter_List[2] is the callback parameter.
*/
static void BLE_GATT_Connection_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Event_Data_t *GATT_Connection_Event_Data, unsigned long CallbackParameter)
{
   BoardStr_t             BoardStr;
   Generic_Device_Info_t *DeviceInfo;
   qapi_Status_t          Result;
   uint16_t               MTU;

   if((BLE_Demo_Context.BluetoothStackID == BluetoothStackID) && (GATT_Connection_Event_Data))
   {
      switch(GATT_Connection_Event_Data->Event_Data_Type)
      {
         case QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_E:
            if(GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT Connection Device Connection event with size %d: \r\n", GATT_Connection_Event_Data->Event_Data_Size);

               BD_ADDRToStr(GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection ID:   %d.\r\n", GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->ConnectionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Type: %s.\r\n", ((GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR"));
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote Device Adress: %s.\r\n", BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection MTU: %d.\r\n", GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->MTU);

               /* Try to find the info about remote device in device info */
               /* list. */
               DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice);

               if((DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice)) == NULL)
               {
                  /* A new device is connecting woth us, allocate a new */
                  /* entry in the device info list. */
                  DeviceInfo = CreateNewDeviceInfoEntry(&(BLE_Demo_Context.DeviceInfoList), GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice);

                  if(DeviceInfo == NULL)
                  {
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to create remote device information.\r\n");
                  }
               }

               /* Make sure we found the remote device information entry or */
               /* has created it. */
               if(DeviceInfo)
               {
                  /* Increment the number of connected remote devices.  */
                  BLE_Demo_Context.ConnectedDeviceCounter += 1;

                  /* Note: the demo will treat the device with most recent */
                  /* connection event as the active connected device. The */
                  /* data will be send to and received from this device. */
                  BLE_Demo_Context.ActiveConnectionID      = GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->ConnectionID;
                  BLE_Demo_Context.ActiveConnectionBD_ADDR = GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice;

                  /* Updata device info. */
                  DeviceInfo->LocalDeviceIsMaster = BLE_Demo_Context.LocalDeviceIsMaster;
                  DeviceInfo->DeviceAddressType   = BLE_Demo_Context.ConnectingDeviceAddressType;
                  DeviceInfo->DeviceAddress       = GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice;
                  DeviceInfo->ConnectionID        = GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->ConnectionID;

                  /* Inform the user of the active connected remote device.     */
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Active Remote Device:\r\n");
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Address:       %s\n", BoardStr);
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   ID:            %u\n", BLE_Demo_Context.ActiveConnectionID);

                  if(BLE_Demo_Context.LocalDeviceIsMaster)
                  {
                     /* Try to exchange the MTU info. */
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Try to exchange MTU info: \r\n");

                     /* Attempt to update the MTU to the maximum supported.*/
                     Result = qapi_BLE_GATT_Query_Maximum_Supported_MTU(BLE_Demo_Context.BluetoothStackID, &MTU);

                     /* Inform the user the result of BLE operation. */
                     QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Query_Maximum_Supported_MTU", Result);

                     if(Result == QAPI_OK)
                     {
                        /* Send the GATT exchange MTU request. */
                        Result = qapi_BLE_GATT_Exchange_MTU_Request(BLE_Demo_Context.BluetoothStackID, DeviceInfo->ConnectionID, MTU, BLE_GATT_Client_Event_Callback, 0);

                        if(Result)
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT exchange MTU request transaction ID: %d.\r\n", Result);
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to send GATT exchange MTU request.\r\n");
                        }
                     }
                  }
               }
               else
               {
                  /* The device entry could not be found or created, the */
                  /* connection could not be established, so proceed to */
                  /* disconnect procedure. */
                  Result = qapi_BLE_GAP_LE_Disconnect(BLE_Demo_Context.BluetoothStackID, GATT_Connection_Event_Data->Event_Data.GATT_Device_Connection_Data->RemoteDevice);

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Disconnect", Result);
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT connection device connection event.\r\n");
            }
            break;

         case QAPI_BLE_ET_GATT_CONNECTION_DEVICE_DISCONNECTION_E:
            if(GATT_Connection_Event_Data->Event_Data.GATT_Device_Disconnection_Data)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT Connection Device Disconnection with size %d: \r\n", GATT_Connection_Event_Data->Event_Data_Size);
               BD_ADDRToStr(GATT_Connection_Event_Data->Event_Data.GATT_Device_Disconnection_Data->RemoteDevice, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Connection ID:   %u.\n", GATT_Connection_Event_Data->Event_Data.GATT_Device_Disconnection_Data->ConnectionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Connection Type: %s.\n", ((GATT_Connection_Event_Data->Event_Data.GATT_Device_Disconnection_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR"));
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Remote Device:   %s.\n", BoardStr);

               /* Check if the disconnecting device is the atctive */
               /* connection device. */
               if(QAPI_BLE_COMPARE_BD_ADDR(GATT_Connection_Event_Data->Event_Data.GATT_Device_Disconnection_Data->RemoteDevice, BLE_Demo_Context.ActiveConnectionBD_ADDR))
               {
                  DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);

                  if(DeviceInfo != NULL)
                  {
                     DeviceInfo = DeleteDeviceInfoEntry(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);
                     if(DeviceInfo != NULL)
                     {
                        /* Inform the user the remote device information*/
                        /* is being deleted.                            */
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "The remote device information has been deleted.\r\n", BoardStr);

                        /* The entry has been removed from the list so  */
                        /* we just need to free the memory.             */
                        FreeDeviceInfoEntryMemory(DeviceInfo);

                        /* Mark the active connection ID and active connection */
                        /* BD_ADDR to 0 and NULL. */
                        QAPI_BLE_ASSIGN_BD_ADDR(BLE_Demo_Context.ActiveConnectionBD_ADDR, 0, 0, 0, 0, 0, 0);
                        BLE_Demo_Context.ActiveConnectionID = 0;

                        /* Update the connection counter. */
                        if(BLE_Demo_Context.ConnectedDeviceCounter)
                        {
                           BLE_Demo_Context.ConnectedDeviceCounter -= 1;
                        }
                     }
                     else
                     {
                        /* Failed to delete device info in device list. */
                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to delete device info in device list when disconnecting.\r\n", BoardStr);
                     }
                  }
                  else
                  {
                     /* Failed to find device info in device list. */
                     QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Data received for unknown device.\r\n", BoardStr);
                  }
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT connection device disconnection event.\r\n");
            }
            break;

         case QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E:
            if(GATT_Connection_Event_Data->Event_Data.GATT_Server_Notification_Data)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "GATT Connection server notitication event with size %d: \r\n", GATT_Connection_Event_Data->Event_Data_Size);

               /* Find the Device Info for the device that has sent us the */
               /* notification. */

               DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), GATT_Connection_Event_Data->Event_Data.GATT_Server_Notification_Data->RemoteDevice);
               if(DeviceInfo != NULL)
               {
                  if(DeviceInfo->GATTProfileFlags & SUPPORTED_GATT_PROFILE_BAS)
                  {
                     /* Handle the BAS notifications. */
                     Handle_BAS_Notification(GATT_Connection_Event_Data->Event_Data.GATT_Server_Notification_Data);
                  }
               }
               else
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Data received for unknown device.\r\n");
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT server notification data.\r\n");
            }
            break;

         default:
            break;
      }
   }
}

/**
   @brief Callback function to handle GATT service discovery event.

   Parameter_List[0] is the Bluetooth stack ID.
   Parameter_List[1] is the GATT service discovery event.
   Parameter_List[2] is the callback parameter.
*/
static void BLE_GATT_Service_Discovery_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data, unsigned long CallbackParameter)
{
   Generic_Device_Info_t *DeviceInfo;

   if((BLE_Demo_Context.BluetoothStackID == BluetoothStackID) && (GATT_Service_Discovery_Event_Data))
   {
      DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BLE_Demo_Context.ActiveConnectionBD_ADDR);
      if(DeviceInfo != NULL)
      {
         switch(GATT_Service_Discovery_Event_Data->Event_Data_Type)
         {
            case QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E:
               /* Verify the event data.                                */
               if(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Service 0x%04X - 0x%04X, UUID: ", GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.Service_Handle, GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.End_Group_Handle);
                  DisplayUUID(BLE_Demo_Context.QCLI_Handle, &(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.UUID));

                  /* Attempt to populate the handles for the GAP        */
                  /* Service.                                           */
                  GAPSPopulateHandles(&(DeviceInfo->GAPSClientInfo), GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data);

                  /* Attempt to populate the handles for the Custom     */
                  /* Service.                                           */
                  CustomPopulateHandles(&(DeviceInfo->CustomClientInfo), GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data);
               }
               break;

            case QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E:
               /* Verify the event data.                                */
               if(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Complete_Data)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Service Discovery Operation Complete, Status 0x%02X.\n", GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Complete_Data->Status);

                  /* Flag that no service discovery operation is        */
                  /* outstanding for this device.                       */
                  DeviceInfo->Flags &= ~DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING;
               }
               break;

            default:
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Unhandled GATT service discovery event: %d.\r\n", GATT_Service_Discovery_Event_Data->Event_Data_Type);
               break;
         }
      }
   }
}

/**
@brief Callback function to handle GATT client event.

Parameter_List[0] is the Bluetooth stack ID.
Parameter_List[1] is the GATT service discovery event.
Parameter_List[2] is the callback parameter.
*/
static void BLE_GATT_Client_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data, unsigned long CallbackParameter)
{
   char                  *NameBuffer;
   Generic_Device_Info_t *DeviceInfo;
   uint16_t               Appearance;
   uint32_t               Value;
   BoardStr_t             BoardStr;

   /* Verify that all parameters to this callback are Semi-Valid. */
   if((BLE_Demo_Context.BluetoothStackID == BluetoothStackID) && (GATT_Client_Event_Data))
   {
      /* Determine the event that occurred. */
      switch(GATT_Client_Event_Data->Event_Data_Type)
      {
         case QAPI_BLE_ET_GATT_CLIENT_ERROR_RESPONSE_E:
            if(GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data)
            {
               BD_ADDRToStr(GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->RemoteDevice, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Error Response.\n");
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection ID:   %d.\n", GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ConnectionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Transaction ID:  %d.\n", GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->TransactionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Type: %s.\n", (GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR");
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR:         %s.\n", BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Error Type:      %s.\n", (GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ErrorType == QAPI_BLE_RET_ERROR_RESPONSE_E)?"Response Error":"Response Timeout");

               /* Only print out the rest if it is valid. */
               if(GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ErrorType == QAPI_BLE_RET_ERROR_RESPONSE_E)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Request Opcode:  0x%02X.\n", GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->RequestOpCode);
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Request Handle:  0x%04X.\n", GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->RequestHandle);
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Error Code:      0x%02X.\n", GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ErrorCode);
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Error Mesg:      %s.\n", ErrorCodeStr[GATT_Client_Event_Data->Event_Data.GATT_Request_Error_Data->ErrorCode]);
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT client error response data.\r\n");
            }
            break;

         case QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E:
            if(GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data)
            {
               BD_ADDRToStr(GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data->RemoteDevice, BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Exchange MTU Response.\n");
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection ID:   %d.\n", GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data->ConnectionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Transaction ID:  %d.\n", GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data->TransactionID);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Type: %s.\n", (GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR");
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BD_ADDR:         %s.\n", BoardStr);
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "MTU:             %u.\n", GATT_Client_Event_Data->Event_Data.GATT_Exchange_MTU_Response_Data->ServerMTU);
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT client write response data.\r\n");
            }
            break;

         case QAPI_BLE_ET_GATT_CLIENT_READ_RESPONSE_E:
            if(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data)
            {
               DeviceInfo = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->RemoteDevice);
               if(DeviceInfo != NULL)
               {
                  if(DeviceInfo->GAPSClientInfo.DeviceNameHandle == (uint16_t)CallbackParameter)
                  {
                     /* Display the remote device name.                 */
                     if((NameBuffer = (char *)qapi_Malloc(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength + 1)) != NULL)
                     {
                        memset(NameBuffer, 0, GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength + 1);
                        memscpy(NameBuffer, (GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength + 1), GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValue, GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength);

                        QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote Device Name: %s.\r\n", NameBuffer);
                        qapi_Free(NameBuffer);
                     }
                  }
                  else
                  {
                     if(DeviceInfo->GAPSClientInfo.DeviceAppearanceHandle == (uint16_t)CallbackParameter)
                     {
                        if(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength == QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_LENGTH)
                        {
                           Appearance = READ_UNALIGNED_WORD_LITTLE_ENDIAN(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValue);

                           if(AppearanceToString(Appearance, &NameBuffer))
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote Device Appearance: %s(%u).\n", NameBuffer, Appearance);
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Remote Device Appearance: Unknown(%u).\n", Appearance);
                           }
                        }
                        else
                        {
                           QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid Remote Appearance Value Length %u.\n", GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength);
                        }
                     }
                     else
                     {
                        if(DeviceInfo->CustomClientInfo.ReadHandle == (uint16_t)CallbackParameter)
                        {
                           if(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength >= QAPI_BLE_NON_ALIGNED_DWORD_SIZE)
                           {
                              Value = QAPI_BLE_READ_UNALIGNED_DWORD_LITTLE_ENDIAN(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValue);

                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Read value: %u.\n", Value);
                           }
                           else
                           {
                              QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid attribute length %u.\n", GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength);
                           }
                        }
                     }
                  }
               }
            }
            else
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid GATT client read response data.\r\n");
            }
            break;

         default:
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Unhandled GATT client event type :d.\r\n", GATT_Client_Event_Data->Event_Data_Type);
            break;
      }
   }
}

/**
@brief Callback function to handle GATT server event.

Parameter_List[0] is the Bluetooth stack ID.
Parameter_List[1] is the GATT server event.
Parameter_List[2] is the callback parameter.
*/
static void Custom_GATTServerEventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Server_Event_Data_t *GATT_ServerEventData, unsigned long CallbackParameter)
{
   qapi_BLE_NonAlignedDWord_t Temp;

   if((BluetoothStackID) && (GATT_ServerEventData))
   {
      switch(GATT_ServerEventData->Event_Data_Type)
      {
         case QAPI_BLE_ET_GATT_SERVER_READ_REQUEST_E:
            /* Make sure this is not a GATT read long request.          */
            if(GATT_ServerEventData->Event_Data.GATT_Read_Request_Data->AttributeValueOffset == 0)
            {
               /* Determine the attribute that is being read based on   */
               /* the received attribute offset. .                      */
               switch(GATT_ServerEventData->Event_Data.GATT_Read_Request_Data->AttributeOffset)
               {
                  case CUSTOM_READ_CHARACTERISTIC_ATTRIBUTE_OFFSET:
                     /* We will simply send the Bluetooth stack ID for  */
                     /* the attribute value.                            */
                     QAPI_BLE_ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD(&Temp, BluetoothStackID);

                     /* Respond to the GATT client with the attribute   */
                     /* value.                                          */
                     qapi_BLE_GATT_Read_Response(BluetoothStackID, GATT_ServerEventData->Event_Data.GATT_Read_Request_Data->TransactionID, QAPI_BLE_NON_ALIGNED_DWORD_SIZE, (uint8_t *)&Temp);
                     break;
                  default:
                     /* We wouldn't have received the callback unless   */
                     /* the attribute was in range of the custom        */
                     /* service.                                        */
                     break;
               }
            }
            else
            {
               qapi_BLE_GATT_Error_Response(BluetoothStackID, GATT_ServerEventData->Event_Data.GATT_Read_Request_Data->TransactionID, GATT_ServerEventData->Event_Data.GATT_Read_Request_Data->AttributeOffset, QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_ATTRIBUTE_NOT_LONG);
            }
            break;

         default:
            /* We wouldn't have received the callback since the custom  */
            /* service does not support any other characteristic or     */
            /* attribute properties.                                    */
            break;
      }
   }
}

/**
   @brief Get the discoverability mode.
*/
static void GetDiscoverabilityMode(void)
{
   char *DisplayString;

   /* Display Connectability_Mode. */
   switch(BLE_Demo_Context.DiscoverabilityMode)
   {
      case QAPI_BLE_DM_NON_DISCOVERABLE_MODE_E:
         DisplayString = "Not Discoverable";
         break;

      case QAPI_BLE_DM_LIMITED_DISCOVERABLE_MODE_E:
         DisplayString = "Limited Discoverable";
         break;

      case QAPI_BLE_DM_GENERAL_DISCOVERABLE_MODE_E:
         DisplayString = "General Discoverable";
         break;

      default:
         DisplayString = NULL;
         break;
   }

   if(DisplayString != NULL)
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Discoverability Mode: %s.\r\n", DisplayString);
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Invalid Discoverability Mode.\r\n");
   }
}

/**
   @brief Set Discoverability mode.

   Parameter_List[0] (0-2) is a flag indicates the discover ability mode to be
                     set.
                     0 = Not Discoverable.
                     1 = Limited Discoverable.
                     2 = General Discoverable.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetDiscoverabilityMode(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t  Ret_Val;
   char    *Mode;

   /* Make sure that all of the parameters required for this function
      appear to be at least semi-valid. */
   if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_DM_NON_DISCOVERABLE_MODE_E, QAPI_BLE_DM_GENERAL_DISCOVERABLE_MODE_E)))
   {
      /* Parameters appear to be valid, map the specified parameters into
         the API specific parameters. */
      if(Parameter_List[0].Integer_Value == 0)
      {
         Mode = "Not Discoverable";
      }
      else if(Parameter_List[0].Integer_Value == 1)
      {
         Mode = "Limited Discoverable";
      }
      else
      {
         Mode = "General Discoverable";
      }

      BLE_Demo_Context.DiscoverabilityMode = (qapi_BLE_GAP_Discoverability_Mode_t)(Parameter_List[0].Integer_Value);

      /* The Mode was changed successfully. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Discoverability mode changed to: %s.\r\n", Mode);

      /* Flag success to the caller. */
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Discoverability Mode: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 0 [Mode(0=Non Discoverable, 1=Limited Discoverable, 2=General Discoverable)].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Get the advertise connectability prameters.
*/
static void GetAdvertiseConnectabilityParameters(void)
{
   char                           *DisplayString;
   qapi_BLE_GAP_LE_Address_Type_t  AddressType;
   BoardStr_t                      BoardStr;

   /* Display Connectability_Mode. */
   switch(BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode)
   {
      case QAPI_BLE_LCM_NON_CONNECTABLE_E:
         DisplayString = "LCM Non Connectable";
         break;

      case QAPI_BLE_LCM_CONNECTABLE_E:
         DisplayString = "LCM Connectable";
         break;

      case QAPI_BLE_LCM_DIRECT_CONNECTABLE_E:
         DisplayString = "LCM Direct Connectable";
         break;

      case QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E:
         DisplayString = "LCM Low Duty Cycle Direct Connectable";
         break;

      default:
         DisplayString = NULL;
         break;
   }

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connectability Parameters:\r\n");

   if(DisplayString != NULL)
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Connectability Mode: %s.\r\n", DisplayString);
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Invalid Connectability Mode.\r\n");
   }

   AddressType = BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Own Address Type: %s.\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));

   /* Determine if we need to display Direct_Address_Type and
      Direct_Address. */
   if(((BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode == QAPI_BLE_LCM_DIRECT_CONNECTABLE_E) || (BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode == QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E)) || ((BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type == QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E) || (BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type == QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E)))
   {
      /* Convert the address type to string. */
      AddressType = BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address_Type;
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Direct Address Type: %s.\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));

      /* Dispaly Direct_Address. */
      BD_ADDRToStr(BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address, BoardStr);
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Direct Address: %s.\r\n", BoardStr);
   }
}

/**
   @brief Set advertise connectability parameters.

   Parameter_List[0] is the connectability mode.
   Parameter_List[1] is the own address type.
   Parameter_List[2] is the direct address type.
   Parameter_List[3] is the direct address.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetAdvertiseConnectabilityParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Ret_Val;

   /* Make sure that Connectability_Mode and Own_Address_Type are provided
      at least and thery are in proper range. */
   if((Parameter_Count >= 2) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_LCM_NON_CONNECTABLE_E, QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E)) && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_LAT_PUBLIC_E, QAPI_BLE_LAT_ANONYMOUS_E)))
   {
      /* Set Connectability_Mode. */
      BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode = (qapi_BLE_GAP_LE_Connectability_Mode_t)(Parameter_List[0].Integer_Value);

      /* Set Own_Address_Type. */
      BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type = (qapi_BLE_GAP_LE_Address_Type_t)(Parameter_List[1].Integer_Value);

      /* Determine if Direct_Address_Type and Direct_Address should be
         set. */
      if(((BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode == QAPI_BLE_LCM_DIRECT_CONNECTABLE_E) || (BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode == QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E)) || ((BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type == QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E) || (BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type == QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E)))
      {
         if((Parameter_Count >= 4) && (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_LAT_PUBLIC_E, QAPI_BLE_LAT_ANONYMOUS_E)))
         {
            BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address_Type = (qapi_BLE_GAP_LE_Address_Type_t)(Parameter_List[2].Integer_Value);

            /* Convert the user provided address value to qapi format. */
            StrToBD_ADDR(Parameter_List[3].String_Value, &(BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address));

            /* We are done with setting the connectability parameters and
               set return value to success. */
            Ret_Val = true;
         }
         else
         {
            /* The parameters are invalid. */
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Need direct BDADDR type and direct BDADDR.\r\n");
            Ret_Val = false;
         }
      }
      else
      {
         /* We are done with setting the connectability parameters and set
            return value to success. */
         Ret_Val = true;
      }

      if(Ret_Val)
      {
         /* The Mode was changed successfully. */
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connectability had been set successfully.\r\n");
      }
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Connectability parameters: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 1 [Connect Mode][Own Address Type][Direct Address Type][Direct Address].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Get the advertise LE parameters.
*/
static void GetAdvertiseLEParameters(void)
{
   qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Advertise LE Parameters:\r\n");

   /* Display Advertising_Interval_Min. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Min Advertising Interval: %d.\r\n", BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Min);

   /* Display Advertising_Interval_Max. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Max Advertising Interval: %d.\r\n", BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Max);

   /* Display Advertising_Channel_Map. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Advertising Channel Map: %d.\r\n", BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Channel_Map);

   /* Convert Scan_Request_Filter to string. */
   FilterPolicy = BLE_Demo_Context.AdvertisingParameters.Parameters.Scan_Request_Filter;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Scan Request Filter: %s.\r\n", ((FilterPolicy <= NUMBER_OF_FILTER_POLICIES) ? Filter_Policy_Strings[FilterPolicy]: Filter_Policy_Strings[NUMBER_OF_FILTER_POLICIES]));

   /* Convert Connect_Request_Filter to string. */
   FilterPolicy = BLE_Demo_Context.AdvertisingParameters.Parameters.Connect_Request_Filter;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Connect Request Filter: %s.\r\n", ((FilterPolicy <= NUMBER_OF_FILTER_POLICIES) ? Filter_Policy_Strings[FilterPolicy]: Filter_Policy_Strings[NUMBER_OF_FILTER_POLICIES]));

   /* Display BREDRSupport. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Advertise BREDR Support: %s.\r\n", ((BLE_Demo_Context.AdvertisingParameters.BREDRSupport) ? "Yes" : "No"));

   /* Display scan response enable. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Scan response: %s.\r\n", ((BLE_Demo_Context.AdvertisingParameters.ScanResponse == true) ? "Yes" : "No"));
}

/**
   @brief Set Advertise LE parameters.

   Parameter_List[0] is the minimum advertise interval in millisecond.
   Parameter_List[1] is the maximum advertise interval in millisecond.
   Parameter_List[2] is the advertising channel map.
   Parameter_List[3] is the scan request filter.
   Parameter_List[4] is the connect request filter.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetAdvertiseLEParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Ret_Val;

   /* Make sure that Connectability_Mode and Own_Address_Type are provided
      at least and thery are in proper range. */
   if((Parameter_Count >= 7) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_MINIMUM_ADVERTISING_INTERVAL, QAPI_BLE_MAXIMUM_ADVERTISING_INTERVAL))
      && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_MINIMUM_ADVERTISING_INTERVAL, QAPI_BLE_MAXIMUM_ADVERTISING_INTERVAL))
      && (Parameter_List[2].Integer_Is_Valid) && (QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_FP_NO_FILTER_E, QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E))
      && (QCLI_Verify_Integer_Parameter(&Parameter_List[4], QAPI_BLE_FP_NO_FILTER_E, QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[5], 0, 1))) && ((QCLI_Verify_Integer_Parameter(&Parameter_List[6], 0, 1))))
   {
      if(Parameter_List[0].Integer_Value < Parameter_List[1].Integer_Value)
      {
         /* Set Advertising_Interval_Min and Advertising_Interval_Max. */
         BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Min = (uint16_t)(Parameter_List[0].Integer_Value);
         BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Max = (uint16_t)(Parameter_List[1].Integer_Value);

         Ret_Val = true;
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Advertise interval min must be less than advertise interval max.\n");

         Ret_Val = false;
      }

      if(Ret_Val)
      {
         /* Set Advertising_Channel_Map. */
         BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Channel_Map = (uint8_t)(Parameter_List[2].Integer_Value);

         /* Set Scan_Request_Filter. */
         BLE_Demo_Context.AdvertisingParameters.Parameters.Scan_Request_Filter = (qapi_BLE_GAP_LE_Filter_Policy_t)(Parameter_List[3].Integer_Value);

         /* Set Connect_Request_Filter. */
         BLE_Demo_Context.AdvertisingParameters.Parameters.Connect_Request_Filter = (qapi_BLE_GAP_LE_Filter_Policy_t)(Parameter_List[4].Integer_Value);

         /* Set BREDRSupport. */
         BLE_Demo_Context.AdvertisingParameters.BREDRSupport = (qbool_t)(Parameter_List[5].Integer_Value);

         /* Set ScanResponse. */
         BLE_Demo_Context.AdvertisingParameters.ScanResponse = (qbool_t)(Parameter_List[6].Integer_Value);

         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "LE advertising parameters had been set successfully.\n");
      }
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Advertise LE parameters: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 2 [MIN Advertise Interval][MAX Advertise Interval][Advertise Channle Map][Scan Request Filter][Connect Request Filter][BR EDR Support][Scan Response].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Get the scan parameters.
*/
static void GetScanParameters(void)
{
   qapi_BLE_GAP_LE_Address_Type_t  AddressType;
   qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan Parameters:\r\n");

   /* Display scan type. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Scan type: %s.\r\n", ((BLE_Demo_Context.ScanParameters.ScanType == QAPI_BLE_ST_PASSIVE_E) ? "ST PASSIVE" : "ST ACTIVE"));

   /* Display scan interval. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Scan interval: %d.\r\n", BLE_Demo_Context.ScanParameters.ScanInterval);

   /* Display scan window. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Scan window: %d.\r\n", BLE_Demo_Context.ScanParameters.ScanWindow);

   /* Display local address type. */
   AddressType = BLE_Demo_Context.ScanParameters.LocalAddressType;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Local address type: %s.\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));

   /* Display filter policy. */
   FilterPolicy = BLE_Demo_Context.ScanParameters.FilterPolicy;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Filter policy: %s.\r\n", ((FilterPolicy <= NUMBER_OF_FILTER_POLICIES) ? Filter_Policy_Strings[FilterPolicy]: Filter_Policy_Strings[NUMBER_OF_FILTER_POLICIES]));

   /* Display filter duplicates. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Filter duplicates: %s.\r\n", ((BLE_Demo_Context.ScanParameters.FilterDuplicates == true) ? "Yes" : "No"));
}

/**
   @brief Set Scan parameters.

   Parameter_List[0] is scan type.
   Parameter_List[1] is scan interval.
   Parameter_List[2] is scan window.
   Parameter_List[3] is local address type.
   Parameter_List[4] is filter policy.
   Parameter_List[5] is fliter duplicates.
   Parameter_List[5] is the flag indicates if scan response is enabled.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetScanParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Ret_Val;

   /* Make sure that Connectability_Mode and Own_Address_Type are provided
      at least and thery are in proper range. */
   if((Parameter_Count >= 6) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_ST_PASSIVE_E, QAPI_BLE_ST_ACTIVE_E)) && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_MINIMUM_LE_SCAN_INTERVAL, QAPI_BLE_MAXIMUM_LE_SCAN_INTERVAL))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_MINIMUM_LE_SCAN_WINDOW, QAPI_BLE_MAXIMUM_LE_SCAN_WINDOW))) && ((QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_LAT_PUBLIC_E, QAPI_BLE_LAT_ANONYMOUS_E)))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[4], QAPI_BLE_FP_NO_FILTER_E, QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E))) && (QCLI_Verify_Integer_Parameter(&Parameter_List[5], 0, 1)))
   {
      BLE_Demo_Context.ScanParameters.ScanType         = (qapi_BLE_GAP_LE_Scan_Type_t)(Parameter_List[0].Integer_Value);
      BLE_Demo_Context.ScanParameters.ScanInterval     = (uint32_t)(Parameter_List[1].Integer_Value);
      BLE_Demo_Context.ScanParameters.ScanWindow       = (uint32_t)(Parameter_List[2].Integer_Value);
      BLE_Demo_Context.ScanParameters.LocalAddressType = (qapi_BLE_GAP_LE_Address_Type_t)(Parameter_List[3].Integer_Value);
      BLE_Demo_Context.ScanParameters.FilterPolicy     = (qapi_BLE_GAP_LE_Filter_Policy_t)(Parameter_List[4].Integer_Value);
      BLE_Demo_Context.ScanParameters.FilterDuplicates = (qbool_t)(Parameter_List[5].Integer_Value);

      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Scan parameters had been set successfully.\n");

      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Scan parameters: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 3 [Scan Type][Scan Interval][Scan Window][Local Address Type][Filter Policy][Filter Duplicates(0=No,1=Yes)].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Get the connection parameters.
*/
static void GetConnectionParameters(void)
{
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection Parameters:\r\n");

   /* Display Connection interval min. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MIN Connection Interval: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Connection_Interval_Min);

   /* Display Connection interval max. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MAX Connection Interval: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Connection_Interval_Max);

   /* Display Slave latency */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Slave Latency: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Slave_Latency);

   /* Display Supervision timeout. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Supervision Timeout: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Supervision_Timeout);

   /* Display Minimum connection length. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MIN Connection Length: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Minimum_Connection_Length);

   /* Display Maximum connection length. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MAX Connection Length: %d.\r\n", BLE_Demo_Context.ConnectionParamters.Maximum_Connection_Length);
}

/**
   @brief Set Connection parameters

   Parameter_List[0] is minimum connection interval.
   Parameter_List[1] is maximum connection interval.
   Parameter_List[2] is slave latency.
   Parameter_List[3] is supervision timeout.
   Parameter_List[4] is minimum connection length.
   Parameter_List[5] is maximum connection length.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetConnectionParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Ret_Val;

   /* Make sure that Connectability_Mode and Own_Address_Type are provided
      at least and thery are in proper range. */
   if((Parameter_Count >= 6) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_MINIMUM_MINIMUM_CONNECTION_INTERVAL, QAPI_BLE_MAXIMUM_MINIMUM_CONNECTION_INTERVAL))
      && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_MINIMUM_MAXIMUM_CONNECTION_INTERVAL, QAPI_BLE_MAXIMUM_MAXIMUM_CONNECTION_INTERVAL))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_MINIMUM_SLAVE_LATENCY, QAPI_BLE_MAXIMUM_SLAVE_LATENCY))) && ((QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_MINIMUM_LINK_SUPERVISION_TIMEOUT, QAPI_BLE_MAXIMUM_LINK_SUPERVISION_TIMEOUT)))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[4], QAPI_BLE_MINIMUM_CONNECTION_EVENT_LENGTH, QAPI_BLE_MAXIMUM_CONNECTION_EVENT_LENGTH))) && (QCLI_Verify_Integer_Parameter(&Parameter_List[5], QAPI_BLE_MINIMUM_CONNECTION_EVENT_LENGTH, QAPI_BLE_MAXIMUM_CONNECTION_EVENT_LENGTH)))
   {
      /* Verify if MIN connection interval is less than MAX connection interval. */
      if((uint16_t)(Parameter_List[0].Integer_Value) < (uint16_t)(Parameter_List[1].Integer_Value))
      {
         BLE_Demo_Context.ConnectionParamters.Connection_Interval_Min = (uint16_t)(Parameter_List[0].Integer_Value);
         BLE_Demo_Context.ConnectionParamters.Connection_Interval_Max = (uint16_t)(Parameter_List[1].Integer_Value);

         Ret_Val = true;
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "MIN connection interval must be less than MAX connection interval.\n");

         Ret_Val = false;
      }

      if(Ret_Val)
      {
         /* Verify if MIN connection length is less than MAX connection length. */
         if((uint16_t)(Parameter_List[4].Integer_Value) < (uint16_t)(Parameter_List[5].Integer_Value))
         {
            BLE_Demo_Context.ConnectionParamters.Minimum_Connection_Length = (uint16_t)(Parameter_List[4].Integer_Value);
            BLE_Demo_Context.ConnectionParamters.Maximum_Connection_Length = (uint16_t)(Parameter_List[5].Integer_Value);

            Ret_Val = true;
         }
         else
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "MIN connection length must be less than MAX connection length.\n");

            Ret_Val = false;
         }
      }

      if(Ret_Val)
      {
         /* Everything is fine, sets up the remaining connectoin parameters. */
         BLE_Demo_Context.ConnectionParamters.Slave_Latency       = (uint16_t)(Parameter_List[2].Integer_Value);
         BLE_Demo_Context.ConnectionParamters.Supervision_Timeout = (uint16_t)(Parameter_List[3].Integer_Value);

         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Connection parameters had been set successfully.\n");
      }
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Connection parameters: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 4 [MIN Connection Interval(8-4000)][MAX Connection Interval(8-4000)][Slave Latency(0-500)][Supervision Timeout(100-32000)][MIN Connection Length(0-40959)][MAX Connection Length(0-40959)].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Get the pair parameters.
*/
static void GetPairParameters(void)
{
   char *DisplayString;

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pair Parameters:\r\n");

   /* Display I/O capabilitty. */
   switch(BLE_Demo_Context.PairParameters.IOCapability)
   {
      case QAPI_BLE_LIC_DISPLAY_ONLY_E:
         DisplayString = "Display Only";
         break;

      case QAPI_BLE_LIC_DISPLAY_YES_NO_E:
         DisplayString = "Display Yes No";
         break;

      case QAPI_BLE_LIC_KEYBOARD_ONLY_E:
         DisplayString = "Keyboard Only";
         break;

      case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
         DisplayString = "No Input, No Output";
         break;

      case QAPI_BLE_LIC_KEYBOARD_DISPLAY_E:
         DisplayString = "Keyboard Display";
         break;

      default:
         DisplayString = NULL;
         break;
   }

   if(DisplayString != NULL)
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " I/O Capability: %s.\r\n", DisplayString);
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Invalid I/O Capability Setting.\r\n");
   }

   /* Display MITM protection. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MITM Protection: %s.\r\n", ((BLE_Demo_Context.PairParameters.MITMProtection == 0) ? "No" : "Yes"));

   /* Display secure connection. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Secure Connection: %s.\r\n", ((BLE_Demo_Context.PairParameters.SecureConnections == 0) ? "No" : "Yes"));

   /* Display OOB data present. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " OOB Data Present: %s.\r\n", ((BLE_Demo_Context.PairParameters.OOBDataPresent == 0) ? "No" : "Yes"));
}

/**
   @brief Set Pair parameters

   Parameter_List[0] is I/O capability.
   Parameter_List[1] is MITM proctection flag.
   Parameter_List[2] is secure connection flag.
   Parameter_List[3] is OOB data present flag.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - true  indicates the parameters are set successfully.
    - false indicates the parameters are not set successfully.
*/
static qbool_t SetPairParameters(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Ret_Val;

   /* Make sure the parameters provided are valid. */
   if((Parameter_Count >= 4) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_LIC_DISPLAY_ONLY_E, QAPI_BLE_LIC_KEYBOARD_DISPLAY_E)) && (QCLI_Verify_Integer_Parameter(&Parameter_List[1], 0, 1))
      && ((QCLI_Verify_Integer_Parameter(&Parameter_List[2], 0, 1))) && ((QCLI_Verify_Integer_Parameter(&Parameter_List[3], 0, 1))))
   {
      BLE_Demo_Context.PairParameters.IOCapability      = (qapi_BLE_GAP_LE_IO_Capability_t)(Parameter_List[0].Integer_Value);
      BLE_Demo_Context.PairParameters.MITMProtection    = (qbool_t)(Parameter_List[1].Integer_Value);
      BLE_Demo_Context.PairParameters.SecureConnections = (qbool_t)(Parameter_List[2].Integer_Value);
      BLE_Demo_Context.PairParameters.OOBDataPresent    = (qbool_t)(Parameter_List[3].Integer_Value);

      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Pair parameters had been set successfully.\n");

      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   if(!Ret_Val)
   {
      /* Print out the usage string. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Usage for Set Pair parameters: \r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "SetLEParameters 5 [IO Capability][MITM Protection][Secure Connections][OOB Data Present].\r\n");
   }

   return(Ret_Val);
}

/**
   @brief Populate defualt LE parameters.
*/
static void PopulateDefaultLEParameters(void)
{
   /* Populate default pairing parametrs. */
   BLE_Demo_Context.PairParameters.IOCapability      = QAPI_BLE_LIC_DISPLAY_YES_NO_E;
   BLE_Demo_Context.PairParameters.MITMProtection    = true;
   BLE_Demo_Context.PairParameters.SecureConnections = true;
   BLE_Demo_Context.PairParameters.OOBDataPresent    = false;

   /* Populate default connection parameters. */
   BLE_Demo_Context.ConnectionParamters.Connection_Interval_Min   = 50;
   BLE_Demo_Context.ConnectionParamters.Connection_Interval_Max   = 100;
   BLE_Demo_Context.ConnectionParamters.Slave_Latency             = 30;
   BLE_Demo_Context.ConnectionParamters.Supervision_Timeout       = 10000;
   BLE_Demo_Context.ConnectionParamters.Minimum_Connection_Length = 0;
   BLE_Demo_Context.ConnectionParamters.Maximum_Connection_Length = 20000;

   /* Populate default advertising parameters. */
   BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Min = 100;
   BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Interval_Max = 200;
   BLE_Demo_Context.AdvertisingParameters.Parameters.Advertising_Channel_Map  = QAPI_BLE_GAP_LE_ADVERTISING_CHANNEL_MAP_USE_ALL_CHANNELS;
   BLE_Demo_Context.AdvertisingParameters.Parameters.Scan_Request_Filter      = QAPI_BLE_FP_NO_FILTER_E;
   BLE_Demo_Context.AdvertisingParameters.Parameters.Connect_Request_Filter   = QAPI_BLE_FP_NO_FILTER_E;
   BLE_Demo_Context.AdvertisingParameters.BREDRSupport                        = false;
   BLE_Demo_Context.AdvertisingParameters.ScanResponse                        = true;

   /* Populate default advertising connectability parameters. */
   BLE_Demo_Context.AdvertiseConnectabilityParameters.Connectability_Mode = QAPI_BLE_LCM_CONNECTABLE_E;
   BLE_Demo_Context.AdvertiseConnectabilityParameters.Own_Address_Type    = QAPI_BLE_LAT_PUBLIC_E;
   BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address_Type = QAPI_BLE_LAT_PUBLIC_E;
   QAPI_BLE_ASSIGN_BD_ADDR(BLE_Demo_Context.AdvertiseConnectabilityParameters.Direct_Address, 0, 0, 0, 0, 0, 0);

   /* Populate scan parameters. */
   BLE_Demo_Context.ScanParameters.ScanType         = QAPI_BLE_ST_ACTIVE_E;
   BLE_Demo_Context.ScanParameters.ScanInterval     = 10;
   BLE_Demo_Context.ScanParameters.ScanWindow       = 10;
   BLE_Demo_Context.ScanParameters.LocalAddressType = QAPI_BLE_LAT_PUBLIC_E;
   BLE_Demo_Context.ScanParameters.FilterPolicy     = QAPI_BLE_FP_NO_FILTER_E;
   BLE_Demo_Context.ScanParameters.FilterDuplicates = true;
}

/**
   @brief Populate extended capabilities.

   @param Capabilities is the extended capabilties to be populated.
*/
static void PopulateExtendedCapabilities(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Capabilities)
{
   if(Capabilities != NULL)
   {
      memset(Capabilities, 0, QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_SIZE);

      if(BLE_Demo_Context.PairParameters.MITMProtection)
      {
         Capabilities->Flags |= QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_MITM_REQUESTED;
      }

      if(BLE_Demo_Context.PairParameters.SecureConnections)
      {
         Capabilities->Flags |= QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_SECURE_CONNECTIONS;
      }

      if(BLE_Demo_Context.PairParameters.OOBDataPresent)
      {
         Capabilities->Flags |= QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_OOB_DATA_PRESENT;
      }

      Capabilities->IO_Capability                     = BLE_Demo_Context.PairParameters.IOCapability;
      Capabilities->Bonding_Type                      = QAPI_BLE_LBT_BONDING_E;
      Capabilities->Maximum_Encryption_Key_Size       = QAPI_BLE_GAP_LE_MAXIMUM_ENCRYPTION_KEY_SIZE;

      Capabilities->Receiving_Keys.Encryption_Key     = true;
      Capabilities->Receiving_Keys.Identification_Key = false;
      Capabilities->Receiving_Keys.Signing_Key        = false;
      Capabilities->Receiving_Keys.Link_Key           = false;

      Capabilities->Sending_Keys.Encryption_Key       = true;
      Capabilities->Sending_Keys.Identification_Key   = false;
      Capabilities->Sending_Keys.Signing_Key          = false;
      Capabilities->Sending_Keys.Link_Key             = false;
   }
}

/**
   @brief Displays the received advertise data.

   @param AdvertisingReportEvent is the received advertise data.
*/
static void DisplayAdvertiseData(uint32_t ResponseNumber, qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t *AdvertiseReportData)
{
   qapi_BLE_GAP_LE_Address_Type_t            AddressType;
   BoardStr_t                                BoardStr;
   uint32_t                                  DataEntryIndex;
   uint32_t                                  Index;
   qapi_BLE_GAP_LE_Advertising_Data_Entry_t  Advertising_Data_Entry;
   uint8_t                                  *AdvertisingData;
   uint16_t                                  AdvertisingDataLength;
   uint16_t                                  Length;

   /* Display response number. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Response: %d\r\n", ResponseNumber);

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "\r\nAdvertising Report:\r\n");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Properties: 0x%08lX\r\n", AdvertiseReportData->Event_Type_Flags);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Connectable:          %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_CONNECTABLE)         ? "Yes" : "No");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Scannable:            %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SCANNABLE)           ? "Yes" : "No");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Directed:             %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_DIRECTED)            ? "Yes" : "No");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Scan Response:        %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SCAN_RESPONSE)       ? "Yes" : "No");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Legacy PDU:           %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_LEGACY_PDU)          ? "Yes" : "No");
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "      Secondary PHY Valid:  %s\r\n", (AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SECONDARY_PHY_VALID) ? "Yes" : "No");

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Data Status: %u\r\n", AdvertiseReportData->Data_Status);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Primary PHY: %u\r\n", AdvertiseReportData->Primary_PHY);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Secondary PHY: %u\r\n", AdvertiseReportData->Secondary_PHY);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Tx Power: %u\r\n", AdvertiseReportData->Tx_Power);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Periodic Adv. intervalr: %u\r\n", AdvertiseReportData->Periodic_Advertising_Interval);

   /* Display address type. */
   AddressType = AdvertiseReportData->Address_Type;
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Address type: %s\r\n", ((AddressType <= NUMBER_OF_ADDRESS_TYPES) ? Address_Type_Strings[AddressType]: Address_Type_Strings[NUMBER_OF_ADDRESS_TYPES]));

   /* Display the address. */
   BD_ADDRToStr(AdvertiseReportData->BD_ADDR, BoardStr);
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Address: %s\r\n", BoardStr);

   /* Display the RSSI. */
   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "RSSI: %d\r\n", AdvertiseReportData->RSSI);

   /* Only display advertising data for legacy advertising PDU.s. In order
      to display extended PDUs we would need to track the advertising report's
      fragmented advertising data if it all cannot be received in single extended
      advertising report. We will not do this. */
   if((AdvertiseReportData->Event_Type_Flags & GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_LEGACY_PDU) && (AdvertiseReportData->Raw_Report_Length <= QAPI_BLE_ADVERTISING_DATA_SIZE))
   {
      /* Process raw advertising data. */
      DataEntryIndex        = 0;
      AdvertisingDataLength = AdvertiseReportData->Raw_Report_Length;
      AdvertisingData       = AdvertiseReportData->Raw_Report_Data;

      /* Make sure we have enough remaining advertising data to decode
         the mandatory fields for the TLV. */
      while(AdvertisingDataLength >= ADVERTISING_DATA_TLV_SIZE(0))
      {
         /* Decode the advertising data entry. */
         Advertising_Data_Entry.AD_Data_Length = QAPI_BLE_READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((Advertising_Data_TLV_t *)AdvertisingData)->Length));
         Advertising_Data_Entry.AD_Type        = QAPI_BLE_READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((Advertising_Data_TLV_t *)AdvertisingData)->Type));
         Advertising_Data_Entry.AD_Data_Buffer = (uint8_t *)&(((Advertising_Data_TLV_t *)AdvertisingData)->Variable_Data[0]);

         /* Since we know the AD Length we can use it to determine
            the actual length of the advertising data entry.  */
         Length = ADVERTISING_DATA_TLV_SIZE(Advertising_Data_Entry.AD_Data_Length - QAPI_BLE_NON_ALIGNED_BYTE_SIZE);

         /* Make sure the advertising TLV is less than or equal to
            the remaining amount of advertising data.*/
         if(AdvertisingDataLength >= Length)
         {
            /* Subtract one from the AD length field to get the actual
               length of the TLV data. */
            Advertising_Data_Entry.AD_Data_Length -= QAPI_BLE_NON_ALIGNED_BYTE_SIZE;

            /* Display the TLV. */
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Advertise data entry: %d\r\n", (DataEntryIndex + 1));

            /* Display AD type. */
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "AD Type: %d\r\n", (Advertising_Data_Entry.AD_Type));

            /* Display AD data. */
            if(Advertising_Data_Entry.AD_Data_Length)
            {
               QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Advertise data: \r\n");
               for(Index = 0; Index < Advertising_Data_Entry.AD_Data_Length; Index++)
               {
                  QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "%d ", Advertising_Data_Entry.AD_Data_Buffer[Index]);
               }
            }

            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "\r\n");

            /* Continue to the next TLV. */
            DataEntryIndex++;
            AdvertisingDataLength -= Length;
            AdvertisingData       += Length;
         }
         else
         {
            /* Malformatted advertising data. We will stop here
               an assume everything that follows is also malformatted. */
            break;
         }
      }
   }

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "\r\n");
}

/**
   @brief Sends the pairing request.

   @param BD_ADDR       is Bluetooth address (Caller should ensure the
                        BD ADDR is not NULL.)

   @param LocalIsMaster is the flag indicates if the local device is master.

   @return
    - zero          indicates the function is executed successfully.
    - negtive value indicates the function is failed to execute.
*/
static qapi_Status_t SendPairingRequest(qapi_BLE_BD_ADDR_t BD_ADDR, qbool_t LocalIsMaster)
{
   qapi_Status_t                                   Result;
   qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t Capabilities;

   if(!QAPI_BLE_COMPARE_NULL_BD_ADDR(BD_ADDR))
   {
      /* Populate the extended capabilities. */
      PopulateExtendedCapabilities(&Capabilities);

      if(LocalIsMaster)
      {
         /* Try to pair with the remote device. */
         Result = qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(BLE_Demo_Context.BluetoothStackID, BD_ADDR, &Capabilities, BLE_GAP_LE_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Extended_Pair_Remote_Device", Result);

        if(Result == QAPI_BLE_BTPS_ERROR_SECURE_CONNECTIONS_NOT_SUPPORTED)
         {
            QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Secure connection is not supported and will try to pair without secure connection.\r\n");

            /* Secure connection is not supported and clear the
               corresponding flag in Capabilities. */
            Capabilities.Flags &= ~ QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_SECURE_CONNECTIONS;

            /* Try to pair with remote device without secure connection.*/
            Result = qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionBD_ADDR, &Capabilities, BLE_GAP_LE_Event_Callback, 0);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Extended_Pair_Remote_Device", Result);
         }
      }
      else
      {
         /* Device is slave and it should request the master to start
            pairring procedure. */
         Result = qapi_BLE_GAP_LE_Extended_Request_Security(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.ActiveConnectionBD_ADDR, &Capabilities, BLE_GAP_LE_Event_Callback, 0);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Extended_Request_Security", Result);
      }
   }
   else
   {
      Result = QAPI_ERROR;
   }

   return(Result);
}

/**
   @brief Sends the slave pairing request response.

   @param BD_ADDR   is Bluetooth address (Caller should ensure the BD ADDR is
                    not NULL.)

   @return
    - zero          indicates the function is executed successfully.
    - negtive value indicates the function is failed to execute.
*/
static qapi_Status_t SlavePairingRequestResponse(qapi_BLE_BD_ADDR_t BD_ADDR)
{
   qapi_Status_t                                         Result;
   qapi_BLE_GAP_LE_Authentication_Response_Information_t AuthenticationResponseData;

   if(!QAPI_BLE_COMPARE_NULL_BD_ADDR(BD_ADDR))
   {
      /* We must be the slave if we have received a Pairing Request     */
      /* thus we will respond with our capabilities.                    */
      AuthenticationResponseData.GAP_LE_Authentication_Type = QAPI_BLE_LAR_PAIRING_CAPABILITIES_E;
      AuthenticationResponseData.Authentication_Data_Length = QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_SIZE;

      /* Configure the Application Pairing Parameters. */
      PopulateExtendedCapabilities(&(AuthenticationResponseData.Authentication_Data.Extended_Pairing_Capabilities));

      /* Attempt to pair to the remote device. */
      Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, BD_ADDR, &AuthenticationResponseData);

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);

      if(Result == QAPI_BLE_BTPS_ERROR_SECURE_CONNECTIONS_NOT_SUPPORTED)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Secure Connections not supported, disabling Secure Connections.\r\n");

         AuthenticationResponseData.Authentication_Data.Extended_Pairing_Capabilities.Flags &= ~QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_SECURE_CONNECTIONS;

         /* Try this again.                                             */
         Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, BD_ADDR, &AuthenticationResponseData);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);
      }
   }
   else
   {
      Result = QAPI_ERROR;
   }

   return(Result);
}

/**
   @brief Sends encryption info request response.

   @param BD_ADDR   is Bluetooth address (Caller should ensure the BD ADDR is
                    not NULL.)

   @param KeySize   is the key size.

   @param GAP_LE_Authentication_Response_Information
                    is authentication response.

   @return
    - zero          indicates the function is executed successfully.
    - negtive value indicates the function is failed to execute.
*/
static qapi_Status_t EncryptionInformationRequestResponse(qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t KeySize, qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Response_Information)
{
   qapi_Status_t Result;
   uint16_t      LocalDiv;

   if((!QAPI_BLE_COMPARE_NULL_BD_ADDR(BD_ADDR)) && (GAP_LE_Authentication_Response_Information != NULL))
   {
       QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Calling GAP_LE_Generate_Long_Term_Key.\n");

      /* Generate a new LTK, EDIV and Rand tuple.                    */
      Result = qapi_BLE_GAP_LE_Generate_Long_Term_Key(BLE_Demo_Context.BluetoothStackID, (qapi_BLE_Encryption_Key_t *)(&(BLE_Demo_Context.DHK)), (qapi_BLE_Encryption_Key_t *)(&ER), &(GAP_LE_Authentication_Response_Information->Authentication_Data.Encryption_Information.LTK), &LocalDiv, &(GAP_LE_Authentication_Response_Information->Authentication_Data.Encryption_Information.EDIV), &(GAP_LE_Authentication_Response_Information->Authentication_Data.Encryption_Information.Rand));

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Generate_Long_Term_Key", Result);

      if(Result == QAPI_OK)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Encryption Information Request Response.\n");

         /* Response to the request with the LTK, EDIV and Rand      */
         /* values.                                                  */
         GAP_LE_Authentication_Response_Information->GAP_LE_Authentication_Type                                     = QAPI_BLE_LAR_ENCRYPTION_INFORMATION_E;
         GAP_LE_Authentication_Response_Information->Authentication_Data_Length                                     = QAPI_BLE_GAP_LE_ENCRYPTION_INFORMATION_DATA_SIZE;
         GAP_LE_Authentication_Response_Information->Authentication_Data.Encryption_Information.Encryption_Key_Size = KeySize;

         Result = qapi_BLE_GAP_LE_Authentication_Response(BLE_Demo_Context.BluetoothStackID, BD_ADDR, GAP_LE_Authentication_Response_Information);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BLE_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Authentication_Response", Result);
      }
   }
   else
   {
      Result = QAPI_ERROR;
   }

   return(Result);
}

/**
   @brief Displays the received legacy pairing request.

   @param AdvertisingReportEvent is the received legacy pairing request.
*/
static void DisplayLegacyPairingInformation(qapi_BLE_GAP_LE_Pairing_Capabilities_t *Pairing_Capabilities)
{
   char *DisplayString;

   if(Pairing_Capabilities != NULL)
   {
      /* Display the IO Capability.                                     */
      switch(Pairing_Capabilities->IO_Capability)
      {
         case QAPI_BLE_LIC_DISPLAY_ONLY_E:
            DisplayString = "Display Only";
            break;

         case QAPI_BLE_LIC_DISPLAY_YES_NO_E:
            DisplayString = "Display Yes No";
            break;

         case QAPI_BLE_LIC_KEYBOARD_ONLY_E:
            DisplayString = "Keyboard Only";
            break;

         case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
            DisplayString = "No Input, No Output";
            break;

         case QAPI_BLE_LIC_KEYBOARD_DISPLAY_E:
            DisplayString = "Keyboard Display";
            break;

         default:
            DisplayString = NULL;
            break;
      }

      if(DisplayString != NULL)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " I/O capability: %s.\r\n", DisplayString);
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Invalid I/O Capability Setting.\r\n");
      }

      /* Display MITM protection. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MITM protection: %s.\r\n", ((Pairing_Capabilities->MITM == 0) ? "No" : "Yes"));

      /* Display Bonding type. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Bonding type: %s.\r\n", ((Pairing_Capabilities->Bonding_Type == QAPI_BLE_LBT_NO_BONDING_E) ? "No Bonding" : "Bonding"));

      /* Display OOB data presnet. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " OOB presented: %s.\r\n", ((Pairing_Capabilities->OOB_Present == 0) ? "No" : "Yes"));

      /* Display encryption key size. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Encryption key size: %d.\r\n", Pairing_Capabilities->Maximum_Encryption_Key_Size);

      /* Display sending keys info. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Sending keys:\r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     LTK: %s.\r\n", (Pairing_Capabilities->Sending_Keys.Encryption_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     IRK: %s.\r\n", (Pairing_Capabilities->Sending_Keys.Identification_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     CSRK: %s.\r\n", (Pairing_Capabilities->Sending_Keys.Signing_Key == true) ? "Yes" : "No" );

      /* Display receving keys info. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Receiving keys:\r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     LTK: %s.\r\n", (Pairing_Capabilities->Receiving_Keys.Encryption_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     IRK: %s.\r\n", (Pairing_Capabilities->Receiving_Keys.Identification_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     CSRK: %s.\r\n", (Pairing_Capabilities->Receiving_Keys.Signing_Key == true) ? "Yes" : "No" );
   }
}

/**
   @brief Displays the received extended pairing data.

   @param AdvertisingReportEvent is the received extended pairing data.
*/
static void DisplayPairingInformation(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Pairing_Capabilities)
{
   char *DisplayString;

   if(Extended_Pairing_Capabilities != NULL)
   {
      /* Display the IO Capability.                                     */
      switch(Extended_Pairing_Capabilities->IO_Capability)
      {
         case QAPI_BLE_LIC_DISPLAY_ONLY_E:
            DisplayString = "Display Only";
            break;

         case QAPI_BLE_LIC_DISPLAY_YES_NO_E:
            DisplayString = "Display Yes No";
            break;

         case QAPI_BLE_LIC_KEYBOARD_ONLY_E:
            DisplayString = "Keyboard Only";
            break;

         case QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E:
            DisplayString = "No Input, No Output";
            break;

         case QAPI_BLE_LIC_KEYBOARD_DISPLAY_E:
            DisplayString = "Keyboard Display";
            break;

         default:
            DisplayString = NULL;
            break;
      }

      if(DisplayString != NULL)
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " I/O capability: %s.\r\n", DisplayString);
      }
      else
      {
         QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Invalid I/O Capability Setting.\r\n");
      }

      /* Display MITM protection. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " MITM protection: %s.\r\n", ((Extended_Pairing_Capabilities->Flags & QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_MITM_REQUESTED) ? "Yes" : "No"));

      /* Display Bonding type. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Bonding type: %s.\r\n", ((Extended_Pairing_Capabilities->Bonding_Type == QAPI_BLE_LBT_NO_BONDING_E) ? "No Bonding" : "Bonding"));

      /* Display OOB data presnet. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " OOB presented: %s.\r\n", ((Extended_Pairing_Capabilities->Flags & QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_OOB_DATA_PRESENT) ? "Yes" : "No"));

      /* Display section connection. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Secure connections: %s.\r\n", ((Extended_Pairing_Capabilities->Flags & QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_SECURE_CONNECTIONS) ? "Yes" : "No"));

      /* Display encryption key size. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, " Encryption key size: %d.\r\n", Extended_Pairing_Capabilities->Maximum_Encryption_Key_Size);

      /* Display sending keys info. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Sending keys:\r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     LTK: %s.\r\n", (Extended_Pairing_Capabilities->Sending_Keys.Encryption_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     IRK: %s.\r\n", (Extended_Pairing_Capabilities->Sending_Keys.Identification_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     CSRK: %s.\r\n", (Extended_Pairing_Capabilities->Sending_Keys.Signing_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     Link key: %s.\r\n", (Extended_Pairing_Capabilities->Sending_Keys.Link_Key == true) ? "Yes" : "No" );

      /* Display receving keys info. */
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "   Receiving keys:\r\n");
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     LTK: %s.\r\n", (Extended_Pairing_Capabilities->Receiving_Keys.Encryption_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     IRK: %s.\r\n", (Extended_Pairing_Capabilities->Receiving_Keys.Identification_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     CSRK: %s.\r\n", (Extended_Pairing_Capabilities->Receiving_Keys.Signing_Key == true) ? "Yes" : "No" );
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "     Link key: %s.\r\n", (Extended_Pairing_Capabilities->Receiving_Keys.Link_Key == true) ? "Yes" : "No" );
   }
}

/**
   @brief Populates GAPS handle.

   @param ClientInfo  is the client info.

   @param ServiceInfo is the service info.
*/
static void GAPSPopulateHandles(GAPS_Client_Info_t *ClientInfo, qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceInfo)
{
   uint32_t                                    Index;
   qapi_BLE_GATT_Characteristic_Information_t *CurrentCharacteristic;

   /* Verify that the input parameters are semi-valid.                  */
   if((ClientInfo) && (ServiceInfo) && (ServiceInfo->ServiceInformation.UUID.UUID_Type == QAPI_BLE_GU_UUID_16_E) && (QAPI_BLE_GAP_COMPARE_GAP_SERVICE_UUID_TO_UUID_16(ServiceInfo->ServiceInformation.UUID.UUID.UUID_16)))
   {
      /* Loop through all characteristics discovered in the service     */
      /* and populate the correct entry.                                */
      CurrentCharacteristic = ServiceInfo->CharacteristicInformationList;
      if(CurrentCharacteristic)
      {
         for(Index = 0; Index < ServiceInfo->NumberOfCharacteristics; Index++, CurrentCharacteristic++)
         {
            /* All GAP Service UUIDs are defined to be 16 bit UUIDs.    */
            if(CurrentCharacteristic->Characteristic_UUID.UUID_Type == QAPI_BLE_GU_UUID_16_E)
            {
               /* Determine which characteristic this is.               */
               if(!QAPI_BLE_GAP_COMPARE_GAP_DEVICE_NAME_UUID_TO_UUID_16(CurrentCharacteristic->Characteristic_UUID.UUID.UUID_16))
               {
                  if(!QAPI_BLE_GAP_COMPARE_GAP_DEVICE_APPEARANCE_UUID_TO_UUID_16(CurrentCharacteristic->Characteristic_UUID.UUID.UUID_16))
                     continue;
                  else
                  {
                     ClientInfo->DeviceAppearanceHandle = CurrentCharacteristic->Characteristic_Handle;
                     continue;
                  }
               }
               else
               {
                  ClientInfo->DeviceNameHandle = CurrentCharacteristic->Characteristic_Handle;
                  continue;
               }
            }
         }
      }
   }
}

/**
   @brief Maps apperance value to apperance string.

   @param AdvertisingReportEvent is the received advertise data.
*/
static qbool_t AppearanceToString(uint16_t Appearance, char **String)
{
   qbool_t  Ret_Val;
   uint32_t Index;

   /* Verify that the input parameters are semi-valid.                  */
   if(String)
   {
      for(Index = 0; Index < NUMBER_OF_APPEARANCE_MAPPINGS; Index++)
      {
         if(AppearanceMappings[Index].Appearance == Appearance)
         {
            *String = AppearanceMappings[Index].String;
            Ret_Val = TRUE;
            break;
         }
      }

      if(Index >= NUMBER_OF_APPEARANCE_MAPPINGS)
      {
         Ret_Val=FALSE;
      }
   }
   else
   {
      Ret_Val = FALSE;
   }

   return(Ret_Val);
}

/**
   @brief Populates Custom service handles during service discovery.

   @param ClientInfo  is the client info.

   @param ServiceInfo is the service info.
*/
static void CustomPopulateHandles(Custom_Client_Info_t *ClientInfo, qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceInfo)
{
   uint32_t                                    Index;
   qapi_BLE_GATT_Characteristic_Information_t *CurrentCharacteristic;

   /* Verify that the input parameters are semi-valid.                  */
   if((ClientInfo) && (ServiceInfo) && (ServiceInfo->ServiceInformation.UUID.UUID_Type == QAPI_BLE_GU_UUID_128_E) && (CUSTOM_COMPARE_CUSTOM_SERVICE_UUID_TO_UUID_128(ServiceInfo->ServiceInformation.UUID.UUID.UUID_128)))
   {
      /* Loop through all characteristics discovered in the service     */
      /* and populate the correct entry.                                */
      CurrentCharacteristic = ServiceInfo->CharacteristicInformationList;
      if(CurrentCharacteristic)
      {
         for(Index = 0; Index < ServiceInfo->NumberOfCharacteristics; Index++, CurrentCharacteristic++)
         {
            /* All Custom Service UUIDs are defined to be 128 bit UUIDs.*/
            if(CurrentCharacteristic->Characteristic_UUID.UUID_Type == QAPI_BLE_GU_UUID_128_E)
            {
               /* Determine which characteristic this is.               */
               if(CUSTOM_READ_CHARACTERISTIC_COMPARE_CHARACTERISTIC_UUID_TO_UUID_128(CurrentCharacteristic->Characteristic_UUID.UUID.UUID_128))
               {
                  ClientInfo->ReadHandle = CurrentCharacteristic->Characteristic_Handle;

                  continue;
               }
            }
         }
      }
   }
}

/**
   @brief Creates a new device info entry in the device list.

   @param ListHead    is the device list.
   @param DeviceAddress is the peer address.

   @return
    - pointer to device entry indicates the function is executed successfully.
    - NULL                    indicates the function is failed to execute.
*/
static Generic_Device_Info_t *CreateNewDeviceInfoEntry(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress)
{
   Generic_Device_Info_t *Ret_Val;
   Generic_Device_Info_t *DeviceInfo;

   /* Verify that the passed in parameters seem semi-valid.             */
   if((ListHead) && (!QAPI_BLE_COMPARE_NULL_BD_ADDR(DeviceAddress)))
   {
      /* Allocate the memory for the entry.                             */
      if((Ret_Val = qapi_Malloc(sizeof(Generic_Device_Info_t))) != NULL)
      {
         /* Initialize the entry.                                       */
         memset(Ret_Val, 0, sizeof(Generic_Device_Info_t));

         /* Store the remote device address.                            */
         Ret_Val->DeviceAddress = DeviceAddress;

         if(*ListHead == NULL)
         {
            /* If the head is NULL, set it to the new entry.            */
            *ListHead = Ret_Val;
         }
         else
         {
            /* Otherwise, loop through the list and find the end.      */
            DeviceInfo = *ListHead;

            while (DeviceInfo)
            {
               if(DeviceInfo->NextDevice == NULL)
               {
                  /* Found the end, now add the new entry.            */
                  DeviceInfo->NextDevice = Ret_Val;
                  break;
               }
               else
               {
                  /* Move to the next entry.                         */
                  DeviceInfo = DeviceInfo->NextDevice;
               }
            }
         }
      }
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
   @brief Searches device info entry in the device list by BD ADDR.

   @param ListHead    is the device list.
   @param DeviceAddress is the peer address.

   @return
    - pointer to device entry indicates the function is executed successfully.
    - NULL                    indicates the function is failed to execute.
*/
static Generic_Device_Info_t *SearchDeviceInfoEntryByBD_ADDR(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress)
{
   Generic_Device_Info_t *Ret_Val;
   Generic_Device_Info_t *DeviceInfo;

   /* Verify the list head. */
   if(ListHead)
   {
      DeviceInfo = *ListHead;
      Ret_Val    = NULL;

      /* Loop through the device information. */
      while(DeviceInfo)
      {
         /* If the BD_ADDR is a match then we found the remote device */
         /* information. */
         if(QAPI_BLE_COMPARE_BD_ADDR(DeviceInfo->DeviceAddress, DeviceAddress))
         {
            /* Set the remote device information pointer to the return  */
            /* value and break since we are done. */
            Ret_Val = DeviceInfo;
            break;
         }

         DeviceInfo = DeviceInfo->NextDevice;
      }
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
   @brief Searches device info entry in the device list by connection ID.

   @param ListHead    is the device list.
   @param DeviceAddress is the peer address.

   @return
    - pointer to device entry indicates the function is executed successfully.
    - NULL                    indicates the function is failed to execute.
*/
static Generic_Device_Info_t *SearchDeviceInfoEntryByConnectionID(Generic_Device_Info_t **ListHead, uint32_t ConnectionID)
{
   Generic_Device_Info_t *Ret_Val;
   Generic_Device_Info_t *DeviceInfo;

   /* Verify the list head. */
   if(ListHead)
   {
      DeviceInfo = *ListHead;
      Ret_Val    = NULL;

      /* Loop through the device information. */
      while(DeviceInfo)
      {
         /* If the connection ID is a match then we found the remote device */
         /* information. */
         if(DeviceInfo->ConnectionID == ConnectionID)
         {
            /* Set the remote device information pointer to the return  */
            /* value and break since we are done. */
            Ret_Val = DeviceInfo;
            break;
         }

         DeviceInfo = DeviceInfo->NextDevice;
      }
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
   @brief Deletes device info entry in the device list by BD ADDR.

   @param ListHead    is the device list.
   @param DeviceAddress is the peer address.

   @return
    - pointer to device entry indicates the function is executed successfully.
    - NULL                    indicates the function is failed to execute.
*/
static Generic_Device_Info_t *DeleteDeviceInfoEntry(Generic_Device_Info_t **ListHead, qapi_BLE_BD_ADDR_t DeviceAddress)
{
   Generic_Device_Info_t *Ret_Val;
   Generic_Device_Info_t *DeviceInfo;
   Generic_Device_Info_t *PrevDeviceInfo;

   if(ListHead)
   {
      DeviceInfo     = *ListHead;
      PrevDeviceInfo = NULL;
      Ret_Val        = NULL;

      while (DeviceInfo)
      {
         /* If the BD_ADDR is a match then we found the remote device   */
         /* information.                                                */
         if(QAPI_BLE_COMPARE_BD_ADDR(DeviceInfo->DeviceAddress, DeviceAddress))
         {
            /* Set the remote device information pointer to the return  */
            /* value and remove from the list.                          */
            Ret_Val = DeviceInfo;

            if (PrevDeviceInfo == NULL)
            {
               /* If this is the head, set the head to the next entry.  */
               *ListHead = Ret_Val->NextDevice;
            }
            else
            {
               /* Otherwise, set the previous entry to the next one.    */
               PrevDeviceInfo->NextDevice = Ret_Val->NextDevice;
            }

            break;
         }
         else
         {
            /* Move to the next entry.                                  */
            PrevDeviceInfo = DeviceInfo;
            DeviceInfo = DeviceInfo->NextDevice;
         }
      }
   }
   else
   {
      Ret_Val = NULL;
   }

   return(Ret_Val);
}

/**
   @brief Free the memory space ocupied by device entry.

   @param EntryToFree is the entry to be freed.
*/
static void FreeDeviceInfoEntryMemory(Generic_Device_Info_t *EntryToFree)
{
   if(EntryToFree)
   {
      qapi_Free((void *)(EntryToFree));
   }
}

/**
   @brief Free the memory space ocupied by the whole device list.

   @param ListHead is the list to be freed.
*/
static void FreeDeviceInfoList(Generic_Device_Info_t **ListHead)
{
   Generic_Device_Info_t *DeviceInfo;
   Generic_Device_Info_t *PrevDeviceInfo;

   if(ListHead)
   {
      DeviceInfo = *ListHead;

      while (DeviceInfo)
      {
         PrevDeviceInfo = DeviceInfo;
         DeviceInfo = DeviceInfo->NextDevice;

         /* Free the entry.                                             */
         qapi_Free(PrevDeviceInfo);
      }

      *ListHead = NULL;
   }
}

static void ShutDownBLEDemo(void)
{
   /* Shutdown the other demo stuff that relies on an open Bluetooth    */
   /* stack.                                                            */
   Shutdown_BAS_Demo();

   /* Shutdown internal things.                                         */
   qapi_BLE_GAPS_Cleanup_Service(BLE_Demo_Context.BluetoothStackID, BLE_Demo_Context.GAPInstanceID);

   qapi_BLE_GATT_Cleanup(BLE_Demo_Context.BluetoothStackID);

   qapi_BLE_BSC_Shutdown(BLE_Demo_Context.BluetoothStackID);

   FreeDeviceInfoList(&(BLE_Demo_Context.DeviceInfoList));
   BLE_Demo_Context.DeviceInfoList   = NULL;
   BLE_Demo_Context.BluetoothStackID = 0;

   QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BT stack has been shutdown successfully.\r\n");
}

/**
   @brief Initializes the BLE demo application.

   @param HCI_DriverInformation  is the HCI driver information for inititializing
                                 the bluetooth stack.
*/
void Initialize_BLE_Demo(qapi_BLE_HCI_DriverInformation_t *HCI_DriverInformation)
{
   memset(&BLE_Demo_Context, 0, sizeof(BLE_Demo_Context_t));

   /* Register top level main BLE command group. */
   BLE_Demo_Context.QCLI_Handle = QCLI_Register_Command_Group(NULL, &BLE_CMD_Group);

   if(BLE_Demo_Context.QCLI_Handle != NULL)
   {
      /* Initialize BAS demo. */
      Initialize_BAS_Demo(BLE_Demo_Context.QCLI_Handle);

      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "BLE Demo Initialized.\n");

      BLE_Demo_Context.DriverInformation = HCI_DriverInformation;
   }
   else
   {
      QCLI_Printf(BLE_Demo_Context.QCLI_Handle, "Failed to register main BLE commands.\n");
   }
}

/**
   @brief Cleans up resources used by the BLE demo application.
*/
void Cleanup_BLE_Demo(void)
{
   if(BLE_Demo_Context.QCLI_Handle)
   {
      /* Un-register the BT Group. */
      Cleanup_BAS_Demo();

      if(BLE_Demo_Context.BluetoothStackID)
      {
         ShutDownBLEDemo();
      }

      QCLI_Unregister_Command_Group(BLE_Demo_Context.QCLI_Handle);

      BLE_Demo_Context.QCLI_Handle = NULL;
   }
}

/**
   @brief Converts the bluetooth address in QAPI format to string format.

   @param Board_Address is the BD address in QAPI format.
   @param BoardStr      is the converted BD address in string format.
*/
void BD_ADDRToStr(qapi_BLE_BD_ADDR_t Board_Address, BoardStr_t BoardStr)
{
   snprintf((char *)BoardStr, sizeof(BoardStr_t), "0x%02X%02X%02X%02X%02X%02X", Board_Address.BD_ADDR5,
                                                                                Board_Address.BD_ADDR4,
                                                                                Board_Address.BD_ADDR3,
                                                                                Board_Address.BD_ADDR2,
                                                                                Board_Address.BD_ADDR1,
                                                                                Board_Address.BD_ADDR0);
}

/**
   @brief Converts the bluetooth address in string format to QAPI format.

   @param BoardStr      is the BD address in string format.
   @param Board_Address is the converted BD address in QAPI format.
*/
void StrToBD_ADDR(char *BoardStr, qapi_BLE_BD_ADDR_t *Board_Address)
{
   char    Buffer[5];
   int32_t Result;

   if ((BoardStr) && (strlen(BoardStr) == sizeof(qapi_BLE_BD_ADDR_t)* 2) && (Board_Address))
   {
      Buffer[0] = '0';
      Buffer[1] = 'x';
      Buffer[4] = '\0';

      Buffer[2] = BoardStr[0];
      Buffer[3] = BoardStr[1];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR5 = (uint8_t)Result;

      Buffer[2] = BoardStr[2];
      Buffer[3] = BoardStr[3];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR4 = (uint8_t)Result;

      Buffer[2] = BoardStr[4];
      Buffer[3] = BoardStr[5];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR3 = (uint8_t)Result;

      Buffer[2] = BoardStr[6];
      Buffer[3] = BoardStr[7];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR2 = (uint8_t)Result;

      Buffer[2] = BoardStr[8];
      Buffer[3] = BoardStr[9];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR1 = (uint8_t)Result;

      Buffer[2] = BoardStr[10];
      Buffer[3] = BoardStr[11];
      QCLI_String_To_Integer(Buffer, &Result);
      Board_Address->BD_ADDR0 = (uint8_t)Result;
   }
   else
   {
      if(Board_Address)
      {
         memset(Board_Address, 0, sizeof(qapi_BLE_BD_ADDR_t));
      }
   }
}

/**
   @brief Function to get the QCLI handle for the BLE demo.

   @return The QCLI handled used by the BLE demo.
*/
QCLI_Group_Handle_t GetBLEQCLIHandle(void)
{
   return(BLE_Demo_Context.QCLI_Handle);
}

/**
   @brief Function to get Bluetooth stack ID.

   @return Bluetooth stack ID.
*/
uint32_t GetBluetoothStackID(void)
{
   return(BLE_Demo_Context.BluetoothStackID);
}

/**
   @brief Function to get the ID of the current connection.

   @return The ID of the current connection.
*/
uint32_t GetActiveConnectionID(void)
{
   return(BLE_Demo_Context.ActiveConnectionID);
}

/**
   @brief Function to get the BDADDR of the currently connected device.

   @return The BDADDR of the currently connected device.
*/
qapi_BLE_BD_ADDR_t GetActiveConnectionBDADDR(void)
{
   return(BLE_Demo_Context.ActiveConnectionBD_ADDR);
}

/**
   @brief Function to get the device info by conncetion ID.

   @return The pointer to device info or NULL.
*/
Generic_Device_Info_t *GetDeviceInfoByConnectionID(uint32_t ConnectionID)
{
   Generic_Device_Info_t *Ret_Val;

   Ret_Val = SearchDeviceInfoEntryByConnectionID(&(BLE_Demo_Context.DeviceInfoList), ConnectionID);

   return(Ret_Val);
}

/**
   @brief Function to get the device info by BD_ADDR.

   @return The pointer to device info or NULL.
*/
Generic_Device_Info_t *GetDeviceInfoByBDADDR(qapi_BLE_BD_ADDR_t BDADDR)
{
   Generic_Device_Info_t *Ret_Val;

   Ret_Val = SearchDeviceInfoEntryByBD_ADDR(&(BLE_Demo_Context.DeviceInfoList), BDADDR);

   return(Ret_Val);
}

/**
   @brief Function to display the received UUID.

   @param QCLI_Handle is the QCLI handle

   @param UUID        is the UUID info
*/
void DisplayUUID(QCLI_Group_Handle_t QCLI_Handle, qapi_BLE_GATT_UUID_t *UUID)
{
   if((QCLI_Handle != NULL) && (UUID != NULL))
   {
      if(UUID->UUID_Type == QAPI_BLE_GU_UUID_16_E)
         QCLI_Printf(QCLI_Handle, "%02X%02X\n", UUID->UUID.UUID_16.UUID_Byte1, UUID->UUID.UUID_16.UUID_Byte0);
      else
      {
         if(UUID->UUID_Type == QAPI_BLE_GU_UUID_128_E)
         {
            QCLI_Printf(QCLI_Handle, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n", UUID->UUID.UUID_128.UUID_Byte15, UUID->UUID.UUID_128.UUID_Byte14, UUID->UUID.UUID_128.UUID_Byte13,
                                                                                                    UUID->UUID.UUID_128.UUID_Byte12, UUID->UUID.UUID_128.UUID_Byte11, UUID->UUID.UUID_128.UUID_Byte10,
                                                                                                    UUID->UUID.UUID_128.UUID_Byte9,  UUID->UUID.UUID_128.UUID_Byte8,  UUID->UUID.UUID_128.UUID_Byte7,
                                                                                                    UUID->UUID.UUID_128.UUID_Byte6,  UUID->UUID.UUID_128.UUID_Byte5,  UUID->UUID.UUID_128.UUID_Byte4,
                                                                                                    UUID->UUID.UUID_128.UUID_Byte3,  UUID->UUID.UUID_128.UUID_Byte2,  UUID->UUID.UUID_128.UUID_Byte1,
                                                                                                    UUID->UUID.UUID_128.UUID_Byte0);
            QCLI_Printf(QCLI_Handle, "\r\n");
         }
      }
   }
}

