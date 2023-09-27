/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include "qcc710.h"
#include "core_cm3.h"
#include "HALhwio.h"
#include "hwio_tlmm.h"
#include "qapi_gpio.h"
#include "qapi_heap.h"
#include "qapi_timer.h"
#include "hwio_aon.h"
#include "qapi_fuse.h"
#include "qapi_mtp.h"
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
/**
   @brief Point of GPIO callback function structure.
*/
qapi_GPIO_CB_List_t *GPIO_CB_Function = NULL;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Changes the SoC PIO configuration.

   This Function configures an SoC PIO based on a set of fields specified in
   the configuration structure reference passed in as a parameter.

   @param[in] GPIO_ID           GPIO number.
   @param[in] qapi_GPIO_Config  PIO configuration to use.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *qapi_GPIO_Config)
{
    uint8_t pull;

    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (qapi_GPIO_Config == NULL))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (qapi_GPIO_Config->Pull == QAPI_GPIO_PULL_UP_E)
    {
        pull = QAPI_GPIO_PULL_UP_E + 1;
    }
    else
    {
        pull = qapi_GPIO_Config->Pull;
    }

    qapi_TSK_Enter_Critical();    
    HWIO_TLMM_GPIO_CFGm_OUTI(GPIO_ID, (qapi_GPIO_Config->PIOFunc
                            << HWIO_TLMM_GPIO_CFGm_FUNC_SEL_SHFT)
                            | (pull << HWIO_TLMM_GPIO_CFGm_GPIO_PULL_SHFT)
                            | (qapi_GPIO_Config->Drive
                            << HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_SHFT));

    HWIO_TLMM_GPIO_OE_OUTM(0x1 << GPIO_ID, qapi_GPIO_Config->Dir << GPIO_ID);
    qapi_TSK_Exit_Critical();    

    return QAPI_OK;
}

