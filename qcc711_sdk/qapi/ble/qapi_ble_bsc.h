/*
 * Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_bsc.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack Bluetooth Stack Controller
 * Profile API Type Definitions, Constants, and Prototypes.
 *
 * @details
 * The functions in this section are not defined in the
 * Bluetooth specification, but have been added to provide
 * some stack management and debugging aids.
 */

#ifndef __QAPI_BLE_BSC_H__
#define __QAPI_BLE_BSC_H__

#include "./qapi_ble_btapityp.h" /* Bluetooth API Type Definitions.           */
#include "./qapi_ble_bttypes.h"  /* Bluetooth Type Definitions/Constants.     */
#include "./qapi_ble_hcitypes.h" /* Bluetooth HCI Type Definitions/Constants. */

/** @addtogroup qapi_ble_core_bsc
@{ */

/** Bit flag passed to qapi_BLE_BSC_Initialize() that indicates that the L2CAP
    layer should not be initialized. */
#define QAPI_BLE_BSC_INITIALIZE_FLAG_NO_L2CAP                   0x00000001L

/** Bit flag passed to qapi_BLE_BSC_Initialize() that indicates that the GAP
    layer should not be initialized. */
#define QAPI_BLE_BSC_INITIALIZE_FLAG_NO_GAP                     0x00001000L

/**
   Enumeration of the types of fields that list returns may key off of.
*/
typedef enum
{
   QAPI_BLE_EK_NONE_E,
   /**< Indicates no key to key off of. */

   QAPI_BLE_EK_BOOLEAN_T_E,
   /**< Indicates that the key is a Boolean value. */

   QAPI_BLE_EK_BYTE_T_E,
   /**< Indicates that the key is a byte value. */

   QAPI_BLE_EK_WORD_T_E,
   /**< Indicates that the key is a word (2 byte) value. */

   QAPI_BLE_EK_DWORD_T_E,
   /**< Indicates that the key is a double word (4 byte) value. */

   QAPI_BLE_EK_BD_ADDR_T_E,
   /**< Indicates that the key is a Bluetooth address value. */

   QAPI_BLE_EK_ENTRY_POINTER_E,
   /**< Indicates that the key is a pointer value. */

   QAPI_BLE_EK_UNSIGNED_INTEGER_E
   /**< Indicates that the key is an unsigned integer value. */
} qapi_BLE_BSC_Generic_List_Entry_Key_t;

/** @cond */
/** Special value used for the TxPower field in qapi_BLE_BSC_SetTxPower()
    to revert back to the default value. */
#define QAPI_BLE_BSC_TX_POWER_REVERT_TO_DEFAULT                     (127)
/** @endcond */

/**
 * Holds the Bluetooth firmware version information that is queried from the
 * controller.
 */
typedef struct qapi_BLE_BSC_Version_Information_s
{
   uint32_t ROM_Version;    /**< Indicates the ROM version. */
   uint32_t Patch_Version;  /**< Indicates the patch version. */
   uint32_t Config_Version; /**< Indicates the configuration version. */
} qapi_BLE_BSC_Version_Information_t;

#define QAPI_BLE_BSC_VERSION_INFORMATION_SIZE               (sizeof(qapi_BLE_BSC_Version_Information_t))

/**
 * Holds the Bluetooth firmware statistics that are returned from 
 * qapi_BLE_BSC_QueryStatistics().
 */
typedef struct qapi_BLE_BSC_Statistics_s
{
   /** Indicates the ROM version.
     */
   uint32_t ROM_Version;

   /** Indicates the patch version.
     */
   uint32_t Patch_Version;

   /** Indicates the configuration version.
     */
   uint32_t Config_Version;

   /** Time (in milliseconds) that the BTSS has spent outside of deep sleep
    *  since initialization.
    */
   uint64_t ActiveTimeMs;

   /** Contains the total number of ACL bytes transmitted by the host stack.
    */
   uint64_t TxAclBytes;

   /** Contains the total number of packets transmitted by the radio.
    */
   uint16_t TxPackets;

   /** Contains the total number of ACL bytes received by the host stack.
    */
   uint64_t RxAclBytes;

   /** Contains the total number of packets received by the radio without
    *  any errors.
    */
   uint16_t RxPackets_NoError;

   /** Contains the total number of packets received by the radio that have a
    *  CRC error.
    */
   uint16_t RxPackets_CRCError;

   /** Contains the total number of packets received by the radio that have a
    *  MIC error.
    */
   uint16_t RxPackets_MICError;

   /** Contains the total number of radio scan operations that have timed out
    *  (no packet received).
    */
   uint16_t RxTimeouts;
} qapi_BLE_BSC_Statistics_t;

