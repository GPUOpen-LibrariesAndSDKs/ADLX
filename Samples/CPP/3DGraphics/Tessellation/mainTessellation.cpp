//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainTessellation.cpp
/// \brief Demonstrates how to access tessellation options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <map>
#include <string>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX destory.
// so we use global variables to ensure the valid of the interface.
static ADLXHelper g_ADLXHelp;

// Display tessellation support
void ShowSupport(const IADLX3DTessellationPtr& tessellation);

// Get current tessellation state
void GetState(const IADLX3DTessellationPtr& tessellation);

// Set tessellation mode
void SetMode(const IADLX3DTessellationPtr& tessellation, int index);

// Set tessellation level
void SetLevel(const IADLX3DTessellationPtr& tessellation);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DTessellationPtr& tessellation);

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

            // Get IADLX3DTessellation interface
            IADLX3DTessellationPtr tessellation;
            res = d3dSettingSrv->GetTessellation(gpuInfo, &tessellation);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(tessellation);
            }
        }
        else
        {
            std::cout << "Failed to get the 3DSettings Services: " << res << std::endl;
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

static const std::map<ADLX_TESSELLATION_MODE, const char*> Modes =
    {
        {T_MODE_AMD_OPTIMIZED, "AMD optimized"},
        {T_MODE_USE_APP_SETTINGS, "Use application settings"},
        {T_MODE_OVERRIDE_APP_SETTINGS, "Override application settings"}};

static const std::map<ADLX_TESSELLATION_LEVEL, const char*> Levels =
    {
        {T_LEVEL_OFF, "Off"},
        {T_LEVEL_2X, "2X"},
        {T_LEVEL_4X, "4X"},
        {T_LEVEL_6X, "6X"},
        {T_LEVEL_8X, "8X"},
        {T_LEVEL_16X, "16X"},
        {T_LEVEL_32X, "32X"},
        {T_LEVEL_64X, "64X"}};

void ShowSupport(const IADLX3DTessellationPtr& tessellation)
{
    adlx_bool supported = false;
    ADLX_RESULT res = tessellation->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

void GetState(const IADLX3DTessellationPtr& tessellation)
{
    ADLX_TESSELLATION_MODE mode;
    ADLX_RESULT res = tessellation->GetMode(&mode);
    std::cout << "\tMode: " << Modes.find(mode)->second << ", return code is: " << res << "(0 means success)" << std::endl;

    ADLX_TESSELLATION_LEVEL level;
    res = tessellation->GetLevel(&level);
    std::cout << "\tLevel: " << Levels.find(level)->second << ", return code is: " << res << "(0 means success)" << std::endl;
}

void SetMode(const IADLX3DTessellationPtr& tessellation, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    ADLX_TESSELLATION_MODE mode = T_MODE_AMD_OPTIMIZED;
    mode = (ADLX_TESSELLATION_MODE)(mode + index);
    res = tessellation->SetMode(mode);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetLevel(const IADLX3DTessellationPtr& tessellation)
{
    ADLX_TESSELLATION_LEVEL level;
    tessellation->GetLevel(&level);
    level = (level == T_LEVEL_2X) ? T_LEVEL_4X : T_LEVEL_2X;
    ADLX_RESULT res = tessellation->SetLevel(level);
    std::cout << "\tSet level: " << Levels.find(level)->second << " res is " << res << std::endl;
}

int WaitAndExit(const char* msg, const int retCode)
{
    // Print out the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display tessellation support" << std::endl;
    std::cout << "\t->Press 2 to get tessellation state" << std::endl;
    std::cout << "\t->Press 3 to set tessellation mode: AMD optimized" << std::endl;
    std::cout << "\t->Press 4 to set tessellation mode: Use application settings" << std::endl;
    std::cout << "\t->Press 5 to set tessellation mode: Override application settings" << std::endl;

    std::cout << "\t->Press 6 to set tessellation change level" << std::endl;

    std::cout << "\t->Press Q/q quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DTessellationPtr& tessellation)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display tessellation support
        case '1':
            ShowSupport(tessellation);
            break;

            // Get and display current tessellation state
        case '2':
            GetState(tessellation);
            break;

            // Set tessellation mode
        case '3':
        case '4':
        case '5':
            SetMode(tessellation, num - '3');
            break;

            // Set anti-aliasing level
        case '6':
            SetLevel(tessellation);
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
