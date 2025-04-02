//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
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
// Display default GPU tuning states
void GetDefaultStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2);
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
            std::cout << "\tGet GPU tuning services failed " << std::endl;
            goto EXIT;
        }
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_FAILED (res))
        {
            std::cout << "\tGet GPU list failed " << std::endl;
            goto EXIT;
        }
        IADLXGPUPtr oneGPU;
        res = gpus->At(0, &oneGPU);
        if (ADLX_FAILED (res) || oneGPU == nullptr)
        {
            std::cout << "\tGet GPU failed " << std::endl;
            goto EXIT;
        }
        adlx_bool supported = false;
        res = gpuTuningService->IsSupportedManualGFXTuning(oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
        {
            std::cout << "\tThis GPU doesn't supported manual graphics tuning " << std::endl;
            goto EXIT;
        }
        IADLXInterfacePtr manualGFXTuningIfc;
        res = gpuTuningService->GetManualGFXTuning(oneGPU, &manualGFXTuningIfc);
        if (ADLX_FAILED (res) || manualGFXTuningIfc == nullptr)
        {
            std::cout << "\tGet manual graphics tuning interface failed " << std::endl;
            goto EXIT;
        }
        // Pre-Navi ASIC
        IADLXManualGraphicsTuning1Ptr manualGFXTuning1(manualGFXTuningIfc);
        // Post-Navi ASIC
        IADLXManualGraphicsTuning2Ptr manualGFXTuning2(manualGFXTuningIfc);
        if (manualGFXTuning1 == nullptr && manualGFXTuning2 == nullptr)
        {
            std::cout << "\tGet manual graphics tuning failed " << std::endl;
            goto EXIT;
        }
        // Display main menu options
        MainMenu(manualGFXTuning1, manualGFXTuning2);

        // Get and execute the choice
        MenuControl(manualGFXTuning1, manualGFXTuning2);
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    EXIT:
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
    std::cout << "\t->Press 4 to display default GPU states" << std::endl;
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

            // Display default GPU tuning states
            case '4':
                GetDefaultStates(manualGFXTuning2);
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
              << ", " << freqRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
    std::cout << "\tVoltage range: (" << voltRange.minValue
              << ", " << voltRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1)
{
    IADLXManualTuningStateListPtr states;
    IADLXManualTuningStatePtr oneState;
    ADLX_RESULT res = manualGFXTuning1->GetGPUTuningStates(&states);
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
        {
            states->At(crt, &oneState);
            adlx_int freq = 0, volt = 0;
            res = oneState->GetFrequency(&freq);
            std::cout << "\tThe current state " << crt << ": frequency is " << freq << ", return code is: "<< res << "(0 means success)" << std::endl;
            res = oneState->GetVoltage(&volt);
            std::cout << "\tThe current state " << crt << ": voltage is " << volt << ", return code is: "<< res << "(0 means success)" << std::endl;
        }
    }
}

// Set GPU states
void SetGPUStates(IADLXManualGraphicsTuning1Ptr manualGFXTuning1)
{
    IADLXManualTuningStateListPtr states;
    IADLXManualTuningStatePtr oneState;
    ADLX_RESULT res1 = manualGFXTuning1->GetEmptyGPUTuningStates(&states);
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res2 = manualGFXTuning1->GetGPUTuningRanges(&freqRange, &voltRange);
    if (ADLX_SUCCEEDED (res1) && ADLX_SUCCEEDED (res2))
    {
        for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
        {
            states->At(crt, &oneState);
            adlx_int freq = 0, volt = 0;
            int freqStep = (freqRange.maxValue - freqRange.minValue) / (states->Size());
            // The Step should not be too large
            if (freqStep >= 60)
                freqStep = 60;
            int voltStep = (voltRange.maxValue - voltRange.minValue) / (states->Size());
            // The Step should not be too large
            if (voltStep >= 20)
                voltStep = 20;
            ADLX_RESULT res = oneState->SetFrequency(freqRange.minValue + freqStep * crt);
            res = oneState->GetFrequency(&freq);
            res = oneState->SetVoltage(voltRange.minValue + voltStep * crt);
            res = oneState->GetVoltage(&volt);
            std::cout << "\tSet empty state " << crt << ": frequency is " << freq << ", voltage is " << volt << ", return code is: "<< res << "(0 means success)" << std::endl;
        }
    }
    
    adlx_int errorIndex;
    ADLX_RESULT res = manualGFXTuning1->IsValidGPUTuningStates(states, &errorIndex);
    if (ADLX_SUCCEEDED(res))
    {
        res = manualGFXTuning1->SetGPUTuningStates(states);
        std::cout << "\tSet GPU tuning states " << (ADLX_SUCCEEDED (res) ? "succeeded" : "failed") << std::endl;
    }
    else
        std::cout << "\tIsValidGPUTuningStates, errorIndex is : " << errorIndex << std::endl;

    res = manualGFXTuning1->GetGPUTuningStates(&states);
    std::cout << "\tAfter setting:" << std::endl;
    if (ADLX_SUCCEEDED (res))
    {
        for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt)
        {
            res = states->At(crt, &oneState);
            adlx_int freq = 0, volt = 0;
            res = oneState->GetFrequency(&freq);
            res = oneState->GetVoltage(&volt);
            std::cout << "\tThe current state " << crt << ": frequency is " << freq << ", voltage is " << volt << ", return code is: "<< res << "(0 means success)" << std::endl;
        }
    }
}

