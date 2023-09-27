/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_sense.h"
#include "qapi_power.h"
#include "qapi_task.h"
#include "qapi_mtp.h"
#include "hwio_pmu.h"
#include "hwio_aon.h"
#include "hwio_fuse.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define TEMP_SENSE_SENSING_TIMEOUT                           2000 /**< Time unit is us. */
#define TEMP_SENSE_SAMPLE_TIMES                              16  /**< Set based on conversion algorithm implementation. */

#define VOLT_SENSE_LOCK_TIMEOUT                              125 /**< Time unit is us. */
#define VOLT_SENSE_SAMPLING_TIMEOUT                          125 /**< Time unit is us. */
#define VOLT_SENSE_STARTUP_DELAY                             5   /**< Time unit is us. */
#define VOLT_SENSE_SAMPLE_TIMES                              16

/* Priority used for power callbacks. Set slightly lower than the default so
   they are called closer to the actual shutdown. */
#define SENSE_POWER_CALLBACK_PRIORITY                        (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT - 10)

/* Voltage sensor state. */
#define VOLT_SENSE_STATE_SENSOR_EN                           0x1
#define VOLT_SENSE_STATE_VBAT_MONITOR_EN                     0x2
#define VOLT_SENSE_STATE_PIO0_EN                             0x4
#define VOLT_SENSE_STATE_PIO1_EN                             0x8
#define VOLT_SENSE_STATE_PIO2_EN                             0x10
#define VOLT_SENSE_STATE_PIO3_EN                             0x20

#define VOLT_SENSE_INVALID_PIO_SOURCE                        0xFF

#define VOLT_SENSE_MUXSEL_VBAT                               1
#define VOLT_SENSE_MUXSEL_PIO0                               4
#define VOLT_SENSE_MUXSEL_GMUX7                              7

#define PMU_MUX_BUS_SEL_NANOCORE_ANA_TEST3                   15

/* Input source divider. */
#define VOLT_SENSE_VBAT_VOLTAGE_DIVIDER                      3
#define VOLT_SENSE_PIO_DIVIDER_BY2                           2
#define VOLT_SENSE_PIO_NO_DIVIDER                            1

/* LDR measurement supply sel. */
#define VOLT_SENSE_LDR_SUPPLY_SEL_PIO0                       3
#define VOLT_SENSE_LDR_SUPPLY_SEL_PIO1_2                     2

/* BIST MUX CTRL for different sources and internal pullup resistors. */
#define VOLT_SENSE_PIO0_100K                                 0x1C6
#define VOLT_SENSE_PIO0_10K                                  0x144
#define VOLT_SENSE_PIO1_100K                                 0x37
#define VOLT_SENSE_PIO1_10K                                  0x2C
#define VOLT_SENSE_PIO2_100K                                 0x187
#define VOLT_SENSE_PIO2_10K                                  0x105

#define VOLT_SENSE_CAL_GAIN                                  1110000 /**< Unit is microvolt. */
#define VOLT_SENSE_CAL_OFFSET                                90000   /**< Unit is microvolt. */
#define VOLT_SENSE_0P6V_REF                                  600000  /**< Unit is microvolt. */

#define VOLT_SENSE_VBAT_DIV_RATIO_MAIN_IN_0P1_UINT           9
#define VOLT_SENSE_VBAT_DIV_RATIO_DIVIDER                    1280

#define VOLT_SENSE_100K_STORE_IN_UNIT_2OHMS                  2
#define VOLT_SENSE_LOAD_CELL_STORE_IN_UNIT_10OHMS            10

#define HWIO_APSS_ULPBG_CTRL_ULPBG_EN_OP6REF_TEST_SHFT       4

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Structure used to specify voltage sensor parameters.
*/
typedef struct SENS_VoltSensParam_s
{
    uint8_t State;     /**< Voltage sensor state. */
    uint8_t PioSource; /**< Voltage sensor pio source selection. */
} SENS_VoltSensParam_t;

typedef struct SENS_VoltSensRetainParam_s
{
    void *PwrCallbacks; /**< Handle for the power callbacks. */
} SENS_VoltSensRetainParam_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static SENS_VoltSensParam_t       SENS_VoltSensParam;
static SENS_VoltSensRetainParam_t SENS_VoltSensRetainParam __attribute__((section (".bss.retain")));

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static int32_t SENS_ConvertCodeToCelsius(uint16_t Code);
static qbool_t SENS_Shutdown_CB(void *UserParam);
static void SENS_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Convert temperature code to 1/100th degrees Celsius.

   @param[in] Code  Temperature code in 9U4 format (code * 16).

   @return Temperature value in 1/100th degrees Celsius.
 */
