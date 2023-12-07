//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPrimaryAdapter.cpp
/// \brief Demonstrates how to get the primary adapter when programming with ADLX.

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

// Display the primary adapter
void ShowPrimaryAdapter();

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

    std::cout << "\t->Press 1 to display the Primary Adapter" << std::endl;

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
            // Display the Primary Adapter
        case '1':
            ShowPrimaryAdapter();
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

// Display how to get primary adapter
void ShowPrimaryAdapter()
{
    IADLXDesktopServicesPtr desktopSrv;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetDesktopsServices(&desktopSrv);
    if (ADLX_FAILED(res))
    {
        std::cout << "\tFailed to get the Desktop Services interface" << std::endl;
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
        ADLX_Point point = { 0 };
        res = desktop->TopLeft (&point);
        if (ADLX_SUCCEEDED(res) && 0 == point.x && 0 == point.y)
        {
            IADLXDisplayListPtr displays;
            res = desktop->GetDisplays(&displays);
            if (ADLX_FAILED(res))
            {
                std::cout << "\tFailed to get the Display List interface" << std::endl;
                return;
            }
            IADLXDisplayPtr display;
            res = displays->At(0, &display);
            if (ADLX_FAILED(res))
            {
                std::cout << "\tFailed to get the first display" << std::endl;
                return;
            }
            IADLXGPUPtr gpu;
            res = display->GetGPU (&gpu);
            if (ADLX_FAILED(res))
            {
                std::cout << "\tFailed to get the GPU" << std::endl;
                return;
            }
            const char* gpuName;
            gpu->Name (&gpuName);
            std::cout << "\tPrimary Adapter: " << gpuName << std::endl;
            break;
        }
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