#define QAPI_BLE_BSC_STATISTICS_SIZE                        (sizeof(qapi_BLE_BSC_Statistics_t))

#define QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_RX               (0x00000001)
/**< Bit flag passed to qapi_BLE_BSC_ClearStatistics() to indicate that the Rx 
  statistics should be cleared. */

#define QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_TX               (0x00000002)
/**< Bit flag passed to qapi_BLE_BSC_ClearStatistics() to indicate that the Tx 
  statistics should be cleared. */

#define QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_ACTIVE_TIME      (0x00000004)
/**< Bit flag passed to qapi_BLE_BSC_ClearStatistics() to indicate that the 
  active time statistics should be cleared. */

#define QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_ALL              (0x00000007)
/**< Bit flag passed to qapi_BLE_BSC_ClearStatistics() to indicate that all 
  statistics should be cleared. */

/**
 * @brief
 * This declared type represents the Prototype Function
 * for a Bluetooth Stack Timer Callback.
 *
 * @details
 * This function will be called whenever an installed Timer
 * has expired.
 *
 * This function is
 * guaranteed not to be invoked more than once simultaneously for the
 * specified installed callback (that is, this function does not have be
 * reentrant).
 *
 * This function is called
 * in the Thread Context of a Thread that the user does not own.
 * Therefore, processing in this function should be as efficient as
 * possible (this argument holds anyway because no other Timer and/or
 * Stack Callbacks will be issued while function call is
 * outstanding).
 *
 * This function must not block and wait for events that
 * can only be satisfied by receiving other Stack Events.
 * A Deadlock will occur because no Stack Event Callbacks
 * will be issued while this function is currently
 * outstanding.
 *
 * @param[in] BluetoothStackID    Bluetooth stack ID for which the timer
 *                                is valid.
 *
 * @param[in] TimerID             Timer ID of the expired timer.
 *
 * @param[in] CallbackParameter   User-defined parameter (e.g., tag
 *                                value) that was defined in the
 *                                callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_BSC_Timer_Callback_t)(uint32_t BluetoothStackID, uint32_t TimerID, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the Prototype Function for
 * an Bluetooth Stack Debug Data Callback.
 *
 * @details
 * This function will be
 * called whenever a complete HCI packet has been sent or received by
 * the Bluetooth Device that was opened with the Bluetooth Protocol
 * Stack.
 *
 * This function passes to the caller the HCI packet that
 * was received and the Debug Callback Parameter that was specified
 * when this Callback was installed. The caller should use the
 * contents of the HCI packet only in the context of this callback.
 * this callback. If the caller requires the data for a longer
 * period of time, the callback function must copy the data
 * into another Data Buffer.
 *
 * This function is
 * guaranteed not to be invoked more than once simultaneously for the
 * specified installed callback (that is, this function does not have be
 * reentrant).
 *
 * This function is called in the Thread
 * Context of a Thread that the user does not own. Therefore,
 * processing in this function should be as efficient as possible
 * (this argument holds anyway because Packet Processing
 * (Sending/Receiving) will be suspended while the function call is
 * outstanding).
 *
 * @note1hang
 * This function must not call any Bluetooth Stack
 * functions. Failure to follow this guideline will
 * result in potential Deadlocks and/or erratic
 * behavior.
 * The Debug Callback is a very low-level callback and as
 * such, does not allow the Bluetooth Stack to be
 * reentrant.
 *
 * @param[in]  BluetoothStackID    Bluetooth Stack ID of the stack
 *                                 that the HCI packet was sent from.
 *
 * @param[in]  PacketSent          Boolean value that indicates TRUE if the
 *                                 packet was sent or FALSE if it was
 *                                 received.
 *
 * @param[in]  HCIPacket           Pointer to the packet contents.
 *
 * @param[in]  CallbackParameter   User-defined parameter (e.g., tag
 *                                 value) that was defined in the
 *                                 callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_BSC_Debug_Callback_t)(uint32_t BluetoothStackID, boolean_t PacketSent, qapi_BLE_HCI_Packet_t *HCIPacket, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the Prototype Function for
 * the BSC Asynchronous Callback.
 *
 * @details
 * This function will be called once
 * for each call to qapi_BLE_BSC_ScheduleAsynchronousCallback. This
 * function passes to the caller the Bluetooth Stack ID and the user
 * specified Callback Parameter that was passed into the
 * qapi_BLE_BSC_ScheduleAsynchronousCallback function.
 *
 * It should
 * also be noted that this function is called in the Thread Context
 * of a Thread that the user does not own. Therefore, processing in
 * this function should be as efficient as possible.
 *
 * The caller should keep the processing of these
 * callbacks small because other events will not be able
 * to be called while one is being serviced.
 *
 * @param[in]  BluetoothStackID   Bluetooth Stack ID of the Bluetooth
 *                                Stack that issued the call to
 *                                qapi_BLE_BSC_ScheduleAsynchronousCallback.
 *
 * @param[in]  CallbackParameter  User-defined parameter (e.g., tag
 *                                value) that was defined in the
 *                                callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_BSC_AsynchronousCallbackFunction_t)(uint32_t BluetoothStackID, unsigned long CallbackParameter);

/**
 * @brief
 * Initializes a Bluetooth
 * Protocol Stack for the specified Bluetooth Device (using the
 * specified HCI Transport).
 *
 * @note1hang
 * This function must be called (and
 * complete successfully) before any function in this module can be
 * called.
 *
 * The first parameter specifies the Bluetooth HCI Driver
 * Transport Information to use when opening the Bluetooth Device and
 * the second parameter specifies flags that are to be used to alter
 * the base Bluetooth Protocol Stack functionality.
 *
 * The HCI Driver
 * Information parameter is not optional and must specify a valid
 * Bluetooth HCI Driver transport provided by this Protocol Stack
 * Implementation.
 *
 * The flags parameter should be zero unless altered
 * functionality is required.
 *
 * Upon successfuly completion, this
 * function will return a positive, nonzero, return value. This
 * value will be used as input to functions provided by the Bluetooth
 * Protocol Stack that require a Bluetooth Protocol Stack ID
 * (functions that operate directly on a Bluetooth device). If this
 * function fails, the return value will be a negative return code
 * which specifies the error.
 * Once this function completes, the specified Bluetooth Protocol
 * Stack ID will remain valid for the specified Bluetooth device
 * until the Bluetooth Stack is closed via a call to the
 * qapi_BLE_BSC_Shutdown() function.
 *
 * @param[in] HCI_DriverInformation  Pointer to the driver information structure.
 *                                   This must be a valid transport supported by
 *                                   the stack.
 *
 * @param[in] Flags                  Should be zero (0) to load the
 *                                   standard/complete Bluetooth stack.
 *                                   Logical ORing of the following bitmask
 *                                   constants can be used to modify the
 *                                   standard/complete stack: \n
 *                                     #QAPI_BLE_BSC_INITIALIZE_FLAG_NO_L2CAP \n
 *                                     #QAPI_BLE_BSC_INITIALIZE_FLAG_NO_GAP
 *
 * @return
 * Positive unique identifier -- That is the BluetoothStackID used
 *             in other stack calls
 *             and callbacks. This ID remains valid for the
 *             specified Bluetooth device until the
 *             Bluetooth stack is closed via a call to the
 *             qapi_BLE_BSC_Shutdown() function.\n
 * Negative value -- That is an ErrorCode. Possible values are:
 *             @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_L2CAP_INITIALIZATION_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_Initialize(qapi_BLE_HCI_DriverInformation_t *HCI_DriverInformation, unsigned long Flags);

/**
 * @brief
 * Closes the Bluetooth
 * Protocol Stack that was opened for the Bluetooth device specified
 * via a successful call to the qapi_BLE_BSC_Initialize() function.
 *
 * @details
 * The input parameter to this function must have been acquired by a
 * successful call to the qapi_BLE_BSC_Initialize() function. Once
 * this function completes, the Bluetooth Device that was opened (and
 * the Bluetooth Protocol Stack that is associated with the device)
 * cannot be accessed again until the device (and a corresponding
 * Bluetooth Protocol Stack) is reopened by calling the
 * qapi_BLE_BSC_Initialize() function.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_Shutdown(uint32_t BluetoothStackID);

/**
 * @brief
 * Debugging function that allows the
 * caller to register a Debugging Callback that will be called each
 * time an HCI packet is sent or received.
 *
 * @details
 * Because this function will be called every time a packet is sent
 * or received, this function should only be used when debugging is required
 * because of the performance penalty that is present when using this
 * mechanism. This callback registration can only be removed via a call
 * to qapi_BLE_BSC_UnRegisterDebugCallback().
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  DebugCallback       Pointer to a user-supplied callback
 *                                 function which is defined as above in
 *                                 the BSC callback section.
 *
 * @param[in]  CallbackParameter   User-defined parameter (e.g., a
 *                                 tag value) that will be passed back
 *                                 to the user in the callback function
 *                                 with each packet.
 *
 * @return
 * Positive -- If successful.\n
 * Negative -- If an Error occurred. Possible values are:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_DEBUG_CALLBACK_ALREADY_INSTALLED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_RegisterDebugCallback(uint32_t BluetoothStackID, qapi_BLE_BSC_Debug_Callback_t DebugCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Removes a previously
 * installed Debug Callback for the specified Bluetooth Protocol
 * Stack (specified by the specified BluetoothStackID parameter).
 *
 * @details
 * After this function has completed,
 * the caller will no longer be notified via the debug callback function
 * when a debug event occurs.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_UnRegisterDebugCallback(uint32_t BluetoothStackID);

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief
 * Aids profile programmers by providing a
 * Mutex/Semaphore Lock that is completely thread safe.
 *
 * @details
 * This lock
 * is the same lock that the Bluetooth Protocol Stack uses to guard
 * against reentrancy problems. Using this mechanism allows atomic
 * operations to be performed (on the specified Bluetooth Protocol
 * Stack) and guarantees that no other thread can cause an operation
 * to be performed (on the specified Bluetooth Protocol Stack only).
 * This is a very low-level primitive and its use is really only
 * applicable to Profiles and/or Stack extensions. Applications
 * should never need to call this function (or its converse unlock
 * function). See the documentation contained in the header
 * file (qapi_ble_bsc.h) for more information on this function. It is
 * very important to note that if this function is called,
 * the qapi_BLE_BSC_UnLockBluetoothStack() is required to be called for
 * every successful call to this function. Failure to comply
 * with the preceding statement can and will lead to erratic
 * behavior. This function can be called more than once (in
 * the same thread), however the programmer must call the
 * unlock function the same number of times that this function
 * is successfully called.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an error occured. Possible values are:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_LockBluetoothStack(uint32_t BluetoothStackID);

/**
 * @brief
 * Allows the programmer a mechanism
 * to release a previous lock that was successfully acquired with the
 * BSC_LockBluetoothStack function.
 *
 * @details
 * The locking/unlocking mechanism exists to aid Profile programmers by
 * providing a Mutex/Semaphore Lock that is completely thread safe.
 * See qapi_BLE_BSC_LockBluetoothStack().
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_UnLockBluetoothStack(uint32_t BluetoothStackID);

/**
 * @brief
 * Utility function that exists to allow
 * the programmer a mechanism for installing an asynchronous
 * Bluetooth timer (of the specified timeout value).
 *
 * @details
 * The registered timer callback function will be called when the
 * timeout period expires (in milliseconds), passing the user-
 * supplied callback parameter to the caller. Once a callback
 * is installed, it will be removed from the system when it expires,
 * the stack is closed, or it is removed by the programmer via the
 * qapi_BLE_BSC_StopTimer(). Timers should be used sparingly because there
 * are only a finite number of timers present in the system. It
 * should be noted that all installed timers are one-shot timers
 * and not periodic (that is, they will only expire once). If a
 * periodic timer is required, the timer must be reregistered.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to
 *                                    this Bluetooth Protocol Stack
 *                                    via a call to
 *                                    qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Timeout               Timeout value (in milliseconds).
 *
 * @param[in]   TimerCallback         Pointer to a user-supplied
 *                                    callback function which is
 *                                    defined as above in the BSC
 *                                    callback section.
 *
 * @param[in]   CallbackParameter     User-defined parameter (e.g.,
 *                                    a tag value) that will be passed
 *                                    back to the user in the callback
 *                                    function when the timer expires.
 *
 * @return       Positive nonzero value if successful. This is the
 *               TimerID that is used to identify the timer. This
 *               value can be passed to the BSC_StopTimer function to
 *               cancel the timer.
 *
 * @return       Negative if an Error occurred. Possible values are:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_StartTimer(uint32_t BluetoothStackID, unsigned long Timeout, qapi_BLE_BSC_Timer_Callback_t TimerCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Removes a previously installed Bluetooth timer that
 * was registered with the qapi_BLE_BSC_StartTimer() function.
 *
 * @details
 * If this function returns successfully, the specified timer
 * (via TimerID) will no longer be present in the system, and hence
 * not expire.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TimerID            Timer indentifier of the timer that
 *                                is to be stopped. This value must
 *                                be a successful return value from
 *                                the qapi_BLE_BSC_StartTimer function.
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an error occurred. Possible values are:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_StopTimer(uint32_t BluetoothStackID, uint32_t TimerID);

/**
 * @brief
 * Function provided as a mechanism to determine whether
 * the specified Bluetooth Protocol Stack has any active connections
 * of the specified type. Active connections imply active ACLs or
 * pending outgoing connection attempts.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[in] Flags                  Should be set to zero (0).
 *
 * @return
 * TRUE -- If there are active BLE connections. \n
 * FALSE -- If there are no active BLE connections.
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_BSC_QueryActiveConnections(uint32_t BluetoothStackID, unsigned long Flags);

/**
 * @brief
 * Allows a mechanism of scheduling
 * a one-shot asynchronous callback that will be called once for each
 * function invocation.
 *
 * @param[in]  BluetoothStackID               Unique identifier assigned to
 *                                            this Bluetooth Protocol Stack
 *                                            via a call to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]  AsynchronousCallbackFunction   Pointer to a function that
 *                                            is to be scheduled to run
 *                                            asynchronously.
 *
 * @param[in]  CallbackParameter              User-defined parameter
 *                                            (e.g., a tag value) that will
 *                                            be passed back to the user in
 *                                            the callback function when it
 *                                            is called.
 *
 * @return
 * Non-zero -- If successful. \n
 * Zero -- If an error occurred.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_ScheduleAsynchronousCallback(uint32_t BluetoothStackID, qapi_BLE_BSC_AsynchronousCallbackFunction_t AsynchronousCallbackFunction, unsigned long CallbackParameter);

/**
 * @brief
 * Allows a mechanism to acquire a
 * global lock that can be used to search lists that are maintained by
 * modules (for resource tracking).
 *
 * @details
 * This lock cannot be held while holding or acquiring any other lock.
 * This functionality is provided to allow a mechanism on smaller
 * (embedded) systems so that individual modules (such as the HCI
 * drivers and profiles) to not have to waste resources for locks to
 * protect their internal lists. The caller must call the
 * qapi_BLE_BSC_ReleaseListLock() function to release the lock when
 * finished.
 *
 * @return
 * TRUE -- If the list lock was obtained successfully. \n
 * FALSE -- If the lock was unable to be obtained (or an error occured).
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_BSC_AcquireListLock(void);

/**
 * @brief
 * Allows a mechansim for the
 * caller to release the acquired list lock (previously acquired via
 * a successful call to the qapi_BLE_BSC_AcquireListLock() function).
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_ReleaseListLock(void);

/**
 * @brief
 * Utility function that adds the actual
 * specified opaque list entry to the specified opaque list entry list.
 *
 * @details
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list
 * (including this one) are told the necessary structure offsets
 * (and sizes) of each entry. The utility functions also define
 * the concept of a key that can be used for searching through
 * the list.
 *
 * Valid values must be specified for the following parameters (or the function
 * will fail): \n
 *   ListHead       -- The parameter cannot be NULL, but the value that it
 *                     points to can be NULL \n
 *   ListEntryToAdd -- The parameter cannot be NULL, and it must point to the
 *                     List Entry Data that is to be added (of size ListEntrySize).
 *
 * If the GenericListEntryKey value is anything other than ekNone, this function
 * does not insert duplicate entries into the list. An item is considered a duplicate
 * if the key value of the entry being added matches any key value of an entry
 * already in the list. When this parameter is anything other than QAPI_BLE_EK_NONE_E,
 * the following parameters must be specified: \n
 *   ListEntryKeyOffset -- Specifies the byte offset of the Generic List Entry Key
 *                         Element (in each individual List Entry).
 *
 * In all cases, the ListEntryNextPointerOffset parameter must specify the byte
 * offset of the element that represents a pointer to the next element that is
 * present in the list (for each individual List Entry)
 *
 * @param[in]  GenericListEntryKey          Key value type that is used to search for
 *                                          duplicates (see notes above).
 *
 * @param[in]  ListEntryKeyOffset           Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry key is located.
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry next pointer is located.
 *
 * @param[in]  ListHead                     Pointer to the location that holds a
 *                                          pointer to the first entry in the list
 *                                          (the value at this location can be NULL
 *                                          for an empty list, but this parameter
 *                                          cannot be NULL).
 *
 * @param[in]  ListEntryToAdd               Pointer to the actual list entry that
 *                                          is to be added to the specified list
 *                                          (note that the offsets specified in
 *                                          the prior parameters are applied to
 *                                          this address to resolve the correct
 *                                          locations).
 *
 * @return
 * TRUE -- If the specified list entry was added to the specified list. \n
 * FALSE -- If the entry was unable to be added (either invalid parameter
 *          or there was a duplicate entry in the list).
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_BSC_AddGenericListEntry_Actual(qapi_BLE_BSC_Generic_List_Entry_Key_t GenericListEntryKey, uint32_t ListEntryKeyOffset, uint32_t ListEntryNextPointerOffset, void **ListHead, void *ListEntryToAdd);

/**
 * @brief
 * Utility function that adds an opaque list
 * entry (with the specified opaque list entry information) to the specified
 * opaque list entry list.
 *
 * @details
 * This function does not add the specified entry directly to the list.
 * This function allocates an entry (of the correct sizes) and copies
 * the data from the specified entry into this newly allocated entry.
 * This newly allocated entry is then added to the specified list.
 *
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list
 * (including this one) are told the necessary structure offsets
 * (and sizes) of each entry. The utility functions also define
 * the concept of a key that can be used for searching through
 * the list.
 *
 * Valid values must be specified for the following parameters (or the function
 * will fail): \n
 *   ListHead       -- The parameter cannot be NULL, but the value that it points
 *                     to can be NULL. \n
 *   ListEntryToAdd -- The parameter cannot be NULL, and it must point to the
 *                     List Entry Data that is to be added (of size ListEntrySize).
 *
 * If the GenericListEntryKey value is anything other than ekNone, this function
 * does not insert duplicate entries into the list. An item is considered a duplicate
 * if the key value of the entry being added matches any key value of an entry already
 * in the list. When this parameter is anything other than QAPI_BLE_EK_NONE_E, the
 * following parameters must be specified: \n
 *   ListEntryKeyOffset -- Specifies the byte offset of the Generic List Entry Key
 *                         Element (in each individual List Entry).
 *
 * In all cases, the ListEntryNextPointerOffset parameter must specify the byte offset
 * of the element that represents a pointer to the next element that is present in the
 * list (for each individual List Entry).
 *
 * @param[in]  ListEntrySizeToAllocate      Entire size (in bytes) of the entry to
 *                                          allocate. Note that this is note the
 *                                          size of the list entry itself. This
 *                                          value must be at least the size of
 *                                          ListEntrySize, but can be specified
 *                                          larger. This allows the ability to
 *                                          allocate extra space immediately after
 *                                          the list entry.
 *
 * @param[in]  GenericListEntryKey          Key value type that is used to search for
 *                                          duplicates (see notes above).
 *
 * @param[in]  ListEntryKeyOffset           Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry key is located.
 *
 * @param[in]  ListEntrySize                Cannot be zero and must be less than
 *                                          or equal to the ListEntrySizeToAllocate
 *                                          parameter.
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry next pointer is located.
 *
 * @param[in]  ListHead                     Pointer to the location that holds a
 *                                          pointer to the first entry in the list
 *                                          (the value at this location can be NULL
 *                                          for an empty list, but this parameter
 *                                          cannot be NULL).
 *
 * @param[in]  ListEntryToAdd               Pointer to the actual list entry that
 *                                          is to be added to the specified list
 *                                          (note that the offsets specified in
 *                                          the prior parameters are applied to
 *                                          this address to resolve the correct
 *                                          locations).
 *
 * @return
 * TRUE -- If the specified list entry was added to the specified list. \n
 * FALSE -- If the entry was unable to be added (either invalid parameter,
 *          or there was a duplicate entry in the list).
 */
