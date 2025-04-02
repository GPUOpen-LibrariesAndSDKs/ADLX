//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDRRC.c
/// \brief Demonstrates how to configure the Dynamic Refresh Rate Control options, and perform related testing when programming with ADLX.


#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays3.h"

// Thread to quit event
static HANDLE quitEvent = NULL;

// Thread to quit flag
static int g_quit = 0;

// Thread to timeout
static HANDLE thread = NULL;

// Check if Dynamic Refresh Rate Control is supported
void ShowDynamicRefreshRateControlSupport(IADLXDisplayServices3* displayService3, IADLXDisplay* display);

// Get the current state of Dynamic Refresh Rate Control
void GetDynamicRefreshRateControlState(IADLXDisplayServices3* displayService3, IADLXDisplay* display);

// Set the state of Dynamic Refresh Rate Control
void SetDynamicRefreshRateControlState(IADLXDisplayServices3* displayService3, IADLXDisplay* display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXDisplayServices3* displayService3, const IADLXDisplay* display);

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
            IADLXDisplayServices3* displayServices3 = NULL;
            ADLX_RESULT res3 = displayService->pVtbl->QueryInterface(displayService, IID_IADLXDisplayServices3(), (void**)&displayServices3);

            // Get display list
            IADLXDisplayList* displayList = NULL;
            res = displayService->pVtbl->GetDisplays(displayService, &displayList);
            if (ADLX_SUCCEEDED(res) && ADLX_SUCCEEDED(res3))
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
                    MenuControl(displayServices3, display);
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

            if (NULL != displayServices3)
            {
                displayServices3->pVtbl->Release(displayServices3);
                displayServices3 = NULL;
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

void ShowDynamicRefreshRateControlSupport(IADLXDisplayServices3* displayService3, IADLXDisplay* display)
{
    IADLXDisplayDynamicRefreshRateControl* displayDynamicRefreshRateControl;
    ADLX_RESULT res = displayService3->pVtbl->GetDynamicRefreshRateControl(displayService3,display, &displayDynamicRefreshRateControl);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get Dynamic Refresh Rate Control Supported ===\n");
        adlx_bool supported = false;
        res = displayDynamicRefreshRateControl->pVtbl->IsSupported(displayDynamicRefreshRateControl, &supported);
        printf("\tDynamic Refresh Rate Control is supported on the display: %s, return code: %d (0 means success)\n", supported ? "true" : "false", res);
        displayDynamicRefreshRateControl->pVtbl->Release(displayDynamicRefreshRateControl);
    }
}
void GetDynamicRefreshRateControlState(IADLXDisplayServices3* displayService3, IADLXDisplay* display)
{
    IADLXDisplayDynamicRefreshRateControl* displayDynamicRefreshRateControl ;
    ADLX_RESULT res = displayService3->pVtbl->GetDynamicRefreshRateControl(displayService3,display, &displayDynamicRefreshRateControl);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get Dynamic Refresh Rate Control enabled ===\n");
        adlx_bool enabled = false;
        res = displayDynamicRefreshRateControl->pVtbl->IsEnabled(displayDynamicRefreshRateControl, &enabled);
        printf("\tDynamic Refresh Rate Control is enabled on the display, res: %d, enabled: %s\n", res, enabled ? "true" : "false");
        displayDynamicRefreshRateControl->pVtbl->Release(displayDynamicRefreshRateControl);
    }
}

void SetDynamicRefreshRateControlState(IADLXDisplayServices3* displayService3, IADLXDisplay* display, const int key)
{
    IADLXDisplayDynamicRefreshRateControl* displayDynamicRefreshRateControl;
    ADLX_RESULT res = displayService3->pVtbl->GetDynamicRefreshRateControl(displayService3,display, &displayDynamicRefreshRateControl);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Set Dynamic Refresh Rate Control ===\n");
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set Dynamic Refresh Rate Control disabled
        case 0:
            res = displayDynamicRefreshRateControl->pVtbl->SetEnabled(displayDynamicRefreshRateControl, false);
            break;
            // Set Dynamic Refresh Rate Control enabled
        case 1:
            res = displayDynamicRefreshRateControl->pVtbl->SetEnabled(displayDynamicRefreshRateControl, true);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means Success)\n", res);
        displayDynamicRefreshRateControl->pVtbl->Release(displayDynamicRefreshRateControl);
    }
}

void MainMenu()
{
    printf("\tChoose from following options:\n");

    printf("\t->Press 1 to Dynamic Refresh Rate Control support\n");

    printf("\t->Press 2 to get Dynamic Refresh Rate Control state\n");

    printf("\t->Press 3 to set current Dynamic Refresh Rate Control enable\n");
    printf("\t->Press 4 to set current Dynamic Refresh Rate Control disable\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(IADLXDisplayServices3* displayService3, const IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display Dynamic Refresh Rate Control support
        case '1':
            ShowDynamicRefreshRateControlSupport(displayService3, display);
            break;

            // Display current Dynamic Refresh Rate Control state
        case '2':
            GetDynamicRefreshRateControlState(displayService3, display);
            break;

            // Set Dynamic Refresh Rate Control state
        case '3':
        case '4':
            SetDynamicRefreshRateControlState(displayService3, display, num - '3');
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