static int32_t SENS_ConvertCodeToCelsius(uint16_t Code)
{
    int32_t  CodeAdj;
    int32_t  Result;
    int16_t  AdcCal;
    uint16_t Gradient;
    uint16_t QuadGradient;
    uint16_t CalTemp;

    AdcCal = (HWIO_AON_TCSR_EFUSE_SENSED_INM(HWIO_AON_TCSR_EFUSE_SENSED_TEMP_TRIM_BMSK) >> HWIO_AON_TCSR_EFUSE_SENSED_TEMP_TRIM_SHFT);
    Gradient = QAPI_MTP_APSS_RO_PTR->TsGradient;
    QuadGradient = (QAPI_MTP_APSS_RO_PTR->TsGradientQuad_Trim1Default & QAPI_MTP_TS_GRADIENT_QUAD_MASK) >> QAPI_MTP_TS_GRADIENT_QUAD_SHIFT;
    CalTemp = QAPI_MTP_APSS_RO_PTR->TsCalTemperature;

    /* Code is 9U4, convert AdcCal to same before subtraction. */
    CodeAdj = Code - (AdcCal << 4);

    /* Gradient is 1U9. Result is 9U13.  */
    Result = (Gradient * CodeAdj);

    /* CalTemp is 16U0 (although realistically will not exceed 13 bits).
       Result is 17U13. */
    Result += CalTemp << 13;

    /* 9U4 * 9U4 = 18U8 */
    CodeAdj *= CodeAdj;

    /* Convert to to 18U0 so following operation fits in 30 bits. */
    CodeAdj >>= 8;

    /* QuadGradient is -10U22, meaning only the lowest 12 fractional bits
       shall be non-zero. So, it is treated as having a bit width of
       12 for the fixed point multiplication, but the full fractional is
       shifted out afterwards to get the final integer result. */
    CodeAdj *= QuadGradient;

    /* CodeAdj is in 6U22. Convert to 6U13. */
    CodeAdj >>= 9;

    /* Subtract quadratic result from linear result. */
    Result -= CodeAdj;

    /* Convert final result to integer only portion. */
    Result >>= 13;

    return Result;
}

/**
   @brief Callback function called before the subsystem enters the shutdown
          state.

   This function is called with interrupts disabled and the interrupts must not
   be re-enabled.

   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t SENS_Shutdown_CB(void *UserParam)
{
    if (SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN)
    {
        /* Cancel the request for the VMA LDO. */
        qapi_PWR_Set_VMA_LDO(false);
    }

    return true;
}

/**
   @brief Callback function called when shutdown wakes from shutdown or a
          shutdown is aborted.

   This function is called with interrupts disabled and the interrupts must not
   be re-enabled.

   @param[in] ShutdownAborted  Flag indicating if this function is called
                               because a shutdown was aborted (true) or because
                               the subsystem woke up from shutdown (false).
   @param[in] UserParam        User specified parameter provided when the
                               callback is registered.
*/
static void SENS_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam)
{
    if ((ShutdownAborted) && (SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN))
    {
        /* Re-request the VMA LDO. */
        qapi_PWR_Set_VMA_LDO(true);
    }
}