QAPI_BLE_DECLARATION void *QAPI_BLE_BTPSAPI qapi_BLE_BSC_AddGenericListEntry(uint32_t ListEntrySizeToAllocate, qapi_BLE_BSC_Generic_List_Entry_Key_t GenericListEntryKey, uint32_t ListEntryKeyOffset, uint32_t ListEntrySize, uint32_t ListEntryNextPointerOffset, void **ListHead, void *ListEntryToAdd);

/**
 * @brief
 * Utility function that enables
 * a search for a specific opaque list entry (located in the specified
 * opaque list entry list).
 *
 * @details
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list
 * (including this one) are told the necessary structure offsets
 * (and sizes) of each entry. The utility functions also define the
 * concept of a key that can be used for searching through the list.
 *
 * @param[in]  GenericListEntryKey          Key value type that is used to search for
 *                                          duplicates (see notes above).
 *
 * @param[in]  GenericListEntryKeyValue     Pointer to the key value that is to
 *                                          matched for the search. The actual data
 *                                          type that this value points to depends
 *                                          upon the value of the previous parameter.
 *                                          Note that this value cannot be NULL.
 *
 * @param[in]  ListEntryKeyOffset           Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry key is located.
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry next pointer is located.
 *
 * @param[in]  ListHead                     Pointer to the location that holds a
 *                                          pointer to the first entry in the list
 *                                          (the value at this location can be NULL
 *                                          for an empty list, but this parameter
 *                                          cannot be NULL).
 *
 * @return
 * Non-NULL value -- Indicates success (a pointer to the entry that was found). \n
 * NULL value -- Indicates that an entry was not located in the specified list.
 */
