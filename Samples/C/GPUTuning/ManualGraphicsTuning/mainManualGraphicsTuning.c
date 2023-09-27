//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualGraphicsTuning.c
/// \brief Demonstrates how to control manual graphics tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUManualGFXTuning.h"
#include "SDK/Include/IGPUTuning.h"

// Main menu
void MainMenu(IADLXManualGraphicsTuning1* manualGFXTuning1, IADLXManualGraphicsTuning2* manualGFXTuning2);

// Menu action control
void MenuControl(IADLXManualGraphicsTuning1* manualGFXTuning1, IADLXManualGraphicsTuning2* manualGFXTuning2);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode,
                IADLXGPUTuningServices* gpuTuningService,
                IADLXGPUList* gpus,
                IADLXGPU* oneGPU,
                IADLXInterface* manualGFXTuningIfc,
                IADLXManualGraphicsTuning1* manualGFXTuning1,
                IADLXManualGraphicsTuning2* manualGFXTuning2);

/***** The first is pre-Navi, the second is post-Navi *****/
// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange1(IADLXManualGraphicsTuning1* manualGFXTuning1);
void ShowFrequencyAndVoltageRange2(IADLXManualGraphicsTuning2* manualGFXTuning2);
// Display current GPU tuning states
void GetCurrentStates1(IADLXManualGraphicsTuning1* manualGFXTuning1);
void GetCurrentStates2(IADLXManualGraphicsTuning2* manualGFXTuning2);
// Set GPU states
void SetGPUStates1(IADLXManualGraphicsTuning1* manualGFXTuning1);
void SetGPUStates2(IADLXManualGraphicsTuning2* manualGFXTuning2);

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
        IADLXInterface* manualGFXTuningIfc = NULL;
        IADLXManualGraphicsTuning1* manualGFXTuning1 = NULL;
        IADLXManualGraphicsTuning2* manualGFXTuning2 = NULL;

        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningService);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU tuning services failed", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);

        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU list failed", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);

        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, 0, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == NULL)
            return WaitAndExit("\tGet GPU failed", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);

        adlx_bool supported = false;
        res = gpuTuningService->pVtbl->IsSupportedManualGFXTuning(gpuTuningService, oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
            return WaitAndExit("\tThis GPU does not support manual graphics tuning", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);

        res = gpuTuningService->pVtbl->GetManualGFXTuning(gpuTuningService, oneGPU, &manualGFXTuningIfc);
        if (ADLX_FAILED(res) || manualGFXTuningIfc == NULL)
            return WaitAndExit("\tGet manual graphics tuning interface failed", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);

        // Pre-Navi ASIC
        manualGFXTuningIfc->pVtbl->QueryInterface(manualGFXTuningIfc, IID_IADLXManualGraphicsTuning1(), (void**)&manualGFXTuning1);
        // Post-Navi ASIC
        manualGFXTuningIfc->pVtbl->QueryInterface(manualGFXTuningIfc, IID_IADLXManualGraphicsTuning2(), (void**)&manualGFXTuning2);

        if (manualGFXTuning1 == NULL && manualGFXTuning2 == NULL)
            return WaitAndExit("\tGet manual graphics tuning failed", 0, gpuTuningService, gpus, oneGPU,
                               manualGFXTuningIfc, manualGFXTuning1, manualGFXTuning2);
        // Display main menu options
        MainMenu(manualGFXTuning1, manualGFXTuning2);

        // Get and execute the choice
        MenuControl(manualGFXTuning1, manualGFXTuning2);

        // Release the manualGFXTuning1 interface
        if (manualGFXTuning1 != NULL)
        {
            manualGFXTuning1->pVtbl->Release(manualGFXTuning1);
            manualGFXTuning1 = NULL;
        }
        if (manualGFXTuning2 != NULL)
        {
            manualGFXTuning2->pVtbl->Release(manualGFXTuning2);
            manualGFXTuning2 = NULL;
        }
        if (manualGFXTuningIfc != NULL)
        {
            manualGFXTuningIfc->pVtbl->Release(manualGFXTuningIfc);
            manualGFXTuningIfc = NULL;
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
void MainMenu(IADLXManualGraphicsTuning1* manualGFXTuning1, IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    if (manualGFXTuning1)
        printf("\tThe current GPU is pre-Navi. Choose from the following options:\n");
    else if (manualGFXTuning2)
        printf("\tThe current GPU is post-Navi. Choose from the following options:\n");
    printf("\t->Press 1 to display GPU frequency and voltage\n");
    printf("\t->Press 2 to display current GPU states\n");
    printf("\t->Press 3 to set GPU states\n");
    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXManualGraphicsTuning1* manualGFXTuning1, IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    char num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        //  Pre-Navi Menu action control
        if (manualGFXTuning1)
        {
            switch (num)
            {
            // Display GPU frequency and voltage range
            case '1':
                ShowFrequencyAndVoltageRange1(manualGFXTuning1);
                break;

            // Display current GPU tuning states
            case '2':
                GetCurrentStates1(manualGFXTuning1);
                break;

            // Set GPU states
            case '3':
                SetGPUStates1(manualGFXTuning1);
                break;

            // Display menu options
            case 'm':
            case 'M':
                MainMenu(manualGFXTuning1, manualGFXTuning2);
                break;
            default:
                break;
            }
        }
        // Post-Navi Menu action control
        else
        {
            switch (num)
            {
            // Display GPU frequency and voltage range
            case '1':
                ShowFrequencyAndVoltageRange2(manualGFXTuning2);
                break;

            // Display current GPU tuning states
            case '2':
                GetCurrentStates2(manualGFXTuning2);
                break;

            // Set GPU states
            case '3':
                SetGPUStates2(manualGFXTuning2);
                break;

            // Display menu options
            case 'm':
            case 'M':
                MainMenu(manualGFXTuning1, manualGFXTuning2);
                break;
            default:
                break;
            }
        }
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode,
                IADLXGPUTuningServices* gpuTuningService,
                IADLXGPUList* gpus,
                IADLXGPU* oneGPU,
                IADLXInterface* manualGFXTuningIfc,
                IADLXManualGraphicsTuning1* manualGFXTuning1,
                IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    // Release the manualGFXTuning interface
    if (manualGFXTuning1 != NULL)
    {
        manualGFXTuning1->pVtbl->Release(manualGFXTuning1);
        manualGFXTuning1 = NULL;
    }
    if (manualGFXTuning2 != NULL)
    {
        manualGFXTuning2->pVtbl->Release(manualGFXTuning2);
        manualGFXTuning2 = NULL;
    }
    if (manualGFXTuningIfc != NULL)
    {
        manualGFXTuningIfc->pVtbl->Release(manualGFXTuningIfc);
        manualGFXTuningIfc = NULL;
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

// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange1(IADLXManualGraphicsTuning1* manualGFXTuning1)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning1->pVtbl->GetGPUTuningRanges(manualGFXTuning1, &freqRange, &voltRange);
    printf("\tFrequency range: (%d, %d), return code is: %d(0 means success)\n", freqRange.minValue, freqRange.maxValue, res);
    printf("\tVoltage range: (%d, %d), return code is: %d(0 means success)\n", voltRange.minValue, voltRange.maxValue, res);
}

// Display current GPU tuning states
void GetCurrentStates1(IADLXManualGraphicsTuning1* manualGFXTuning1)
{
    IADLXManualTuningStateList* states;
    IADLXManualTuningState* oneState;
    ADLX_RESULT res = manualGFXTuning1->pVtbl->GetGPUTuningStates(manualGFXTuning1, &states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->pVtbl->Begin(states); crt != states->pVtbl->End(states); ++crt)
        {
            states->pVtbl->At_ManualTuningStateList(states, crt, &oneState);
            adlx_int freq = 0, volt = 0;
            res = oneState->pVtbl->GetFrequency(oneState, &freq);
            printf("\tThe current state %d: frequency is %d, return code is: %d(0 means success)\n", crt, freq, res);
            res = oneState->pVtbl->GetVoltage(oneState, &volt);
            printf("\tThe current state %d: voltage is %d, return code is: %d(0 means success)\n", crt, volt, res);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
    }
    if (states != NULL)
    {
        states->pVtbl->Release (states);
        states = NULL;
    }
}

// Set GPU states
void SetGPUStates1(IADLXManualGraphicsTuning1* manualGFXTuning1)
{
    IADLXManualTuningStateList* states;
    IADLXManualTuningState* oneState;
    ADLX_RESULT res1 = manualGFXTuning1->pVtbl->GetEmptyGPUTuningStates(manualGFXTuning1, &states);
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res2 = manualGFXTuning1->pVtbl->GetGPUTuningRanges(manualGFXTuning1, &freqRange, &voltRange);
    if (ADLX_SUCCEEDED (res1) && ADLX_SUCCEEDED (res2))
    {
        for (adlx_uint crt = states->pVtbl->Begin(states); crt != states->pVtbl->End(states); ++crt)
        {
            states->pVtbl->At_ManualTuningStateList(states, crt, &oneState);
            adlx_int freq = 0, volt = 0;
            int freqStep = (freqRange.maxValue - freqRange.minValue) / (states->pVtbl->Size(states));
            // The Step should not be too large
            if (freqStep >= 60)
                freqStep = 60;
            int voltStep = (voltRange.maxValue - voltRange.minValue) / (states->pVtbl->Size(states));
            // The Step should not be too large
            if (voltStep >= 20)
                voltStep = 20;
            ADLX_RESULT res = oneState->pVtbl->SetFrequency(oneState, freqRange.minValue + freqStep * crt);
            res = oneState->pVtbl->GetFrequency(oneState, &freq);
            res = oneState->pVtbl->SetVoltage(oneState, voltRange.minValue + voltStep * crt);
            res = oneState->pVtbl->GetVoltage(oneState, &volt);
            printf("\tSet empty state %d: frequency is %d, voltage is %d, return code is: %d(0 means success)\n", crt, freq, volt, res);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
    }
    adlx_int errorIndex;
    ADLX_RESULT res = manualGFXTuning1->pVtbl->IsValidGPUTuningStates(manualGFXTuning1, states, &errorIndex);
    printf("\tIsValidGPUTuningStates, errorIndex is : %d, return code is: %d(0 means success)\n", errorIndex, res);
    if (ADLX_SUCCEEDED(res))
    {
        res = manualGFXTuning1->pVtbl->SetGPUTuningStates(manualGFXTuning1, states);
        printf ("\tSet GPU tuning states %s\n", (ADLX_SUCCEEDED (res) ? "succeeded" : "failed"));
    }
    if (states != NULL)
    {
        states->pVtbl->Release (states);
        states = NULL;
    }

    res = manualGFXTuning1->pVtbl->GetGPUTuningStates(manualGFXTuning1, &states);
    printf("\tAfter setting:\n");
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->pVtbl->Begin(states); crt != states->pVtbl->End(states); ++crt)
        {
            states->pVtbl->At_ManualTuningStateList(states, crt, &oneState);
            adlx_int freq = 0, volt = 0;
            res = oneState->pVtbl->GetFrequency(oneState, &freq);
            res = oneState->pVtbl->GetVoltage(oneState, &volt);
            printf("\tThe current state %d: frequency is %d, voltage is %d, return code is: %d(0 means success)\n", crt, freq, volt, res);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
    }
    if (states != NULL)
    {
        states->pVtbl->Release (states);
        states = NULL;
    }
}

// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange2(IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res= manualGFXTuning2->pVtbl->GetGPUMinFrequencyRange(manualGFXTuning2, &freqRange);
    printf("\tGPU minimum frequency range: (%d, %d), return code is: %d(0 means success)\n", freqRange.minValue, freqRange.maxValue, res);
    res = manualGFXTuning2->pVtbl->GetGPUMaxFrequencyRange(manualGFXTuning2, &freqRange);
    printf("\tGPU maximum frequency range: (%d, %d), return code is: %d(0 means success)\n", freqRange.minValue, freqRange.maxValue, res);
    res = manualGFXTuning2->pVtbl->GetGPUVoltageRange(manualGFXTuning2, &voltRange);
    printf("\tVoltage range: (%d, %d), return code is: %d(0 means success)\n", voltRange.minValue, voltRange.maxValue, res);
}

// Display current GPU tuning states
void GetCurrentStates2(IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    ADLX_RESULT res = manualGFXTuning2->pVtbl->GetGPUMinFrequency(manualGFXTuning2, &minFreq);
    printf("\tCurrent GPU minimum frequency: %d, return code is: %d(0 means success)\n", minFreq, res);
    res = manualGFXTuning2->pVtbl->GetGPUMaxFrequency(manualGFXTuning2, &maxFreq);
    printf("\tCurrent GPU maximum frequency: %d, return code is: %d(0 means success)\n", maxFreq, res);
    res = manualGFXTuning2->pVtbl->GetGPUVoltage(manualGFXTuning2, &volt);
    printf("\tCurrent GPU clock voltage: %d, return code is: %d(0 means success)\n", volt, res);
}

// Set GPU states
void SetGPUStates2(IADLXManualGraphicsTuning2* manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning2->pVtbl->GetGPUMinFrequencyRange(manualGFXTuning2, &freqRange);
    res = manualGFXTuning2->pVtbl->GetGPUVoltageRange(manualGFXTuning2, &voltRange);
    res = manualGFXTuning2->pVtbl->SetGPUMinFrequency(manualGFXTuning2, freqRange.minValue);
    printf ("\tSet GPU min frequency %s\n", (ADLX_SUCCEEDED (res) ? "succeeded" : "failed"));
    res = manualGFXTuning2->pVtbl->SetGPUMaxFrequency(manualGFXTuning2, freqRange.maxValue);
    printf ("\tSet GPU max frequency %s\n", (ADLX_SUCCEEDED (res) ? "succeeded" : "failed"));
    res = manualGFXTuning2->pVtbl->SetGPUVoltage(manualGFXTuning2, voltRange.minValue + (voltRange.maxValue - voltRange.minValue) / 2);
    printf ("\tSet GPU voltage %s\n", (ADLX_SUCCEEDED (res) ? "succeeded" : "failed"));
    printf("\tAfter setting:\n");
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    res = manualGFXTuning2->pVtbl->GetGPUMinFrequency(manualGFXTuning2, &minFreq);
    printf("\tCurrent GPU min frequency: %d, return code is: %d(0 means success)\n", minFreq, res);
    res = manualGFXTuning2->pVtbl->GetGPUMaxFrequency(manualGFXTuning2, &maxFreq);
    printf("\tCurrent GPU max frequency: %d, return code is: %d(0 means success)\n", maxFreq, res);
    res = manualGFXTuning2->pVtbl->GetGPUVoltage(manualGFXTuning2, &volt);
    printf("\tCurrent GPU clock voltage: %d, return code is: %d(0 means success)\n", volt, res);
}