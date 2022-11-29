//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayColorDepth.c
/// \brief Demonstrates how to obtain the color depth of a display when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayColorDepthSupport
void ShowDisplayColorDepthSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayColorDepth state
void GetColorDepthState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayColorDepth
void SetColorDepthState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

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

        // Get display services
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
                    // Get and parse the selection
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

void ShowDisplayColorDepthSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayColorDepth* pDisplayColorDepth = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetColorDepth(pDisplayService, pDisplay, &pDisplayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get ColorDepth Supported ===\n");
        adlx_bool supported = false;
        res = pDisplayColorDepth->pVtbl->IsSupported(pDisplayColorDepth, &supported);
        printf("\tIsSupported, res %d, supported: %s\n", res, supported ? "true" : "false");
    }

    if (pDisplayColorDepth != NULL)
    {
        pDisplayColorDepth->pVtbl->Release(pDisplayColorDepth);
        pDisplayColorDepth = NULL;
    }
}

void GetSupportStateForEachColorDepth (IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayColorDepth* pDisplayColorDepth = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetColorDepth(pDisplayService, pDisplay, &pDisplayColorDepth);
    if (ADLX_SUCCEEDED (res) && pDisplayColorDepth)
    {
        printf("  === Get ColorDepth Support List ===\n");

        adlx_bool isSupported = false;
        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_6 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_6, result %d,  BPC_6 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_8 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_8, result %d,  BPC_8 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_10 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_10, result %d,  BPC_10 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_12 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_12, result %d,  BPC_12 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_14 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_14, result %d,  BPC_14 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedBPC_16 (pDisplayColorDepth, &isSupported);
        printf("\tIsSupportedBPC_16, result %d,  BPC_16 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_6, &isSupported);
        printf("\tIsSupportedBPC_6, result %d,  BPC_6 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_8, &isSupported);
        printf("\tIsSupportedBPC_8, result %d,  BPC_8 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_10, &isSupported);
        printf("\tIsSupportedBPC_10, result %d,  BPC_10 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_12, &isSupported);
        printf("\tIsSupportedBPC_12, result %d,  BPC_12 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_14, &isSupported);
        printf("\tIsSupportedBPC_14, result %d,  BPC_14 support: %d\n", res, isSupported);

        res = pDisplayColorDepth->pVtbl->IsSupportedColorDepth (pDisplayColorDepth, BPC_16, &isSupported);
        printf("\tIsSupportedBPC_16, result %d,  BPC_16 support: %d\n", res, isSupported);

        //Release the DisplayColorDepth interface
        pDisplayColorDepth->pVtbl->Release(pDisplayColorDepth);
        pDisplayColorDepth = NULL;
    }
}

void GetColorDepthState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayColorDepth* pDisplayColorDepth = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetColorDepth(pDisplayService, pDisplay, &pDisplayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get ColorDepth Enabled ===\n");
        ADLX_COLOR_DEPTH cd = BPC_UNKNOWN;
        res = pDisplayColorDepth->pVtbl->GetValue(pDisplayColorDepth, &cd);
        char* cdStr = "BPC_Unknown";
        switch (cd)
        {
        case BPC_6:
            cdStr = "BPC_6";
            break;
        case BPC_8:
            cdStr = "BPC_8";
            break;
        case BPC_10:
            cdStr = "BPC_10";
            break;
        }

        printf("\tGetValue, result %d,  color depth: %s\n", res, cdStr);
    }

    if (pDisplayColorDepth != NULL)
    {
        pDisplayColorDepth->pVtbl->Release(pDisplayColorDepth);
        pDisplayColorDepth = NULL;
    }
}

void SetColorDepthState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayColorDepth* pDisplayColorDepth = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetColorDepth(pDisplayService, pDisplay, &pDisplayColorDepth);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set ColorDepth BPC_6
        case 0:
            printf("  === Set color depth: BPC_6\n");
            res = pDisplayColorDepth->pVtbl->SetValue(pDisplayColorDepth, BPC_6);
            break;
            // Set ColorDepth BPC_8
        case 1:
            printf("  === Set color depth: BPC_8\n");
            res = pDisplayColorDepth->pVtbl->SetValue(pDisplayColorDepth, BPC_8);
            break;
            // set ColorDepth BPC_10
        case 2:
            printf("  === Set color depth: BPC_10\n");
            res = pDisplayColorDepth->pVtbl->SetValue(pDisplayColorDepth, BPC_10);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means Success)\n", res);
    }

    if (pDisplayColorDepth != NULL)
    {
        pDisplayColorDepth->pVtbl->Release(pDisplayColorDepth);
        pDisplayColorDepth = NULL;
    }
}

void MainMenu()
{
    printf("\tChoose from the following options\n");

    printf("\t->Press 1 to display color depth support\n");

    printf("\t->Press 2 to get color depth state\n");

    printf("\t->Press 3 to set current color depth to BPC_6\n");
    printf("\t->Press 4 to set current color depth to BPC_8\n");
    printf("\t->Press 5 to set current color depth to BPC_10\n");

    printf("\t->Press 6 to get support state for each color depth\n");

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
            // Display displayColorDepthSupport
        case '1':
            ShowDisplayColorDepthSupport(pDisplayService, pDisplay);
            break;

            // Display current displayColorDepth state
        case '2':
            GetColorDepthState(pDisplayService, pDisplay);
            break;

            // Set displayColorDepth
        case '3':
        case '4':
        case '5':
            SetColorDepthState(pDisplayService, pDisplay, num - '3');
            break;

        case '6':
            GetSupportStateForEachColorDepth(pDisplayService, pDisplay);
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