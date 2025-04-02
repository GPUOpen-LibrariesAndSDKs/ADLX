//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayCustomColor.c
/// \brief Demonstrates how to obtain the display custom resolution when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display custom resolution support
void ShowCustomResolutionSupport(IADLXDisplayCustomResolution* pCustomResolution);

// Display availabe display resolutions
void GetResolutionList(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolutionList** ppResolutionList);

// Display current display resolution
void GetCurrentResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution** ppResolution);

// Create new customized display resolution
void CreateNewResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution* pResolution);

// Delete display resolution
void DeleteResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution* pResolution);

// Print out given resolution
void PrintResolution(IADLXDisplayResolution* pResolution);

// Print out given resolution list
void PrintResolutions(IADLXDisplayResolutionList* pResolutionList);

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

void ShowCustomResolutionSupport(IADLXDisplayCustomResolution* pCustomResolution)
{
    printf("  === Get custom resolution supported ===\n");
    adlx_bool supported = false;
    ADLX_RESULT res = pCustomResolution->pVtbl->IsSupported(pCustomResolution, &supported);
    printf("\tIsSupported, result %d, supported: %s\n", res, supported ? "true" : "false");
}

void GetResolutionList(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolutionList** ppResolutionList)
{
    ADLX_RESULT res = pCustomResolution->pVtbl->GetResolutionList(pCustomResolution, ppResolutionList);
    if (ADLX_FAILED(res))
        printf("  GetResolutionList, failed.\n");
}

void GetCurrentResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution** ppResolution)
{
    ADLX_RESULT res = pCustomResolution->pVtbl->GetCurrentAppliedResolution(pCustomResolution, ppResolution);
    if (ADLX_FAILED(res))
        printf("  GetCurrentResolution, failed.\n");
}

void CreateNewResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution* pResolution)
{
    ADLX_RESULT res = pCustomResolution->pVtbl->CreateNewResolution(pCustomResolution, pResolution);
    if (ADLX_FAILED(res))
        printf("  CreateNewResolution, failed.\n");
}

void DeleteResolution(IADLXDisplayCustomResolution* pCustomResolution, IADLXDisplayResolution* pResolution)
{
    PrintResolution(pResolution);
    ADLX_RESULT res = pCustomResolution->pVtbl->DeleteResolution(pCustomResolution, pResolution);
    if (ADLX_FAILED(res))
        printf("  DeleteResolution, failed.\n");
}

void PrintResolution(IADLXDisplayResolution* pResolution)
{
    ADLX_CustomResolution cr;
    pResolution->pVtbl->GetValue(pResolution, &cr);

    char* sPresention = (cr.presentation == INTERLACED) ? "Interlaced" : "Progressive";
    char* sTimingStandard = "Manual";
    char* sHPolarity = (cr.detailedTiming.hPolarity == POSITIVE) ? "Positive" : "Negative";
    char* sVPolarity = (cr.detailedTiming.vPolarity == POSITIVE) ? "Positive" : "Negative";

    switch (cr.timingStandard)
    {
    case MANUAL:
        sTimingStandard = "Manual";
        break;
    case DMT:
        sTimingStandard = "DMT";
        break;
    case GTF:
        sTimingStandard = "GTF";
        break;
    case CVT_RB:
        sTimingStandard = "CVT - Reduced Blanking";
        break;
    case CVT:
        sTimingStandard = "CVT";
        break;
    default:
        break;
    }

    char buff[1024] = {0};
    int offset = snprintf(buff, sizeof(buff), "\n  Resolution (Px)\t\t%d x %d\n", cr.resWidth, cr.resHeight);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Refresh Rate (Hz)\t\t%d\n", cr.refreshRate);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Presentation\t\t\t%s\n", sPresention);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Standard\t\t%s\n", sTimingStandard);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  G.Pixel Clock (kHz)\t\t%d\n", cr.GPixelClock);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Information\t\t\tHorizontal\tVertical\n");
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Total\t\t\t%d\t%d\n", cr.detailedTiming.hTotal, cr.detailedTiming.vTotal);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Display\t\t%d\t%d\n", cr.detailedTiming.hDisplay, cr.detailedTiming.vDisplay);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Front Porch\t\t%d\t%d\n", cr.detailedTiming.hFrontPorch, cr.detailedTiming.vFrontPorch);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Sync Width\t\t%d\t%d\n", cr.detailedTiming.hSyncWidth, cr.detailedTiming.vSyncWidth);
    offset += snprintf(buff + offset, sizeof(buff) - offset, "  Timing Polarity\t\t%s %s\n", sHPolarity, sVPolarity);

    printf("%s\n", buff);
}

