/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
*  @file qapi_firmware_update.h
*  @brief Firmware update package APIs, types, and definitions.

    This module provides APIs for verification of update package and applying device firmware updates.

    These APIs provide high level interfaces for firmware update operations, and
    support blocking and non-blocking modes of operation. The supplied callback
    is used only in case of non-blocking modes.
    Note: Callback is executed in interrupt context, and should be released immediately. 
    Calling other QAPIs from the callback is not supported.

    The flow for a typical update operation is shown below:

    @msc
    arcgradient = 0, width="1000";
    Application, Firmware_Update_Module;
    ...;
    ...;
    Application => Firmware_Update_Module [label="Verify update package"];
    Firmware_Update_Module => Application [label="Response"];
    |||;
    |||;
    Application => Firmware_Update_Module [label="Apply update (does not return)"];
    |||;
    |||;
    ---  [ label = "System Reboots for applying update" ];
    @endmsc

*/

#ifndef __QAPI_FWUP_H__
#define __QAPI_FWUP_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_fwup
@{ */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Enumeration of supported firmware update operations. */
typedef enum
{
   QAPI_FWUP_VERIFY_UPDATE_PACKAGE_E, /**< Verify update package. */
   QAPI_FWUP_APPLY_UPDATE_PACKAGE_E,  /**< Apply update package. */
} qapi_FWUP_Operation_t;

/** Enumeration of package verification status. */
typedef enum
{
   QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E,  /**< Software authentication success. */
   QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E,  /**< Software authentication failure. */
   QAPI_FWUP_VERIFICATION_INVALID_INPUT_E, /**< Software update image is invalid. */
   QAPI_FWUP_VERIFICATION_IMAGE_OVERLAP_E  /**< Software image overlaps. */
} qapi_FWUP_Verification_Status_t;

/** Structure representing the parameters required to perform verify update package operation. */
typedef struct qapi_FWUP_Verify_Update_Package_s
{
   uint32_t                         Size;               /**< Update package size in bytes. */
   uint32_t                         Location;           /**< Update package location on NVM. 
                                                             Location must be 32-bit word aligned. */
   qbool_t                          VerifyAllImages;    /**< If set to true, then all the imgaes i.e.
                                                             updated and non-updated will be
                                                             verified. Otherwise, image authentication
                                                             is done if the authentication bit is set
                                                             for the OEM_SECURITY_POLICY fuse. */
   qapi_FWUP_Verification_Status_t  VerificationStatus; /**< Update package verification status. */
} qapi_FWUP_Verify_Update_Package_t;

/** Structure representing the parameters required to perform apply update package operation. */
typedef struct qapi_FWUP_Apply_Update_Package_s
{
   qbool_t   LockDebug; /**< If set true, then OEM M3 debugging capability is locked. Also when
                             LockDebug is set to true, before applying update, RoT will verify
                             all the images i.e. both updated and non-updated. When it is set to
                             false, image authentication is done if the authentication bit is set
                             for the OEM_SECURITY_POLICY fuse */
   uint32_t  Size;      /**< Update package size in bytes. */
   uint32_t  Location;  /**< Update package location on NVM.
                             Location must be 32-bit word aligned. */
} qapi_FWUP_Apply_Update_Package_t;

/** Structure representing the event data as received in callback. */
typedef struct qapi_FWUP_Operation_Event_Data_s
{
  qapi_FWUP_Operation_t Operation;                           /**< Operation type. */
  union {
    qapi_FWUP_Verify_Update_Package_t *VerifyUpdateParams;   /**< Verify update package params. */
  }
  Data;                                                      /**< Event data. */
} qapi_FWUP_Operation_Event_Data_t;

/** @brief Prototype for a function called after a non-blocking firmware update operation is complete.
    @param[in] Status     Operation result.
    @param[in] EventData  Event Data for firmware update operation.
    @param[in] UserParam  User specified parameter provided when the callback is registered. */
typedef void (*qapi_FWUP_Operation_CB_t)(qapi_Status_t Status, qapi_FWUP_Operation_Event_Data_t *EventData, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Verifies the update package.

   This operation requires operation on NVM. Parallel operations on NVM are not recommended.

   The verification status is provided as output for the update package.

   @param[in,out] VerifyUpdatePackageParams  Verify update package parameters.
   @param[in]     FwupCB                     Callback function, only used in non-blocking mode.
                                             NULL for blocking mode.
   @param[in]     UserParam                  User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call was successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter VerifyUpdatePackageParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_FWUP_Verify_Update_Package(qapi_FWUP_Verify_Update_Package_t *VerifyUpdatePackageParams,
                                              qapi_FWUP_Operation_CB_t           FwupCB,
                                              void                              *UserParam);

/**
   @brief Applies the firmware update.

   This operation verifies the firmware update package and applies it. If the operation is successful.
   It triggers an SoC reset, and does not return.

   Also, this operation requires operation on NVM. Parallel operations on NVM are not recommended.

   All the software component images must be decrypted and placed in NVM before calling this API.
   If LockDebug is set TRUE, then the APSS processor debugging capability is locked.

   @param[in,out] ApplyUpdateParams  Apply update parameters.

   @return
   Negative value if there is an error.

   \attention All the software component images must exist on NVM in plaintext before applying an update.

*/
qapi_Status_t qapi_FWUP_Apply_Update_Package(qapi_FWUP_Apply_Update_Package_t *ApplyUpdateParams);

/** @} */ /* end_addtogroup qapi_fwup */

#endif
