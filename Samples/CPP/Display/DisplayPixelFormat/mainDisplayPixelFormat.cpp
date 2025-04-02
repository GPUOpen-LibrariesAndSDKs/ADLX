//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayPixelFormat.cpp
/// \brief Demonstrates how to obtain the pixel format when programming with ADLX and perform related operations.

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
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display displayPixelFormat support
void ShowDisplayPixelFormatSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Display current displayPixelFormat state
void GetPixelFormatState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set displayPixelFormat
void SetPixelFormatState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

// Get support state for each pixel format
void GetSupportStateForEachPixelFormat(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

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
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the print out
    system("Pause");

    return 0;
}

void ShowDisplayPixelFormatSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayPixelFormatPtr displayPixelFormat;
    ADLX_RESULT res = displayService->GetPixelFormat(display, &displayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get pixel format supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayPixelFormat->IsSupported(&supported);
        std::cout << "\tPixel format is supported on the display: " << supported << " , return code: " << res << " (0 means success)\n" << std::endl;
    }
}

void GetPixelFormatState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    const std::unordered_map<int, std::string> PixelFormatMap = {{0, "FORMAT_UNKNOWN"}, {1, "RGB_444_FULL"}, {2, "YCBCR_444"}, {3, "YCBCR_422"}, {4, "RGB_444_LIMITED"}};
    IADLXDisplayPixelFormatPtr displayPixelFormat;
    ADLX_RESULT res = displayService->GetPixelFormat(display, &displayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get pixel format enabled ===" << std::endl;
        ADLX_PIXEL_FORMAT pf = FORMAT_UNKNOWN;
        res = displayPixelFormat->GetValue(&pf);
        std::string pfStr = "FORMAT_UNKNOWN";
        auto searchIter = PixelFormatMap.find(pf);
        if (searchIter != PixelFormatMap.end())
        {
            pfStr = searchIter->second;
        }
        std::cout << "\tGetValue, res " << res << " pixel format: " << pfStr.c_str() << std::endl;
    }
}

void SetPixelFormatState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayPixelFormatPtr displayPixelFormat;
    ADLX_RESULT res = displayService->GetPixelFormat(display, &displayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set pixel format to RGB_444_FULL
        case 0:
            std::cout << "  === Set pixel format to RGB_444_FULL" << std::endl;
            res = displayPixelFormat->SetValue(RGB_444_FULL);
            break;
            // Set pixel format to YCBCR_444
        case 1:
            std::cout << "  === Set pixel format to YCBCR_444" << std::endl;
            res = displayPixelFormat->SetValue(YCBCR_444);
            break;
            // Set pixel format to YCBCR_422
        case 2:
            std::cout << "  === Set pixel format to YCBCR_422" << std::endl;
            res = displayPixelFormat->SetValue(YCBCR_422);
            break;
            // Set pixel format to RGB_444_LIMITED
        case 3:
            std::cout << "  === Set pixel format to RGB_444_LIMITED" << std::endl;
            res = displayPixelFormat->SetValue(RGB_444_LIMITED);
            break;
        default:
            break;
        }
        std::cout << "\tReturn code is: " << res <<" (0 means success)" << std::endl;
    }
}

// Get support state for each pixel format
void GetSupportStateForEachPixelFormat(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayPixelFormatPtr displayPixelFormat;
    ADLX_RESULT res = displayService->GetPixelFormat(display, &displayPixelFormat);
    if (ADLX_SUCCEEDED(res) && displayPixelFormat)
    {
        std::cout << " === Get pixel format list ===" << std::endl;
        adlx_bool support = false;

        res = displayPixelFormat->IsSupportedRGB444Full(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs support RGB 4:4:4 PC Standard (Full RGB): " << support << std::endl;
        res = displayPixelFormat->IsSupportedYCbCr444(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs support YCbCr 4:4:4: " << support << std::endl;
        res = displayPixelFormat->IsSupportedYCbCr422(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs support YCbCr 4:2:2: " << support << std::endl;
        res = displayPixelFormat->IsSupportedRGB444Limited(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs support RGB 4:4:4 Studio (Limited RGB): " << support << std::endl;
        res = displayPixelFormat->IsSupportedYCbCr420(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs support YCbCr 4:2:0: " << support << std::endl;

        const std::unordered_map<ADLX_PIXEL_FORMAT, std::string> PixelFormatMap{
            {RGB_444_FULL, "RGB 4:4:4 PC Standard (Full RGB)"},
            {YCBCR_444, "YCbCr 4:4:4"},
            {YCBCR_422, "YCbCr 4:2:2"},
            {RGB_444_LIMITED, "RGB 4:4:4 Studio (Limited RGB)"},
            {YCBCR_420, "YCbCr 4:2:0"}
        };
        for_each(PixelFormatMap.begin(), PixelFormatMap.end(), [&](auto pixelFormat) {
            res = displayPixelFormat->IsSupportedPixelFormat(pixelFormat.first, &support);
            if (ADLX_SUCCEEDED(res))
                std::cout << "\tIs support " << pixelFormat.second << ": " << support << std::endl;
        });
    }
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display PixelFormat support" << std::endl;

    std::cout << "\t->Press 2 to get PixelFormat state" << std::endl;

    std::cout << "\t->Press 3 to set current pixel format to RGB_444_FULL" << std::endl;
    std::cout << "\t->Press 4 to set current pixel format to YCBCR_444" << std::endl;
    std::cout << "\t->Press 5 to set current pixel format to YCBCR_422" << std::endl;
    std::cout << "\t->Press 6 to set current pixel format to RGB_444_LIMITED" << std::endl;

    std::cout << "\t->Press 7 to get support state for each pixel format" << std::endl;

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
            // Display displayPixelFormat support
        case '1':
            ShowDisplayPixelFormatSupport(displayService, display);
            break;

            // Display current displayPixelFormat state
        case '2':
            GetPixelFormatState(displayService, display);
            break;

            // Set displayPixelFormat
        case '3':
        case '4':
        case '5':
        case '6':
            SetPixelFormatState(displayService, display, num - '3');
            break;

            // Get displayPixelFormat support list
        case '7':
            GetSupportStateForEachPixelFormat(displayService, display);
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