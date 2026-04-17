//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFidelityFXSuperResolution.cpp
/// \brief Demonstrates how to access AMD FidelityFX Super Resolution options, and perform related testing when programming with ADLX.

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

// Display FidelityFXSuperResolution support
void ShowFidelityFXSuperResolutionSupport(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution);

// Display current FidelityFXSuperResolution state
void GetFidelityFXSuperResolutionState(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution);

// Set FidelityFXSuperResolution state
void SetFidelityFXSuperResolutionState(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution, int index);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution);

int WaitAndExit(const char* msg, const int retCode) {
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

int main() {
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res)) {
        // Get GPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);
        IADLX3DSettingsServices3Ptr d3dSettingSrv3(d3dSettingSrv);

        if (!gpus->Empty() && ADLX_SUCCEEDED(res)) {
            // Get GPU interface
            IADLXGPUPtr gpuInfo;
            adlx_uint index = 0;
            res = gpus->At(index, &gpuInfo);
            const char* gpuName = nullptr;
            res = gpuInfo->Name(&gpuName);
            std::cout << "\t" << gpuName << " is selected." << std::endl;

            // Get FidelityFX Super Resolution interface
            IADLX3DFidelityFXSuperResolutionPtr d3dFidelityFXSuperResolution;
            res = d3dSettingSrv3->GetFidelityFXSuperResolution(gpuInfo, &d3dFidelityFXSuperResolution);
            if (ADLX_SUCCEEDED(res)) {
                MainMenu();
                MenuControl(d3dFidelityFXSuperResolution);
            }
        }
        else {
            std::cout << "Failed to get 3DSettings services: " << res << std::endl;
        }
    }
    else {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

void MainMenu() {
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display FidelityFX Super Resolution support" << std::endl;
    std::cout << "\t->Press 2 to get current FidelityFX Super Resolution state" << std::endl;
    std::cout << "\t->Press 3 to enable FidelityFX Super Resolution" << std::endl;
    std::cout << "\t->Press 4 to disable FidelityFX Super Resolution" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution) {
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            ShowFidelityFXSuperResolutionSupport(d3dFidelityFXSuperResolution);
            break;

        case '2':
            GetFidelityFXSuperResolutionState(d3dFidelityFXSuperResolution);
            break;
        case '3':
        case '4':
            SetFidelityFXSuperResolutionState(d3dFidelityFXSuperResolution, num - '3');
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

void ShowFidelityFXSuperResolutionSupport(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution) {
    adlx_bool supported = false;
    ADLX_RESULT res = d3dFidelityFXSuperResolution->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetFidelityFXSuperResolutionState(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution) {
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dFidelityFXSuperResolution->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetFidelityFXSuperResolutionState(const IADLX3DFidelityFXSuperResolutionPtr& d3dFidelityFXSuperResolution, int index) {
    ADLX_RESULT res = d3dFidelityFXSuperResolution->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
    if (ADLX_SUCCEEDED(res)) {
        adlx_bool enabled = false;
        res = d3dFidelityFXSuperResolution->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tFidelityFX Super Resolution is now: " << (enabled ? "Enabled" : "Disabled") << std::endl;
    }
    else
        std::cout << "\tFailed to set FidelityFX Super Resolution state." << std::endl;
}