//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualFanTuning.c
/// \brief Demonstrates how to control manual fan tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUManualFanTuning.h"
#include "SDK/Include/IGPUTuning.h"

// Main menu
void MainMenu ();

// Menu action control
void MenuControl (IADLXManualFanTuning* manualFanTuning);

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode,
    IADLXGPUTuningServices* gpuTuningService,
    IADLXGPUList* gpus,
    IADLXGPU* oneGPU,
    IADLXInterface* manualFanTuningIfc,
    IADLXManualFanTuning* manualFanTuning);

// Display and set fan settings
void ShowGetAndSetFan (IADLXManualFanTuning* manualFanTuning);

// Display and set ZeroRPM settings
void ShowGetAndSetZeroRPM (IADLXManualFanTuning* manualFanTuning);

// Display and set MinAcoustic settings
void ShowGetAndSetMinAcoustic (IADLXManualFanTuning* manualFanTuning);

// Display and set MinFanSpeed settings
void ShowGetAndSetMinFanSpeed (IADLXManualFanTuning* manualFanTuning);

// Display and set TargetFanSpeed settings
void ShowGetAndSetTargetFanSpeed (IADLXManualFanTuning* manualFanTuning);

int main ()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize ();

    if (ADLX_SUCCEEDED (res))
    {
        IADLXSystem* sys = ADLXHelper_GetSystemServices ();
        IADLXGPUTuningServices* gpuTuningService = NULL;
        IADLXGPUList* gpus = NULL;
        IADLXGPU* oneGPU = NULL;
        IADLXInterface* manualFanTuningIfc = NULL;
        IADLXManualFanTuning* manualFanTuning = NULL;

        res = sys->pVtbl->GetGPUTuningServices (sys, &gpuTuningService);
        if (ADLX_FAILED (res))
            return WaitAndExit ("\tGet GPU tuning services failed", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        res = sys->pVtbl->GetGPUs (sys, &gpus);
        if (ADLX_FAILED (res))
            return WaitAndExit ("\tGet GPU list failed", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        res = gpus->pVtbl->At_GPUList (gpus, 0, &oneGPU);
        if (ADLX_FAILED (res) || oneGPU == NULL)
            return WaitAndExit ("\tGet GPU failed", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        adlx_bool supported = false;
        res = gpuTuningService->pVtbl->IsSupportedManualFanTuning (gpuTuningService, oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
            return WaitAndExit ("\tThis GPU does not support manual fan tuning", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        res = gpuTuningService->pVtbl->GetManualFanTuning (gpuTuningService, oneGPU, &manualFanTuningIfc);
        if (ADLX_FAILED (res) || manualFanTuningIfc == NULL)
            return WaitAndExit ("\tGet manual fan tuning interface failed", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        manualFanTuningIfc->pVtbl->QueryInterface (manualFanTuningIfc, IID_IADLXManualFanTuning (), (void**)&manualFanTuning);
        if (manualFanTuning == NULL)
            return WaitAndExit ("\tGet manual fan tuning failed", 0, gpuTuningService, gpus, oneGPU, manualFanTuningIfc, manualFanTuning);

        // Display main menu options
        MainMenu ();

        // Get and execute the choice
        MenuControl (manualFanTuning);

        // Release the manualFanTuning interface
        if (manualFanTuning != NULL)
        {
            manualFanTuning->pVtbl->Release (manualFanTuning);
            manualFanTuning = NULL;
        }
        if (manualFanTuningIfc != NULL)
        {
            manualFanTuningIfc->pVtbl->Release (manualFanTuningIfc);
            manualFanTuningIfc = NULL;
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release (oneGPU);
            oneGPU = NULL;
        }
        if (gpus != NULL)
        {
            gpus->pVtbl->Release (gpus);
            gpus = NULL;
        }
        if (gpuTuningService != NULL)
        {
            gpuTuningService->pVtbl->Release (gpuTuningService);
            gpuTuningService = NULL;
        }
    }
    else
    {
        printf ("\tg_ADLXHelp initialize failed\n");
        system ("pause");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate ();
    printf ("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system ("pause");

    return 0;
}

// Main menu
void MainMenu ()
{
    printf ("\tChoose from the following options:\n");

    printf ("\t->Press 1 to display and set fan setting\n");
    printf ("\t->Press 2 to display and set ZeroRPM setting\n");
    printf ("\t->Press 3 to display and set MinAcoustic setting\n");
    printf ("\t->Press 4 to display and set MinFanSpeed setting\n");
    printf ("\t->Press 5 to display and set TargetFanSpeed setting\n");

    printf ("\t->Press Q/q to terminate the application\n");
    printf ("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl (IADLXManualFanTuning* manualFanTuning)
{
    int num = 0;
    while ((num = getchar ()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display and set fan settings
        case '1':
            ShowGetAndSetFan (manualFanTuning);
            break;

            // Display and set ZeroRPM settings
        case '2':
            ShowGetAndSetZeroRPM (manualFanTuning);
            break;

            // Display and set MinAcoustic settings
        case '3':
            ShowGetAndSetMinAcoustic (manualFanTuning);
            break;

            // Display and set MinFanSpeed settings
        case '4':
            ShowGetAndSetMinFanSpeed (manualFanTuning);
            break;

            // Display and set TargetFanSpeed settings
        case '5':
            ShowGetAndSetTargetFanSpeed (manualFanTuning);
            break;

            // Display menu options
        case 'm':
        case 'M':
            MainMenu ();
            break;
        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode,
    IADLXGPUTuningServices* gpuTuningService,
    IADLXGPUList* gpus,
    IADLXGPU* oneGPU,
    IADLXInterface* manualFanTuningIfc,
    IADLXManualFanTuning* manualFanTuning)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf ("%s\n", msg);

    // Release the manualFanTuning interface
    if (manualFanTuning != NULL)
    {
        manualFanTuning->pVtbl->Release (manualFanTuning);
        manualFanTuning = NULL;
    }
    if (manualFanTuningIfc != NULL)
    {
        manualFanTuningIfc->pVtbl->Release (manualFanTuningIfc);
        manualFanTuningIfc = NULL;
    }
    if (oneGPU != NULL)
    {
        oneGPU->pVtbl->Release (oneGPU);
        oneGPU = NULL;
    }
    if (gpus != NULL)
    {
        gpus->pVtbl->Release (gpus);
        gpus = NULL;
    }
    if (gpuTuningService != NULL)
    {
        gpuTuningService->pVtbl->Release (gpuTuningService);
        gpuTuningService = NULL;
    }
    // Destroy ADLX
    ADLX_RESULT res = ADLXHelper_Terminate ();
    printf ("Destroy ADLX res: %d\n", res);

    system ("pause");
    return retCode;
}

// Display and set fan settings
void ShowGetAndSetFan (IADLXManualFanTuning* manualFanTuning)
{
    // Display manual fan tuning ranges (speed, temperature)
    ADLX_IntRange fanSpeedRange, fanTemperatureRange;
    ADLX_RESULT res = manualFanTuning->pVtbl->GetFanTuningRanges (manualFanTuning, &fanSpeedRange, &fanTemperatureRange);
    printf ("\tFan speed range: (%d, %d)\n", fanSpeedRange.minValue, fanSpeedRange.maxValue);
    printf ("\tFan temperature range: (%d, %d)\n", fanTemperatureRange.minValue, fanTemperatureRange.maxValue);
    printf ("\tReturn code is: %d(0 means success)\n", res);

    // Display current fan tuning states
    IADLXManualFanTuningStateList* states;
    IADLXManualFanTuningState* oneState;
    res = manualFanTuning->pVtbl->GetFanTuningStates (manualFanTuning, &states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->pVtbl->Begin (states); crt != states->pVtbl->End (states); ++crt)
        {
            res = states->pVtbl->At_ManualFanTuningStateList (states, crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            oneState->pVtbl->GetFanSpeed (oneState, &speed);
            oneState->pVtbl->GetTemperature (oneState, &temperature);
            printf ("\tThe current %d state: speed is %d temperature is %d\n", crt, speed, temperature);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
        if (states != NULL)
        {
            states->pVtbl->Release (states);
            states = NULL;
        }
    }
    

    // Set empty fan tuning states
    res = manualFanTuning->pVtbl->GetEmptyFanTuningStates (manualFanTuning, &states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->pVtbl->Begin (states); crt != states->pVtbl->End (states); ++crt)
        {
            res = states->pVtbl->At_ManualFanTuningStateList (states, crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            int fanSpeedStep = (fanSpeedRange.maxValue - fanSpeedRange.minValue) / states->pVtbl->Size (states);
            int fanTemperatureStep = (fanTemperatureRange.maxValue - fanTemperatureRange.minValue) / states->pVtbl->Size (states);
            oneState->pVtbl->SetFanSpeed (oneState, fanSpeedRange.minValue + fanSpeedStep * crt);
            oneState->pVtbl->GetFanSpeed (oneState, &speed);
            oneState->pVtbl->SetTemperature (oneState, fanTemperatureRange.minValue + fanTemperatureStep * crt);
            oneState->pVtbl->GetTemperature (oneState, &temperature);
            printf ("\tSet empty %d state: speed is %d temperature is %d\n", crt, speed, temperature);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
    }

    // Set empty fan tuning states to current fan tuning states
    adlx_int errorIndex;
    res = manualFanTuning->pVtbl->IsValidFanTuningStates (manualFanTuning, states, &errorIndex);
    printf ("\tIsValidGPUTuningStates, errorIndex is : %d\n", errorIndex);
    if (ADLX_SUCCEEDED (res))
    {
        manualFanTuning->pVtbl->SetFanTuningStates (manualFanTuning, states);
    }
    if (states != NULL)
    {
        states->pVtbl->Release (states);
        states = NULL;
    }
    res = manualFanTuning->pVtbl->GetFanTuningStates (manualFanTuning, &states);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("\tAfter setting:\n");
        for (adlx_uint crt = states->pVtbl->Begin (states); crt != states->pVtbl->End (states); ++crt)
        {
            res = states->pVtbl->At_ManualFanTuningStateList (states, crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            oneState->pVtbl->GetFanSpeed (oneState, &speed);
            oneState->pVtbl->GetTemperature (oneState, &temperature);
            printf ("\tThe current %d state: speed is %d temperature is %d\n", crt, speed, temperature);
            if (oneState != NULL)
            {
                oneState->pVtbl->Release (oneState);
                oneState = NULL;
            }
        }
        if (states != NULL)
        {
            states->pVtbl->Release (states);
            states = NULL;
        }
    }
}

// Display and set ZeroRPM settings
void ShowGetAndSetZeroRPM (IADLXManualFanTuning* manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->pVtbl->IsSupportedZeroRPM (manualFanTuning, &supported);
    printf ("\tIs support ZeroRPM: %d\n", supported);
    if (ADLX_FAILED (res) || !supported)
        return;
    adlx_bool isZeroRPMStateSet = false;
    res = manualFanTuning->pVtbl->SetZeroRPMState (manualFanTuning, true);
    printf ("\tSet ZeroRPM state, return code is: %d(0 means success)\n", res);
    res = manualFanTuning->pVtbl->GetZeroRPMState (manualFanTuning, &isZeroRPMStateSet);
    printf ("\tIs ZeroRPM state set: %d, return code is: %d(0 means success)\n", isZeroRPMStateSet, res);
    res = manualFanTuning->pVtbl->SetZeroRPMState (manualFanTuning, false);
    printf ("\tReset ZeroRPM state, return code is: %d(0 means success)\n", res);
    res = manualFanTuning->pVtbl->GetZeroRPMState (manualFanTuning, &isZeroRPMStateSet);
    printf ("\tIs ZeroRPM state set: %d, return code is: %d(0 means success)\n", isZeroRPMStateSet, res);
}

// Display and set MinAcoustic settings
void ShowGetAndSetMinAcoustic (IADLXManualFanTuning* manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->pVtbl->IsSupportedMinAcousticLimit (manualFanTuning, &supported);
    printf ("\tIs MinAcousticLimit supported: %d\n", supported);
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->pVtbl->GetMinAcousticLimitRange (manualFanTuning, &tuningRange);
    printf ("\tMinAcoustic limit range: (%d, %d), return code is: %d(0 means success)\n", tuningRange.minValue, tuningRange.maxValue, res);

    adlx_int minAcousticLimit;
    res = manualFanTuning->pVtbl->GetMinAcousticLimit (manualFanTuning, &minAcousticLimit);
    printf ("\tCurrent min acoustic limit: %d, return code is: %d(0 means success)\n", minAcousticLimit, res);
    res = manualFanTuning->pVtbl->SetMinAcousticLimit (manualFanTuning, tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->pVtbl->GetMinAcousticLimit (manualFanTuning, &minAcousticLimit);
    printf ("\tSet current min acoustic limit to: %d, return code is: %d(0 means success)\n", minAcousticLimit, res);
}

// Display and set MinFanSpeed settings
void ShowGetAndSetMinFanSpeed (IADLXManualFanTuning* manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->pVtbl->IsSupportedMinFanSpeed (manualFanTuning, &supported);
    printf ("\tIs MinFanSpeed supported: %d\n", supported);
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->pVtbl->GetMinFanSpeedRange (manualFanTuning, &tuningRange);
    printf ("\tMinFanSpeed range: (%d, %d), return code is: %d(0 means success)\n", tuningRange.minValue, tuningRange.maxValue, res);

    adlx_int minFanSpeed = 0;
    res = manualFanTuning->pVtbl->GetMinFanSpeed (manualFanTuning, &minFanSpeed);
    printf ("\tCurrent MinFanSpeed: %d, return code is: %d(0 means success)\n", minFanSpeed, res);
    res = manualFanTuning->pVtbl->SetMinFanSpeed (manualFanTuning, tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->pVtbl->GetMinFanSpeed (manualFanTuning, &minFanSpeed);
    printf ("\tSet current MinFanSpeed to: %d, return code is: %d(0 means success)\n", minFanSpeed, res);
}

// Display and set TargetFanSpeed settings
void ShowGetAndSetTargetFanSpeed (IADLXManualFanTuning* manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->pVtbl->IsSupportedTargetFanSpeed (manualFanTuning, &supported);
    printf ("\tIs TargetFanSpeed supported: %d\n", supported);
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->pVtbl->GetTargetFanSpeedRange (manualFanTuning, &tuningRange);
    printf ("\tTargetFanSpeed range: (%d, %d), return code is: %d(0 means success)\n", tuningRange.minValue, tuningRange.maxValue, res);

    adlx_int minAcousticLimit;
    res = manualFanTuning->pVtbl->GetTargetFanSpeed (manualFanTuning, &minAcousticLimit);
    printf ("\tCurrent TargetFanSpeed: %d, return code is: %d(0 means success)\n", minAcousticLimit, res);
    res = manualFanTuning->pVtbl->SetTargetFanSpeed (manualFanTuning, tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->pVtbl->GetTargetFanSpeed (manualFanTuning, &minAcousticLimit);
    printf ("\tSet current TargetFanSpeed to: %d, return code is: %d(0 means success)\n", minAcousticLimit, res);
}