/**
   @brief Request ADC data sampling and get data.

   @param[in]  AdcMuxSel  Select ADC's analog input.
   @param[out] AdcData    Sampled data of ADC.

   @return QAPI_OK on success, or an error code on failure.
*/
static qapi_Status_t SENS_GetAdcData(uint32_t AdcMuxSel, uint32_t *AdcData)
{
    uint32_t Start;
    uint32_t Now;
    uint32_t Sum = 0;
    uint32_t SampleTimes = 0;

    if (AdcData == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    HWIO_BIST_APSS_CONF0_OUTM(HWIO_BIST_APSS_CONF0_BIST_ADC_APSS_MUXSEL_BMSK,
                              (AdcMuxSel << HWIO_BIST_APSS_CONF0_BIST_ADC_APSS_MUXSEL_SHFT));

    while (SampleTimes < VOLT_SENSE_SAMPLE_TIMES)
    {
        /* Disable context switching while capturing timestamps for start and
           poll operations. */
        qapi_TSK_Enter_Critical();

        /* Request a data sampling. */
        HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_BIST_ADC_APSS_START_REQ_BMSK);

        /* Wait conversion done. */
        Start = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
        while (HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_BUSY_BMSK))
        {
            Now = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;

            /* Temporarily re-enable context switching to avoid blocking
               for the duration of the entire sampling event. */
            qapi_TSK_Exit_Critical();

            if (Now - Start >= VOLT_SENSE_SAMPLING_TIMEOUT)
            {
                return QAPI_ERR_TIMEOUT;
            }

            qapi_TSK_Enter_Critical();
        }

        qapi_TSK_Exit_Critical();

        Sum += (HWIO_BIST_ADC_APSS_DATA_INM(HWIO_BIST_ADC_APSS_DATA_BIST_ADC_APSS_DATA_BMSK) >> HWIO_BIST_ADC_APSS_DATA_BIST_ADC_APSS_DATA_SHFT);
        SampleTimes++;
    }

    *AdcData = (Sum / VOLT_SENSE_SAMPLE_TIMES);

    return QAPI_OK;
}

/**
   @brief Get the temperature.

   This function requests temperature sensing and returns the temperature
   in 1/100th degrees Celsius.

   @param[out] Temperature  Temperature in 1/100th degrees Celsius reported
                            by the sensor.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Temp(int32_t *Temperature)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      Start;
    uint32_t      Now;
    uint32_t      SampleTimes = 0;
    uint16_t      Sum = 0;

    if (Temperature == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* Force Temp sensor analog blcok on to save time spent on startup time from the second sensing. */
    HWIO_PMU_TS_APSS_ANA_CONF_OUTM(HWIO_PMU_TS_APSS_ANA_CONF_TS_APSS_ANA_FORCE_EN_BMSK,
                                   (0x1 << HWIO_PMU_TS_APSS_ANA_CONF_TS_APSS_ANA_FORCE_EN_SHFT));

    /* Enable CTMR. */
    HWIO_AON_CTMR_MAIN_CTRL_OUTM(HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_BMSK, (1 << HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_SHFT));

    while (SampleTimes < TEMP_SENSE_SAMPLE_TIMES)
    {
        /* Disable context switching while capturing timestamps for start and
           poll operations. */
        qapi_TSK_Enter_Critical();

        /* Request for a temperature sensing. */
        HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_TS_APSS_START_REQ_BMSK);

        /* Wait measure done. */
        Start = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
        while (HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_TS_APSS_BUSY_BMSK))
        {
            Now = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;

            /* Temporarily re-enable context switching to avoid blocking
               for the duration of the entire sampling event. */
            qapi_TSK_Exit_Critical();

            if (Now - Start >= TEMP_SENSE_SENSING_TIMEOUT)
            {
                Status = QAPI_ERR_TIMEOUT;
                goto GET_TEMP_END;
            }

            qapi_TSK_Enter_Critical();
        }

        qapi_TSK_Exit_Critical();

        Sum += (HWIO_PMU_TS_RESULT_INM(HWIO_PMU_TS_RESULT_TS_RESULT_BMSK) >> HWIO_PMU_TS_RESULT_TS_RESULT_SHFT);
        SampleTimes++;
    }

GET_TEMP_END:
    /* Release Temp sensor analog block's enable control. */
     HWIO_PMU_TS_APSS_ANA_CONF_OUTM(HWIO_PMU_TS_APSS_ANA_CONF_TS_APSS_ANA_FORCE_EN_BMSK, 0);

    if (Status == QAPI_OK)
    {
        *Temperature = SENS_ConvertCodeToCelsius(Sum);
    }

    return Status;
}

