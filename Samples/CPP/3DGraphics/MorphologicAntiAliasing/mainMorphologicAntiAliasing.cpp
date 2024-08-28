//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainMorphologicAntiAliasing.cpp
/// \brief Demonstrates how to access morphological anti-aliasing options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include <iostream>
#include <string>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display morphological anti-aliasing support
void ShowSupport(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing);

// Get current morphological anti-aliasing state of the GPU
void GetState(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing);

// Set morphological anti-aliasing state
void SetState(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing);

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
                    // Get MorphologicAntiAliasing interface
                    IADLX3DMorphologicalAntiAliasingPtr mAntiAliasing;
                    res = d3dSettingSrv->GetMorphologicalAntiAliasing(gpuInfo, &mAntiAliasing);
                    if (ADLX_SUCCEEDED(res))
                    {
                        MainMenu();
                        MenuControl(mAntiAliasing);
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
            std::cout << "Failed to get the GPU" << std::endl;
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

void ShowSupport(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing)
{
    adlx_bool supported = false;
    ADLX_RESULT res = mAntiAliasing->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

void GetState(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = mAntiAliasing->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << ", return code is: " << res << "(0 means success)" << std::endl;
}

void SetState(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing, int index)
{
    ADLX_RESULT res = mAntiAliasing->SetEnabled(index == 0);
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

    std::cout << "\t->Press 1 to display morphological anti-aliasing support" << std::endl;
    std::cout << "\t->Press 2 to get current morphological anti-aliasing state of the GPU" << std::endl;
    std::cout << "\t->Press 3 to enable morphological anti-aliasing" << std::endl;
    std::cout << "\t->Press 4 to disable morphological anti-aliasing" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DMorphologicalAntiAliasingPtr& mAntiAliasing)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display morphological anti-aliasing support
        case '1':
            ShowSupport(mAntiAliasing);
            break;

            // Get and display current morphological anti-aliasing state of the GPU
        case '2':
            GetState(mAntiAliasing);
            break;

            // Set morphological anti-aliasing state
        case '3':
        case '4':
            SetState(mAntiAliasing, num - '3');
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
