//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainBoost.c
/// \brief Demonstrates how to access AMD Radeon Boost options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Boost support
void ShowBoostSupport(IADLX3DBoost* d3dBoost);

// Display current Boost state
void GetBoostState(IADLX3DBoost* d3dBoost);

// Set Boost state
void SetBoostState(IADLX3DBoost* d3dBoost, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DBoost* d3dBoost);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

            // Get Boost interface
            IADLX3DBoost* d3dBoost = NULL;
            res = d3dSettingSrv->pVtbl->GetBoost(d3dSettingSrv, gpu, &d3dBoost);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dBoost);
            }

            // Release Boost interface
            if (d3dBoost != NULL)
            {
                d3dBoost->pVtbl->Release(d3dBoost);
                d3dBoost = NULL;
            }

            // Release the GPU interface
            if (gpu != NULL)
            {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else
        {
            printf("Failed to get 3DSettings services\n");
        }

        // Release the 3DSettingsService interface
        if (d3dSettingSrv != NULL)
        {
            d3dSettingSrv->pVtbl->Release(d3dSettingSrv);
            d3dSettingSrv = NULL;
        }

        // Release the GPUs list interface
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowBoostSupport(IADLX3DBoost* d3dBoost)
{
    adlx_bool supported = false;
    d3dBoost->pVtbl->IsSupported(d3dBoost, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetBoostState(IADLX3DBoost* d3dBoost)
{
    adlx_bool enabled = false;
    d3dBoost->pVtbl->IsEnabled(d3dBoost, &enabled);
    printf("\tIsEnabled: %d\n", enabled);
    adlx_int minRes;
    ADLX_IntRange resolutionRange;
    d3dBoost->pVtbl->GetResolution(d3dBoost, &minRes);
    d3dBoost->pVtbl->GetResolutionRange(d3dBoost, &resolutionRange);
    printf("\tCurrent Resolution: %d\n,\tResolution limit [ %d , %d ], step: %d\n", minRes, resolutionRange.minValue, resolutionRange.maxValue, resolutionRange.step);
}

void SetBoostState(IADLX3DBoost* d3dBoost, int index)
{
    ADLX_RESULT res = d3dBoost->pVtbl->SetEnabled(d3dBoost, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int minRes;
        ADLX_IntRange resolutionRange;
        d3dBoost->pVtbl->GetResolution(d3dBoost, &minRes);
        d3dBoost->pVtbl->GetResolutionRange(d3dBoost, &resolutionRange);
        if (minRes != resolutionRange.minValue)
        {
            res = d3dBoost->pVtbl->SetResolution(d3dBoost, resolutionRange.minValue);
            printf("\tUse minimum resolution limit, return code is: %d (0 means success)\n", res);
        }
        else
        {
            res = d3dBoost->pVtbl->SetResolution(d3dBoost, resolutionRange.maxValue);
            printf("\tUse maximum resolution limit, return code is: %d (0 means success)\n", res);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Boost support\n");
    printf("\t->Press 2 to display current Boost state\n");
    printf("\t->Press 3 to enable Boost\n");
    printf("\t->Press 4 to disable Boost\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DBoost* d3dBoost)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Boost support
        case '1':
            ShowBoostSupport(d3dBoost);
            break;

            // Display current Boost state
        case '2':
            GetBoostState(d3dBoost);
            break;

            // Set Boost
        case '3':
        case '4':
            SetBoostState(d3dBoost, num - '3');
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