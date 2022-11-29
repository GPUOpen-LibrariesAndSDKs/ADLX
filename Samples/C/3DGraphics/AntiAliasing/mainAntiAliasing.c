//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAntiAliasing.c
/// \brief Demonstrates how to access anti-aliasing options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display anti-aliasing support
void ShowAntiAliasingSupport(IADLX3DAntiAliasing* antiAliasing);

// Display current anti-aliasing state
void GetAntiAliasingState(IADLX3DAntiAliasing* antiAliasing);

// Set anti-aliasing mode
void SetAntiAliasingMode(IADLX3DAntiAliasing* antiAliasing, int index);

// Set anti-aliasing method
void SetAntiAliasingMethod(IADLX3DAntiAliasing* antiAliasing);

// Set anti-aliasing level
void SetAntiAliasingLevel(IADLX3DAntiAliasing* antiAliasing);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DAntiAliasing* antiAliasing);

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

            // Get AntiAliasing interface
            IADLX3DAntiAliasing* antiAliasing = NULL;
            res = d3dSettingSrv->pVtbl->GetAntiAliasing(d3dSettingSrv, gpu, &antiAliasing);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(antiAliasing);
            }

            // Release the AntiAliasing interface
            if (antiAliasing != NULL)
            {
                antiAliasing->pVtbl->Release(antiAliasing);
                antiAliasing = NULL;
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

static char* getModeStr(ADLX_ANTI_ALIASING_MODE mode)
{
    switch (mode)
    {
    case AA_MODE_USE_APP_SETTINGS:
        return "Use application settings";
    case AA_MODE_ENHANCE_APP_SETTINGS:
        return "Enhance application settings";
    case AA_MODE_OVERRIDE_APP_SETTINGS:
        return "Override application settings";
    default:
        return "UNKNOWN";
    }
};

static char* getMethodStr(ADLX_ANTI_ALIASING_METHOD method)
{
    switch (method)
    {
    case AA_METHOD_MULTISAMPLING:
        return "Muti-Sampling";
    case AA_METHOD_ADAPTIVE_MULTISAMPLING:
        return "Adaptive Muti-Sampling";
    case AA_METHOD_SUPERSAMPLING:
        return "Super Sampling";
    default:
        return "UNKNOWN";
    }
};

static char* getLevelStr(ADLX_ANTI_ALIASING_LEVEL level)
{
    switch (level)
    {
    case AA_LEVEL_INVALID:
        return "Level Invalid";
    case AA_LEVEL_2X:
        return "2X";
    case AA_LEVEL_2XEQ:
        return "2XEQ";
    case AA_LEVEL_4X:
        return "4X";
    case AA_LEVEL_4XEQ:
        return "4XEQ";
    case AA_LEVEL_8X:
        return "8X";
    case AA_LEVEL_8XEQ:
        return "8XEQ";
    default:
        return "UNKNOWN";
    }
};

void ShowAntiAliasingSupport(IADLX3DAntiAliasing* antiAliasing)
{
    adlx_bool supported = false;
    antiAliasing->pVtbl->IsSupported(antiAliasing, &supported);
    printf("\tIsSupported: %d\n", supported);
}

void GetAntiAliasingState(IADLX3DAntiAliasing* antiAliasing)
{
    ADLX_ANTI_ALIASING_MODE mode;
    antiAliasing->pVtbl->GetMode(antiAliasing, &mode);
    ADLX_ANTI_ALIASING_METHOD method;
    antiAliasing->pVtbl->GetMethod(antiAliasing, &method);
    ADLX_ANTI_ALIASING_LEVEL level;
    antiAliasing->pVtbl->GetLevel(antiAliasing, &level);
    printf("\tMode: %s\n\tMethod: %s\n\tLevel: %s\n", getModeStr(mode), getMethodStr(method), getLevelStr(level));
}

void SetAntiAliasingMode(IADLX3DAntiAliasing* antiAliasing, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    ADLX_ANTI_ALIASING_MODE mode = AA_MODE_USE_APP_SETTINGS;
    mode = (ADLX_ANTI_ALIASING_MODE)(mode + index);
    res = antiAliasing->pVtbl->SetMode(antiAliasing, mode);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void SetAntiAliasingMethod(IADLX3DAntiAliasing* antiAliasing)
{
    ADLX_ANTI_ALIASING_METHOD method = AA_METHOD_MULTISAMPLING;
    antiAliasing->pVtbl->GetMethod(antiAliasing, &method);
    method = (ADLX_ANTI_ALIASING_METHOD)((method + 1) % 3);
    ADLX_RESULT res = antiAliasing->pVtbl->SetMethod(antiAliasing, method);
    printf("\tSet method: %s, res is: %d\n", getMethodStr(method), res);
}

void SetAntiAliasingLevel(IADLX3DAntiAliasing* antiAliasing)
{
    ADLX_ANTI_ALIASING_LEVEL level;
    antiAliasing->pVtbl->GetLevel(antiAliasing, &level);
    level = (level == AA_LEVEL_2X) ? AA_LEVEL_4X : AA_LEVEL_2X;
    ADLX_RESULT res = antiAliasing->pVtbl->SetLevel(antiAliasing, level);
    printf("\tSet level: %s, res is: %d\n", getLevelStr(level), res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display anti-aliasing support\n");
    printf("\t->Press 2 to display current anti-aliasing state\n");
    printf("\t->Press 3 to set anti-aliasing mode: Use application settings\n");
    printf("\t->Press 4 to set anti-aliasing mode: Enhance application settings\n");
    printf("\t->Press 5 to set anti-aliasing mode: Override application settings\n");

    printf("\t->Press 6 to change anti-aliasing method\n");
    printf("\t->Press 7 to change anti-aliasing level\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DAntiAliasing* antiAliasing)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display anti-aliasing support
        case '1':
            ShowAntiAliasingSupport(antiAliasing);
            break;

            // Display current anti-aliasing status
        case '2':
            GetAntiAliasingState(antiAliasing);
            break;

            // Set anti-aliasing mode
        case '3':
        case '4':
        case '5':
            SetAntiAliasingMode(antiAliasing, num - '3');
            break;

            // Set anti-aliasing method
        case '6':
            SetAntiAliasingMethod(antiAliasing);
            break;

            // Set anti-aliasing level
        case '7':
            SetAntiAliasingLevel(antiAliasing);
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