QAPI_BLE_DECLARATION void *QAPI_BLE_BTPSAPI qapi_BLE_BSC_SearchGenericListEntry(qapi_BLE_BSC_Generic_List_Entry_Key_t GenericListEntryKey, void *GenericListEntryKeyValue, uint32_t ListEntryKeyOffset, uint32_t ListEntryNextPointerOffset, void **ListHead);

/**
 * @brief
 * Utility function that allows the ability
 * to find the next opaque list entry give the specified opaque list entry
 * list.
 *
 * @details
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list (including
 * this one) are told the necessary structure offsets (and sizes) of each
 * entry. The utility functions also define the concept of a key that
 * can be used for searching through the list.
 *
 * @param[in]  GenericListEntryKey          Key value type that is used to search for
 *                                          duplicates (see notes above).
 *
 * @param[in]  GenericListEntryKeyValue     Pointer to the key value that is to
 *                                          matched for the search. The actual data
 *                                          type that this value points to depends
 *                                          upon the value of the previous parameter.
 *                                          Note that this value cannot be NULL.
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry next pointer is located.
 *
 * @param[in]  ListHead                     Pointer to the location that holds a
 *                                          pointer to the first entry in the list
 *                                          (the value at this location can be NULL
 *                                          for an empty list, but this parameter
 *                                          cannot be NULL).
 *
 * @return
 * Non-NULL value -- Indicates success (a pointer to the entry that was found). \n
 * NULL value -- Indicates that an entry was not located in the specified list.
 */
