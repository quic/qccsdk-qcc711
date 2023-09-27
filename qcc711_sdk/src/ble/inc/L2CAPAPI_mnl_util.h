/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __L2CAPAPIMNLUTILH__
#define __L2CAPAPIMNLUTILH__

/* Even unsigned int IDs in the stack never use the top bit, since they are returned as signed from
 * the APIs. We can use the bit to identify the type of ID. */
#define L2CAP_CALLBACK_KEY_TYPE_MASK    (0x80000000)
#define L2CAP_CALLBACK_KEY_KEY_MASK     (~L2CAP_CALLBACK_KEY_TYPE_MASK)
#define L2CAP_CALLBACK_KEY_TYPE_PSMID   (0x80000000)
#define L2CAP_CALLBACK_KEY_TYPE_CID     (0x00000000)

#endif /* __L2CAPAPIMNLUTILH__ */
