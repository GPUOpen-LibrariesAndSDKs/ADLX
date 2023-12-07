//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayConnectivityExperience.cpp
/// \brief Demonstrates how to obtain Connectivity-Experience when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays2.h"
#include <iostream>
#include <unordered_map>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display supported HDMI quality detection
void ShowSupportedHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Display supported DP link
void ShowSupportedDPLink(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Display current HDMI quality detection state
void GetEnabledHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Set displayVariBright status to enable/disable
void SetEnabledHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, adlx_bool enableDisable);

// Display DP link rate value
void GetDPLinkRate(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Display number of active lanes
void GetNumberOfActiveLanes(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Display number of total lanes
void GetNumberOfTotalLanes(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Display relative pre-emphasis
void GetRelativePreEmphasis(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Relative pre-emphasis setting menu control
void RelativePreEmphasisSettingMenuControl(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Set relative pre-emphasis
void SetRelativePreEmphasis(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, int relativePreEmphasis);

// Display relative pre-emphasis
void GetRelativeVoltageSwing(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Relative voltage swing setting menu control
void RelativeVoltageSwingSettingMenuControl(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Set relative pre-emphasis
void SetRelativeVoltageSwing(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, int relativeVoltageSwing);

// Display current link protection statue
void GetEnabledLinkProtection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServices2Ptr& displayService, const IADLXDisplayPtr& display);

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
            IADLXDisplayServices2Ptr displayServices1(displayService);

            if (nullptr != displayServices1)
            {
                // Get display list
                IADLXDisplayListPtr displayList;
                res = displayService->GetDisplays(&displayList);
                if (ADLX_FAILED (res))
                {
                    // Destroy ADLX
                    res = g_ADLXHelp.Terminate ();
                    std::cout << "Destroy ADLX res: " << res << std::endl;
                    return WaitAndExit ("Failed to get the display list", 0);
                }
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplayPtr display;
                res = displayList->At(it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and parse the selection
                    MenuControl(displayServices1, display);
                }
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

void ShowSupportedHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get HDMI quality detection Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayConnectivityExperience->IsSupportedHDMIQualityDetection(&supported);
        std::cout << "\tHDMI quality detection is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
    }
}

void ShowSupportedDPLink(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get DP Link Supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayConnectivityExperience->IsSupportedDPLink(&supported);
        std::cout << "\tDP Link is supported on the display: " << (supported ? "true" : "false") << ", return code: " << res << " (0 means success)" << std::endl;
    }
}

void GetEnabledHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get HDMI quality detection enabled ===" << std::endl;
        adlx_bool enabled = false;
        res = displayConnectivityExperience->IsEnabledHDMIQualityDetection(&enabled);
        std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
    }
}

void SetEnabledHDMIQualityDetection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, adlx_bool enableDisable)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED (res))
    {
        if (!enableDisable)
        {
            res = displayConnectivityExperience->SetEnabledHDMIQualityDetection(false);
            std::cout << "\tSet enabled to false, result: " << res << " (0 means success)" << std::endl;
        }
        else
        {
            res = displayConnectivityExperience->SetEnabledHDMIQualityDetection (true);
            std::cout << "\tSet enabled to true, result: " << res << " (0 means success)" << std::endl;
        }
    }
}

void GetDPLinkRate(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    const std::unordered_map<int, std::string> DPLinkRateMap =
        {
            {0, "DP_LINK_RATE_RBR"},
            {1, "DP_LINK_RATE_2_16GBPS"},
            {2, "DP_LINK_RATE_2_43GBPS"},
            {3, "DP_LINK_RATE_HBR"},
            {4, "DP_LINK_RATE_4_32GBPS"},
            {5, "DP_LINK_RATE_HBR2"},
            {6, "DP_LINK_RATE_HBR3"},
            {7, "DP_LINK_RATE_UHBR10"},
            {8, "DP_LINK_RATE_UHBR13D5"},
            {9, "DP_LINK_RATE_UHBR20"}};

    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get DP link rate ===" << std::endl;
        ADLX_DP_LINK_RATE DPLinkRate = ADLX_DP_LINK_RATE::DP_LINK_RATE_UNKNOWN;
        res = displayConnectivityExperience->GetDPLinkRate(&DPLinkRate);
        std::string DPLinkRateStr = 0 != DPLinkRateMap.count(DPLinkRate) ? DPLinkRateMap.at(DPLinkRate) : "DP_LINK_RATE_UNKNOWN";
        std::cout << "\tGetValue, result: " <<  res << " mode: " << DPLinkRateStr.c_str() << std::endl;
    }
}

void GetNumberOfActiveLanes(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get number of active lanes ===" << std::endl;
        adlx_uint numberOfActiveLanes;
        res = displayConnectivityExperience->GetNumberOfActiveLanes(&numberOfActiveLanes);
        std::cout << "\tGetValue, result: " << res << " value: " << numberOfActiveLanes << std::endl;
    }
}

void GetNumberOfTotalLanes(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get number of total lanes ===" << std::endl;
        adlx_uint numberOfTotalLanes;
        res = displayConnectivityExperience->GetNumberOfTotalLanes(&numberOfTotalLanes);
        std::cout << "\tGetValue, result: " << res << " value: " << numberOfTotalLanes << std::endl;
    }
}