QAPI_BLE_DECLARATION void *QAPI_BLE_BTPSAPI qapi_BLE_BSC_GetNextGenericListEntry(qapi_BLE_BSC_Generic_List_Entry_Key_t GenericListEntryKey, void *GenericListEntryKeyValue, uint32_t ListEntryNextPointerOffset, void **ListHead);

/**
 * @brief
 * Utility function that allows the ability to
 * remove a specific opaque list entry from the specified opaque list entry
 * list.
 *
 * @details
 * This function does not delete the memory for the entry, it simply
 * removes it from the list and returns a pointer to the newly removed
 * entry.
 *
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list (including
 * this one) are told the necessary structure offsets (and sizes) of each
 * entry. The utility functions also define the concept of a key that
 * can be used for searching through the list.
 *
 * @param[in]  GenericListEntryKey          Key value type that is used to search for
 *                                          duplicates (see notes above).
 *
 * @param[in]  GenericListEntryKeyValue     Pointer to the key value that is to
 *                                          matched for the search. The actual data
 *                                          type that this value points to depends
 *                                          upon the value of the previous parameter.
 *                                          Note that this value cannot be NULL.
 *
 * @param[in]  ListEntryKeyOffset           Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry key is located.
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the
 *                                          beginning of the list entry where the
 *                                          list entry next pointer is located.
 *
 * @param[in]  ListHead                     Pointer to the location that holds a
 *                                          pointer to the first entry in the list
 *                                          (the value at this location can be NULL
 *                                          for an empty list, but this parameter
 *                                          cannot be NULL).
 *
 * @return
 * Non-NULL value -- Indicates success (a pointer to the entry that was found). \n
 * NULL value -- Indicates that an entry was not located in the specified list.
 */
