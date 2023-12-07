//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncPowerTuning.c
/// \brief Demonstrates how to receive notifications of changes in power tuning settings using ADLX. To receive the event, another application (such as SmartShiftMax) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPowerTuning.h"
#include "SDK/Include/ISystem1.h"

// Block event to verify call back
HANDLE blockEvent = NULL;

// Call back to handle changed events
adlx_bool ADLX_STD_CALL OnPowerTuningChanged(IADLXPowerTuningChangedListener* pthis, IADLXPowerTuningChangedEvent* pPoweruningChangedEvent)
{
    ADLX_SYNC_ORIGIN origin = pPoweruningChangedEvent->pVtbl->GetOrigin(pPoweruningChangedEvent);
    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        if (pPoweruningChangedEvent->pVtbl->IsSmartShiftMaxChanged(pPoweruningChangedEvent))
        {
            printf("\tSmartShiftMaxChanged\n");
        }
    }
    SetEvent(blockEvent);

    // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
}
typedef struct PowerTuningChangedCall
{
    adlx_bool(ADLX_STD_CALL* OnPowerTuningChanged)(IADLXPowerTuningChangedListener*, IADLXPowerTuningChangedEvent*);
} PowerTuningChangedCall;

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Create block event
        blockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get IADLXSystem1 interface
        IADLXSystem1* system1 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem1(), (void**)(&system1));
        if (ADLX_SUCCEEDED(res))
        {
            // Get power tuning services
            IADLXPowerTuningServices* powerTuningServices = NULL;
            res = system1->pVtbl->GetPowerTuningServices(system1, &powerTuningServices);

            if (ADLX_SUCCEEDED(res))
            {
                // Get the Change Handle interface
                IADLXPowerTuningChangedHandling* changeHandle = NULL;
                res = powerTuningServices->pVtbl->GetPowerTuningChangedHandling(powerTuningServices, &changeHandle);
                if (ADLX_SUCCEEDED(res))
                {
                    // Create call back
                    PowerTuningChangedCall* call = (PowerTuningChangedCall*)malloc(sizeof(PowerTuningChangedCall));
                    call->OnPowerTuningChanged = &OnPowerTuningChanged;

                    // Add call back
                    changeHandle->pVtbl->AddPowerTuningEventListener(changeHandle, (IADLXPowerTuningChangedListener*)&call);

                    // Waits for power tuning sync with a timeout of 60s
                    while (true)
                    {
                        printf("\nWaiting for power tuning change event (60s)...\n");
                        DWORD waitRet = WaitForSingleObject(blockEvent, 60000);
                        if (waitRet == WAIT_TIMEOUT)
                        {
                            printf("== = Wait timeout(60s), ready to quit == = \n");
                            break;
                        }
                        ResetEvent(blockEvent);
                    }

                    // Remove call back
                    changeHandle->pVtbl->RemovePowerTuningEventListener(changeHandle, (IADLXPowerTuningChangedListener*)&call);

                    // Release call back
                    free(call);
                    call = NULL;
                }
                else
                    printf("Failed to get power tuning changed handling interface\n");

                // Release the Change Handle interface
                if (changeHandle != NULL)
                {
                    changeHandle->pVtbl->Release(changeHandle);
                    changeHandle = NULL;
                }
            }
            else
                printf("Failed to get power tuning service\n");

            // Release power tuning services interface
            if (powerTuningServices != NULL)
            {
                powerTuningServices->pVtbl->Release(powerTuningServices);
                powerTuningServices = NULL;
            }
        }
        else
            printf("Failed to get IADLXSystem1\n");

        // Release IADLXSystem1 interface
        if (system1 != NULL)
        {
            system1->pVtbl->Release(system1);
            system1 = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Close event
    if (blockEvent)
        CloseHandle(blockEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}