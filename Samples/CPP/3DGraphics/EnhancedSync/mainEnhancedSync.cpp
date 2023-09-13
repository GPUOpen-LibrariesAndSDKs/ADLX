//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainEnhancedSync.cpp
/// \brief Demonstrates how to access AMD Radeon Enhanced Sync options, and perform related testing when programming with ADLX.

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

// Display Enhanced Sync support
void ShowEnhancedSyncSupport(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync);

// Get current Enhanced Sync state
void GetEnhancedSyncState(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync);

// Set Enhanced Sync state
void SetEnhancedSyncState(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync);

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

            // Get EnhancedSync interface
            IADLX3DEnhancedSyncPtr d3dEnhancedSync;
            res = d3dSettingSrv->GetEnhancedSync(gpuInfo, &d3dEnhancedSync);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(d3dEnhancedSync);
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get 3DSettings services", 0);
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

void ShowEnhancedSyncSupport(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync)
{
    adlx_bool supported = false;
    d3dEnhancedSync->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetEnhancedSyncState(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync)
{
    adlx_bool enabled = false;
    d3dEnhancedSync->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << std::endl;
}

void SetEnhancedSyncState(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync, int index)
{
    ADLX_RESULT res = d3dEnhancedSync->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
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

    std::cout << "\t->Press 1 to display Enhanced Sync support" << std::endl;
    std::cout << "\t->Press 2 to get Enhanced Sync state" << std::endl;
    std::cout << "\t->Press 3 to enable Enhanced Sync" << std::endl;
    std::cout << "\t->Press 4 to disable Enhanced Sync" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DEnhancedSyncPtr& d3dEnhancedSync)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Enhanced Sync support
        case '1':
            ShowEnhancedSyncSupport(d3dEnhancedSync);
            break;

            // Get and display current Enhanced Sync state
        case '2':
            GetEnhancedSyncState(d3dEnhancedSync);
            break;

            // Set Enhanced Sync state
        case '3':
        case '4':
            SetEnhancedSyncState(d3dEnhancedSync, num - '3');
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
