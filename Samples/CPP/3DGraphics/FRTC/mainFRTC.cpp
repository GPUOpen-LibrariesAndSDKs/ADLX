//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFRTC.cpp
/// \brief Demonstrates how to access AMD Frame Rate Target Control (FRTC) options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <string>
#include <vector>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display FRTC support
void ShowFRTCSupport(const IADLX3DFrameRateTargetControlPtr& frtc);

// Get and display current FRTC state
void GetFRTCState(const IADLX3DFrameRateTargetControlPtr& frtc);

// Set FRTC state
void SetFRTCState(const IADLX3DFrameRateTargetControlPtr& frtc, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DFrameRateTargetControlPtr& frtc);

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
        // Get GPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_SUCCEEDED(res) && !gpus->Empty())
        {
            // Get 3DSettings service
            IADLX3DSettingsServicesPtr d3dSettingSrv;
            res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);
            if (ADLX_SUCCEEDED(res))
            {
                // Get GPU interface
                IADLXGPUPtr gpuInfo;
                adlx_uint index = 0;
                res = gpus->At(index, &gpuInfo);
                if (ADLX_SUCCEEDED(res))
                {
                    // Get FRTC interface
                    IADLX3DFrameRateTargetControlPtr frtc;
                    res = d3dSettingSrv->GetFrameRateTargetControl(gpuInfo, &frtc);
                    if (ADLX_SUCCEEDED(res))
                    {
                        MainMenu();
                        MenuControl(frtc);
                    }
                }
            }
            else
            {
                std::cout << "Failed to get 3DSettings services" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get GPU" << std::endl;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the printout
    system("pause");

    return 0;
}

void ShowFRTCSupport(const IADLX3DFrameRateTargetControlPtr& frtc)
{
    adlx_bool supported = false;
    frtc->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetFRTCState(const IADLX3DFrameRateTargetControlPtr& frtc)
{
    adlx_bool enabled = false;
    frtc->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << std::endl;
    adlx_int fps;
    ADLX_IntRange range  = {0};
    frtc->GetFPS(&fps);
    frtc->GetFPSRange(&range);
    std::cout << "\tCurrent FPS:" << fps << std::endl
              << "\tFPS limit [ " << range.minValue << " ," << range.maxValue << " ], step: " << range.step << std::endl;
}

void SetFRTCState(const IADLX3DFrameRateTargetControlPtr& frtc, int index)
{
    ADLX_RESULT res = frtc->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int fps;
        ADLX_IntRange range  = {0};
        frtc->GetFPS(&fps);
        frtc->GetFPSRange(&range);
        if (fps != range.minValue)
        {
            res = frtc->SetFPS(range.minValue);
            std::cout << "\tUse minimum FPS limit: return code is: " << res << "(0 means success)" << std::endl;
        }
        else
        {
            res = frtc->SetFPS(range.maxValue);
            std::cout << "\tUse maximum FPS limit: return code is: " << res << "(0 means success)" << std::endl;
        }
    }
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

    std::cout << "\t->Press 1 to display FRTC support" << std::endl;
    std::cout << "\t->Press 2 to get and display current FRTC state" << std::endl;
    std::cout << "\t->Press 3 to enable FRTC" << std::endl;
    std::cout << "\t->Press 4 to disable FRTC" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DFrameRateTargetControlPtr& frtc)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display FRTC support
        case '1':
            ShowFRTCSupport(frtc);
            break;

            // Get and display current FRTC state
        case '2':
            GetFRTCState(frtc);
            break;

            // Set FRTC state
        case '3':
        case '4':
            SetFRTCState(frtc, num - '3');
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