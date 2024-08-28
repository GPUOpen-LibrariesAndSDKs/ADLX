//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
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
        if (ADLX_SUCCEEDED (res))
        {
            IADLXGPUListPtr gpus;
            res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
            if (ADLX_SUCCEEDED (res))
            {
                IADLXGPUPtr oneGPU;
                res = gpus->At(0, &oneGPU);
                if (ADLX_SUCCEEDED (res) && oneGPU != nullptr)
                {
                    adlx_bool supported = false;
                    res = gpuTuningService->IsSupportedPresetTuning(oneGPU, &supported);
                    if (ADLX_SUCCEEDED (res) && supported)
                    {
                        IADLXInterfacePtr gpuPresetTuningIfc;
                        res = gpuTuningService->GetPresetTuning(oneGPU, &gpuPresetTuningIfc);
                        if (ADLX_SUCCEEDED (res) && gpuPresetTuningIfc != nullptr)
                        {
                            IADLXGPUPresetTuningPtr gpuPresetTuning(gpuPresetTuningIfc);
                            if (gpuPresetTuning != nullptr)
                            {
                                // Display main menu options
                                MainMenu();

                                // Get and execute the choice
                                MenuControl(gpuPresetTuning);
                            }
                            else
                            {
                                std::cout << "\tGet GPU preset tuning failed" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "\tGet GPU preset tuning interface failed" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "\tGPU preset tuning is not supported by this GPU" << std::endl;
                    }
                }
                else
                {
                    std::cout << "\tGet GPU failed" << std::endl;
                }
            }
            else
            {
                std::cout << "\tGet GPU list failed" << std::endl;
            }
        }
        else
        {
            std::cout << "\tGet GPU tuning services failed" << std::endl;
        }
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
    ADLX_RESULT res = gpuPresetTuning->IsSupportedPowerSaver(&supported);
    std::cout << "\tIs Power Saver supported by the GPU: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
    supported = false;
    res = gpuPresetTuning->IsSupportedQuiet(&supported);
    std::cout << "\tIs Quiet supported by the GPU: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
    supported = false;
    res = gpuPresetTuning->IsSupportedBalanced(&supported);
    std::cout << "\tIs Balanced supported by the GPU: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
    supported = false;
    res = gpuPresetTuning->IsSupportedTurbo(&supported);
    std::cout << "\tIs Turbo supported by the GPU: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
    supported = false;
    res = gpuPresetTuning->IsSupportedRage(&supported);
    std::cout << "\tIs Rage supported by the GPU: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

// Display current GPU tuning states
void GetCurrentStates(IADLXGPUPresetTuningPtr gpuPresetTuning)
{
    adlx_bool applied = false;
    ADLX_RESULT res = gpuPresetTuning->IsCurrentPowerSaver(&applied);
    std::cout << "\tIs Power Saver applied: " << applied << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->IsCurrentQuiet(&applied);
    std::cout << "\tIs Quiet applied: " << applied << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->IsCurrentBalanced(&applied);
    std::cout << "\tIs Balanced applied: " << applied << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->IsCurrentTurbo(&applied);
    std::cout << "\tIs Turbo applied: " << applied << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->IsCurrentRage(&applied);
    std::cout << "\tIs Rage applied: " << applied << ", return code is: " << res << "(0 means success)" << std::endl;
}

// Set GPU states
void SetGPUStates(IADLXGPUPresetTuningPtr gpuPresetTuning)
{
    adlx_bool applied = false;
    ADLX_RESULT res = gpuPresetTuning->SetPowerSaver();
    res = gpuPresetTuning->IsCurrentPowerSaver(&applied);
    std::cout << "\tSet Power Saver preset tuning " << (applied ? "Successful" : "failed") << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->SetQuiet();
    res = gpuPresetTuning->IsCurrentQuiet(&applied);
    std::cout << "\tSet Quiet preset tuning " << (applied ? "Successful" : "failed") << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->SetBalanced();
    res = gpuPresetTuning->IsCurrentBalanced(&applied);
    std::cout << "\tSet Balanced preset tuning " << (applied ? "Successful" : "failed") << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->SetTurbo();
    res = gpuPresetTuning->IsCurrentTurbo(&applied);
    std::cout << "\tSet Turbo preset tuning " << (applied ? "Successful" : "failed") << ", return code is: " << res << "(0 means success)" << std::endl;
    applied = false;
    res = gpuPresetTuning->SetRage();
    res = gpuPresetTuning->IsCurrentRage(&applied);
    std::cout << "\tSet Rage preset tuning " << (applied ? "Successful" : "failed") << ", return code is: " << res << "(0 means success)" << std::endl;
}
