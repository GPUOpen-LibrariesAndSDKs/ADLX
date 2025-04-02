//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVideoupscale.c
/// \brief Demonstrates how to control video upscale when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include//IMultimedia.h"
#include "SDK/Include/ISystem2.h"

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLXVideoUpscale* videoupscale);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display video upscale support
void ShowVideoupscaleSupport(IADLXVideoUpscale* videoupscale);

// Display current video upscale state
void GetVideoupscaleState(IADLXVideoUpscale* videoupscale);

// Set video upscale state
void SetVideoupscaleState(IADLXVideoUpscale* videoupscale, int index);


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

        // Get IADLXSystem2 interface
        IADLXSystem2* system2 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem2(), (void**)(&system2));

        if (ADLX_SUCCEEDED(res))
        {

            // Get multimedia services
            IADLXMultimediaServices* multimediaServices = NULL;
            res = system2->pVtbl->GetMultimediaServices(system2, &multimediaServices);

            if (ADLX_SUCCEEDED(res))
            {
                // Get GPU interface
                IADLXGPU* gpu = NULL;
                adlx_uint index = 0;
                res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

                //Get video upscale interface
                IADLXVideoUpscale* videoupscale = NULL;
                multimediaServices->pVtbl->GetVideoUpscale(multimediaServices, gpu, &videoupscale);

                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(videoupscale);
                }

                // Release the video upscale interface
                if (videoupscale != NULL)
                {
                    videoupscale->pVtbl->Release(videoupscale);
                    videoupscale = NULL;
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
                printf("Failed to get multimedia services\n");
            }

            // Release the multimedia services interface
            if (multimediaServices != NULL)
            {
                multimediaServices->pVtbl->Release(multimediaServices);
                multimediaServices = NULL;
            }
        }
        else
        {
            printf("Failed to get IADLXSystem2 interface\n");
        }

        // Release IADLXSystem2 interface
        if (system2 != NULL)
        {
            system2->pVtbl->Release(system2);
            system2 = NULL;
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

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Videoupscale support\n");
    printf("\t->Press 2 to display current Videoupscale state\n");
    printf("\t->Press 3 to enable Videoupscale\n");
    printf("\t->Press 4 to disable Videoupscale\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void ShowVideoupscaleSupport(IADLXVideoUpscale* videoupscale)
{
    adlx_bool supported = false;
    ADLX_RESULT res = videoupscale->pVtbl->IsSupported(videoupscale, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetVideoupscaleState(IADLXVideoUpscale* videoupscale)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = videoupscale->pVtbl->IsEnabled(videoupscale, &enabled);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsEnabled: %d\n", enabled);
    adlx_int minSharp;
    ADLX_IntRange sharpnessRange;
    res = videoupscale->pVtbl->GetSharpness(videoupscale, &minSharp);
    if (ADLX_SUCCEEDED(res))
        printf("\tCurrent Resolution: %d\n", minSharp);
    res = videoupscale->pVtbl->GetSharpnessRange(videoupscale, &sharpnessRange);
    if (ADLX_SUCCEEDED(res))
        printf("\tResolution limit [ %d , %d ], step: %d\n", sharpnessRange.minValue, sharpnessRange.maxValue, sharpnessRange.step);
}

void SetVideoUpscaleState(IADLXVideoUpscale* videoupscale, int index)
{
    ADLX_RESULT res = videoupscale->pVtbl->SetEnabled(videoupscale, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int minSharp;
        ADLX_IntRange sharpnessRange;
        ADLX_RESULT res1 = videoupscale->pVtbl->GetSharpness(videoupscale, &minSharp);
        ADLX_RESULT res2 = videoupscale->pVtbl->GetSharpnessRange(videoupscale, &sharpnessRange);
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            if (minSharp != sharpnessRange.minValue)
            {
                res = videoupscale->pVtbl->SetSharpness(videoupscale, sharpnessRange.minValue);
                printf("\tUse minimum resolution limit, return code is: %d (0 means success)\n", res);
            }
            else
            {
                res = videoupscale->pVtbl->SetSharpness(videoupscale, sharpnessRange.maxValue);
                printf("\tUse maximum resolution limit, return code is: %d (0 means success)\n", res);
            }
        }
    }
}


void MenuControl(IADLXVideoUpscale* videoupscale)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display video upscale support
        case '1':
            ShowVideoupscaleSupport(videoupscale);
            break;

            // Display current video upscale state
        case '2':
            GetVideoupscaleState(videoupscale);
            break;

            // Set video upscale
        case '3':
        case '4':
            SetVideoUpscaleState(videoupscale, num - '3');
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