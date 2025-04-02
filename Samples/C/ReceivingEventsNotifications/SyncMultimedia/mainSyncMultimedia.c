//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncMultimedia.c
/// \brief Demonstrates how to receive notifications of changes in multimedia settings using ADLX. To receive the event, another application (such as Videoupscale) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IMultiMedia.h"
#include "SDK/Include/ISystem2.h"


// Block event to verify call back
HANDLE blockEvent = NULL;
HANDLE quitEvent = NULL;


adlx_bool ADLX_STD_CALL OnMultimediaChanged(IADLXMultimediaChangedEventListener* pThis, IADLXMultimediaChangedEvent* pMultimediaChangedEvent)
{
    // Get the GPU interface
    IADLXGPU* gpu = NULL;
    pMultimediaChangedEvent->pVtbl->GetGPU(pMultimediaChangedEvent, &gpu);

    ADLX_SYNC_ORIGIN origin = pMultimediaChangedEvent->pVtbl->GetOrigin(pMultimediaChangedEvent);

    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        if (pMultimediaChangedEvent->pVtbl->IsVideoUpscaleChanged(pMultimediaChangedEvent))
        {
            printf("\tVideoupscale is changed\n");
        }
        else if (pMultimediaChangedEvent->pVtbl->IsVideoSuperResolutionChanged(pMultimediaChangedEvent))
        {
            printf("\tVideo Super Resolution is changed\n");
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

static IADLXMultimediaChangedEventListenerVtbl vtbl = { &OnMultimediaChanged };
static IADLXMultimediaChangedEventListener eventListener = { &vtbl };

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

        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get IADLXSystem2 interface
        IADLXSystem2* system2 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem2(), (void**)(&system2));
        if (ADLX_SUCCEEDED(res))
        {
            // Get multimedia services
            IADLXMultimediaServices* multimediaServices = NULL;
            res = system2->pVtbl->GetMultimediaServices(system2, &multimediaServices);

            if (ADLX_SUCCEEDED(res))
            {
                // Get the Change Handle interface
                IADLXMultimediaChangedHandling* changeHandle = NULL;;
                res = multimediaServices->pVtbl->GetMultimediaChangedHandling(multimediaServices, &changeHandle);

                if (ADLX_SUCCEEDED(res))
                {
                    // Add call back
                    changeHandle->pVtbl->AddMultimediaEventListener(changeHandle, &eventListener);

                    // Create a thread to detect quit input
                    adlx_bool loopFlag = true;
                    DWORD threadId = 0;
                    HANDLE hThread = CreateThread(NULL, 0, QuitWait, &loopFlag, 0, &threadId);

                    printf("\nWaiting for Multimedia change event... Press Q/q to quit\n");
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
                    changeHandle->pVtbl->RemoveMultimediaEventListener(changeHandle, &eventListener);
                }

                // Release the Change Handle interface
                if (changeHandle != NULL)
                {
                    changeHandle->pVtbl->Release(changeHandle);
                    changeHandle = NULL;
                }

                // Release the multimedia services interface
                if (multimediaServices != NULL)
                {
                    multimediaServices->pVtbl->Release(multimediaServices);
                    multimediaServices = NULL;
                }

            }

            else
            {
                printf("Failed to get multimedia Services\n");
            }

        }
        else
            printf("Failed to get IADLXSystem2\n");

        // Release IADLXSystem2 interface
        if (system2 != NULL)
        {
            system2->pVtbl->Release(system2);
            system2 = NULL;
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