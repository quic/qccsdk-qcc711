/*=============================================================================

            TME COM Client Porting layer for OS specifc APIs.


   Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Qualcomm Technologies, Inc. Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "ram.h"
#include "Tmecom.h"
#include "qapi_nvm.h"
#include "hwio_ram.h"
#include "hwio_aon.h"
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_power.h"
#include "qapi_timer.h"
#include "qapi_status.h"

/*=============================================================================
                       GLOBAL DATA DECLARATIONS
=============================================================================*/
#define TME_STATE_ACTIVE    0x1

/*=============================================================================

                       FUNCTION DEFINITIONS

=============================================================================*/

/**
   @brief Set/remove dependancy on TME subsystem based on sessionStart value.
          If this API is called from sesion start then set dependancy on TME SS,
          and wait till TME SS is up.
          Else remove the dependancy on TME SS.

   @param[in] sessionStart Indicate whether this API is called from session start or
              session end.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomOsSetTmeState(bool sessionStart)
{
    TmecomResponse_t          result   = TMECOM_RSP_SUCCESS;
    volatile qapi_PWR_State_t tmeState = QAPI_PWR_STATE_SHUTDOWN_E;
    uint32_t rotState  = 0;
    uint64_t startTime = 0;
    uint64_t currTime  = 0;

    /* Based on sessionStart value determine whether to vote for ACTIVE or SHUTDOWN state of TME */
    tmeState = (sessionStart ? QAPI_PWR_STATE_ACTIVE_E : QAPI_PWR_STATE_SHUTDOWN_E);

    /* Set TME state, QAPI will vote/unvote on TME as per tmeState value */
    CHECK_COND_ERR((QAPI_OK != qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_ROT_E, (qapi_PWR_State_t)tmeState)),
            TMECOM_RSP_FAILURE, "qapi_PWR_Set_Module_State failed!");

    /* If it's start of an IPC session, make sure TME is in powered on state,
       Poll either till TME ROT operative bit is set or until timeout occurrs */
    if(sessionStart) {
        CALL_N_CHECK(TmecomOsGetTime(&startTime));
        /* Wait till TME is powered ON */
        do {
            CALL_N_CHECK(TmecomOsGetTime(&currTime));
            if(gIpcWaitTimeout) {
                /* Check for timeout */
                CHECK_COND_ERR(((currTime - startTime) >= gIpcWaitTimeout),
                        TMECOM_RSP_FAILURE_TME_PWR_STATE_TIMEOUT,
                        "Timeout occurred");
            }
            /* Get TME's power state */
            tmeState = qapi_PWR_Get_Module_State(QAPI_PWR_MODULE_ROT_E);
        }while(QAPI_PWR_STATE_ACTIVE_E != tmeState);

        /* Wait for ROT operative bit to get set */
        CALL_N_CHECK(TmecomOsGetTime(&startTime));
        do {
            CALL_N_CHECK(TmecomOsGetTime(&currTime));
            if(gIpcWaitTimeout) {
                /* Check for timeout */
                CHECK_COND_ERR(((currTime - startTime) >= gIpcWaitTimeout),
                        TMECOM_RSP_FAILURE_TME_BOOT_STATE_TIMEOUT,
                        "Timeout occurred");
            }
            /* Get current ROT OERATIVE state from AON_PME_APPS_STATUS register */
            rotState = (HWIO_AON_PME_APPS_STATUS_INM(HWIO_AON_PME_APPS_STATUS_ROT_OPERATIVE_BMSK)
                        >> HWIO_AON_PME_APPS_STATUS_ROT_OPERATIVE_SHFT);
        }while(TME_STATE_ACTIVE != rotState);
    }
exit:
    return result;
}

/**
   @brief API to allocate memory using OS specific APIs.

   @param[out] memAddr Pointer to the allocated memory.
   @param[in]  size    Size of memory block in bytes.

   @return TMECOM_RSP_SUCCESS - if memory allocated successfully, error otherwise.
 */
