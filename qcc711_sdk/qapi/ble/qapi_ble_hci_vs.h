
/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_hci_vs.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack HCI API Type
 * Definitions, Constants, and Prototypes.
 *
 * @details
 * The Host Controller Interface (HCI) layer API of the Bluetooth
 * Protocol Stack provides software  access to the HCI command
 * interface to the baseband controller and link manager.  This
 * allows access to hardware status and control registers.  This
 * API provides a uniform method of accessing the Bluetooth baseband
 * capabilities.
 */

#ifndef __QAPI_BLE_HCI_VS_H__
#define __QAPI_BLE_HCI_VS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_hcitypes.h"  /* Bluetooth HCI Type Definitions/Constants.*/
#include "./qapi_ble_hci_vstypes.h"  /* Bluetooth HCI VS Type Definitions/Constants.*/

/** @addtogroup qapi_ble_core_hci
@{ */

/**
 * @brief
 * Stops the current test.
 *
 * @details
 * Issues the
 * HCI_VS_PROD_TEST_COMMAND PROD_TEST_STOP
 * Command to the Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack using a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                 If the function returns zero
 *                                           (success), this variable 
 *                                           contains the Status Result returned
 *                                           from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_Stop(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Forces the radio to transmit Bluetooth LE packets continuously
 * on the specified channel.
 *
 * @details
 * Issues the
 * HCI_VS_PROD_TEST_COMMAND_PROD_TEST_LE_TX_CONTINUOUS
 * Command to the Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device, or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack using a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Channel_Index                Device transmit channel number.
 *
 * @param[in]   Transmit_Output_Power        Transmit output power.
 *
 * @param[in]   Transmit_Type                Transmit Type.
 *
 * @param[in]   Packet_Length                Specifies length of repeated
 *                                           pattern.
 *
 * @param[in]   Bit_Pattern                  Bit pattern transmitted repeatedly
 *                                           (4 octets).
 *
 * @param[out]  StatusResult                 If the function returns zero
 *                                           (success) this variable will
 *                                           contain the Status Result returned
 *                                           from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Continuous(uint32_t BluetoothStackID, uint8_t Channel_Index, uint8_t Transmit_Output_Power, uint8_t Transmit_Type, uint8_t Packet_Length, uint32_t Bit_Pattern, uint8_t *StatusResult);

/**
 * @brief
 * Transmits Bluetooth LE and QHS packets while bursting, without being in a connection
 * with another device.
 *
 * @details
 * Issues the
 * HCI_VS_PROD_TEST_COMMAND_PROD_TEST_LE_TX_BURST
 * Command to the Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Hop_Channels                 Hopping mode.
 *
 * @param[in]   Payload_Length               Length of payload.
 *
 * @param[in]   Payload_Type                 Payload Type.
 *
 * @param[in]   Packet_Type                  Packet type.
 *
 * @param[in]   Transmit_Output_Power        Transmit output power.
 *
 * @param[out]  StatusResult                 If the function returns zero
 *                                           (success), this variable 
 *                                           contains the Status Result returned
 *                                           from the Bluetooth device.
 *
 * @param[out]  SubOpCode                    If the function returns zero
 *                                           (success), this variable
 *                                           contains the sub op code returned
 *                                           from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Burst(uint32_t BluetoothStackID, uint8_t Hop_Channels, uint16_t Payload_Length, uint8_t Payload_Type, uint8_t Packet_Type, uint8_t Transmit_Output_Power, uint8_t *StatusResult, uint8_t *SubOpCode);

/** @} */ /* end_addtogroup qapi_ble_core_hci */

#endif


