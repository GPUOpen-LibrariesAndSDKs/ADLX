//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainEyefinity.cpp
/// \brief Demonstrates how to create an AMD Eyefinity desktop when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDesktops.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu();

// Menu action control
void MenuControl();

// Display Eyefinity support
void ShowEyefinitySupport();

// Create an Eyefinity desktop
void CreateEyefinityDesktop();

// Destroy all the Eyefinity desktops
void DestroyAllEyefinityDesktop();

// Destroy the specified Eyefinity desktop
void DestroyGivenEyefinityDesktop();

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
        // Display main menu options
        MainMenu();
        // Get and execute the choice
        MenuControl();
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the printout
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display Eyefinity support" << std::endl;
    std::cout << "\t->Press 2 to create an Eyefinity desktop with all the enabled displays" << std::endl;
    std::cout << "\t->Press 3 to destroy all the Eyefinity desktops" << std::endl;
    std::cout << "\t->Press 4 to destroy the specified Eyefinity desktop" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl()
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Eyefinity support
        case '1':
            ShowEyefinitySupport();
            break;

            // Create an Eyefinity desktop
        case '2':
            CreateEyefinityDesktop();
            break;

            // Destroy all the Eyefinity desktops
        case '3':
            DestroyAllEyefinityDesktop();
            break;

            // Destroy the specified Eyefinity desktop
        case '4':
            DestroyGivenEyefinityDesktop();
            break;

            // Display the options again
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}

// Display Eyefinity support status
void ShowEyefinitySupport()
{
    IADLXDesktopServicesPtr desktopSrv;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopSrv);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop Services interface" << std::endl;
        return;
    }
    IADLXSimpleEyefinityPtr eyefinity;
    res = desktopSrv->GetSimpleEyefinity(&eyefinity);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the simple Eyefinity interface" << std::endl;
        return;
    }
    adlx_bool supported = false;
    res = eyefinity->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIs Eyefinity supported: " << supported << std::endl;
}

// Create an Eyefinity desktop
void CreateEyefinityDesktop()
{
    IADLXDesktopServicesPtr desktopSrv;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopSrv);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop Services interface" << std::endl;
        return;
    }
    IADLXSimpleEyefinityPtr eyefinity;
    res = desktopSrv->GetSimpleEyefinity(&eyefinity);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the simple Eyefinity interface" << std::endl;
        return;
    }
    IADLXEyefinityDesktopPtr eyefinityDesktop;
    res = eyefinity->Create(&eyefinityDesktop);
    std::cout << "\tReturn code is: " << res << " (0 means Success)" << std::endl;
}

// Destroy all the Eyefinity desktops
void DestroyAllEyefinityDesktop()
{
    IADLXDesktopServicesPtr desktopSrv;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopSrv);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop Services interface" << std::endl;
        return;
    }
    IADLXSimpleEyefinityPtr eyefinity;
    res = desktopSrv->GetSimpleEyefinity(&eyefinity);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the simple Eyefinity interface" << std::endl;
        return;
    }
    res = eyefinity->DestroyAll();
    std::cout << "\tReturn code is: " << res << " (0 means Success)" << std::endl;

}

// Destroy the specified Eyefinity desktop
void DestroyGivenEyefinityDesktop()
{
    IADLXDesktopServicesPtr desktopSrv;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopSrv);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop Services interface" << std::endl;
        return;
    }
    IADLXSimpleEyefinityPtr eyefinity;
    res = desktopSrv->GetSimpleEyefinity(&eyefinity);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the simple Eyefinity interface" << std::endl;
        return;
    }
    IADLXDesktopListPtr desktops;
    res = desktopSrv->GetDesktops(&desktops);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop List interface " << std::endl;
        return;
    }
    for (adlx_uint crt = desktops->Begin(); crt != desktops->End(); ++crt)
    {
        IADLXDesktopPtr desktop;
        res = desktops->At(crt, &desktop);
        if (ADLX_FAILED(res))
        {
            std::cout << "\tFailed to get the Desktop interface" << std::endl;
            break;
        }
        IADLXEyefinityDesktopPtr eyefinityDesktop(desktop);
        if (eyefinityDesktop == nullptr)
        {
            std::cout << "\tfailed to get the Eyefinity Desktop interface" << std::endl;
            break;
        }
        res = eyefinity->Destroy(eyefinityDesktop);
        std::cout << "\tReturn code for destroying Desktop " << crt << " is: " << res << " (0 means Success)"<< std::endl;
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}