TmecomResponse_t TmecomOsMemAlloc(void **memAddr, size_t size)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    CHECK_PTR(memAddr);
    CHECK_SIZE(size);

    *memAddr = qapi_Malloc(size);
    CHECK_COND_ERR((NULL == *memAddr), TMECOM_RSP_FAILURE, "OS malloc failed");

exit:
    return result;
}

/**
   @brief API to free previously allocated memory using OS specific APIs.

   @param[in] memAddr Pointer to the allocated memory.

   @return TMECOM_RSP_SUCCESS - if memory de-allocated successfully, error otherwise.
 */
TmecomResponse_t TmecomOsMemFree(void **memAddr)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    CHECK_PTR(*memAddr);
    qapi_Free(*memAddr);
    *memAddr = NULL;

exit:
    return result;
}

/**
   @brief Shares RAM address block with TME subsystem using OS specific APIs.

   @param[in] addrList     List of SRAM addresses to be shared with TME.
   @param[in] listSize     No. of entries in the addrList array.
   @param[in] perm         Permissions the TME will have to the shared memory.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomOsShareMemoryWithTme(TmecomSramBuf_t *addrList,
                                            size_t listSize,
                                            TmecomMemPerm_t perm)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    RAM_Permission_t ramPerm = RAM_PERM_NO_ACCESS_E;
    qbool_t nvmShare = false;
    uint32_t ramBlocks = 0;
    uint32_t nvmBlocks = 0;
    uint32_t nvmRet = 0;

    CHECK_PTR(addrList);
    CHECK_SIZE(listSize);

    /* Map TMECOM permissions to OS specific mem permissions */
    switch(perm) {
        case TMECOM_MEM_PERM_NO_ACCESS:
            ramPerm = RAM_PERM_NO_ACCESS_E;
            nvmShare = false;
            break;
        case TMECOM_MEM_PERM_READ_ONLY:
            ramPerm = RAM_PERM_READ_ONLY_E;
            nvmShare = true;
            break;
        case TMECOM_MEM_PERM_READ_WRITE:
            ramPerm = RAM_PERM_READ_WRITE_E;
            break;
        default:
            CHECK_COND_ERR(true, TMECOM_RSP_FAILURE_INVALID_ARGS, "Invalid perm");
    }

    /* Get block bitmask for all addresses */
    for(size_t i=0; i<listSize; i++)
    {
        /* If addresses are invalid or not respective ranges then below APIs return 0 */
        ramBlocks |= RAM_AddressRangeToBlocks((const void *)addrList[i].addr, (const void *)(addrList[i].addr + addrList[i].size));
        nvmBlocks |= qapi_NVM_Address_Range_To_Blocks((const void *)addrList[i].addr, (const void *)(addrList[i].addr + addrList[i].size));
    }

    if(ramBlocks)
    {
        /* Share RAM buffers with TME */
        CHECK_COND_ERR((QAPI_OK != RAM_Share(RAM_SUBSYSTEM_ROT_E, ramBlocks, ramPerm)),
                TMECOM_RSP_FAILURE, "RAM_Share API failed");
    }
    if(nvmBlocks)
    {
        /* Share NVM buffers with TME; qapi_NVM_Share() will provide rad-only access to TME */
        nvmRet = qapi_NVM_Share(nvmBlocks, QAPI_NVM_SUBSYSTEM_ROT_E, nvmShare);
        CHECK_COND_ERR((nvmBlocks != nvmRet), TMECOM_RSP_FAILURE, "NVM_Share QAPI failed");
    }
exit:
    return result;
}

/**
   @brief API to get current timer value using OS specific APIs.

   @param[out] time  Current timer value in microseconds.

   @return TMECOM_RSP_SUCCESS - if timer value is read successfully, error otherwise.
 */
