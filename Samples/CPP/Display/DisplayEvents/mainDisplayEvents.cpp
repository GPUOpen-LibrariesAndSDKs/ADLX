//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayEvents.cpp
/// \brief Demontrates how to handle notifications about display change when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplay3DLUT.h"
#include "SDK/Include/IDisplayGamma.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Callback for displayListChanged
class DisplayListChangedCallBack : public IADLXDisplayListChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplayListChanged(IADLXDisplayList* pNewDisplays) override
    {
        std::cout << "Display list has been changed" << std::endl;
        
        // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
        return true;
    }
};

// Callback for displayGamutChanged
class DisplayGamutCallBack : public IADLXDisplayGamutChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplayGamutChanged(IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent) override
    {
        std::cout << "Display gamut is changed" << std::endl;
        // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
        return true;
    }
};

// Callback for displayGammaChanged
class DisplayGammaCallBack : public IADLXDisplayGammaChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplayGammaChanged(IADLXDisplayGammaChangedEvent* pDisplayGammaChangedEvent) override
    {
        std::cout << "Display gamma is changed" << std::endl;

        IADLXDisplayPtr display;
        ADLX_RESULT res = pDisplayGammaChangedEvent->GetDisplay(&display);
        if (ADLX_SUCCEEDED(res))
        {
            const char* displayName = nullptr;
            display->Name(&displayName);
            adlx_bool changed = pDisplayGammaChangedEvent->IsDeGammaChanged();
            std::cout << "\tDisplay: " << displayName << " DeGamma changed: " << changed << std::endl;
            changed = pDisplayGammaChangedEvent->IsReGammaChanged();
            std::cout << "\tDisplay: " << displayName << " ReGamma changed: " << changed << std::endl;
            changed = pDisplayGammaChangedEvent->IsGammaCoefficientChanged();
            std::cout << "\tDisplay: " << displayName << " Gamma Coefficient changed: " << changed << std::endl;
            changed = pDisplayGammaChangedEvent->IsGammaRampChanged();
            std::cout << "\tDisplay: " << displayName << " Gamma Ramp changed: " << changed << std::endl;
        }
        // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
        return true;
    }
};

// Callback for display3DLUT
class Display3DLUTCallBack : public IADLXDisplay3DLUTChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplay3DLUTChanged(IADLXDisplay3DLUTChangedEvent* pDisplay3DLUTChangedEvent) override
    {
        std::cout << "Display 3DLUT is changed" << std::endl;
        // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
        return true;
    }
};

// Loop thread
void LoopThread();

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
        // Get display services
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display change handler
            IADLXDisplayChangedHandlingPtr displayChangeHandler;
            res = displayService->GetDisplayChangedHandling(&displayChangeHandler);
            if (ADLX_FAILED(res))
                return WaitAndExit("Failed to get display change handler", 0);

            // Create the callbacks
            IADLXDisplayListChangedListener* listChangeCallBack = new DisplayListChangedCallBack;
            IADLXDisplayGammaChangedListener* gammaChangeCallBack = new DisplayGammaCallBack;
            IADLXDisplayGamutChangedListener* gamutChangeCallBack = new DisplayGamutCallBack;
            IADLXDisplay3DLUTChangedListener* display3DLUTChangeCallBack = new Display3DLUTCallBack;

            // Add the callbacks to the ADLX event handler
            {
                displayChangeHandler->AddDisplayListEventListener(listChangeCallBack);
                displayChangeHandler->AddDisplayGammaEventListener(gammaChangeCallBack);
                displayChangeHandler->AddDisplayGamutEventListener(gamutChangeCallBack);
                displayChangeHandler->AddDisplay3DLUTEventListener(display3DLUTChangeCallBack);
            }

            // Create loop thread for wait event
            std::thread loop(&LoopThread);
            loop.join();

            // Remove and destroy callbacks
            displayChangeHandler->RemoveDisplayGamutEventListener(gamutChangeCallBack);
            displayChangeHandler->RemoveDisplayListEventListener(listChangeCallBack);
            displayChangeHandler->RemoveDisplay3DLUTEventListener(display3DLUTChangeCallBack);
            displayChangeHandler->RemoveDisplayGammaEventListener(gammaChangeCallBack);

            delete listChangeCallBack;
            listChangeCallBack = nullptr;
            delete gamutChangeCallBack;
            gamutChangeCallBack = nullptr;
            delete gammaChangeCallBack;
            gammaChangeCallBack = nullptr;
            delete display3DLUTChangeCallBack;
            display3DLUTChangeCallBack = nullptr;
        }
        else
        {
            std::cout << "Failed to get display services: " << res << std::endl;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the printout
    system("pause");

    return 0;
}

// Loop thread
void LoopThread()
{
    std::cout << "Loop thread is currently running." << std::endl;
    std::cout << "-> Plug or unplug the display to trigger DisplayListChange, which will further trigger other changes." << std::endl;
    std::cout << "->Press Q/q to terminate the loop." << std::endl;
    int num = 0;
    std::chrono::seconds dura(1);
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        std::cout << "Wait for the event to get triggered. The display can be pluged or unpluged to trigger DisplayListChange." << std::endl;
        std::this_thread::sleep_for(dura);
        num = getchar();
        if (num == 'q' || num == 'Q')
            break;
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}