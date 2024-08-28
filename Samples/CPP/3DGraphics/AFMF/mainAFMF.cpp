//
// Copyright (c) 2023 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAFMF.cpp
/// \brief Demonstrates how to access AMD Fluid Motion Frames options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings1.h"
#include <iostream>
#include <string>
#include <vector>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display AFMF support
void ShowAFMFSupport(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF);

// Display current AFMF state
void GetAFMFState(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF);

// Set AFMF state
void SetAFMFState(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF);

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
        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get 3DSettings service
            IADLX3DSettingsServices1Ptr d3dSettingSrv1(d3dSettingSrv);

            if (NULL != d3dSettingSrv1)
            {

                // Get AFMF interface
                IADLX3DAMDFluidMotionFramesPtr d3dAFMF;
                res = d3dSettingSrv1->GetAMDFluidMotionFrames(&d3dAFMF);
                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(d3dAFMF);
                }
            }
            else
            {
                // Destroy ADLX
                res = g_ADLXHelp.Terminate();
                std::cout << "Destroy ADLX res: " << res << std::endl;
                return WaitAndExit("Failed to get 3DSettings services2", 0);
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get 3DSettings services", 0);
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

void ShowAFMFSupport(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dAFMF->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

void GetAFMFState(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dAFMF->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << ", return code is: " << res << "(0 means success)" << std::endl;

}

void SetAFMFState(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF,int index)
{
    ADLX_RESULT res = d3dAFMF->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

}

int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display AFMF support" << std::endl;
    std::cout << "\t->Press 2 to display current AFMF state" << std::endl;
    std::cout << "\t->Press 3 to enable AFMF" << std::endl;
    std::cout << "\t->Press 4 to disable AFMF" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display AFMF support
        case '1':
            ShowAFMFSupport(d3dAFMF);
            break;

            // Display current AFMF state
        case '2':
            GetAFMFState(d3dAFMF);
            break;

            // Set AFMF
        case '3':
        case '4':
            SetAFMFState(d3dAFMF, num - '3');
            break;

            // Display menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}