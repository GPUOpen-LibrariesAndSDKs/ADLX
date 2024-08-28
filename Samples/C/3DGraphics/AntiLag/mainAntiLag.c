//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiLag.c
/// \brief Demonstrates how to access AMD Radeon Anti-Lag options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display Anti-Lag support
void ShowAntiLagSupport(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1);

// Display current Anti-Lag state
void GetAntiLagState(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1);

// Set Anti-Lag state
void SetAntiLagState(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1, int index);

// Display current Anti-Lag Level
void GetAntiLagLevel(IADLX3DAntiLag1* d3dAntiLag1);

// Set Anti-Lag Level
void SetAntiLagLevel(IADLX3DAntiLag1* d3dAntiLag1, ADLX_ANTILAG_STATE level);


// Menu
void MainMenu(int alnSupport);

// Menu control
void MenuControl(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

            // Get AntiLag interface
            IADLX3DAntiLag* d3dAntiLag = NULL;
            IADLX3DAntiLag1* d3dAntiLag1 = NULL;
            res = d3dSettingSrv->pVtbl->GetAntiLag(d3dSettingSrv, gpu, &d3dAntiLag);
            if (ADLX_SUCCEEDED(res))
            {
                // Get AntiLag1 interface                
                ADLX_RESULT resALN = d3dAntiLag->pVtbl->QueryInterface(d3dAntiLag, IID_IADLX3DAntiLag1, (void**)(&d3dAntiLag1));

                MainMenu(d3dAntiLag1 != NULL ? 1 : 0);
                MenuControl(d3dAntiLag, d3dAntiLag1);
            }

            // Release the d3dAntiLag interface
            if (d3dAntiLag != NULL)
            {
                d3dAntiLag->pVtbl->Release(d3dAntiLag);
                d3dAntiLag = NULL;
            }
            if (d3dAntiLag1 != NULL)
            {
                d3dAntiLag1->pVtbl->Release(d3dAntiLag1);
                d3dAntiLag1 = NULL;
            }
            // Release the GPU interface
            if (gpu != NULL)
            {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else
        {
            printf("Failed to get 3DSettings services\n");
        }

        // Release the 3DSettingsService interface
        if (d3dSettingSrv != NULL)
        {
            d3dSettingSrv->pVtbl->Release(d3dSettingSrv);
            d3dSettingSrv = NULL;
        }

        // Release the GPUs list interface
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowAntiLagSupport(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1)
{
    adlx_bool supported = false;
    if (d3dAntiLag1 != NULL)
        d3dAntiLag1->pVtbl->IsSupported(d3dAntiLag1, &supported);
    else
        d3dAntiLag->pVtbl->IsSupported(d3dAntiLag, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetAntiLagState(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1)
{
    adlx_bool enabled = false;
    if (d3dAntiLag1 != NULL)
        d3dAntiLag1->pVtbl->IsEnabled(d3dAntiLag1, &enabled);
    else
        d3dAntiLag->pVtbl->IsEnabled(d3dAntiLag, &enabled);
    printf("\tIsEnabled: %d\n", enabled);
}

void SetAntiLagState(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1, int index)
{
    ADLX_RESULT res;
    if (d3dAntiLag1 != NULL)
        res = d3dAntiLag1->pVtbl->SetEnabled(d3dAntiLag1, index == 0);
    else
        res = d3dAntiLag->pVtbl->SetEnabled(d3dAntiLag, index == 0);
    printf("\tReturn code is: %d (0 means Success)\n", res);
}

void GetAntiLagLevel(IADLX3DAntiLag1* d3dAntiLag1)
{
    ADLX_ANTILAG_STATE level = ANTILAG;
    ADLX_RESULT res = d3dAntiLag1->pVtbl->GetLevel(d3dAntiLag1, &level);
    if (ADLX_SUCCEEDED(res))
        printf("\tLevel: %s\n", (level == ANTILAG ? "Anti-Lag" : "Anti-Lag Next"));
}

void SetAntiLagLevel(IADLX3DAntiLag1* d3dAntiLag1, ADLX_ANTILAG_STATE level)
{
    ADLX_RESULT res = d3dAntiLag1->pVtbl->SetLevel(d3dAntiLag1, level == ANTILAGNEXT);
    printf("\tReturn code is: %d (0 means Success)\n", res);
}

void MainMenu(int alnSupport)
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Anti-Lag support\n");
    printf("\t->Press 2 to display current Anti-Lag state\n");
    printf("\t->Press 3 to enable Anti-Lag\n");
    printf("\t->Press 4 to disable Anti-Lag\n");
    if (alnSupport == 1)
    {
        printf("\t->Press 5 to Get Anti-Lag Level\n");
        printf("\t->Press 6 to Set Anti-Lag level to Anti-Lag\n");
        printf("\t->Press 7 to Set Anti-Lag level to Anti-Lag Next\n");
    }
    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DAntiLag* d3dAntiLag, IADLX3DAntiLag1* d3dAntiLag1)
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
            SetAntiLagLevel(d3dAntiLag1, ANTILAG);
            break;
        case '7':
            SetAntiLagLevel(d3dAntiLag1, ANTILAGNEXT);
            break;
        // Display menu options
        case 'm':
        case 'M':
            MainMenu(d3dAntiLag1 != NULL ? 1 : 0);
            break;
        default:
            break;
        }
    }
}
