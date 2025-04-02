//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayCustomResolution.cpp
/// \brief This document describes how to obtain the display HDCP through ADLX and perform related tests.

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
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display custom resolution support
void ShowCustomResolutionSupport(IADLXDisplayCustomResolutionPtr pCustomResolution);

// Display available display resolutions
void GetResolutionList(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionList** ppResolutionList);

// Display current display resolution
void GetCurrentResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolution** ppResolution);

// Create new customized display resolution
void CreateNewResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionPtr pResolution);

// Delete display resolution
void DeleteResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionPtr pResolution);

// Print out specified resolution
void PrintResolution(IADLXDisplayResolutionPtr pResolution);

// Print out specified resolution list
void PrintResolutions(IADLXDisplayResolutionListPtr pResolutionList);

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
            std::cout << "Failed to get the Display Services: " << res << std::endl;
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

void ShowCustomResolutionSupport(IADLXDisplayCustomResolutionPtr pCustomResolution)
{
    std::cout << "  === custom resolution supported ===" << std::endl;
    adlx_bool supported = false;
    ADLX_RESULT res = pCustomResolution->IsSupported(&supported);
    std::cout << "\tIsSupported result: " << res << ", supported: " << supported << std::endl;
}

void GetResolutionList(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionList** ppResolutionList)
{
    ADLX_RESULT res = pCustomResolution->GetResolutionList(ppResolutionList);
    if (ADLX_FAILED(res))
        std::cout << " GetResolutionList: failed" << std::endl;

}

void GetCurrentResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolution** ppResolution)
{
    ADLX_RESULT res = pCustomResolution->GetCurrentAppliedResolution(ppResolution);
    if (ADLX_FAILED(res))
        std::cout << " GetCurrentAppliedResolution: failed" << std::endl;
}

void CreateNewResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionPtr pResolution)
{
    ADLX_RESULT res = pCustomResolution->CreateNewResolution(pResolution);
    if (ADLX_FAILED(res))
        std::cout << " CreateNewResolution: failed." << std::endl;
}

void DeleteResolution(IADLXDisplayCustomResolutionPtr pCustomResolution, IADLXDisplayResolutionPtr pResolution)
{
    PrintResolution(pResolution);
    ADLX_RESULT res = pCustomResolution->DeleteResolution(pResolution);
    if (ADLX_FAILED(res))
        std::cout << " DeleteResolution: failed." << std::endl;
}

void PrintResolution(IADLXDisplayResolutionPtr pResolution)
{
    ADLX_CustomResolution cr;
    pResolution->GetValue(&cr);

    std::string sPresention = (cr.presentation == ADLX_DISPLAY_SCAN_TYPE::INTERLACED) ? "Interlaced" : "Progressive";
    std::string sTimingStandard = "Manual";
    std::string sHPolarity = (cr.detailedTiming.hPolarity == ADLX_DISPLAY_TIMING_POLARITY::POSITIVE) ? "Positive" : "Negative";
    std::string sVPolarity = (cr.detailedTiming.vPolarity == ADLX_DISPLAY_TIMING_POLARITY::POSITIVE) ? "Positive" : "Negative";
    try
    {
        const std::unordered_map<ADLX_TIMING_STANDARD, std::string> timingStandardMap =
            {
                {MANUAL, "Manual"}, {DMT, "DMT"}, {GTF, "GTF"}, {CVT_RB, "CVT - Reduced Blanking"}, {CVT, "CVT"}};

        sTimingStandard = timingStandardMap.at(cr.timingStandard);
    } catch (...)
    {
        std::cout << "  Timing standard out of range!" << std::endl;
        return;
    }

    char buff[1024] = {0};
    int offset = std::snprintf(buff, sizeof(buff), "\n  resolution (Px)\t\t%d x %d\n", cr.resWidth, cr.resHeight);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Refresh Rate (Hz)\t\t%d\n", cr.refreshRate);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Presentation\t\t\t%s\n", sPresention.c_str());
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Standard\t\t%s\n", sTimingStandard.c_str());
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  G.Pixel Clock (kHz)\t\t%d\n", cr.GPixelClock);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Info\t\t\tHorizontal\tVertical\n");
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Total\t\t\t%d\t%d\n", cr.detailedTiming.hTotal, cr.detailedTiming.vTotal);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Display\t\t%d\t%d\n", cr.detailedTiming.hDisplay, cr.detailedTiming.vDisplay);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Front Porch\t\t%d\t%d\n", cr.detailedTiming.hFrontPorch, cr.detailedTiming.vFrontPorch);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Sync Width\t\t%d\t%d\n", cr.detailedTiming.hSyncWidth, cr.detailedTiming.vSyncWidth);
    offset += std::snprintf(buff + offset, sizeof(buff) - offset, "  Timing Polarity\t\t%s %s\n", sHPolarity.c_str(), sVPolarity.c_str());

    std::cout << buff << std::endl;
}

