//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncDisplayReceive.c
/// \brief Demonstrates how to receive notifications of changes in display settings using ADLX. To receive the event, another application (such as DisplayFreeSync) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays1.h"
#include "SDK/Include/IDisplays2.h"
#include "SDK/Include/IDisplaySettings.h"
#include "conio.h"

// Block event to verify call back
HANDLE displaySettingsEvent = NULL;
HANDLE display3DLUTEvent = NULL;
// Quit event to exit
HANDLE quitEvent = NULL;

// Get the display unique name
void DisplayUniqueName(IADLXDisplay* display, char* uniqueName);

// Call back to handle changed events
adlx_bool ADLX_STD_CALL OnDisplaySettingsChanged(IADLXDisplaySettingsChangedListener* pThis, IADLXDisplaySettingsChangedEvent* pDisplaySettingsChangedEvent)
{
    ADLX_SYNC_ORIGIN origin = pDisplaySettingsChangedEvent->pVtbl->GetOrigin(pDisplaySettingsChangedEvent);

    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        IADLXDisplay *display = NULL;
        pDisplaySettingsChangedEvent->pVtbl->GetDisplay(pDisplaySettingsChangedEvent, &display);
        char displayName[128] = "Unknown";
        DisplayUniqueName(display, displayName);
        if (pDisplaySettingsChangedEvent->pVtbl->IsColorDepthChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Color Depth is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomColorBrightnessChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Color Brightness is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomColorContrastChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Color Contrast is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomColorHueChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Color Hue is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomColorSaturationChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Color Saturation is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomColorTemperatureChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Color Temperature is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsCustomResolutionChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Custom Resolution is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsFreeSyncChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, FreeSync is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsGPUScalingChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, GPU Scaling is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsHDCPChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, HDCP is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsIntegerScalingChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Integer Scaling is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsPixelFormatChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Pixel Format is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsScalingModeChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, Scaling Mode is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsVariBrightChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, VariBright is changed\n", displayName);
        }
        else if (pDisplaySettingsChangedEvent->pVtbl->IsVSRChanged(pDisplaySettingsChangedEvent))
        {
            printf("Display %s get sync event, VSR is changed\n", displayName);
        }

        // Get IADLXDisplaySettingsChangedEvent1 interface
        IADLXDisplaySettingsChangedEvent1* pDisplaySettingChangedEvent1 = NULL;
        ADLX_RESULT res = pDisplaySettingsChangedEvent->pVtbl->QueryInterface(pDisplaySettingsChangedEvent, IID_IADLXDisplaySettingsChangedEvent1(), &pDisplaySettingChangedEvent1);
        if (!ADLX_SUCCEEDED(res) || NULL == pDisplaySettingChangedEvent1)
        {
            printf("IID_IADLXDisplaySettingsChangedEvent1 not supported");
        }
        else
        {
            if (pDisplaySettingChangedEvent1->pVtbl->IsDisplayBlankingChanged(pDisplaySettingChangedEvent1))
            {
                printf("Display %s get sync event, Display blanking is changed\n", displayName);
            }
        }

        // Release the IADLXDisplaySettingsChangedEvent1 interface
        if (pDisplaySettingChangedEvent1 != NULL)
        {
            pDisplaySettingChangedEvent1->pVtbl->Release(pDisplaySettingChangedEvent1);
            pDisplaySettingChangedEvent1 = NULL;
        }

        // Get IADLXDisplaySettingsChangedEvent2 interface
        IADLXDisplaySettingsChangedEvent2* pDisplaySettingChangedEvent2 = NULL;
        res = pDisplaySettingsChangedEvent->pVtbl->QueryInterface(pDisplaySettingsChangedEvent, IID_IADLXDisplaySettingsChangedEvent2(), &pDisplaySettingChangedEvent2);
        if (!ADLX_SUCCEEDED(res) || NULL == pDisplaySettingChangedEvent2)
        {
            printf("IID_IADLXDisplaySettingsChangedEvent2 not supported");
        }
        else
        {
            if (pDisplaySettingChangedEvent2->pVtbl->IsDisplayConnectivityExperienceChanged(pDisplaySettingChangedEvent2))
            {
                printf("Display %s get sync event, Display connectivity experience is changed\n", displayName);
            }
        }

        // Release the IADLXDisplaySettingsChangedEvent2 interface
        if (pDisplaySettingChangedEvent2 != NULL)
        {
            pDisplaySettingChangedEvent2->pVtbl->Release(pDisplaySettingChangedEvent2);
            pDisplaySettingChangedEvent2 = NULL;
        }
         
        // Release the Display interface
        if (display != NULL)
        {
            display->pVtbl->Release(display);
            display = NULL;
        }
    }
    SetEvent(displaySettingsEvent);

    // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
}

