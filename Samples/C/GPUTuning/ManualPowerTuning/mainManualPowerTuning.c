//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualPowerTuning.c
/// \brief Demonstrates how to control manual power tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUManualPowerTuning.h"
#include "SDK/Include/IGPUTuning.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXManualPowerTuning* manualPowerTuning);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode,
                IADLXGPUTuningServices* gpuTuningService,
                IADLXGPUList* gpus,
                IADLXGPU* oneGPU,
                IADLXInterface* manualPowerTuningIfc,
                IADLXManualPowerTuning* manualPowerTuning);

// Display power limit range
void ShowGetPowerLimitRange(IADLXManualPowerTuning* manualPowerTuning);

// Display current power limit
void ShowGetPowerLimit(IADLXManualPowerTuning* manualPowerTuning);

// Set power limit
void ShowSetPowerLimit(IADLXManualPowerTuning* manualPowerTuning);

//Show to check TDC  limit is supported
void ShowTDCLimitSupported(IADLXManualPowerTuning* manualPowerTuning);

// Show how to get TDC limit range.
void ShowGetTDCLimitRange(IADLXManualPowerTuning* manualPowerTuning);

// Show how to get current TDC limit.
void ShowGetTDCLimit(IADLXManualPowerTuning* manualPowerTuning);

// Show how to set TDC limit.
void ShowSetTDCLimit(IADLXManualPowerTuning* manualPowerTuning);