// Display GPU frequency and voltage range
void ShowFrequencyAndVoltageRange(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning2->GetGPUMinFrequencyRange(&freqRange);
    std::cout << "\tGPU min frequency range: (" << freqRange.minValue
              << ", " << freqRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUMaxFrequencyRange(&freqRange);
    std::cout << "\tGPU max frequency (offset) range: (" << freqRange.minValue
              << ", " << freqRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUVoltageRange(&voltRange);
    std::cout << "\tVoltage (offset) range: (" << voltRange.minValue
              << ", " << voltRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    ADLX_RESULT res = manualGFXTuning2->GetGPUMinFrequency(&minFreq);
    std::cout << "\tCurrent GPU min frequency: " << minFreq << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUMaxFrequency(&maxFreq);
    std::cout << "\tCurrent GPU max frequency (offset): " << maxFreq << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUVoltage(&volt);
    std::cout << "\tCurrent GPU clock voltage (offset): " << volt << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display default GPU tuning states
void GetDefaultStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    // Post-Navi ASIC
    IADLXManualGraphicsTuning2_1Ptr manualGFXTuning2_1(manualGFXTuning2);
    if (manualGFXTuning2_1 == nullptr)
    {
        std::cout << "\tGet default states failed" << std::endl;
        return;
    }

    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    ADLX_RESULT res = manualGFXTuning2_1->GetGPUMinFrequencyDefault(&minFreq);
    std::cout << "\tDefault GPU min frequency: " << minFreq << ", return code is: " << res << "(0 means success)" << std::endl;
    res = manualGFXTuning2_1->GetGPUMaxFrequencyDefault(&maxFreq);
    std::cout << "\tDefault GPU max frequency (offset): " << maxFreq << ", return code is: " << res << "(0 means success)" << std::endl;
    res = manualGFXTuning2_1->GetGPUVoltageDefault(&volt);
    std::cout << "\tDefault GPU clock voltage (offset): " << volt << ", return code is: " << res << "(0 means success)" << std::endl;
}

// Set GPU states
void SetGPUStates(IADLXManualGraphicsTuning2Ptr manualGFXTuning2)
{
    ADLX_IntRange freqRange, voltRange;
    ADLX_RESULT res = manualGFXTuning2->GetGPUMinFrequencyRange(&freqRange);
    res = manualGFXTuning2->GetGPUVoltageRange(&voltRange);
    res = manualGFXTuning2->SetGPUMinFrequency(freqRange.minValue);
    std::cout << "\tSet GPU min frequency " << (ADLX_SUCCEEDED (res) ? "succeeded" : "failed") << std::endl;
    res = manualGFXTuning2->SetGPUMaxFrequency(freqRange.minValue + 100);
    std::cout << "\tSet GPU max frequency (offset) " << (ADLX_SUCCEEDED (res) ? "succeeded" : "failed") << std::endl;
    res = manualGFXTuning2->SetGPUVoltage(voltRange.minValue + (voltRange.maxValue - voltRange.minValue) / 2);
    std::cout << "\tSet GPU voltage (offset) " << (ADLX_SUCCEEDED (res) ? "succeeded" : "failed") << std::endl;
    std::cout << "\tAfter setting:" << std::endl;
    adlx_int minFreq = 0, maxFreq = 0, volt = 0;
    res = manualGFXTuning2->GetGPUMinFrequency(&minFreq);
    std::cout << "\tCurrent GPU min frequency: " << minFreq << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUMaxFrequency(&maxFreq);
    std::cout << "\tCurrent GPU max frequency (offset): " << maxFreq << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = manualGFXTuning2->GetGPUVoltage(&volt);
    std::cout << "\tCurrent GPU clock voltage (offset): " << volt << ", return code is: "<< res << "(0 means success)" << std::endl;
}