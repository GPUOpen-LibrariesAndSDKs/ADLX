//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFidelityFXFrameGenUpgrade.c
/// \brief Demonstrates how to access AMD FidelityFX Frame Generation options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Display FidelityFXFrameGenUpgrade support
void ShowFidelityFXFrameGenUpgradeSupport(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

// Display current FidelityFXFrameGenUpgrade state
void GetFidelityFXFrameGenUpgradeState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

// Set FidelityFXFrameGenUpgrade state
void SetFidelityFXFrameGenUpgradeState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade, int index);

// Get available FidelityFXFrameGenUpgrade ratios
void GetFidelityFXFrameGenUpgradeAvailableRatios(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

// Get current FidelityFXFrameGenUpgrade ratio
void GetFidelityFXFrameGenUpgradeRatioState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

// Set FidelityFXFrameGenUpgrade ratio
void SetFidelityFXFrameGenUpgradeRatioState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

// Wait for exit with error message
int WaitAndExit(const char* msg, int retCode);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade);

void MainMenu() {
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to display FidelityFX Frame Gen Upgrade support\n");
    printf("\t->Press 2 to get current FidelityFX Frame Gen Upgrade state\n");
    printf("\t->Press 3 to enable FidelityFX Frame Gen Upgrade\n");
    printf("\t->Press 4 to disable FidelityFX Frame Gen Upgrade\n");
    printf("\t->Press 5 to get available FidelityFX Frame Gen Upgrade ratios\n");
    printf("\t->Press 6 to get current FidelityFX Frame Gen Upgrade ratio\n");
    printf("\t->Press 7 to set FidelityFX Frame Gen Upgrade ratio\n");
    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}