/**
   @brief Enable or disable the voltage sensor.

   This function should be called to enable the voltage sensor before other
   voltage sensor functions. It should be called to disable the voltage sensor
   if the sensor is not used any more.

   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Voltage_Sensor_Enable(qbool_t Enable)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      Start;
    uint32_t      Now;

    /* Enable sensor. */
    if (Enable)
    {
        if (SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN)
        {
            return Status;
        }

        if (SENS_VoltSensRetainParam.PwrCallbacks == NULL)
        {
            SENS_VoltSensRetainParam.PwrCallbacks = qapi_PWR_Register_Shutdown_Callbacks(SENS_Shutdown_CB, SENS_Wakeup_CB, SENSE_POWER_CALLBACK_PRIORITY, NULL);
        }

        /* turn on LDO VMA. */
        qapi_PWR_Set_VMA_LDO(true);

        /* Enable CTMR. */
        HWIO_AON_CTMR_MAIN_CTRL_OUTM(HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_BMSK, (1 << HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_SHFT));
        
        /* Disable context switching while capturing timestamps for start and
           poll operations. */
        qapi_TSK_Enter_Critical();

        /* Lock BIST ADC. */
        HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_BIST_ADC_APSS_LOCK_REQ_BMSK);
        
        /* Check if lock status is asserted. */
        Start = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
        while (!HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_LOCKED_BMSK))
        {
            Now = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;

            /* Temporarily re-enable context switching to avoid blocking
               for the duration of the entire sampling event. */
            qapi_TSK_Exit_Critical();

            if (Now - Start >= VOLT_SENSE_LOCK_TIMEOUT)
            {
                Status = QAPI_ERR_TIMEOUT;
                goto RELEASE_ADC;
            }

            qapi_TSK_Enter_Critical();
        }

        qapi_TSK_Exit_Critical();

        /* Wait BIST ADC startup delay. */
        Now = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
        while(HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN - Now < VOLT_SENSE_STARTUP_DELAY);

        SENS_VoltSensParam.State |= VOLT_SENSE_STATE_SENSOR_EN;
        SENS_VoltSensParam.PioSource = VOLT_SENSE_INVALID_PIO_SOURCE;
        return Status;
    }

    /* Disable sensor. */
    if (!(SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN))
    {
        return Status;
    }

    HWIO_APSS_ULPBG_CTRL_OUTM((1 << HWIO_APSS_ULPBG_CTRL_ULPBG_EN_OP6REF_TEST_SHFT),0);
    HWIO_BIST_MUX_BUS_SEL_OUTM(HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_BMSK,0);

    /* Turn off VBAT MON, LOAD CELL, AMUX ENABLE. */
    HWIO_BIST_APSS_CONF0_OUT(0);
    HWIO_BIST_APSS_CONF1_OUT(0);

RELEASE_ADC:
    /* Release BIST ADC. */
    HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_BIST_ADC_APSS_RELEASE_REQ_BMSK);

    /* Release LDO VMA. */
    qapi_PWR_Set_VMA_LDO(false);

    SENS_VoltSensParam.State = 0;
    SENS_VoltSensParam.PioSource = VOLT_SENSE_INVALID_PIO_SOURCE;
    return Status;
}

/**
   @brief Enable or disable the load cell for VBAT measurement.

   @param[in]  Load        Load cell selection for VBAT measurement.
   @param[in]  Enable      Set to TRUE to enable or FALSE to disable the load cell.
   @param[out] Resistance  Resistance of the selected load in Ohms.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Vbat_Load_Cell_Enable(qapi_SENS_Vbat_Load_t Load, qbool_t Enable, uint32_t *Resistance)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      StoreValue;
    
    if (Load > QAPI_SENS_VBAT_LOAD_CELL2_E || Resistance == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* If voltage sensor is not enabled, or PIO source is enabled. */
    if (!(SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN) || SENS_VoltSensParam.PioSource != VOLT_SENSE_INVALID_PIO_SOURCE)
    {
        return QAPI_ERROR;
    }

    switch(Load)
    {
        case QAPI_SENS_VBAT_LOAD_CELL1_E:
            StoreValue = QAPI_MTP_APSS_RO_PTR->VbatLoadCell1;
            break;

        case QAPI_SENS_VBAT_LOAD_CELL2_E:
            StoreValue = QAPI_MTP_APSS_RO_PTR->VbatLoadCell2;
            break;

        default:
            Status = QAPI_ERR_INVALID_PARAM;
            break;
    }

    if (Status == QAPI_OK)
    {
        HWIO_BIST_APSS_CONF0_OUTM((1 << (HWIO_BIST_APSS_CONF0_APSS_LOAD_CELL_SEL_SHFT + Load)), 
                                  (Enable ? (1 << (HWIO_BIST_APSS_CONF0_APSS_LOAD_CELL_SEL_SHFT + Load)) : 0));
        *Resistance = StoreValue * VOLT_SENSE_LOAD_CELL_STORE_IN_UNIT_10OHMS;
    }

    return QAPI_OK;
}

