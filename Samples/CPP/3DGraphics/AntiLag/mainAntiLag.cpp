//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiLag.cpp
/// \brief Demonstrates how to access AMD Radeon Anti-Lag options, and perform related testing when programming with ADLX.

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

// Display Anti-Lag support
void ShowAntiLagSupport(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1);

// Display current Anti-Lag state
void GetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1);

// Set Anti-Lag state
void SetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1, int index);

// Display current Anti-Lag state
void GetAntiLagLevel(const IADLX3DAntiLag1Ptr& d3dAntiLag1);

// Set Anti-Lag state
void SetAntiLagLevel(const IADLX3DAntiLag1Ptr& d3dAntiLag1, ADLX_ANTILAG_STATE level);

// Menu
void MainMenu(bool alnSupported);

// Menu control
void MenuControl(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;
    
    ADLX_RESULT resALN = ADLX_FAIL;
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

            // Get AntiLag interface
            IADLX3DAntiLagPtr d3dAntiLag;
            
            res = d3dSettingSrv->GetAntiLag(gpuInfo, &d3dAntiLag);
            IADLX3DAntiLag1Ptr d3dAntiLag1(d3dAntiLag);
            if (ADLX_SUCCEEDED(res))
            {
                //resALN = d3dAntiLag->QueryInterface(IADLX3DAntiLag1::IID(), reinterpret_cast<void**>(&d3dAntiLag1));               
             
                MainMenu(d3dAntiLag1 != NULL);
                MenuControl(d3dAntiLag, d3dAntiLag1);
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

void ShowAntiLagSupport(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1)
{
    adlx_bool supported = false;
    if (d3dAntiLag1 != NULL)
        d3dAntiLag1->IsSupported(&supported);
    else
        d3dAntiLag->IsSupported(&supported);
    std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1)
{
    adlx_bool enabled = false;
    if (d3dAntiLag1 != NULL)
        d3dAntiLag1->IsEnabled(&enabled);
    else
        d3dAntiLag->IsEnabled(&enabled);
    std::cout << "\tIsEnabled: " << enabled << std::endl;
}

void SetAntiLagState(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1, int index)
{
    ADLX_RESULT res;
    if (d3dAntiLag1 != NULL)
        res = d3dAntiLag1->SetEnabled(index == 0);
    else
        res = d3dAntiLag->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void GetAntiLagLevel(const IADLX3DAntiLag1Ptr& d3dAntiLag1)
{
    ADLX_ANTILAG_STATE level ;
    ADLX_RESULT res = d3dAntiLag1->GetLevel(&level);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tLevel: " << (level == ADLX_ANTILAG_STATE::ANTILAG ? "Anti-Lag" : "Anti-Lag Next") << std::endl;
}

void SetAntiLagLevel(const IADLX3DAntiLag1Ptr& d3dAntiLag1, ADLX_ANTILAG_STATE level)
{
    ADLX_RESULT res = d3dAntiLag1->SetLevel(level);
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

void MainMenu(bool alnSupported)
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display Anti-Lag support" << std::endl;
    std::cout << "\t->Press 2 to display current Anti-Lag state" << std::endl;    
    std::cout << "\t->Press 3 to enable Anti-Lag" << std::endl;
    std::cout << "\t->Press 4 to disable Anti-Lag" << std::endl;
    if (alnSupported)
    {
        std::cout << "\t->Press 5 to Get Level" << std::endl;
        std::cout << "\t->Press 6 to Set Level to Anti-Lag" << std::endl;
        std::cout << "\t->Press 7 to Set Level to Anti-Lag Next" << std::endl;
    }
    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DAntiLagPtr& d3dAntiLag, const IADLX3DAntiLag1Ptr& d3dAntiLag1 )
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Anti-Lag support
        case '1':
            ShowAntiLagSupport(d3dAntiLag, d3dAntiLag1);
            break;

            // Display current Anti-Lag state
        case '2':
            GetAntiLagState(d3dAntiLag, d3dAntiLag1);
            break;

            // Set Anti-Lag state
        case '3':
        case '4':
            SetAntiLagState(d3dAntiLag, d3dAntiLag1, num - '3');
            break;

        case '5':
            GetAntiLagLevel(d3dAntiLag1);
            break;
        case '6':
            SetAntiLagLevel(d3dAntiLag1, ADLX_ANTILAG_STATE::ANTILAG);
            break;
        case '7':
            SetAntiLagLevel(d3dAntiLag1, ADLX_ANTILAG_STATE::ANTILAGNEXT);
            break;
        // Display menu options
        case 'm':
        case 'M':
            MainMenu(d3dAntiLag1 != NULL ? true : false);
            break;
        default:
            break;
        }
    }
}
