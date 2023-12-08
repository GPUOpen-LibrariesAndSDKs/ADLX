//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSync3DReceive.c
/// \brief Demonstrates how to receive notifications of changes in 3D settings using ADLX. To receive the event, another application (such as AntiLag) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include "conio.h"

// Block event to verify call back
HANDLE blockEvent = NULL;
HANDLE quitEvent = NULL;

// Get the GPU unique name
void GPUUniqueName(IADLXGPU* gpu, char* uniqueName);

// Call back to handle changed events
adlx_bool ADLX_STD_CALL On3DSettingsChanged(IADLX3DSettingsChangedListener *pThis, IADLX3DSettingsChangedEvent* p3DSettingsChangedEvent)
{
    // Get the GPU interface
    IADLXGPU* gpu = NULL;
    p3DSettingsChangedEvent->pVtbl->GetGPU(p3DSettingsChangedEvent, &gpu);

    //RadeonSuperResolution is a global feature (the GPU interface is NULL); skip printing its name
    if (!p3DSettingsChangedEvent->pVtbl->IsRadeonSuperResolutionChanged(p3DSettingsChangedEvent))
    {
        char uniqueName[128] = "Unknown";
        GPUUniqueName(gpu, uniqueName);
        printf("GPU: %s get sync event\n", uniqueName);
    }
    ADLX_SYNC_ORIGIN origin = p3DSettingsChangedEvent->pVtbl->GetOrigin(p3DSettingsChangedEvent);
    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        if (p3DSettingsChangedEvent->pVtbl->IsAntiLagChanged(p3DSettingsChangedEvent))
        {
            printf("\tAnti-Lag is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsChillChanged(p3DSettingsChangedEvent))
        {
            printf("\tChill is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsBoostChanged(p3DSettingsChangedEvent))
        {
            printf("\tBoost is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsImageSharpeningChanged(p3DSettingsChangedEvent))
        {
            printf("\tImage Sharpening is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsEnhancedSyncChanged(p3DSettingsChangedEvent))
        {
            printf("\tEnhanced Sync is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsWaitForVerticalRefreshChanged(p3DSettingsChangedEvent))
        {
            printf("\tWait For Vertical Refresh is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsFrameRateTargetControlChanged(p3DSettingsChangedEvent))
        {
            printf("\tFRTC is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsAntiAliasingChanged(p3DSettingsChangedEvent))
        {
            printf("\tAnti-Aliasing is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsMorphologicalAntiAliasingChanged(p3DSettingsChangedEvent))
        {
            printf("\tMorphological Anti-Aliasing is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsAnisotropicFilteringChanged(p3DSettingsChangedEvent))
        {
            printf("\tAnisotropic Filtering is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsTessellationModeChanged(p3DSettingsChangedEvent))
        {
            printf("\tTessellation Mode is changed\n");
        }
        else if (p3DSettingsChangedEvent->pVtbl->IsResetShaderCache(p3DSettingsChangedEvent))
        {
            printf("\tResetShaderCache\n");
        }
    }

    if (origin == SYNC_ORIGIN_UNKNOWN)
    {
        if (p3DSettingsChangedEvent->pVtbl->IsRadeonSuperResolutionChanged(p3DSettingsChangedEvent))
        {
            printf("\tget sync event, RSR changed\n");
        }
    }
    
    // Release the GPU interface
    if (gpu != NULL)
    {
        gpu->pVtbl->Release(gpu);
        gpu = NULL;
    }

    SetEvent(blockEvent);

    // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
}

// Wait for quit signal
DWORD WINAPI QuitWait(LPVOID lpParam)
{
    adlx_bool* loopFlag = (adlx_bool*)lpParam;
    while (true)
    {
        // Non-blocking checking if the I/O cache has characters
        if (_kbhit())
        {
            char c;
            if ((c = getchar()) == 'q' || c == 'Q')
            {
                *loopFlag = false;
                SetEvent(quitEvent);
                break;
            }
        }
        Sleep(100);
    }
    return 0;
}

static IADLX3DSettingsChangedListenerVtbl vtbl = {&On3DSettingsChanged};
static IADLX3DSettingsChangedListener eventListener = {&vtbl};

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
        // Create quit event
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create event array
        HANDLE eventArray[] = { blockEvent, quitEvent };

        // Get the System Services interface
        IADLXSystem *sys = ADLXHelper_GetSystemServices();

        // Get the 3D Settings Service interface
        IADLX3DSettingsServices *d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get the Change Handle interface
            IADLX3DSettingsChangedHandling *changeHandle = NULL;;
            res = d3dSettingSrv->pVtbl->Get3DSettingsChangedHandling(d3dSettingSrv, &changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Add call back
                changeHandle->pVtbl->Add3DSettingsEventListener(changeHandle, &eventListener);

                // Create a thread to detect quit input
                adlx_bool loopFlag = true;
                DWORD threadId = 0;
                HANDLE hThread = CreateThread(NULL, 0, QuitWait, &loopFlag, 0, &threadId);

                printf("\nWaiting for 3DSetting change event... Press Q/q to quit\n");
                while (true)
                {
                    // Wait for change event or request to quit
                    DWORD waitRet = WaitForMultipleObjects(2, eventArray, FALSE, INFINITE);
                    if (!loopFlag)
                    {
                        CloseHandle(hThread);
                        break;
                    }
                    ResetEvent(blockEvent);
                }

                // Remove call back
                changeHandle->pVtbl->Remove3DSettingsEventListener(changeHandle, &eventListener);
            }
            // Release the Change Handle interface
            if (changeHandle != NULL)
            {
                changeHandle->pVtbl->Release(changeHandle);
                changeHandle = NULL;
            }
            // Release the 3DSettings Services interface
            if (d3dSettingSrv != NULL)
            {
                d3dSettingSrv->pVtbl->Release(d3dSettingSrv);
                d3dSettingSrv = NULL;
            }
        }
        else
        {
            printf("Failed to get 3DSettings Services\n");
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
    if (quitEvent)
        CloseHandle(quitEvent);

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