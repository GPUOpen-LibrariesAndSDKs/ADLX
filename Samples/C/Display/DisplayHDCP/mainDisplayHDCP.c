//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSync.c
/// \brief TDemonstrates how to obtain the display HDCP when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayHDCP support
void ShowDisplayHDCPSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayHDCP state
void GetHDCPState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set display HDCP
void SetHDCPState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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

void ShowDisplayHDCPSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayHDCP* pDisplayHDCP = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetHDCP(pDisplayService, pDisplay, &pDisplayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get HDCP supported ===\n");
        adlx_bool supported = false;
        res = pDisplayHDCP->pVtbl->IsSupported(pDisplayHDCP, &supported);
        printf("\tIsSupported, res %d, supported: %s\n", res, supported ? "true" : "false");
        pDisplayHDCP->pVtbl->Release(pDisplayHDCP);
    }
}

void GetHDCPState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayHDCP* pDisplayHDCP = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetHDCP(pDisplayService, pDisplay, &pDisplayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get HDCP enabled ===\n");
        adlx_bool enabled = false;
        res = pDisplayHDCP->pVtbl->IsEnabled(pDisplayHDCP, &enabled);
        printf("\tIsEnabled, res: %d, enabled: %s\n", res, enabled ? "true" : "false");
        pDisplayHDCP->pVtbl->Release(pDisplayHDCP);
    }
}

void SetHDCPState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayHDCP* pDisplayHDCP = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetHDCP(pDisplayService, pDisplay, &pDisplayHDCP);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set HDCP disabled
        case 0:
            printf("  === Set HDCP enabled to false\n");
            res = pDisplayHDCP->pVtbl->SetEnabled(pDisplayHDCP, false);
            break;
            // Set HDCP enabled
        case 1:
            printf("  === Set HDCP enabled to true\n");
            res = pDisplayHDCP->pVtbl->SetEnabled(pDisplayHDCP, true);
            break;
        default:
            break;
        }
        printf("\tReturn code is: %d (0 means Success)\n", res);
        pDisplayHDCP->pVtbl->Release(pDisplayHDCP);
    }
}

void MainMenu()
{
    printf("\tChoose from following options:\n");

    printf("\t->Press 1 to display HDCP support\n");

    printf("\t->Press 2 to get HDCP state\n");

    printf("\t->Press 3 to set current HDCP to disabled\n");
    printf("\t->Press 4 to set current HDCP to enabled\n");

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
            // Display displayHDCP support
        case '1':
            ShowDisplayHDCPSupport(pDisplayService, pDisplay);
            break;

            // Display current displayHDCP state
        case '2':
            GetHDCPState(pDisplayService, pDisplay);
            break;

            // Set displayHDCP
        case '3':
        case '4':
            SetHDCPState(pDisplayService, pDisplay, num - '3');
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