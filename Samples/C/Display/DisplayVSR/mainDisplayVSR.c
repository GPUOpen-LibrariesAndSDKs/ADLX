//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSync.c
/// \brief Demonstrates how to obtain the display VSR when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayVSR support
void ShowDisplayVSRSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayVSR state
void GetVirtualSuperResolutionState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayVSR
void SetVSRState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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
        // Get system service
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
                    // Get and execute the choice
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

void ShowDisplayVSRSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayVSR* pDisplayVSR = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVirtualSuperResolution(pDisplayService, pDisplay, &pDisplayVSR);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get VSR supported ===\n");
        adlx_bool supported = false;
        res = pDisplayVSR->pVtbl->IsSupported(pDisplayVSR, &supported);
        printf("\tIsSupported, res %d, supported: %s\n", res, supported ? "true" : "false");
        pDisplayVSR->pVtbl->Release(pDisplayVSR);
    }
}

void GetVirtualSuperResolutionState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayVSR* pDisplayVSR = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVirtualSuperResolution(pDisplayService, pDisplay, &pDisplayVSR);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get VSR enabled ===\n");
        adlx_bool enabled = false;
        res = pDisplayVSR->pVtbl->IsEnabled(pDisplayVSR, &enabled);
        printf("\tIsEnabled, res: %d, enabled: %s\n", res, enabled ? "true" : "false");
        pDisplayVSR->pVtbl->Release(pDisplayVSR);
    }
}

void SetVSRState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayVSR* pDisplayVSR = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVirtualSuperResolution(pDisplayService, pDisplay, &pDisplayVSR);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set VSR disabled
        case 0:
            printf("  === Set VSR enabled to false\n");
            res = pDisplayVSR->pVtbl->SetEnabled(pDisplayVSR, false);
            break;
            // Set VSR enabled
        case 1:
            printf("  === Set VSR enabled to true\n");
            res = pDisplayVSR->pVtbl->SetEnabled(pDisplayVSR, true);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means success)\n", res);
        pDisplayVSR->pVtbl->Release(pDisplayVSR);
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display VSR support\n");

    printf("\t->Press 2 to get VSR state\n");

    printf("\t->Press 3 to set current VSR to disabled\n");
    printf("\t->Press 4 to set current VSR to enabled\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display displayVSR support
        case '1':
            ShowDisplayVSRSupport(pDisplayService, pDisplay);
            break;

            // Display current displayVSR state
        case '2':
            GetVirtualSuperResolutionState(pDisplayService, pDisplay);
            break;

            // Set displayVSR
        case '3':
        case '4':
            SetVSRState(pDisplayService, pDisplay, num - '3');
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
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}