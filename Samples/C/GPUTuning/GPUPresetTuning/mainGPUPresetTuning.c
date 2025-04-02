//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUPresetTuning.c
/// \brief Demonstrates how to control GPU preset tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUPresetTuning.h"
#include "SDK/Include/IGPUTuning.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUPresetTuning* gpuPresetTuning);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode,
                IADLXGPUTuningServices* gpuTuningService,
                IADLXGPUList* gpus,
                IADLXGPU* oneGPU,
                IADLXInterface* gpuPresetTuningIfc,
                IADLXGPUPresetTuning* gpuPresetTuning);

// Display GPU tuning support states
void ShowIsSupported(IADLXGPUPresetTuning* gpuPresetTuning);

// Display current GPU tuning states
void GetCurrentStates(IADLXGPUPresetTuning* gpuPresetTuning);

// Set GPU states
void SetGPUStates(IADLXGPUPresetTuning* gpuPresetTuning);

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
        IADLXInterface* gpuPresetTuningIfc = NULL;
        IADLXGPUPresetTuning* gpuPresetTuning = NULL;

        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningService);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU tuning services failed", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);

        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU list failed", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);

        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, 0, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == NULL)
            return WaitAndExit("\tGet GPU failed", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);

        adlx_bool supported = false;
        res = gpuTuningService->pVtbl->IsSupportedPresetTuning(gpuTuningService, oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
            return WaitAndExit("\tGPU preset tuning is not supported by this GPU", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);

        res = gpuTuningService->pVtbl->GetPresetTuning(gpuTuningService, oneGPU, &gpuPresetTuningIfc);
        if (ADLX_FAILED(res) || gpuPresetTuningIfc == NULL)
            return WaitAndExit("\tGet GPU preset tuning interface failed", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);

        gpuPresetTuningIfc->pVtbl->QueryInterface(gpuPresetTuningIfc, IID_IADLXGPUPresetTuning(), (void**)&gpuPresetTuning);
        if (gpuPresetTuning == NULL)
            return WaitAndExit("\tGet GPU preset tuning failed", 0, gpuTuningService, gpus, oneGPU,
                               gpuPresetTuningIfc, gpuPresetTuning);
        // Display main menu options
        MainMenu();

        // Get and execute the choice
        MenuControl(gpuPresetTuning);

        // Release the gpuPresetTuning interface
        if (gpuPresetTuning != NULL)
        {
            gpuPresetTuning->pVtbl->Release(gpuPresetTuning);
            gpuPresetTuning = NULL;
        }
        if (gpuPresetTuningIfc != NULL)
        {
            gpuPresetTuningIfc->pVtbl->Release(gpuPresetTuningIfc);
            gpuPresetTuningIfc = NULL;
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

    printf("\t->Press 1 to display GPU tuning support states\n");
    printf("\t->Press 2 to display current GPU tuning states\n");
    printf("\t->Press 3 to set GPU states\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXGPUPresetTuning* gpuPresetTuning)
{
    char num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display GPU tuning support states
        case '1':
            ShowIsSupported(gpuPresetTuning);
            break;

        // Display current GPU tuning states
        case '2':
            GetCurrentStates(gpuPresetTuning);
            break;

        // Set GPU states
        case '3':
            SetGPUStates(gpuPresetTuning);
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
                IADLXInterface* gpuPresetTuningIfc,
                IADLXGPUPresetTuning* gpuPresetTuning)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    if (gpuPresetTuning != NULL)
    {
        gpuPresetTuning->pVtbl->Release(gpuPresetTuning);
        gpuPresetTuning = NULL;
    }
    if (gpuPresetTuningIfc != NULL)
    {
        gpuPresetTuningIfc->pVtbl->Release(gpuPresetTuningIfc);
        gpuPresetTuningIfc = NULL;
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

// Display GPU tuning support states
void ShowIsSupported(IADLXGPUPresetTuning* gpuPresetTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = gpuPresetTuning->pVtbl->IsSupportedPowerSaver(gpuPresetTuning, &supported);
    printf("\tIs Power Save supported by the GPU: %d, return code is: %d(0 means success)\n", supported, res);
    supported = false;
    res = gpuPresetTuning->pVtbl->IsSupportedQuiet(gpuPresetTuning, &supported);
    printf("\tIs Quiet supported by the GPU: %d, return code is: %d(0 means success)\n", supported, res);
    supported = false;
    res = gpuPresetTuning->pVtbl->IsSupportedBalanced(gpuPresetTuning, &supported);
    printf("\tIs Balanced supported by the GPU: %d, return code is: %d(0 means success)\n", supported, res);
    supported = false;
    res = gpuPresetTuning->pVtbl->IsSupportedTurbo(gpuPresetTuning, &supported);
    printf("\tIs Turbo supported by the GPU: %d, return code is: %d(0 means success)\n", supported, res);
    supported = false;
    res = gpuPresetTuning->pVtbl->IsSupportedRage(gpuPresetTuning, &supported);
    printf("\tIs Rage supported by the GPU: %d, return code is: %d(0 means success)\n", supported, res);
}

// Display current GPU tuning states
void GetCurrentStates(IADLXGPUPresetTuning* gpuPresetTuning)
{
    adlx_bool applied = false;
    ADLX_RESULT res = gpuPresetTuning->pVtbl->IsCurrentPowerSaver(gpuPresetTuning, &applied);
    printf("\tIs Power Saver applied: %d, return code is: %d(0 means success)\n", applied, res);
    applied = false;
    res = gpuPresetTuning->pVtbl->IsCurrentQuiet(gpuPresetTuning, &applied);
    printf("\tIs Quiet applied: %d, return code is: %d(0 means success)\n", applied, res);
    applied = false;
    res = gpuPresetTuning->pVtbl->IsCurrentBalanced(gpuPresetTuning, &applied);
    printf("\tIs Balanced applied: %d, return code is: %d(0 means success)\n", applied, res);
    applied = false;
    res = gpuPresetTuning->pVtbl->IsCurrentTurbo(gpuPresetTuning, &applied);
    printf("\tIs Turbo applied: %d, return code is: %d(0 means success)\n", applied, res);
    applied = false;
    res = gpuPresetTuning->pVtbl->IsCurrentRage(gpuPresetTuning, &applied);
    printf("\tIs Rage applied: %d, return code is: %d(0 means success)\n", applied, res);
}

// Set GPU states
void SetGPUStates(IADLXGPUPresetTuning* gpuPresetTuning)
{
    adlx_bool applied = false;
    ADLX_RESULT res = gpuPresetTuning->pVtbl->SetPowerSaver(gpuPresetTuning);
    res = gpuPresetTuning->pVtbl->IsCurrentPowerSaver(gpuPresetTuning, &applied);
    printf("\tSet Power Saver preset tuning %s, return code is: %d(0 means success)\n", (applied ? "Successful" : "failed"), res);
    applied = false;
    res = gpuPresetTuning->pVtbl->SetQuiet(gpuPresetTuning);
    res = gpuPresetTuning->pVtbl->IsCurrentQuiet(gpuPresetTuning, &applied);
    printf("\tSet Quiet preset tuning %s, return code is: %d(0 means success)\n", (applied ? "Successful" : "failed"), res);
    applied = false;
    res = gpuPresetTuning->pVtbl->SetBalanced(gpuPresetTuning);
    res = gpuPresetTuning->pVtbl->IsCurrentBalanced(gpuPresetTuning, &applied);
    printf("\tSet Balanced preset tuning %s, return code is: %d(0 means success)\n", (applied ? "Successful" : "failed"), res);
    applied = false;
    res = gpuPresetTuning->pVtbl->SetTurbo(gpuPresetTuning);
    res = gpuPresetTuning->pVtbl->IsCurrentTurbo(gpuPresetTuning, &applied);
    printf("\tSet Turbo preset tuning %s, return code is: %d(0 means success)\n", (applied ? "Successful" : "failed"), res);
    applied = false;
    res = gpuPresetTuning->pVtbl->SetRage(gpuPresetTuning);
    res = gpuPresetTuning->pVtbl->IsCurrentRage(gpuPresetTuning, &applied);
    printf("\tSet Rage preset tuning %s, return code is: %d(0 means success)\n", (applied ? "Successful" : "failed"), res);
}
