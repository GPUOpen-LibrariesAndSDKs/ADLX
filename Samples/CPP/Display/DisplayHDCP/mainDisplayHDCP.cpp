//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayHDCP.cpp
/// \brief Demonstrates how to obtain the display HDCP when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// so we use global variables to ensure the valid of the interface.
static ADLXHelper g_ADLXHelp;

// Display display HDCP support
void ShowDisplayHDCPSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current display HDCP state
void GetHDCPState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set display HDCP
void SetHDCPState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

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
            std::cout << "Destroy ADLX result: " << res << std::endl;
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

void ShowDisplayHDCPSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayHDCPPtr displayHDCP;
    ADLX_RESULT res = displayService->GetHDCP(display, &displayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get HDCP Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayHDCP->IsSupported(&supported);
        std::cout << "\tIsSupported, result: " << res << " supported: " << (supported ? "true" : "false") << std::endl;
    }
}

void GetHDCPState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayHDCPPtr displayHDCP;
    ADLX_RESULT res = displayService->GetHDCP(display, &displayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get HDCP Enabled ===" << std::endl;
        adlx_bool enabled = false;
        res = displayHDCP->IsEnabled(&enabled);
        std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
    }
}

void SetHDCPState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayHDCPPtr displayHDCP;
    ADLX_RESULT res = displayService->GetHDCP(display, &displayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set HDCP disabled
        case 0:
            std::cout << "  === Set HDCP Enabled: false" << std::endl;
            res = displayHDCP->SetEnabled(false);
            break;
            // Set HDCP enabled
        case 1:
            std::cout << "  === Set HDCP Enabled: true" << std::endl;
            res = displayHDCP->SetEnabled(true);
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

    std::cout << "\t->Press 1 to display HDCP support" << std::endl;

    std::cout << "\t->Press 2 to get HDCP state" << std::endl;

    std::cout << "\t->Press 3 to set current HDCP to disabled" << std::endl;
    std::cout << "\t->Press 4 to set current HDCP to enabled" << std::endl;

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
            // Display displayHDCP support
        case '1':
            ShowDisplayHDCPSupport(displayService, display);
            break;

            // Display current displayHDCP state
        case '2':
            GetHDCPState(displayService, display);
            break;

            // Set displayHDCP
        case '3':
        case '4':
            SetHDCPState(displayService, display, num - '3');
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