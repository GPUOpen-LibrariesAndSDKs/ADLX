//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainImageSharpening.c
/// \brief Demonstrates how to access AMD Radeon Image Sharpening and Image Sharpen Desktop options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include "SDK/Include/I3DSettings2.h"

// Display Image Sharpening and Image Sharpen Desktop support
void ShowImageSharpenSupport(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop);

// Get current Image Sharpening and Image Sharpen Desktop state & additional information
void GetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop);

// Set Image Sharpening and Image Sharpen Desktop state
void SetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop, int imageSharpeningIndex, int imageSharpenDesktopIndex);

// Disable Image Sharpening
void DisableImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop);

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

        IADLX3DSettingsServices2* d3dSettingSrv2 = NULL;
        res=d3dSettingSrv->pVtbl->QueryInterface(d3dSettingSrv, IID_IADLX3DSettingsServices2(), (&d3dSettingSrv2));

        if (ADLX_SUCCEEDED(res))
        {
                // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

            // Get Image Sharpening interface
            IADLX3DImageSharpening* d3dImageSharpen = NULL;
            res = d3dSettingSrv->pVtbl->GetImageSharpening(d3dSettingSrv, gpu, &d3dImageSharpen);

            // Get Image Sharpen Desktop interface
            IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop = NULL;
            res = d3dSettingSrv2->pVtbl->GetImageSharpenDesktop(d3dSettingSrv2, gpu, &d3dImageSharpenDesktop);

            if (ADLX_SUCCEEDED(res))
            {
                    MainMenu();
                    MenuControl(d3dImageSharpen, d3dImageSharpenDesktop);
            }

            // Release the Image Sharpening interface
            if (d3dImageSharpen != NULL)
            {
                d3dImageSharpen->pVtbl->Release(d3dImageSharpen);
                d3dImageSharpen = NULL;
            }

            // Release the Image Sharpen Desktop interface
            if (d3dImageSharpenDesktop != NULL)
            {
                d3dImageSharpenDesktop->pVtbl->Release(d3dImageSharpenDesktop);
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

        // Release the 3DSettingsService2 interface
        if (d3dSettingSrv2 != NULL)
        {
            d3dSettingSrv2->pVtbl->Release(d3dSettingSrv2);
            d3dSettingSrv2 = NULL;
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

void ShowImageSharpenSupport(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dImageSharpen->pVtbl->IsSupported(d3dImageSharpen, &supported);
    printf("\tImage Sharpening IsSupported: %d, return code is: %d(0 means success)\n", supported, res);

    supported = false;
    res = d3dImageSharpenDesktop->pVtbl->IsSupported(d3dImageSharpenDesktop, &supported);
    printf("\tImage Sharpen Desktop IsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dImageSharpen->pVtbl->IsEnabled(d3dImageSharpen, &enabled);
    printf("\tImage Sharpening IsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
    enabled = false;
    res = d3dImageSharpenDesktop->pVtbl->IsEnabled(d3dImageSharpenDesktop, &enabled);
    printf("\tImage Sharpen Desktop IsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
    adlx_int min;
    ADLX_IntRange range = { 0 };
    res = d3dImageSharpen->pVtbl->GetSharpness(d3dImageSharpen, &min);
    printf("\tCurrent Sharpness: %d, return code is: %d(0 means success)\n", min, res);
    res = d3dImageSharpen->pVtbl->GetSharpnessRange(d3dImageSharpen, &range);
    printf("\tSharpness limit [ %d , %d ], step: %d, return code is: %d(0 means success)\n", range.minValue, range.maxValue, range.step, res);
}

void SetImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop, int imageSharpeningIndex, int imageSharpenDesktopIndex)
{
    ADLX_RESULT res = d3dImageSharpen->pVtbl->SetEnabled(d3dImageSharpen, imageSharpeningIndex);
    printf("\tImage Sharpening Return code is: %d (0 means success)\n", res);

    if (imageSharpeningIndex && ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = d3dImageSharpenDesktop->pVtbl->SetEnabled(d3dImageSharpenDesktop, imageSharpenDesktopIndex);
        printf("\tImage Sharpen Desktop Return code is: %d (0 means success)\n", res);

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

void DisableImageSharpenState(IADLX3DImageSharpening* d3dImageSharpen, int index)
{
    ADLX_RESULT res = d3dImageSharpen->pVtbl->SetEnabled(d3dImageSharpen, index);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Image Sharpening and Image Sharpen Desktop support\n");
    printf("\t->Press 2 to get current Image Sharpening and Image Sharpen Desktop state & additional information\n");
    printf("\t->Press 3 to enable Image Sharpening and disable Image Sharpen Desktop\n");
    printf("\t->Press 4 to enable Image Sharpening and Image Sharpen Desktop\n");
    printf("\t->Press 5 to disable Image Sharpening\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DImageSharpening* d3dImageSharpen, IADLX3DImageSharpenDesktop* d3dImageSharpenDesktop)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Image Sharpening and Image Sharpen Desktop support
        case '1':
            ShowImageSharpenSupport(d3dImageSharpen, d3dImageSharpenDesktop);
            break;

            // Get current Image Sharpening and Image Sharpen Desktop state & additional information
        case '2':
            GetImageSharpenState(d3dImageSharpen, d3dImageSharpenDesktop);
            break;

            // Enable Image Sharpening and disable Image Sharpen Desktop
        case '3':
            SetImageSharpenState(d3dImageSharpen, d3dImageSharpenDesktop, true, false);
            break;

            //enable Image Sharpening and Image Sharpen Desktop
        case '4':
            SetImageSharpenState(d3dImageSharpen, d3dImageSharpenDesktop, true, true);
            break;

            //disable Image Sharpening
        case '5':
            DisableImageSharpenState(d3dImageSharpen, false);
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