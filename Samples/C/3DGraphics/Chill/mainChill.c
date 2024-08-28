//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainChill.c
/// \brief Demonstrates how to access AMD Radeon Chill options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Chill support
void ShowChillSupport(IADLX3DChill* d3dChill);

// Display current Chill state
void GetChillState(IADLX3DChill* d3dChill);

// Set Chill state
void SetChillState(IADLX3DChill* d3dChill, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DChill* d3dChill);

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

            // Get Chill interface
            IADLX3DChill* d3dChill = NULL;
            res = d3dSettingSrv->pVtbl->GetChill(d3dSettingSrv, gpu, &d3dChill);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dChill);
            }

            // Release Chill interface
            if (d3dChill != NULL)
            {
                d3dChill->pVtbl->Release(d3dChill);
                d3dChill = NULL;
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

        // Release 3DSettingsService interface
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

void ShowChillSupport(IADLX3DChill* d3dChill)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dChill->pVtbl->IsSupported(d3dChill, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetChillState(IADLX3DChill* d3dChill)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dChill->pVtbl->IsSupported(d3dChill, &supported);
    if (supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = d3dChill->pVtbl->IsEnabled(d3dChill, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tIsEnabled: %d\n", enabled);
        adlx_int minFPS, maxFPS;
        ADLX_IntRange fpsRange;
        res = d3dChill->pVtbl->GetMinFPS(d3dChill, &minFPS);
        if (ADLX_SUCCEEDED(res))
            printf("\tCurrent MinFPS: %d\n", minFPS);
        res = d3dChill->pVtbl->GetMaxFPS(d3dChill, &maxFPS);
        if (ADLX_SUCCEEDED(res))
            printf("\tCurrent MaxFPS: %d\n", maxFPS);
        res = d3dChill->pVtbl->GetFPSRange(d3dChill, &fpsRange);
        if (ADLX_SUCCEEDED(res))
            printf("\tFPSSet limit [ %d, %d ], step: %d\n", fpsRange.minValue, fpsRange.maxValue, fpsRange.step);
    }
    else
    {
        printf("\t Chill feature is not Supported\n");
    }
}

void SetChillState(IADLX3DChill* d3dChill, int index)
{
    ADLX_RESULT res = d3dChill->pVtbl->SetEnabled(d3dChill, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int minFPS, maxFPS;
        ADLX_IntRange fpsRange;
        d3dChill->pVtbl->GetMinFPS(d3dChill, &minFPS);
        d3dChill->pVtbl->GetMaxFPS(d3dChill, &maxFPS);
        d3dChill->pVtbl->GetFPSRange(d3dChill, &fpsRange);
        printf("\t\tEnter two space delimited integers:[minFPS, maxFPS]\n");

        int coeffs[2] = {fpsRange.minValue, fpsRange.maxValue};

        for (int i = 0; i < 2; i++)
        {
            scanf_s("%d", &coeffs[i]);
        }

        res = d3dChill->pVtbl->SetMinFPS(d3dChill, coeffs[0]);
        printf("\tSet minimum FPS return code is: %d (0 means success)\n", res);
        res = d3dChill->pVtbl->SetMaxFPS(d3dChill, coeffs[1]);
        printf("\tSet maximum FPS return code is: %d (0 means success)\n", res);
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Chill support\n");
    printf("\t->Press 2 to display current Chill state\n");
    printf("\t->Press 3 to enable Chill\n");
    printf("\t->Press 4 to disable Chill\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DChill* d3dChill)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Chill support
        case '1':
            ShowChillSupport(d3dChill);
            break;

            // Display current Chill state
        case '2':
            GetChillState(d3dChill);
            break;

            // Set Chill state
        case '3':
        case '4':
            SetChillState(d3dChill, num - '3');
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