void PrintResolutions(IADLXDisplayResolutionList* pResolutionList)
{
    printf("  Print out resolution list ==\n");
    if (pResolutionList == NULL)
    {
        printf("  Resolution list is NULL\n");
        return;
    }

    if (pResolutionList->pVtbl->Size(pResolutionList) == 0)
    {
        printf("  Resolution list is empty!\n");
        return;
    }

    ADLX_RESULT res = ADLX_FAIL;
    for (adlx_uint crt = 0; crt < pResolutionList->pVtbl->Size(pResolutionList); crt++)
    {
        IADLXDisplayResolution* pDispResolution = NULL;
        res = pResolutionList->pVtbl->At_DisplayResolutionList(pResolutionList, crt, &pDispResolution);
        if (ADLX_SUCCEEDED(res))
        {
            printf("  Resolution index: %d\n", crt);
            PrintResolution(pDispResolution);
        }
    }
}

void MainMenu()
{
    printf("\tChoose from following options\n");

    printf("\t->Press 1 to display custom resolution support\n");

    printf("\t->Press 2 to get custom resolution list\n");

    printf("\t->Press 3 to get current applied resolution\n");
    printf("\t->Press 4 to create new customized resolution\n");
    printf("\t->Press 5 to delete avaible resolution\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayCustomResolution* pCustomResolution = NULL;
    pDisplayService->pVtbl->GetCustomResolution(pDisplayService, pDisplay, &pCustomResolution);

    if (!pCustomResolution)
    {
        printf("Menu control: cannot retrive custom resolution instance!\n");
        return;
    }

    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display custom resolution support
        case '1':
            ShowCustomResolutionSupport(pCustomResolution);
            break;

            // Display current available resolutions
        case '2':
        {
            printf("  === Get Resolution List: ===\n");
            IADLXDisplayResolutionList* pResolutionList = NULL;
            GetResolutionList(pCustomResolution, &pResolutionList);
            if (pResolutionList != NULL)
            {
                PrintResolutions(pResolutionList);
                pResolutionList->pVtbl->Release(pResolutionList);
            }
            break;
        }

        // Get current applied resolution
        case '3':
        {
            printf("  === Get current resolution: ===\n");
            IADLXDisplayResolution* pDisplayResolution = NULL;
            GetCurrentResolution(pCustomResolution, &pDisplayResolution);
            if (pDisplayResolution != NULL)
            {
                PrintResolution(pDisplayResolution);
                pDisplayResolution->pVtbl->Release(pDisplayResolution);
            }
            break;
        }
        // Create customized resolution
        case '4':
        {
            printf("  === Create new resolution: ===\n");
            IADLXDisplayResolution* pDisplayResolution = NULL;
            GetCurrentResolution(pCustomResolution, &pDisplayResolution);
            if (pDisplayResolution)
            {
                ADLX_CustomResolution customRes;
                pDisplayResolution->pVtbl->GetValue(pDisplayResolution, &customRes);

                customRes.resWidth = 1920;
                customRes.resHeight = 1080;
                customRes.detailedTiming.hDisplay = 1920;
                customRes.detailedTiming.vDisplay = 1080;
                pDisplayResolution->pVtbl->SetValue(pDisplayResolution, customRes);

                PrintResolution(pDisplayResolution);
                CreateNewResolution(pCustomResolution, pDisplayResolution);
                pDisplayResolution->pVtbl->Release(pDisplayResolution);
            }
            break;
        }
        // Delete available resolution
        case '5':
        {
            printf("  === Delete resolution: ===\n");
            IADLXDisplayResolutionList* pResolutionList = NULL;
            GetResolutionList(pCustomResolution, &pResolutionList);
            if (pResolutionList != NULL && pResolutionList->pVtbl->Size(pResolutionList) > 0)
            {
                IADLXDisplayResolution* pDisplayResolution = NULL;
                ADLX_RESULT res = pResolutionList->pVtbl->At_DisplayResolutionList(pResolutionList, 0, &pDisplayResolution);
                if (ADLX_SUCCEEDED(res))
                {
                    DeleteResolution(pCustomResolution, pDisplayResolution);
                    pDisplayResolution->pVtbl->Release(pDisplayResolution);
                }
                pResolutionList->pVtbl->Release(pResolutionList);
            }
            break;
        }
        // Display main menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }

    pCustomResolution->pVtbl->Release(pCustomResolution);
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