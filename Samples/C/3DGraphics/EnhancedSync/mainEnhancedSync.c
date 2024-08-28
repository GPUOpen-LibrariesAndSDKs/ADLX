//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainEnhancedSync.c
/// \brief Demonstrates how to access AMD Radeon Enhanced Sync options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Enhanced Sync support
void ShowEnhancedSyncSupport(IADLX3DEnhancedSync* d3dEnhancedSync);

// Get current Enhanced Sync state
void GetEnhancedSyncState(IADLX3DEnhancedSync* d3dEnhancedSync);

// Set Enhanced Sync state
void SetEnhancedSyncState(IADLX3DEnhancedSync* d3dEnhancedSync, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DEnhancedSync* d3dEnhancedSync);

// Wait for exit with error message
int WaitAndExit(char* msg, int retCode);

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

            // Get EnhancedSync interface
            IADLX3DEnhancedSync* d3dEnhancedSync;
            res = d3dSettingSrv->pVtbl->GetEnhancedSync(d3dSettingSrv, gpu, &d3dEnhancedSync);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dEnhancedSync);
            }

            // Release the EnhancedSync interface
            if (d3dEnhancedSync != NULL)
            {
                d3dEnhancedSync->pVtbl->Release(d3dEnhancedSync);
                d3dEnhancedSync = NULL;
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

void ShowEnhancedSyncSupport(IADLX3DEnhancedSync* d3dEnhancedSync)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dEnhancedSync->pVtbl->IsSupported(d3dEnhancedSync, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetEnhancedSyncState(IADLX3DEnhancedSync* d3dEnhancedSync)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dEnhancedSync->pVtbl->IsEnabled(d3dEnhancedSync, &enabled);
    printf("\tIsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
}

void SetEnhancedSyncState(IADLX3DEnhancedSync* d3dEnhancedSync, int index)
{
    ADLX_RESULT res = d3dEnhancedSync->pVtbl->SetEnabled(d3dEnhancedSync, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Enhanced Sync support\n");
    printf("\t->Press 2 to get Enhanced Sync state\n");
    printf("\t->Press 3 to enable Enhanced Sync\n");
    printf("\t->Press 4 to disable Enhanced Sync\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DEnhancedSync* d3dEnhancedSync)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Enhanced Sync support
        case '1':
            ShowEnhancedSyncSupport(d3dEnhancedSync);
            break;

            // Get and display current Enhanced Sync state
        case '2':
            GetEnhancedSyncState(d3dEnhancedSync);
            break;

            // Set Enhanced Sync state
        case '3':
        case '4':
            SetEnhancedSyncState(d3dEnhancedSync, num - '3');
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
