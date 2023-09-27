//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayColorDepth.cpp
/// \brief Demonstrates how to obtain the Color Depth of a display when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface. 
static ADLXHelper g_ADLXHelp;

// Display DisplayColorDepthSupport
void ShowDisplayColorDepthSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current display color depth state
void GetColorDepthState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set display color depth
void SetColorDepthState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

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
            return WaitAndExit("Failed to get display services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the printout
    system("Pause");

    return 0;
}

void ShowDisplayColorDepthSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayColorDepthPtr displayColorDepth;
    ADLX_RESULT res = displayService->GetColorDepth(display, &displayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get color depth supported status ===" << std::endl;
        adlx_bool supported = false;
        res = displayColorDepth->IsSupported(&supported);
        std::cout << "\tIsSupported, res " << res << ", supported: " << supported << std::endl;
    }
}
void GetSupportStateForEachColorDepth (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayColorDepthPtr displayColorDepth;
    ADLX_RESULT res = displayService->GetColorDepth(display, &displayColorDepth);
    if (ADLX_SUCCEEDED (res) && displayColorDepth)
    {
        std::cout << "  === Get color depth support list ===" << std::endl;
        adlx_bool isSupported = false;
        res = displayColorDepth->IsSupportedBPC_6 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_6, result " << res << " BPC_6 support: " << isSupported << std::endl;
        res = displayColorDepth->IsSupportedBPC_8 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_6, result " << res << " BPC_8 support: " << isSupported << std::endl;
        res = displayColorDepth->IsSupportedBPC_10 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_10, result " << res << " BPC_10 support: " << isSupported << std::endl;
        res = displayColorDepth->IsSupportedBPC_12 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_12, result " << res << " BPC_12 support: " << isSupported << std::endl;
        res = displayColorDepth->IsSupportedBPC_14 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_14, result " << res << " BPC_14 support: " << isSupported << std::endl;
        res = displayColorDepth->IsSupportedBPC_16 (&isSupported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedBPC_16, result " << res << " BPC_16 support: " << isSupported << std::endl;

        const std::unordered_map<ADLX_COLOR_DEPTH, std::string> colorDepthMap{
            {BPC_6, "BPC_6"},
            {BPC_8, "BPC_8"},
            {BPC_10, "BPC_10"},
            {BPC_12, "BPC_12"},
            {BPC_14, "BPC_14"},
            {BPC_16, "BPC_16"}
        };
        for_each (colorDepthMap.begin (), colorDepthMap.end (), [&](auto colorDepth) {
            res = displayColorDepth->IsSupportedColorDepth (colorDepth.first, &isSupported);
            std::cout << "\tIsSupported" << colorDepth.second << ": " << isSupported << std::endl;
        });
    }
}

void GetColorDepthState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    const std::unordered_map<int, std::string> colorDepthMap = {{0, "BPC_UNKNOWN"}, {1, "BPC_6"}, {2, "BPC_8"}, {3, "BPC_10"}};
    IADLXDisplayColorDepthPtr displayColorDepth;
    ADLX_RESULT res = displayService->GetColorDepth(display, &displayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get color depth enabled status ===" << std::endl;
        ADLX_COLOR_DEPTH cd = BPC_UNKNOWN;
        res = displayColorDepth->GetValue(&cd);
        std::string cdStr = "BPC_Unknown";
        auto searchIter = colorDepthMap.find(cd);
        if (searchIter != colorDepthMap.end())
        {
            cdStr = searchIter->second;
        }
        std::cout << "\tGetValue, result " << res << " color depth: " << cdStr.c_str() << std::endl;
    }
}

void SetColorDepthState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayColorDepthPtr displayColorDepth;
    ADLX_RESULT res = displayService->GetColorDepth(display, &displayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Set color depth ===" << std::endl;
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // set ColorDepth BPC_6
        case 0:
            res = displayColorDepth->SetValue(BPC_6);
            break;
            // set ColorDepth BPC_8
        case 1:
            res = displayColorDepth->SetValue(BPC_8);
            break;
            // set ColorDepth BPC_10
        case 2:
            res = displayColorDepth->SetValue(BPC_10);
            break;
        default:
            break;
        }
        std::cout << "\tReturn code is: " << res <<"(0 means success)" << std::endl;
    }
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display color depth support" << std::endl;

    std::cout << "\t->Press 2 to get color depth state" << std::endl;

    std::cout << "\t->Press 3 to set current color depth to BPC_6" << std::endl;
    std::cout << "\t->Press 4 to set current color depth to BPC_8" << std::endl;
    std::cout << "\t->Press 5 to set current color depth to BPC_10" << std::endl;

    std::cout << "\t->Press 6 to get support state for each color depth" << std::endl;

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
            // Display DisplayColorDepthSupport
        case '1':
            ShowDisplayColorDepthSupport(displayService, display);
            break;

            // Display current display color depth state
        case '2':
            GetColorDepthState(displayService, display);
            break;

            // Set display color depth
        case '3':
        case '4':
        case '5':
            SetColorDepthState(displayService, display, num - '3');
            break;

        case '6':
            GetSupportStateForEachColorDepth(displayService, display);
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
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("Pause");
    return retCode;
}