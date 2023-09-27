/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

/**************************************************************************//**
 * @file     system_qcc710.c
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Source File for
 *           Device QCC710
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include "qcc710.h"
#include "HALhwio.h"
#include "hwio_aon.h"


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL            (32000000U)       /* Oscillator frequency             */

#define SYSTEM_CLOCK    (1 * XTAL)


/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Clock Frequency (Core Clock)*/



/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/

void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  SystemCoreClock = SYSTEM_CLOCK;
}

void SystemInit (void)
{
  SystemCoreClock = SYSTEM_CLOCK;

  /* Make the vote for NVM to be active. */
  HWIO_AON_PME_APPS_DEPEND_ACTIVE_OUTM(HWIO_AON_PME_APPS_DEPEND_ACTIVE_NVM_BMSK, HWIO_AON_PME_APPS_DEPEND_ACTIVE_NVM_BMSK);

  /* Signal that APSS is running. */
  HWIO_AON_PME_APPS_STATUS_OUTM(HWIO_AON_PME_APPS_STATUS_OPERATIVE_BMSK, HWIO_AON_PME_APPS_STATUS_OPERATIVE_BMSK);
}