/**
   @brief Enable or disable the VBAT monitor.

   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Vbat_Monitor_Enable(qbool_t Enable)
{
    /* If voltage sensor is not enabled, or PIO source is enabled. */
    if (!(SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN) || SENS_VoltSensParam.PioSource != VOLT_SENSE_INVALID_PIO_SOURCE)
    {
        return QAPI_ERROR;
    }

    if (Enable && !(SENS_VoltSensParam.State & VOLT_SENSE_STATE_VBAT_MONITOR_EN))
    {
        /* Enable VBAT monitor. */
        HWIO_BIST_APSS_CONF0_OUTM(HWIO_BIST_APSS_CONF0_APSS_VBAT_MON_EN_BMSK,
                                  (1 << HWIO_BIST_APSS_CONF0_APSS_VBAT_MON_EN_SHFT));
        /* Route buffered 0.6V ref to nanocore_ana_test<3>. */
        HWIO_APSS_ULPBG_CTRL_OUTM((1 << HWIO_APSS_ULPBG_CTRL_ULPBG_EN_OP6REF_TEST_SHFT),
                                  (1 << HWIO_APSS_ULPBG_CTRL_ULPBG_EN_OP6REF_TEST_SHFT));
        /* Connect 0.6V buffer to gmux7. */
        HWIO_BIST_MUX_BUS_SEL_OUTM(HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_BMSK,
                                   (PMU_MUX_BUS_SEL_NANOCORE_ANA_TEST3 << HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_SHFT));

        SENS_VoltSensParam.State |= VOLT_SENSE_STATE_VBAT_MONITOR_EN;
    }
    else if (!Enable && (SENS_VoltSensParam.State & VOLT_SENSE_STATE_VBAT_MONITOR_EN))
    {
        HWIO_APSS_ULPBG_CTRL_OUTM((1 << HWIO_APSS_ULPBG_CTRL_ULPBG_EN_OP6REF_TEST_SHFT),0);
        HWIO_BIST_MUX_BUS_SEL_OUTM(HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_BMSK,0);
        HWIO_BIST_APSS_CONF0_OUTM(HWIO_BIST_APSS_CONF0_APSS_VBAT_MON_EN_BMSK, 0);

        SENS_VoltSensParam.State &= ~VOLT_SENSE_STATE_VBAT_MONITOR_EN;
    }

    return QAPI_OK;
}

