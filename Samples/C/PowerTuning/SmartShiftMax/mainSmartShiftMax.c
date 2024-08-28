//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartShiftMax.c
/// \brief Demonstrates how to control AMD SmartShift Max when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPowerTuning.h"
#include "SDK/Include/ISystem1.h"

// Display AMD SmartShift max support
void ShowSmartShiftMaxSupport(IADLXSmartShiftMax* ssm);

// Display current AMD SmartShift max state
void ShowSmartShiftMaxSate(IADLXSmartShiftMax* ssm);

// Set AMD SmartShift max bias mode
void SetSmartShiftMaxBiasMode(IADLXSmartShiftMax* ssm, int index);

// Set AMD SmartShift max bias value
void SetSmartShiftMaxBiasValue(IADLXSmartShiftMax* ssm);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXSmartShiftMax* ssm);

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

        // Get IADLXSystem1 interface
        IADLXSystem1* system1 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem1(), (void**)(&system1));
        if (ADLX_SUCCEEDED(res))
        {
            // Get power tuning services
            IADLXPowerTuningServices* powerTuningServices = NULL;
            res = system1->pVtbl->GetPowerTuningServices(system1, &powerTuningServices);

            // Get AMD SmartShift Max interface
            IADLXSmartShiftMax* ssm = NULL;
            res = powerTuningServices->pVtbl->GetSmartShiftMax(powerTuningServices, &ssm);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(ssm);
            }

            // Release AMD SmartShift Max interface
            if (ssm != NULL)
            {
                ssm->pVtbl->Release(ssm);
                ssm = NULL;
            }

            // Release power tuning services interface
            if (powerTuningServices != NULL)
            {
                powerTuningServices->pVtbl->Release(powerTuningServices);
                powerTuningServices = NULL;
            }
        }
        else
        {
            printf("Failed to get IADLXSystem1 interface\n");
        }

        // Release IADLXSystem1 interface
        if (system1 != NULL)
        {
            system1->pVtbl->Release(system1);
            system1 = NULL;
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

void ShowSmartShiftMaxSupport(IADLXSmartShiftMax* ssm)
{
    adlx_bool supported = false;
    ssm->pVtbl->IsSupported(ssm, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void ShowSmartShiftMaxSate(IADLXSmartShiftMax* ssm)
{
    ADLX_SSM_BIAS_MODE mode;
    ADLX_RESULT ret = ssm->pVtbl->GetBiasMode(ssm, &mode);
    if (ADLX_SUCCEEDED(ret))
        printf("\tBias mode: %s\n", (mode == SSM_BIAS_MANUAL ? "manual" : "auto"));
    else
        printf("\tFailed to get bias mode, error code: %d\n", ret);

    adlx_int bias = 0;
    ret = ssm->pVtbl->GetBias(ssm, &bias);
    if (ADLX_SUCCEEDED(ret))
        printf("\tBias value: %d\n", bias);
    else
        printf("\tFailed to get bias value, error code: %d\n", ret);

    ADLX_IntRange range;
    ret = ssm->pVtbl->GetBiasRange(ssm, &range);
    if (ADLX_SUCCEEDED(ret))
        printf("\tBias range: [ %d, %d ], step: %d\n", range.minValue, range.maxValue, range.step);
    else
        printf("\tFailed to get bias range, error code: %d\n", ret);
}

void SetSmartShiftMaxBiasMode(IADLXSmartShiftMax* ssm, int index)
{
    ADLX_SSM_BIAS_MODE mode = index == 0 ? SSM_BIAS_MANUAL : SSM_BIAS_AUTO;
    ADLX_RESULT res = ssm->pVtbl->SetBiasMode(ssm, mode);
    printf("\tSet bias mode %s, return code: %d\n", (mode == SSM_BIAS_MANUAL ? "manual" : "auto"), res);
}

void SetSmartShiftMaxBiasValue(IADLXSmartShiftMax* ssm)
{
    adlx_int bias = 0;
    ssm->pVtbl->GetBias(ssm, &bias);
    ADLX_IntRange range;
    ssm->pVtbl->GetBiasRange(ssm, &range);
    adlx_int base = (range.maxValue + range.minValue) / 2;
    adlx_int value = bias == base ? base + range.step : base;
    ADLX_RESULT res = ssm->pVtbl->SetBias(ssm, value);
    printf("\tSet bias value: %d, return code: %d\n", value, res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to display AMD SmartShift Max support\n");
    printf("\t->Press 2 to display AMD SmartShift Max bias value, bias mode, and bias range\n");
    printf("\t->Press 3 to set AMD SmartShift Max bias mode to Manual\n");
    printf("\t->Press 4 to set AMD SmartShift Max bias mode to Auto\n");
    printf("\t->Press 5 to set AMD SmartShift Max bias value\n");
    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXSmartShiftMax* ssm)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display AMD SmartShift max support
        case '1':
            ShowSmartShiftMaxSupport(ssm);
            break;

            // Display current AMD SmartShift max state
        case '2':
            ShowSmartShiftMaxSate(ssm);
            break;

            // Set AMD SmartShift max bias mode
        case '3':
        case '4':
            SetSmartShiftMaxBiasMode(ssm, num - '3');
            break;

            // Set AMD SmartShift max bias value
        case '5':
            SetSmartShiftMaxBiasValue(ssm);
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
