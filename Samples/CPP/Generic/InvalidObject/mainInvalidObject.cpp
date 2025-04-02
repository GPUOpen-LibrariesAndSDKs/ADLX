//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainInvalidObject.cpp
/// \brief Demonstrates how to handle invalid objects when programming in ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

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
            // Get the display list and iterate through the list
            IADLXDisplayListPtr displayList;
            res = displayService->GetDisplays(&displayList);
            if (ADLX_FAILED (res))
            {
                // Destroy ADLX
                res = g_ADLXHelp.Terminate ();
                std::cout << "Destroy ADLX res: " << res << std::endl;
                return WaitAndExit ("Failed to get the Display list", 0);
            }
            adlx_uint it = displayList->Begin();
            IADLXDisplayPtr display;
            for (; it != displayList->End(); it++)
            {
                res = displayList->At(it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    break;
                }
            }

            // Get the display name and prompt to unplug the display
            const char* dispName;
            res = display->Name(&dispName);
            std::cout << "Within 15 seconds, unplug the display " << dispName << std::endl;

            // Block for 15s
            Sleep(15 * 1000);

            //After 15 seconds, reading the display name again. If the display was unplugged, the method will fail and return ADLX_INVALID_OBJECT.
            // Get display name again.
            res = display->Name(&dispName);
            std::cout << "Get display name return code is: " << res << " (" << ADLX_INVALID_OBJECT << " means that the method was called into an invalid object)" << std::endl;
            if (ADLX_INVALID_OBJECT == res)
            {
                //To do: Handle the invalid display
                std::cout << "The display is invalid." << std::endl;
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
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");
    return 0;
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