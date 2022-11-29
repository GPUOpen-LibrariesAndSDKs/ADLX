//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainRSR.c
/// \brief Demonstrates how to access AMD Radeon Super Resolution options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Radeon Super Resolution support
void ShowRadeonSuperResolutionSupport(IADLX3DRadeonSuperResolution* rsr);

// Display current Radeon Super Resolution state
void GetRadeonSuperResolutionState(IADLX3DRadeonSuperResolution* rsr);

// Set Radeon Super Resolution state
void SetRadeonSuperResolutionState(IADLX3DRadeonSuperResolution* rsr, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DRadeonSuperResolution* rsr);

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

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get RadeonSuperResolution interface
            IADLX3DRadeonSuperResolution* rsr = NULL;
            res = d3dSettingSrv->pVtbl->GetRadeonSuperResolution(d3dSettingSrv, &rsr);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(rsr);
            }
            else
            {
                printf("Get RadeonSuperResolution res: %d\n", res);
            }

            // Release the RadeonSuperResolution interface
            if (rsr != NULL)
            {
                rsr->pVtbl->Release(rsr);
                rsr = NULL;
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

void ShowRadeonSuperResolutionSupport(IADLX3DRadeonSuperResolution* rsr)
{
    adlx_bool supported = false;
    rsr->pVtbl->IsSupported(rsr, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetRadeonSuperResolutionState(IADLX3DRadeonSuperResolution* rsr)
{
    adlx_bool enabled = false;
    rsr->pVtbl->IsEnabled(rsr, &enabled);
    printf("\tIsEnabled: %d\n", enabled);
    adlx_int sharpness;
    ADLX_IntRange sharpnessRange;
    rsr->pVtbl->GetSharpness(rsr, &sharpness);
    rsr->pVtbl->GetSharpnessRange(rsr, &sharpnessRange);
    printf("\tCurrent sharpness: %d\n\tSharpness limit [ %d , %d ], step: %d\n", sharpness, sharpnessRange.minValue, sharpnessRange.maxValue, sharpnessRange.step);
}

void SetRadeonSuperResolutionState(IADLX3DRadeonSuperResolution* rsr, int index)
{
    ADLX_RESULT res = rsr->pVtbl->SetEnabled(rsr, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int sharpness;
        ADLX_IntRange sharpnessRange;
        rsr->pVtbl->GetSharpness(rsr, &sharpness);
        rsr->pVtbl->GetSharpnessRange(rsr, &sharpnessRange);
        if (sharpness != sharpnessRange.minValue)
        {
            res = rsr->pVtbl->SetSharpness(rsr, sharpnessRange.minValue);
            printf("\tUse minimum sharpness limit, return code is: %d (0 means success)\n", res);
        }
        else
        {
            res = rsr->pVtbl->SetSharpness(rsr, sharpnessRange.maxValue);
            printf("\tUse maximum sharpness limit, return code is: %d (0 means success)\n", res);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Radeon Super Resolution support\n");
    printf("\t->Press 2 to display current Radeon Super Resolution state\n");
    printf("\t->Press 3 to enable Radeon Super Resolution\n");
    printf("\t->Press 4 to disable Radeon Super Resolution\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DRadeonSuperResolution* rsr)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Radeon Super Resolution support
        case '1':
            ShowRadeonSuperResolutionSupport(rsr);
            break;

            // Display current Radeon Super Resolution state
        case '2':
            GetRadeonSuperResolutionState(rsr);
            break;

            // Set Radeon Super Resolution
        case '3':
        case '4':
            SetRadeonSuperResolutionState(rsr, num - '3');
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