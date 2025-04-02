//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayVariBright.c
/// \brief Demonstrates how to obtain the display VariBright when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Display displayVari-Bright support
void ShowDisplayVariBrightSupport( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay);

// Display current displayVari-Bright state
void GetVariBrightEnabled( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay);

// Set display Vari-Bright state to enable or disable
void SetVariBrightEnabled ( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay, adlx_bool enableDisable);

// Get display Vari-Bright current state
void GetCurrentVariBright ( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay, int userChoice);

// Get display Vari-Bright current state
void SetCurrentVariBright ( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay, int userChoice);

// Display supported status, enabled state and set state for Backlight Adaptive Vari-Bright Scaling mode
void BacklightAdaptiveFunctionality(IADLXDisplayVariBright1* displayVariBright1);

// Display supported status, enabled state and set state for Battery Life Vari-Bright Scaling mode
void BatteryLifeFunctionality(IADLXDisplayVariBright1* displayVariBright1);

// Display supported status, enabled state and set state for Windows Power Mode Vari-Bright Scaling mode
void WindowsPowerModeFunctionality(IADLXDisplayVariBright1* displayVariBright1);

// Display supported status, enabled state and set state for Full-Screen Video Vari-Bright Scaling mode
void FullScreenVideoFunctionality(IADLXDisplayVariBright1* displayVariBright1);

// Main menu
void MainMenu();

// Vari-Bright Scaling menu action control
void VariBrightScalingMenuControl(IADLXDisplayVariBright1* displayVariBright1, int userChoice);

// Menu action control
void MenuControl( IADLXDisplayServices* pDisplayService,  IADLXDisplay* pDisplay);

