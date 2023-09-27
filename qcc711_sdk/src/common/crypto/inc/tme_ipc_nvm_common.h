/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

#ifndef TME_IPC_NVM_COMMON_H__
#define TME_IPC_NVM_COMMON_H__

/** Structure representing the NVM write ROT request. */
typedef struct qapi_NVM_Write_Rot_Params_s
{
   uint32_t    Offset;     /**< Offset location to perform write operation. */
   const void  *Buffer;    /**< Data to write to ROT NVM. */
   uint32_t    BufferLen;  /**< Length of the data to write to NVM. */
} qapi_NVM_Write_Rot_Params_t;

/** Structure representing the NVM read ROT request. */
typedef struct qapi_NVM_Read_Rot_Params_s
{
   uint32_t  Offset;     /**< Offset location to perform read operation. */
   void     *Buffer;     /**< Buffer to store data. */
   uint32_t  BufferLen;  /**< Length of the data to read from ROT NVM. */
} qapi_NVM_Read_Rot_Params_t;

#endif //TME_IPC_NVM_COMMON_H__