/**
   @brief Enable or disable the PIO switch for a specified PIO source.

   The related PIO should be configured to be an input and the pulls are
   disabled, prior to enabling its PIO switch.

   The PIO source can be selected based on the PIO input voltage range or
   PIO usage. If the:
   - Input PIO voltage is 1.8&nbsp;V ~ 3.6&nbsp;V -- an enumerator
   QAPI_SENS_PIO_SOURCE_PIO[X]_DIVIDE_BY2_E must be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_DIVIDE_BY2_E).
   - Input PIO voltage is 0&nbsp;V ~ 1.8&nbsp;V -- an enumerator 
   QAPI_SENS_PIO_SOURCE_PIO[X]_NO_DIVIDE_E can be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_NO_DIVIDE_E).
   - PIO usage is to measure external load like LDR -- 
   QAPI_SENS_PIO_SOURCE_PIO[X]_PULLUP_[X]K_E can be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E).

   @param[in] Source  The input PIO source.
   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Pio_Switch_Enable(qapi_SENS_PIO_Source_t Source, qbool_t Enable)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      BistMux;
    uint32_t      LdrSupplySel;
    uint8_t       PioEnBit;

    if (Source > QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_10K_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* If voltage sensor is not enabled, or vbat / another PIO source is enabled. */
    if (!(SENS_VoltSensParam.State & VOLT_SENSE_STATE_SENSOR_EN) || (SENS_VoltSensParam.State & VOLT_SENSE_STATE_VBAT_MONITOR_EN) ||
        (SENS_VoltSensParam.PioSource != VOLT_SENSE_INVALID_PIO_SOURCE && SENS_VoltSensParam.PioSource != Source))
    {
        return QAPI_ERROR;
    }

    if ((Enable && SENS_VoltSensParam.PioSource == Source) || (!Enable && SENS_VoltSensParam.PioSource == VOLT_SENSE_INVALID_PIO_SOURCE))
    {
        return QAPI_OK;
    }
    
    if (Source <= QAPI_SENS_PIO_SOURCE_PIO3_DIVIDE_BY2_E)
    {
        PioEnBit = Source - QAPI_SENS_PIO_SOURCE_PIO0_DIVIDE_BY2_E;
        HWIO_BIST_APSS_CONF0_OUTM(HWIO_BIST_APSS_CONF0_BIST_APSS_PIO_AMUX_EN_BMSK,
                                  (Enable ? (1 << (HWIO_BIST_APSS_CONF0_BIST_APSS_PIO_AMUX_EN_SHFT + PioEnBit)) : 0));
        
    }
    else if (Source <= QAPI_SENS_PIO_SOURCE_PIO2_NO_DIVIDE_E)
    {
        PioEnBit = Source - QAPI_SENS_PIO_SOURCE_PIO0_NO_DIVIDE_E;
        HWIO_BIST_APSS_CONF0_OUTM(HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_BMSK,
                                  (Enable ? (1 << (HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_SHFT + PioEnBit)) : 0));
    }
    else
    {
        switch (Source)
        {
            case QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E:
                BistMux = VOLT_SENSE_PIO0_100K;
                break;

            case QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_10K_E:
                BistMux = VOLT_SENSE_PIO0_10K;
                break;

            case QAPI_SENS_PIO_SOURCE_PIO1_PULLUP_100K_E:
                BistMux = VOLT_SENSE_PIO1_100K;
                break;

            case QAPI_SENS_PIO_SOURCE_PIO1_PULLUP_10K_E:
                BistMux = VOLT_SENSE_PIO1_10K;
                break;

            case QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_100K_E:
                BistMux = VOLT_SENSE_PIO2_100K;
                break;

            case QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_10K_E:
                BistMux = VOLT_SENSE_PIO2_10K;
                break;

            default:
                Status = QAPI_ERR_INVALID_PARAM;
                break;
        }

        if (Status == QAPI_OK)
        {
            /* Select internal supply. */
            if (Source <= QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_10K_E)
            {
                LdrSupplySel = VOLT_SENSE_LDR_SUPPLY_SEL_PIO0;
            }
            else
            {
                LdrSupplySel = VOLT_SENSE_LDR_SUPPLY_SEL_PIO1_2;
            }
            PioEnBit = (Source - QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E) / 2;

            if (Enable)
            {
                HWIO_BIST_APSS_CONF0_OUTM((HWIO_BIST_APSS_CONF0_APSS_LDR_MEAS_SUPPLY_SEL_BMSK |
                                          HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_BMSK),
                                          ((LdrSupplySel << HWIO_BIST_APSS_CONF0_APSS_LDR_MEAS_SUPPLY_SEL_SHFT) |
                                          (1 << (HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_SHFT + PioEnBit))));
                
                HWIO_BIST_APSS_CONF1_OUTM(HWIO_BIST_APSS_CONF1_BIST_APSS_BIST_MUX_CTRL_BMSK,
                                          (BistMux << HWIO_BIST_APSS_CONF1_BIST_APSS_BIST_MUX_CTRL_SHFT));
            }
            else
            {
                HWIO_BIST_APSS_CONF0_OUTM((HWIO_BIST_APSS_CONF0_APSS_LDR_MEAS_SUPPLY_SEL_BMSK |
                                           HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_BMSK), 0);
                
                HWIO_BIST_APSS_CONF1_OUTM(HWIO_BIST_APSS_CONF1_BIST_APSS_BIST_MUX_CTRL_BMSK, 0);
            }
        }
    }

    if (Status == QAPI_OK)
    {
        if (Enable)
        {
            SENS_VoltSensParam.PioSource = Source;
            SENS_VoltSensParam.State |= (VOLT_SENSE_STATE_PIO0_EN << PioEnBit);
        }
        else
        {
            SENS_VoltSensParam.PioSource = VOLT_SENSE_INVALID_PIO_SOURCE;
            SENS_VoltSensParam.State &= ~(VOLT_SENSE_STATE_PIO0_EN << PioEnBit);
        }
    }

    return Status;
}