void PrintResolutions(IADLXDisplayResolutionListPtr pResolutionList)
{
    std::cout << " Print out resolution list ==" << std::endl;
    if (pResolutionList == nullptr)
    {
        std::cout << " resolution list is null" << std::endl;
        return;
    }

    if (pResolutionList->Size() == 0)
    {
        std::cout << " resolution list is empty!" << std::endl;
        return;
    }

    ADLX_RESULT res = ADLX_FAIL;
    for (adlx_uint crt = 0; crt < pResolutionList->Size(); crt++)
    {
        IADLXDisplayResolutionPtr pDispResolution = nullptr;
        res = pResolutionList->At(crt, &pDispResolution);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "  resolution index: " << crt << std::endl;
            PrintResolution(pDispResolution);
        }
    }
}

void MainMenu()
{
    std::cout << "\tChoose from the following options" << std::endl;

    std::cout << "\t->Press 1 to display custom Resolution support" << std::endl;

    std::cout << "\t->Press 2 to get custom Resolution list" << std::endl;

    std::cout << "\t->Press 3 to get current applied Resolution" << std::endl;
    std::cout << "\t->Press 4 to create new customized Resolution" << std::endl;
    std::cout << "\t->Press 5 to delete avaible Resolution" << std::endl;

    std::cout << "\t->Press Q/q  terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the command prompt menu" << std::endl;
}

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    IADLXDisplayCustomResolutionPtr pCustomResolution;
    displayService->GetCustomResolution(display, &pCustomResolution);

    if (!pCustomResolution)
    {
        std::cout << "Menu control: cannot retrive custom resolution instance!" << std::endl;
        return;
    }

    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display custom resolution support
        case '1':
            ShowCustomResolutionSupport(pCustomResolution);
            break;

            // Get current resolution
        case '2':
        {
            std::cout << "  === Get resolution list: ===" << std::endl;
            IADLXDisplayResolutionListPtr pResolutionList;
            GetResolutionList(pCustomResolution, &pResolutionList);
            PrintResolutions(pResolutionList);
            break;
        }

            // Get current applied resolution
        case '3':
        {
            std::cout << "  === Get current resolution: ===" << std::endl;
            IADLXDisplayResolutionPtr pDisplayResolution;
            GetCurrentResolution(pCustomResolution, &pDisplayResolution);
            PrintResolution(pDisplayResolution);
            break;
        }
            // Create new customized resolution
        case '4':
        {
            std::cout << "  === Create new resolution: ===" << std::endl;
            IADLXDisplayResolutionPtr pDisplayResolution;
            GetCurrentResolution(pCustomResolution, &pDisplayResolution);

            if (pDisplayResolution)
            {
                ADLX_CustomResolution customRes = {};
                pDisplayResolution->GetValue(&customRes);

                customRes.resWidth = 1920;
                customRes.resHeight = 1080;
                customRes.detailedTiming.hDisplay = 1920;
                customRes.detailedTiming.vDisplay = 1080;
                pDisplayResolution->SetValue(customRes);

                PrintResolution(pDisplayResolution);
                CreateNewResolution(pCustomResolution, pDisplayResolution);
            }
            break;
        }
            // Delete available resolution
        case '5':
        {
            std::cout << "  === Delete resolution: ===" << std::endl;
            IADLXDisplayResolutionListPtr pResolutionList;
            GetResolutionList(pCustomResolution, &pResolutionList);
            if (pResolutionList->Size() > 0)
            {
                IADLXDisplayResolutionPtr pDisplayResolution;
                ADLX_RESULT res = pResolutionList->At(0, &pDisplayResolution);
                if (ADLX_SUCCEEDED(res))
                    DeleteResolution(pCustomResolution, pDisplayResolution);
            }
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

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("Pause");
    return retCode;
}