/**
   @brief Sets the state of an SoC PIO configured as an output GPIO.

   This Function Drives the output of an SoC PIO that has been configured as a
   generic output GPIO to a specified value.

   @param[in] GPIO_ID   GPIO number.
   @param[in] Value     Output value.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Set(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Value_t Value)
{
    if (GPIO_ID > QAPI_GPIO_ID25_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    qapi_TSK_Enter_Critical();    
    if (Value == QAPI_GPIO_HIGH_VALUE_E)
    {
        HWIO_TLMM_GPIO_OUT_OUTM(0x01 << GPIO_ID, 0x01 << GPIO_ID);
    }
    else
    {
        HWIO_TLMM_GPIO_OUT_OUTM(0x01 << GPIO_ID, 0x00 << GPIO_ID);
    }
    qapi_TSK_Exit_Critical();    

  return (QAPI_OK);
}

/**
   @brief Reads the state of an SoC PIO.

   @param[in]  GPIO_ID  GPIO number.
   @param[out] Value    Input value.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Get(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Value_t *Value)
{
    uint32_t  output;

    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (Value == NULL))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    output = HWIO_TLMM_GPIO_IN_INM(0x01 << GPIO_ID);

    if (output)
    {
        *Value = QAPI_GPIO_HIGH_VALUE_E;
    }
    else
    {
        *Value = QAPI_GPIO_LOW_VALUE_E;
    }

    return (QAPI_OK);
}

/**
   @brief Registers a callback for a GPIO interrupt.

   Registers a callback Function with the GPIO interrupt controller and enables
   the interrupt. This Function configures and routes the interrupt accordingly,
   as well as enabling it in the underlying layers.

   @param[in] GPIO_ID   GPIO number.
   @param[in] Trigger   Trigger type for the interrupt.
   @param[in] Callback  Callback Function pointer.
   @param[in] Data      Callback data.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Enable_Interrupt(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Trigger_t Trigger, qapi_GPIO_CB_t Callback, qapi_GPIO_CB_Data_t Data)
{
    uint32_t  Value;
    qbool_t   Found;
    qapi_GPIO_CB_List_t *Point;
    qapi_GPIO_CB_List_t *CB_Function;

    if (GPIO_ID > QAPI_GPIO_ID25_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (Trigger == QAPI_GPIO_TRIGGER_EDGE_RISING_E)
    {
        HWIO_APPSS_INT_SEL_DUAL_STAT_OUTM(0x01 << GPIO_ID, 0x00 << GPIO_ID);
        HWIO_APPSS_INT_SEL_RISE_FALL_STAT_OUTM(0x01 << GPIO_ID, 0x00 << GPIO_ID);
    }
    else if (Trigger == QAPI_GPIO_TRIGGER_EDGE_FALLING_E)
    {
        HWIO_APPSS_INT_SEL_DUAL_STAT_OUTM(0x01 << GPIO_ID, 0x00 << GPIO_ID);
        HWIO_APPSS_INT_SEL_RISE_FALL_STAT_OUTM(0x01 << GPIO_ID, 0x01 << GPIO_ID);
    }
    else if (Trigger == QAPI_GPIO_TRIGGER_EDGE_DUAL_E)
    {
        HWIO_APPSS_INT_SEL_DUAL_STAT_OUTM(0x01 << GPIO_ID, 0x01 << GPIO_ID);
    }
    else
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Found = 0;
    Point = GPIO_CB_Function;
    while (Point != NULL)
    {
        if (Point->GPIO_ID == GPIO_ID)
        {
            Point->Func = Callback;
            Point->Data = Data;
            Found = 1;
            break;
        }

        Point = Point->Next;
    }

    if (Found == 0)
    {
        CB_Function = (qapi_GPIO_CB_List_t *)qapi_Malloc(sizeof(qapi_GPIO_CB_List_t));
        if (CB_Function == NULL)
        {
            return QAPI_ERR_NO_MEMORY;
        }
        CB_Function->GPIO_ID = GPIO_ID;
        CB_Function->Func = Callback;
        CB_Function->Data = Data;
        CB_Function->Next = GPIO_CB_Function;
        GPIO_CB_Function = CB_Function;
    }

    Value = HWIO_APPSS_MASK_INM(HWIO_APPSS_MASK_INTERRUPT_BMSK);
    Value &= ~(0x01 << GPIO_ID);
    HWIO_APPSS_MASK_OUTM(HWIO_APPSS_MASK_INTERRUPT_BMSK, Value);

    return QAPI_OK;
}

/**
   @brief Deregisters a callback for a GPIO interrupt.

   Deregisters a callback Function from the GPIO interrupt controller and
   disables the interrupt. This Function deconfigures the interrupt
   accordingly, as well as disabling it in the underlying layers.

   @param[in] GPIO_ID  GPIO number.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Disable_Interrupt(qapi_GPIO_Id_t GPIO_ID)
{
    uint32_t  Value;

    if (GPIO_ID > QAPI_GPIO_ID25_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }
    Value = HWIO_APPSS_MASK_INM(HWIO_APPSS_MASK_INTERRUPT_BMSK);
    Value |= 0x01 << GPIO_ID;
    HWIO_APPSS_MASK_OUTM(HWIO_APPSS_MASK_INTERRUPT_BMSK, Value);
    qapi_GPIO_CB_List_t  *Point;
    qapi_GPIO_CB_List_t  *Point_Prev;
    qapi_GPIO_CB_List_t  *Point_Next;

    if (GPIO_CB_Function == NULL)
    {
        return QAPI_ERROR;
    }
    else
    {
        if (GPIO_CB_Function->GPIO_ID == GPIO_ID)
        {
            Point = GPIO_CB_Function->Next;
            qapi_Free(GPIO_CB_Function);
            GPIO_CB_Function = Point;

            return QAPI_OK;
        }
        Point_Prev = GPIO_CB_Function;
        Point = GPIO_CB_Function->Next;
    }

    while (Point != NULL)
    {
        Point_Next = Point->Next;

        if (Point->GPIO_ID == GPIO_ID)
        {
            qapi_Free(Point);
            Point_Prev->Next = Point_Next;

            return QAPI_OK;
        }

        Point_Prev = Point;
        Point = Point_Next;
    }

    return QAPI_ERROR;
}

/**
   @brief GPIO interrupt handler.
*/
void GPIO_IntHandler(void)
{
    uint8_t GPIO_ID;
    uint32_t Sum_Reg, Stat_Reg;
    qapi_GPIO_CB_t Callback;
    qapi_GPIO_CB_Data_t Data;
    qapi_GPIO_CB_List_t *Point;

    NVIC_DisableIRQ(GPIO_IRQn);

    Sum_Reg = HWIO_APPSS_SUM_INM(HWIO_APPSS_SUM_INTERRUPT_BMSK);

    if (Sum_Reg)
    {
        Stat_Reg = HWIO_APPSS_STAT_INM(HWIO_APPSS_STAT_INTERRUPT_BMSK);

        for (GPIO_ID=0; GPIO_ID<QAPI_GPIO_MAX_ID_E; GPIO_ID++)
        {
            if (Stat_Reg & 0x01<<GPIO_ID)
            {
                HWIO_APPSS_CLR_OUT(0x01<<GPIO_ID);

                Point = GPIO_CB_Function;
                while (Point != NULL)
                {
                    if (Point->GPIO_ID == GPIO_ID)
                    {
                        Callback = Point->Func;
                        Data = Point->Data;
                        Callback(Data);
                        break;
                    }

                    Point = Point->Next;
                }
            }
        }
    }

    NVIC_EnableIRQ(GPIO_IRQn);
}

