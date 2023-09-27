//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncGPUTuning.c
/// \brief Demonstrates how to receive notifications of changes in GPU tuning settings using ADLX. To receive the event, another application (such as GPUAutoTuning) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUTuning.h"

// Block event to verify call back
HANDLE blockEvent = NULL;

// Get the GPU unique name
void GPUUniqueName(IADLXGPU* gpu, char* uniqueName);

// Call back to handle changed events
adlx_bool ADLX_STD_CALL OnGPUTuningChanged(IADLXGPUTuningChangedListener* pthis, IADLXGPUTuningChangedEvent* pGPUTuningChangedEvent)
{
    ADLX_SYNC_ORIGIN origin = pGPUTuningChangedEvent->pVtbl->GetOrigin(pGPUTuningChangedEvent);
    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        // Get the GPU interface
        IADLXGPU* gpu = NULL;
        pGPUTuningChangedEvent->pVtbl->GetGPU(pGPUTuningChangedEvent, &gpu);
        char uniqueName[128] = "Unknown";
        GPUUniqueName(gpu, uniqueName);
        printf("GPU: %s get sync event\n", uniqueName);

        if (pGPUTuningChangedEvent->pVtbl->IsAutomaticTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tAutomaticTuningChanged\n");
        }
        else if (pGPUTuningChangedEvent->pVtbl->IsPresetTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tPresetTuningChanged\n");
        }
        else if (pGPUTuningChangedEvent->pVtbl->IsManualGPUCLKTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tManualGPUCLKTuningChanged\n");
        }
        else if (pGPUTuningChangedEvent->pVtbl->IsManualVRAMTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tManualVRAMTuningChanged\n");
        }
        else if (pGPUTuningChangedEvent->pVtbl->IsManualFanTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tManualFanTuningChanged\n");
        }
        else if (pGPUTuningChangedEvent->pVtbl->IsManualPowerTuningChanged(pGPUTuningChangedEvent))
        {
            printf("\tManualPowerTuningChanged\n");
        }

        // Release the GPU interface
        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }
    }
    SetEvent(blockEvent);

    // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
}
typedef struct GPUTuningChangedCall
{
    adlx_bool(ADLX_STD_CALL* OnGPUTuningChanged)(IADLXGPUTuningChangedListener*, IADLXGPUTuningChangedEvent*);
} GPUTuningChangedCall;

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

        // Get the System Services interface
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get the GPU Tuning Service interface
        IADLXGPUTuningServices* gpuTuningSrv = NULL;
        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get the Change Handle interface
            IADLXGPUTuningChangedHandling* changeHandle = NULL;
            res = gpuTuningSrv->pVtbl->GetGPUTuningChangedHandling(gpuTuningSrv, &changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Create call back
                GPUTuningChangedCall* call = (GPUTuningChangedCall*)malloc(sizeof(GPUTuningChangedCall));
                call->OnGPUTuningChanged = &OnGPUTuningChanged;

                // Add call back
                changeHandle->pVtbl->AddGPUTuningEventListener(changeHandle, (IADLXGPUTuningChangedListener*)&call);

                // Waits for GPUTuning sync with a timeout of 60s
                while (true)
                {
                    printf("\nWaiting for GPUTuning change event (60s)...\n");
                    DWORD waitRet = WaitForSingleObject(blockEvent, 60000);
                    if (waitRet == WAIT_TIMEOUT)
                    {
                        printf("== = Wait timeout(60s), ready to quit == = \n");
                        break;
                    }
                    ResetEvent(blockEvent);
                }

                // Remove call back
                changeHandle->pVtbl->RemoveGPUTuningEventListener(changeHandle, (IADLXGPUTuningChangedListener*)&call);

                // Release call back
                free(call);
                call = NULL;
            }

            // Release the Change Handle interface
            if (changeHandle != NULL)
            {
                changeHandle->pVtbl->Release(changeHandle);
                changeHandle = NULL;
            }
        }
        else
        {
            printf("Failed to get GPUTuning Services\n");
        }

        // Release the GPUTuning Service interface
        if (gpuTuningSrv != NULL)
        {
            gpuTuningSrv->pVtbl->Release(gpuTuningSrv);
            gpuTuningSrv = NULL;
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

void GPUUniqueName(IADLXGPU* gpu, char* uniqueName)
{
    if (NULL != gpu && NULL != uniqueName)
    {
        const char* gpuName = NULL;
        gpu->pVtbl->Name(gpu, &gpuName);
        adlx_int id;
        gpu->pVtbl->UniqueId(gpu, &id);
        sprintf_s(uniqueName, 128, "name:%s, id:%d", gpuName, id);
    }
}