TmecomResponse_t TmecomOsGetTime(uint64_t *time)
{
    *time = 0;

    *time = qapi_TMR_Get_Current_Time();

    return (*time ? TMECOM_RSP_SUCCESS : TMECOM_RSP_FAILURE);
}

/**
   @brief API to initialize OS specific lock context.

   @param[out] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock context iniitialized successfully, error otherwise.
 */
TmecomResponse_t TmecomOsLockInit(TmecomLock_t tmecomLock)
{
    /* Not required currently for this OS, implement if needed */
    return TMECOM_RSP_SUCCESS;
}

/**
   @brief API to try acquire OS specific Tmecom lock, if lock is already
          in acquired state then return TMECOM_RSP_FAILURE_BUSY error.

   @param[in] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock acquired successfully, TMECOM_RSP_FAILURE_BUSY otherwise.
 */
TmecomResponse_t TmecomOsTryLock(TmecomLock_t tmecomLock)
{
    /* Interrupt lock mechanism is used to implement lock-
       - Disable all interrupts before entering critical section
       - Execute critical section
       - Enable back all interrupts */

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    /* Disable all interrupts */
    qapi_TSK_Enter_Critical();

    /* Critical section :
       - Read lock variable
       - If it's already acquired return a busy error
       - If it's in free state then set the lock variable to acquired state
         and return success */
    CHECK_COND_ERR((*(volatile uint32_t *)tmecomLock == TMECOM_LOCK_ACQUIRED),
                     TMECOM_RSP_FAILURE_BUSY, "Lock is already acquired");

    *(volatile uint32_t *)tmecomLock = TMECOM_LOCK_ACQUIRED;
exit:
    /* Enable interrupts */
    qapi_TSK_Exit_Critical();
    return result;
}

/**
   @brief API to unlock the OS specific Tmecom Lock.

   @param[in] tmecomLock OS specific lock context

   @return TMECOM_RSP_SUCCESS - if lock released successfully, error otherwise.
 */
TmecomResponse_t TmecomOsFreeLock(TmecomLock_t tmecomLock)
{
    /* Interrupt lock mechanism is used to implement lock-
       - Disable all interrupts before entering critical section
       - Execute critical section
       - Enable back all interrupts */

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    /* Disable all interrupts */
    qapi_TSK_Enter_Critical();

    /* Critical section :
       - Set the lock variable to free state*/
    *(volatile uint32_t *)tmecomLock = TMECOM_LOCK_FREE;

    /* Enable interrupts */
    qapi_TSK_Exit_Critical();

    return result;
}

/**
   @brief API to destroy OS specific Lock context which was intialized using TmecomOsLockInit().

   @param[out] tmecomLock OS specific lock context returned by TmecomOsLockInit().

   @return TMECOM_RSP_SUCCESS - if Lock context destroyed successfully, error otherwise.
 */
TmecomResponse_t TmecomOsLockDestroy(TmecomLock_t tmecomLock)
{
    return TMECOM_RSP_SUCCESS;
}

/**
   @brief API to check if OS specific Tmecom lock is already taken or not.

   @return TMECOM_RSP_SUCCESS if Tmecom lock is in free state.
           TMECOM_RSP_FAILURE_BUSY if Tmecom lock is already acquired.
*/
TmecomResponse_t TmecomOsIsLockFree(TmecomLock_t tmecomLock)
{
    /* Interrupt lock mechanism is used to implement lock-
       - Disable all interrupts before entering critical section
       - Execute critical section
       - Enable back all interrupts */

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    /* Disable all interrupts */
    qapi_TSK_Enter_Critical();

    /* Critical section :
       - Read lock variable
       - If it's already acquired return a busy error */
    CHECK_COND_ERR((*(volatile uint32_t *)tmecomLock == TMECOM_LOCK_ACQUIRED),
                     TMECOM_RSP_FAILURE_BUSY, "Lock is already acquired");

exit:
    /* Enable interrupts */
    qapi_TSK_Exit_Critical();

    return result;
}

