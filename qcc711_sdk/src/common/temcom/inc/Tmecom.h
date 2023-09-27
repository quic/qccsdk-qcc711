/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef TME_COM_H
#define TME_COM_H

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stdint.h>
#include "TmecomClient.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/* TODO-ZIGGY: Add proper log APIs here*/
#define TMECOM_LOG_ERR(fmt, ...)
#define TMECOM_LOG_INFO(fmt, ...)

/* Error checking helper macros */
#define ERROR(...)  {                             \
        TMECOM_LOG_ERR(__VA_ARGS__)                \
        goto exit;                                 \
    }

#define CHECK_COND_ERR(cond, errorCode, ...)  {   \
        if (cond) {                                \
            result = errorCode;                    \
            ERROR(__VA_ARGS__);                    \
        }                                          \
    }

#define CHECK_RET(rv, errorCode, ...)  {          \
        if (rv != TMECOM_RSP_SUCCESS) {            \
            result = errorCode;                    \
            ERROR(__VA_ARGS__);                    \
        }                                          \
    }

#define CALL_N_CHECK(func, ...)  {                \
        result = func;                             \
        if (result != TMECOM_RSP_SUCCESS) {        \
            ERROR(__VA_ARGS__);                    \
        }                                          \
    }

//#define DISABLE_TIMEOUT_LOGIC  /* Define this to disable timeout logic */
/* TODO: NOP added while waiting in loop as a workaround for bug in NVM, remove once NVM bug is fixed
         Bug id -  https://qti-jira.qualcomm.com/jira/browse/ZIGGY-640 */
#ifndef DISABLE_TIMEOUT_LOGIC
#define WAIT_ON_CONDITION_TILL_TIMEOUT(cond, timeout, errCode) {       \
        CALL_N_CHECK(TmecomOsGetTime(&startTime));                     \
        do {                                                           \
            if(timeout) {                                              \
            CALL_N_CHECK(TmecomOsGetTime(&currTime));                  \
            /* Check for timeout */                                    \
            CHECK_COND_ERR(((currTime - startTime) >= (timeout)),      \
                            errCode, "Timeout occurred");              \
             }                                                         \
             __asm volatile ("nop");                                   \
         }while (cond);                                                \
    }
#else
#define WAIT_ON_CONDITION_TILL_TIMEOUT(cond, timeout, errCode) {       \
        do {                                                           \
             __asm volatile ("nop");                                   \
         }while (cond);                                                \
    }
#endif

#define CHECK_PTR(ptr)                        \
CHECK_COND_ERR((NULL == ptr), TMECOM_RSP_FAILURE_BAD_ADDR, "NULL Address")

#define CHECK_SIZE(size)                      \
CHECK_COND_ERR(((size) <= 0), TMECOM_RSP_FAILURE_INVALID_ARGS, "Invalid size")

#define TMECOM_UNUSED(x)    (void)(x)

#define TMECOM_4_BYTE_ALIGNED 4
#define IS_ALIGNED(type, x, d) (0 == ((type)(x)&(type)((d)-1)))

#define CHECK_ALIGNMENT(type, value, alignSize)                      \
    CHECK_COND_ERR((!IS_ALIGNED(type, value, alignSize)),            \
            TMECOM_RSP_FAILURE_INVALID_ARGS, "Address is not aligned, addr:%x", (value))

#define ALIGN_UP(type, value, align) (((type)(value)+(type)(align-1)) & ~((type)(align-1)))

/* Stores OS specific Tmecom Lock context */
#define TmecomLock_t volatile void *
/* Lock in acquired state  */
#define TMECOM_LOCK_ACQUIRED 1
/* lock in free state  */
#define TMECOM_LOCK_FREE 0

/* MBOX related macros */
#define TMECOM_HW_MBOX_SIZE 32
#define TMECOM_MBOX_QMP_CONTROL_DATA_SIZE 8
#define TMECOM_MBOX_IPC_PACKET_SIZE (TMECOM_HW_MBOX_SIZE - TMECOM_MBOX_QMP_CONTROL_DATA_SIZE)
#define TMECOM_MBOX_IPC_MAX_PARAMS  5

/*----------------------------------------------------------------------------
 * 32bit ParamID consists of paramCount(4b) and paramType(2b) for each params.
 * Max 14 params can be described using 32b paramID.
 * -------------------------------------------------------------------------*/
