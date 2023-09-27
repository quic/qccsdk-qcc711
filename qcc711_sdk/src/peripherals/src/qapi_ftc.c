/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qcc710.h"
#include "core_cm3.h"
#include "HALhwio.h"
#include "hwio_periph.h"
#include "qapi_ftc.h"
#include "qapi_task.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/
qapi_FTC_User_CB_t FTC_CB_Function[QAPI_FTC_INSTANCE_CASCADED_E+1];

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Set FTC configuration for each instance.

   Set the configuration for generate the PWM signal or start a timer. use
   Input_enable to choose clock or input signal as counter source, InputConfig
   is used for setting input signal configuration. Output_enable is used to
   control output signal, for timer function, it may do not need to output any
   signal.

   @param[in] Instance_ID  FTC instance ID.
   @param[in] Config       FTC configurations.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_Initialize(qapi_FTC_Instance_t Instance_ID, qapi_FTC_Config_t *Config)
{
    uint8_t i;
    uint8_t Clk_type;
    uint32_t Addr;
    uint8_t CascadedInstance;
    uint32_t InstanceMask;
    uint16_t Maxval;
    uint8_t ChannelID;

    if (Config == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }
    qapi_TSK_Enter_Critical();    
    HWIO_PERIPH_CLOCK_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 
                               HWIO_PERIPH_CLOCK_CFG_FTC_CORE_EN_BMSK | HWIO_PERIPH_CLOCK_CFG_FTC_CLK_EN_BMSK,
                               HWIO_PERIPH_CLOCK_CFG_FTC_CORE_EN_BMSK | HWIO_PERIPH_CLOCK_CFG_FTC_CLK_EN_BMSK); //enable FTC0-3 clock
    qapi_TSK_Exit_Critical();

    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            HWIO_PERIPH_FTC_CMN_CTRL2_CASCADED_MODE_BMSK, 1);
        /* set_default_clk */
        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            0x03 << HWIO_PERIPH_FTC_CMN_CTRL2_FTC0_FTC_CLK_SEL_SHFT,
            0 << HWIO_PERIPH_FTC_CMN_CTRL2_FTC0_FTC_CLK_SEL_SHFT);
        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            0x03 << HWIO_PERIPH_FTC_CMN_CTRL2_FTC1_FTC_CLK_SEL_SHFT,
            0 << HWIO_PERIPH_FTC_CMN_CTRL2_FTC1_FTC_CLK_SEL_SHFT);
        CascadedInstance = QAPI_FTC_INSTANCE_0_E;
        InstanceMask = 0x03;
    }
    else
    {
        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            HWIO_PERIPH_FTC_CMN_CTRL2_CASCADED_MODE_BMSK, 0);
        /* set_default_clk use FTC0 clock */
        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            0x03 << (4 * Instance_ID + 4), 0 << (4 * Instance_ID + 4));
        /* counter_clk_Sel */
        HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_OUTM(
            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
            HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_CNT_CLK_SEL_BMSK, 0);
        CascadedInstance = Instance_ID;
        InstanceMask = 0x1 << Instance_ID;
    }

    /* set_pre_scaler */
    if (Config->Scale >= 0)
    {
        if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
        {
            return QAPI_ERR_INVALID_PARAM;
        }
        HWIO_PERIPH_FTC_0_FTC_CTRL1_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_BMSK, 1);
        HWIO_PERIPH_FTC_0_FTC_CTRL1_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_CFG_BMSK,
            Config->Scale << HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_CFG_SHFT);
        Clk_type = 1;  /* prescaler clock */
    }
    else
    {
        HWIO_PERIPH_FTC_0_FTC_CTRL1_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_BMSK, 0);
        HWIO_PERIPH_FTC_0_FTC_CTRL1_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_CFG_BMSK,
            0 << HWIO_PERIPH_FTC_0_FTC_CTRL1_FTC_PSC_CFG_SHFT);
        Clk_type = 0;  /* FTC clock */
    }

    /* counter_clk_Sel */
    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE,
            HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_CNT_CLK_SEL_BMSK, Clk_type);
        HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_OUTM(PERIPH_FTC_1_FTC_1_FTC_REG_BASE,
            HWIO_PERIPH_FTC_1_FTC_CNT_CLK_SEL_CNT_CLK_SEL_BMSK, Clk_type);
    }
    else
    {
        HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
            HWIO_PERIPH_FTC_0_FTC_CNT_CLK_SEL_CNT_CLK_SEL_BMSK,
            Clk_type);
    }

    if (Config->InputEnable)
    {
        /* connect_input_to_channel */
        HWIO_PERIPH_FTC_CMN_CTRL1_OUTM(PERIPH_FTC_TOP_REG_BASE,
            HWIO_PERIPH_FTC_CMN_CTRL1_FTC0_CH_IN0_SEL_BMSK <<
            CascadedInstance * HWIO_PERIPH_FTC_CMN_CTRL1_FTC1_CH_IN0_SEL_SHFT,
            Config->InputConfig.FtcInput << CascadedInstance
            * HWIO_PERIPH_FTC_CMN_CTRL1_FTC1_CH_IN0_SEL_SHFT);

        /* configure_input_filter */
        HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_SMP_NUM_BMSK,
            Config->InputConfig.SmpNum
            << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_SMP_NUM_SHFT);
        if (Config->InputConfig.SmpNum > 0)
        {
            HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_CLK_SEL_BMSK,
                Config->InputConfig.Sel
                << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_CLK_SEL_SHFT);
            HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                +PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_CLK_DIV_BMSK,
                Config->InputConfig.Div
                << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_CLK_DIV_SHFT);
            HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                +PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_SYNC_EN_BMSK,
                1 << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_FLT_SYNC_EN_SHFT);
        }
        HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_IN_INV_BMSK,
            0 << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_IN_INV_SHFT);

        /* set_count_mode */
        HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_MODE_BMSK, 1);
        HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_SUB_MODE_BMSK,
            0 << HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_SUB_MODE_SHFT);

        /* config_edge_detector */
        HWIO_PERIPH_FTC_0_FTC_IN0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_EDGE_SEL_BMSK,
            (Config->InputConfig.Edge + 1)
            << HWIO_PERIPH_FTC_0_FTC_IN1_CTRL_IN1_CTRL_EDGE_SEL_SHFT);

        /* connect_ccb_chan_a */
        HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE*CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CH_A_SEL_BMSK,
            0x4 << HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CH_A_SEL_SHFT);
        
        if (Config->Period > 1)
        {
            /* set_max_cmp_function */
            HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_MAX_CMP_FUNC_BMSK,
                1 << HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_MAX_CMP_FUNC_SHFT);
    
            /* set_max_cmn_cmp */
            Maxval = Config->Period - 1;
            
            HWIO_PERIPH_FTC_0_FTC_MAX_CMP_OUTM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_MAX_CMP_FTC_MAX_CMP_BMSK, Maxval);
            while (0 == HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE +
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_MAX_CMP_WR_READY_BMSK))
            {
                ;
            }
            HWIO_PERIPH_FTC_0_FTC_MAX_CMP_FORCE_DB_OUT(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance, 1);
            while (0 == HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_MAX_CMP_FORCE_DB_WR_READY_BMSK))
            {
                ;
            }
        }
    }
    else
    {
        /* set_count_mode */
        HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_MODE_BMSK, 0);
        HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_SUB_MODE_BMSK,
            0 << HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_CNT_SUB_MODE_SHFT);

        /* Load the max value if specified */
        if (Config->Period > 1)
        {
            for (i=0; i<QAPI_FTC_INSTANCE_CASCADED_E; i++)
            {
                if (InstanceMask & 1 << i)
                {
                    /* set_max_cmp_function */
                    HWIO_PERIPH_FTC_0_FTC_CTRL2_OUTM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                        HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_MAX_CMP_FUNC_BMSK,
                        1 << HWIO_PERIPH_FTC_0_FTC_CTRL2_FTC_MAX_CMP_FUNC_SHFT);

                    /* set_max_cmn_cmp */
                    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
                    {
                        if (0 == i)
                        {
                            Maxval = (Config->Period - 1) & 0xFFFF;
                        }
                        else
                        {
                            Maxval = (Config->Period - 1) >> 16;
                        }
                    }
                    else
                    {
                        Maxval = Config->Period - 1;
                    }
                    HWIO_PERIPH_FTC_0_FTC_MAX_CMP_OUTM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                        HWIO_PERIPH_FTC_0_FTC_MAX_CMP_FTC_MAX_CMP_BMSK, Maxval);
                    while (0 == HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE +
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                        HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_MAX_CMP_WR_READY_BMSK))
                    {
                        ;
                    }
                    HWIO_PERIPH_FTC_0_FTC_MAX_CMP_FORCE_DB_OUT(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i, 1);
                    while (0 == HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                        HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_MAX_CMP_FORCE_DB_WR_READY_BMSK))
                    {
                        ;
                    }
                }
            }
        }
        else
        {
            return QAPI_ERR_INVALID_PARAM;
        }

        /* Set the initial value to 0 */
        if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
        {
            HWIO_PERIPH_FTC_0_FTC_CNT_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE,
                HWIO_PERIPH_FTC_0_FTC_CNT_FTC_CNT_VAL_BMSK, 0);
            
            HWIO_PERIPH_FTC_1_FTC_CNT_OUTM(PERIPH_FTC_1_FTC_1_FTC_REG_BASE,
                HWIO_PERIPH_FTC_1_FTC_CNT_FTC_CNT_VAL_BMSK, 0);
            
            HWIO_PERIPH_FTC_CMN_CNT_UPDATE_OUT(PERIPH_FTC_TOP_REG_BASE, 0x3);
            while (HWIO_PERIPH_FTC_CMN_CNT_UPDATE_READY_INM(
                PERIPH_FTC_TOP_REG_BASE, 0x3) == 0)
            {
                ;
            }
        }
        else
        {
            HWIO_PERIPH_FTC_0_FTC_CNT_OUTM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_CNT_FTC_CNT_VAL_BMSK, 0);
            
            while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CNT_WR_READY_BMSK) == 0)
            {
                ;
            }
        }

        /* set_count_down_cycles */
        HWIO_PERIPH_FTC_0_FTC_CYC_DCNT_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
            HWIO_PERIPH_FTC_0_FTC_CYC_DCNT_FTC_CYC_DCNT_NUM_BMSK,
            Config->NumCycles);
    }

    for (ChannelID=0; ChannelID<QAPI_FTC_CHANNEL_MAX_E; ChannelID++)
    {
        if (Config->OutputEnable[ChannelID])
        {
            /* set_ccp_mode */
            HWIO_PERIPH_FTC_0_FTC_CTRL3_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                HWIO_PERIPH_FTC_0_FTC_CTRL3_FTC_CH_0_CTRL_BMSK
                << (ChannelID * 4), 0x2 << (ChannelID * 4));

            /* set_cmp */
            if (Config->Pulse[ChannelID] > 0)
            {
            	if (ChannelID == QAPI_FTC_CHANNEL_0_E)
                {
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP0_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_CAP_CMP0_CAP_CMP0_VAL_BMSK,
                            Config->Pulse[ChannelID]);
                    
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP0_WR_READY_BMSK) == 0)
                    {
                        ;
                    }
                    
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_OUT(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_CAP_CMP0_FORCE_DB_BMSK);
                
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP_FORCE_DB_WR_READY_BMSK)
                        == 0)
                    {
                        ;
                    }
                }
                else if (ChannelID == QAPI_FTC_CHANNEL_1_E)
                {
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP1_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_CAP_CMP1_CAP_CMP1_VAL_BMSK,
                            Config->Pulse[ChannelID]);
                    
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP1_WR_READY_BMSK) == 0)
                    {
                        ;
                    }
                    
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_OUT(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_CAP_CMP1_FORCE_DB_BMSK);
                
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP_FORCE_DB_WR_READY_BMSK)
                        == 0)
                    {
                        ;
                    }
                }
                else //QAPI_FTC_CHANNEL_2_E
                {
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP2_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_CAP_CMP2_CAP_CMP2_VAL_BMSK,
                            Config->Pulse[ChannelID]);
                    
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                            HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP2_WR_READY_BMSK) == 0)
                    {
                        ;
                    }
                    
                    HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_OUT(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_CAP_CMP_FORCE_DB_CAP_CMP2_FORCE_DB_BMSK);
                
                    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                        PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
                        HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_CAP_CMP_FORCE_DB_WR_READY_BMSK)
                        == 0)
                    {
                        ;
                    }
                }

                Addr = PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                    + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance;
                if (ChannelID == QAPI_FTC_CHANNEL_1_E)
                {
                    Addr += (HWIO_PERIPH_FTC_0_FTC_OUT2_CTRL_ADDR(0)
                        - HWIO_PERIPH_FTC_0_FTC_OUT1_CTRL_ADDR(0));
                }
                else if (ChannelID == QAPI_FTC_CHANNEL_2_E)
                {
                    Addr += (HWIO_PERIPH_FTC_0_FTC_OUT2_CTRL_ADDR(0)
                        - HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_ADDR(0));
                }

                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUTM(Addr,
                    HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_CTRL_OP_OVFW_BMSK,
                    1 << HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_CTRL_OP_OVFW_SHFT);
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUTM(Addr,
                    HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_CTRL_OP_CH_UP_BMSK,
                    2 << HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_CTRL_OP_CH_UP_SHFT);
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUTM(Addr,
                    HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INIT_BMSK,
                    1 << HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INIT_SHFT);
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUTM(Addr,
                    HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INV_BMSK,
                    1 << HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INV_SHFT);
            }
        }
    }

    return QAPI_OK;
}

