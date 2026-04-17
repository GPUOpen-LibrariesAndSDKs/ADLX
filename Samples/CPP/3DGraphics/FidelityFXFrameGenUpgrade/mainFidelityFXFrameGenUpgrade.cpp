// FidelityFXFrameGenUpgrade.cpp : Source file for your target.
//

/// \file mainFidelityFXFrameGenUpgrade.cpp
/// \brief Demonstrates how to access AMD FidelityFX Frame Generation options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings3.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display FidelityFXFrameGenUpgrade support
void ShowFidelityFXFrameGenUpgradeSupport(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

// Display current FidelityFXFrameGenUpgrade state
void GetFidelityFXFrameGenUpgradeState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

// Set FidelityFXFrameGenUpgrade state
void SetFidelityFXFrameGenUpgradeState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade, int index);

// Get available FidelityFXFrameGenUpgrade ratios
void GetFidelityFXFrameGenUpgradeAvailableRatios(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

// Get current FidelityFXFrameGenUpgrade ratio
void GetFidelityFXFrameGenUpgradeRatioState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

// Set FidelityFXFrameGenUpgrade ratio
void SetFidelityFXFrameGenUpgradeRatioState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade);

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
            // Get FidelityFX Frame Generation Upgrade interface
            IADLX3DFidelityFXFrameGenUpgradePtr d3dFidelityFXFrameGenUpgrade;
            res = d3dSettingSrv3->GetFidelityFXFrameGenUpgrade(gpuInfo, &d3dFidelityFXFrameGenUpgrade);
            if (ADLX_SUCCEEDED(res)) {
                MainMenu();
                MenuControl(d3dFidelityFXFrameGenUpgrade);
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

    std::cout << "\t->Press 1 to display FidelityFX Frame Gen Upgrade support" << std::endl;
    std::cout << "\t->Press 2 to get current FidelityFX Frame Gen Upgrade state" << std::endl;
    std::cout << "\t->Press 3 to enable FidelityFX Frame Gen Upgrade" << std::endl;
    std::cout << "\t->Press 4 to disable FidelityFX Frame Gen Upgrade" << std::endl;
    std::cout << "\t->Press 5 to get available FidelityFX Frame Gen Upgrade ratios" << std::endl;
    std::cout << "\t->Press 6 to get current FidelityFX Frame Gen Upgrade ratio" << std::endl;
    std::cout << "\t->Press 7 to set FidelityFX Frame Gen Upgrade ratio" << std::endl;

    std::cout << "\t->Press Q/q to quit the application" << std::endl;
    std::cout << "\t->Press M/m to display menu options" << std::endl;
}

