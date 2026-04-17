//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVideoSuperResolution.cpp
/// \brief Demonstrates how to control VideoSuperResolution when programming with ADLX.

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
void MenuControl(const IADLXVideoSuperResolutionPtr& videoSuperResolution);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display video Super Resolution support
void ShowVideoSuperResolutionSupport(const IADLXVideoSuperResolutionPtr& videoSuperResolution);

// Display current video Super Resolution state
void GetVideoSuperResolutionState(const IADLXVideoSuperResolutionPtr& videoSuperResolution);

// Set video Super Resolution state
void SetVideoSuperResolutionState(const IADLXVideoSuperResolutionPtr& videoSuperResolution, int index);

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
                const char* gpuName = nullptr;
                res = gpuInfo->Name(&gpuName);
                std::cout << "\t" << gpuName << " is selected." << std::endl;

                // Get video Super Resolution interface
                IADLXVideoSuperResolutionPtr videoSuperResolution;
                res = MultimediaService->GetVideoSuperResolution(gpuInfo, &videoSuperResolution);
                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(videoSuperResolution);
                }
            }

        }
        else
        {
            std::cout << "Failed to get system2 res: " << res << std::endl;
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

void ShowVideoSuperResolutionSupport(const IADLXVideoSuperResolutionPtr& videoSuperResolution)
{
    adlx_bool supported = false;
    ADLX_RESULT res = videoSuperResolution->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetVideoSuperResolutionState(const IADLXVideoSuperResolutionPtr& videoSuperResolution)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = videoSuperResolution->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
        std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetVideoSuperResolutionState(const IADLXVideoSuperResolutionPtr& VideoSuperResolution, int index)
{
    ADLX_RESULT res = VideoSuperResolution->SetEnabled(index == 0);
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

    std::cout << "\t->Press 1 to display VideoSuperResolution support" << std::endl;
    std::cout << "\t->Press 2 to display current VideoSuperResolution state" << std::endl;
    std::cout << "\t->Press 3 to enable VideoSuperResolution" << std::endl;
    std::cout << "\t->Press 4 to disable VideoSuperResolution" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLXVideoSuperResolutionPtr& videoSuperResolution)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display video Super Resolution support
        case '1':
            ShowVideoSuperResolutionSupport(videoSuperResolution);
            break;

            // Display current video Super Resolution state
        case '2':
            GetVideoSuperResolutionState(videoSuperResolution);
            break;

            // Set video Super Resolution
        case '3':
        case '4':
            SetVideoSuperResolutionState(videoSuperResolution, num - '3');
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
