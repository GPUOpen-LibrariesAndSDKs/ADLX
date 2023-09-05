//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainWaitForVerticalRefresh.cpp
/// \brief Demonstrates how to access VSync options, and perform related testing when programming with ADLX.

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

// Display VSync support
void ShowvsyncSupport(const IADLX3DWaitForVerticalRefreshPtr& vsync);

// Get current VSync state
void GetvsyncState(const IADLX3DWaitForVerticalRefreshPtr& vsync);

// Set VSync mode
void SetvsyncMode(const IADLX3DWaitForVerticalRefreshPtr& vsync, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DWaitForVerticalRefreshPtr& vsync);

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

            // Get VSync interface
            IADLX3DWaitForVerticalRefreshPtr vsync;
            res = d3dSettingSrv->GetWaitForVerticalRefresh(gpuInfo, &vsync);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(vsync);
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

static const std::map<ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, const char*> vsyncMode =
    {
        {WFVR_ALWAYS_OFF, "Always off"},
        {WFVR_OFF_UNLESS_APP_SPECIFIES, "Off (unless specified by the application)"},
        {WFVR_ON_UNLESS_APP_SPECIFIES, "On (unless specified by the application)"},
        {WFVR_ALWAYS_ON, "Always on"}};

void ShowvsyncSupport(const IADLX3DWaitForVerticalRefreshPtr& vsync)
{
    adlx_bool supported = false;
    ADLX_RESULT res = vsync->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

void GetvsyncState(const IADLX3DWaitForVerticalRefreshPtr& vsync)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = vsync->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << ", return code is: " << res << "(0 means success)" << std::endl;
    ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode = WFVR_ALWAYS_OFF;
    res = vsync->GetMode(&mode);
    std::cout << "\tMode: " << vsyncMode.find(mode)->second << ", return code is: " << res << "(0 means success)" << std::endl;
}

void SetvsyncMode(const IADLX3DWaitForVerticalRefreshPtr& vsync, int index)
{
    ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode = WFVR_ALWAYS_OFF;
    mode = (ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)(mode + index);
    ADLX_RESULT res = vsync->SetMode(mode);
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

    std::cout << "\t->Press 1 to display VSync support" << std::endl;
    std::cout << "\t->Press 2 to get current VSync state" << std::endl;
    std::cout << "\t->Press 3 to set VSync to Always Off" << std::endl;
    std::cout << "\t->Press 4 to set VSync to Off (unless specified by the application)" << std::endl;
    std::cout << "\t->Press 5 to set VSync to On (unless specified by the application)" << std::endl;
    std::cout << "\t->Press 6 to set VSync to Always On" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DWaitForVerticalRefreshPtr& vsync)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display VSync support
        case '1':
            ShowvsyncSupport(vsync);
            break;

            // Get and display current VSync state
        case '2':
            GetvsyncState(vsync);
            break;

            // Set VSync model
        case '3':
        case '4':
        case '5':
        case '6':
            SetvsyncMode(vsync, num - '3');
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
