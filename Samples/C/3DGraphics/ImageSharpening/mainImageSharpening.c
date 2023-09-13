//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainImageSharpening.c
/// \brief Demonstrates how to access AMD Radeon Image Sharpening options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Image Sharpening support
void ShowImageSharpenSupport(IADLX3DImageSharpening* d3dImageSharpen);

// Get current Image Sharpening state and additional information
void GetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen);

// Set Image Sharpening state
void SetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DImageSharpening* d3dImageSharpen);

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

            // Get Image Sharpening interface
            IADLX3DImageSharpening* d3dImageSharpen = NULL;
            res = d3dSettingSrv->pVtbl->GetImageSharpening(d3dSettingSrv, gpu, &d3dImageSharpen);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dImageSharpen);
            }

            // Release the Image Sharpening interface
            if (d3dImageSharpen != NULL)
            {
                d3dImageSharpen->pVtbl->Release(d3dImageSharpen);
                d3dImageSharpen = NULL;
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

    // Pause to see the printout
    system("pause");

    return 0;
}

void ShowImageSharpenSupport(IADLX3DImageSharpening* d3dImageSharpen)
{
    adlx_bool supported = false;
    d3dImageSharpen->pVtbl->IsSupported(d3dImageSharpen, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen)
{
    adlx_bool enabled = false;
    d3dImageSharpen->pVtbl->IsEnabled(d3dImageSharpen, &enabled);
    printf("\tIsEnabled: %d\n", enabled);
    adlx_int min;
    ADLX_IntRange range = { 0 };
    d3dImageSharpen->pVtbl->GetSharpness(d3dImageSharpen, &min);
    d3dImageSharpen->pVtbl->GetSharpnessRange(d3dImageSharpen, &range);
    printf("\tCurrent Sharpness: %d\n\tSharpness limit [ %d , %d ], step: %d\n", min, range.minValue, range.maxValue, range.step);
}

void SetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, int index)
{
    ADLX_RESULT res = d3dImageSharpen->pVtbl->SetEnabled(d3dImageSharpen, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int min;
        ADLX_IntRange range = { 0 };
        d3dImageSharpen->pVtbl->GetSharpness(d3dImageSharpen, &min);
        d3dImageSharpen->pVtbl->GetSharpnessRange(d3dImageSharpen, &range);
        if (min != range.minValue)
        {
            res = d3dImageSharpen->pVtbl->SetSharpness(d3dImageSharpen, range.minValue);
            printf("\tUse Minimum Sharpness limit: return code is: %d (0 means success)\n", res);
        }
        else
        {
            res = d3dImageSharpen->pVtbl->SetSharpness(d3dImageSharpen, range.maxValue);
            printf("\tUse Maximum Sharpness limit: return code is: %d (0 means success)\n", res);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Image Sharpening support\n");
    printf("\t->Press 2 to get current Image Sharpening state and additional information\n");
    printf("\t->Press 3 to enable and configure Image Sharpening\n");
    printf("\t->Press 4 to disable Image Sharpening\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DImageSharpening* d3dImageSharpen)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Image Sharpening support
        case '1':
            ShowImageSharpenSupport(d3dImageSharpen);
            break;

            // Get current Image Sharpening state and additional information
        case '2':
            GetImageSharpenState(d3dImageSharpen);
            break;

            // Set Image Sharpening state
        case '3':
        case '4':
            SetImageSharpenState(d3dImageSharpen, num - '3');
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