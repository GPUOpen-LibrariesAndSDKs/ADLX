
//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainResetShaderCache.cpp
/// \brief Demonstrates how to access reset shader cache options, and perform related testing when programming with ADLX.

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

// Display reset shader cache support
void ShowSupport(const IADLX3DResetShaderCachePtr& resetShaderCache);

// Reset GPU shader cache
void ResetShaderCache(const IADLX3DResetShaderCachePtr& resetShaderCache);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DResetShaderCachePtr& resetShaderCache);

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

            // Get ResetShaderCache interface
            IADLX3DResetShaderCachePtr resetShaderCache;
            res = d3dSettingSrv->GetResetShaderCache(gpuInfo, &resetShaderCache);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(resetShaderCache);
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

void ShowSupport(const IADLX3DResetShaderCachePtr& resetShaderCache)
{
    adlx_bool supported = false;
    ADLX_RESULT res = resetShaderCache->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << ", return code is: " << res << "(0 means success)" << std::endl;
}

void ResetShaderCache(const IADLX3DResetShaderCachePtr& resetShaderCache)
{
    ADLX_RESULT res = resetShaderCache->ResetShaderCache();
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
    std::cout << "\t->Press 1 to display reset shader cache support" << std::endl;
    std::cout << "\t->Press 2 to reset GPU shader cache" << std::endl;
    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DResetShaderCachePtr& resetShaderCache)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display reset shader cache support
        case '1':
            ShowSupport(resetShaderCache);
            break;

            // Reset GPU shader cache
        case '2':
            ResetShaderCache(resetShaderCache);
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
