//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncMultimedia.cpp
/// \brief Demonstrates how to receive notifications of changes in multimedia settings using ADLX. To receive the event, another application (such as Videoupscale) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IMultiMedia.h"
#include "SDK/Include/ISystem2.h"
#include "conio.h"
#include <iostream>
#include <string>
#include <map>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Block event to verify call back.
HANDLE blockEvent = nullptr;
HANDLE quitEvent = nullptr;

// Call back to handl changed events
class CallBackMultimediaSettingsChanged : public IADLXMultimediaChangedEventListener
{
public:

    adlx_bool ADLX_STD_CALL OnMultimediaChanged(IADLXMultimediaChangedEvent* pMultimediaChangedEvent)
    {
        // Define return code
        ADLX_RESULT res = ADLX_FAIL;

        // Get Multimedia service
        // Get IADLXSystem2 interface via IADLXSystem::QueryInterface
        IADLXSystem2Ptr system2;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));
        if (ADLX_SUCCEEDED(res))
        {
            // Get multimedia services 
            IADLXMultimediaServicesPtr multimediaServices;
            res = system2->GetMultimediaServices(&multimediaServices);
            if (ADLX_SUCCEEDED(res))
            {
                // Get the GPU interface
                IADLXGPUPtr gpu;
                pMultimediaChangedEvent->GetGPU(&gpu);

                ADLX_SYNC_ORIGIN origin = pMultimediaChangedEvent->GetOrigin();
                if (origin == SYNC_ORIGIN_EXTERNAL)
                {
                    if (pMultimediaChangedEvent->IsVideoUpscaleChanged())
                    {
                        std::cout << "\tIsVideoUpscaleChanged " << std::endl;
                    }
                    else if (pMultimediaChangedEvent->IsVideoSuperResolutionChanged())
                    {
                        std::cout << "\tIsVideoSuperResolutionChanged " << std::endl;
                    }
                }
            }
        }

        SetEvent(blockEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification
        return true;
    }
};

// Wait for quit signal
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
        blockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create quit event
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create event array
        HANDLE eventArray[] = { blockEvent, quitEvent };

        // Get IADLXSystem2 interface via IADLXSystem::QueryInterface
        IADLXSystem2Ptr system2;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));
        if (ADLX_SUCCEEDED(res))
        {
            // Get multimedia services 
            IADLXMultimediaServicesPtr multimediaServices;
            res = system2->GetMultimediaServices(&multimediaServices);
            if (ADLX_SUCCEEDED(res))
            {
                // Get Change handle
                IADLXMultimediaChangedHandlingPtr changeHandle;

                multimediaServices->GetMultimediaChangedHandling(&changeHandle);
                if (ADLX_SUCCEEDED(res))
                {
                    // Create call back
                    IADLXMultimediaChangedEventListener* call = new CallBackMultimediaSettingsChanged;

                    // Add call back
                    changeHandle->AddMultimediaEventListener(call);

                    // Create a thread to check quit event
                    bool loopFlag = true;
                    std::thread t{ QuitWait, &loopFlag };

                    std::cout << "\nWaiting for 3DSetting change event... Press Q/q to quit" << std::endl;
                    while (true)
                    {
                        // Wait for change event or request to quit
                        DWORD waitRet = WaitForMultipleObjects(2, eventArray, FALSE, INFINITE);
                        if (!loopFlag)
                        {
                            if (t.joinable())
                            {
                                t.join();
                            }
                            break;
                        }
                        ResetEvent(blockEvent);
                    }

                    // Remove call back
                    changeHandle->RemoveMultimediaEventListener(call);

                    // Delete call back
                    delete call;
                    call = nullptr;
                }
                    

            }
            else
                std::cout << "Failed to get multi media service" << std::endl;
        }
        else
            std::cout << "Failed to get IADLXSystem2" << std::endl;
    }
    else
    {
        std::cout << "Failed to init ADLX" << std::endl;
        return 0;
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Close event
    if (blockEvent)
        CloseHandle(blockEvent);

    // Pause for user see the print out
    system("pause");

    return 0;
}