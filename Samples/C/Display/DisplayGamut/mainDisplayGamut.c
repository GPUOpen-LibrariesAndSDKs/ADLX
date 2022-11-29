//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayGamut.c
/// \brief Demonstrates how to obtain the display gamut when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"

// Display displayGamutSupport
void ShowDisplayGamutSupport(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get displayGamut
    IADLXDisplayGamut* displayGamut = NULL;
    ADLX_RESULT res = displayService->pVtbl->GetGamut(displayService, display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool supported = false;
        printf("  === Gamut space supported status ===\n");
        res = displayGamut->pVtbl->IsSupportedCCIR709ColorSpace(displayGamut, &supported);
        printf("\tIsSupportedGamut_CCIR_709: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedCCIR601ColorSpace(displayGamut, &supported);
        printf("\tIsSupportedGamut_CCIR_601: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedAdobeRgbColorSpace(displayGamut, &supported);
        printf("\tIsSupportedGamut_Adobe_RGB: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedCIERgbColorSpace(displayGamut, &supported);
        printf("\tIsSupportedGamut_CIE_RGB: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedCCIR2020ColorSpace(displayGamut, &supported);
        printf("\tIsSupportedCCIR2020ColorSpace: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedCustomColorSpace(displayGamut, &supported);
        printf("\tIsSupportedGamut_Custom: %d\n", supported);

        printf("  === White point supported status ===\n");
        res = displayGamut->pVtbl->IsSupported5000kWhitePoint(displayGamut, &supported);
        printf("\tIsSupportedWhitePoint_5000k: %d\n", supported);
        res = displayGamut->pVtbl->IsSupported6500kWhitePoint(displayGamut, &supported);
        printf("\tIsSupportedWhitePoint_6500k: %d\n", supported);
        res = displayGamut->pVtbl->IsSupported7500kWhitePoint(displayGamut, &supported);
        printf("\tIsSupportedWhitePoint_7500k: %d\n", supported);
        res = displayGamut->pVtbl->IsSupported9300kWhitePoint(displayGamut, &supported);
        printf("\tIsSupportedWhitePoint_9300k: %d\n", supported);
        res = displayGamut->pVtbl->IsSupportedCustomWhitePoint(displayGamut, &supported);
        printf("\tIsSupportedWhitePoint_Custom: %d\n", supported);
    }

    // Release the displayGamut interface
    if (NULL != displayGamut)
    {
        displayGamut->pVtbl->Release(displayGamut);
        displayGamut = NULL;
    }
}

// Display gamut information, it contains white point and color space
void GetCurrentGamutInfo(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get displayGamut
    IADLXDisplayGamut* displayGamut = NULL;
    ADLX_RESULT res = displayService->pVtbl->GetGamut(displayService, display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool applied = false;
        ADLX_RESULT res = ADLX_FAIL;
        printf("  === Current white point status ===\n");
        res = displayGamut->pVtbl->IsCurrent5000kWhitePoint(displayGamut, &applied);
        printf("\tIsCurrentWhitePoint_5000k: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrent6500kWhitePoint(displayGamut, &applied);
        printf("\tIsCurrentWhitePoint_6500k: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrent7500kWhitePoint(displayGamut, &applied);
        printf("\tIsCurrentWhitePoint_7500k: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrent9300kWhitePoint(displayGamut, &applied);
        printf("\tIsCurrentWhitePoint_9300k: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentCustomWhitePoint(displayGamut, &applied);
        printf("\tIsCurrentWhitePoint_Custom: %d\n", applied);
        ADLX_Point point = {0};
        res = displayGamut->pVtbl->GetWhitePoint(displayGamut, &point);
        printf("\tGetWhitePoint: ( %d,  %d)\n", point.x, point.y);

        printf("  === Current gamut space status ===\n");
        res = displayGamut->pVtbl->IsCurrentCCIR709ColorSpace(displayGamut, &applied);
        printf("\tIsCurrentGamut_CCIR_709: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentCCIR601ColorSpace(displayGamut, &applied);
        printf("\tIsCurrentGamut_CCIR_601: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentAdobeRgbColorSpace(displayGamut, &applied);
        printf("\tIsCurrentGamut_Adobe_RGB: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentCIERgbColorSpace(displayGamut, &applied);
        printf("\tIsCurrentGamut_CIE_RGB: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentCCIR2020ColorSpace(displayGamut, &applied);
        printf("\tIsCurrentCCIR2020ColorSpace: %d\n", applied);
        res = displayGamut->pVtbl->IsCurrentCustomColorSpace(displayGamut, &applied);
        printf("\tIsCurrentCustomColorSpace: %d\n", applied);
        ADLX_GamutColorSpace gamutCoordinates = {0};
        res = displayGamut->pVtbl->GetGamutColorSpace(displayGamut, &gamutCoordinates);
        printf("\tGetGamutColorSpace: R( %d, %d ), G( %d, %d ), B( %d, %d )\n",
               gamutCoordinates.red.x, gamutCoordinates.red.y,
               gamutCoordinates.green.x, gamutCoordinates.green.y,
               gamutCoordinates.blue.x, gamutCoordinates.blue.y);
    }

    // Release the displayGamut interface
    if (NULL != displayGamut)
    {
        displayGamut->pVtbl->Release(displayGamut);
        displayGamut = NULL;
    }
}

// Set gamut(white point and color space)
void SetGamut(IADLXDisplayServices* displayService, IADLXDisplay* display, int key)
{
    printf("  === Set white point and gamut space ===\n");

    ADLX_RESULT res = ADLX_FAIL;
    ADLX_WHITE_POINT predefinedWhitePoint = WHITE_POINT_6500K;
    ADLX_GAMUT_SPACE predefinedGamutSpace = GAMUT_SPACE_ADOBE_RGB;
    ADLX_RGB customWhitePoint = {0.654108, 0.767112, 1};
    ADLX_GamutColorSpace customGamutSpace =
    {
        {6400, 3300}, {3000, 6000}, {1500, 600}
    };

    // Get displayGamut
    IADLXDisplayGamut* displayGamut = NULL;
    res = displayService->pVtbl->GetGamut(displayService, display, &displayGamut);
    if (ADLX_SUCCEEDED(res))
    {

        switch (key)
        {
        // Set gamut with predefined white point and predefined gamut space
        case 0:
            res = displayGamut->pVtbl->SetGamut_PW_PG(displayGamut, predefinedWhitePoint, predefinedGamutSpace);
            break;

        // Set gamut with custom white  point and predefined gamut space
        case 1:
            res = displayGamut->pVtbl->SetGamut_CW_PG(displayGamut, customWhitePoint, predefinedGamutSpace);
            break;

        // Set gamut with predefined white point and custom gamut space
        case 2:
            res = displayGamut->pVtbl->SetGamut_PW_CG(displayGamut, predefinedWhitePoint, customGamutSpace);
            break;

        // Set gamut with custom white point and custom gamut space
        case 3:
            res = displayGamut->pVtbl->SetGamut_CW_CG(displayGamut, customWhitePoint, customGamutSpace);
            break;
        default:
            break;
        }
        printf("\treturn code(0 means Success) is: %d\n", res);
    }

    // Release the displayGamut interface
    if (NULL != displayGamut)
    {
        displayGamut->pVtbl->Release(displayGamut);
        displayGamut = NULL;
    }
}

// Main menu
void MainMenu()
{
    printf("\tChoose from  following options\n");

    printf("\t->Press 1 to display gamut support\n");

    printf("\t->Press 2 to get current display gamut information\n");

    printf("\t->Press 3 to set predefined white point and predefined gamut space\n");
    printf("\t->Press 4 to set custom white point and predefined gamut space\n");
    printf("\t->Press 5 to set predefined white point and custom gamut space\n");
    printf("\t->Press 6 to set custom white point and custom gamut space\n");

    printf("\t->Press Q/q to terminate the application. \n");
    printf("\t->Press M/m to display main menu options \n");
}

// Menu action control
void MenuControl(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display displayGamutSupport
        case '1':
            ShowDisplayGamutSupport(displayService, display);
            break;

        // Get gamut information with white point and color space
        case '2':
            GetCurrentGamutInfo(displayService, display);
            break;

        // Set gamut with white point and color space
        case '3':
        case '4':
        case '5':
        case '6':
            SetGamut(displayService, display, num - '3');
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