/**
   @brief Clear the FTC configuration for each instance.

   Clear the configuration of FTC module.

   @param[in] Instance_ID  FTC instance ID.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_Uninitialize(qapi_FTC_Instance_t Instance_ID)
{
    uint8_t i;
    uint32_t Cmd, InstanceMask;

    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        Cmd = 0x4040;
        InstanceMask = 0x3;
    }
    else
    {
        Cmd = 0x40 << (HWIO_PERIPH_FTC_CMN_CMD_FTC1_CMN_CMD_SHFT * Instance_ID);
        InstanceMask = 0x1 << Instance_ID;

        HWIO_PERIPH_FTC_CMN_CTRL2_OUTM(PERIPH_FTC_TOP_REG_BASE,
            HWIO_PERIPH_FTC_CMN_CTRL2_CASCADED_MODE_BMSK, 0);
    }

    for (i=0; i<QAPI_FTC_INSTANCE_CASCADED_E; i++)
    {
        if(InstanceMask & 1 << i)
        {
            /* set_ccp_mode */
            HWIO_PERIPH_FTC_0_FTC_CTRL3_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_CTRL3_RMSK, 0);
            HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INV_BMSK, 0);
            HWIO_PERIPH_FTC_0_FTC_OUT1_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INV_BMSK, 0);
            HWIO_PERIPH_FTC_0_FTC_OUT2_CTRL_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_OUT0_CTRL_OUT0_OUT_INV_BMSK, 0);

            HWIO_PERIPH_FTC_0_FTC_REGS_WR_UPDATE_OUT(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i, 1);
            while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_REGS_UPDATE_READY_BMSK)
                == 0)
            {
                ;
            }
        }
    }

    HWIO_PERIPH_FTC_CMN_CMD_OUT(PERIPH_FTC_TOP_REG_BASE, Cmd);

    while (HWIO_PERIPH_FTC_CMN_CMD_WR_READY_INM(PERIPH_FTC_TOP_REG_BASE,
        InstanceMask) == 0)
    {
        ;
    }

    return QAPI_OK;
}

