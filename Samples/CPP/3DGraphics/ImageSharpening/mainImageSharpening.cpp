//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainImageSharpening.cpp
/// \brief Demonstrates how to access AMD Radeon Image Sharpening options, and perform related testing when programming with ADLX.

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

// Display Image Sharpening support
void ShowImageSharpenSupport(const IADLX3DImageSharpeningPtr& d3dImageSharpen);

// Get current Image Sharpening state and additional information
void GetImageSharpenState(const IADLX3DImageSharpeningPtr& d3dImageSharpen);

// Set Image Sharpening state
void SetImageSharpenState(const IADLX3DImageSharpeningPtr& d3dImageSharpen, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DImageSharpeningPtr& d3dImageSharpen);

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
                    // Get Image Sharpening interface
                    IADLX3DImageSharpeningPtr d3dImageSharpen;
                    res = d3dSettingSrv->GetImageSharpening(gpuInfo, &d3dImageSharpen);
                    if (ADLX_SUCCEEDED(res))
                    {
                        MainMenu();
                        MenuControl(d3dImageSharpen);
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

void ShowImageSharpenSupport(const IADLX3DImageSharpeningPtr& d3dImageSharpen)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dImageSharpen->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: "<< res << "(0 means success)" << std::endl;
}

void GetImageSharpenState(const IADLX3DImageSharpeningPtr& d3dImageSharpen)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dImageSharpen->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << ", return code is: "<< res << "(0 means success)" << std::endl;
    adlx_int sharpness;
    ADLX_IntRange sharpnessRange  = {0};
    res = d3dImageSharpen->GetSharpness(&sharpness);
    std::cout << "\tCurrent Sharpness:" << sharpness
              << ", return code is: "<< res << "(0 means success)" << std::endl;
    res = d3dImageSharpen->GetSharpnessRange(&sharpnessRange);
    std::cout << "\tSharpness limit [ " << sharpnessRange.minValue << " ," << sharpnessRange.maxValue << " ], step: " << sharpnessRange.step 
              << ", return code is: "<< res << "(0 means success)" << std::endl;
}

void SetImageSharpenState(const IADLX3DImageSharpeningPtr& d3dImageSharpen, int index)
{
    ADLX_RESULT res = d3dImageSharpen->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int sharpness;
        ADLX_IntRange sharpnessRange  = {0};
        d3dImageSharpen->GetSharpness(&sharpness);
        d3dImageSharpen->GetSharpnessRange(&sharpnessRange);
        if (sharpness != sharpnessRange.minValue)
        {
            res = d3dImageSharpen->SetSharpness(sharpnessRange.minValue);
            std::cout << "\tUse minimum Sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
        }
        else
        {
            res = d3dImageSharpen->SetSharpness(sharpnessRange.maxValue);
            std::cout << "\tUse maximum Sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
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

    std::cout << "\t->Press 1 to display Image Sharpening support" << std::endl;
    std::cout << "\t->Press 2 to get current Image Sharpening state and additional information" << std::endl;
    std::cout << "\t->Press 3 to enable and configure Image Sharpening" << std::endl;
    std::cout << "\t->Press 4 to disable Image Sharpening" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DImageSharpeningPtr& d3dImageSharpen)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Image Sharpening support
        case '1':
            ShowImageSharpenSupport(d3dImageSharpen);
            break;

            // Get current Image Sharpening state and additional information
        case '2':
            GetImageSharpenState(d3dImageSharpen);
            break;

            // Set Image Sharpening state
        case '3':
        case '4':
            SetImageSharpenState(d3dImageSharpen, num - '3');
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