#define TMECOM_MAX_PARAM_IN_PARAM_ID   14

#define TMECOM_PARAM_CNT_FOR_PARAM_TYPE_OUTBUF  3 /* bufAddr, bufLen, bufOutLen */

/*----------------------------------------------------------------------------
 * In worst case when all 14 params are of type TME_MSG_PARAM_TYPE_BUF_OUT or
 * TME_MSG_PARAM_TYPE_BUF_IN_OUT, then total params will be 42(14*3)
 * -------------------------------------------------------------------------*/
#define TMECOM_SRAM_IPC_MAX_PARAMS  (TMECOM_MAX_PARAM_IN_PARAM_ID) * (TMECOM_PARAM_CNT_FOR_PARAM_TYPE_OUTBUF) /* 14*3*/

#define TMECOM_SRAM_IPC_MAX_BUF_SIZE (TMECOM_SRAM_IPC_MAX_PARAMS * sizeof(uint32_t))

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
/* default max time (microseconds) TMECOM should wait for response from TME */
extern uint32_t gIpcWaitTimeout;

/*----------------------------------------------------------------------------
 * Memory permission types
 * -------------------------------------------------------------------------*/
typedef enum {
    TMECOM_MEM_PERM_NO_ACCESS,
    TMECOM_MEM_PERM_READ_ONLY,
    TMECOM_MEM_PERM_READ_WRITE,
} TmecomMemPerm_t;

/*----------------------------------------------------------------------------
 * SRAM buffer
 * -------------------------------------------------------------------------*/
typedef struct {
    uint8_t *addr;
    size_t size;
} TmecomSramBuf_t;

/*
                    QMP HW Mailbox Byte layout(32B)
     _________________________________________________________
    |                    |                |                   |
    |   31---------12    |  11--------8   |   7---------0     |
    |   Payload  Data    |   IPC Header   |  QMP Ctrl Data    |
    |____________________|________________|___________________|

*/

/*
               IPC Header Bit Layout(32 Bits)
      __________________________________________________
     |         |        |         |          |          |
     |  31--24  |  23--16  |  15--8  |  7--1  |    0    |
     | response | actionId | msgType | msgLen | ipcType |
     |__________|__________|_________|________|_________|

*/

/*----------------------------------------------------------------------------
 * IPC Types
 * -------------------------------------------------------------------------*/
typedef enum {
    TMECOM_IPC_TYPE_MBOX_ONLY = 0, /* genericPayload is part of mailbox */
    TMECOM_IPC_TYPE_MBOX_SRAM = 1, /* genericPayload is placed in SRAM */
} TmecomIpc_t;

/*----------------------------------------------------------------------------
 * Message Header structure to uniquely identify service API and get response
 * for requested service.
 * -------------------------------------------------------------------------*/
typedef struct {
    uint8_t ipcType : 1; /* 0:TMECOM_IPC_TYPE_MBOX_ONLY, 1:TMECOM_IPC_TYPE_MBOX_SRAM */
    uint8_t msgLen : 7;  /* message length being copied into mailbox. */
    uint8_t msgType;     /* or command id. */
    uint8_t actionId;    /* or subcommand id. */
    int8_t  response;    /* TME FW Transport layer return value(Success/Failure) */
} TmecomIpcHeader_t;

/*----------------------------------------------------------------------------
 * IPC Payload is part of mailbox.
 * -------------------------------------------------------------------------*/
typedef struct {
    uint32_t param[TMECOM_MBOX_IPC_MAX_PARAMS]; /* Max 5 params can be sent as payload */
} TmecomMboxOnlyPayload_t;

/*----------------------------------------------------------------------------
 * IPC Payload is shared via SRAM buffers.
 * -------------------------------------------------------------------------*/
typedef struct {
    void *payloadPtr;  /* SRAM address holding payload data */
    size_t payloadLen; /* Length of Palyload data */
} TmecomMboxSramPayload_t;

/*----------------------------------------------------------------------------
 * IPC Payload data.
 * -------------------------------------------------------------------------*/
typedef union {
    TmecomMboxOnlyPayload_t    mailboxPayload;  /* for TMECOM_IPC_TYPE_MBOX_ONLY */
    TmecomMboxSramPayload_t    sramPayload;     /* for TMECOM_IPC_TYPE_MBOX_SRAM */
} TmecomMboxIpcPayload_t;