adlx_bool ADLX_STD_CALL OnDisplay3DLUTChanged(IADLXDisplay3DLUTChangedListener* pThis, IADLXDisplay3DLUTChangedEvent* pDisplay3DLUTChangedEvent)
{
    ADLX_SYNC_ORIGIN origin = pDisplay3DLUTChangedEvent->pVtbl->GetOrigin(pDisplay3DLUTChangedEvent);
    if (origin == SYNC_ORIGIN_EXTERNAL)
    {
        IADLXDisplay* display = NULL;
        pDisplay3DLUTChangedEvent->pVtbl->GetDisplay(pDisplay3DLUTChangedEvent, &display);
        const char* displayName = NULL;
        display->pVtbl->Name(display, &displayName);
        if (pDisplay3DLUTChangedEvent->pVtbl->IsSCEChanged(pDisplay3DLUTChangedEvent))
        {
            printf("Display %s get sync event, SCE is changed\n", displayName);
        }
        else if (pDisplay3DLUTChangedEvent->pVtbl->IsCustom3DLUTChanged(pDisplay3DLUTChangedEvent))
        {
            printf("Display %s get sync event, Custom 3DLUT is changed\n", displayName);
        }

        // Release the Display interface
        if (display != NULL)
        {
            display->pVtbl->Release(display);
            display = NULL;
        }
    }
    SetEvent(display3DLUTEvent);

    // Return true for ADLX to continue notifying the next listener, or false to stop notification
    return true;
}

static IADLXDisplaySettingsChangedListenerVtbl displaySettingsVtbl = {&OnDisplaySettingsChanged};
static IADLXDisplaySettingsChangedListener displaySettingsEventListener = {&displaySettingsVtbl};
static IADLXDisplay3DLUTChangedListenerVtbl display3DLUTVtbl = {&OnDisplay3DLUTChanged};
static IADLXDisplay3DLUTChangedListener display3DLUTEventListener = {&display3DLUTVtbl};

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
        displaySettingsEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        display3DLUTEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        // Create quit event
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create event array
        HANDLE eventArray[] = { displaySettingsEvent, display3DLUTEvent, quitEvent };

        // Get Display Services
        IADLXSystem *sys = ADLXHelper_GetSystemServices();
        IADLXDisplayServices *displayServices = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayServices);

        if (ADLX_SUCCEEDED(res))
        {
            // Get the Change Handle interface
            IADLXDisplayChangedHandling *changeHandle = NULL;
            res = displayServices->pVtbl->GetDisplayChangedHandling(displayServices, &changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Add call back
                changeHandle->pVtbl->AddDisplaySettingsEventListener(changeHandle, &displaySettingsEventListener);
                changeHandle->pVtbl->AddDisplay3DLUTEventListener(changeHandle, &display3DLUTEventListener);

                // Create a thread to detect quit input
                adlx_bool loopFlag = true;
                DWORD threadId = 0;
                HANDLE hThread = CreateThread(NULL, 0, QuitWait, &loopFlag, 0, &threadId);

                printf("\nWaiting for display change event... Press Q/q to quit\n");
                while (true)
                {
                    // Wait for change event or request to quit
                    DWORD waitRet = WaitForMultipleObjects(3, eventArray, FALSE, INFINITE);
                    if (!loopFlag)
                    {
                        CloseHandle(hThread);
                        break;
                    }
                }

                // Remove call back
                changeHandle->pVtbl->RemoveDisplaySettingsEventListener(changeHandle, &displaySettingsEventListener);
                changeHandle->pVtbl->RemoveDisplay3DLUTEventListener(changeHandle, &display3DLUTEventListener);
            }
            // Release the Change Handle interface
            if (changeHandle != NULL)
            {
                changeHandle->pVtbl->Release(changeHandle);
                changeHandle = NULL;
            }
            // Release the Display Services interface
            if (displayServices != NULL)
            {
                displayServices->pVtbl->Release(displayServices);
                displayServices = NULL;
            }
        }
        else
        {
            printf("Failed to get Display Services\n");
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
    if (displaySettingsEvent)
        CloseHandle(displaySettingsEvent);
    if (display3DLUTEvent)
        CloseHandle(display3DLUTEvent);
    if (quitEvent)
        CloseHandle(quitEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}

void DisplayUniqueName(IADLXDisplay* display, char* uniqueName)
{
    if (NULL != display && NULL != uniqueName)
    {
        const char* gpuName = NULL;
        display->pVtbl->Name(display, &gpuName);
        adlx_size id;
        display->pVtbl->UniqueId(display, &id);
        sprintf_s(uniqueName, 128, "name:%s, id:%zu", gpuName, id);
    }
}