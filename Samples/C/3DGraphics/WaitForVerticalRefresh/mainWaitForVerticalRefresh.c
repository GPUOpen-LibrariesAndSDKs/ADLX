//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainWaitForVerticalRefresh.c
/// \brief Demonstrates how to access VSync options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display VSync support
void ShowvsyncSupport(IADLX3DWaitForVerticalRefresh* vsync);

// Get current VSync state
void GetvsyncState(IADLX3DWaitForVerticalRefresh* vsync);

// Set VSync mode
void SetvsyncMode(IADLX3DWaitForVerticalRefresh* vsync, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DWaitForVerticalRefresh* vsync);

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

            // Get VSync interface
            IADLX3DWaitForVerticalRefresh* vsync = NULL;
            res = d3dSettingSrv->pVtbl->GetWaitForVerticalRefresh(d3dSettingSrv, gpu, &vsync);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(vsync);
            }

            // Release VSync interface
            if (vsync != NULL)
            {
                vsync->pVtbl->Release(vsync);
                vsync = NULL;
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

static char* getModeStr(ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode)
{
    switch (mode)
    {
    case WFVR_ALWAYS_OFF:
        return "Always Off";
    case WFVR_OFF_UNLESS_APP_SPECIFIES:
        return "Off (unless specified by the application)";
    case WFVR_ON_UNLESS_APP_SPECIFIES:
        return "On (unless specified by the application)";
    case WFVR_ALWAYS_ON:
        return "Always On";
    default:
        return "UNKNOWN";
    }
};

void ShowvsyncSupport(IADLX3DWaitForVerticalRefresh* vsync)
{
    adlx_bool supported = false;
    ADLX_RESULT res = vsync->pVtbl->IsSupported(vsync, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetvsyncState(IADLX3DWaitForVerticalRefresh* vsync)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = vsync->pVtbl->IsEnabled(vsync, &enabled);
    printf("\tIsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
    ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode = WFVR_ALWAYS_OFF;
    res = vsync->pVtbl->GetMode(vsync, &mode);
    printf("\tMode: %s, return code is: %d(0 means success)\n", getModeStr(mode), res);
}

void SetvsyncMode(IADLX3DWaitForVerticalRefresh* vsync, int index)
{
    ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode = WFVR_ALWAYS_OFF;
    mode = (ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)(mode + index);
    ADLX_RESULT res = vsync->pVtbl->SetMode(vsync, mode);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display VSync support\n");
    printf("\t->Press 2 to get current VSync state\n");
    printf("\t->Press 3 to set VSync to Always Off\n");
    printf("\t->Press 4 to set VSync to Off (unless specified by the application)\n");
    printf("\t->Press 5 to set VSync to On (unless specified by the application)\n");
    printf("\t->Press 6 to set VSync to Always On\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DWaitForVerticalRefresh* vsync)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display VSync support
        case '1':
            ShowvsyncSupport(vsync);
            break;

            // Get and display current VSync state
        case '2':
            GetvsyncState(vsync);
            break;

            // Set VSync model
        case '3':
        case '4':
        case '5':
        case '6':
            SetvsyncMode(vsync, num - '3');
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
