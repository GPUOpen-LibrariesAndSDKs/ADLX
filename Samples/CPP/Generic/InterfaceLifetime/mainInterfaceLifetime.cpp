//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainInterfaceLifetime.cpp
/// \brief Demonstrates how to manage the lifetime of ADLX interfaces in a long-running application, where ADLX is
/// initialized at startup and terminated from an unrelated shutdown path.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// The interfaces this application keeps for its lifetime.
//
// These are global only because this sample models an application whose startup and shutdown are in separate functions.
// Being global does NOT keep them valid: their destructors run during process shutdown, which is after ADLX is terminated.
// They must be released explicitly in ReleaseADLXInterfaces before ADLX is terminated.
static IADLXGPUListPtr g_gpus;
static IADLXPerformanceMonitoringServicesPtr g_perfMonitoringService;

// Releases every interface held for the lifetime of the application.
// Must be called before every ADLX termination, on every path that reaches one.
static void ReleaseADLXInterfaces()
{
    // Assigning nullptr to a smart pointer releases the underlying interface
    g_gpus = nullptr;
    g_perfMonitoringService = nullptr;
}

// Initializes ADLX and acquires the interfaces used for the lifetime of the application
static ADLX_RESULT StartUp()
{
    // Initialize ADLX
    ADLX_RESULT res = g_ADLXHelp.Initialize();
    if (ADLX_FAILED(res))
    {
        std::cout << "ADLX initialization failed" << std::endl;
        return res;
    }

    // Get Performance Monitoring services
    res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&g_perfMonitoringService);
    if (ADLX_FAILED(res))
    {
        std::cout << "Get performance monitoring services failed" << std::endl;

        // Early exit of a partially completed initialization.
        // Nothing has been acquired yet on this path, but the same release is used on every path so that the ordering
        // does not depend on how far the initialization progressed.
        ReleaseADLXInterfaces();
        g_ADLXHelp.Terminate();
        return res;
    }

    // Get GPU list
    res = g_ADLXHelp.GetSystemServices()->GetGPUs(&g_gpus);
    if (ADLX_FAILED(res))
    {
        std::cout << "Get GPU list failed" << std::endl;

        // Early exit of a partially completed initialization.
        // g_perfMonitoringService is already acquired on this path and must be released before the termination.
        ReleaseADLXInterfaces();
        g_ADLXHelp.Terminate();
        return res;
    }

    return ADLX_OK;
}

// Uses the interfaces acquired at startup
static void DoWork()
{
    if (g_gpus == nullptr)
        return;

    std::cout << "\nGPUs reported by ADLX:" << std::endl;
    for (adlx_uint it = g_gpus->Begin(); it != g_gpus->End(); ++it)
    {
        IADLXGPUPtr oneGPU;
        if (ADLX_SUCCEEDED(g_gpus->At(it, &oneGPU)))
        {
            const char* gpuName = nullptr;
            if (ADLX_SUCCEEDED(oneGPU->Name(&gpuName)))
                std::cout << "\t" << gpuName << std::endl;
        }

        // oneGPU is a local interface and is released here, at the end of the iteration
    }
}

// Terminates ADLX
static void ShutDown()
{
    // Release the interfaces before the termination.
    // Terminate unloads the ADLX library, so an interface released after this point dispatches into unloaded code and
    // results in an access violation. The crash occurs during process shutdown, after the last line of application code
    // has run, which makes it appear unrelated to ADLX.
    ReleaseADLXInterfaces();

    // Destroy ADLX
    ADLX_RESULT res = g_ADLXHelp.Terminate();
    std::cout << "\nDestroy ADLX res: " << res << std::endl;
}

int main()
{
    // In a real application these three calls are in unrelated places: the startup path, the running application, and
    // the shutdown path. The interfaces are not local to the function that terminates ADLX, so the correct ordering
    // cannot be obtained from their scope and must be arranged explicitly.
    if (ADLX_FAILED(StartUp()))
    {
        system("pause");
        return 0;
    }

    DoWork();

    ShutDown();

    // Pause to see the print out
    system("pause");

    return 0;
}
