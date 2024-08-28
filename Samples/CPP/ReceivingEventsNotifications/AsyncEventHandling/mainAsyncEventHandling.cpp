//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAsyncEventHandling.cpp
/// \brief Demonstrates how to handle long processing for an event on a separate thread when programming in ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// Handle gamutChangedEevent
HANDLE gamutChangedEvent = nullptr;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Callback displayGamut in thread
class DisplayGamutCallBack : public IADLXDisplayGamutChangedListener
{
public:
    ~DisplayGamutCallBack()
    {
        if (m_td)
        {
            m_td->detach();
        }
    }

    adlx_bool ADLX_STD_CALL OnDisplayGamutChanged(IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent) override
    {
        // Acquire the interface before passing to the asynchronous thread
        pDisplayGamutChangedEvent->Acquire();
        auto run = [](IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent) {

            // Some time-consuming operations
            Sleep(5000);
            std::cout << "On the asynchronous thread: Thread Id: " << GetCurrentThreadId() << " : After the time-consuming operations, get the display gamut changed event:" << std::endl;
            std::cout << "\tColor space change: " << pDisplayGamutChangedEvent->IsColorSpaceChanged() << std::endl
                      << "\tWhite point change: " << pDisplayGamutChangedEvent->IsWhitePointChanged() << std::endl;

            // Release the interface when the task is completed.
            pDisplayGamutChangedEvent->Release();

            SetEvent(gamutChangedEvent);
        };

        m_td = std::make_shared<std::thread>(run, pDisplayGamutChangedEvent);
        return true;
    }

private:
    std::shared_ptr<std::thread> m_td = nullptr;
};

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Create event
        gamutChangedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // Get display service
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display change handler
            IADLXDisplayChangedHandlingPtr displayChangeHandler;
            res = displayService->GetDisplayChangedHandling(&displayChangeHandler);
            if (ADLX_FAILED (res))
            {
                // Destroy ADLX
                res = g_ADLXHelp.Terminate ();
                std::cout << "Destroy ADLX result: " << res << std::endl;
                return WaitAndExit ("Failed to get display change handler", 0);
            }
            // Create the callbacks
            IADLXDisplayGamutChangedListener* gamutChangeCallBack = new DisplayGamutCallBack;

            // Add the callbacks to the ADLX event handler
            ADLX_RESULT addListenerRes = displayChangeHandler->AddDisplayGamutEventListener(gamutChangeCallBack);

            // Set gamut for the first display
            IADLXDisplayListPtr displays;
            displayService->GetDisplays(&displays);
            adlx_uint it = 0;
            IADLXDisplayPtr display;
            displays->At(it, &display);
            IADLXDisplayGamutPtr dispGamut;
            res = displayService->GetGamut(display, &dispGamut);
            res = dispGamut->SetGamut(WHITE_POINT_5000K, GAMUT_SPACE_CIE_RGB);
            std::cout << "Set gamut ret: " << res << std::endl;
            if (ADLX_SUCCEEDED(res))
            {
                std::cout << "This will trigger gamut change and send gamut change in thread: " << GetCurrentThreadId() << std::endl;
            }

            if (ADLX_SUCCEEDED (addListenerRes))
            {
                // Wait for gamut change
                WaitForSingleObject(gamutChangedEvent, INFINITE);

                // Remove and destroy callbacks
                res = displayChangeHandler->RemoveDisplayGamutEventListener(gamutChangeCallBack);
                if (ADLX_FAILED (res))
                    std::cout << "Remove display gamut event listener failed" << std::endl;
            }

            delete gamutChangeCallBack;
            gamutChangeCallBack = nullptr;
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get the Display Services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Close event
    if (gamutChangedEvent)
        CloseHandle(gamutChangedEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}