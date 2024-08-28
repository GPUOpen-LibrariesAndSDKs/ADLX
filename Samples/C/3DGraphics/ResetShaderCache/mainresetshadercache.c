
//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainResetShaderCache.c
/// \brief Demonstrates how to access reset shader cache options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display reset shader cache support
void ShowSupport(IADLX3DResetShaderCache* resetShaderCache);

// Reset GPU shader cache
void ResetShaderCache(IADLX3DResetShaderCache* resetShaderCache);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DResetShaderCache* resetShaderCache);

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

            // Get ResetShaderCache interface
            IADLX3DResetShaderCache* resetShaderCache = NULL;
            res = d3dSettingSrv->pVtbl->GetResetShaderCache(d3dSettingSrv, gpu, &resetShaderCache);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(resetShaderCache);
            }

            // Release the ResetShaderCache interface
            if (resetShaderCache != NULL)
            {
                resetShaderCache->pVtbl->Release(resetShaderCache);
                resetShaderCache = NULL;
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

void ShowSupport(IADLX3DResetShaderCache* resetShaderCache)
{
    adlx_bool supported = false;
    ADLX_RESULT res = resetShaderCache->pVtbl->IsSupported(resetShaderCache, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void ResetShaderCache(IADLX3DResetShaderCache* resetShaderCache)
{
    ADLX_RESULT res = resetShaderCache->pVtbl->ResetShaderCache(resetShaderCache);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to display reset shader cache support\n");
    printf("\t->Press 2 to reset GPU shader cache\n");
    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DResetShaderCache* resetShaderCache)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display reset shader cache support
        case '1':
            ShowSupport(resetShaderCache);
            break;

            // Reset GPU shader cache
        case '2':
            ResetShaderCache(resetShaderCache);
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
