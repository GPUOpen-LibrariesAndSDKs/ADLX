//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUStressTest.c
/// \brief Demonstrates how to start GPU stress test, receive notifications when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISystem3.h"
#include <stdio.h>

// Check if GPU stress test is supported
void IsGPUStressTestSupported(IADLXGPUList* gpus);

// Start GPU stress test
void StartGPUStressTest(IADLXGPUList* gpus);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUList* gpus);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

HANDLE g_hEvent = NULL;

// GPU stress test finished event listener
adlx_bool ADLX_STD_CALL OnGPUStressTestFinished(IADLXGPUStressTestFinishedListener* pThis, IADLXGPU3* pGPU, adlx_bool result)
{
    const char* gpuName = NULL;
    ADLX_RESULT res = pGPU->pVtbl->Name(pGPU, &gpuName);
    printf("GPU Stress Test finished for GPU: %s, result: %s\n", gpuName, result ? "Passed" : "Failed");

    // Signal the event to indicate that the stress test is finished
    if (g_hEvent)
    {
        SetEvent(g_hEvent);
    }
    return true;
}


int main()
{
    // Create an event to signal when the GPU stress test is finished
    g_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get GPU list
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_SUCCEEDED(res))
        {
            // Display main menu options
            MainMenu();
            // Get and parse the selection
            MenuControl(gpus);

            if (gpus != NULL)
            {
                gpus->pVtbl->Release(gpus);
                gpus = NULL;
            }
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Check if GPU stress test is supported
void IsGPUStressTestSupported(IADLXGPUList* gpus)
{
    for (adlx_uint i = gpus->pVtbl->Begin(gpus); i != gpus->pVtbl->End(gpus); ++i)
    {
        IADLXGPU* gpu = NULL;
        gpus->pVtbl->At_GPUList(gpus, i, &gpu);
        IADLXGPU3* gpu3 = NULL;
        ADLX_RESULT res = gpu->pVtbl->QueryInterface(gpu, IID_IADLXGPU3(), (void**)&gpu3);
        if (ADLX_SUCCEEDED(res) && gpu3 != NULL)
        {
            adlx_bool supported = false;
            res = gpu3->pVtbl->IsSupportedStressTest(gpu3, &supported);
            if (ADLX_SUCCEEDED(res))
            {
                printf("GPU stress test is %s on GPU %d, result: %d\n", supported ? "supported" : "not supported", i, res);
            }
            else
            {
                printf("Failed to check if GPU stress test is supported, result: %d\n", res);
            }
            
            // Release the IADLXGPU3 interface
            if (gpu3 != NULL)
            {
                gpu3->pVtbl->Release(gpu3);
                gpu3 = NULL;
            }
        }
        else
        {
            printf("Failed to query IADLXGPU3 interface: %d\n", res);
        }

        // Release the IADLXGPU interface
        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }
    }
}

// Start GPU stress test
void StartGPUStressTest(IADLXGPUList* gpus)
{
    for (adlx_uint i = gpus->pVtbl->Begin(gpus); i != gpus->pVtbl->End(gpus); ++i)
    {
        IADLXGPU* gpu = NULL;
        gpus->pVtbl->At_GPUList(gpus, i, &gpu);
        IADLXGPU3* gpu3 = NULL;
        ADLX_RESULT res = gpu->pVtbl->QueryInterface(gpu, IID_IADLXGPU3(), (void**)&gpu3);
        if (ADLX_SUCCEEDED(res) && gpu3 != NULL)
        {
            adlx_bool supported = false;
            res = gpu3->pVtbl->IsSupportedStressTest(gpu3, &supported);
            if (ADLX_SUCCEEDED(res) && supported)
            {
                // Create a listener for GPU stress test finished event
                IADLXGPUStressTestFinishedListenerVtbl listenerVtbl = { &OnGPUStressTestFinished };
                IADLXGPUStressTestFinishedListener listener = { &listenerVtbl };

                const adlx_uint STRESS_TEST_DURATION_SECONDS = 15;
                ADLX_RESULT res = gpu3->pVtbl->StartStressTest(gpu3, &listener, STRESS_TEST_DURATION_SECONDS); // Start stress test for 15 seconds
                printf("Starting GPU stress test for GPU %d for %u seconds... result: %d\n", i, STRESS_TEST_DURATION_SECONDS, res);
                printf("Waiting for GPU stress test to finish......\n");
                // Wait for the stress test to finish
                auto waitResult = WaitForSingleObject(g_hEvent, STRESS_TEST_DURATION_SECONDS * 1000 * 2); // Wait for twice the duration to ensure we catch the event
                if (waitResult == WAIT_OBJECT_0)
                {
                    printf("GPU stress test finished on GPU %d.\n", i);
                }
                else
                {
                    printf("GPU stress test did not finish in the expected time on GPU %d.\n", i);
                }
                fflush(stdout);
                ResetEvent(g_hEvent); // Reset the event
            }
            else
            {
                printf("GPU stress test is not supported on GPU %d, result: %d\n", i, res);
            }

            // Release the IADLXGPU3 interface
            if (gpu3 != NULL)
            {
                gpu3->pVtbl->Release(gpu3);
                gpu3 = NULL;
            }
        }
        else
        {
            printf("Failed to query IADLXGPU3 interface: %d\n", res);
        }

        // Release the IADLXGPU interface
        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }
    }
}

// Main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to check if GPU stress test is supported\n");
    printf("\t->Press 2 to start GPU stress test\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXGPUList* gpus)
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}
