//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAnisotropicFiltering.c
/// \brief Demonstrates how to access anisotropic filtering options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display anisotropic filtering support
void ShowSupport(IADLX3DAnisotropicFiltering* anisotropicFiltering);

// Get current anisotropic filtering state
void GetState(IADLX3DAnisotropicFiltering* anisotropicFiltering);

// Set anisotropic filtering state
void SetState(IADLX3DAnisotropicFiltering* anisotropicFiltering, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DAnisotropicFiltering* anisotropicFiltering);

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

            // Get AnisotropicFiltering interface
            IADLX3DAnisotropicFiltering* anisotropicFiltering = NULL;
            res = d3dSettingSrv->pVtbl->GetAnisotropicFiltering(d3dSettingSrv, gpu, &anisotropicFiltering);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(anisotropicFiltering);
            }

            // Release the AnisotropicFiltering interface
            if (anisotropicFiltering != NULL)
            {
                anisotropicFiltering->pVtbl->Release(anisotropicFiltering);
                anisotropicFiltering = NULL;
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

static char* getlevelStr(ADLX_ANISOTROPIC_FILTERING_LEVEL level)
{
    switch (level)
    {
    case AF_LEVEL_INVALID:
        return "Invalid";
    case AF_LEVEL_X2:
        return "2X";
    case AF_LEVEL_X4:
        return "4X";
    case AF_LEVEL_X8:
        return "8X";
    case AF_LEVEL_X16:
        return "16X";
    default:
        return "UNKNOWN";
    }
};

void ShowSupport(IADLX3DAnisotropicFiltering* anisotropicFiltering)
{
    adlx_bool supported = false;
    ADLX_RESULT res = anisotropicFiltering->pVtbl->IsSupported(anisotropicFiltering, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetState(IADLX3DAnisotropicFiltering* anisotropicFiltering)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = anisotropicFiltering->pVtbl->IsEnabled(anisotropicFiltering, &enabled);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsEnabled: %d\n", enabled);
    ADLX_ANISOTROPIC_FILTERING_LEVEL level;
    res = anisotropicFiltering->pVtbl->GetLevel(anisotropicFiltering, &level);
    if (ADLX_SUCCEEDED(res))
        printf("\tLevel: %s\n", getlevelStr(level));
}

void SetState(IADLX3DAnisotropicFiltering* anisotropicFiltering, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    res = anisotropicFiltering->pVtbl->SetEnabled(anisotropicFiltering, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        ADLX_ANISOTROPIC_FILTERING_LEVEL level;
        res = anisotropicFiltering->pVtbl->GetLevel(anisotropicFiltering, &level);
        if (ADLX_SUCCEEDED (res))
        {
            level = (level == AF_LEVEL_X2) ? AF_LEVEL_X4 : AF_LEVEL_X2;
            res = anisotropicFiltering->pVtbl->SetLevel(anisotropicFiltering, level);
            printf("\tSet level: %s  ,return code is: %d (0 means success)\n", getlevelStr(level), res);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display anisotropic filtering support\n");
    printf("\t->Press 2 to display current anisotropic filtering state\n");
    printf("\t->Press 3 to enable and change anisotropic filtering levels\n");
    printf("\t->Press 4 to disable anisotropic filtering\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLX3DAnisotropicFiltering* anisotropicFiltering)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display anisotropic filtering support
        case '1':
            ShowSupport(anisotropicFiltering);
            break;

            // Display current anisotropic filtering state
        case '2':
            GetState(anisotropicFiltering);
            break;

            // Enable and change anisotropic filtering levels
        case '3':
        case '4':
            SetState(anisotropicFiltering, num - '3');
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
