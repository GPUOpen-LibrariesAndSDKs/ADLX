//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainMorphologicAntiAliasing.c
/// \brief Demonstrates how to access morphological anti-aliasing options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display morphological anti-aliasing support
void ShowSupport(IADLX3DMorphologicalAntiAliasing* mAntiAliasing);

// Get current morphological anti-aliasing state of the GPU
void GetState(IADLX3DMorphologicalAntiAliasing* mAntiAliasing);

// Set morphological anti-aliasing state
void SetState(IADLX3DMorphologicalAntiAliasing* mAntiAliasing, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DMorphologicalAntiAliasing* mAntiAliasing);

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

            // Get MorphologicAntiAliasing interface
            IADLX3DMorphologicalAntiAliasing* mAntiAliasing = NULL;
            res = d3dSettingSrv->pVtbl->GetMorphologicalAntiAliasing(d3dSettingSrv, gpu, &mAntiAliasing);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(mAntiAliasing);
            }

            // Release the d3dAntiLag interface
            if (mAntiAliasing != NULL)
            {
                mAntiAliasing->pVtbl->Release(mAntiAliasing);
                mAntiAliasing = NULL;
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
            printf("Failed to get 3DSettings Services\n");
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

    // Pause to see the printout
    system("pause");

    return 0;
}

void ShowSupport(IADLX3DMorphologicalAntiAliasing* mAntiAliasing)
{
    adlx_bool supported = false;
    ADLX_RESULT res = mAntiAliasing->pVtbl->IsSupported(mAntiAliasing, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetState(IADLX3DMorphologicalAntiAliasing* mAntiAliasing)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = mAntiAliasing->pVtbl->IsEnabled(mAntiAliasing, &enabled);
    printf("\tIsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
}

void SetState(IADLX3DMorphologicalAntiAliasing* mAntiAliasing, int index)
{
    ADLX_RESULT res = mAntiAliasing->pVtbl->SetEnabled(mAntiAliasing, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display morphological anti-aliasing support\n");
    printf("\t->Press 2 to get current morphological anti-aliasing state of the GPU\n");
    printf("\t->Press 3 to enable morphological anti-aliasing\n");
    printf("\t->Press 4 to disable morphological anti-aliasing\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DMorphologicalAntiAliasing* mAntiAliasing)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display morphological anti-aliasing support
        case '1':
            ShowSupport(mAntiAliasing);
            break;

            // Get and display current morphological anti-aliasing state of the GPU
        case '2':
            GetState(mAntiAliasing);
            break;

            // Set morphological anti-aliasing state
        case '3':
        case '4':
            SetState(mAntiAliasing, num - '3');
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
