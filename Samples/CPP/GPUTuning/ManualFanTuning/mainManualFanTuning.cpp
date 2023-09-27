//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualFanTuning.cpp
/// \brief Demonstrates how to control manual fan tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUManualFanTuning.h"
#include "SDK/Include/IGPUTuning.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu ();

// Menu action control
void MenuControl (IADLXManualFanTuningPtr manualFanTuning);

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode);

// Display and set fan settings
void ShowGetAndSetFan (IADLXManualFanTuningPtr manualFanTuning);

// Display and set ZeroRPM settings
void ShowGetAndSetZeroRPM (IADLXManualFanTuningPtr manualFanTuning);

// Display and set MinAcoustic settings
void ShowGetAndSetMinAcoustic (IADLXManualFanTuningPtr manualFanTuning);

// Display and set MinFanSpeed settings
void ShowGetAndSetMinFanSpeed (IADLXManualFanTuningPtr manualFanTuning);

// Display and set TargetFanSpeed settings
void ShowGetAndSetTargetFanSpeed (IADLXManualFanTuningPtr manualFanTuning);

int main ()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize ();

    if (ADLX_SUCCEEDED (res))
    {
        IADLXGPUTuningServicesPtr gpuTuningService;
        res = g_ADLXHelp.GetSystemServices ()->GetGPUTuningServices (&gpuTuningService);
        if (ADLX_FAILED (res))
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU tuning services failed", 0);
        }
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices ()->GetGPUs (&gpus);
        if (ADLX_FAILED (res))
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU list failed", 0);
        }
        IADLXGPUPtr oneGPU;
        res = gpus->At (0, &oneGPU);
        if (ADLX_FAILED (res) || oneGPU == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU failed", 0);
        }
        adlx_bool supported = false;
        res = gpuTuningService->IsSupportedManualFanTuning (oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tThis GPU doesn't supported manual fan tuning", 0);
        }
        IADLXInterfacePtr manualFanTuningIfc;
        res = gpuTuningService->GetManualFanTuning (oneGPU, &manualFanTuningIfc);
        if (ADLX_FAILED (res) || manualFanTuningIfc == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual fan tuning interface failed", 0);
        }
        IADLXManualFanTuningPtr manualFanTuning (manualFanTuningIfc);
        if (manualFanTuning == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual fan tuning failed", 0);
        }
        // Display main menu options
        MainMenu ();

        // Get and execute the choice
        MenuControl (manualFanTuning);
    }
    else
        return WaitAndExit ("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate ();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system ("pause");

    return 0;
}

// Main menu
void MainMenu ()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display and set fan settings" << std::endl;
    std::cout << "\t->Press 2 to display and set ZeroRPM settings" << std::endl;
    std::cout << "\t->Press 3 to display and set MinAcoustic settings" << std::endl;
    std::cout << "\t->Press 4 to display and set MinFanSpeed settings" << std::endl;
    std::cout << "\t->Press 5 to display and set TargetFanSpeed settings" << std::endl;
    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl (IADLXManualFanTuningPtr manualFanTuning)
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
int WaitAndExit (const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system ("pause");
    return retCode;
}

// Display and set fan settings
void ShowGetAndSetFan (IADLXManualFanTuningPtr manualFanTuning)
{
    // Display manual fan tuning ranges (speed, temperature)
    ADLX_IntRange fanSpeedRange, fanTemperatureRange;
    ADLX_RESULT res = manualFanTuning->GetFanTuningRanges (&fanSpeedRange, &fanTemperatureRange);
    std::cout << "\tFan speed range is: (" << fanSpeedRange.minValue
        << ", " << fanSpeedRange.maxValue << ")" << std::endl;
    std::cout << "\tFan temperature range is: (" << fanTemperatureRange.minValue
        << ", " << fanTemperatureRange.maxValue << ")" << std::endl;
    std::cout << "\tReturn code is: "<< res << "(0 means success)" << std::endl;

    // Display current fan tuning states
    IADLXManualFanTuningStateListPtr states;
    IADLXManualFanTuningStatePtr oneState;
    res = manualFanTuning->GetFanTuningStates (&states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->Begin (); crt != states->End (); ++crt)
        {
            res = states->At (crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            oneState->GetFanSpeed (&speed);
            oneState->GetTemperature (&temperature);
            std::cout << "\tThe current " << crt << " state: speed is " << speed << " temperature is " << temperature << std::endl;
        }
    }
    

    // Set empty fan tuning states
    res = manualFanTuning->GetEmptyFanTuningStates (&states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->Begin (); crt != states->End (); ++crt)
        {
            res = states->At (crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            int fanSpeedStep = (fanSpeedRange.maxValue - fanSpeedRange.minValue) / states->Size ();
            int fanTemperatureStep = (fanTemperatureRange.maxValue - fanTemperatureRange.minValue) / states->Size ();
            oneState->SetFanSpeed (fanSpeedRange.minValue + fanSpeedStep * crt);
            oneState->GetFanSpeed (&speed);
            oneState->SetTemperature (fanTemperatureRange.minValue + fanTemperatureStep * crt);
            oneState->GetTemperature (&temperature);
            std::cout << "\tSet empty " << crt << " state: speed is " << speed << " temperature is " << temperature << std::endl;
        }
    }

    // Set empty fan tuning states to current fan tuning states
    adlx_int errorIndex;
    res = manualFanTuning->IsValidFanTuningStates (states, &errorIndex);
    std::cout << "\tIsValidGPUTuningStates, errorIndex is :" << errorIndex << std::endl;
    if (ADLX_SUCCEEDED (res))
    {
        manualFanTuning->SetFanTuningStates (states);
    }
    res = manualFanTuning->GetFanTuningStates (&states);
    if (ADLX_SUCCEEDED (res))
    {
        std::cout << "\tAfter setting:" << std::endl;
        for (adlx_uint crt = states->Begin (); crt != states->End (); ++crt)
        {
            res = states->At (crt, &oneState);
            adlx_int speed = 0, temperature = 0;
            oneState->GetFanSpeed (&speed);
            oneState->GetTemperature (&temperature);
            std::cout << "\tThe current " << crt << " state: speed is " << speed << " temperature is " << temperature << std::endl;
        }
    }
}

