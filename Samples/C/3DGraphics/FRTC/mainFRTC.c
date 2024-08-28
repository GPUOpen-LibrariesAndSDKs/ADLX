//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFRTC.c
/// \brief Demonstrates how to access AMD Frame Rate Target Control (FRTC) options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display FRTC support
void ShowFRTCSupport(IADLX3DFrameRateTargetControl* frtc);

// Get and display current FRTC state
void GetFRTCState(IADLX3DFrameRateTargetControl* frtc);

// Set FRTC state
void SetFRTCState(IADLX3DFrameRateTargetControl* frtc, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DFrameRateTargetControl* frtc);

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

            // Get FRTC interface
            IADLX3DFrameRateTargetControl* frtc = NULL;
            res = d3dSettingSrv->pVtbl->GetFrameRateTargetControl(d3dSettingSrv, gpu, &frtc);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(frtc);
            }

            // Release the FRTC interface
            if (frtc != NULL)
            {
                frtc->pVtbl->Release(frtc);
                frtc = NULL;
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

void ShowFRTCSupport(IADLX3DFrameRateTargetControl* frtc)
{
    adlx_bool supported = false;
    ADLX_RESULT res = frtc->pVtbl->IsSupported(frtc, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetFRTCState(IADLX3DFrameRateTargetControl* frtc)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = frtc->pVtbl->IsEnabled(frtc, &enabled);
    printf("\tIsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
    adlx_int fps;
    ADLX_IntRange range = { 0 };
    res = frtc->pVtbl->GetFPS(frtc, &fps);
    printf("\tCurrent FPS: %d, return code is: %d(0 means success)\n", fps, res);
    res = frtc->pVtbl->GetFPSRange(frtc, &range);
    printf("\tFPS limit [ %d , %d ], step: %d, return code is: %d(0 means success)\n", range.minValue, range.maxValue, range.step, res);
}

void SetFRTCState(IADLX3DFrameRateTargetControl* frtc, int index)
{
    ADLX_RESULT res = frtc->pVtbl->SetEnabled(frtc, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int fps;
        ADLX_IntRange range = { 0 };
        frtc->pVtbl->GetFPS(frtc, &fps);
        frtc->pVtbl->GetFPSRange(frtc, &range);
        if (fps != range.minValue)
        {
            res = frtc->pVtbl->SetFPS(frtc, range.minValue);
            printf("\tUse minimum FPS limit: return code is: %d (0 means success)\n", res);
        }
        else
        {
            res = frtc->pVtbl->SetFPS(frtc, range.maxValue);
            printf("\tUse maximum FPS limit: return code is: %d (0 means success)\n", res);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display FRTC support\n");
    printf("\t->Press 2 to get and display current FRTC state\n");
    printf("\t->Press 3 to enable and configure FRTC\n");
    printf("\t->Press 4 to disable FRTC\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DFrameRateTargetControl* frtc)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display FRTC support
        case '1':
            ShowFRTCSupport(frtc);
            break;

            // Get and display current FRTC state
        case '2':
            GetFRTCState(frtc);
            break;

            // Set FRTC state
        case '3':
        case '4':
            SetFRTCState(frtc, num - '3');
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