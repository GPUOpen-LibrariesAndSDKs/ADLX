//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainBoost.cpp
/// \brief Demonstrates how to access AMD Radeon Boost options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <string>
#include <vector>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display Boost support
void ShowBoostSupport(const IADLX3DBoostPtr& d3dBoost);

// Display current Boost state
void GetBoostState(const IADLX3DBoostPtr& d3dBoost);

// Set Boost state
void SetBoostState(const IADLX3DBoostPtr& d3dBoost, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DBoostPtr& d3dBoost);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (!gpus->Empty() && ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPUPtr gpuInfo;
            adlx_uint index = 0;
            res = gpus->At(index, &gpuInfo);

            // Get Boost interface
            IADLX3DBoostPtr d3dBoost;
            res = d3dSettingSrv->GetBoost(gpuInfo, &d3dBoost);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dBoost);
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get 3DSettings services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowBoostSupport(const IADLX3DBoostPtr& d3dBoost)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dBoost->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetBoostState(const IADLX3DBoostPtr& d3dBoost)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dBoost->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
    adlx_int resolution;
    ADLX_IntRange resolutionRange;
    res = d3dBoost->GetResolution(&resolution);
    if (ADLX_SUCCEEDED (res))
        std::cout << "\tCurrent Resolution:" << resolution << std::endl;
    res = d3dBoost->GetResolutionRange(&resolutionRange);
    if (ADLX_SUCCEEDED (res))
        std::cout << "\tResolution limit [ " << resolutionRange.minValue << " ," << resolutionRange.maxValue << " ], step: " << resolutionRange.step << std::endl;
}

void SetBoostState(const IADLX3DBoostPtr& d3dBoost, int index)
{
    ADLX_RESULT res = d3dBoost->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int resolution;
        ADLX_IntRange resolutionRange;
        ADLX_RESULT res1 = d3dBoost->GetResolution(&resolution);
        ADLX_RESULT res2 = d3dBoost->GetResolutionRange(&resolutionRange);
        if (ADLX_SUCCEEDED (res1) && ADLX_SUCCEEDED (res2))
        {
            if (resolution != resolutionRange.minValue)
            {
                res = d3dBoost->SetResolution(resolutionRange.minValue);
                std::cout << "\tSet minimum resolution limit: return code is: " << res << "(0 means success)" << std::endl;
            }
            else
            {
                res = d3dBoost->SetResolution(resolutionRange.maxValue);
                std::cout << "\tSet maximum resolution limit: return code is: " << res << "(0 means success)" << std::endl;
            }
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

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display Boost support" << std::endl;
    std::cout << "\t->Press 2 to display current Boost state" << std::endl;
    std::cout << "\t->Press 3 to enable Boost" << std::endl;
    std::cout << "\t->Press 4 to disable Boost" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DBoostPtr& d3dBoost)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Boost support
        case '1':
            ShowBoostSupport(d3dBoost);
            break;

            // Display current Boost state
        case '2':
            GetBoostState(d3dBoost);
            break;

            // Set Boost
        case '3':
        case '4':
            SetBoostState(d3dBoost, num - '3');
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