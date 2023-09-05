//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSync.c
/// \brief Demonstrates how to obtain the pixel format when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayPixelFormat support
void ShowDisplayPixelFormatSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Display current displayPixelFormat state
void GetPixelFormatState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Set displayPixelFormat
void SetPixelFormatState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key);

// Get support state for each pixel format
void GetSupportStateForEachPixelFormat(IADLXDisplayServices* displayService, IADLXDisplay* display);

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

                //Release the display interface
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

void ShowDisplayPixelFormatSupport(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayPixelFormat* pDisplayPixelFormat = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetPixelFormat(pDisplayService, pDisplay, &pDisplayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get PixelFormat supported ===\n");
        adlx_bool supported = false;
        res = pDisplayPixelFormat->pVtbl->IsSupported(pDisplayPixelFormat, &supported);
        printf("\tPixel format is supported on the display: %s , return code: %d (0 means success)\n", supported ? "true" : "false", res);
        pDisplayPixelFormat->pVtbl->Release(pDisplayPixelFormat);
    }
}

void GetPixelFormatState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayPixelFormat* pDisplayPixelFormat = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetPixelFormat(pDisplayService, pDisplay, &pDisplayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get PixelFormat enabled ===\n");
        ADLX_PIXEL_FORMAT pf = FORMAT_UNKNOWN;
        res = pDisplayPixelFormat->pVtbl->GetValue(pDisplayPixelFormat, &pf);
        char* pfStr = "FORMAT_UNKNOWN";
        switch (pf)
        {
        case RGB_444_FULL:
            pfStr = "RGB_444_FULL";
            break;
        case YCBCR_444:
            pfStr = "YCBCR_444";
            break;
        case YCBCR_422:
            pfStr = "YCBCR_422";
            break;
        case RGB_444_LIMITED:
            pfStr = "RGB_444_LIMITED";
            break;
        case YCBCR_420:
            pfStr = "YCBCR_420";
            break;
        default:
            break;
        }
        printf("\tThe pixel format on the display is %s , return code: %d (0 means success)\n", pfStr, res);
        pDisplayPixelFormat->pVtbl->Release(pDisplayPixelFormat);
    }
}

void SetPixelFormatState(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int key)
{
    IADLXDisplayPixelFormat* pDisplayPixelFormat = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetPixelFormat(pDisplayService, pDisplay, &pDisplayPixelFormat);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set PixelFormat RGB_444_FULL
        case 0:
            printf("  === Set pixel format to RGB_444_FULL\n");
            res = pDisplayPixelFormat->pVtbl->SetValue(pDisplayPixelFormat, RGB_444_FULL);
            break;
            // Set PixelFormat YCBCR_444
        case 1:
            printf("  === Set pixel format to YCBCR_444\n");
            res = pDisplayPixelFormat->pVtbl->SetValue(pDisplayPixelFormat, YCBCR_444);
            break;
            // Set pixel format YCBCR_422
        case 2:
            printf("  === Set pixel format to YCBCR_422\n");
            res = pDisplayPixelFormat->pVtbl->SetValue(pDisplayPixelFormat, YCBCR_422);
            break;
            // Set pixel format RGB_444_LIMITED
        case 3:
            printf("  === Set pixel format to RGB_444_LIMITED\n");
            res = pDisplayPixelFormat->pVtbl->SetValue(pDisplayPixelFormat, RGB_444_LIMITED);
            break;
        default:
            break;
        }
        printf("\treturn code is: %d (0 means success)\n", res);
        pDisplayPixelFormat->pVtbl->Release(pDisplayPixelFormat);
    }
}

// Get support state for each pixel format
void GetSupportStateForEachPixelFormat(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    IADLXDisplayPixelFormat* displayPixelFormat = NULL;
    ADLX_RESULT res = displayService->pVtbl->GetPixelFormat(displayService, display, &displayPixelFormat);
    if (ADLX_SUCCEEDED(res) && displayPixelFormat)
    {
        printf(" === Get pixel format list === \n");
        adlx_bool support = false;

        res = displayPixelFormat->pVtbl->IsSupportedRGB444Full(displayPixelFormat, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support RGB 4:4:4 PC Standard (Full RGB): %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedYCbCr444(displayPixelFormat, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:4:4: %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedYCbCr422(displayPixelFormat, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:2:2: %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedRGB444Limited(displayPixelFormat, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support RGB 4:4:4 Studio (Limited RGB): %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedYCbCr420(displayPixelFormat, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:2:0: %d\n", support);

        res = displayPixelFormat->pVtbl->IsSupportedPixelFormat(displayPixelFormat, RGB_444_FULL, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support RGB 4:4:4 PC Standard (Full RGB): %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedPixelFormat(displayPixelFormat, YCBCR_444, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:4:4: %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedPixelFormat(displayPixelFormat, YCBCR_422, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:2:2: %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedPixelFormat(displayPixelFormat, RGB_444_LIMITED, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support RGB 4:4:4 Studio (Limited RGB): %d\n", support);
        res = displayPixelFormat->pVtbl->IsSupportedPixelFormat(displayPixelFormat, YCBCR_420, &support);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs support YCbCr 4:2:0: %d\n", support);

        displayPixelFormat->pVtbl->Release(displayPixelFormat);
        displayPixelFormat = NULL;
    }
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display pixel format support\n");

    printf("\t->Press 2 to get pixel format state\n");

    printf("\t->Press 3 to set current pixel format to RGB_444_FULL\n");
    printf("\t->Press 4 to set current pixel format to YCBCR_444\n");
    printf("\t->Press 5 to set current pixel format to YCBCR_422\n");
    printf("\t->Press 6 to set current pixel format to RGB_444_LIMITED\n");

    printf("\t->Press 7 to get support state for each pixel format\n");

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
            // Display displayPixelFormat support
        case '1':
            ShowDisplayPixelFormatSupport(pDisplayService, pDisplay);
            break;

            // Display current displayPixelFormat state
        case '2':
            GetPixelFormatState(pDisplayService, pDisplay);
            break;

            // Set displayPixelFormat
        case '3':
        case '4':
        case '5':
        case '6':
            SetPixelFormatState(pDisplayService, pDisplay, num - '3');
            break;

            // Get support state for each pixel format
        case '7':
            GetSupportStateForEachPixelFormat(pDisplayService, pDisplay);
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