//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiLag.cpp
/// \brief Demonstrates how to access AMD Radeon Anti-Lag options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display Anti-Lag support
void ShowAntiLagSupport(const IADLX3DAntiLagPtr& d3dAntiLag);

// Display current Anti-Lag state
void GetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag);

// Set Anti-Lag state
void SetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DAntiLagPtr& d3dAntiLag);

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

            // Get AntiLag interface
            IADLX3DAntiLagPtr d3dAntiLag;
            res = d3dSettingSrv->GetAntiLag(gpuInfo, &d3dAntiLag);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dAntiLag);
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

void ShowAntiLagSupport(const IADLX3DAntiLagPtr& d3dAntiLag)
{
    adlx_bool supported = false;
    d3dAntiLag->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag)
{
    adlx_bool enabled = false;
    d3dAntiLag->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << std::endl;
}

void SetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, int index)
{
    ADLX_RESULT res = d3dAntiLag->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
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

    std::cout << "\t->Press 1 to display Anti-Lag support" << std::endl;
    std::cout << "\t->Press 2 to display current Anti-Lag state" << std::endl;
    std::cout << "\t->Press 3 to enable Anti-Lag" << std::endl;
    std::cout << "\t->Press 4 to disable Anti-Lag" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DAntiLagPtr& d3dAntiLag)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Anti-Lag support
        case '1':
            ShowAntiLagSupport(d3dAntiLag);
            break;

            // Display current Anti-Lag state
        case '2':
            GetAntiLagState(d3dAntiLag);
            break;

            // Set Anti-Lag state
        case '3':
        case '4':
            SetAntiLagState(d3dAntiLag, num - '3');
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