void GetRelativePreEmphasis(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get relative pre-emphasis ===" << std::endl;
        adlx_int relativePreEmphasis;
        res = displayConnectivityExperience->GetRelativePreEmphasis(&relativePreEmphasis);
        std::cout << "\tGetValue, result: " << res << " value: " << relativePreEmphasis << std::endl;
    }
}

void RelativePreEmphasisSettingMenuControl(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    printf ("  === relative pre-emphasis setting ===\n");
    printf ("\t->Press integer in [-2:2] to set relative pre-emphasis or return main menu\n");
    int num = 0;
    if ((std::cin >> num) && (-2 <= num && num <= 2))
    {
        SetRelativePreEmphasis(displayService2, display, num);
    }
}

void SetRelativePreEmphasis(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, int relativePreEmphasis)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Set relative pre-emphasis ===" << std::endl;
        res = displayConnectivityExperience->SetRelativePreEmphasis(relativePreEmphasis);
        std::cout << "\tReturn code is: " << res <<" (0 means success)" << std::endl;
    }
}

void GetRelativeVoltageSwing(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get relative voltage swing ===" << std::endl;
        adlx_int relativeVoltageSwing;
        res = displayConnectivityExperience->GetRelativeVoltageSwing(&relativeVoltageSwing);
        std::cout << "\tGetValue, result: " << relativeVoltageSwing << std::endl;
    }
}

void RelativeVoltageSwingSettingMenuControl(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    printf ("  === relative voltage swing setting ===\n");
    printf ("\t->Press integer in [-2:2] to set relative voltage swing or return main menu\n");
    int num = 0;
    if ((std::cin >> num) && (-2 <= num && num <= 2))
    {
        SetRelativeVoltageSwing(displayService2, display, num);
    }
}

void SetRelativeVoltageSwing(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display, int relativeVoltageSwing)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Set relative voltage swing ===" << std::endl;
        res = displayConnectivityExperience->SetRelativeVoltageSwing(relativeVoltageSwing);
        std::cout << "\tReturn code is: " << res <<" (0 means success)" << std::endl;
    }
}

void GetEnabledLinkProtection(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
    ADLX_RESULT res = displayService2->GetDisplayConnectivityExperience(display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get link protection enabled ===" << std::endl;
        adlx_bool enabled = false;
        res = displayConnectivityExperience->IsEnabledLinkProtection(&enabled);
        std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
    }
}


void MainMenu()
{
    std::cout << "\tChoose from following options" << std::endl;

    std::cout << "\t->Press 1 to display HDMI quality detection support" << std::endl;
    std::cout << "\t->Press 2 to display DP link support" << std::endl;
    std::cout << "\t->Press 3 to get HDMI quality detection status" << std::endl;
    std::cout << "\t->Press 4 to set HDMI quality detection to Enable" << std::endl;
    std::cout << "\t->Press 5 to set HDMI quality detection status to Disable" << std::endl;
    std::cout << "\t->Press 6 to display DP link rate" << std::endl;
    std::cout << "\t->Press 7 to display number of active lanes" << std::endl;
    std::cout << "\t->Press 8 to display number of total lanes" << std::endl;
    std::cout << "\t->Press 9 to display relative pre-emphasis" << std::endl;
    std::cout << "\t->Press a to enter the Relative Pre-emphasis settings menu" << std::endl;
    std::cout << "\t->Press b to display relative voltage swing" << std::endl;
    std::cout << "\t->Press c to enter the Relative Voltage Swing settings menu" << std::endl;
    std::cout << "\t->Press d to display if link protection is enabled" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXDisplayServices2Ptr& displayService2, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display supported HDMI quality detection
        case '1':
            ShowSupportedHDMIQualityDetection(displayService2, display);
            break;

            // Display ssupported DP link
        case '2':
            ShowSupportedDPLink(displayService2, display);
            break;

            // Get HDMI quality detection enable
        case '3':
             GetEnabledHDMIQualityDetection(displayService2, display);
            break;

            // Set HDMI quality detection enable
        case '4':
            SetEnabledHDMIQualityDetection(displayService2, display, true);
            break;

            // Set HDMI quality detection disable
        case '5':
            SetEnabledHDMIQualityDetection(displayService2, display, false);
            break;

            // Display DP link rate
        case '6':
            GetDPLinkRate(displayService2, display);
            break;

            // Display number of active lanes
        case '7':
            GetNumberOfActiveLanes(displayService2, display);
            break;

            // Display number of totla lanes
        case '8':
            GetNumberOfTotalLanes(displayService2, display);
            break;

            // Display relative pre-emphasis
        case '9':
            GetRelativePreEmphasis(displayService2, display);
            break;

            // Enter relative pre-emphasis setting control
        case 'a':
            RelativePreEmphasisSettingMenuControl(displayService2, display);
            break;

            // Display relative voltage swing
        case 'b':
            GetRelativeVoltageSwing(displayService2, display);
            break;

            // Enter relative voltage swing setting control
        case 'c':
            RelativeVoltageSwingSettingMenuControl(displayService2, display);
            break;

            // Display link protection status
        case 'd':
            GetEnabledLinkProtection(displayService2, display);
            break;

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
