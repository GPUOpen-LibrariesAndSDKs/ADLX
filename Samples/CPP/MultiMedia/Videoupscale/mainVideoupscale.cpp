//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVideoupscale.cpp
/// \brief Demonstrates how to control Videoupscale when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IMultiMedia.h"
#include "SDK/Include/ISystem2.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLXVideoUpscalePtr& videoupscale);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display video upscale support
void ShowVideoupscaleSupport(const IADLXVideoUpscalePtr& videoupscale);

// Display current video upscale state
void GetVideoupscaleState(const IADLXVideoUpscalePtr& videoupscale);

// Set video upscale state
void SetVideoupscaleState(const IADLXVideoUpscalePtr& videoupscale, int index);

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

        // Get IADLXSystem2 interface via IADLXSystem::QueryInterface
        IADLXSystem2Ptr system2;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));

        if (!gpus->Empty() && ADLX_SUCCEEDED(res))
        {
            // Get multimedia services 
            IADLXMultimediaServicesPtr MultimediaService;
            res = system2->GetMultimediaServices(&MultimediaService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get GPU interface
                IADLXGPUPtr gpuInfo;
                adlx_uint index = 0;
                res = gpus->At(index, &gpuInfo);

                // Get video upscale interface
                IADLXVideoUpscalePtr VideoUpscale;
                res = MultimediaService->GetVideoUpscale(gpuInfo, &VideoUpscale);
                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(VideoUpscale);
                }

                else
                {
                    std::cout << "Failed to get 3DSettings services: " << res << std::endl;
                }
            }
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

void ShowVideoupscaleSupport(const IADLXVideoUpscalePtr& videoupscale)
{
    adlx_bool supported = false;
    ADLX_RESULT res = videoupscale->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetVideoupscaleState(const IADLXVideoUpscalePtr& videoupscale)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = videoupscale->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
        std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
    adlx_int sharpness;
    ADLX_IntRange sharpnessRange;
    res = videoupscale->GetSharpness(&sharpness);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tCurrent sharpness:" << sharpness << std::endl;
    res = videoupscale->GetSharpnessRange(&sharpnessRange);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tsharpnesslimit [ " << sharpnessRange.minValue << " ," << sharpnessRange.maxValue << " ], step: " << sharpnessRange.step << std::endl;
}

void SetVideoupscaleState(const IADLXVideoUpscalePtr& videoupscale, int index)
{
    ADLX_RESULT res = videoupscale->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;

    if (index == 0 && ADLX_SUCCEEDED(res))
    {
        adlx_int sharpness;
        ADLX_IntRange sharpnessRange;
        ADLX_RESULT res1 = videoupscale->GetSharpness(&sharpness);
        ADLX_RESULT res2 = videoupscale->GetSharpnessRange(&sharpnessRange);
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            if (sharpness != sharpnessRange.minValue)
            {
                res = videoupscale->SetSharpness(sharpnessRange.minValue);
                std::cout << "\tSet minimum sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
            }
            else
            {
                res = videoupscale->SetSharpness(sharpnessRange.maxValue);
                std::cout << "\tSet maximum sharpness limit: return code is: " << res << "(0 means success)" << std::endl;
            }
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

    std::cout << "\t->Press 1 to display Videoupscale support" << std::endl;
    std::cout << "\t->Press 2 to display current Videoupscale state" << std::endl;
    std::cout << "\t->Press 3 to enable Videoupscale" << std::endl;
    std::cout << "\t->Press 4 to disable Videoupscale" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLXVideoUpscalePtr& videoupscale)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display video upscale support
        case '1':
            ShowVideoupscaleSupport(videoupscale);
            break;

            // Display current video upscale state
        case '2':
            GetVideoupscaleState(videoupscale);
            break;

            // Set video upscale
        case '3':
        case '4':
            SetVideoupscaleState(videoupscale, num - '3');
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
