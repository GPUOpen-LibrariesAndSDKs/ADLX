//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file main3DSettingsEvent.c
/// \brief Demonstrates how to register and unregister for notifications when 3D Graphics settings change, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Block event
HANDLE blockEvent = NULL;

// Get the GPU unique name
void GPUUniqueName(IADLXGPU* gpu, char* uniqueName);

// Call-back to handle changed events
adlx_bool ADLX_STD_CALL on3DSettingsChanged(IADLX3DSettingsChangedListener* pThis, IADLX3DSettingsChangedEvent* p3DSettingsChangedEvent)
{
    ADLX_RESULT res;
    IADLXGPU* gpu = NULL;
    res = p3DSettingsChangedEvent->pVtbl->GetGPU(p3DSettingsChangedEvent, &gpu);
    if (ADLX_SUCCEEDED(res))
    {
        char uniqueName[128] = "Unknown";
        GPUUniqueName(gpu, uniqueName);
        adlx_bool antiLagChanged = p3DSettingsChangedEvent->pVtbl->IsAntiLagChanged(p3DSettingsChangedEvent);
        printf("\tGPU: %s AntiLag changed: %d\n", uniqueName, antiLagChanged);
    }

    SetEvent(blockEvent);

    // Release the GPU interface
    if (gpu != NULL)
    {
        gpu->pVtbl->Release(gpu);
        gpu = NULL;
    }

        // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
};
static IADLX3DSettingsChangedListenerVtbl vtbl = {&on3DSettingsChanged};
static IADLX3DSettingsChangedListener call = {&vtbl};

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

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

            // Get change handle
            IADLX3DSettingsChangedHandling* changeHandle = NULL;
            res = d3dSettingSrv->pVtbl->Get3DSettingsChangedHandling(d3dSettingSrv, &changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Add call-back
                ADLX_RESULT addListenerRes = changeHandle->pVtbl->Add3DSettingsEventListener(changeHandle, &call);

                // Change anti-lag state
                IADLX3DAntiLag* antiLag = NULL;
                d3dSettingSrv->pVtbl->GetAntiLag(d3dSettingSrv, gpu, &antiLag);
                adlx_bool enable;
                antiLag->pVtbl->IsEnabled(antiLag, &enable);

                printf("\nWaiting for 3DSettings change event (5s)...\n");
                antiLag->pVtbl->SetEnabled(antiLag, !enable);
                WaitForSingleObject(blockEvent, 5000);

                if (ADLX_SUCCEEDED (addListenerRes))
                {
                    // Remove call-back
                    res = changeHandle->pVtbl->Remove3DSettingsEventListener(changeHandle, &call);
                    if (ADLX_FAILED (res))
                        printf("\nRemove 3DSettings event listener failed\n");
                }

                // Release the AntiLag interface
                if (antiLag != NULL)
                {
                    antiLag->pVtbl->Release(antiLag);
                    antiLag = NULL;
                }
                
            }

            // Release the changeHandle interface
            if (changeHandle != NULL)
            {
                changeHandle->pVtbl->Release(changeHandle);
                changeHandle = NULL;
            }

            // Release the GPU interface
            if (gpu != NULL)
            {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else
        {
            printf("Failed to get 3DSettings services\n");
        }

        // Release the 3DSettingsService interface
        if (d3dSettingSrv != NULL)
        {
            d3dSettingSrv->pVtbl->Release(d3dSettingSrv);
            d3dSettingSrv = NULL;
        }

        // Release the GPUs list interface
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
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
        ADLX_RESULT res1 = gpu->pVtbl->Name(gpu, &gpuName);
        adlx_int id;
        ADLX_RESULT res2 = gpu->pVtbl->UniqueId(gpu, &id);
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            sprintf_s(uniqueName, 128, "name:%s, id:%d", gpuName, id);
    }
}