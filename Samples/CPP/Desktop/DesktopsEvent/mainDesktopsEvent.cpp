//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDesktopEvent.cpp
/// \brief This document describes how to obtain the desktops changed handle and add/remove call back of changed events through ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDesktops.h"
#include "SDK/Include/IDisplays.h"
#include "conio.h"
#include <iostream>
#include <string>
#include <thread>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX destory.
// so we use global variables to ensure the valid of the interface.
static ADLXHelper g_ADLXHelp;

// event to verify call back
HANDLE hDesktopChangedEvent = nullptr;
HANDLE hQuitSignal = nullptr;

// Call back to handle changed events
class CallBackDesktopListChanged : public IADLXDesktopListChangedListener
{
  public:
    adlx_bool ADLX_STD_CALL OnDesktopListChanged(IADLXDesktopList* pDesktopList) override
    {
        std::cout << "desktop list has been changed\n";
        adlx_bool slsActive = false;
        IADLXDesktopPtr desktop = nullptr;
        for (adlx_uint crt = pDesktopList->Begin(); crt != pDesktopList->End(); crt++)
        {
            ADLX_RESULT res = pDesktopList->At(crt, &desktop);
            if (ADLX_SUCCEEDED(res) && nullptr != desktop)
            {
                ADLX_DESKTOP_TYPE desktopType;
                desktop->Type(&desktopType);
                if (desktopType == DESKTOP_EYEFINITY)
                {
                    std::cout << "Eyefinity Creation Event is received" << std::endl;
                    slsActive = true;
                    break;
                }
            }
        }

        if (false == slsActive)
        {
            std::cout << "Eyefinity Destruction Event is received" << std::endl;
        }
        SetEvent(hDesktopChangedEvent);
        // Returns true will make ADLX continue to notify next listener or false to stop to notify
        return true;
    }
};

// thread to detect user's input for quit
void QuitWait(adlx_bool* loopFlag);

int main()
{
    // The ADL_4KWORKAROUND_CANCEL environment variable is a must for Eyefinity
    LPCSTR EnvironmentVariable = "ADL_4KWORKAROUND_CANCEL";
    SetEnvironmentVariableA(EnvironmentVariable, "TRUE");

    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Create desktop changed event
        hDesktopChangedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        hQuitSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
        HANDLE hSignalArray[2] = { hDesktopChangedEvent, hQuitSignal };

        // Get desktop services
        IADLXDesktopServicesPtr desktopServices;
        res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopServices);
        if (desktopServices != nullptr && ADLX_SUCCEEDED(res))
        {
            adlx_uint numDesktop;
            res = desktopServices->GetNumberOfDesktops(&numDesktop);
            std::cout << "The number of desktop is: " << numDesktop << std::endl;

            IADLXSimpleEyefinityPtr eyefinity;
            res = desktopServices->GetSimpleEyefinity(&eyefinity);
            if (eyefinity != nullptr && ADLX_SUCCEEDED(res))
            {
                // Verify if support eyefinity
                adlx_bool supported = false;
                eyefinity->IsSupported(&supported);
                if (supported)
                {
                    IADLXDesktopChangedHandlingPtr eventHandling;
                    desktopServices->GetDesktopChangedHandling(&eventHandling);
                    IADLXDesktopListChangedListener* eventListener = new CallBackDesktopListChanged;
                    eventHandling->AddDesktopListEventListener(eventListener);

                    std::cout << "Waiting for desktop event... Press Q/q to quit" << std::endl;
                    // create a thread to detect user's input for quit
                    adlx_bool loopFlag = true;
                    std::thread recvUserInput{ QuitWait, &loopFlag };
                    recvUserInput.detach();

                    IADLXEyefinityDesktopPtr eyefinityDesktop;
                    res = eyefinity->Create(&eyefinityDesktop);
                    while (true)
                    {
                        // Waiting for receiving desktop event or user exit event
                        WaitForMultipleObjects(2, hSignalArray, FALSE, INFINITE);
                        if (!loopFlag)
                            break;
                        ResetEvent(hDesktopChangedEvent);
                    }
                    res = eyefinity->DestroyAll();

                    eventHandling->RemoveDesktopListEventListener(eventListener);
                    delete eventListener;
                    eventListener = nullptr;
                }
                else
                {
                    std::cout << "Do not support eyefinity" << std::endl;
                }
            }
            else
            {
                std::cout << "Get simple eyefinity failed" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get the desktop Services" << std::endl;
        }
    }
    else
    {
        std::cout << "ADLX initialize failed" << std::endl;
        return 0;
    }
    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Close event
    if (hDesktopChangedEvent)
        CloseHandle(hDesktopChangedEvent);
    if (hQuitSignal)
        CloseHandle(hQuitSignal);

    // Pause for user see the print out
    system("pause");

    return 0;
}

void QuitWait(adlx_bool* loopFlag)
{
    while (true)
    {
        // Non-block I/O, check I/O cache whether have characters.
        if (_kbhit())
        {
            char c;
            if ((c = getchar()) == 'q' || c == 'Q')
            {
                *loopFlag = false;
                SetEvent(hQuitSignal);
            }
        }
        Sleep(100);
    }
}