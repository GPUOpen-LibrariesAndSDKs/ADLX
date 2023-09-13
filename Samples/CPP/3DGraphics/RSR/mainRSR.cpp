//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainRSR.cpp
/// \brief Demonstrates how to access AMD Radeon Super Resolution options, and perform related testing when programming with ADLX.

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

// Display Radeon Super Resolution support
void ShowRadeonSuperResolutionSupport(const IADLX3DRadeonSuperResolutionPtr& rsr);

// Display current Radeon Super Resolution state
void GetRadeonSuperResolutionState(const IADLX3DRadeonSuperResolutionPtr& rsr);

// Set Radeon Super Resolution state
void SetRadeonSuperResolutionState(const IADLX3DRadeonSuperResolutionPtr& rsr, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DRadeonSuperResolutionPtr& rsr);

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
        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get RadeonSuperResolution interface
            IADLX3DRadeonSuperResolutionPtr rsr;
            res = d3dSettingSrv->GetRadeonSuperResolution(&rsr);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(rsr);
            }
            else
            {
                std::cout << "Get RadeonSuperResolution res: " << res << std::endl;
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

void ShowRadeonSuperResolutionSupport(const IADLX3DRadeonSuperResolutionPtr& rsr)
{
    adlx_bool supported = false;
    rsr->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetRadeonSuperResolutionState(const IADLX3DRadeonSuperResolutionPtr& rsr)
{
    adlx_bool enabled = false;
    rsr->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << std::endl;
    adlx_int sharpness;
    ADLX_IntRange sharpnessRange;
    rsr->GetSharpness(&sharpness);
    rsr->GetSharpnessRange(&sharpnessRange);
    std::cout << "\tCurrent sharpness:" << sharpness << std::endl
              << "\tSharpness limit [ " << sharpnessRange.minValue << " ," << sharpnessRange.maxValue << " ], step: " << sharpnessRange.step << std::endl;
}

void SetRadeonSuperResolutionState(const IADLX3DRadeonSuperResolutionPtr& rsr, int index)
{
    ADLX_RESULT res = rsr->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int sharpness;
        ADLX_IntRange sharpnessRange;
        rsr->GetSharpness(&sharpness);
        rsr->GetSharpnessRange(&sharpnessRange);
        if (sharpness != sharpnessRange.minValue)
        {
            res = rsr->SetSharpness(sharpnessRange.minValue);
            std::cout << "\tSet minimum sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
        }
        else
        {
            res = rsr->SetSharpness(sharpnessRange.maxValue);
            std::cout << "\tSet maximum sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
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

    std::cout << "\t->Press 1 to display Radeon Super Resolution support" << std::endl;
    std::cout << "\t->Press 2 to display current Radeon Super Resolution state" << std::endl;
    std::cout << "\t->Press 3 to enable Radeon Super Resolution" << std::endl;
    std::cout << "\t->Press 4 to disable Radeon Super Resolution" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DRadeonSuperResolutionPtr& d3dRadeonSuperResolution)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Radeon Super Resolution support
        case '1':
            ShowRadeonSuperResolutionSupport(d3dRadeonSuperResolution);
            break;

            // Display current Radeon Super Resolution state
        case '2':
            GetRadeonSuperResolutionState(d3dRadeonSuperResolution);
            break;

            // Set Radeon Super Resolution
        case '3':
        case '4':
            SetRadeonSuperResolutionState(d3dRadeonSuperResolution, num - '3');
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