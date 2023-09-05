//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualPowerTuning.cpp
/// \brief Demonstrates how to control manual power tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUManualPowerTuning.h"
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
void MenuControl(IADLXManualPowerTuningPtr manualPowerTuning);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display power limit range
void ShowGetPowerLimitRange(IADLXManualPowerTuningPtr manualPowerTuning);

// Display current power limit
void ShowGetPowerLimit(IADLXManualPowerTuningPtr manualPowerTuning);

// Set power limit
void ShowSetPowerLimit(IADLXManualPowerTuningPtr manualPowerTuning);

//Show to check TDC  limit is supported
void ShowTDCLimitSupported(IADLXManualPowerTuningPtr manualPowerTuning);

// Show how to get TDC limit range.
void ShowGetTDCLimitRange(IADLXManualPowerTuningPtr manualPowerTuning);

// Show how to get current TDC limit.
void ShowGetTDCLimit(IADLXManualPowerTuningPtr manualPowerTuning);

// Show how to set TDC limit.
void ShowSetTDCLimit(IADLXManualPowerTuningPtr manualPowerTuning);

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
        res = gpuTuningService->IsSupportedManualPowerTuning(oneGPU, &supported);
        if (ADLX_FAILED (res) || supported == false)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tThis GPU does not support manual power tuning", 0);
        }
        IADLXInterfacePtr manualPowerTuningIfc;
        res = gpuTuningService->GetManualPowerTuning(oneGPU, &manualPowerTuningIfc);
        if (ADLX_FAILED (res) || manualPowerTuningIfc == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual power tuning interface failed", 0);
        }
        IADLXManualPowerTuningPtr manualPowerTuning(manualPowerTuningIfc);
        if (manualPowerTuning == nullptr)
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("\tGet manual power tuning failed", 0);
        }
        // Display main menu options
        MainMenu();

        // Get and execute the choice
        MenuControl(manualPowerTuning);
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

    std::cout << "\t->Press 1 to show how to get power limit range" << std::endl;
    std::cout << "\t->Press 2 to show how to get current power limit" << std::endl;
    std::cout << "\t->Press 3 to show how to set power limit" << std::endl;
    std::cout << "\t->Press 4 to show TDC Limit is supported" << std::endl;
    std::cout << "\t->Press 5 to show how to get TDC limit range" << std::endl;
    std::cout << "\t->Press 6 to show how to get current TDC limit" << std::endl;
    std::cout << "\t->Press 7 to show how to set TDC limit" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(IADLXManualPowerTuningPtr manualPowerTuning)
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
            // Show to check if TDCLimit is supported
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
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display power limit range
void ShowGetPowerLimitRange(IADLXManualPowerTuningPtr manualPowerTuning)
{
    ADLX_IntRange powerRange;
    ADLX_RESULT res = manualPowerTuning->GetPowerLimitRange(&powerRange);
    std::cout << "\tPower limit range: (" << powerRange.minValue
              << ", " << powerRange.maxValue << ")" << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Display current power limit
void ShowGetPowerLimit(IADLXManualPowerTuningPtr manualPowerTuning)
{
    adlx_int powerLimit;
    ADLX_RESULT res = manualPowerTuning->GetPowerLimit(&powerLimit);
    std::cout << "\tCurrent power limit: " << powerLimit << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Set power limit
void ShowSetPowerLimit(IADLXManualPowerTuningPtr manualPowerTuning)
{
    ADLX_IntRange powerRange;
    ADLX_RESULT res = manualPowerTuning->GetPowerLimitRange(&powerRange);
    res = manualPowerTuning->SetPowerLimit(powerRange.step + powerRange.minValue + (powerRange.maxValue - powerRange.minValue) / 2);
    std::cout << "\tSet power limit " << (ADLX_SUCCEEDED (res) ? "succeeded" : "failed") << std::endl;
    adlx_int powerLimit;
    res = manualPowerTuning->GetPowerLimit(&powerLimit);
    std::cout << "\tSet current power limit to: " << powerLimit << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Show TDCLimit is supported.
void ShowTDCLimitSupported(IADLXManualPowerTuningPtr manualPowerTuning)
{
    adlx_bool supportedTDC;
    ADLX_RESULT res = manualPowerTuning->IsSupportedTDCLimit(&supportedTDC);
    std::cout << "\tTDC limit is supported: " << supportedTDC << ", return code is: "<< res << "(0 means success)" << std::endl;
}

// Show how to get tdc limit range.
void ShowGetTDCLimitRange(IADLXManualPowerTuningPtr manualPowerTuning)
{
    ADLX_IntRange tdcRange;
    ADLX_RESULT res = manualPowerTuning->GetTDCLimitRange(&tdcRange);
    std::cout << "\tGet TDC limit range is: (" << tdcRange.minValue
        << ", " << tdcRange.maxValue << "), return code (0 is Success) is: " << res << std::endl;
}

// Show how to get current TDC limit.
void ShowGetTDCLimit(IADLXManualPowerTuningPtr manualPowerTuning)
{
    adlx_int tdcLimit;
    ADLX_RESULT res = manualPowerTuning->GetTDCLimit(&tdcLimit);
    std::cout << "\tThe current TDC limit is: " << tdcLimit << ", return code (0 is Success) is: " << res << std::endl;
}

// Show how to set TDC limit.
void ShowSetTDCLimit(IADLXManualPowerTuningPtr manualPowerTuning)
{
    ADLX_IntRange tdcRange;
    ADLX_RESULT res = manualPowerTuning->GetTDCLimitRange(&tdcRange);

    res = manualPowerTuning->SetTDCLimit(tdcRange.step + tdcRange.minValue + (tdcRange.maxValue - tdcRange.minValue) / 2);
    adlx_int tdcLimit;
    res = manualPowerTuning->GetTDCLimit (&tdcLimit);
    std::cout << "\tSet current TDC limit to: " << tdcLimit << ", return code (0 is Success) is: " << res << std::endl;
}