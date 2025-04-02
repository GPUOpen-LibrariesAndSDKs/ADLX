//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainChill.cpp
/// \brief Demonstrates how to access AMD Radeon Chill options, and perform related testing when programming with ADLX.

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

// Display Chill support
void ShowChillSupport(const IADLX3DChillPtr& d3dChill);

// Display current Chill state
void GetChillState(const IADLX3DChillPtr& d3dChill);

// Set Chill state
void SetChillState(const IADLX3DChillPtr& d3dChill, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DChillPtr& d3dChill);

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

        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (!gpus->Empty() && ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPUPtr gpuInfo;
            adlx_uint index = 0;
            res = gpus->At(index, &gpuInfo);

            // Get Chill interface
            IADLX3DChillPtr d3dChill;
            res = d3dSettingSrv->GetChill(gpuInfo, &d3dChill);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dChill);
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

void ShowChillSupport(const IADLX3DChillPtr& d3dChill)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dChill->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetChillState(const IADLX3DChillPtr& d3dChill)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dChill->IsSupported(&supported);
    if (supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = d3dChill->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsEnabled: " << enabled << std::endl;
        adlx_int minFPS, maxFPS;
        ADLX_IntRange fpsRange;
        res = d3dChill->GetMinFPS(&minFPS);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tCurrent MinFPS: " << minFPS << std::endl;
        res = d3dChill->GetMaxFPS(&maxFPS);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tCurrent MaxFPS: " << maxFPS << std::endl;
        res = d3dChill->GetFPSRange(&fpsRange);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tFPSSet limit [ " << fpsRange.minValue << " ," << fpsRange.maxValue << " ], step: " << fpsRange.step << std::endl;
    }
    else
    {
        std::cout << "\tChill feature is not supported " << std::endl;
    }
}

void SetChillState(const IADLX3DChillPtr& d3dChill, int index)
{
    ADLX_RESULT res = d3dChill->SetEnabled(index == 0);
    std::cout << "\treturn code(0 is Success) is: " << res << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int minFPS, maxFPS;
        ADLX_IntRange fpsRange;
        d3dChill->GetMinFPS(&minFPS);
        d3dChill->GetMaxFPS(&maxFPS);
        d3dChill->GetFPSRange(&fpsRange);
        std::cout << "\t\tEnter two space delimited integers:[minFPS, maxFPS]" << std::endl;

        int userKey = 0;
        std::vector<adlx_int> coeffs;
        while (std::cin >> userKey)
        {
            coeffs.push_back(userKey);
            if (coeffs.size() > 1)
                break;
        }
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        if (coeffs.size() > 1)
        {
            res = d3dChill->SetMinFPS(coeffs[0]);
            std::cout << "\tSet minimum FPS return code: " << res << "(0 means success)" << std::endl;
            res = d3dChill->SetMaxFPS(coeffs[1]);
            std::cout << "\tSet maximum FPS return code: " << res << "(0 means success)" << std::endl;
        }
        else
        {
            res = d3dChill->SetMinFPS(fpsRange.minValue);
            std::cout << "\tUse FPS minimum limit, set minimum FPS return code is: " << res << "(0 means success)" << std::endl;
            res = d3dChill->SetMaxFPS(fpsRange.maxValue);
            std::cout << "\tUse FPS maximum limit, set maximum FPS return code is: " << res << "(0 means success)" << std::endl;
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

    std::cout << "\t->Press 1 to display Chill support" << std::endl;
    std::cout << "\t->Press 2 to display current Chill state" << std::endl;
    std::cout << "\t->Press 3 to enable Chill" << std::endl;
    std::cout << "\t->Press 4 to disable Chill" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DChillPtr& d3dChill)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Chill support
        case '1':
            ShowChillSupport(d3dChill);
            break;

            // Display current Chill state
        case '2':
            GetChillState(d3dChill);
            break;

            // Set Chill state
        case '3':
        case '4':
            SetChillState(d3dChill, num - '3');
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