/**
   @brief Registers a callback for a GPIO interrupt in deep sleep mode.

   Registers a callback Function with the GPIO interrupt controller and enables
   the interrupt in deep sleep mode. This Function configures and routes the
   interrupt accordingly, as well as enabling it in the underlying layers.

   @param[in] GPIO_ID   GPIO number.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Enable_Sleep_Interrupt(qapi_GPIO_Id_t GPIO_ID)
{
    uint32_t  value;
    uint32_t Rise_Status, Fall_Status;

    if (GPIO_ID > QAPI_GPIO_ID25_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* Configure GPIO IS Field. */
    HWIO_TLMM_GPIO_CFGm_OUTMI(GPIO_ID, HWIO_TLMM_GPIO_CFGm_IS_BMSK, HWIO_TLMM_GPIO_CFGm_IS_BMSK);

    /* Configure TAD block */
    /* Enable the mask bit for the required GPIO */
    value = HWIO_TAD_SUM_INT_INM(HWIO_TAD_SUM_INT_MASK_BMSK);
    value |= 0x01 << GPIO_ID;
    HWIO_TAD_SUM_INT_OUTM(HWIO_TAD_SUM_INT_MASK_BMSK, value);

    /* Clear TAD interrupts */
    qapi_GPIO_Clear_Sleep_Interrupt_Status(GPIO_ID);

    /* make sure that you read Zeros in both TAD_RISE and TAD_FALL. */
    Rise_Status = HWIO_TAD_RISE_INM(0x01 << GPIO_ID);
    Fall_Status = HWIO_TAD_FALL_INM(0x01 << GPIO_ID);
    if ((Rise_Status !=0 ) || (Fall_Status != 0))
    {
        return QAPI_ERROR;
    }

    return QAPI_OK;
}

/**
   @brief Deregisters a callback for a GPIO interrupt in deep sleep mode.

   Deregisters a callback Function from the GPIO interrupt controller and
   disables the interrupt in deep sleep mode. This Function deconfigures the
   interrupt accordingly, as well as disabling it in the underlying layers.

   @param[in] GPIO_ID  GPIO number.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Disable_Sleep_Interrupt(qapi_GPIO_Id_t GPIO_ID)
{
    uint32_t  value;

    if (GPIO_ID > QAPI_GPIO_ID25_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    value = HWIO_TAD_SUM_INT_INM(HWIO_TAD_SUM_INT_MASK_BMSK);
    value &= ~(0x01 << GPIO_ID);
    HWIO_TAD_SUM_INT_OUTM(HWIO_TAD_SUM_INT_MASK_BMSK, value);

    /* Make sure the interrupt is cleared. */
    qapi_GPIO_Clear_Sleep_Interrupt_Status(GPIO_ID);

    return QAPI_OK;
}

