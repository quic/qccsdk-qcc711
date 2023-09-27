/*=============================================================================

                    TME COM Client Utilities Source File


   Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Qualcomm Technologies, Inc. Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stddef.h>

#include "Tmecom.h"

/*=============================================================================
                         LOCAL DATA DECLARATIONS
=============================================================================*/

/*----------------------------------------------------------------------------
 * Glink config struct for APSS
 *--------------------------------------------------------------------------*/
static TmecomGlinkCfg_t gApssGlinkCfg = {
    "tme", "tmeRequest"
};

/*=============================================================================

                PUBLIC FUNCTION DEFINITIONS

=============================================================================*/

/**
   @brief Get APSS client config data.

   @return A pointer to local subsytem specific config structure.
 */
const TmecomGlinkCfg_t* TmecomGetClientCfg()
{
    return &gApssGlinkCfg;
}

