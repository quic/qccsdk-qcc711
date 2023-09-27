/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>

#include "qapi_mfg.h"
#include "qapi_gpio.h"
#include "qapi_nvm.h"
#include "qapi_mtp.h"
#include "hwio_gcc.h"
#include "hwio_pmu.h"
#include "hwio_tlmm.h"
#include "qapi_fuse.h"
#include "qapi_rot.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Prototypes
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/


/**
   @brief Enable/disables clock output.

   If QAPI_MFG_CLOCK_LFCLK_E is specified for the Clock parameter, and
   the output is disabled, then QAPI_GPIO_ID13_E will be set to input (no pull).

   If QAPI_MFG_CLOCK_HFCLK_E is specified for the Clock parameter, and
   the output is disabled, then QAPI_GPIO_ID11_E will be set to input (no pull).

   @param[in] Clock       Identifies the clock.
   @param[in] Enable      Enables/disables clock output.

   @return QAPI_OK if the successful or a negative value if
           there was an error.
*/
qapi_Status_t qapi_MFG_Enable_CLK_Output(qapi_MFG_Clock_t Clock, qbool_t Enable)
{
   qapi_Status_t      RetVal;
   qapi_GPIO_Config_t Config;
   qapi_GPIO_Id_t     GpioId;

   /* Make sure the input parameters are valid. */
   if((Clock == QAPI_MFG_CLOCK_LFCLK_E) || (Clock == QAPI_MFG_CLOCK_HFCLK_E))
   {
      if(Enable)
      {
         Config.PIOFunc = 8;
         Config.Dir     = QAPI_GPIO_OUTPUT_E;
         Config.Pull    = QAPI_GPIO_NO_PULL_E;
         Config.Drive   = QAPI_GPIO_FAST_2MA_E;
      }
      else
      {
         Config.PIOFunc = 0;
         Config.Dir     = QAPI_GPIO_INPUT_E;
         Config.Pull    = QAPI_GPIO_PULL_DOWN_E;
         Config.Drive   = QAPI_GPIO_FAST_2MA_E;
      }

      GpioId = (Clock == QAPI_MFG_CLOCK_LFCLK_E) ? QAPI_GPIO_ID13_E : QAPI_GPIO_ID11_E;

      RetVal = qapi_GPIO_Config(GpioId, &Config);
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Updates the coarse trim in real time for the specified clock.

   To store the trim persistently, the qapi_MFG_Store_CLK_Trim() function may be
   used.

   @param[in] Clock       Identifies the clock.
   @param[in] Trim        Specifies the coarse trim.

   @return QAPI_OK if the successful or a negative value if there was an error.
*/
qapi_Status_t qapi_MFG_Update_CLK_Coarse_Trim(qapi_MFG_Clock_t Clock, uint16_t Trim)
{
   qapi_Status_t RetVal;

   /* Make sure the input parameters are valid. */
   if(((Clock == QAPI_MFG_CLOCK_LFCLK_E) && (Trim >= QAPI_MFG_MIN_LFCLK_COARSE_TRIM) && (Trim <= QAPI_MFG_MAX_LFCLK_COARSE_TRIM)) ||
      ((Clock == QAPI_MFG_CLOCK_HFCLK_E) && (Trim >= QAPI_MFG_MIN_HFCLK_COURSE_TRIM) && (Trim <= QAPI_MFG_MAX_HFCLK_COURSE_TRIM)))
   {
      if(Clock == QAPI_MFG_CLOCK_LFCLK_E)
      {
         HWIO_APSS_XTAL_CL_CONF_OUT(Trim);
      }
      else
      {
         HWIO_AUX_ANA_CTRL3_REG_OUTM(HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_BMSK, Trim << HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_SHFT);
      }

      RetVal = QAPI_OK;
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Updates the fine trim in real time for the specified clock.

   QAPI_MFG_CLOCK_LFCLK_E may not be specified for the Clock parameter since the
   fine trim for the low frequency clock is not supported.

   To store the trim persistently, the qapi_MFG_Store_CLK_Trim() function may be
   used.

   @param[in] Clock Identifies the clock.

   @param[in] Trim Specifies the fine trim.

   @return QAPI_OK if the successful or a negative value if there was an error.
*/
qapi_Status_t qapi_MFG_Update_CLK_Fine_Trim(qapi_MFG_Clock_t Clock, int16_t Trim)
{
   qapi_Status_t RetVal;

   /* Make sure the input parameters are valid. */
   if((Clock == QAPI_MFG_CLOCK_HFCLK_E) && (Trim >= QAPI_MFG_MIN_HFCLK_FINE_TRIM) && (Trim <= QAPI_MFG_MAX_HFCLK_FINE_TRIM))
   {
      HWIO_AUX_ANA_CTRL3_REG_OUTM(HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_BMSK, Trim << HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_SHFT);

      RetVal = QAPI_OK;
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Persistently stores the specified clock trim.

   The FineTrim parameter will be ignored if QAPI_MFG_CLOCK_LFCLK_E is specified
   for the Clock parameter since fine trim is not supported by the low frequency
   clock.

   @param[in] Clock       Identifies the clock.
   @param[in] CoarseTrim  Specifies the coarse trim.
   @param[in] FineTrim    Specifies the fine trim.

   @return QAPI_OK if the successful or a negative value if there was an error.
*/
qapi_Status_t qapi_MFG_Store_CLK_Trim(qapi_MFG_Clock_t Clock, uint16_t CoarseTrim, int16_t FineTrim)
{
   qapi_Status_t   RetVal;
   const uint16_t *MtpAddress;
   uint16_t        Value;

   /* Make sure the input parameters are valid. */
   if(((Clock == QAPI_MFG_CLOCK_LFCLK_E) && (CoarseTrim >= QAPI_MFG_MIN_LFCLK_COARSE_TRIM) && (CoarseTrim <= QAPI_MFG_MAX_LFCLK_COARSE_TRIM)) ||
      ((Clock == QAPI_MFG_CLOCK_HFCLK_E) && (CoarseTrim >= QAPI_MFG_MIN_HFCLK_COURSE_TRIM) && (CoarseTrim <= QAPI_MFG_MAX_HFCLK_COURSE_TRIM) &&
                                            (FineTrim >= QAPI_MFG_MIN_HFCLK_FINE_TRIM) && (FineTrim <= QAPI_MFG_MAX_HFCLK_FINE_TRIM)))
   {
      if(Clock == QAPI_MFG_CLOCK_LFCLK_E)
      {
         /* Update the LFCLK trim. */
         MtpAddress = &(QAPI_MTP_APSS_RW_PTR->Xtal32kCfg_LdoVmaSelPt);

         Value  = *MtpAddress & ~QAPI_MTP_XTAL_32K_CFG_TRIM_CL_BITMASK;
         Value |= CoarseTrim << QAPI_MTP_XTAL_32K_CFG_TRIM_CL_SHIFT;
      }
      else
      {
         /* Update the HFCLK trim. */
         MtpAddress = &(QAPI_MTP_APSS_RW_PTR->AuxCtrl3);

         Value  = *MtpAddress & ~(HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_BMSK | HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_BMSK);
         Value |= (uint16_t)FineTrim << HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_SHFT;
         Value |= CoarseTrim << HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_SHFT;
      }

      RetVal = qapi_ROT_Session_Start();

      if(RetVal == QAPI_OK)
      {
         /* Write the value to MTP. */
         RetVal = qapi_NVM_Request_Write();
         if(RetVal == QAPI_OK)
         {
             RetVal = qapi_NVM_Write(MtpAddress, &Value, sizeof(Value));

             qapi_NVM_Release_Write();
         }

         qapi_ROT_Session_End();
      }
      else
      {
         RetVal = QAPI_ERR_INVALID_PARAM;
      }
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

