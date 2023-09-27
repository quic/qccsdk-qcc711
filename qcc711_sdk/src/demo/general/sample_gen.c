/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qcli_pal.h"

#include "qapi_ble_hcitypes.h"
#include "ble_demo.h"
#include "mfg_demo.h"
#include "plat_demo.h"
#include "rot_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

static qapi_BLE_HCI_DriverInformation_t HCI_DriverInformation;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializing the individual sample applications.
*/
void Initialize_Samples(void)
{
   QAPI_BLE_HCI_DRIVER_SET_COMM_INFORMATION(&HCI_DriverInformation, 0, 0, QAPI_BLE_COMM_PROTOCOL_UART_E);
   Initialize_BLE_Demo(&HCI_DriverInformation);
   Initialize_Plat_Demo();
   Initialize_RoT_Demo();
}

/**
   @brief Cleanup the individual sample applications before exitting.
*/
void Cleanup_Samples(void)
{
   Cleanup_BLE_Demo();
   Cleanup_Plat_Demo();
   Cleanup_RoT_Demo();
}