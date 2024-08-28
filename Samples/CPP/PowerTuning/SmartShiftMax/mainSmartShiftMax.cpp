//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartShiftMax.cpp
/// \brief Demonstrates how to control AMD SmartShift Max when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPowerTuning.h"
#include "SDK/Include/ISystem1.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display AMD SmartShift Max support
void ShowSmartShiftMaxSupport(const IADLXSmartShiftMaxPtr& ssm);

// Display current AMD SmartShift Max state
void ShowSmartShiftMaxSate(const IADLXSmartShiftMaxPtr& ssm);

// Set AMD SmartShift Max bias mode
void SetSmartShiftMaxBiasMode(const IADLXSmartShiftMaxPtr& ssm, int index);

// Set AMD SmartShift Max bias value
void SetSmartShiftMaxBiasValue(const IADLXSmartShiftMaxPtr& ssm);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXSmartShiftMaxPtr& ssm);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get IADLXSystem1 interface via IADLXSystem::QueryInterface
        IADLXSystem1Ptr system1;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem1::IID(), reinterpret_cast<void**>(&system1));
        if (ADLX_SUCCEEDED(res))
        {
            // Get power tuning service 
            IADLXPowerTuningServicesPtr powerTuningService;
            res = system1->GetPowerTuningServices(&powerTuningService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get AMD SmartShift Max interface
                IADLXSmartShiftMaxPtr ssm;
                res = powerTuningService->GetSmartShiftMax(&ssm);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(ssm);
                }
                else
                    std::cout << "Failed to get AMD SmartShift Max interface" << std::endl;
            }
            else
                std::cout << "Failed to get power tuning service" << std::endl;
        }
        else
            std::cout << "Failed to get IADLXSystem1" << std::endl;
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

void ShowSmartShiftMaxSupport(const IADLXSmartShiftMaxPtr& ssm)
{
    adlx_bool supported = false;
    ssm->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void ShowSmartShiftMaxSate(const IADLXSmartShiftMaxPtr& ssm)
{
    ADLX_SSM_BIAS_MODE mode;
    ADLX_RESULT ret = ssm->GetBiasMode(&mode);
    if (ADLX_SUCCEEDED(ret))
        std::cout << "\tBias mode: " << (mode == ADLX_SSM_BIAS_MODE::SSM_BIAS_MANUAL ? "manual" : "auto") << std::endl;
    else
        std::cout << "\tFailed to get bias mode, error code: " << ret << std::endl;

    adlx_int bias = 0;
    ret = ssm->GetBias(&bias);
    if (ADLX_SUCCEEDED(ret))
        std::cout << "\tBias value: " << bias << std::endl;
    else
        std::cout << "\tFailed to get bias value, error code: " << ret << std::endl;

    ADLX_IntRange range;
    ret = ssm->GetBiasRange(&range);
    if (ADLX_SUCCEEDED(ret))
        std::cout << "\tBias range: [ " << range.minValue << " ," << range.maxValue << " ], step: " << range.step << std::endl;
    else
        std::cout << "\tFailed to get bias range, error code: " << ret << std::endl;
}

void SetSmartShiftMaxBiasMode(const IADLXSmartShiftMaxPtr& ssm, int index)
{
    ADLX_SSM_BIAS_MODE mode = index == 0 ? ADLX_SSM_BIAS_MODE::SSM_BIAS_MANUAL : ADLX_SSM_BIAS_MODE::SSM_BIAS_AUTO;
    ADLX_RESULT res = ssm->SetBiasMode(mode);
    std::cout << "\tSet bias mode " << (mode == ADLX_SSM_BIAS_MODE::SSM_BIAS_MANUAL ? "manual" : "auto") << ", return code: " << res << std::endl;
}

void SetSmartShiftMaxBiasValue(const IADLXSmartShiftMaxPtr& ssm)
{
    adlx_int bias = 0;
    ssm->GetBias(&bias);
    ADLX_IntRange range;
    ssm->GetBiasRange(&range);
    adlx_int base = (range.maxValue + range.minValue) / 2;
    adlx_int value = bias == base ? base + range.step : base;
    ADLX_RESULT res = ssm->SetBias(value);
    std::cout << "\tSet bias value: " << value << ", return code: " << res << std::endl;
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;
    std::cout << "\t->Press 1 to display AMD SmartShift Max support" << std::endl;
    std::cout << "\t->Press 2 to display AMD SmartShift Max bias value, bias mode, and bias range" << std::endl;
    std::cout << "\t->Press 3 to set AMD SmartShift Max bias mode to Manual" << std::endl;
    std::cout << "\t->Press 4 to set AMD SmartShift Max bias mode to Auto" << std::endl;
    std::cout << "\t->Press 5 to set AMD SmartShift Max bias value" << std::endl;
    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(const IADLXSmartShiftMaxPtr& ssm)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display AMD SmartShift max support
        case '1':
            ShowSmartShiftMaxSupport(ssm);
            break;

            // Display current AMD SmartShift max state
        case '2':
            ShowSmartShiftMaxSate(ssm);
            break;

            // Set AMD SmartShift max bias mode
        case '3':
        case '4':
            SetSmartShiftMaxBiasMode(ssm, num - '3');
            break;

            // Set AMD SmartShift max bias value
        case '5':
            SetSmartShiftMaxBiasValue(ssm);
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

int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}