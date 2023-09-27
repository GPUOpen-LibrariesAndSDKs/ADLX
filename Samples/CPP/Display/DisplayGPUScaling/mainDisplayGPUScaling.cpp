//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayGPUScaling.cpp
/// \brief This document describes how to obtain the display GPUScaling through ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display displayGPUScaling support
void ShowDisplayGPUScalingSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current displayGPUScaling state
void GetGPUScalingState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set displayGPUScaling
void SetGPUScalingState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

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
        // Get display service
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display list
            IADLXDisplayListPtr displayList;
            res = displayService->GetDisplays(&displayList);
            if (ADLX_SUCCEEDED (res))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplayPtr display;
                res = displayList->At(it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and parse the selection
                    MenuControl(displayService, display);
                }
            }
            else
            {
                std::cout << "Failed to get the display list" << std::endl;
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX result: " << res << std::endl;
            return WaitAndExit("Failed to get the display services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the print out
    system("Pause");

    return 0;
}

void ShowDisplayGPUScalingSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayGPUScalingPtr displayGPUScaling;
    ADLX_RESULT res = displayService->GetGPUScaling(display, &displayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get GPUScaling Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayGPUScaling->IsSupported(&supported);
        std::cout << "\tIsSupported, result: " << res << " supported: " << (supported ? "true" : "false") << std::endl;
    }
}

void GetGPUScalingState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayGPUScalingPtr displayGPUScaling;
    ADLX_RESULT res = displayService->GetGPUScaling(display, &displayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get GPUScaling Enabled ===" << std::endl;
        adlx_bool enabled = false;
        res = displayGPUScaling->IsEnabled(&enabled);
        std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
    }
}

void SetGPUScalingState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayGPUScalingPtr displayGPUScaling;
    ADLX_RESULT res = displayService->GetGPUScaling(display, &displayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set GPUScaling disabled
        case 0:
            std::cout << "  === Set GPUScaling enabled: false" << std::endl;
            res = displayGPUScaling->SetEnabled(false);
            break;
            // Set GPUScaling enabled
        case 1:
            std::cout << "  === Set GPUScaling enabled: true" << std::endl;
            res = displayGPUScaling->SetEnabled(true);
            break;
        default:
            break;
        }
        std::cout << "\tReturn code is: " << res <<" (0 means success)" << std::endl;
    }
}

void MainMenu()
{
    std::cout << "\tChoose from following options" << std::endl;

    std::cout << "\t->Press 1 to display GPUScaling support" << std::endl;

    std::cout << "\t->Press 2 to get GPUScaling state" << std::endl;

    std::cout << "\t->Press 3 to set current GPUScaling to disabled" << std::endl;
    std::cout << "\t->Press 4 to set current GPUScaling to enabled" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Show displayGPUScaling support
        case '1':
            ShowDisplayGPUScalingSupport(displayService, display);
            break;

            // Display current displayGPUScaling state
        case '2':
            GetGPUScalingState(displayService, display);
            break;

            // Set displayGPUScaling
        case '3':
        case '4':
            SetGPUScalingState(displayService, display, num - '3');
            break;

            // Display main menu options
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

    system("Pause");
    return retCode;
}