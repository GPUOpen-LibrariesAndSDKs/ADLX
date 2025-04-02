//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayGamut.cpp
/// \brief Demonstrates how to obtain the display Gamut when programming with ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed. 
// Use global variables to ensure validity of the interface. 
static ADLXHelper g_ADLXHelp;

// Show display gamut support
void ShowDisplayGamutSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Get and display gamut information, it contains white point and color space
void GetCurrentGamutInfo(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set gamut(white point and color space)
void SetGamut(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

// main menu
void MainMenu();

// menu action control
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
                    // Show a menu with options to chose from
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(displayService, display);
                }
            }
            else
            {
                std::cout << "Failed to get the Displays list" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get the Display Services" << std::endl;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause for user see the print out
    system("pause");

    return 0;
}

// Show display Gamut support
void ShowDisplayGamutSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get displayGamut
    IADLXDisplayGamutPtr displayGamut;
    ADLX_RESULT res = displayService->GetGamut(display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool supported = false;
        std::cout << "  === Gamut Space supported status ===" << std::endl;
        res = displayGamut->IsSupportedCCIR709ColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedGamut_CCIR_709: " << supported << std::endl;
        res = displayGamut->IsSupportedCCIR601ColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedGamut_CCIR_601: " << supported << std::endl;
        res = displayGamut->IsSupportedAdobeRgbColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedGamut_Adobe_RGB: " << supported << std::endl;
        res = displayGamut->IsSupportedCIERgbColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedGamut_CIE_RGB: " << supported << std::endl;
        res = displayGamut->IsSupportedCCIR2020ColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedCCIR2020ColorSpace: " << supported << std::endl;
        res = displayGamut->IsSupportedCustomColorSpace(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedGamut_Custom: " << supported << std::endl;

        std::cout << "  === White point supported status ===" << std::endl;
        res = displayGamut->IsSupported5000kWhitePoint(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedWhitePoint_5000k: " << supported << std::endl;
        res = displayGamut->IsSupported6500kWhitePoint(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedWhitePoint_6500k: " << supported << std::endl;
        res = displayGamut->IsSupported7500kWhitePoint(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedWhitePoint_7500k: " << supported << std::endl;
        res = displayGamut->IsSupported9300kWhitePoint(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedWhitePoint_9300k: " << supported << std::endl;
        res = displayGamut->IsSupportedCustomWhitePoint(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedWhitePoint_Custom: " << supported << std::endl;
    }
}

// Get and show Gamut information, it contains white point and color space
void GetCurrentGamutInfo(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get displayGamut
    IADLXDisplayGamutPtr displayGamut;
    ADLX_RESULT res = displayService->GetGamut(display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool applied = false;
        ADLX_RESULT res = ADLX_FAIL;
        std::cout << "  === Currnt White point status ===" << std::endl;
        res = displayGamut->IsCurrent5000kWhitePoint(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentWhitePoint_5000k: " << applied << std::endl;
        res = displayGamut->IsCurrent6500kWhitePoint(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentWhitePoint_6500k: " << applied << std::endl;
        res = displayGamut->IsCurrent7500kWhitePoint(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentWhitePoint_7500k: " << applied << std::endl;
        res = displayGamut->IsCurrent9300kWhitePoint(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentWhitePoint_9300k: " << applied << std::endl;
        res = displayGamut->IsCurrentCustomWhitePoint(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentWhitePoint_Custom: " << applied << std::endl;
        ADLX_Point point = {0};
        res = displayGamut->GetWhitePoint(&point);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tGetWhitePoint: ( " << point.x << ", " << point.y << " )" << std::endl;

        std::cout << "  === Currnt gamut space status ===" << std::endl;
        res = displayGamut->IsCurrentCCIR709ColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentGamut_CCIR_709: " << applied << std::endl;
        res = displayGamut->IsCurrentCCIR601ColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentGamut_CCIR_601: " << applied << std::endl;
        res = displayGamut->IsCurrentAdobeRgbColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentGamut_Adobe_RGB: " << applied << std::endl;
        res = displayGamut->IsCurrentCIERgbColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentGamut_CIE_RGB: " << applied << std::endl;
        res = displayGamut->IsCurrentCCIR2020ColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentCCIR2020ColorSpace: " << applied << std::endl;
        res = displayGamut->IsCurrentCustomColorSpace(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentCustomColorSpace: " << applied << std::endl;
        ADLX_GamutColorSpace gamutCoordinates = {0};
        res = displayGamut->GetGamutColorSpace(&gamutCoordinates);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tGetGamutColorSpace: R( " << gamutCoordinates.red.x << ", " << gamutCoordinates.red.y << " ) "
                      << "G(" << gamutCoordinates.green.x << ", " << gamutCoordinates.green.y << ") "
                      << "B(" << gamutCoordinates.blue.x << ", " << gamutCoordinates.blue.y << ") " << std::endl;
    }
}

// Set Gamut(white point and color space)
void SetGamut(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    std::cout << "  === Set white point and gamut space ===" << std::endl;

    ADLX_RESULT res = ADLX_FAIL;
    ADLX_WHITE_POINT predefinedWhitePoint = WHITE_POINT_6500K;
    ADLX_GAMUT_SPACE predefinedGamutSpace = GAMUT_SPACE_ADOBE_RGB;
    ADLX_RGB customWhitePoint = {0.654108, 0.767112, 1};
    ADLX_GamutColorSpace customGamutSpace =
    {
        {6400, 3300}, {3000, 6000}, {1500, 600}
    };

    // Get displayGamut
    IADLXDisplayGamutPtr displayGamut;
    res = displayService->GetGamut(display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {
        switch (key)
        {
        case 0:
            res = displayGamut->SetGamut(predefinedWhitePoint, predefinedGamutSpace);
            break;
        case 1:
            res = displayGamut->SetGamut(customWhitePoint, predefinedGamutSpace);
            break;
        case 2:
            res = displayGamut->SetGamut(predefinedWhitePoint, customGamutSpace);
            break;
        case 3:
            res = displayGamut->SetGamut(customWhitePoint, customGamutSpace);
            break;

        default:
            break;
        }
        std::cout << "\treturn code(0 is Success) is: " << res << std::endl;
    }
}

// main menu
void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to show Gamut support" << std::endl;

    std::cout << "\t->Press 2 to get current display Gamut info" << std::endl;

    std::cout << "\t->Press 3 to set predefined white point and predefined Gamut space" << std::endl;
    std::cout << "\t->Press 4 to set custom white point and predefined Gamut space" << std::endl;
    std::cout << "\t->Press 5 to set predefined white point and custom Gamut space" << std::endl;
    std::cout << "\t->Press 6 to set custom white point and custom Gamut space" << std::endl;

    std::cout << "\t->Press Q/q to quit" << std::endl;
    std::cout << "\t->Press M/m to show the options again" << std::endl;
}

// menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Show display Gamut support
        case '1':
            ShowDisplayGamutSupport(displayService, display);
            break;

        // Get Gamut information(white point and color space)
        case '2':
            GetCurrentGamutInfo(displayService, display);
            break;

        // Set Gamut(white point and color space)
        case '3':
        case '4':
        case '5':
        case '6':
            SetGamut(displayService, display, num - '3');
            break;

        // Show options again
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
    // Printout the message and pause for user to see it then return the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}