//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUPresetTuning.cpp
/// \brief Demonstrates how to control GPU preset tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUPresetTuning.h"
#include "SDK/Include/IGPUTuning.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUPresetTuningPtr gpuPresetTuning);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display GPU tuning support states
void ShowIsSupported(IADLXGPUPresetTuningPtr gpuPresetTuning);

// Display current GPU tuning states
void GetCurrentStates(IADLXGPUPresetTuningPtr gpuPresetTuning);

// Set GPU states
void SetGPUStates(IADLXGPUPresetTuningPtr gpuPresetTuning);

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
        res = gpuTuningService->IsSupportedPresetTuning(oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGPU preset tuning is not supported by this GPU", 0);
        }
        IADLXInterfacePtr gpuPresetTuningIfc;
        res = gpuTuningService->GetPresetTuning(oneGPU, &gpuPresetTuningIfc);
        if (ADLX_FAILED (res) || gpuPresetTuningIfc == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU preset tuning interface failed", 0);
        }
        IADLXGPUPresetTuningPtr gpuPresetTuning(gpuPresetTuningIfc);
        if (gpuPresetTuning == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet GPU preset tuning failed", 0);
        }
        // Display main menu options
        MainMenu();

        // Get and execute the choice
        MenuControl(gpuPresetTuning);
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
void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display GPU tuning support states" << std::endl;
    std::cout << "\t->Press 2 to display current GPU tuning states" << std::endl;
    std::cout << "\t->Press 3 to set GPU states" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(IADLXGPUPresetTuningPtr gpuPresetTuning)
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
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display GPU tuning support states
void ShowIsSupported(IADLXGPUPresetTuningPtr gpuPresetTuning)
{
    adlx_bool supported = false;
    gpuPresetTuning->IsSupportedPowerSaver(&supported);
    std::cout << "\tIs Power Saver supported by the GPU: " << supported << std::endl;
    supported = false;
    gpuPresetTuning->IsSupportedQuiet(&supported);
    std::cout << "\tIs Quiet supported by the GPU: " << supported << std::endl;
    supported = false;
    gpuPresetTuning->IsSupportedBalanced(&supported);
    std::cout << "\tIs Balanced supported by the GPU: " << supported << std::endl;
    supported = false;
    gpuPresetTuning->IsSupportedTurbo(&supported);
    std::cout << "\tIs Turbo supported by the GPU: " << supported << std::endl;
    supported = false;
    gpuPresetTuning->IsSupportedRage(&supported);
    std::cout << "\tIs Rage supported by the GPU: " << supported << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXGPUPresetTuningPtr gpuPresetTuning)
{
    adlx_bool applied = false;
    gpuPresetTuning->IsCurrentPowerSaver(&applied);
    std::cout << "\tIs Power Saver applied: " << applied << std::endl;
    applied = false;
    gpuPresetTuning->IsCurrentQuiet(&applied);
    std::cout << "\tIs Quiet applied: " << applied << std::endl;
    applied = false;
    gpuPresetTuning->IsCurrentBalanced(&applied);
    std::cout << "\tIs Balanced applied: " << applied << std::endl;
    applied = false;
    gpuPresetTuning->IsCurrentTurbo(&applied);
    std::cout << "\tIs Turbo applied: " << applied << std::endl;
    applied = false;
    gpuPresetTuning->IsCurrentRage(&applied);
    std::cout << "\tIs Rage applied: " << applied << std::endl;
}

// Set GPU states
void SetGPUStates(IADLXGPUPresetTuningPtr gpuPresetTuning)
{
    adlx_bool applied = false;
    gpuPresetTuning->SetPowerSaver();
    gpuPresetTuning->IsCurrentPowerSaver(&applied);
    std::cout << "\tSet Power Saver preset tuning " << (applied ? "Successful" : "failed") << std::endl;
    applied = false;
    gpuPresetTuning->SetQuiet();
    gpuPresetTuning->IsCurrentQuiet(&applied);
    std::cout << "\tSet Quiet preset tuning " << (applied ? "Successful" : "failed") << std::endl;
    applied = false;
    gpuPresetTuning->SetBalanced();
    gpuPresetTuning->IsCurrentBalanced(&applied);
    std::cout << "\tSet Balanced preset tuning " << (applied ? "Successful" : "failed") << std::endl;
    applied = false;
    gpuPresetTuning->SetTurbo();
    gpuPresetTuning->IsCurrentTurbo(&applied);
    std::cout << "\tSet Turbo preset tuning " << (applied ? "Successful" : "failed") << std::endl;
    applied = false;
    gpuPresetTuning->SetRage();
    gpuPresetTuning->IsCurrentRage(&applied);
    std::cout << "\tSet Rage preset tuning " << (applied ? "Successful" : "failed") << std::endl;
}