/**
   @brief Clear sleep interrupt status.

   Each processor should clear the status of its own pre-configured GPIO after
   sleep interrupt happened.

   @param[in] GPIO_ID  GPIO number.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Clear_Sleep_Interrupt_Status(qapi_GPIO_Id_t GPIO_ID)
{
    HWIO_TAD_INT_OUTM(0x01 << GPIO_ID, 0x01 << GPIO_ID);
    qapi_TMR_Delay_Us(100);
    HWIO_TAD_INT_OUTM(0x01 << GPIO_ID, 0);

    return QAPI_OK;
}

/**
   @brief Get sleep interrupt status.

   Get sleep interrupt status, it shows triggled by rising or failing signal
   from GPIO input.

   @param[in]   GPIO_ID  GPIO number.
   @param[out]  Status   Interrupt status. 0:fall, 1:rise, 2:both,.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Get_Sleep_Interrupt_Status(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Sleep_Trigger_t *Status)
{
    uint32_t Rise_Status, Fall_Status;

    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (Status == NULL))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Rise_Status = HWIO_TAD_RISE_INM(0x01 << GPIO_ID);
    Fall_Status = HWIO_TAD_FALL_INM(0x01 << GPIO_ID);

    if (Rise_Status && Fall_Status)
    {
        *Status = QAPI_GPIO_SLEEP_TRIGGER_EDGE_DUAL_E;
    }
    else if (Rise_Status)
    {
        *Status = QAPI_GPIO_SLEEP_TRIGGER_EDGE_RISING_E;
    }
    else if (Fall_Status)
    {
        *Status = QAPI_GPIO_SLEEP_TRIGGER_EDGE_FALLING_E;
    }
    else
    {
        return QAPI_ERROR;
    }

    return QAPI_OK;
}

/**
   @brief Change the mapping of serial engine interface.

   Control the 5*5 mus in front of each Serial engine interface,
   to give flexipilty to serial engine PIO mapping on PADs.

   @param[in]   SE_ID    Serial Engine number.
   @param[in]   GPIO_ID  GPIO number.
   @param[in]   SE_PORT  Serial Engine port number.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Port_Mapping(uint8_t SE_ID, qapi_GPIO_Id_t GPIO_ID, SE_PORT_t SE_PORT)
{
    uint8_t OUT_PORT;
    uint8_t SE_ORIG_PORT;
    uint32_t Value;

    SE_ORIG_PORT = SE_PORT & 0x7; /* low 3 bits */
    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (SE_ID > 3) || (SE_ORIG_PORT > 4))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (SE_PORT == SE_PORT_DEFAULT)
    {
        /* restore to default mapping */
        switch (SE_ID)
        {
            case 0:
                Value = HWIO_SERIAL_ENGINE_0_1_INM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_BMSK);
                Value &= ~0x7FFF;
                Value |= 0x4688;
                HWIO_SERIAL_ENGINE_0_1_OUTM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_BMSK, Value);
                break;
            case 1:
                Value = HWIO_SERIAL_ENGINE_0_1_INM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_BMSK);
                Value &= ~0x3FFF8000;
                Value |= 0x23440000;
                HWIO_SERIAL_ENGINE_0_1_OUTM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_BMSK, Value);
                break;
            case 2:
                Value = HWIO_SERIAL_ENGINE_2_3_INM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_BMSK);
                Value &= ~0x7FFF;
                Value |= 0x4688;
                HWIO_SERIAL_ENGINE_2_3_OUTM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_BMSK, Value);
                break;
            case 3:
                Value = HWIO_SERIAL_ENGINE_2_3_INM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_BMSK);
                Value &= ~0x3FFF8000;
                Value |= 0x23440000;
                HWIO_SERIAL_ENGINE_2_3_OUTM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_BMSK, Value);
                break;
        }
        return QAPI_OK;
    }

    if (SE_ID == 0)
    {
        if (GPIO_ID < 4)
        {
            OUT_PORT = GPIO_ID;
        }
        else if (GPIO_ID < 9)
        {
            OUT_PORT = (GPIO_ID + 1) % 5;
        }
        else
        {
            OUT_PORT = (GPIO_ID - 1) % 5;
        }
    }
    else if (SE_ID == 1)
    {
        if (GPIO_ID < 15)
        {
            OUT_PORT = GPIO_ID % 5;
        }
        else
        {
            OUT_PORT = (GPIO_ID - 1) % 5;
        }
    }
    else
    {
        if (GPIO_ID < 20)
        {
            OUT_PORT = GPIO_ID % 5;
        }
        else
        {
            OUT_PORT = (GPIO_ID - 1) % 5;
        }
    }

    switch (SE_ID)
    {
        case 0:
            Value = HWIO_SERIAL_ENGINE_0_1_INM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_BMSK);
            Value &= ~(0x7 << (OUT_PORT * 3));
            Value |= SE_ORIG_PORT << (OUT_PORT * 3);
            HWIO_SERIAL_ENGINE_0_1_OUTM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_BMSK, Value);
            break;
        case 1:
            Value = HWIO_SERIAL_ENGINE_0_1_INM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_BMSK);
            Value &= ~(0x7 << (OUT_PORT * 3 + HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_SHFT));
            Value |= SE_ORIG_PORT << (OUT_PORT * 3 + HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_SHFT);
            HWIO_SERIAL_ENGINE_0_1_OUTM(HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_BMSK, Value);
            break;
        case 2:
            Value = HWIO_SERIAL_ENGINE_2_3_INM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_BMSK);
            Value &= ~(0x7 << (OUT_PORT * 3));
            Value |= SE_ORIG_PORT << (OUT_PORT * 3);
            HWIO_SERIAL_ENGINE_2_3_OUTM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_BMSK, Value);
            break;
        case 3:
            Value = HWIO_SERIAL_ENGINE_2_3_INM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_BMSK);
            Value &= ~(0x7 << (OUT_PORT * 3 + HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_SHFT));
            Value |= SE_ORIG_PORT << (OUT_PORT * 3 + HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_SHFT);
            HWIO_SERIAL_ENGINE_2_3_OUTM(HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_BMSK, Value);
            break;
    }

    return QAPI_OK;
}

