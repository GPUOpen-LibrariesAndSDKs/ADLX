//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAnisotropicFiltering.cpp
/// \brief Demonstrates how to access anisotropic filtering options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <map>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display anisotropic filtering support
void ShowSupport(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering);

// Get anisotropic filtering current state
void GetState(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering);

// Set anisotropic filtering state
void SetState(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering);

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

            // Get AnisotropicFilteringPtr interface
            IADLX3DAnisotropicFilteringPtr anisotropicFiltering;
            res = d3dSettingSrv->GetAnisotropicFiltering(gpuInfo, &anisotropicFiltering);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(anisotropicFiltering);
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

static const std::map<ADLX_ANISOTROPIC_FILTERING_LEVEL, const char*> levelMap =
    {
        {AF_LEVEL_INVALID, "Invalid"},
        {AF_LEVEL_X2, "2X"},
        {AF_LEVEL_X4, "4X"},
        {AF_LEVEL_X8, "8X"},
        {AF_LEVEL_X16, "16X"}};

void ShowSupport(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering)
{
    adlx_bool supported = false;
    ADLX_RESULT res = anisotropicFiltering->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetState(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = anisotropicFiltering->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
    ADLX_ANISOTROPIC_FILTERING_LEVEL level;
    res = anisotropicFiltering->GetLevel(&level);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tLevel: " << levelMap.find(level)->second << std::endl;
}

void SetState(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    res = anisotropicFiltering->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success) "<< std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        ADLX_ANISOTROPIC_FILTERING_LEVEL level;
        res = anisotropicFiltering->GetLevel(&level);
        if (ADLX_SUCCEEDED (res))
        {
            level = (level == AF_LEVEL_X2) ? AF_LEVEL_X4 : AF_LEVEL_X2;
            res = anisotropicFiltering->SetLevel(level);
            std::cout << "\tSet level: " << levelMap.find(level)->second << "Return code is: " << res << " (0 means success) " << std::endl;
        }
    }
}

int WaitAndExit(const char* msg, const int retCode)
{
    // Print out the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display anisotropic filtering support" << std::endl;
    std::cout << "\t->Press 2 to display current anisotropic filtering state" << std::endl;
    std::cout << "\t->Press 3 to enable and change anisotropic filtering levels" << std::endl;
    std::cout << "\t->Press 4 to disable anisotropic filtering" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(const IADLX3DAnisotropicFilteringPtr& anisotropicFiltering)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display anisotropic filtering support
        case '1':
            ShowSupport(anisotropicFiltering);
            break;

            // Display current anisotropic filtering state
        case '2':
            GetState(anisotropicFiltering);
            break;

            // Enable and change anisotropic filtering levels
        case '3':
        case '4':
            SetState(anisotropicFiltering, num - '3');
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
