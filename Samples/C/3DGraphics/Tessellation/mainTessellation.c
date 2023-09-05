//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainTessellation.c
/// \brief Demonstrates how to access tessellation options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"

// Display tessellation support
void ShowSupport(IADLX3DTessellation* tessellation);

// Get current tessellation state
void GetState(IADLX3DTessellation* tessellation);

// Set tessellation mode
void SetMode(IADLX3DTessellation* tessellation, int index);

// Set tessellation level
void SetLevel(IADLX3DTessellation* tessellation);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DTessellation* tessellation);

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

            // Get the IADLX3DTessellation interface
            IADLX3DTessellation* tessellation = NULL;
            res = d3dSettingSrv->pVtbl->GetTessellation(d3dSettingSrv, gpu, &tessellation);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(tessellation);
            }

            // Release the IADLX3DTessellation interface
            if (tessellation != NULL)
            {
                tessellation->pVtbl->Release(tessellation);
                tessellation = NULL;
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

static char* getModeStr(ADLX_TESSELLATION_MODE mode)
{
    switch (mode)
    {
    case T_MODE_AMD_OPTIMIZED:
        return "AMD optimized";
    case T_MODE_USE_APP_SETTINGS:
        return "Use application settings";
    case T_MODE_OVERRIDE_APP_SETTINGS:
        return "Override application settings";
    default:
        return "UNKNOWN";
    }
};

static char* getLevelStr(ADLX_TESSELLATION_LEVEL level)
{
    switch (level)
    {
    case T_LEVEL_OFF:
        return "Off";
    case T_LEVEL_2X:
        return "2X";
    case T_LEVEL_4X:
        return "4X";
    case T_LEVEL_6X:
        return "6X";
    case T_LEVEL_8X:
        return "8X";
    case T_LEVEL_16X:
        return "16X";
    case T_LEVEL_32X:
        return "32X";
    case T_LEVEL_64X:
        return "64X";
    default:
        return "UNKNOWN";
    }
};

void ShowSupport(IADLX3DTessellation* tessellation)
{
    adlx_bool supported = false;
    ADLX_RESULT res = tessellation->pVtbl->IsSupported(tessellation, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetState(IADLX3DTessellation* tessellation)
{
    ADLX_TESSELLATION_MODE mode;
    ADLX_RESULT res = tessellation->pVtbl->GetMode(tessellation, &mode);
    printf("\tMode: %s, return code is: %d(0 means success)\n", getModeStr(mode), res);
    ADLX_TESSELLATION_LEVEL level;
    res = tessellation->pVtbl->GetLevel(tessellation, &level);
    printf("\tLevel: %s, return code is: %d(0 means success)\n", getLevelStr(level), res);
}

void SetMode(IADLX3DTessellation* tessellation, int index)
{
    ADLX_RESULT res = ADLX_FAIL;
    ADLX_TESSELLATION_MODE mode = T_MODE_AMD_OPTIMIZED;
    mode = (ADLX_TESSELLATION_MODE)(mode + index);
    res = tessellation->pVtbl->SetMode(tessellation, mode);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void SetLevel(IADLX3DTessellation* tessellation)
{
    ADLX_TESSELLATION_LEVEL level;
    tessellation->pVtbl->GetLevel(tessellation, &level);
    level = (level == T_LEVEL_2X) ? T_LEVEL_4X : T_LEVEL_2X;
    ADLX_RESULT res = tessellation->pVtbl->SetLevel(tessellation, level);
    printf("\tSet level: %s, res is: %d\n", getLevelStr(level), res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display tessellation support\n");
    printf("\t->Press 2 to get tessellation state\n");
    printf("\t->Press 3 to set tessellation mode: AMD optimized\n");
    printf("\t->Press 4 to set tessellation mode: Use application settings\n");
    printf("\t->Press 5 to set tessellation mode: Override application settings\n");

    printf("\t->Press 6 to set tessellation level\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void MenuControl(IADLX3DTessellation* tessellation)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display tessellation support
        case '1':
            ShowSupport(tessellation);
            break;

            // Get and display current tessellation state
        case '2':
            GetState(tessellation);
            break;

            // Set tessellation mode
        case '3':
        case '4':
        case '5':
            SetMode(tessellation, num - '3');
            break;

            // Set anti-aliasing level
        case '6':
            SetLevel(tessellation);
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
