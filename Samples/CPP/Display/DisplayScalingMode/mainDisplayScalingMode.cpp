//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayScalingMode.cpp
/// \brief Demonstrates how to obtain scaling mode when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display displayScalingMode support
void ShowDisplayScalingModeSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current displayScalingMode state
void GetScalingModeState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set displayScalingMode
void SetScalingModeState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

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
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("Failed to get the display services", 0);
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
    system("Pause");

    return 0;
}

void ShowDisplayScalingModeSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayScalingModePtr displayScalingMode;
    ADLX_RESULT res = displayService->GetScalingMode(display, &displayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get ScalingMode Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayScalingMode->IsSupported(&supported);
        std::cout << "\tIsSupported, result: " << res << " supported: " << (supported ? "true" : "false") << std::endl;
    }
}

void GetScalingModeState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    const std::unordered_map<int, std::string> scalingModeMap =
        {
            {0, "PRESERVE_ASPECT_RATIO"},
            {1, "FULL_PANEL"},
            {2, "CENTERED"}};

    IADLXDisplayScalingModePtr displayScalingMode;
    ADLX_RESULT res = displayService->GetScalingMode(display, &displayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get ScalingMode Enabled ===" << std::endl;
        ADLX_SCALE_MODE sm = PRESERVE_ASPECT_RATIO;
        res = displayScalingMode->GetMode(&sm);
        std::string smStr = "Unknown";
        auto searchIter = scalingModeMap.find(sm);
        if (searchIter != scalingModeMap.end())
        {
            smStr = searchIter->second;
        }
        std::cout << "\tGetMode, result " << res << " mode: " << smStr.c_str() << std::endl;
    }
}

void SetScalingModeState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayScalingModePtr displayScalingMode;
    ADLX_RESULT res = displayService->GetScalingMode(display, &displayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set scaling mode to PRESERVE_ASPECT_RATIO
        case 0:
            std::cout << "  === Set ScalingMode PRESERVE_ASPECT_RATIO" << std::endl;
            res = displayScalingMode->SetMode(PRESERVE_ASPECT_RATIO);
            break;
            // Set scaling mode to FULL_PANEL
        case 1:
            std::cout << "  === Set ScalingMode FULL_PANEL" << std::endl;
            res = displayScalingMode->SetMode(FULL_PANEL);
            break;
            // Set scaling mode to CENTERED
        case 2:
            std::cout << "  === Set ScalingMode CENTERED" << std::endl;
            res = displayScalingMode->SetMode(CENTERED);
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

    std::cout << "\t->Press 1 to display scaling mode support" << std::endl;

    std::cout << "\t->Press 2 to get scaling mode state" << std::endl;

    std::cout << "\t->Press 3 to set current scaling mode to PRESERVE_ASPECT_RATIO" << std::endl;
    std::cout << "\t->Press 4 to set current scaling mode to FULL_PANEL" << std::endl;
    std::cout << "\t->Press 5 to set current scaling mode to CENTERED" << std::endl;

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
            // Display displayScalingMode support
        case '1':
            ShowDisplayScalingModeSupport(displayService, display);
            break;

            // Display current displayScalingMode state
        case '2':
            GetScalingModeState(displayService, display);
            break;

            // Set displayScalingMode
        case '3':
        case '4':
        case '5':
            SetScalingModeState(displayService, display, num - '3');
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