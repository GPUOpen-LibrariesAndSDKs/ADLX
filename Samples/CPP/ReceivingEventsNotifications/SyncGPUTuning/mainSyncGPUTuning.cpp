//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSyncGPUTuning.cpp
/// \brief Demonstrates how to receive notifications of changes in GPU tuning settings using ADLX. To receive the event, another application (such as GPUAutoTuning) must be used to change these settings.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUTuning1.h"
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

// Get the GPU unique name
void GPUUniqueName(IADLXGPUPtr gpu, char* uniqueName);

// Call back to handle changed events
class CallBackGPUTuningChanged : public IADLXGPUTuningChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnGPUTuningChanged(IADLXGPUTuningChangedEvent* pGPUTuningChangedEvent) override
    {
        IADLXGPUTuningChangedEvent1* pGPUTuningChangedEvent1 = nullptr;
        pGPUTuningChangedEvent->QueryInterface(L"IADLXGPUTuningChangedEvent1", reinterpret_cast<void**>(&pGPUTuningChangedEvent1));
        ADLX_SYNC_ORIGIN origin = pGPUTuningChangedEvent->GetOrigin();
        if (origin == SYNC_ORIGIN_EXTERNAL)
        {
            // Get GPU
            IADLXGPUPtr gpu;
            pGPUTuningChangedEvent->GetGPU(&gpu);
            char uniqueName[128] = "Unknown";
            GPUUniqueName(gpu, uniqueName);
            std::cout << "GPU: " << uniqueName << "Get sync event, update required" << std::endl;

            if (pGPUTuningChangedEvent->IsAutomaticTuningChanged())
            {
                std::cout << "\tAutomaticTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent->IsPresetTuningChanged())
            {
                std::cout << "\tPresetTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent->IsManualGPUCLKTuningChanged())
            {
                std::cout << "\tManualGPUCLKTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent->IsManualVRAMTuningChanged()) 
            {
                std::cout << "\tManualVRAMTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent->IsManualFanTuningChanged())
            {
                std::cout << "\tManualFanTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent->IsManualPowerTuningChanged())
            {
                std::cout << "\tManualPowerTuningChanged" << std::endl;
            }
            else if (pGPUTuningChangedEvent1->IsSmartAccessMemoryChanged())
            {
                std::cout << "\tSmartAccessMemoryChanged" << std::endl;
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

        // Get GPUTuning service
        IADLXGPUTuningServicesPtr gpuTuningSrv;
        res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices(&gpuTuningSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get Change handle
            IADLXGPUTuningChangedHandlingPtr changeHandle;
            res = gpuTuningSrv->GetGPUTuningChangedHandling(&changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Create call back
                IADLXGPUTuningChangedListener* call = new CallBackGPUTuningChanged;

                // Add call back
                changeHandle->AddGPUTuningEventListener(call);

                // Waits for GPUTuning sync with a timeout of 60s
                while (true)
                {
                    std::cout << "\nWaiting for GPUTuning change event (60s)...\n";
                    DWORD waitRet = WaitForSingleObject(blockEvent, 60000);
                    if (waitRet == WAIT_TIMEOUT)
                    {
                        std::cout << "=== Wait timeout(60s), ready to quit ===\n";
                        break;
                    }
                    ResetEvent(blockEvent);
                }

                // Remove call back
                changeHandle->RemoveGPUTuningEventListener(call);

                // Delete call back
                delete call;
                call = nullptr;
            }
        }
        else
        {
            std::cout << "Failed to get GPUTuning Services" << std::endl;
        }
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

void GPUUniqueName(IADLXGPUPtr gpu, char* uniqueName)
{
    if (nullptr != gpu && nullptr != uniqueName)
    {
        const char* gpuName = nullptr;
        gpu->Name(&gpuName);
        adlx_int id;
        gpu->UniqueId(&id);
        sprintf_s(uniqueName, 128, "name:%s, id:%d", gpuName, id);
    }
}