/**
   @brief Initialize GPIO configuration.

   Initialize GPIO global parameters. Open CPU interrupt for the GPIO module.
   Apply the alternative GPIO configuration to GPIO register. If do not need,
   set NULL to parameter.

   @param[in]   AltConfig  Alternative PIO configuration table.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Initialize(qapi_GPIO_Alt_Config_t *AltConfig)
{
    qapi_Status_t Status;
    uint8_t SE_ID;
    SE_PORT_t SE_PORT;
    qapi_GPIO_Id_t  GPIO_ID;
    qapi_GPIO_Config_t Config;

    GPIO_CB_Function = NULL;
    NVIC_EnableIRQ(GPIO_IRQn);

    if (AltConfig == NULL)
    {
        return QAPI_OK;
    }

    for (GPIO_ID = QAPI_GPIO_ID0_E; GPIO_ID < QAPI_GPIO_MAX_ID_E; GPIO_ID++)
    {
        SE_ID = 0xFF;

        SE_PORT = (SE_PORT_t)AltConfig[GPIO_ID].se_port;

        if (AltConfig[GPIO_ID].PIOFunc == 1)
        {
            SE_ID = 0;
        }
        else if (AltConfig[GPIO_ID].PIOFunc == 2)
        {
            SE_ID = 2;
        }
        else if (AltConfig[GPIO_ID].PIOFunc == 3)
        {
            SE_ID = 1;
        }
        else if (AltConfig[GPIO_ID].PIOFunc == 4)
        {
            SE_ID = 3;
        }

        if (SE_ID != 0xFF)
        {
            Status = qapi_GPIO_Port_Mapping(SE_ID, GPIO_ID, SE_PORT);
            if (Status != QAPI_OK)
            {
                return Status;
            }
        }

        Config.PIOFunc = AltConfig[GPIO_ID].PIOFunc;
        Config.Dir = (qapi_GPIO_Direction_t)AltConfig[GPIO_ID].Dir;
        Config.Pull = (qapi_GPIO_Pull_t)AltConfig[GPIO_ID].Pull;
        Config.Drive = (qapi_GPIO_Drive_t)AltConfig[GPIO_ID].Drive;
        Status = qapi_GPIO_Config(GPIO_ID, &Config);
        if (Status != QAPI_OK)
        {
            return Status;
        }
    }

    return QAPI_OK;
}

/**
   @brief Enable/Disable debugger function.

   When disable debugger function, GPIO9,10,11,12 can be used as alternate functions.
   Otherwise they will be either mapped to SWD or JTAG according to the state of
   the chip. Default value is enabled.

   @param[in] Enable  Enable/Disable JTAG function.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Debugger_Enable(qbool_t Enable)
{
    if (Enable)
    {
        HWIO_JTAG_MUX_CTRL_OUTM(
            HWIO_JTAG_MUX_CTRL_SWD_LOCK_NO_SCAN_BMSK 
            | HWIO_JTAG_MUX_CTRL_DFLT_JTAG_DISABLE_NO_SCAN_BMSK,
            HWIO_JTAG_MUX_CTRL_SWD_LOCK_NO_SCAN_BMSK);
    }
    else
    {
        HWIO_JTAG_MUX_CTRL_OUTM(
            HWIO_JTAG_MUX_CTRL_SWD_LOCK_NO_SCAN_BMSK 
            | HWIO_JTAG_MUX_CTRL_DFLT_JTAG_DISABLE_NO_SCAN_BMSK,
            HWIO_JTAG_MUX_CTRL_DFLT_JTAG_DISABLE_NO_SCAN_BMSK);
    }

    return QAPI_OK;
}

/**
   @brief Set GPIO configuration to MTP.

   Set the GPIO configuration to MTP, this function do not update GPIO
   registers.

   @param[in] GPIO_ID           GPIO number.
   @param[in] qapi_GPIO_Config  Pin configuration to use.
   @param[in] Value             Output value.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Set_MTP_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *qapi_GPIO_Config, qapi_GPIO_Value_t Value)
{
    qapi_Status_t  Status;
    uint32_t       MTP_GPIO_Config_Value;
    uint32_t       MTP_GPIO_OE_Value;
    uint32_t       MTP_GPIO_Out_Value;
    uint8_t        Pull;
    uint32_t       Address, Config_Value;

    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (qapi_GPIO_Config == NULL))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (qapi_GPIO_Config->Pull == QAPI_GPIO_PULL_UP_E)
    {
        Pull = QAPI_GPIO_PULL_UP_E + 1;
    }
    else
    {
        Pull = qapi_GPIO_Config->Pull;
    }

    Status = qapi_Fuse_Read((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOe,
                            &MTP_GPIO_OE_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = qapi_Fuse_Read((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOut,
                            &MTP_GPIO_Out_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    MTP_GPIO_Config_Value = (qapi_GPIO_Config->PIOFunc 
                            << HWIO_TLMM_GPIO_CFGm_FUNC_SEL_SHFT)
                            | (Pull << HWIO_TLMM_GPIO_CFGm_GPIO_PULL_SHFT)
                            | (qapi_GPIO_Config->Drive
                            << HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_SHFT);
    Address = (uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioCfg[GPIO_ID / 2 * 2];
    Status = qapi_Fuse_Read(Address, &Config_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    if ((GPIO_ID % 2) == 0)
    {
        Config_Value &= 0xFFFF0000;
        Config_Value |= MTP_GPIO_Config_Value;
    }
    else
    {
        Config_Value &= 0x0000FFFF;
        Config_Value |= (MTP_GPIO_Config_Value << 16);
    }

    Status = qapi_Fuse_Write(Address, Config_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    MTP_GPIO_OE_Value &= ~(0x01 << GPIO_ID);
    MTP_GPIO_OE_Value |= (qapi_GPIO_Config->Dir << GPIO_ID);
    Status = qapi_Fuse_Write((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOe,
                             MTP_GPIO_OE_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    MTP_GPIO_Out_Value &= ~(0x01 << GPIO_ID);
    if (Value == QAPI_GPIO_HIGH_VALUE_E)
    {
        MTP_GPIO_Out_Value |= (0x01 << GPIO_ID);
    }
    Status = qapi_Fuse_Write((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOut,
                             MTP_GPIO_Out_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    return QAPI_OK;
}

/**
   @brief Get GPIO configuration from MTP.

   Get the GPIO configuration from MTP, the result may not match the current
   GPIO registers configuration.

   @param[in] GPIO_ID           GPIO number.
   @param[in] qapi_GPIO_Config  Pin configuration to use.
   @param[in] Value             Output value.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Get_MTP_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *qapi_GPIO_Config, qapi_GPIO_Value_t *Value)
{
    qapi_Status_t  Status;
    uint32_t       MTP_GPIO_Config_Value;
    uint32_t       MTP_GPIO_OE_Value;
    uint32_t       MTP_GPIO_Out_Value;
    uint32_t       Address, Config_Value;

    if ((GPIO_ID > QAPI_GPIO_ID25_E) || (qapi_GPIO_Config == NULL) 
     || (Value == NULL))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Address = (uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioCfg[GPIO_ID / 2 * 2];
    Status = qapi_Fuse_Read(Address, &Config_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    if ((GPIO_ID % 2) == 0)
    {
        MTP_GPIO_Config_Value = Config_Value & 0x0000FFFF;
    }
    else
    {
        MTP_GPIO_Config_Value = (Config_Value & 0xFFFF0000) >> 16;
    }

    Status = qapi_Fuse_Read((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOe,
                            &MTP_GPIO_OE_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = qapi_Fuse_Read((uint32_t)&QAPI_MTP_APSS_RW_PTR->GpioOut,
                            &MTP_GPIO_Out_Value);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    qapi_GPIO_Config->PIOFunc = (MTP_GPIO_Config_Value 
                               & HWIO_TLMM_GPIO_CFGm_FUNC_SEL_BMSK)
                               >> HWIO_TLMM_GPIO_CFGm_FUNC_SEL_SHFT;
    if ((MTP_GPIO_Config_Value & HWIO_TLMM_GPIO_CFGm_GPIO_PULL_BMSK)
        == (QAPI_GPIO_PULL_UP_E + 1))
    {
        qapi_GPIO_Config->Pull = QAPI_GPIO_PULL_UP_E;
    }
    else if ((MTP_GPIO_Config_Value & HWIO_TLMM_GPIO_CFGm_GPIO_PULL_BMSK)
        == QAPI_GPIO_PULL_DOWN_E)
    {
        qapi_GPIO_Config->Pull = QAPI_GPIO_PULL_DOWN_E;
    }
    else
    {
        qapi_GPIO_Config->Pull = QAPI_GPIO_NO_PULL_E;
    }

    qapi_GPIO_Config->Drive = (qapi_GPIO_Drive_t)((MTP_GPIO_Config_Value 
                             & HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_BMSK)
                             >> HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_SHFT);

    qapi_GPIO_Config->Dir = (qapi_GPIO_Direction_t)((MTP_GPIO_OE_Value
                             & (0x01 << GPIO_ID)) >> GPIO_ID);

    *Value = (qapi_GPIO_Value_t)((MTP_GPIO_Out_Value & (0x01 << GPIO_ID)) >> GPIO_ID);

    return QAPI_OK;
}
