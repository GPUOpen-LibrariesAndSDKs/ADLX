//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSync.c
/// \brief Demonstrates how to obtain the display FreeSync when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayFreeSync Support
void ShowDisplayFreeSyncSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayFreeSync state
void GetFreeSyncState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayFreeSync
void SetFreeSyncState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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
                    // Display main menu selection
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

void ShowDisplayFreeSyncSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayFreeSync* pDisplayFreeSync = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetFreeSync(pDisplayService, pDisplay, &pDisplayFreeSync);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get FreeSync supported ===\n");
        adlx_bool supported = false;
        res = pDisplayFreeSync->pVtbl->IsSupported(pDisplayFreeSync, &supported);
        printf("\tIsSupported, res: %d, supported: %s\n", res, supported ? "true" : "false");
        pDisplayFreeSync->pVtbl->Release(pDisplayFreeSync);
    }
}

void GetFreeSyncState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayFreeSync* pDisplayFreeSync = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetFreeSync(pDisplayService, pDisplay, &pDisplayFreeSync);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get FreeSync enabled ===\n");
        adlx_bool enabled = false;
        res = pDisplayFreeSync->pVtbl->IsEnabled(pDisplayFreeSync, &enabled);
        printf("\tIsEnabled, res: %d, enabled: %d\n", res, enabled);
        pDisplayFreeSync->pVtbl->Release(pDisplayFreeSync);
    }
}

void SetFreeSyncState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayFreeSync* pDisplayFreeSync = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetFreeSync(pDisplayService, pDisplay, &pDisplayFreeSync);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set FreeSync disabled
        case 0:
            printf("  === Set FreeSync to false\n");
            res = pDisplayFreeSync->pVtbl->SetEnabled(pDisplayFreeSync, false);
            break;
            // Set FreeSync enabled
        case 1:
            printf("  === Set FreeSync to true\n");
            res = pDisplayFreeSync->pVtbl->SetEnabled(pDisplayFreeSync, true);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means Success)\n", res);
        pDisplayFreeSync->pVtbl->Release(pDisplayFreeSync);
    }
}

void MainMenu()
{
    printf("\tChoose from following options:\n");

    printf("\t->Press 1 to Display FreeSync support\n");

    printf("\t->Press 2 to get FreeSync state\n");

    printf("\t->Press 3 to set current FreeSync to disabled\n");
    printf("\t->Press 4 to set current FreeSync to enabled\n");

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
            // Display displayFreeSync support
        case '1':
            ShowDisplayFreeSyncSupport(pDisplayService, pDisplay);
            break;

            // Display current displayFreeSync state
        case '2':
            GetFreeSyncState(pDisplayService, pDisplay);
            break;

            // Set displayFreeSync
        case '3':
        case '4':
            SetFreeSyncState(pDisplayService, pDisplay, num - '3');
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