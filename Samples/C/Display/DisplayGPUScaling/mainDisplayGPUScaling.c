//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayCustomColor.c
/// \brief Demonstrates how to obtain the display GPU scaling when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayGPUScaling support
void ShowDisplayGPUScalingSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayGPUScaling state
void GetGPUScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayGPUScaling
void SetGPUScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

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

        // Get display service
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display list
            IADLXDisplayList* displayList = NULL;
            res = displayService->pVtbl->GetDisplays(displayService, &displayList);
            if (ADLX_SUCCEEDED(res))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplay* display = NULL;
                res = displayList->pVtbl->At_DisplayList(displayList, it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and execute the selection
                    MenuControl(displayService, display);
                }

                // Release the display interface
                if (NULL != display)
                {
                    display->pVtbl->Release(display);
                    display = NULL;
                }
            }

            // Release the displayList interface
            if (NULL != displayList)
            {
                displayList->pVtbl->Release(displayList);
                displayList = NULL;
            }
        }

        // Release the displayService interface
        if (NULL != displayService)
        {
            displayService->pVtbl->Release(displayService);
            displayService = NULL;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowDisplayGPUScalingSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayGPUScaling* pDisplayGPUScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetGPUScaling(pDisplayService, pDisplay, &pDisplayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get GPUScaling supported ===\n");
        adlx_bool supported = false;
        res = pDisplayGPUScaling->pVtbl->IsSupported(pDisplayGPUScaling, &supported);
        printf("\tIsSupported, res %d, supported: %s\n", res, supported ? "true" : "false");
        pDisplayGPUScaling->pVtbl->Release(pDisplayGPUScaling);
    }
}

void GetGPUScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayGPUScaling* pDisplayGPUScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetGPUScaling(pDisplayService, pDisplay, &pDisplayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get GPUScaling enabled ===\n");
        adlx_bool enabled = false;
        res = pDisplayGPUScaling->pVtbl->IsEnabled(pDisplayGPUScaling, &enabled);
        printf("\tIsEnabled, res: %d, enabled: %s\n", res, enabled ? "true" : "false");
        pDisplayGPUScaling->pVtbl->Release(pDisplayGPUScaling);
    }
}

void SetGPUScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayGPUScaling* pDisplayGPUScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetGPUScaling(pDisplayService, pDisplay, &pDisplayGPUScaling);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Set GPU scaling ===\n");
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set GPU scaling disabled
        case 0:
            res = pDisplayGPUScaling->pVtbl->SetEnabled(pDisplayGPUScaling, false);
            break;
            // Set GPU scaling enabled
        case 1:
            res = pDisplayGPUScaling->pVtbl->SetEnabled(pDisplayGPUScaling, true);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means Success)\n", res);
        pDisplayGPUScaling->pVtbl->Release(pDisplayGPUScaling);
    }
}

void MainMenu()
{
    printf("\tChoose from following options:\n");

    printf("\t->Press 1 to display GPU scaling support\n");

    printf("\t->Press 2 to get GPU scaling state\n");

    printf("\t->Press 3 to set current GPU scaling to disabled\n");
    printf("\t->Press 4 to set current GPU scaling to enabled\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display displayGPUScaling support
        case '1':
            ShowDisplayGPUScalingSupport(pDisplayService, pDisplay);
            break;

            // Display current displayGPUScaling state
        case '2':
            GetGPUScalingState(pDisplayService, pDisplay);
            break;

            // Set displayGPUScaling
        case '3':
        case '4':
            SetGPUScalingState(pDisplayService, pDisplay, num - '3');
            break;

            // Display main menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}