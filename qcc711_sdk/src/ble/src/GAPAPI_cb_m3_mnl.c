/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "GAPAPI_cb_params.h"
#include "GAPAPI_cb_m3.h"
#include "GAPAPI_mnl_util.h"
#include "callback.h"
#include "qapi_heap.h"

void GAP_LE_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    GAP_LE_Event_Callback_Params_t *Params = (GAP_LE_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;
    qapi_BLE_GAP_LE_Advertising_Report_Data_t *AdvReport;
    unsigned int Index;
    unsigned int Index2;
    bool Dispatch = true;

    if(BufferLength >= sizeof(GAP_LE_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            switch(Params->GAP_LE_Event_Data->Event_Data_Type)
            {
                case QAPI_BLE_ET_LE_ADVERTISING_REPORT_E:
                    /* The complexity of this event makes it simpler to parse the raw advertising data here,
                     * rather than attempt to serialized each parsed AD structure over IPC. */
                    for(Index=0; Index < Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Number_Device_Entries && Dispatch; Index++)
                    {
                        AdvReport = &Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Advertising_Data[Index];

                        if(AdvReport->Advertising_Data.Number_Data_Entries > 0)
                        {
                            /* Allocate memory to hold the parse AD entries. */
                            AdvReport->Advertising_Data.Data_Entries = (qapi_BLE_GAP_LE_Advertising_Data_Entry_t *)qapi_Malloc(AdvReport->Advertising_Data.Number_Data_Entries * QAPI_BLE_GAP_LE_ADVERTISING_DATA_ENTRY_SIZE);

                            if(AdvReport->Advertising_Data.Data_Entries != NULL)
                            {
                                /* Attempt to parse the raw advertising data. */
                                if(ParseAdvertisingData(AdvReport->Raw_Report_Length, AdvReport->Raw_Report_Data, &AdvReport->Advertising_Data) <= 0)
                                {
                                    /* Failed to parse the report data, so free the allocated list. */
                                    qapi_Free(AdvReport->Advertising_Data.Data_Entries);
                                    AdvReport->Advertising_Data.Data_Entries = NULL;

                                    /* Flag the failure. */
                                    Dispatch = false;
                                }
                            }
                        }
                        else
                            AdvReport->Advertising_Data.Data_Entries = NULL;
                    }

                    /* If an error occurred, free everything we allocated. */
                    if(!Dispatch)
                    {
                        for(Index=0; Index <  Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Number_Device_Entries; Index++)
                        {
                            AdvReport = &Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Advertising_Data[Index];

                            if(AdvReport->Advertising_Data.Data_Entries)
                            {
                                /* Free each allocated parsed buffer. */
                                for(Index2=0; Index2 < AdvReport->Advertising_Data.Number_Data_Entries; Index2++)
                                {
                                    qapi_Free(AdvReport->Advertising_Data.Data_Entries[Index2].AD_Data_Buffer);
                                }

                                /* Free the allocated list. */
                                qapi_Free(AdvReport->Advertising_Data.Data_Entries);
                                AdvReport->Advertising_Data.Data_Entries = NULL;
                            }
                            else
                            {
                                /* The failed entry will have been nulled out, so stop at this point. */
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }

            if(Dispatch)
            {
                /* Make the callback. */
                ((qapi_BLE_GAP_LE_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->GAP_LE_Event_Data, KeyedCBInfo.AppParam);

                /* Handle any postprocessing required by some events. */
                switch(Params->GAP_LE_Event_Data->Event_Data_Type)
                {
                    case QAPI_BLE_ET_LE_ADVERTISING_REPORT_E:
                        /* Free all the parsed AD. */
                        for(Index=0; Index < Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Number_Device_Entries; Index++)
                        {
                            AdvReport = &Params->GAP_LE_Event_Data->Event_Data.GAP_LE_Advertising_Report_Event_Data->Advertising_Data[Index];

                            for(Index2=0; Index2 < AdvReport->Advertising_Data.Number_Data_Entries; Index2++)
                            {
                                qapi_Free(AdvReport->Advertising_Data.Data_Entries[Index2].AD_Data_Buffer);
                            }

                            qapi_Free(AdvReport->Advertising_Data.Data_Entries);
                            AdvReport->Advertising_Data.Data_Entries = NULL;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

