//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayVariBright.cpp
/// \brief Demonstrates how to obtain Vari-Bright when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display displayVariBright support
void ShowDisplayVariBrightSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current displayVariBright state
void GetVariBrightEnabled(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set displayVariBright enable/disable
void SetVariBrightEnabled (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, adlx_bool enableDisable);

// Get displayVariBright current state
void GetCurrentVariBright (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, int userChoice);

// Get displayVariBright current state
void SetCurrentVariBright (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, int userChoice);

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
            if (ADLX_SUCCEEDED(res))
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
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the print out
    system("Pause");

    return 0;
}

void ShowDisplayVariBrightSupport (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayVariBrightPtr displayVariBright;
    ADLX_RESULT res = displayService->GetVariBright (display, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        std::cout << "  === Get VariBright Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayVariBright->IsSupported (&supported);
        std::cout << "\tVari-Bright is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
    }
}

void GetVariBrightEnabled (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayVariBrightPtr displayVariBright;
    ADLX_RESULT res = displayService->GetVariBright (display, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        std::cout << "  === Get VariBright enabled ===" << std::endl;
        adlx_bool enabled = false;
        res = displayVariBright->IsEnabled (&enabled);
        std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
    }
}

void SetVariBrightEnabled (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, adlx_bool enableDisable)
{
    IADLXDisplayVariBrightPtr displayVariBright;
    ADLX_RESULT res = displayService->GetVariBright (display, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        if (!enableDisable)
        {
            res = displayVariBright->SetEnabled (false);
            std::cout << "\tSet enabled to false, result: " << res << std::endl;
        }
        else
        {
            res = displayVariBright->SetEnabled (true);
            std::cout << "\tSet enabled to true, result: " << res << std::endl;
        }
    }
}

void GetCurrentVariBright (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, int userChoice)
{
    IADLXDisplayVariBrightPtr displayVariBright;
    ADLX_RESULT res = displayService->GetVariBright (display, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        adlx_bool applied = false;
        switch (userChoice)
        {
        case 0:
            res = displayVariBright->IsCurrentMaximizeBrightness (&applied);
            std::cout << "\tMaximize Brightness preset is used on the display: " << (applied ? "Yes" : "No") << ", return code: " << res << " (0 means success)" << std::endl;
            break;

        case 1:
            res = displayVariBright->IsCurrentOptimizeBrightness (&applied);
            std::cout << "\t Optimize Brightness preset is used on the display: " << (applied ? "Yes" : "No") << ", return code: " << res << " (0 means success)" << std::endl;
            break;

        case 2:
            res = displayVariBright->IsCurrentBalanced (&applied);
            std::cout << "\t Balanced preset is used on the display: " << (applied ? "Yes" : "No") << ", return code: " << res << " (0 means success)" << std::endl;
            break;

        case 3:
            res = displayVariBright->IsCurrentOptimizeBattery (&applied);
            std::cout << "\t Optimize Battery preset is used on the display: " << (applied ? "Yes" : "No") << ", return code: " << res << " (0 means success)" << std::endl;
            break;

        case 4:
            res = displayVariBright->IsCurrentMaximizeBattery (&applied);
            std::cout << "\t Maximize Battery preset is used on the display: " << (applied ? "Yes" : "No") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        }
    }
}

void SetCurrentVariBright (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, int userChoice)
{
    IADLXDisplayVariBrightPtr displayVariBright;
    ADLX_RESULT res = displayService->GetVariBright (display, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        switch (userChoice)
        {
            case 0:
                res = displayVariBright->SetMaximizeBrightness ();
                std::cout << "\t Set Maximize Brightness , result: " << res << std::endl;
            break;

            case 1:
                res = displayVariBright->SetOptimizeBrightness ();
                std::cout << "\t Set Optimize Brightness, result: " << res << std::endl;
            break;

            case 2:
                res = displayVariBright->SetBalanced ();
                std::cout << "\t Set Balanced, result: " << res << std::endl;
            break;
            case 3:
                res = displayVariBright->SetOptimizeBattery ();
                std::cout << "\t Set Optimize Battery, result: " << res << std::endl;
            break;

            case 4:
                res = displayVariBright->SetMaximizeBattery ();
                std::cout << "\t Set Maximize Battery, result: " << res << std::endl;
            break;
        }
    }
}

void MainMenu()
{
    std::cout << "\tChoose from following options" << std::endl;

    std::cout << "\t->Press 1 to display VariBright support" << std::endl;
    std::cout << "\t->Press 2 to get VariBright enable state" << std::endl;
    std::cout << "\t->Press 3 to set VariBright enable" << std::endl;
    std::cout << "\t->Press 4 to set VariBright disable" << std::endl;
    std::cout << "\t->Press 5 to check if Vari-Bright mode is Maximized Brightness preset on a display" << std::endl;
    std::cout << "\t->Press 6 to check if Vari-Bright mode is Optimized Brightness preset on a display" << std::endl;
    std::cout << "\t->Press 7 to check if Vari-Bright mode is Balanced preset on a display" << std::endl;
    std::cout << "\t->Press 8 to check if Vari-Bright mode is Optimized Battery preset on a display" << std::endl;
    std::cout << "\t->Press 9 to check if Vari-Bright mode is Maximized Battery preset on a display" << std::endl;
    std::cout << "\t->Press a to set the Vari-Bright mode to Maximized Brightness preset on a display" << std::endl;
    std::cout << "\t->Press b to set the Vari-Bright mode to Optimized Brightness preset on a display" << std::endl;
    std::cout << "\t->Press c to set the Vari-Bright mode to Balanced preset on a display" << std::endl;
    std::cout << "\t->Press d to set the Vari-Bright mode to Optimized Battery preset on a display" << std::endl;
    std::cout << "\t->Press e to set the Vari-Bright mode to Maximized Battery preset on a display" << std::endl;

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
            // Display displayVariBright support
        case '1':
            ShowDisplayVariBrightSupport (displayService, display);
            break;

            // Display current displayVariBright state
        case '2':
            GetVariBrightEnabled (displayService, display);
            break;

            // Set displayVariBright enable
        case '3':
            SetVariBrightEnabled (displayService, display, true);
            break;

            // Set displayVariBright enable
        case '4':
            SetVariBrightEnabled (displayService, display, false);
            break;

        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            GetCurrentVariBright (displayService, display, num - '5');
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
            SetCurrentVariBright (displayService, display, num - 'a');
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