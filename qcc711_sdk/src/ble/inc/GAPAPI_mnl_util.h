/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GAPAPIMNLUTILH__
#define __GAPAPIMNLUTILH__

#include "qapi_ble_gap.h"

   /* The following define valid return status' from the                */
   /* APSS_Buffer_Allow_Access_For_BTSS function.                       */
#define GAP_ERROR_BUFFER_STATUS_OK                       0
#define GAP_ERROR_BUFFER_STATUS_INVALID_PARAMETER       (QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER)
#define GAP_ERROR_BUFFER_STATUS_IGNORE_RETURN_SUCCESS   -2
#define GAP_ERROR_BUFFER_STATUS_INVALID_OPERATION       (QAPI_BLE_BTPS_ERROR_ACTION_NOT_ALLOWED)
#define GAP_ERROR_BUFFER_STATUS_UNKNOWN_ERROR           (QAPI_BLE_BTPS_ERROR_INTERNAL_ERROR)

unsigned int CountAdvertisingDataRecords(unsigned int Advertising_Data_Length, uint8_t *Advertising_Data);
unsigned int ParseAdvertisingData(unsigned int Advertising_Data_Length, uint8_t *Advertising_Data, qapi_BLE_GAP_LE_Advertising_Data_t *ParsedData);

   /* These functions a integrated with the APSS buffer management for  */
   /* ESL use case and thus are here.                                   */
void ESLD_Write_Request_Event_Received(void);
void ESLD_Write_Stopped_Event_Received(void);

   /* This function enables access for BTSS to read/write the specified */
   /* buffer of the specified length.  If NonObjectWriteCall is TRUE    */
   /* then this buffer is not involved in an ESL object write operation */
   /* and the APSS_Buffer_Revoke_Access_From_BTSS() API must be called  */
   /* to revoke access to the memory when BTSS no longer needs access to*/
   /* the memory.                                                       */
int APSS_Buffer_Allow_Access_For_BTSS(uint32_t Buffer_Length, uint8_t *Buffer, boolean_t NonObjectWriteCall);

   /* This function is called to revoke BTSS access to the specified    */
   /* buffer.  This should never be called for a buffer used in an ESL  */
   /* Buffer Write (those are cleaned up when the object write operation*/
   /* is complete).                                                     */
void APSS_Buffer_Revoke_Access_From_BTSS(uint32_t Buffer_Length, uint8_t *Buffer);

#endif /* __GAPAPIMNLUTILH__ */
