//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartAccessMemory.cpp
/// \brief Demonstrates how to control AMD SmartAccess Memory when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/ISmartAccessMemory.h"
#include "SDK/Include/IGPUTuning1.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

static HANDLE SAMEvent = nullptr;

class GPUTuningChangedListener : public IADLXGPUTuningChangedListener
{
public:

    bool ADLX_STD_CALL OnGPUTuningChanged(IADLXGPUTuningChangedEvent* pGPUTuningChangedEvent)
    {
        IADLXGPUTuningChangedEvent1Ptr pGPUTuningChangedEvent1 = IADLXGPUTuningChangedEvent1Ptr(pGPUTuningChangedEvent);
        adlx_bool SAMChange = pGPUTuningChangedEvent1->IsSmartAccessMemoryChanged();
        if (SAMChange)
        {
            adlx_bool enabled = false, completed = false;
            pGPUTuningChangedEvent1->GetSmartAccessMemoryStatus(&enabled, &completed);
        }

        SetEvent(SAMEvent);
        return true;
    }
};

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Find the first GPU index that supports AMD SmartAccess Memory. Return -1 if all GPUs are not supported
adlx_uint GetGPUIndexSupportSAM(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus);

// Display AMD SmartAccess Memory support status on a GPU
void ShowSmartAccessMemorySupport(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus);

// Display AMD SmartAccess Memory enabled status
void ShowSmartAccessMemoryState(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus);

