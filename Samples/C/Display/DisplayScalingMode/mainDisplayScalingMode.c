//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayScalingMode.c
/// \brief Demonstrates how to obtain the display scaling mode when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayScalingMode support
void ShowDisplayScalingModeSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayScalingMode state
void GetScalingModeState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayScalingMode
void SetScalingModeState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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
    printf("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowDisplayScalingModeSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayScalingMode* pDisplayScalingMode = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetScalingMode(pDisplayService, pDisplay, &pDisplayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get scaling mode supported ===\n");
        adlx_bool supported = false;
        res = pDisplayScalingMode->pVtbl->IsSupported(pDisplayScalingMode, &supported);
        printf("\tScaling mode is supported on the display: %s , return code: %d (0 means success)\n", supported ? "true" : "false", res);
        pDisplayScalingMode->pVtbl->Release(pDisplayScalingMode);
    }
}

void GetScalingModeState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayScalingMode* pDisplayScalingMode = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetScalingMode(pDisplayService, pDisplay, &pDisplayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get scaling-mode mode ===\n");
        ADLX_SCALE_MODE sm = PRESERVE_ASPECT_RATIO;
        res = pDisplayScalingMode->pVtbl->GetMode(pDisplayScalingMode, &sm);
        char* smStr = "Unknown";
        switch (sm)
        {
        case PRESERVE_ASPECT_RATIO:
            smStr = "PRESERVE_ASPECT_RATIO";
            break;
        case FULL_PANEL:
            smStr = "FULL_PANEL";
            break;
        case CENTERED:
            smStr = "CENTERED";
            break;
        }
        printf("\tThe scaling mode on the display is %s , return code: %d (0 means success)\n", smStr, res);
        pDisplayScalingMode->pVtbl->Release(pDisplayScalingMode);
    }
}

void SetScalingModeState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayScalingMode* pDisplayScalingMode = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetScalingMode(pDisplayService, pDisplay, &pDisplayScalingMode);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set scaling mode to PRESERVE_ASPECT_RATIO
        case 0:
            printf("  === Set scaling mode to PRESERVE_ASPECT_RATIO ===\n");
            res = pDisplayScalingMode->pVtbl->SetMode(pDisplayScalingMode, PRESERVE_ASPECT_RATIO);
            break;
            // Set scaling mode to FULL_PANEL
        case 1:
            printf("  === Set scaling mode to FULL_PANEL ===\n");
            res = pDisplayScalingMode->pVtbl->SetMode(pDisplayScalingMode, FULL_PANEL);
            break;
            // set ScalingMode CENTERED
        case 2:
            printf("  === Set scaling mode to CENTERED ===\n");
            res = pDisplayScalingMode->pVtbl->SetMode(pDisplayScalingMode, CENTERED);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means success)\n", res);
        pDisplayScalingMode->pVtbl->Release(pDisplayScalingMode);
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to Display scaling mode support\n");

    printf("\t->Press 2 to get scaling mode state\n");

    printf("\t->Press 3 to set current scaling mode to PRESERVE_ASPECT_RATIO\n");
    printf("\t->Press 4 to set current scaling mode to FULL_PANEL\n");
    printf("\t->Press 5 to set current scaling mode to CENTERED\n");

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
            // Display displayScalingMode support
        case '1':
            ShowDisplayScalingModeSupport(pDisplayService, pDisplay);
            break;

            // Display current displayScalingMode state
        case '2':
            GetScalingModeState(pDisplayService, pDisplay);
            break;

            // Set displayScalingMode
        case '3':
        case '4':
        case '5':
            SetScalingModeState(pDisplayService, pDisplay, num - '3');
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