/**
   @brief Enable/Disable FTC function.

   Enables/disables the output of PWM signals for a given set of channels.
   Start/stop the FTC timer function.

   @param[in] Instance_ID  FTC instance ID.
   @param[in] Enable       Start/Stop FTC function.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_Enable(qapi_FTC_Instance_t Instance_ID, qbool_t Enable)
{
    uint8_t i;
    uint32_t Cmd, InstanceMask;

    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        if (Enable == 1)
        {
            Cmd = 0x0101;
        }
        else
        {
            Cmd = 0x0202;
        }
        InstanceMask = 0x3;
    }
    else
    {
        if (Enable == 1)
        {
            Cmd = 0x01 << (HWIO_PERIPH_FTC_CMN_CMD_FTC1_CMN_CMD_SHFT * Instance_ID);
        }
        else
        {
            Cmd = 0x02 << (HWIO_PERIPH_FTC_CMN_CMD_FTC1_CMN_CMD_SHFT * Instance_ID);
        }
        InstanceMask = 0x1 << Instance_ID;
    }

    for (i=0; i<QAPI_FTC_INSTANCE_CASCADED_E; i++)
    {
        if(InstanceMask & 1 << i)
        {
            HWIO_PERIPH_FTC_0_FTC_REGS_WR_UPDATE_OUT(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i, 1);
            while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
                HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_REGS_UPDATE_READY_BMSK)
                == 0)
            {
                ;
            }
        }
    }

    HWIO_PERIPH_FTC_CMN_CMD_OUT(PERIPH_FTC_TOP_REG_BASE, Cmd);

    while (HWIO_PERIPH_FTC_CMN_CMD_WR_READY_INM(PERIPH_FTC_TOP_REG_BASE,
        InstanceMask) == 0)
    {
        ;
    }

    return QAPI_OK;
}

/**
   @brief Registers a callback for a FTC interrupt.

   Registers a callback function with the FTC interrupt controller and enables
   the interrupt.

   @param[in] Instance_ID  FTC instance ID.
   @param[in] Callback     Callback function when the interrupt occurs.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_Register_Interrupt(qapi_FTC_Instance_t Instance_ID, qapi_FTC_User_CB_t Callback)
{
    uint8_t CascadedInstance;

    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        CascadedInstance = QAPI_FTC_INSTANCE_0_E;
    }
    else
    {
        CascadedInstance = Instance_ID;
    }

    HWIO_PERIPH_FTC_0_FTC_INTR_EN_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
        HWIO_PERIPH_FTC_0_FTC_INTR_EN_CNT_OVFW_INTR_EN_BMSK, 1);

    FTC_CB_Function[CascadedInstance] = Callback;

    NVIC_EnableIRQ((IRQn_Type)(FTC0_IRQn + (IRQn_Type)CascadedInstance));

    return QAPI_OK;
}

/**
   @brief Deregisters a callback for a FTC interrupt.

   Deregisters a callback function from the FTC interrupt controller and
   disables the interrupt.

   @param[in] Instance_ID  FTC instance ID.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_Unregister_Interrupt(qapi_FTC_Instance_t Instance_ID)
{
    uint8_t CascadedInstance;

    if (Instance_ID == QAPI_FTC_INSTANCE_CASCADED_E)
    {
        CascadedInstance = QAPI_FTC_INSTANCE_0_E;
    }
    else
    {
        CascadedInstance = Instance_ID;
    }

    NVIC_DisableIRQ((IRQn_Type)(FTC0_IRQn + (IRQn_Type)CascadedInstance));

    HWIO_PERIPH_FTC_0_FTC_INTR_EN_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE
        + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * CascadedInstance,
        HWIO_PERIPH_FTC_0_FTC_INTR_EN_CNT_OVFW_INTR_EN_BMSK, 0);

    FTC_CB_Function[CascadedInstance] = NULL;

    return QAPI_OK;
}

/**
   @brief Enable/Disable FTC function.

   Enables/disables the output of FTC signals for LED.

   @param[in] Enable       Start/Stop FTC function for LED.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_FTC_LED_Enable(qbool_t Enable)
{
    uint8_t i;
    uint32_t Cmd;
    
    if (Enable == 1)
    {
        Cmd = 0x010101;
    }
    else
    {
        Cmd = 0x404040;
    }
    
    for (i=0; i<3; i++)
    {
        HWIO_PERIPH_FTC_0_FTC_REGS_WR_UPDATE_OUT(
            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i, 1);
        while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
            PERIPH_FTC_0_FTC_0_FTC_REG_BASE
            + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * i,
            HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_REGS_UPDATE_READY_BMSK)
            == 0)
        {
            ;
        }
    }
    
    HWIO_PERIPH_FTC_CMN_CMD_OUT(PERIPH_FTC_TOP_REG_BASE, Cmd);

    while (HWIO_PERIPH_FTC_CMN_CMD_WR_READY_INM(PERIPH_FTC_TOP_REG_BASE,
        0x7) == 0)
    {
        ;
    }

    return QAPI_OK;
}

/**
   @brief FTC interrupt handler.
*/
void FTC_Interrupt_Dispatch(qapi_FTC_Instance_t Instance_ID)
{
    uint32_t Stat_Reg;
    IRQn_Type IRQn = (IRQn_Type)(FTC0_IRQn + (IRQn_Type)Instance_ID);

	NVIC_DisableIRQ(IRQn);

    HWIO_PERIPH_FTC_0_FTC_REGS_RD_REQ_OUT(PERIPH_FTC_0_FTC_0_FTC_REG_BASE + 
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
                    HWIO_PERIPH_FTC_0_FTC_REGS_RD_REQ_INT_RD_REQ_BMSK);

	while (0 == HWIO_PERIPH_FTC_0_FTC_REGS_RD_READY_INM(
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE + 
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
                    HWIO_PERIPH_FTC_0_FTC_REGS_RD_READY_FTC_REGS_RD_READY_BMSK))
    {
        ;
    }

    Stat_Reg = HWIO_PERIPH_FTC_0_FTC_INTR_INM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE + 
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
                    HWIO_PERIPH_FTC_0_FTC_INTR_CNT_OVFW_INTR_BMSK);
    
    if (Stat_Reg)
    {
        FTC_CB_Function[Instance_ID](Instance_ID);
    }

    HWIO_PERIPH_FTC_0_FTC_INTR_OUTM(PERIPH_FTC_0_FTC_0_FTC_REG_BASE + 
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
                    HWIO_PERIPH_FTC_0_FTC_INTR_CNT_OVFW_INTR_BMSK,
                    HWIO_PERIPH_FTC_0_FTC_INTR_CNT_OVFW_INTR_BMSK);

    HWIO_PERIPH_FTC_0_FTC_REGS_WR_UPDATE_OUT(
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                    + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID, 1);
    while (HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_INM(
                    PERIPH_FTC_0_FTC_0_FTC_REG_BASE
                    + PERIPH_FTC_0_FTC_0_FTC_REG_BASE_SIZE * Instance_ID,
                    HWIO_PERIPH_FTC_0_FTC_REGS_WR_READY_FTC_INTR_WR_READY_BMSK)
                    == 0)
    {
        ;
    }

	NVIC_EnableIRQ(IRQn);

}

void FTC0_IntHandler(void)
{
    FTC_Interrupt_Dispatch(QAPI_FTC_INSTANCE_0_E);
}

void FTC1_IntHandler(void)
{
    FTC_Interrupt_Dispatch(QAPI_FTC_INSTANCE_1_E);
}

void FTC2_IntHandler(void)
{
    FTC_Interrupt_Dispatch(QAPI_FTC_INSTANCE_2_E);
}

void FTC3_IntHandler(void)
{
    FTC_Interrupt_Dispatch(QAPI_FTC_INSTANCE_3_E);
}