/**
   @brief Gets the voltage of the specified input source.

   This function requests voltage measurement of the selected source and returns
   the voltage. The input source should be enabled before
   getting the voltage using this function.

   @param[in]  Source   The input source for the sensor to measure the voltage.
   @param[out] Voltage  The measured voltage of the selected input source in
                        microvolts (1e-6).

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Voltage(qapi_SENS_Voltage_Source_t Source, uint32_t *Voltage)
{
    qapi_Status_t Status;
    uint32_t      AdcMuxSel;
    uint32_t      Divider;
    int32_t       CalVolt;
    uint32_t      AdcLow;
    uint32_t      AdcHigh;
    uint32_t      Adc0d6;
    uint32_t      AdcResult;
    uint32_t      DivRatio;

    if (Source > QAPI_SENS_VOLTAGE_SOURCE_PIO3_E || Voltage == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* Check if source is enabled. */
    if (!(SENS_VoltSensParam.State & (VOLT_SENSE_STATE_VBAT_MONITOR_EN << Source)))
    {
        return QAPI_ERROR;
    }

    if (Source == QAPI_SENS_VOLTAGE_SOURCE_VBAT_E)
    {
        /* Data sample for 0.6V reference. */
        Status = SENS_GetAdcData(VOLT_SENSE_MUXSEL_GMUX7, &Adc0d6);
        if (Status != QAPI_OK)
        {
            return Status;
        }
        
        /* Select VBAT as ADC's analog input. */
        AdcMuxSel = VOLT_SENSE_MUXSEL_VBAT;
    }
    else
    {
        /* Select PIO[X] as ADC's analog input. */
        AdcMuxSel = VOLT_SENSE_MUXSEL_PIO0 + (Source - QAPI_SENS_VOLTAGE_SOURCE_PIO0_E);
        if (SENS_VoltSensParam.PioSource <= QAPI_SENS_PIO_SOURCE_PIO3_DIVIDE_BY2_E)
        {
            Divider = VOLT_SENSE_PIO_DIVIDER_BY2;
        }
        else
        {
            Divider = VOLT_SENSE_PIO_NO_DIVIDER;
        }
    }

    /* Data sample. */
    Status = SENS_GetAdcData(AdcMuxSel, &AdcResult);
    if (Status == QAPI_OK)
    {
        if (Source == QAPI_SENS_VOLTAGE_SOURCE_VBAT_E)
        {
            DivRatio = QAPI_MTP_APSS_RO_PTR->VbatSenseRatio;
            *Voltage = VOLT_SENSE_VBAT_VOLTAGE_DIVIDER * (VOLT_SENSE_0P6V_REF * VOLT_SENSE_VBAT_DIV_RATIO_MAIN_IN_0P1_UINT / 10 + VOLT_SENSE_0P6V_REF * DivRatio / VOLT_SENSE_VBAT_DIV_RATIO_DIVIDER) * AdcResult / Adc0d6;
        }
        else
        {
            AdcLow = QAPI_MTP_APSS_RO_PTR->BistAdcLow;
            AdcHigh = QAPI_MTP_APSS_RO_PTR->BistAdcHigh; 
            CalVolt = (int32_t)(AdcResult - AdcLow) * VOLT_SENSE_CAL_GAIN / (int32_t)(AdcHigh - AdcLow) + VOLT_SENSE_CAL_OFFSET;
            if (CalVolt < 0)
            {
                CalVolt = 0;
            }
            
            *Voltage = CalVolt * Divider;
        }
    }

    return Status;
}

/**
   @brief Gets the resistance of internal pull up resistor.

   @param[in]  Resistor    Specify the internal pull up resistor.
   @param[out] Resistance  Resistance of the selected internal resistor in Ohms.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Pullup_Resistance(qapi_SENS_Pullup_Resistor_t Resistor, uint32_t *Resistance)
{
    qapi_Status_t Status = QAPI_OK;
    
    if (Resistance == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    switch(Resistor)
    {
        case QAPI_SENS_PULLUP_RESISTOR_100K_E:
            *Resistance = VOLT_SENSE_100K_STORE_IN_UNIT_2OHMS * QAPI_MTP_APSS_RO_PTR->BistMux100k;
            break;

        case QAPI_SENS_PULLUP_RESISTOR_10K_E:
            *Resistance = QAPI_MTP_APSS_RO_PTR->BistMux10k;
            break;

        default:
            Status = QAPI_ERR_INVALID_PARAM;
            break;
    }

    return Status;
}

