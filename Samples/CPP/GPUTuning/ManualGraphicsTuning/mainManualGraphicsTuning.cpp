//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualGraphicsTuning.cpp
/// \brief Demonstrates how to control manual graphics tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUManualGFXTuning.h"
#include "SDK/Include/IGPUTuning.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu(IADLXManualGraphicsTuning1Ptr manualGFXTuning1, IADLXManualGraphicsTuning2Ptr manualGFXTuning2);

// Menu action control
void MenuControl(IADLXManualGraphicsTuning1Ptr manualGFXTuning1, IADLXManualGraphicsTuning2Ptr manualGFXTuning2);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

/***** The first is pre-Navi, the second is post-Navi *****/
// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange(IADLXManualGraphicsTuning1Ptr manualGFXTuning1);
void ShowFrequencyAndVoltageRange(IADLXManualGraphicsTuning2Ptr manualGFXTuning2);
// Display current GPU tuning states
void GetCurrentStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1);
void GetCurrentStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2);
// Set GPU states
void SetGPUStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1);
void SetGPUStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        IADLXGPUTuningServicesPtr gpuTuningService;
        res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices(&gpuTuningService);
        if (ADLX_FAILED (res))
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU tuning services failed", 0);
        }
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_FAILED (res))
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU list failed", 0);
        }
        IADLXGPUPtr oneGPU;
        res = gpus->At(0, &oneGPU);
        if (ADLX_FAILED (res) || oneGPU == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU failed", 0);
        }
        adlx_bool supported = false;
        res = gpuTuningService->IsSupportedManualGFXTuning(oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tThis GPU doesn't supported manual graphics tuning", 0);
        }
        IADLXInterfacePtr manualGFXTuningIfc;
        res = gpuTuningService->GetManualGFXTuning(oneGPU, &manualGFXTuningIfc);
        if (ADLX_FAILED (res) || manualGFXTuningIfc == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual graphics tuning interface failed", 0);
        }
        // Pre-Navi ASIC
        IADLXManualGraphicsTuning1Ptr manualGFXTuning1(manualGFXTuningIfc);
        // Post-Navi ASIC
        IADLXManualGraphicsTuning2Ptr manualGFXTuning2(manualGFXTuningIfc);
        if (manualGFXTuning1 == nullptr && manualGFXTuning2 == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual graphics tuning failed", 0);
        }
        // Display main menu options
        MainMenu(manualGFXTuning1, manualGFXTuning2);

        // Get and execute the choice
        MenuControl(manualGFXTuning1, manualGFXTuning2);
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu(IADLXManualGraphicsTuning1Ptr manualGFXTuning1, IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{

    if (manualGFXTuning1)
        std::cout << "\tThe current GPU is pre-Navi. Choose from the following options:" << std::endl;
    else if (manualGFXTuning2)
        std::cout << "\tThe current GPU is post-Navi. Choose from the following options:" << std::endl;
    std::cout << "\t->Press 1 to display GPU frequency and voltage" << std::endl;
    std::cout << "\t->Press 2 to display current GPU states" << std::endl;
    std::cout << "\t->Press 3 to set GPU states" << std::endl;
    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(IADLXManualGraphicsTuning1Ptr manualGFXTuning1, IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
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
                ShowFrequencyAndVoltageRange(manualGFXTuning1);
                break;

            // Display current GPU tuning states
            case '2':
                GetCurrentStates(manualGFXTuning1);
                break;

            // Set GPU states
            case '3':
                SetGPUStates(manualGFXTuning1);
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
                ShowFrequencyAndVoltageRange(manualGFXTuning2);
                break;

            // Display current GPU tuning states
            case '2':
                GetCurrentStates(manualGFXTuning2);
                break;

            // Set GPU states
            case '3':
                SetGPUStates(manualGFXTuning2);
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
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange(IADLXManualGraphicsTuning1Ptr manualGFXTuning1)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning1->GetGPUTuningRanges(&freqRange, &voltRange);
    std::cout << "\tFrequency range: (" << freqRange.minValue
              << ", " << freqRange.maxValue << ")" << std::endl;
    std::cout << "\tVoltage range: (" << voltRange.minValue
              << ", " << voltRange.maxValue << ")" << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1)
{
    IADLXManualTuningStateListPtr states;
    IADLXManualTuningStatePtr oneState;
    manualGFXTuning1->GetGPUTuningStates(&states);
    for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
    {
        states->At(crt, &oneState);
        adlx_int freq = 0, volt = 0;
        oneState->GetFrequency(&freq);
        oneState->GetVoltage(&volt);
        std::cout << "\tThe current state " << crt << ": frequency is " << freq << ", voltage is " << volt << std::endl;
    }
}

// Set GPU states
void SetGPUStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1)
{
    IADLXManualTuningStateListPtr states;
    IADLXManualTuningStatePtr oneState;
    manualGFXTuning1->GetEmptyGPUTuningStates(&states);
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning1->GetGPUTuningRanges(&freqRange, &voltRange);
    for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
    {
        states->At(crt, &oneState);
        adlx_int freq = 0, volt = 0;
        int freqStep = (freqRange.maxValue - freqRange.minValue) / (states->Size());
        int voltStep = (voltRange.maxValue - voltRange.minValue) / (states->Size());
        oneState->SetFrequency(freqRange.minValue + freqStep * crt);
        oneState->GetFrequency(&freq);
        oneState->SetVoltage(voltRange.minValue + voltStep * crt);
        oneState->GetVoltage(&volt);
        std::cout << "\tSet empty state " << crt << ": frequency is " << freq << ", voltage is " << volt << std::endl;
    }
    adlx_int errorIndex;
    res = manualGFXTuning1->IsValidGPUTuningStates(states, &errorIndex);
    if (ADLX_SUCCEEDED(res))
    {
        manualGFXTuning1->SetGPUTuningStates(states);
    }
    else
        std::cout << "\tIsValidGPUTuningStates, errorIndex is : " << errorIndex << std::endl;

    res = manualGFXTuning1->GetGPUTuningStates(&states);
    std::cout << "\tAfter setting:" << std::endl;
    for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
    {
        res = states->At(crt, &oneState);
        adlx_int freq = 0, volt = 0;
        oneState->GetFrequency(&freq);
        oneState->GetVoltage(&volt);
        std::cout << "\tThe current state " << crt << ": frequency is " << freq << ", voltage is " << volt << std::endl;
    }
}

// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    manualGFXTuning2->GetGPUMinFrequencyRange(&freqRange);
    std::cout << "\tGPU min frequency range: (" << freqRange.minValue
              << ", " << freqRange.maxValue << ")" << std::endl;
    manualGFXTuning2->GetGPUMaxFrequencyRange(&freqRange);
    std::cout << "\tGPU max frequency range: (" << freqRange.minValue
              << ", " << freqRange.maxValue << ")" << std::endl;
    ADLX_RESULT res = manualGFXTuning2->GetGPUVoltageRange(&voltRange);
    std::cout << "\tVoltage range: (" << voltRange.minValue
              << ", " << voltRange.maxValue << ")" << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    manualGFXTuning2->GetGPUMinFrequency(&minFreq);
    manualGFXTuning2->GetGPUMaxFrequency(&maxFreq);
    manualGFXTuning2->GetGPUVoltage(&volt);
    std::cout << "\tCurrent GPU min frequency: " << minFreq << std::endl;
    std::cout << "\tCurrent GPU max frequency: " << maxFreq << std::endl;
    std::cout << "\tCurrent GPU clock voltage: " << volt << std::endl;
}

// Set GPU states
void SetGPUStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    manualGFXTuning2->GetGPUMinFrequencyRange(&freqRange);
    manualGFXTuning2->GetGPUVoltageRange(&voltRange);
    manualGFXTuning2->SetGPUMinFrequency(freqRange.minValue);
    manualGFXTuning2->SetGPUMaxFrequency(freqRange.maxValue);
    manualGFXTuning2->SetGPUVoltage(voltRange.minValue + (voltRange.maxValue - voltRange.minValue) / 2);
    std::cout << "\tAfter setting:" << std::endl;
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    manualGFXTuning2->GetGPUMinFrequency(&minFreq);
    manualGFXTuning2->GetGPUMaxFrequency(&maxFreq);
    manualGFXTuning2->GetGPUVoltage(&volt);
    std::cout << "\tCurrent GPU min frequency: " << minFreq << std::endl;
    std::cout << "\tCurrent GPU max frequency: " << maxFreq << std::endl;
    std::cout << "\tCurrent GPU clock voltage: " << volt << std::endl;
}