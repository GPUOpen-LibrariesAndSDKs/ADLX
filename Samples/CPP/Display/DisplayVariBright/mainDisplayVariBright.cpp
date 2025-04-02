//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
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

// Display supported status, enabled state and set state for Backlight Adaptive Vari-Bright Scaling mode
void BacklightAdaptiveFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1);

// Display supported status, enabled state and set state for Battery Life Vari-Bright Scaling mode
void BatteryLifeFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1);

// Display supported status, enabled state and set state for Windows Power Mode Vari-Bright Scaling mode
void WindowsPowerModeFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1);

// Display supported status, enabled state and set state for Full-Screen Video Vari-Bright Scaling mode
void FullScreenVideoFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1);

// Main menu
void MainMenu();

// Vari-Bright Scaling menu action control
void VariBrightScalingMenuControl(const IADLXDisplayVariBright1Ptr& displayVariBright1, int userChoice);

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

void BacklightAdaptiveFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->IsBacklightAdaptiveSupported(&supported);
            std::cout << "\t\tBacklight Adaptive Vari-Bright Scaling mode is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '2':
            res = displayVariBright1->IsBacklightAdaptiveEnabled(&enabled);
            std::cout << "\t\tBacklight Adaptive Vari-Bright Scaling mode is enabled on the display: " << (enabled ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '3':
            res = displayVariBright1->SetBacklightAdaptiveEnabled(true);
            std::cout << "\t\tSet Backlight Adaptive Vari-Bright Scaling mode enabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        case '4':
            res = displayVariBright1->SetBacklightAdaptiveEnabled(false);
            std::cout << "\t\tSet Backlight Adaptive Vari-Bright Scaling mode disabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Battery Life Vari-Bright Scaling mode
void BatteryLifeFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->IsBatteryLifeSupported(&supported);
            std::cout << "\t\tBattery Life Vari-Bright Scaling mode is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '2':
            res = displayVariBright1->IsBatteryLifeEnabled(&enabled);
            std::cout << "\t\tBattery Life Vari-Bright Scaling mode is enabled on the display: " << (enabled ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '3':
            res = displayVariBright1->SetBatteryLifeEnabled(true);
            std::cout << "\t\tSet Battery Life Vari-Bright Scaling mode enabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        case '4':
            res = displayVariBright1->SetBatteryLifeEnabled(false);
            std::cout << "\t\tSet Battery Life Vari-Bright Scaling mode disabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Windows Power Mode Vari-Bright Scaling mode
void WindowsPowerModeFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->IsWindowsPowerModeSupported(&supported);
            std::cout << "\t\tWindows Power Mode Vari-Bright Scaling mode is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '2':
            res = displayVariBright1->IsWindowsPowerModeEnabled(&enabled);
            std::cout << "\t\tWindows Power Mode Vari-Bright Scaling mode is enabled on the display: " << (enabled ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '3':
            res = displayVariBright1->SetWindowsPowerModeEnabled(true);
            std::cout << "\t\tSet Windows Power Mode Vari-Bright Scaling mode enabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        case '4':
            res = displayVariBright1->SetWindowsPowerModeEnabled(false);
            std::cout << "\t\tSet Windows Power Mode Vari-Bright Scaling mode disabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Full-Screen Video Vari-Bright Scaling mode
void FullScreenVideoFunctionality(const IADLXDisplayVariBright1Ptr& displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->IsFullScreenVideoSupported(&supported);
            std::cout << "\t\tFull-Screen Video Vari-Bright Scaling mode is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '2':
            res = displayVariBright1->IsFullScreenVideoEnabled(&enabled);
            std::cout << "\t\tFull-Screen Video Vari-Bright Scaling mode is enabled on the display: " << (enabled ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
            break;
        case '3':
            res = displayVariBright1->SetFullScreenVideoEnabled(true);
            std::cout << "\t\tSet Full-Screen Video Vari-Bright Scaling mode enabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        case '4':
            res = displayVariBright1->SetFullScreenVideoEnabled(false);
            std::cout << "\t\tSet Full-Screen Video Vari-Bright Scaling mode disabled " << (ADLX_SUCCEEDED(res) ? "successfully" : "failed") << std::endl;
            break;
        default:
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
    // Vari-Bright Scaling
    std::cout << "\t->Press f to use Backlight Adaptive Vari-Bright Scaling mode functionality on a display" << std::endl;
    std::cout << "\t->Press g to use Battery Life Vari-Bright Scaling mode functionality on a display" << std::endl;
    std::cout << "\t->Press h to use Windows Power Mode Vari-Bright Scaling mode functionality on a display" << std::endl;
    std::cout << "\t->Press i to use Full-Screen Video Vari-Bright Scaling mode functionality on a display" << std::endl;

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

        case 'f':
        case 'g':
        case 'h':
        case 'i':
        {
            IADLXDisplayVariBrightPtr displayVariBright;
            ADLX_RESULT res = displayService->GetVariBright(display, &displayVariBright);
            if (ADLX_SUCCEEDED(res))
            {
                IADLXDisplayVariBright1Ptr displayVariBright1;
                ADLX_RESULT res = displayVariBright->QueryInterface(IADLXDisplayVariBright1::IID(), reinterpret_cast<void**>(&displayVariBright1));
                if (ADLX_SUCCEEDED(res))
                {
                    VariBrightScalingMenuControl(displayVariBright1, num - 'f');
                }
                else
                    std::cout << "Failed to get the Vari-Bright Scaling" << std::endl;
            }
            else
                std::cout << "Failed to get the Vari-Bright" << std::endl;
            break;
        }

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

// Vari-Bright Scaling menu action control
void VariBrightScalingMenuControl(const IADLXDisplayVariBright1Ptr& displayVariBright1, int userChoice)
{
    switch (userChoice)
    {
    case 0:
        std::cout << "\t\t->Press 1 to check if Backlight Adaptive Vari-Bright Scaling mode is supported on a display" << std::endl;
        std::cout << "\t\t->Press 2 to check if Backlight Adaptive Vari-Bright Scaling mode is enabled on a display" << std::endl;
        std::cout << "\t\t->Press 3 to set Backlight Adaptive Vari-Bright Scaling mode enabled on a display" << std::endl;
        std::cout << "\t\t->Press 4 to set Backlight Adaptive Vari-Bright Scaling mode disabled on a display" << std::endl;
        std::cout << "\t\t->Press Q/q to go back to the previous menu" << std::endl;
        BacklightAdaptiveFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 1:
        std::cout << "\t\t->Press 1 to check if Battery Life Vari-Bright Scaling mode is supported on a display" << std::endl;
        std::cout << "\t\t->Press 2 to check if Battery Life Vari-Bright Scaling mode is enabled on a display" << std::endl;
        std::cout << "\t\t->Press 3 to set Battery Life Vari-Bright Scaling mode enabled on a display" << std::endl;
        std::cout << "\t\t->Press 4 to set Battery Life Vari-Bright Scaling mode disabled on a display" << std::endl;
        std::cout << "\t\t->Press Q/q to go back to the previous menu" << std::endl;
        BatteryLifeFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 2:
        std::cout << "\t\t->Press 1 to check if Windows Power Mode Vari-Bright Scaling mode is supported on a display" << std::endl;
        std::cout << "\t\t->Press 2 to check if Windows Power Mode Vari-Bright Scaling mode is enabled on a display" << std::endl;
        std::cout << "\t\t->Press 3 to set Windows Power Mode Vari-Bright Scaling mode enabled on a display" << std::endl;
        std::cout << "\t\t->Press 4 to set Windows Power Mode Vari-Bright Scaling mode disabled on a display" << std::endl;
        std::cout << "\t\t->Press Q/q to go back to the previous menu" << std::endl;
        WindowsPowerModeFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 3:
        std::cout << "\t\t->Press 1 to check if Full-Screen Video Vari-Bright Scaling mode is supported on a display" << std::endl;
        std::cout << "\t\t->Press 2 to check if Full-Screen Video Vari-Bright Scaling mode is enabled on a display" << std::endl;
        std::cout << "\t\t->Press 3 to set Full-Screen Video Vari-Bright Scaling mode enabled on a display" << std::endl;
        std::cout << "\t\t->Press 4 to set Full-Screen Video Vari-Bright Scaling mode disabled on a display" << std::endl;
        std::cout << "\t\t->Press Q/q to go back to the previous menu" << std::endl;
        FullScreenVideoFunctionality(displayVariBright1);
        MainMenu();
        break;

    default:
        break;
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