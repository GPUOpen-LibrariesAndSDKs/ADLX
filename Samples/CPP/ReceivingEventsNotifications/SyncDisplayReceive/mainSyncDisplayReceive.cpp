//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncDisplayReceive.cpp
/// \brief Demonstrates how to receive notifications of changes in display settings using ADLX. To receive the event, another application (such as DisplayFreeSync) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays1.h"
#include "SDK/Include/IDisplaySettings.h"
#include "conio.h"
#include <iostream>
#include <string>
#include <map>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Block event to verify call back
HANDLE displaySettingsEvent = nullptr;
HANDLE display3DLUTEvent = nullptr;
// Quit event to exit
HANDLE quitEvent = nullptr;

// Get the display unique name
void DisplayUniqueName(IADLXDisplayPtr display, char* uniqueName);

// Call back to handle changed events
class CallBackDisplaySettingsChanged : public IADLXDisplaySettingsChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplaySettingsChanged(IADLXDisplaySettingsChangedEvent* pDisplaySettingsChangedEvent) override
    {
        ADLX_SYNC_ORIGIN origin = pDisplaySettingsChangedEvent->GetOrigin();
        IADLXDisplaySettingsChangedEvent1Ptr pDisplaySettingChangedEvent1(pDisplaySettingsChangedEvent);
        if (nullptr == pDisplaySettingChangedEvent1)
        {
            std::cout << "IADLXDisplaySettingsChangedEvent1 not supported" << std::endl;
        }
        
        if (origin == SYNC_ORIGIN_EXTERNAL)
        {
            IADLXDisplayServicesPtr displayServices;
            g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayServices);
            IADLXDisplayPtr display;
            pDisplaySettingsChangedEvent->GetDisplay(&display);
            char displayName[128] = "Unknown";
            DisplayUniqueName(display, displayName);
            if (pDisplaySettingsChangedEvent->IsColorDepthChanged())
            {
                std::cout << "Display " << displayName << " Get sync event, color depth is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomColorBrightnessChanged())
            {
                std::cout << "Display " << displayName << " Get sync event, custom color brightness is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomColorContrastChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, custom color contrast is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomColorHueChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, custom color hue is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomColorSaturationChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, custom color saturation is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomColorTemperatureChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, custom color temperature is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsCustomResolutionChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, custom resolution is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsFreeSyncChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, free sync is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsGPUScalingChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, GPU scaling is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsHDCPChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, HDCP is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsIntegerScalingChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, integer scaling is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsPixelFormatChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, pixel is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsScalingModeChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, scaling mode is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsVariBrightChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, vari bright is changed" << std::endl;
            }
            else if (pDisplaySettingsChangedEvent->IsVSRChanged())
            {
                std::cout << "Display " << displayName << "Get sync event, VSR is changed" << std::endl;
            }

            if (pDisplaySettingChangedEvent1)
            {
                if (pDisplaySettingChangedEvent1->IsDisplayBlankingChanged())
                {
                    std::cout << "Display " << displayName << "Get sync event, display blanking is changed" << std::endl;
                }
            }

        }
        SetEvent(displaySettingsEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification.
        return true;
    }
};

class CallBackDisplay3DLUTChanged : public IADLXDisplay3DLUTChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplay3DLUTChanged(IADLXDisplay3DLUTChangedEvent* pDisplay3DLUTChangedEvent) override
    {
        ADLX_SYNC_ORIGIN origin = pDisplay3DLUTChangedEvent->GetOrigin();
        if (origin == SYNC_ORIGIN_EXTERNAL)
        {
            IADLXDisplayPtr display;
            pDisplay3DLUTChangedEvent->GetDisplay(&display);
            char displayName[128] = "Unknown";
            DisplayUniqueName(display, displayName);
            if (pDisplay3DLUTChangedEvent->IsSCEChanged())
            {
                std::cout << "Display " << displayName << " Get sync event, SCE is changed" << std::endl;
            }
            else if (pDisplay3DLUTChangedEvent->IsCustom3DLUTChanged())
            {
                std::cout << "Display " << displayName << " Get sync event, custom 3D LUT is changed" << std::endl;
            }
        }
        SetEvent(display3DLUTEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification
        return true;
    }
};

// Wait for exit with error message
void QuitWait(adlx_bool* loopFlag)
{
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
}

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Create block event
        displaySettingsEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        display3DLUTEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        // Create quit event
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create event array
        HANDLE eventArray[] = { displaySettingsEvent, display3DLUTEvent, quitEvent };

        // Get display service
        IADLXDisplayServicesPtr displayServices;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayServices);

        if (ADLX_SUCCEEDED(res))
        {
            // Get Change handle
            IADLXDisplayChangedHandlingPtr changeHandle;
            res = displayServices->GetDisplayChangedHandling(&changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Create call back
                IADLXDisplaySettingsChangedListener *displaySettingsChangedCallBack = new CallBackDisplaySettingsChanged;
                IADLXDisplay3DLUTChangedListener* display3DLUTChangedCallBack = new CallBackDisplay3DLUTChanged;

                // Add call back
                changeHandle->AddDisplaySettingsEventListener(displaySettingsChangedCallBack);
                changeHandle->AddDisplay3DLUTEventListener(display3DLUTChangedCallBack);

                // Create a thread to check quit event
                bool loopFlag = true;
                std::thread t{ QuitWait, &loopFlag};

                std::cout << "\nWaiting for display change event... Press Q/q to quit\n" << std::endl;
                while (true)
                {
                    // Wait for change event or request to quit
                    DWORD waitRet = WaitForMultipleObjects(3, eventArray, FALSE, INFINITE);
                    if (!loopFlag)
                    {
                        if (t.joinable())
                        {
                            t.join();
                        }
                        break;
                    }
                }

                // Remove call back
                changeHandle->RemoveDisplaySettingsEventListener(displaySettingsChangedCallBack);
                changeHandle->RemoveDisplay3DLUTEventListener(display3DLUTChangedCallBack);

                // Delete call back
                delete displaySettingsChangedCallBack;
                delete display3DLUTChangedCallBack;
                displaySettingsChangedCallBack = nullptr;
                display3DLUTChangedCallBack = nullptr;
            }
        }
        else
        {
            std::cout << "Failed to get the Display Services" << std::endl;
        }
    }
    else
    {
        std::cout << "ADLX initialization failed" << std::endl;
        return 0;
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

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

void DisplayUniqueName(IADLXDisplayPtr display, char* uniqueName)
{
    if (nullptr != display && nullptr != uniqueName)
    {
        const char* gpuName = nullptr;
        display->Name(&gpuName);
        adlx_size id;
        display->UniqueId(&id);
        sprintf_s(uniqueName, 128, "name:%s, id:%zu", gpuName, id);
    }
}