//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayInfo.cpp
/// \brief Demonstrates how to obtain the display information when programming with ADLX to perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <map>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Print diplayInfo information
void ShowDisplayInfo(const IADLXDisplayPtr& display);

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
            // Get display list and iterate through the list
            IADLXDisplayListPtr displayList;
            res = displayService->GetDisplays(&displayList);
            if (ADLX_SUCCEEDED (res))
            {
                adlx_uint it = displayList->Begin();
                IADLXDisplayPtr display;
                for (; it != displayList->End(); it++)
                {
                    res = displayList->At(it, &display);
                    if (ADLX_SUCCEEDED(res))
                    {
                        // Get data for each display device and print it on the console
                        ShowDisplayInfo(display);
                    }
                }
            }
            else
            {
                std::cout << "Failed to get the Displays list" << std::endl;
            }

        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate ();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit ("Failed to get the Display Services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the printout
    system("pause");

    return 0;
}

// Extra data
// Map with the display type and associated string
static const std::map<ADLX_DISPLAY_TYPE, const char*> displayTypeMap =
    {
        {DISPLAY_TYPE_MONITOR, "CRT"},
        {DISPLAY_TYPE_TELEVISION, "TV"},
        {DISPLAY_TYPE_LCD_PANEL, "LCD"},
        {DISPLAY_TYPE_DIGITAL_FLAT_PANEL, "DFP"},
        {DISPLAY_TYPE_COMPONENT_VIDEO, "CV"}};

// Map with the display connector type and associated string
static const std::map<ADLX_DISPLAY_CONNECTOR_TYPE, const char*> displayConnectorMap =
    {
        {DISPLAY_CONTYPE_UNKNOWN, "UNKNOWN"},
        {DISPLAY_CONTYPE_VGA, "VGA"},
        {DISPLAY_CONTYPE_DVI_D, "DVI D"},
        {DISPLAY_CONTYPE_DVI_I, "DVI I"},
        {DISPLAY_CONTYPE_CVDONGLE_NTSC, "ATICVDONGLE NTSC"},
        {DISPLAY_CONTYPE_CVDONGLE_JPN, "ATICVDONGLE JPN"},
        {DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN, "ATICVDONGLE NONI2C JPN"},
        {DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC, "ATICVDONGLE NONI2C NTSC"},
        {DISPLAY_CONTYPE_PROPRIETARY, "PROPRIETARY"},
        {DISPLAY_CONTYPE_HDMI_TYPE_A, "HDMI TYPE A"},
        {DISPLAY_CONTYPE_HDMI_TYPE_B, "HDMI TYPE B"},
        {DISPLAY_CONTYPE_SVIDEO, "SVIDEO"},
        {DISPLAY_CONTYPE_COMPOSITE, "COMPOSITE"},
        {DISPLAY_CONTYPE_RCA_3COMPONENT, "RCA 3COMPONENT"},
        {DISPLAY_CONTYPE_DISPLAYPORT, "DISPLAYPORT"},
        {DISPLAY_CONTYPE_EDP, "EDP"},
        {DISPLAY_CONTYPE_WIRELESSDISPLAY, "WIRELESSDISPLAY"},
        {DISPLAY_CONTYPE_USB_TYPE_C, "USB TYPE C"}};

// Map with the scan type and associated string
static const std::map<ADLX_DISPLAY_SCAN_TYPE, const char*> scanTypeMap =
    {
        {PROGRESSIVE, "PROGRESSIVE"}, {INTERLACED, "INTERLACED"}};

// Print diplayInfo information
void ShowDisplayInfo(const IADLXDisplayPtr& display)
{
    ADLX_RESULT res = ADLX_OK;

    std::cout << "\n  === Display info ===" << std::endl;
    const char* dispName;
    res = display->Name(&dispName);
    std::cout << "\tDisplay name: " << dispName << std::endl;

    adlx_uint manufacturerID;
    res = display->ManufacturerID(&manufacturerID);
    std::cout << "\tManufacturer id: " << manufacturerID << std::endl;

    ADLX_DISPLAY_TYPE displayType;
    res = display->DisplayType(&displayType);
    std::cout << "\tDisplay type: " << displayTypeMap.find(displayType)->second << std::endl;

    ADLX_DISPLAY_CONNECTOR_TYPE connectType;
    res = display->ConnectorType(&connectType);
    std::cout << "\tConnector type: " << displayConnectorMap.find(connectType)->second << std::endl;

    const char* edid;
    res = display->EDID(&edid);
    if (ADLX_OK != res)
        std::cout << "\t Display EDID, error code is: " << res << std::endl;
    else
        std::cout << "\tEDID: " << edid << std::endl;

    adlx_double refreshRate;
    res = display->RefreshRate(&refreshRate);
    std::cout << "\tRefresh rate: " << refreshRate << std::endl;

    adlx_uint pixelClock;
    res = display->PixelClock(&pixelClock);
    std::cout << "\tPixel clock: " << pixelClock << std::endl;

    adlx_int maxHResolution = 0;
    adlx_int maxVResolution = 0;
    res = display->NativeResolution(&maxHResolution, &maxVResolution);
    std::cout << "\tNative resolution[h*v]:" << maxHResolution << " " << maxVResolution << std::endl;

    ADLX_DISPLAY_SCAN_TYPE scanType;
    res = display->ScanType(&scanType);
    std::cout << "\tScan type: " << scanTypeMap.find(scanType)->second << std::endl;

    adlx_size id;
    res = display->UniqueId(&id);
    std::cout << "\tUniqueId: " << id << std::endl;
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