/*----------------------------------------------------------------------------
 * IPC outbound/inbound message structure.
 * -------------------------------------------------------------------------*/
typedef struct {
    TmecomIpcHeader_t      msgHdr;         /* Message header */
    TmecomMboxIpcPayload_t payload;        /* Parameters passed to TME */
} TmecomMboxIpcPkt_t;

/*----------------------------------------------------------------------------
 * This have the record of the remote and Local subsystem.
 * -------------------------------------------------------------------------*/
typedef struct {
    const char *remote;  /* Remote SS name */
    const char *channel; /* Local SS name */
} TmecomGlinkCfg_t;

/*=============================================================================

                     PUBLIC FUNCTION DEFINITIONS

=============================================================================*/
/**
   @brief API to get client config data.

   @return A pointer to local subsytem specific config structure.
 */
const TmecomGlinkCfg_t* TmecomGetClientCfg(void);

/**
   @brief API to allocate memory using OS specific APIs.

   @param[out] memAddr Pointer to the allocated memory.
   @param[in]  size    Size of memory block in bytes.

   @return TMECOM_RSP_SUCCESS - if memory allocated successfully, error otherwise.
 */
TmecomResponse_t TmecomOsMemAlloc(void **memAddr, size_t size);

/**
 * @brief API to free previously allocated memory using OS specific APIs.
 *
 * @param[in, out] memAddr Pointer to the allocated memory which
 *                         will be set to NULL after free.
 *
 * @return TMECOM_RSP_SUCCESS - if memory de-allocated successfully, error
 * otherwise.
 */
TmecomResponse_t TmecomOsMemFree(void **memAddr);

/**
   @brief API to initialize OS specific lock context.

   @param[out] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock context iniitialized successfully, error otherwise.
 */
TmecomResponse_t TmecomOsLockInit(TmecomLock_t tmecomLock);

/**
   @brief API to try acquire OS specific Tmecom lock, if lock is already
          in acquired state then return TMECOM_RSP_FAILURE_BUSY error.

   @param[in] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock acquired successfully, TMECOM_RSP_FAILURE_BUSY otherwise.
 */
TmecomResponse_t TmecomOsTryLock(TmecomLock_t tmecomLock);

/**
   @brief API to unlock the OS specific Tmecom Lock.

   @param[in] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock released successfully, error otherwise.
 */
TmecomResponse_t TmecomOsFreeLock(TmecomLock_t tmecomLock);

/**
   @brief API to destroy OS specific Lock context which was intialized using TmecomOsLockInit().

   @param[out] tmecomLock OS specific lock context returned by TmecomOsLockInit().

   @return TMECOM_RSP_SUCCESS - if Lock context destroyed successfully, error otherwise.
 */
TmecomResponse_t TmecomOsLockDestroy(TmecomLock_t tmecomLock);

/**
   @brief API to get current timer value using OS specific APIs.

   @param[out] time  Current timer value in microseconds.

   @return TMECOM_RSP_SUCCESS - if timer value is read successfully, error otherwise.
 */
TmecomResponse_t TmecomOsGetTime(uint64_t *time);

/**
   @brief Set/remove dependancy on TME subsystem based on sessionStart value.
          If this API is called from sesion start then set dependancy on TME SS,
          and wait till TME SS is up.
          Else remove the dependancy on TME SS.

   @param[in] sessionStart Indicate whether this API is called from session start or
                           session end.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomOsSetTmeState(bool sessionStart);

/**
   @brief Shares RAM address block with TME subsystem using OS specific APIs.

   @param[in] addrList     List of SRAM addresses to be shared with TME.
   @param[in] listSize     No. of entries in the addrList array.
   @param[in] perm         Permissions the TME will have to the shared memory.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomOsShareMemoryWithTme(TmecomSramBuf_t *addrList,
                                            size_t listSize,
                                            TmecomMemPerm_t perm);

/**
   @brief API to check if OS specific Tmecom lock is already taken or not.

   @return TMECOM_RSP_SUCCESS if Tmecom lock is in free state.
           TMECOM_RSP_FAILURE_BUSY if Tmecom lock is already acquired.
*/
TmecomResponse_t TmecomOsIsLockFree(TmecomLock_t tmecomLock);

#endif /* TME_COM_H */