void MenuControl(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    int ch = 0;
    while ((ch = getchar()) != 'q' && ch != 'Q') {
        switch (ch) 
        {
        case '1':
            ShowFidelityFXFrameGenUpgradeSupport(pUpgrade);
            break;
        case '2':
            GetFidelityFXFrameGenUpgradeState(pUpgrade);
            break;
        case '3':
            SetFidelityFXFrameGenUpgradeState(pUpgrade, 1);
            break;
        case '4':
            SetFidelityFXFrameGenUpgradeState(pUpgrade, 0);
            break;
        case '5':
            GetFidelityFXFrameGenUpgradeAvailableRatios(pUpgrade);
            break;
        case '6':
            GetFidelityFXFrameGenUpgradeRatioState(pUpgrade);
            break;
        case '7':
            SetFidelityFXFrameGenUpgradeRatioState(pUpgrade);
            break;
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}

int main() {
    ADLX_RESULT res = ADLX_FAIL;

    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res)) {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        IADLX3DSettingsServices3* d3dSettingSrv3 = (IADLX3DSettingsServices3*)d3dSettingSrv;

        if (ADLX_SUCCEEDED(res)) {
            // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

            //Get FidelityFX Frame Generation Upgrade interface
            IADLX3DFidelityFXFrameGenUpgrade* d3dFidelityFXFrameGenUpgrade = NULL;
            res = d3dSettingSrv3->pVtbl->GetFidelityFXFrameGenUpgrade(d3dSettingSrv, gpu, &d3dFidelityFXFrameGenUpgrade);
            if (ADLX_SUCCEEDED(res)) {
                MainMenu();
                MenuControl(d3dFidelityFXFrameGenUpgrade);
            }

            // Release Boost interface
            if (d3dFidelityFXFrameGenUpgrade != NULL) {
                d3dFidelityFXFrameGenUpgrade->pVtbl->Release(d3dFidelityFXFrameGenUpgrade);
                d3dFidelityFXFrameGenUpgrade = NULL;
            }

            // Release the GPU interface
            if (gpu != NULL) {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else {
            printf("Failed to get 3DSettings services: %d\n", res);
        }
    }
    else {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    system("pause");
    return 0;
}

int WaitAndExit(const char* msg, int retCode)
{
    if (msg)
        printf("%s\n", msg);
    system("pause");
    return retCode;
}

void ShowFidelityFXFrameGenUpgradeSupport(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    adlx_bool supported = 0;
    ADLX_RESULT res = pUpgrade->pVtbl->IsSupported(pUpgrade, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetFidelityFXFrameGenUpgradeState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    adlx_bool enabled = 0;
    ADLX_RESULT res = pUpgrade->pVtbl->IsEnabled(pUpgrade, &enabled);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsEnabled: %d\n", enabled);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void SetFidelityFXFrameGenUpgradeState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade, int enable) {
    ADLX_RESULT res = pUpgrade->pVtbl->SetEnabled(pUpgrade, enable ? 1 : 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
    if (ADLX_SUCCEEDED(res)) {
        adlx_bool enabled = 0;
        res = pUpgrade->pVtbl->IsEnabled(pUpgrade, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tFidelityFX Frame Generation Upgrade is now: %s\n", enabled ? "Enabled" : "Disabled");
    }
    else {
        printf("\tFailed to set FidelityFX Frame Generation Upgrade state.\n");
    }
}


void GetFidelityFXFrameGenUpgradeAvailableRatios(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    IADLX3DFidelityFXFrameGenUpgradeRatioOptionList* ratioList = NULL;

    ADLX_RESULT res = pUpgrade->pVtbl->GetAvailableRatios(pUpgrade, &ratioList);

    if (ADLX_SUCCEEDED(res) && ratioList) {
        adlx_uint size = ratioList->pVtbl->Size(ratioList);
        printf("Available FidelityFX Frame Gen Upgrade ratio options count: %u\n", size);

        for (adlx_uint i = 0; i < size; ++i) {
            IADLX3DFidelityFXFrameGenUpgradeRatioOption* ratioOption = NULL;
            res = ratioList->pVtbl->At(ratioList, i, &ratioOption);

            if (ADLX_SUCCEEDED(res) && ratioOption) {
                ADLX_FFX_FRAME_GEN_RATIO ratio;
                res = ratioOption->pVtbl->Ratio(ratioOption, &ratio);

                if (ADLX_SUCCEEDED(res)) {
                    printf("Option %u: Ratio = %d\n", i + 1, ratio);
                }
                ratioOption->pVtbl->Release(ratioOption);
            }
            else {
                printf("Failed to get ratio option at index %u: %d\n", i, res);
            }
        }
        ratioList->pVtbl->Release(ratioList);
    }
    else {
        printf("Failed to get available FidelityFX Frame Gen Upgrade ratios: %d\n", res);
    }
}

void GetFidelityFXFrameGenUpgradeRatioState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    ADLX_FFX_FRAME_GEN_RATIO ratio;
    ADLX_RESULT res = pUpgrade->pVtbl->GetRatio(pUpgrade, &ratio);
    if (ADLX_SUCCEEDED(res)) {
        printf("Current FidelityFX Frame Gen Upgrade ratio: %d\n", ratio);
    }
    else {
        printf("Failed to get current FidelityFX Frame Gen Upgrade ratio: %d\n", res);
    }
}

void SetFidelityFXFrameGenUpgradeRatioState(IADLX3DFidelityFXFrameGenUpgrade* pUpgrade) {
    IADLX3DFidelityFXFrameGenUpgradeRatioOptionList* ratioList = NULL;
    ADLX_RESULT res = pUpgrade->pVtbl->GetAvailableRatios(pUpgrade, &ratioList);

    if (ADLX_SUCCEEDED(res) && ratioList) {
        adlx_uint size = ratioList->pVtbl->Size(ratioList);

        if (size > 0) {
            printf("Available FidelityFX Frame Gen Upgrade ratios:\n");
            IADLX3DFidelityFXFrameGenUpgradeRatioOption* ratioOption = NULL;
            res = ratioList->pVtbl->At(ratioList, 0, &ratioOption);

            if (ADLX_SUCCEEDED(res) && ratioOption) {
                ADLX_FFX_FRAME_GEN_RATIO ratio = FFX_FRAME_GEN_UNKNOWN;
                ratioOption->pVtbl->Ratio(ratioOption, &ratio);
                if (ADLX_SUCCEEDED(res)) {
                    printf("Ratio = %d\n", ratio);
                }

                res = pUpgrade->pVtbl->SetRatio(pUpgrade, ratio);
                if (ADLX_SUCCEEDED(res)) {
                    printf("FidelityFX Frame Gen Upgrade ratio set successfully.\n");
                }
                else {
                    printf("Failed to set FidelityFX Frame Gen Upgrade ratio: %d\n", res);
                }
                ratioOption->pVtbl->Release(ratioOption);
            }
            else {
                printf("Failed to get FidelityFX Frame Gen Upgrade ratio at index 0: %d\n", res);
            }
        }
        else {
            printf("No available FidelityFX Frame Gen Upgrade ratios to set.\n");
        }
        ratioList->pVtbl->Release(ratioList);
    }
    else {
        printf("Failed to get available FidelityFX Frame Gen Upgrade ratios: %d\n", res);
    }
}