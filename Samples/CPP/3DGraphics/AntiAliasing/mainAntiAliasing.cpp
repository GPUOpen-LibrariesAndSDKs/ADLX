//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiAliasing.cpp
/// \brief Demonstrates how to access anti-aliasing options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <map>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display anti-aliasing support
void ShowAntiAliasingSupport(const IADLX3DAntiAliasingPtr& antiAliasing);

// Display anti-aliasing current state
void GetAntiAliasingState(const IADLX3DAntiAliasingPtr& antiAliasing);

// Set anti-aliasing mode
void SetAntiAliasingMode(const IADLX3DAntiAliasingPtr& antiAliasing, int index);

// Set anti-aliasing method
void SetAntiAliasingMethod(const IADLX3DAntiAliasingPtr& antiAliasing);

// Set anti-aliasing level
void SetAntiAliasingLevel(const IADLX3DAntiAliasingPtr& antiAliasing);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DAntiAliasingPtr& antiAliasing);

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
        // GetGPUs
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
                    // Get AntiAliasing interface
                    IADLX3DAntiAliasingPtr antiAliasing;
                    res = d3dSettingSrv->GetAntiAliasing(gpuInfo, &antiAliasing);
                    if (ADLX_SUCCEEDED(res))
                    {
                        MainMenu();
                        MenuControl(antiAliasing);
                    }
                }
            }
            else
            {
                std::cout << "Failed to get the 3DSettings Services" << std::endl;
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

    // Pause to see the print out
    system("pause");

    return 0;
}

static const std::map<ADLX_ANTI_ALIASING_MODE, const char*> antiAliasingMode =
    {
        {AA_MODE_USE_APP_SETTINGS, "Use application settings"},
        {AA_MODE_ENHANCE_APP_SETTINGS, "Enhance application settings"},
        {AA_MODE_OVERRIDE_APP_SETTINGS, "Override application settings"}};

static const std::map<ADLX_ANTI_ALIASING_METHOD, const char*> antiAliasingMethod =
    {
        {AA_METHOD_MULTISAMPLING, "Muti-Sampling"},
        {AA_METHOD_ADAPTIVE_MULTISAMPLING, "Adaptive Muti-Sampling"},
        {AA_METHOD_SUPERSAMPLING, "Super Sampling"}};

static const std::map<ADLX_ANTI_ALIASING_LEVEL, const char*> antiAliasingLevel =
    {
        {AA_LEVEL_INVALID, "Level Invalid"},
        {AA_LEVEL_2X, "2X"},
        {AA_LEVEL_2XEQ, "2XEQ"},
        {AA_LEVEL_4X, "4X"},
        {AA_LEVEL_4XEQ, "4XEQ"},
        {AA_LEVEL_8X, "8X"},
        {AA_LEVEL_8XEQ, "8XEQ"}};

void ShowAntiAliasingSupport(const IADLX3DAntiAliasingPtr& antiAliasing)
{
    adlx_bool supported = false;
    antiAliasing->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetAntiAliasingState(const IADLX3DAntiAliasingPtr& antiAliasing)
{
    ADLX_ANTI_ALIASING_MODE mode;
    antiAliasing->GetMode(&mode);
    ADLX_ANTI_ALIASING_METHOD method;
    antiAliasing->GetMethod(&method);
    ADLX_ANTI_ALIASING_LEVEL level;
    antiAliasing->GetLevel(&level);
    std::cout << "\tMode: " << antiAliasingMode.find(mode)->second << std::endl
              << "\tMethod: " << antiAliasingMethod.find(method)->second << std::endl
              << "\tLevel: " << antiAliasingLevel.find(level)->second << std::endl;
}

void SetAntiAliasingMode(const IADLX3DAntiAliasingPtr& antiAliasing, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    ADLX_ANTI_ALIASING_MODE mode = AA_MODE_USE_APP_SETTINGS;
    mode = (ADLX_ANTI_ALIASING_MODE)(mode + index);
    res = antiAliasing->SetMode(mode);
    std::cout << "\tReturn code is : " << res << "(0 means success)" << std::endl;
}

void SetAntiAliasingMethod(const IADLX3DAntiAliasingPtr& antiAliasing)
{
    ADLX_ANTI_ALIASING_METHOD method = AA_METHOD_MULTISAMPLING;
    antiAliasing->GetMethod(&method);
    method = (ADLX_ANTI_ALIASING_METHOD)((method + 1) % 3);
    ADLX_RESULT res = antiAliasing->SetMethod(method);
    std::cout << "\tSet method: " << antiAliasingMethod.find(method)->second << ", res is " << res << std::endl;
}

void SetAntiAliasingLevel(const IADLX3DAntiAliasingPtr& antiAliasing)
{
    ADLX_ANTI_ALIASING_LEVEL level;
    antiAliasing->GetLevel(&level);
    level = (level == AA_LEVEL_2X) ? AA_LEVEL_4X : AA_LEVEL_2X;
    ADLX_RESULT res = antiAliasing->SetLevel(level);
    std::cout << "\tSet level: " << antiAliasingLevel.find(level)->second << ", res is " << res << std::endl;
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
    std::cout << "\tChoose from the following options" << std::endl;

    std::cout << "\t->Press 1 to display anti-aliasing support" << std::endl;
    std::cout << "\t->Press 2 to display current anti-aliasing state" << std::endl;
    std::cout << "\t->Press 3 to set anti-aliasing mode: Use application settings" << std::endl;
    std::cout << "\t->Press 4 to set anti-aliasing mode: Enhance application settings" << std::endl;
    std::cout << "\t->Press 5 to set anti-aliasing mode: Override application settings" << std::endl;

    std::cout << "\t->Press 6 to change anti-aliasing method" << std::endl;
    std::cout << "\t->Press 7 to change anti-aliasing level" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DAntiAliasingPtr& antiAliasing)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display anti-aliasing support
        case '1':
            ShowAntiAliasingSupport(antiAliasing);
            break;

            // Display current anti-aliasing status
        case '2':
            GetAntiAliasingState(antiAliasing);
            break;

            // Set anti-aliasing mode
        case '3':
        case '4':
        case '5':
            SetAntiAliasingMode(antiAliasing, num - '3');
            break;

            // Set anti-aliasing method
        case '6':
            SetAntiAliasingMethod(antiAliasing);
            break;

            // Set anti-aliasing level
        case '7':
            SetAntiAliasingLevel(antiAliasing);
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