QAPI_BLE_DECLARATION void *QAPI_BLE_BTPSAPI qapi_BLE_BSC_DeleteGenericListEntry(qapi_BLE_BSC_Generic_List_Entry_Key_t GenericListEntryKey, void *GenericListEntryKeyValue, uint32_t ListEntryKeyOffset, uint32_t ListEntryNextPointerOffset, void **ListHead);

/**
 * @brief
 * Utility function that allows the ability to free
 * the memory for an opaque list entry that was allocated via the
 * qapi_BLE_BSC_FreeGenericListEntryMemory() function.
 *
 * @param[in]  EntryToFree   Pointer to the the actual opaque list entry memory
 *                           that is be freed.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_FreeGenericListEntryMemory(void *EntryToFree);

/**
 * @brief
 * Utility function that removes every list entry
 * (and frees each list entry element) from the specified list.
 *
 * @details
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures). This schema
 * is possible because all the routines that operate on the list (including
 * this one) are told the necessary structure offsets (and sizes) of each
 * entry. The utility functions also define the concept of a key that
 * can be used for searching through the list.
 *
 * This function does not free the resources of the element that was deleted
 * from the list, it only removes it from the list and frees the memory of
 * each entry itself.
 *
 * When this function returns, the list head will be set to NULL
 * (indicating an empty list).
 *
 * @param[in]  ListHead                     Pointer to the location that holds a pointer to
 *                                          the first entry in the list (the value at this
 *                                          location can be NULL for an empty list, but
 *                                          this parameter cannot be NULL).
 *
 * @param[in]  ListEntryNextPointerOffset   Offset (specified in bytes) from the beginning
 *                                          of each list entry where the list entry next
 *                                          pointer is located.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BSC_FreeGenericListEntryList(void **ListHead, uint32_t ListEntryNextPointerOffset);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * @brief
 * Utility function that queries the Bluetooth firmware version information.
 *
 * @details
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  VersionInformation   Holds the Bluetooth firmware version
 *                                   information, if this function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an error occurred. Possible values are:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_Query_Version_Information(uint32_t BluetoothStackID, qapi_BLE_BSC_Version_Information_t *VersionInformation);

/**
 * @brief
 * Utility function that queries the Bluetooth firmware statistics.
 *
 * @details
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack, using a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  Statistics        Structure that will be populated with the
 *                                statistics, if this function is successful.
 *
 * @return       Zero if successful.
 *
 * @return       Negative if an Error occurred. Possible values are:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_QueryStatistics(uint32_t BluetoothStackID, qapi_BLE_BSC_Statistics_t *Statistics);

/**
 * @brief
 * Utility function that clears the Bluetooth firmware statistics.
 *
 * @details
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack, using a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  Flags             Flag bitmask to indicate which statistics
 *                                will be cleared. Bits are defined in
 *                                QAPI_BLE_BSC_STATISTICS_CLEAR_FLAG_* macros.
 *
 * @return       Zero if successful.
 *
 * @return       Negative if an Error occurred. Possible values are:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BSC_ClearStatistics(uint32_t BluetoothStackID, uint32_t Flags);

/** @} */ /* end_addtogroup qapi_ble_core_bsc */

#endif