// Wait for exit with error message
int WaitAndExit( char* msg,  int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize ();
    if (ADLX_SUCCEEDED (res))
    {
        // Get system service
        IADLXSystem* sys = ADLXHelper_GetSystemServices ();

        // Get display service
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices (sys, &displayService);
        if (ADLX_SUCCEEDED (res))
        {
            // Get display list
            IADLXDisplayList* displayList = NULL;
            res = displayService->pVtbl->GetDisplays (displayService, &displayList);
            if (ADLX_SUCCEEDED (res))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplay* display = NULL;
                res = displayList->pVtbl->At_DisplayList (displayList, it, &display);
                if (ADLX_SUCCEEDED (res))
                {
                    // Display main menu options
                    MainMenu ();
                    // Get and execute the choice
                    MenuControl (displayService, display);
                }

                // Release the display interface
                if (NULL != display)
                {
                    display->pVtbl->Release (display);
                    display = NULL;
                }
            }

            // Release the displayList interface
            if (NULL != displayList)
            {
                displayList->pVtbl->Release (displayList);
                displayList = NULL;
            }
        }

        // Release the displayService interface
        if (NULL != displayService)
        {
            displayService->pVtbl->Release (displayService);
            displayService = NULL;
        }
    }
    else
    {
        return WaitAndExit ("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate ();
    printf ("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system ("pause");

    return 0;
}

void ShowDisplayVariBrightSupport (IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayVariBright* displayVariBright;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright (pDisplayService, pDisplay, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === Get Vari-Bright supported ===\n");
        adlx_bool supported = false;
        res = displayVariBright->pVtbl->IsSupported (displayVariBright, &supported);
        printf("\tVari-Bright is supported on the display: %s , return code: %d (0 means success)\n", supported ? "true" : "false", res);
        displayVariBright->pVtbl->Release (displayVariBright);
    }
}

void GetVariBrightEnabled (IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    IADLXDisplayVariBright* displayVariBright;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright (pDisplayService, pDisplay, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === Get VariBright enabled ===\n");
        adlx_bool enabled = false;
        res = displayVariBright->pVtbl->IsEnabled (displayVariBright, &enabled);
        printf("\t Vari-Bright is enabled on the display: %s , return code: %d (0 means success)\n", enabled ? "true" : "false", res);
        displayVariBright->pVtbl->Release (displayVariBright);
    }
}

void SetVariBrightEnabled (IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, adlx_bool enableDisable)
{
    IADLXDisplayVariBright* displayVariBright;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright (pDisplayService, pDisplay, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        if (!enableDisable)
        {
            res = displayVariBright->pVtbl->SetEnabled (displayVariBright, false);
            printf ("\tSet enabled to false, result: %d\n", res);
        }
        else
        {
            res = displayVariBright->pVtbl->SetEnabled (displayVariBright, true);
            printf ("\tSet enabled to true, result: %d\n", res);
        }
        displayVariBright->pVtbl->Release (displayVariBright);
    }
}

void GetCurrentVariBright ( IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, int userChoice)
{
    IADLXDisplayVariBright* displayVariBright;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright (pDisplayService, pDisplay, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        adlx_bool applied = false;
        switch (userChoice)
        {
        case 0:
            res = displayVariBright->pVtbl->IsCurrentMaximizeBrightness (displayVariBright, &applied);
            printf("\tMaximize Brightness preset is used on the display: %s, return code: %d (0 means success)\n", (applied ? "Yes" : "No"), res);
            break;

        case 1:
            res = displayVariBright->pVtbl->IsCurrentOptimizeBrightness (displayVariBright, &applied);
            printf("\tOptimize Brightness preset is used on the display: %s, return code: %d (0 means success)\n", (applied ? "Yes" : "No"), res);
            break;

        case 2:
            res = displayVariBright->pVtbl->IsCurrentBalanced (displayVariBright, &applied);
             printf("\tBalanced preset is used on the display: %s, return code: %d (0 means success)\n", (applied ? "Yes" : "No"), res);
            break;

        case 3:
            res = displayVariBright->pVtbl->IsCurrentOptimizeBattery (displayVariBright, &applied);
            printf("\tOptimize Battery preset is used on the display: %s, return code: %d (0 means success)\n", (applied ? "Yes" : "No"), res);
            break;

        case 4:
            res = displayVariBright->pVtbl->IsCurrentMaximizeBattery (displayVariBright, &applied);
            printf("\tMaximize Battery preset is used on the display: %s, return code: %d (0 means success)\n", (applied ? "Yes" : "No"), res);
            break;
        }
        displayVariBright->pVtbl->Release (displayVariBright);
    }
}

void SetCurrentVariBright ( IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, int userChoice)
{
    IADLXDisplayVariBright* displayVariBright;
    ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright (pDisplayService, pDisplay, &displayVariBright);
    if (ADLX_SUCCEEDED (res))
    {
        switch (userChoice)
        {
        case 0:
            res = displayVariBright->pVtbl->SetMaximizeBrightness (displayVariBright);
            printf ("\t Set Maximize Brightness preset , result: %d\n", res);
            break;

        case 1:
            res = displayVariBright->pVtbl->SetOptimizeBrightness (displayVariBright);
            printf ("\t Set Optimize Brightness preset , result: %d\n", res);
            break;

        case 2:
            res = displayVariBright->pVtbl->SetBalanced (displayVariBright);
            printf ("\t Set Balanced preset, result: %d\n", res);
            break;
        case 3:
            res = displayVariBright->pVtbl->SetOptimizeBattery (displayVariBright);
            printf ("\t Set Optimize Battery preset, result: %d\n", res);
            break;

        case 4:
            res = displayVariBright->pVtbl->SetMaximizeBattery (displayVariBright);
            printf ("\t Set Maximize Battery preset , result: %d\n", res);
            break;
        }
        displayVariBright->pVtbl->Release (displayVariBright);
    }
}

void BacklightAdaptiveFunctionality(IADLXDisplayVariBright1* displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->pVtbl->IsBacklightAdaptiveSupported(displayVariBright1, &supported);
            printf("\t\tBacklight Adaptive Vari-Bright Scaling mode is supported on the display: %s, return code: %d (0 means success)\n", (supported ? "true" : "false"), res);
            break;
        case '2':
            res = displayVariBright1->pVtbl->IsBacklightAdaptiveEnabled(displayVariBright1, &enabled);
            printf("\t\tBacklight Adaptive Vari-Bright Scaling mode is enabled on the display: %s, return code: %d (0 means success)\n", (enabled ? "true" : "false"), res);
            break;
        case '3':
            res = displayVariBright1->pVtbl->SetBacklightAdaptiveEnabled(displayVariBright1, true);
            printf("\t\tSet Backlight Adaptive Vari-Bright Scaling mode enabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        case '4':
            res = displayVariBright1->pVtbl->SetBacklightAdaptiveEnabled(displayVariBright1, false);
            printf("\t\tSet Backlight Adaptive Vari-Bright Scaling mode disabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Battery Life Vari-Bright Scaling mode
void BatteryLifeFunctionality(IADLXDisplayVariBright1* displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->pVtbl->IsBatteryLifeSupported(displayVariBright1, &supported);
            printf("\t\tBattery Life Vari-Bright Scaling mode is supported on the display: %s, return code: %d (0 means success)\n", (supported ? "true" : "false"), res);
            break;
        case '2':
            res = displayVariBright1->pVtbl->IsBatteryLifeEnabled(displayVariBright1, &enabled);
            printf("\t\tBattery Life Vari-Bright Scaling mode is enabled on the display: %s, return code: %d (0 means success)\n", (enabled ? "true" : "false"), res);
            break;
        case '3':
            res = displayVariBright1->pVtbl->SetBatteryLifeEnabled(displayVariBright1, true);
            printf("\t\tSet Battery Life Vari-Bright Scaling mode enabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        case '4':
            res = displayVariBright1->pVtbl->SetBatteryLifeEnabled(displayVariBright1, false);
            printf("\t\tSet Battery Life Vari-Bright Scaling mode disabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Windows Power Mode Vari-Bright Scaling mode
void WindowsPowerModeFunctionality(IADLXDisplayVariBright1* displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->pVtbl->IsWindowsPowerModeSupported(displayVariBright1, &supported);
            printf("\t\tWindows Power Mode Vari-Bright Scaling mode is supported on the display: %s, return code: %d (0 means success)\n", (supported ? "true" : "false"), res);
            break;
        case '2':
            res = displayVariBright1->pVtbl->IsWindowsPowerModeEnabled(displayVariBright1, &enabled);
            printf("\t\tWindows Power Mode Vari-Bright Scaling mode is enabled on the display: %s, return code: %d (0 means success)\n", (enabled ? "true" : "false"), res);
            break;
        case '3':
            res = displayVariBright1->pVtbl->SetWindowsPowerModeEnabled(displayVariBright1, true);
            printf("\t\tSet Windows Power Mode Vari-Bright Scaling mode enabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        case '4':
            res = displayVariBright1->pVtbl->SetWindowsPowerModeEnabled(displayVariBright1, false);
            printf("\t\tSet Windows Power Mode Vari-Bright Scaling mode disabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        default:
            break;
        }
    }
}

// Display supported status, enabled state and set state for Full-Screen Video Vari-Bright Scaling mode
void FullScreenVideoFunctionality(IADLXDisplayVariBright1* displayVariBright1)
{
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool supported = false, enabled = false;
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            res = displayVariBright1->pVtbl->IsFullScreenVideoSupported(displayVariBright1, &supported);
            printf("\t\tFull-Screen Video Vari-Bright Scaling mode is supported on the display: %s, return code: %d (0 means success)\n", (supported ? "true" : "false"), res);
            break;
        case '2':
            res = displayVariBright1->pVtbl->IsFullScreenVideoEnabled(displayVariBright1, &enabled);
            printf("\t\tFull-Screen Video Vari-Bright Scaling mode is enabled on the display: %s, return code: %d (0 means success)\n", (enabled ? "true" : "false"), res);
            break;
        case '3':
            res = displayVariBright1->pVtbl->SetFullScreenVideoEnabled(displayVariBright1, true);
            printf("\t\tSet Full-Screen Video Vari-Bright Scaling mode enabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        case '4':
            res = displayVariBright1->pVtbl->SetFullScreenVideoEnabled(displayVariBright1, false);
            printf("\t\tSet Full-Screen Video Vari-Bright Scaling mode disabled %s\n", (ADLX_SUCCEEDED(res) ? "successfully" : "failed"));
            break;
        default:
            break;
        }
    }
}

void MainMenu()
{
    printf ("\tChoose from the following options:\n");

    printf ("\t->Press 1 to display Vari-Bright support\n");
    printf ("\t->Press 2 to get Vari-Bright Enable state\n");
    printf ("\t->Press 3 to enable Vari-Bright\n");
    printf ("\t->Press 4 to Disbale Vari-Bright\n");
    printf ("\t->Press 5 to check if Vari-Bright mode is maximized brightness preset on the display\n");
    printf ("\t->Press 6 to check if Vari-Bright mode is optimized brightness preset on the display\n");
    printf ("\t->Press 7 to check if Vari-Bright mode is balanced preseton the display\n");
    printf ("\t->Press 8 to check if Vari-Bright mode is optimized battery preset on the display\n");
    printf ("\t->Press 9 to check if Vari-Bright mode is maximized battery preset on the display\n");
    printf ("\t->Press a to set the Vari-Bright mode to maximized brightness preset on the display\n");
    printf ("\t->Press b to set the Vari-Bright mode to optimized brightness preset on the display\n");
    printf ("\t->Press c to set the Vari-Bright mode to balanced preset on the display\n");
    printf ("\t->Press d to set the Vari-Bright mode to optimized battery preset on the display\n");
    printf ("\t->Press e to sets the Vari-Bright mode to maximized battery preset on the display\n");
    // Vari-Bright Scaling
    printf("\t->Press f to use Backlight Adaptive Vari-Bright Scaling mode functionality on the display\n");
    printf("\t->Press g to use Battery Life Vari-Bright Scaling mode functionality on the display\n");
    printf("\t->Press h to use Windows Power Mode Vari-Bright Scaling mode functionality on the display\n");
    printf("\t->Press i to use Full-Screen Video Vari-Bright Scaling mode functionality on the display\n");

    printf ("\t->Press Q/q to terminate the application\n");
    printf ("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl( IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display displayVariBright support
        case '1':
            ShowDisplayVariBrightSupport (pDisplayService, pDisplay);
            break;

            // Display current display VariBright state
        case '2':
            GetVariBrightEnabled (pDisplayService, pDisplay);
            break;

            // Set display VariBright enable
        case '3':
            SetVariBrightEnabled (pDisplayService, pDisplay, true);
            break;

            // Set display VariBright disable
        case '4':
            SetVariBrightEnabled (pDisplayService, pDisplay, false);
            break;

        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            GetCurrentVariBright (pDisplayService, pDisplay, num - '5');
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
            SetCurrentVariBright (pDisplayService, pDisplay, num - 'a');
            break;

        case 'f':
        case 'g':
        case 'h':
        case 'i':
        {
            IADLXDisplayVariBright* displayVariBright = NULL;
            ADLX_RESULT res = pDisplayService->pVtbl->GetVariBright(pDisplayService, pDisplay, &displayVariBright);
            if (ADLX_SUCCEEDED(res))
            {
                IADLXDisplayVariBright1* displayVariBright1 = NULL;
                ADLX_RESULT res = displayVariBright->pVtbl->QueryInterface(displayVariBright, IID_IADLXDisplayVariBright1(), (void**)&displayVariBright1);
                if (ADLX_SUCCEEDED(res))
                {
                    VariBrightScalingMenuControl(displayVariBright1, num - 'f');
                    if (NULL != displayVariBright1)
                    {
                        displayVariBright1->pVtbl->Release(displayVariBright1);
                        displayVariBright1 = NULL;
                    }
                }
                else
                    printf("Failed to get the Vari-Bright Scaling\n");

                if (NULL != displayVariBright)
                {
                    displayVariBright->pVtbl->Release(displayVariBright);
                    displayVariBright = NULL;
                }
            }
            else
                printf("Failed to get the Vari-Bright\n");
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
}

// Vari-Bright Scaling menu action control
void VariBrightScalingMenuControl(IADLXDisplayVariBright1* displayVariBright1, int userChoice)
{
    switch (userChoice)
    {
    case 0:
        printf("\t\t->Press 1 to check if Backlight Adaptive Vari-Bright Scaling mode is supported on a display\n");
        printf("\t\t->Press 2 to check if Backlight Adaptive Vari-Bright Scaling mode is enabled on a display\n");
        printf("\t\t->Press 3 to set Backlight Adaptive Vari-Bright Scaling mode enabled on a display\n");
        printf("\t\t->Press 4 to set Backlight Adaptive Vari-Bright Scaling mode disabled on a display\n");
        printf("\t\t->Press Q/q to go back to the previous menu\n");
        BacklightAdaptiveFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 1:
        printf("\t\t->Press 1 to check if Battery Life Vari-Bright Scaling mode is supported on a display\n");
        printf("\t\t->Press 2 to check if Battery Life Vari-Bright Scaling mode is enabled on a display\n");
        printf("\t\t->Press 3 to set Battery Life Vari-Bright Scaling mode enabled on a display\n");
        printf("\t\t->Press 4 to set Battery Life Vari-Bright Scaling mode disabled on a display\n");
        printf("\t\t->Press Q/q to go back to the previous menu\n");
        BatteryLifeFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 2:
        printf("\t\t->Press 1 to check if Windows Power Mode Vari-Bright Scaling mode is supported on a display\n");
        printf("\t\t->Press 2 to check if Windows Power Mode Vari-Bright Scaling mode is enabled on a display\n");
        printf("\t\t->Press 3 to set Windows Power Mode Vari-Bright Scaling mode enabled on a display\n");
        printf("\t\t->Press 4 to set Windows Power Mode Vari-Bright Scaling mode disabled on a display\n");
        printf("\t\t->Press Q/q to go back to the previous menu\n");
        WindowsPowerModeFunctionality(displayVariBright1);
        MainMenu();
        break;

    case 3:
        printf("\t\t->Press 1 to check if Full-Screen Video Vari-Bright Scaling mode is supported on a display\n");
        printf("\t\t->Press 2 to check if Full-Screen Video Vari-Bright Scaling mode is enabled on a display\n");
        printf("\t\t->Press 3 to set Full-Screen Video Vari-Bright Scaling mode enabled on a display\n");
        printf("\t\t->Press 4 to set Full-Screen Video Vari-Bright Scaling mode disabled on a display\n");
        printf("\t\t->Press Q/q to go back to the previous menu\n");
        FullScreenVideoFunctionality(displayVariBright1);
        MainMenu();
        break;

    default:
        break;
    }
}

// Wait for exit with error message
int WaitAndExit( char* msg,  int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf ("%s\n", msg);

    system("Pause");
    return retCode;
}