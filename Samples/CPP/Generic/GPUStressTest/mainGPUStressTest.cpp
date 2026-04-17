//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUStressTest.cpp
/// \brief Demonstrates how to start GPU stress test, receive notifications when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/ISystem3.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Check if GPU stress test is supported
void IsGPUStressTestSupported(const IADLXGPUListPtr& gpus);

// Start GPU stress test
void StartGPUStressTest(const IADLXGPUListPtr& gpus);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXGPUListPtr& gpus);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

HANDLE g_hEvent = nullptr;

// GPU stress test finished event listener
class GPUStressTestFinishedListener : public IADLXGPUStressTestFinishedListener
{
public:
    adlx_bool ADLX_STD_CALL OnGPUStressTestFinished(IADLXGPU3* pGPU, adlx_bool result) override
    {
        const char* gpuName = nullptr;
        ADLX_RESULT res = pGPU->Name(&gpuName);
        std::cout << "GPU Stress Test finished for GPU: " << gpuName << ", result: " << (result ? "Passed" : "Failed") << std::endl;
        // Signal the event to indicate that the stress test is finished
        if (g_hEvent)
        {
            SetEvent(g_hEvent);
        }
        return true;
    }
};


int main()
{
    // Create an event to signal when the GPU stress test is finished
    g_hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU list
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_SUCCEEDED(res) && !gpus->Empty())
        {
            // Display main menu options
            MainMenu();
            // Get and parse the selection
            MenuControl(gpus);
        }
        else
        {
            std::cout << "Failed to get the GPU list" << std::endl;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

void IsGPUStressTestSupported(const IADLXGPUListPtr& gpus)
{
    for (adlx_uint i = gpus->Begin(); i != gpus->End(); ++i)
    {
        IADLXGPUPtr gpu;
        gpus->At(i, &gpu);
        IADLXGPU3Ptr gpu3;
        ADLX_RESULT res = gpu->QueryInterface(IADLXGPU3::IID(), (void**)&gpu3);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool supported = false;
            res = gpu3->IsSupportedStressTest(&supported);
            if (ADLX_SUCCEEDED(res))
            {
                std::cout << "GPU stress test is " << (supported ? "supported" : "not supported") << " on GPU " << i << std::endl;
            }
            else
            {
                std::cout << "Failed to check if GPU stress test is supported, result: " << res << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to query IADLXGPU3 interface" << std::endl;
        }
    }
}

// Start GPU stress test
void StartGPUStressTest(const IADLXGPUListPtr& gpus)
{
    for (adlx_uint i = gpus->Begin(); i != gpus->End(); ++i)
    {
        IADLXGPUPtr gpu;
        gpus->At(i, &gpu);
        IADLXGPU3Ptr gpu3;
        ADLX_RESULT res = gpu->QueryInterface(IADLXGPU3::IID(), (void**)&gpu3);
        if (ADLX_SUCCEEDED(res) && gpu3 != nullptr)
        {
            adlx_bool supported = false;
            res = gpu3->IsSupportedStressTest(&supported);
            if (ADLX_SUCCEEDED(res) && supported)
            {
                // Create GPU stress test finished listener
                GPUStressTestFinishedListener* listener = new GPUStressTestFinishedListener();
                constexpr adlx_uint STRESS_TEST_DURATION_SECONDS = 15;
                ADLX_RESULT ret = gpu3->StartStressTest(listener, STRESS_TEST_DURATION_SECONDS); // Start stress test for 15 seconds
                std::cout << "Starting GPU stress test for GPU " << i << " for " << STRESS_TEST_DURATION_SECONDS << " seconds... result: " << ret << std::endl;
                std::cout << "Waiting for GPU stress test to finish......" << std::endl;
                // Wait for the stress test to finish
                auto waitResult = WaitForSingleObject(g_hEvent, STRESS_TEST_DURATION_SECONDS * 1000 * 2); // Wait for twice the duration to ensure we catch the event
                if (waitResult == WAIT_OBJECT_0)
                {
                    std::cout << "GPU stress test finished on GPU " << i << std::endl;
                }
                else
                {
                    std::cout << "GPU stress test did not finish in the expected time on GPU " << i << std::endl;
                }
                ResetEvent(g_hEvent);
                delete listener; // Clean up the listener
                listener = nullptr;
            }
            else
            {
                std::cout << "GPU stress test is not supported on GPU " << i << ", result: " << res << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to query IADLXGPU3 interface" << std::endl;
        }
    }
}

void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to check if GPU stress test is supported" << std::endl;
    std::cout << "\t->Press 2 to start GPU stress test" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXGPUListPtr& gpus)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Check if GPU stress test is supported
        case '1':
            IsGPUStressTestSupported(gpus);
            break;
        // Start GPU stress test
        case '2':
            StartGPUStressTest(gpus);
            break;
        // Display main menu options
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
