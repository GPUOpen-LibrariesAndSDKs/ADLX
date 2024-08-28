//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file main3DSettingsEvent.cpp
/// \brief Demonstrates how to register and unregister for notifications when 3D Graphics settings change, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
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
class CallBack3DSettingsChanged : public IADLX3DSettingsChangedListener
{
  public:
    adlx_bool ADLX_STD_CALL On3DSettingsChanged(IADLX3DSettingsChangedEvent* p3DSettingsChangedEvent) override
    {
        ADLX_RESULT res;
        IADLXGPUPtr gpu;
        res = p3DSettingsChangedEvent->GetGPU(&gpu);
        if (ADLX_SUCCEEDED(res))
        {
            char uniqueName[128] = "Unknown";
            GPUUniqueName(gpu, uniqueName);
            adlx_bool antiLagChanged = p3DSettingsChangedEvent->IsAntiLagChanged();
            std::cout << "\tGPU: " << uniqueName << " AntiLag changed: " << antiLagChanged << std::endl;
        }

        SetEvent(blockEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification
        return true;
    }
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
        // Create block event
        blockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // GetGPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (!gpus->Empty() && ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPUPtr gpuInfo;
            adlx_uint index = 0;
            res = gpus->At(index, &gpuInfo);

            // Get change handle
            IADLX3DSettingsChangedHandlingPtr changeHandle;
            res = d3dSettingSrv->Get3DSettingsChangedHandling(&changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Create call back
                IADLX3DSettingsChangedListener* call = new CallBack3DSettingsChanged;

                // Add call back
                ADLX_RESULT addListenerRes = changeHandle->Add3DSettingsEventListener(call);
                
                // Change anti-lag state
                IADLX3DAntiLagPtr antiLag;
                d3dSettingSrv->GetAntiLag(gpuInfo, &antiLag);
                adlx_bool enable;
                antiLag->IsEnabled(&enable);

                std::cout << "\nWaiting for 3DSettings change event (5s)...\n";
                antiLag->SetEnabled(!enable);
                WaitForSingleObject(blockEvent, 5000);

                if (ADLX_SUCCEEDED (addListenerRes))
                {
                    // Remove call back
                    res = changeHandle->Remove3DSettingsEventListener(call);
                    if (ADLX_FAILED (res))
                        std::cout << "\nRemove 3DSettings event listener failed" << std::endl;
                }

                // Delete call back
                delete call;
                call = nullptr;
            }
        }
        else
        {
            std::cout << "Failed to get 3DSettings services" << std::endl;
        }
    }
    else
    {
        std::cout << "ADLX initialization failed" << std::endl;
        system("pause");
        return 0;
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Close event
    if (blockEvent)
        CloseHandle(blockEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}

void GPUUniqueName(IADLXGPUPtr gpu, char* uniqueName)
{
    if (nullptr != gpu && nullptr != uniqueName)
    {
        const char* gpuName = nullptr;
        ADLX_RESULT res1 = gpu->Name(&gpuName);
        adlx_int id;
        ADLX_RESULT res2 = gpu->UniqueId(&id);
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            sprintf_s(uniqueName, 128, "name:%s, id:%d", gpuName, id);
    }
}