// Display and set ZeroRPM settings
void ShowGetAndSetZeroRPM (IADLXManualFanTuningPtr manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->IsSupportedZeroRPM (&supported);
    std::cout << "\tIs ZeroRPM supported: " << supported << std::endl;
    if (ADLX_FAILED (res) || !supported)
        return;

    adlx_bool isZeroRPMStateSet = false;
    res = manualFanTuning->SetZeroRPMState (true);
    std::cout << "\tSet ZeroRPM state" << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualFanTuning->GetZeroRPMState (&isZeroRPMStateSet);
    std::cout << "\tIs ZeroRPM state set: " << isZeroRPMStateSet << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualFanTuning->SetZeroRPMState (false);
    std::cout << "\tReset ZeroRPM state" << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualFanTuning->GetZeroRPMState (&isZeroRPMStateSet);
    std::cout << "\tIs ZeroRPM state set: " << isZeroRPMStateSet << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display and set MinAcoustic settings
void ShowGetAndSetMinAcoustic (IADLXManualFanTuningPtr manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->IsSupportedMinAcousticLimit (&supported);
    std::cout << "\tIs MinAcousticLimit supported: " << supported << std::endl;
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->GetMinAcousticLimitRange (&tuningRange);
    std::cout << "\tDisplay MinAcoustic limit range: (" << tuningRange.minValue
        << ", " << tuningRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;

    adlx_int minAcousticLimit;
    res = manualFanTuning->GetMinAcousticLimit (&minAcousticLimit);
    std::cout << "\tDisplay current min acoustic limit: " << minAcousticLimit << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualFanTuning->SetMinAcousticLimit (tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->GetMinAcousticLimit (&minAcousticLimit);
    std::cout << "\tSet current min acoustic limit to: " << minAcousticLimit << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display and set MinFanSpeed settings
void ShowGetAndSetMinFanSpeed (IADLXManualFanTuningPtr manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->IsSupportedMinFanSpeed (&supported);

    std::cout << "\tIs MinFanSpeed supported: " << supported << std::endl;
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->GetMinFanSpeedRange (&tuningRange);
    std::cout << "\tDisplay MinFanSpeed range: (" << tuningRange.minValue
        << ", " << tuningRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;

    adlx_int minFanSpeed = 0;
    res = manualFanTuning->GetMinFanSpeed (&minFanSpeed);
    std::cout << "\tDisplay current MinFanSpeed: " << minFanSpeed << ", return code is: "<< res << "(0 means success)" << std::endl;

    res = manualFanTuning->SetMinAcousticLimit (tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->GetMinFanSpeed (&minFanSpeed);
    std::cout << "\tSet current MinFanSpeed to: " << minFanSpeed << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display and set TargetFanSpeed settings
void ShowGetAndSetTargetFanSpeed (IADLXManualFanTuningPtr manualFanTuning)
{
    adlx_bool supported = false;
    ADLX_RESULT res = manualFanTuning->IsSupportedTargetFanSpeed (&supported);

    std::cout << "\tIs TargetFanSpeed supported: " << supported << std::endl;
    if (ADLX_FAILED (res) || !supported)
        return;

    ADLX_IntRange tuningRange;
    res = manualFanTuning->GetTargetFanSpeedRange (&tuningRange);
    std::cout << "\tDisplay TargetFanSpeed range: (" << tuningRange.minValue
        << ", " << tuningRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;

    adlx_int targetFanSpeed = 0;
    res = manualFanTuning->GetTargetFanSpeed (&targetFanSpeed);
    std::cout << "\tDisplay current TargetFanSpeed: " << targetFanSpeed << ", return code is: "<< res << "(0 means success)" << std::endl;

    res = manualFanTuning->SetTargetFanSpeed (tuningRange.minValue + (tuningRange.maxValue - tuningRange.minValue) / 2);
    res = manualFanTuning->GetTargetFanSpeed (&targetFanSpeed);
    std::cout << "\tSet current TargetFanSpeed to: " << targetFanSpeed << ", return code is: "<< res << "(0 means success)" << std::endl;
}