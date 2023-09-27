/*
* Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/
/*****< qapi_ble_errors.h >****************************************************/
/*      Copyright 2015 - 2016 Qualcomm Technologies, Inc.                     */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  qapi_ble_errors - QAPI BLE Bluetooth Protocol Stack Error Codes.          */
/*                                                                            */
/*  Author:  Tim Cook                                                         */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   08/28/15  T. Cook        Initial creation.                               */
/******************************************************************************/
#ifndef __QAPI_BLE_ERRORS_H__
#define __QAPI_BLE_ERRORS_H__

#define QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER                             (-1)
#define QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID                    (-2)
#define QAPI_BLE_BTPS_ERROR_STACK_INITIALIZATION_ERROR                    (-3)
#define QAPI_BLE_BTPS_ERROR_HCI_INITIALIZATION_ERROR                      (-4)
#define QAPI_BLE_BTPS_ERROR_GAP_INITIALIZATION_ERROR                      (-5)
#define QAPI_BLE_BTPS_ERROR_L2CAP_INITIALIZATION_ERROR                    (-7)
#define QAPI_BLE_BTPS_ERROR_DEBUG_CALLBACK_ALREADY_INSTALLED             (-13)
#define QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR                             (-14)
#define QAPI_BLE_BTPS_ERROR_DEVICE_RESET_ERROR                           (-15)
#define QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR                           (-16)
#define QAPI_BLE_BTPS_ERROR_HCI_TIMEOUT_ERROR                            (-17)
#define QAPI_BLE_BTPS_ERROR_UNSUPPORTED_HCI_VERSION                      (-18)
#define QAPI_BLE_BTPS_ERROR_UNKNOWN_HCI_BUFFER_SIZE                      (-20)
#define QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_EVENT_CALLBACK            (-21)
#define QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_ACL_CALLBACK              (-22)
#define QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED                        (-26)
#define QAPI_BLE_BTPS_ERROR_ADDING_IDENTIFIER_INFORMATION                (-35)
#define QAPI_BLE_BTPS_ERROR_INVALID_CONNECTION_STATE                     (-36)
#define QAPI_BLE_BTPS_ERROR_CHANNEL_NOT_IN_OPEN_STATE                    (-37)
#define QAPI_BLE_BTPS_ERROR_INVALID_CID                                  (-38)
#define QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR                      (-40)
#define QAPI_BLE_BTPS_ERROR_NEGOTIATED_MTU_EXCEEDED                      (-41)
#define QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED                          (-56)
#define QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR                             (-57)
#define QAPI_BLE_BTPS_ERROR_ADDING_CALLBACK_INFORMATION                  (-59)
#define QAPI_BLE_BTPS_ERROR_DELETING_CALLBACK_INFORMATION                (-60)
#define QAPI_BLE_BTPS_ERROR_NO_CALLBACK_REGISTERED                       (-61)
#define QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR                               (-64)
#define QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                    (-65)
#define QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES                       (-66)
#define QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED                         (-98)
#define QAPI_BLE_BTPS_ERROR_ACTION_NOT_ALLOWED                           (-99)
#define QAPI_BLE_BTPS_ERROR_VS_HCI_ERROR                                 (-101)
#define QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE                        (-103)
#define QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE         (-104)
#define QAPI_BLE_BTPS_ERROR_SCAN_ACTIVE                                  (-105)
#define QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE                     (-107)
#define QAPI_BLE_BTPS_ERROR_DEVICE_IS_SLAVE                              (-108)
#define QAPI_BLE_BTPS_ERROR_READ_REMOTE_FEATURES_OUTSTANDING             (-110)
#define QAPI_BLE_BTPS_ERROR_CREATE_CONNECTION_OUTSTANDING                (-111)
#define QAPI_BLE_BTPS_ERROR_INVALID_CONNECTION_PARAMETERS                (-112)
#define QAPI_BLE_BTPS_ERROR_RANDOM_ADDRESS_IN_USE                        (-116)
#define QAPI_BLE_BTPS_ERROR_PAIRING_ACTIVE                               (-117)
#define QAPI_BLE_BTPS_ERROR_PAIRING_NOT_ACTIVE                           (-118)
#define QAPI_BLE_BTPS_ERROR_INVALID_STATE                                (-119)
#define QAPI_BLE_BTPS_ERROR_FEATURE_NOT_CURRENTLY_ACTIVE                 (-120)
#define QAPI_BLE_BTPS_ERROR_CONNECTION_UPDATE_PROCEDURE_OUTSTANDING      (-121)
#define QAPI_BLE_BTPS_ERROR_RESOLVING_LIST_IN_USE                        (-122)
#define QAPI_BLE_BTPS_ERROR_SECURE_CONNECTIONS_NOT_SUPPORTED             (-123)

   /* The following defines the start of the HCI Status Code Error Base.*/
   /* Errors between (-500) -> (-755) are errors returned due to a Error*/
   /* Code between returned by the Bluetooth Controller.                */
#define QAPI_BLE_BTPS_ERROR_CODE_HCI_STATUS_BASE                         (-500)

   /* The following MACRO is a utility MACRO that provides a mechanism  */
   /* for the return value in the range -500->-755 to be converted to an*/
   /* HCI Controller Status Code.  This MACRO accepts as it's only      */
   /* parameter the HCI Error Code to convert and returns the HCI Status*/
   /* Code.                                                             */
#define QAPI_BLE_CONVERT_ERROR_CODE_TO_HCI_STATUS_CODE(_x)               ((uint8_t)(-((_x) - QAPI_BLE_BTPS_ERROR_CODE_HCI_STATUS_BASE)))

#endif
