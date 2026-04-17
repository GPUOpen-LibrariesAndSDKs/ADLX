//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAFMF.cpp
/// \brief Demonstrates how to access AMD Fluid Motion Frames options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings3.h"
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
                std::cout << "Failed to get 3DSettings services2: " << res << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get 3DSettings services: " << res << std::endl;
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

void GetAFMF1Status(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1Ptr d3dAFMF1(d3dAFMF);
    if (d3dAFMF1 == nullptr)
    {
        std::cout << "AFMF2 interface is not supported" << std::endl;
        return;
    }

    adlx_bool supported = false;
    ADLX_RESULT res = d3dAFMF1->IsSupportedAlgorithm(&supported);
    std::cout << "\tIsSupportedAlgorithm: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
    if (ADLX_SUCCEEDED(res) && supported)
    {
        ADLX_AFMF_ALGORITHM algorithm;
        res = d3dAFMF1->GetAlgorithm(&algorithm);
        std::cout << "\tAlgorithm: " << algorithm << ", return code is: " << res << "(0 means success)" << std::endl;
    }

    ADLX_AFMF_SEARCH_MODE_TYPE searchMode;
    res = d3dAFMF1->GetSearchMode(&searchMode);
    std::cout << "\tSearchMode: " << searchMode << ", return code is: " << res << "(0 means success)" << std::endl;

    ADLX_AFMF_PERFORMANCE_MODE_TYPE performanceMode;
    res = d3dAFMF1->GetPerformanceMode(&performanceMode);
    std::cout << "\tPerformanceMode: " << performanceMode << ", return code is: " << res << "(0 means success)" << std::endl;

    ADLX_AFMF_FAST_MOTION_RESP response;
    res = d3dAFMF1->GetFastMotionResponse(&response);
    std::cout << "\tFastMotionResponse: " << response << ", return code is: " << res << "(0 means success)" << std::endl;
}

void SetAlgorithmCapabilities(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1Ptr d3dAFMF1(d3dAFMF);
    if (d3dAFMF1 == nullptr)
    {
        std::cout << "AFMF2 interface is not supported" << std::endl;
        return;
    }
    ADLX_AFMF_ALGORITHM algorithm;
    ADLX_RESULT res = d3dAFMF1->GetAlgorithm(&algorithm);
    // Set algorithm to a different value
    if (AFMF_ALGORITHM_AUTO == algorithm)
        res = d3dAFMF1->SetAlgorithm(AFMF_ALGORITHM_STANDARD);
    else if (AFMF_ALGORITHM_ENHANCED == algorithm)
        res = d3dAFMF1->SetAlgorithm(AFMF_ALGORITHM_STANDARD);
    else
        res = d3dAFMF1->SetAlgorithm(AFMF_ALGORITHM_ENHANCED);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetSearchMode(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1Ptr d3dAFMF1(d3dAFMF);
    if (d3dAFMF1 == nullptr)
    {
        std::cout << "AFMF2 interface is not supported" << std::endl;
        return;
    }
    ADLX_AFMF_SEARCH_MODE_TYPE searchMode;
    ADLX_RESULT res = d3dAFMF1->GetSearchMode(&searchMode);
    // Set search mode to a different value
    if (AFMF_SEARCH_MODE_AUTO == searchMode)
        res = d3dAFMF1->SetSearchMode(AFMF_SEARCH_MODE_STANDARD);
    else if (AFMF_SEARCH_MODE_STANDARD == searchMode)
        res = d3dAFMF1->SetSearchMode(AFMF_SEARCH_MODE_HIGH);
    else if (AFMF_SEARCH_MODE_HIGH == searchMode)
        res = d3dAFMF1->SetSearchMode(AFMF_SEARCH_MODE_AUTO);

    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetPerformanceMode(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1Ptr d3dAFMF1(d3dAFMF);
    if (d3dAFMF1 == nullptr)
    {
        std::cout << "AFMF2 interface is not supported" << std::endl;
        return;
    }
    ADLX_AFMF_PERFORMANCE_MODE_TYPE performanceMode;
    ADLX_RESULT res = d3dAFMF1->GetPerformanceMode(&performanceMode);
    // Set performance mode to a different value
    if (AFMF_PERFORMANCE_MODE_AUTO == performanceMode)
        res = d3dAFMF1->SetPerformanceMode(AFMF_PERFORMANCE_MODE_QUALITY);
    else if (AFMF_PERFORMANCE_MODE_QUALITY == performanceMode)
        res = d3dAFMF1->SetPerformanceMode(AFMF_PERFORMANCE_MODE_PERFORMANCE);
    else
        res = d3dAFMF1->SetPerformanceMode(AFMF_PERFORMANCE_MODE_AUTO);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetFastMotionResponse(const IADLX3DAMDFluidMotionFramesPtr& d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1Ptr d3dAFMF1(d3dAFMF);
    if (d3dAFMF1 == nullptr)
    {
        std::cout << "AFMF2 interface is not supported" << std::endl;
        return;
    }
    ADLX_AFMF_FAST_MOTION_RESP response;
    ADLX_RESULT res = d3dAFMF1->GetFastMotionResponse(&response);
    // Set fast motion response to a different value
    if (AFMF_RESP_REPEAT_FRAMES == response)
        res = d3dAFMF1->SetFastMotionResponse(AFMF_RESP_BLENDED_FRAMES);
    else
        res = d3dAFMF1->SetFastMotionResponse(AFMF_RESP_REPEAT_FRAMES);
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
    std::cout << "\t->Press 5 to display AFMF2.1 capabilities and state" << std::endl;
    std::cout << "\t->Press 6 to set algorithm capabilities" << std::endl;
    std::cout << "\t->Press 7 to set search mode" << std::endl;
    std::cout << "\t->Press 8 to set performance mode" << std::endl;
    std::cout << "\t->Press 9 to set fast motion response" << std::endl;

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

            // Get AFMF2.1 capabilities and state
        case '5':
            GetAFMF1Status(d3dAFMF);
            break;

            // Set Algorithm capabilities
        case '6':
            SetAlgorithmCapabilities(d3dAFMF);
            break;

            // Set Search mode
        case '7':
            SetSearchMode(d3dAFMF);
            break;
            // Set Performance mode
        case '8':
            SetPerformanceMode(d3dAFMF);
            break;

            // Set Fast motion response
        case '9':
            SetFastMotionResponse(d3dAFMF);
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
