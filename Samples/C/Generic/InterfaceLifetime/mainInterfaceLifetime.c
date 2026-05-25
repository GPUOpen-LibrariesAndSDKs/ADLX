//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainInterfaceLifetime.c
/// \brief Demonstrates how to manage the lifetime of ADLX interfaces in a long-running application, where ADLX is
/// initialized at startup and terminated from an unrelated shutdown path.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"

// The interfaces this application keeps for its lifetime.
//
// These are global only because this sample models an application whose startup and shutdown are in separate functions.
// Being global does NOT keep them valid: they must be released explicitly in ReleaseADLXInterfaces before ADLX is
// terminated, because the termination unloads the ADLX library.
static IADLXGPUList* g_gpus = NULL;
static IADLXPerformanceMonitoringServices* g_perfMonitoringService = NULL;

// Releases every interface held for the lifetime of the application.
// Must be called before every ADLX termination, on every path that reaches one.
static void ReleaseADLXInterfaces()
{
    if (NULL != g_gpus)
    {
        g_gpus->pVtbl->Release(g_gpus);
        g_gpus = NULL;
    }

    if (NULL != g_perfMonitoringService)
    {
        g_perfMonitoringService->pVtbl->Release(g_perfMonitoringService);
        g_perfMonitoringService = NULL;
    }
}

// Initializes ADLX and acquires the interfaces used for the lifetime of the application
static ADLX_RESULT StartUp()
{
    IADLXSystem* sys = NULL;

    // Initialize ADLX
    ADLX_RESULT res = ADLXHelper_Initialize();
    if (ADLX_FAILED(res))
    {
        printf("ADLX initialization failed\n");
        return res;
    }

    // Get system services
    sys = ADLXHelper_GetSystemServices();

    // Get Performance Monitoring services
    res = sys->pVtbl->GetPerformanceMonitoringServices(sys, &g_perfMonitoringService);
    if (ADLX_FAILED(res))
    {
        printf("Get performance monitoring services failed\n");

        // Early exit of a partially completed initialization.
        // Nothing has been acquired yet on this path, but the same release is used on every path so that the ordering
        // does not depend on how far the initialization progressed.
        ReleaseADLXInterfaces();
        ADLXHelper_Terminate();
        return res;
    }

    // Get GPU list
    res = sys->pVtbl->GetGPUs(sys, &g_gpus);
    if (ADLX_FAILED(res))
    {
        printf("Get GPU list failed\n");

        // Early exit of a partially completed initialization.
        // g_perfMonitoringService is already acquired on this path and must be released before the termination.
        ReleaseADLXInterfaces();
        ADLXHelper_Terminate();
        return res;
    }

    return ADLX_OK;
}

// Uses the interfaces acquired at startup
static void DoWork()
{
    adlx_uint it = 0;

    if (NULL == g_gpus)
        return;

    printf("\nGPUs reported by ADLX:\n");
    for (it = g_gpus->pVtbl->Begin(g_gpus); it != g_gpus->pVtbl->End(g_gpus); ++it)
    {
        IADLXGPU* oneGPU = NULL;
        if (ADLX_SUCCEEDED(g_gpus->pVtbl->At_GPUList(g_gpus, it, &oneGPU)))
        {
            const char* gpuName = NULL;
            if (ADLX_SUCCEEDED(oneGPU->pVtbl->Name(oneGPU, &gpuName)))
                printf("\t%s\n", gpuName);

            // oneGPU is a local interface and is released here, at the end of the iteration
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

// Terminates ADLX
static void ShutDown()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Release the interfaces before the termination.
    // ADLXHelper_Terminate unloads the ADLX library, so calling Release on an interface after this point dispatches into
    // unloaded code and results in an access violation.
    ReleaseADLXInterfaces();

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("\nDestroy ADLX res: %d\n", res);
}

int main()
{
    // In a real application these three calls are in unrelated places: the startup path, the running application, and
    // the shutdown path. The interfaces are not local to the function that terminates ADLX, so the correct ordering
    // must be arranged explicitly.
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