int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        IADLXSystem* sys = ADLXHelper_GetSystemServices();
        IADLXGPUTuningServices* gpuTuningService = NULL;
        IADLXGPUList* gpus = NULL;
        IADLXGPU* oneGPU = NULL;
        IADLXInterface* manualPowerTuningIfc = NULL;
        IADLXManualPowerTuning* manualPowerTuning = NULL;

        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningService);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU tuning services failed", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU list failed", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        res = gpus->pVtbl->At_GPUList(gpus, 0, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == NULL)
            return WaitAndExit("\tGet GPU failed", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        adlx_bool supported = false;
        res = gpuTuningService->pVtbl->IsSupportedManualPowerTuning(gpuTuningService, oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
            return WaitAndExit("\tThis GPU doesn't supported manual power tuning", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        res = gpuTuningService->pVtbl->GetManualPowerTuning(gpuTuningService, oneGPU, &manualPowerTuningIfc);
        if (ADLX_FAILED(res) || manualPowerTuningIfc == NULL)
            return WaitAndExit("\tGet manual power tuning interface failed", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        res = manualPowerTuningIfc->pVtbl->QueryInterface(manualPowerTuningIfc, IID_IADLXManualPowerTuning(), (void**)&manualPowerTuning);
        if (manualPowerTuning == NULL)
            return WaitAndExit("\tGet manual power tuning failed", 0, gpuTuningService, gpus, oneGPU, manualPowerTuningIfc, manualPowerTuning);

        // Display main menu options
        MainMenu();

        // Get and execute the choice
        MenuControl(manualPowerTuning);

        // Release the manualPowerTuning interface
        if (manualPowerTuning != NULL)
        {
            manualPowerTuning->pVtbl->Release(manualPowerTuning);
            manualPowerTuning = NULL;
        }
        if (manualPowerTuningIfc != NULL)
        {
            manualPowerTuningIfc->pVtbl->Release(manualPowerTuningIfc);
            manualPowerTuningIfc = NULL;
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
        if (gpuTuningService != NULL)
        {
            gpuTuningService->pVtbl->Release(gpuTuningService);
            gpuTuningService = NULL;
        }
    }
    else
    {
        printf("\tg_ADLXHelp initialize failed\n");
        system("pause");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    printf("\tChoose from the following options:\n");
	printf("\t->Press 1 to display power limit range\n");
	printf("\t->Press 2 to display current power limit\n");
	printf("\t->Press 3 to set power limit\n");
	printf("\t->Press 4 to check if TDC Limit is supported\n");
    printf("\t->Press 5 to display TDC limit range\n");
    printf("\t->Press 6 to display current TDC limit\n");
    printf("\t->Press 7 to set TDC limit\n");
    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(IADLXManualPowerTuning* manualPowerTuning)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display power limit range
        case '1':
            ShowGetPowerLimitRange(manualPowerTuning);
            break;

        // Display current power limit
        case '2':
            ShowGetPowerLimit(manualPowerTuning);
            break;

        // Set power limit
        case '3':
            ShowSetPowerLimit(manualPowerTuning);
            break;
            // Show how to check TDC limit is supported.
        case '4':
            ShowTDCLimitSupported(manualPowerTuning);
            break;
            // Show how to get TDC limit range.
        case '5':
            ShowGetTDCLimitRange(manualPowerTuning);
            break;
            // Show how to get current TDC limit.
        case '6':
            ShowGetTDCLimit(manualPowerTuning);
            break;
            // Show how to set TDC limit.
        case '7':
            ShowSetTDCLimit(manualPowerTuning);
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

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode,
                IADLXGPUTuningServices* gpuTuningService,
                IADLXGPUList* gpus,
                IADLXGPU* oneGPU,
                IADLXInterface* manualPowerTuningIfc,
                IADLXManualPowerTuning* manualPowerTuning)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    // Release the manualPowerTuning interface
    if (manualPowerTuning != NULL)
    {
        manualPowerTuning->pVtbl->Release(manualPowerTuning);
        manualPowerTuning = NULL;
    }
    if (manualPowerTuningIfc != NULL)
    {
        manualPowerTuningIfc->pVtbl->Release(manualPowerTuningIfc);
        manualPowerTuningIfc = NULL;
    }
    if (oneGPU != NULL)
    {
        oneGPU->pVtbl->Release(oneGPU);
        oneGPU = NULL;
    }
    if (gpus != NULL)
    {
        gpus->pVtbl->Release(gpus);
        gpus = NULL;
    }
    if (gpuTuningService != NULL)
    {
        gpuTuningService->pVtbl->Release(gpuTuningService);
        gpuTuningService = NULL;
    }

    // Destroy ADLX
    ADLX_RESULT res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    system("pause");
    return retCode;
}

// Display power limit range
void ShowGetPowerLimitRange(IADLXManualPowerTuning* manualPowerTuning)
{
    ADLX_IntRange powerRange;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetPowerLimitRange(manualPowerTuning, &powerRange);
    printf("\tPower limit range: (%d, %d), return code is: %d(0 means success)\n", powerRange.minValue, powerRange.maxValue, res);
}

// Display current power limit
void ShowGetPowerLimit(IADLXManualPowerTuning* manualPowerTuning)
{
    adlx_int powerLimit;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetPowerLimit(manualPowerTuning, &powerLimit);
    printf("\tCurrent power limit: %d, return code is: %d(0 means success)\n", powerLimit, res);
}

// Set power limit
void ShowSetPowerLimit(IADLXManualPowerTuning* manualPowerTuning)
{
    ADLX_IntRange powerRange;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetPowerLimitRange(manualPowerTuning, &powerRange);
    res = manualPowerTuning->pVtbl->SetPowerLimit(manualPowerTuning, powerRange.minValue + (powerRange.maxValue - powerRange.minValue) / 2);
    printf("\tSet power limit %s\n", (ADLX_SUCCEEDED (res) ? "succeeded" : "failed"));
    adlx_int powerLimit;
    res = manualPowerTuning->pVtbl->GetPowerLimit(manualPowerTuning, &powerLimit);
    printf("\tSet current power limit to: %d, return code is: %d(0 means success)\n", powerLimit, res);
}


// Show how to check TDCLimit is supported.
void ShowTDCLimitSupported(IADLXManualPowerTuning* manualPowerTuning)
{
    adlx_bool tdcSupported;
    ADLX_RESULT res = manualPowerTuning->pVtbl->IsSupportedTDCLimit(manualPowerTuning, &tdcSupported);
    printf("\tIs TDC Limit supported: %d, return code is: %d(0 means success)\n", tdcSupported, res);
}

// Show how to get TDC limit range.
void ShowGetTDCLimitRange(IADLXManualPowerTuning* manualPowerTuning)
{
    ADLX_IntRange tdcRange;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetTDCLimitRange(manualPowerTuning, &tdcRange);
    printf("\tGet TDC limit range is: (%d, %d), return code is: %d (0 means success)\n", tdcRange.minValue, tdcRange.maxValue, res);
}

// Show how to get current TDC limit.
void ShowGetTDCLimit(IADLXManualPowerTuning* manualPowerTuning)
{
    adlx_int tdcLimit;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetTDCLimit(manualPowerTuning, &tdcLimit);
    printf("\tThe current TDC limit is: %d, return code is: %d (0 means success)\n", tdcLimit, res);
}

// Show how to set TDC limit.
void ShowSetTDCLimit(IADLXManualPowerTuning* manualPowerTuning)
{
    ADLX_IntRange tdcRange;
    ADLX_RESULT res = manualPowerTuning->pVtbl->GetTDCLimitRange(manualPowerTuning, &tdcRange);
    res = manualPowerTuning->pVtbl->SetTDCLimit(manualPowerTuning, tdcRange.minValue + (tdcRange.maxValue - tdcRange.minValue) / 2);
    adlx_int tdcLimit;
    res = manualPowerTuning->pVtbl->GetTDCLimit(manualPowerTuning, &tdcLimit);
    printf("\tSet current TDC limit to: %d, return code is: %d (0 means success)\n", tdcLimit, res);
}
