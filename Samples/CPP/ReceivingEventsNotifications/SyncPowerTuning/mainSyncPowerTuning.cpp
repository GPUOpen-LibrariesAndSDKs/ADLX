//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncPowerTuning.cpp
/// \brief Demonstrates how to receive notifications of changes in power tuning settings using ADLX. To receive the event, another application (such as SmartShiftMax) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPowerTuning.h"
#include "SDK/Include/ISystem1.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Block event to verify call back
HANDLE blockEvent = nullptr;

// Call back to handle changed events
class CallBackPowerTuningChanged : public IADLXPowerTuningChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnPowerTuningChanged(IADLXPowerTuningChangedEvent* pPowerTuningChangedEvent)
    {
        ADLX_SYNC_ORIGIN origin = pPowerTuningChangedEvent->GetOrigin();
        if (origin == SYNC_ORIGIN_EXTERNAL)
        {
            if (pPowerTuningChangedEvent->IsSmartShiftMaxChanged())
            {
                std::cout << "\tSmartShiftMaxChanged" << std::endl;
            }
        }
        SetEvent(blockEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification.
        return true;
    }
};

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

        // Get IADLXSystem1 interface via IADLXSystem::QueryInterface
        IADLXSystem1Ptr system1;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem1::IID(), reinterpret_cast<void**>(&system1));
        if (ADLX_SUCCEEDED(res))
        {
            // Get power tuning service 
            IADLXPowerTuningServicesPtr powerTuningService;
            res = system1->GetPowerTuningServices(&powerTuningService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get Change handle
                IADLXPowerTuningChangedHandlingPtr changeHandle;
                res = powerTuningService->GetPowerTuningChangedHandling(&changeHandle);
                if (ADLX_SUCCEEDED(res))
                {
                    // Create call back
                    IADLXPowerTuningChangedListener* call = new CallBackPowerTuningChanged;

                    // Add call back
                    changeHandle->AddPowerTuningEventListener(call);

                    // Waits for power tuning sync with a timeout of 60s
                    while (true)
                    {
                        std::cout << "\nWaiting for power tuning change event (60s)...\n";
                        DWORD waitRet = WaitForSingleObject(blockEvent, 60000);
                        if (waitRet == WAIT_TIMEOUT)
                        {
                            std::cout << "=== Wait timeout(60s), ready to quit ===\n";
                            break;
                        }
                        ResetEvent(blockEvent);
                    }

                    // Remove call back
                    changeHandle->RemovePowerTuningEventListener(call);

                    // Delete call back
                    delete call;
                    call = nullptr;
                }
                else
                    std::cout << "Failed to get power tuning changed handling interface" << std::endl;
            }
            else
                std::cout << "Failed to get power tuning service" << std::endl;
        }
        else
            std::cout << "Failed to get IADLXSystem1" << std::endl;
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