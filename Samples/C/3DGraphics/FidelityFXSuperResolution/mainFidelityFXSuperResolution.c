//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFidelityFXSuperResolution.c
/// \brief Demonstrates how to access AMD FidelityFX Super Resolution options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings3.h"
#include <stdio.h>
#include <stdlib.h>

// Display FidelityFXSuperResolution support
void ShowFidelityFXSuperResolutionSupport(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution);

// Display current FidelityFXSuperResolution state
void GetFidelityFXSuperResolutionState(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution);

// Set FidelityFXSuperResolution state
void SetFidelityFXSuperResolutionState(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution, int index);

// Wait for exit with error message
int WaitAndExit(const char* msg, int retCode);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution);

int WaitAndExit(const char* msg, int retCode) {
    if (msg != NULL)
        printf("%s\n", msg);
    system("pause");
    return retCode;
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

            //Get FidelityFX SuperResolution interface
            IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution = NULL;
            res = d3dSettingSrv3->pVtbl->GetFidelityFXSuperResolution(d3dSettingSrv, gpu, &d3dFidelityFXSuperResolution);
            if (ADLX_SUCCEEDED(res)) {
                MainMenu();
                MenuControl(d3dFidelityFXSuperResolution);
            }

            // Release Boost interface
            if (d3dFidelityFXSuperResolution != NULL)
            {
                d3dFidelityFXSuperResolution->pVtbl->Release(d3dFidelityFXSuperResolution);
                d3dFidelityFXSuperResolution = NULL;
            }

            // Release the GPU interface
            if (gpu != NULL)
            {
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

void MainMenu() {
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to display FidelityFX Super Resolution support\n");
    printf("\t->Press 2 to get current FidelityFX Super Resolution state\n");
    printf("\t->Press 3 to enable FidelityFX Super Resolution\n");
    printf("\t->Press 4 to disable FidelityFX Super Resolution\n");
    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution) {
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q') {
        switch (num) {
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
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}

void ShowFidelityFXSuperResolutionSupport(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution) {
    adlx_bool supported = 0;
    ADLX_RESULT res = d3dFidelityFXSuperResolution->pVtbl->IsSupported(d3dFidelityFXSuperResolution, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetFidelityFXSuperResolutionState(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution) {
    adlx_bool enabled = 0;
    ADLX_RESULT res = d3dFidelityFXSuperResolution->pVtbl->IsEnabled(d3dFidelityFXSuperResolution, &enabled);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsEnabled: %d\n", enabled);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void SetFidelityFXSuperResolutionState(IADLX3DFidelityFXSuperResolution* d3dFidelityFXSuperResolution, int index) {
    ADLX_RESULT res = d3dFidelityFXSuperResolution->pVtbl->SetEnabled(d3dFidelityFXSuperResolution, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
    if (ADLX_SUCCEEDED(res)) {
        adlx_bool enabled = 0;
        res = d3dFidelityFXSuperResolution->pVtbl->IsEnabled(d3dFidelityFXSuperResolution, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tFidelityFX Super Resolution is now: %s\n", enabled ? "Enabled" : "Disabled");
    }
    else {
        printf("\tFailed to set FidelityFX Super Resolution state.\n");
    }
}
