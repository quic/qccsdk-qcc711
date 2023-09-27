/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __BAS_DEMO_H__
#define __BAS_DEMO_H__

#include "qcli_api.h"
#include "qapi_ble_gatt.h"

/**
   @brief Initializes the BAS demo application.

   @param[in] BLE_QCLI_Handle is the parent QCLI handle for the BAS demo.
*/
qbool_t Initialize_BAS_Demo(QCLI_Group_Handle_t BLE_QCLI_Handle);

/**
   @brief Cleans up the BAS demo application.
*/
void Cleanup_BAS_Demo(void);

/**
   @brief Frees any resources allocated that aren't valid when stack is shutdown
          without shutting down the QCLI interface for the BAS demo.
*/
void Shutdown_BAS_Demo(void);

/**
   @brief Handle the bas notification event.

   @param[in] GATT_Server_Notification_Data is the notitication data.
*/
void Handle_BAS_Notification(qapi_BLE_GATT_Server_Notification_Data_t *GATT_Server_Notification_Data);

#endif

