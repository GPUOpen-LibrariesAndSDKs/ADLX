//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSync.c
/// \brief Demonstrates how to obtain the display FreeSync through ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayIntegerScaling support
void ShowDisplayIntegerScalingSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayIntegerScaling state
void GetIntegerScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayIntegerScaling
void SetIntegerScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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
                    // Show a menu with options to chose from
                    MainMenu();
                    // Get and excute the selection
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

void ShowDisplayIntegerScalingSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayIntegerScaling* pDisplayIntegerScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetIntegerScaling(pDisplayService, pDisplay, &pDisplayIntegerScaling);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get IntegerScaling supported ===\n");
        adlx_bool supported = false;
        res = pDisplayIntegerScaling->pVtbl->IsSupported(pDisplayIntegerScaling, &supported);
        printf("\tIsSupported, res %d, supported: %s\n", res, supported ? "true" : "false");
        pDisplayIntegerScaling->pVtbl->Release(pDisplayIntegerScaling);
    }
}

void GetIntegerScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayIntegerScaling* pDisplayIntegerScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetIntegerScaling(pDisplayService, pDisplay, &pDisplayIntegerScaling);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get IntegerScaling enabled ===\n");
        adlx_bool enabled = false;
        res = pDisplayIntegerScaling->pVtbl->IsEnabled(pDisplayIntegerScaling, &enabled);
        printf("\tIsEnabled, res: %d, enabled: %s\n", res, enabled ? "true" : "false");
        pDisplayIntegerScaling->pVtbl->Release(pDisplayIntegerScaling);
    }
}

void SetIntegerScalingState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayIntegerScaling* pDisplayIntegerScaling = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetIntegerScaling(pDisplayService, pDisplay, &pDisplayIntegerScaling);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set IntegerScaling disabled
        case 0:
            printf("  === Set IntegerScaling enabled to false;\n");
            res = pDisplayIntegerScaling->pVtbl->SetEnabled(pDisplayIntegerScaling, false);
            break;
            // Set IntegerScaling enabled
        case 1:
            printf("  === Set IntegerScaling enabled to true;\n");
            res = pDisplayIntegerScaling->pVtbl->SetEnabled(pDisplayIntegerScaling, true);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means Success)\n", res);
        pDisplayIntegerScaling->pVtbl->Release(pDisplayIntegerScaling);
    }
}

void MainMenu()
{
    printf("\tChoose from following options\n");

    printf("\t->Press 1 to display integer scaling support\n");

    printf("\t->Press 2 to get integer scaling state\n");

    printf("\t->Press 3 to set current Integer Scaling to disabled\n");
    printf("\t->Press 4 to set current Integer Scaling to enabled\n");

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
            // Display displayIntegerScaling support
        case '1':
            ShowDisplayIntegerScalingSupport(pDisplayService, pDisplay);
            break;

            // Display current displayIntegerScaling state
        case '2':
            GetIntegerScalingState(pDisplayService, pDisplay);
            break;

            // Set displayIntegerScaling
        case '3':
        case '4':
            SetIntegerScalingState(pDisplayService, pDisplay, num - '3');
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