void MenuControl(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
    int num = 0;
    std::vector<ADLX_FFX_FRAME_GEN_RATIO>* ratios = nullptr;
    while ((num = getchar()) != 'q' && num != 'Q') {
        switch (num)
        {
        case '1':
            ShowFidelityFXFrameGenUpgradeSupport(d3dFidelityFXFrameGenUpgrade);
            break;

        case '2':
            GetFidelityFXFrameGenUpgradeState(d3dFidelityFXFrameGenUpgrade);
            break;

        case '3':
        case '4':
            SetFidelityFXFrameGenUpgradeState(d3dFidelityFXFrameGenUpgrade, num - '3');
            break;
        case '5':
            GetFidelityFXFrameGenUpgradeAvailableRatios(d3dFidelityFXFrameGenUpgrade);
            break;
        case '6':
            GetFidelityFXFrameGenUpgradeRatioState(d3dFidelityFXFrameGenUpgrade);
            break;
        case '7':
            SetFidelityFXFrameGenUpgradeRatioState(d3dFidelityFXFrameGenUpgrade);
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

void ShowFidelityFXFrameGenUpgradeSupport(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
    adlx_bool supported = false;
    ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsSupported: " << supported << std::endl;
}

void GetFidelityFXFrameGenUpgradeState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->IsEnabled(&enabled);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIsEnabled: " << enabled << std::endl;
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
}

void SetFidelityFXFrameGenUpgradeState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade, int index) {
    ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->SetEnabled(index == 0);
    std::cout << "\tReturn code is: " << res << "(0 means success)" << std::endl;
    if (ADLX_SUCCEEDED(res)) {
        adlx_bool enabled = false;
        res = d3dFidelityFXFrameGenUpgrade->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tFidelityFX Frame Generation Upgrade is now: " << (enabled ? "Enabled" : "Disabled") << std::endl;
    }
    else
        std::cout << "\tFailed to set FidelityFX Frame Generation Upgrade state." << std::endl;
}

void GetFidelityFXFrameGenUpgradeAvailableRatios(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
   IADLX3DFidelityFXFrameGenUpgradeRatioOptionList* ratioList = nullptr;

   ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->GetAvailableRatios(&ratioList);

   if (ADLX_SUCCEEDED(res) && ratioList != nullptr) {
       std::vector<ADLX_FFX_FRAME_GEN_RATIO> ratios;
       adlx_uint size = ratioList->Size();
       std::cout << "Available FidelityFX Frame Gen Upgrade ratio options count: " << size << std::endl;

       for (adlx_uint i = 0; i < size; ++i) {
           IADLX3DFidelityFXFrameGenUpgradeRatioOption* ratioOption = nullptr;
           res = ratioList->At(i, &ratioOption);

           if (ADLX_SUCCEEDED(res) && ratioOption != nullptr) {
               ADLX_FFX_FRAME_GEN_RATIO ratio;
               res = ratioOption->Ratio(&ratio);

               if (ADLX_SUCCEEDED(res)) {
                   ratios.push_back(ratio);
                   std::cout << "Option " << i + 1 << ": Ratio = " << ratio << std::endl;
               }
               ratioOption->Release();

           } else {
               std::cout << "Failed to get ratio option at index " << i << ": " << res << std::endl;
           }
       }
       ratioList->Release();
   } else {
       std::cout << "Failed to get available FidelityFX Frame Gen Upgrade ratios: " << res << std::endl;
   }
}

void GetFidelityFXFrameGenUpgradeRatioState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
    ADLX_FFX_FRAME_GEN_RATIO ratio;
    ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->GetRatio(&ratio);
    if (ADLX_SUCCEEDED(res)) {
        std::cout << "Current FidelityFX Frame Gen Upgrade ratio: " << ratio << std::endl;
    }
    else {
        std::cout << "Failed to get current FidelityFX Frame Gen Upgrade ratio: " << res << std::endl;
    }
}

void SetFidelityFXFrameGenUpgradeRatioState(const IADLX3DFidelityFXFrameGenUpgradePtr& d3dFidelityFXFrameGenUpgrade) {
    IADLX3DFidelityFXFrameGenUpgradeRatioOptionListPtr ratioList;
    ADLX_RESULT res = d3dFidelityFXFrameGenUpgrade->GetAvailableRatios(&ratioList);

    if (ADLX_SUCCEEDED(res) && ratioList != nullptr) {
        adlx_uint size = ratioList->Size();
        if (size > 0) {
            std::cout << "Available FidelityFX Frame Gen Upgrade ratios:" << std::endl;
            // Set the first available ratio as the current ratio
            IADLX3DFidelityFXFrameGenUpgradeRatioOptionPtr ratioOption;
            res = ratioList->At(0, &ratioOption);
            if (ADLX_SUCCEEDED(res) && ratioOption != nullptr) {
                ADLX_FFX_FRAME_GEN_RATIO ratio = FFX_FRAME_GEN_UNKNOWN;
                ratioOption->Ratio(&ratio);
                if (ADLX_SUCCEEDED(res)) {
                    std::cout << "Ratio = " << ratio << std::endl;
                }
                res = d3dFidelityFXFrameGenUpgrade->SetRatio(ratio);
                if (ADLX_SUCCEEDED(res)) {
                    std::cout << "FidelityFX Frame Gen Upgrade ratio set successfully." << std::endl;
                }
                else {
                    std::cout << "Failed to set FidelityFX Frame Gen Upgrade ratio: " << res << std::endl;
                }
            }
            else {
                std::cout << "Failed to get FidelityFX Frame Gen Upgrade ratio at index 0: " << res << std::endl;
            }
        }
        else {
            std::cout << "No available FidelityFX Frame Gen Upgrade ratios to set." << std::endl;
        }
    }
    else {
        std::cout << "Failed to get available FidelityFX Frame Gen Upgrade ratios: " << res << std::endl;
    }
}