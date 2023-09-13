//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiLag.c
/// \brief Demonstrates how to access AMD Radeon Anti-Lag options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Anti-Lag support
void ShowAntiLagSupport(IADLX3DAntiLag* d3dAntiLag);

// Display current Anti-Lag state
void GetAntiLagState(IADLX3DAntiLag* d3dAntiLag);

// Set Anti-Lag state
void SetAntiLagState(IADLX3DAntiLag* d3dAntiLag, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DAntiLag* d3dAntiLag);

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

            // Get AntiLag interface
            IADLX3DAntiLag* d3dAntiLag = NULL;
            res = d3dSettingSrv->pVtbl->GetAntiLag(d3dSettingSrv, gpu, &d3dAntiLag);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dAntiLag);
            }

            // Release the d3dAntiLag interface
            if (d3dAntiLag != NULL)
            {
                d3dAntiLag->pVtbl->Release(d3dAntiLag);
                d3dAntiLag = NULL;
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

void ShowAntiLagSupport(IADLX3DAntiLag* d3dAntiLag)
{
    adlx_bool supported = false;
    d3dAntiLag->pVtbl->IsSupported(d3dAntiLag, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetAntiLagState(IADLX3DAntiLag* d3dAntiLag)
{
    adlx_bool enabled = false;
    d3dAntiLag->pVtbl->IsEnabled(d3dAntiLag, &enabled);
    printf("\tIsEnabled: %d\n", enabled);
}

void SetAntiLagState(IADLX3DAntiLag* d3dAntiLag, int index)
{
    ADLX_RESULT res = d3dAntiLag->pVtbl->SetEnabled(d3dAntiLag, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Anti-Lag support\n");
    printf("\t->Press 2 to display current Anti-Lag state\n");
    printf("\t->Press 3 to enable Anti-Lag\n");
    printf("\t->Press 4 to disable Anti-Lag\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DAntiLag* d3dAntiLag)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Anti-Lag support
        case '1':
            ShowAntiLagSupport(d3dAntiLag);
            break;

            // Display current Anti-Lag state
        case '2':
            GetAntiLagState(d3dAntiLag);
            break;

            // Set Anti-Lag state
        case '3':
        case '4':
            SetAntiLagState(d3dAntiLag, num - '3');
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