// Set AMD SmartAccess Memory state
void SetSmartAccessMemoryState(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        IADLXGPUTuningServicesPtr gpuTuningService;
        res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices(&gpuTuningService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get gpuTuningService1 via gpuTuningService::QueryInterface()
            IADLXGPUTuningServices1Ptr gpuTuningService1;
            res = gpuTuningService->QueryInterface(gpuTuningService1->IID(), reinterpret_cast<void**>(&gpuTuningService1));
            if (ADLX_SUCCEEDED(res))
            {
                IADLXGPUTuningChangedHandlingPtr gpuTuningHandling;
                res = gpuTuningService1->GetGPUTuningChangedHandling(&gpuTuningHandling);
                if (ADLX_SUCCEEDED(res))
                {
                    // Add listener
                    SAMEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
                    static GPUTuningChangedListener listener;
                    ADLX_RESULT eventRes = gpuTuningHandling->AddGPUTuningEventListener(&listener);

                    // Menu
                    IADLXGPUListPtr gpus;
                    res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
                    if (ADLX_SUCCEEDED(res))
                    {
                        // Display main menu options
                        MainMenu();

                        // Get and execute the choice
                        MenuControl(gpuTuningService1, gpus);
                    }
                    else
                        std::cout << "Failed to get GPU list" << std::endl;

                    // Remove listener
                    if (ADLX_SUCCEEDED(eventRes))
                        eventRes = gpuTuningHandling->RemoveGPUTuningEventListener(&listener);
                }
                else
                    std::cout << "Failed to get GPU Tuning Changed Handling" << std::endl;
            }
            else
                std::cout << "Failed to get gpuTuningService1" << std::endl;
        }
        else
            std::cout << "Failed to get gpuTuningService" << std::endl;
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display AMD SmartAccess Memory supported GPUs" << std::endl;
    std::cout << "\t->Press 2 to display AMD SmartAccess Memory enabled status" << std::endl;
    std::cout << "\t->Press 3 to set the AMD SmartAccess Memory state" << std::endl;
    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display AMD SmartAccess Memory support status on a GPU
        case '1':
            ShowSmartAccessMemorySupport(gpuTuningService1, gpus);
            break;

            // Display AMD SmartAccess Memory enabled status
        case '2':
            ShowSmartAccessMemoryState(gpuTuningService1, gpus);
            break;

            // Set AMD SmartAccess Memory state
        case '3':
            SetSmartAccessMemoryState(gpuTuningService1, gpus);
            break;

            // Display menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
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

// Find the first GPU index that supports AMD SmartAccess Memory. Return -1 if all GPUs are not supported
adlx_uint GetGPUIndexSupportSAM(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus)
{
    adlx_uint supportedIndex = -1;
    IADLXGPUPtr oneGPU;
    IADLXSmartAccessMemoryPtr smartAccessMemory;
    for (auto index = gpus->Begin(); index != gpus->End(); ++index)
    {
        ADLX_RESULT res = gpus->At(index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            // Get the AMD SmartAccess Memory interface
            res = gpuTuningService1->GetSmartAccessMemory(oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool supported = false;
                ADLX_RESULT res = smartAccessMemory->IsSupported(&supported);
                if (ADLX_SUCCEEDED(res) && supported)
                {
                    supportedIndex = index;
                    break;
                }
            }
        }
    }
    return supportedIndex;
}

// Display AMD SmartAccess Memory support status on a GPU
void ShowSmartAccessMemorySupport(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        std::cout << "All GPUs doesn't support AMD SmartAccess Memory" << std::endl;
    else
        std::cout << "The " << (index + 1) << "th GPU support AMD SmartAccess Memory" << std::endl;
}

// Display AMD SmartAccess Memory enabled status
void ShowSmartAccessMemoryState(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        std::cout << "All GPUs doesn't support AMD SmartAccess Memory" << std::endl;
    else
    {
        IADLXGPUPtr oneGPU;
        ADLX_RESULT res = gpus->At(index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXSmartAccessMemoryPtr smartAccessMemory;
            res = gpuTuningService1->GetSmartAccessMemory(oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool enabled = false;
                res = smartAccessMemory->IsEnabled(&enabled);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The AMD SmartAccess Memory is " << (enabled ? "enabled" : "disabled") << " on the " << (index + 1) << "th GPU" << std::endl;
                else
                    std::cout << "Call IsEnabled() failed" << std::endl;
            }
            else
                std::cout << "Failed to get smartAccessMemory" << std::endl;
        }
        else
            std::cout << "Failed to get the GPU" << std::endl;
    }
}

// Set AMD SmartAccess Memory state
void SetSmartAccessMemoryState(IADLXGPUTuningServices1Ptr gpuTuningService1, IADLXGPUListPtr gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        std::cout << "All GPUs doesn't support AMD SmartAccess Memory" << std::endl;
    else
    {
        IADLXGPUPtr oneGPU;
        ADLX_RESULT res = gpus->At(index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXSmartAccessMemoryPtr smartAccessMemory;
            res = gpuTuningService1->GetSmartAccessMemory(oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool enabled = false;
                res = smartAccessMemory->IsEnabled(&enabled);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "Currently AMD SmartAccess Memory is " << (enabled ? "enabled" : "disabled") << " on " << (index + 1) << "th GPU" << std::endl;
                else
                    std::cout << "Call IsEnabled() failed" << std::endl;
                res = smartAccessMemory->SetEnabled(!enabled);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "Set AMD SmartAccess Memory to " << (!enabled ? "enabled" : "disabled") << " for " << (index + 1) << "th GPU" << std::endl;
                else
                    std::cout << "Call SetEnabled() failed" << std::endl;

                // First event received quickly before SAM start
                WaitForSingleObject(SAMEvent, 2000);

                // When receive the first event, avoid calling any other ADLX method, and if any UI application is running, we must close it to avoid crashing
                // Close(application)......

                // Second event received after SAM completed, the maximum consuming time less than 20 seconds.
                WaitForSingleObject(SAMEvent, 20000);

                // Now SAM completed, we can restart the UI application, and continue to call ADLX function
                // Start(application)......

                res = smartAccessMemory->IsEnabled(&enabled);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "After setting, AMD SmartAccess Memory is " << (enabled ? "enabled" : "disabled") << " on " << (index + 1) << "th GPU" << std::endl;
                else
                    std::cout << "Call IsEnabled() failed" << std::endl;
            }
            else
                std::cout << "Failed to get smartAccessMemory" << std::endl;
        }
        else
            std::cout << "Failed to get the GPU" << std::endl;
    }
}