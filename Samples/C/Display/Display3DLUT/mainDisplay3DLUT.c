//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplay3DLUT.c
/// \brief Demonstrates how to obtain the display 3DLUT when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplay3DLUT.h"
#include "SDK/Include/IDisplays.h"
#include <math.h>

const adlx_int DefaultNumOfPoints = MAX_USER_3DLUT_NUM_POINTS;

// Display display3DLUT support
void ShowDisplay3DLUTSupport (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === 3D LUT supported status ===\n");
        adlx_bool supported;
        ADLX_RESULT res = display3DLUT->pVtbl->IsSupportedSCE (display3DLUT, &supported);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs SCE supported on this display: %d\n", supported);
        res = display3DLUT->pVtbl->IsSupportedSCEVividGaming (display3DLUT, &supported);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs SCE Vivid Gaming preset supported on this display: %d\n", supported);
        res = display3DLUT->pVtbl->IsSupportedSCEDynamicContrast(display3DLUT, &supported);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs SCE Dynamic Contrast supported on this display: %d\n", supported);
        res = display3DLUT->pVtbl->IsSupportedUser3DLUT (display3DLUT, &supported);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs 3DLUT supported on this display: %d\n", supported);
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Display current display3DLUT state
void Get3DLUTState (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === Get 3D LUT ===\n");
        adlx_bool applied = false;
        res = display3DLUT->pVtbl->IsCurrentSCEDisabled (display3DLUT, &applied);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs SCE used on this display: %d\n", applied);
        res = display3DLUT->pVtbl->IsCurrentSCEVividGaming (display3DLUT, &applied);
        if (ADLX_SUCCEEDED(res))
            printf ("\tIs SCE Vivid Gaming preset used on this display: %d\n", applied);
        res = display3DLUT->pVtbl->IsCurrentSCEDynamicContrast(display3DLUT, &applied);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs SCE Vivid Dynamic Contrast preset used on this display: %d\n", applied);
        if (applied)
        {
            ADLX_IntRange range;
            display3DLUT->pVtbl->GetSCEDynamicContrastRange(display3DLUT, &range);
            printf("\t\tDynamic Contrast range is: [ %d, %d ]\n", range.minValue, range.maxValue);
            adlx_int contrast;
            display3DLUT->pVtbl->GetSCEDynamicContrast(display3DLUT, &contrast);
            printf("\t\tDynamic Contrast is: %d\n", contrast);
        }
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Set display3DLUT
void Set3DLUTState (IADLXDisplayServices* displayService, IADLXDisplay* display, int key)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === Set 3D LUT ===\n");
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set SCE disabled
        case 0:
            res = display3DLUT->pVtbl->SetSCEDisabled (display3DLUT);
            break;
            // Set SCE Vivid Gaming preset
        case 1:
            res = display3DLUT->pVtbl->SetSCEVividGaming (display3DLUT);
            break;
            // Set SCE Dynamic Contrast
        case 2:
        {
            ADLX_IntRange range;
            display3DLUT->pVtbl->GetSCEDynamicContrastRange(display3DLUT, &range);
            adlx_int curContrast;
            display3DLUT->pVtbl->GetSCEDynamicContrast(display3DLUT, &curContrast);
            adlx_int contrast;
            if (curContrast != range.minValue)
            {
                contrast = range.minValue;
                res = display3DLUT->pVtbl->SetSCEDynamicContrast(display3DLUT, contrast);
                printf ("\tUse minimum Dynamic Contrast\n");
            }
            else
            {
                contrast = range.maxValue;
                res = display3DLUT->pVtbl->SetSCEDynamicContrast(display3DLUT, contrast);
                printf("\tUse maximum Dynamic Contrast\n");
            }
        }
        break;
        default:
            break;
        }
        printf ("\treturn code(0 means Success) is: %d\n", res);
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Get user 3D LUT support
void IsSupportedUser3DLUT (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === IsSupportedUser3DLUT ===\n");
        adlx_bool supported = false;
        res = display3DLUT->pVtbl->IsSupportedUser3DLUT (display3DLUT, &supported);
        if (ADLX_SUCCEEDED (res))
        {
            printf ("  === IsSupportedUser3DLUT: %s\n", (supported ? "True" : "False"));
        }
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Clear user 3D LUT
void ClearUser3DLUT (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === ClearUser3DLUT ===\n");
        res = display3DLUT->pVtbl->ClearUser3DLUT (display3DLUT);
        if (ADLX_SUCCEEDED (res))
        {
            printf ("  === ClearUser3DLUT successful ===\n");
        }
        else
            printf ("  === ClearUser3DLUT failed ===\n");
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Helper functions
inline double Inputvalue (int index, int bitDepth, int numOfPoints)
{
    return fmin ((float)(index * pow (2, bitDepth) / (float)(numOfPoints - 1)), pow (2, bitDepth) - 1);
}

// Generate 3D LUT data
adlx_bool GenerateUser3DLUT_BW (IADLXDisplayServices* displayService, IADLXDisplay* display, adlx_int numOfPoints, ADLX_3DLUT_Data* user3DLUT)
{
    adlx_bool ret = true;
    const int bitDepth = 16;

    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        ADLX_UINT16_RGB rgbCordinate = { 0, 0, 0 };
        adlx_int index = 0;

        for (int r = 0; r < numOfPoints; r++)
        {
            for (int g = 0; g < numOfPoints; g++)
            {
                for (int b = 0; b < numOfPoints; b++)
                {
                    rgbCordinate.red = r;
                    rgbCordinate.green = g;
                    rgbCordinate.blue = b;

                    double temp = 0.25 * Inputvalue (r, bitDepth, numOfPoints) + 0.625 * Inputvalue (g, bitDepth, numOfPoints) + 0.125 * Inputvalue (b, bitDepth, numOfPoints);
                    res = display3DLUT->pVtbl->GetUser3DLUTIndex (display3DLUT, numOfPoints, &rgbCordinate, &index);

                    if (ADLX_SUCCEEDED (res))
                    {
                        adlx_uint16 tValue = (adlx_uint16)(temp);
                        user3DLUT->data[index].red = tValue;
                        user3DLUT->data[index].green = tValue;
                        user3DLUT->data[index].blue = tValue;
                    }
                    else
                    {
                        ret = false;
                        goto EXIT;
                    }
                }
            }
        }
    }

    // Release the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }

EXIT:
    return ret;
}

// Get or Set SDR user 3DLUT
void DemoSDRUser3DLUT (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        // Generate data
        if (GenerateUser3DLUT_BW (displayService, display, DefaultNumOfPoints, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            printf ("  === SetSDRUser3DLUT ===\n");
            res = display3DLUT->pVtbl->SetSDRUser3DLUT (display3DLUT, tf, cs, DefaultNumOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === SetSDRUser3DLUT successful ===\n");
            }
            else
                printf ("  === SetSDRUser3DLUT failed ===\n");

            printf ("  === GetSDRUser3DLUT ===\n");
            res = display3DLUT->pVtbl->GetSDRUser3DLUT (display3DLUT, &tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === GetSDRUser3DLUT successful ===\n");
            }
            else
                printf ("  === GetSDRUser3DLUT failed ===\n");

            // Clear
            res = display3DLUT->pVtbl->ClearUser3DLUT (display3DLUT);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === Clear successful ===\n");
            }
            else
                printf ("  === Clear failed ===\n");
        }
    }

    // Releae the display3DLUT interface
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Get  or Set HDR user 3DLUT
void DemoHDRUser3DLUT (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        // Generate data
        if (GenerateUser3DLUT_BW (displayService, display, DefaultNumOfPoints, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            printf ("  === SetHDRUser3DLUT ===\n");

            res = display3DLUT->pVtbl->SetHDRUser3DLUT (display3DLUT, tf, cs, DefaultNumOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === SetHDRUser3DLUT successful ===\n");
            }
            else
                printf ("  === SetHDRUser3DLUT failed ===\n");

            printf ("  === GetHDRUser3DLUT ===\n");
            res = display3DLUT->pVtbl->GetHDRUser3DLUT (display3DLUT, &tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === GetHDRUser3DLUT successful ===\n");
            }
            else
                printf ("  === GetHDRUser3DLUT failed ===\n");

            // Clear
            res = display3DLUT->pVtbl->ClearUser3DLUT (display3DLUT);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === Restore successful ===\n");
            }
            else
                printf ("  === Restore failed ===\n");
        }
    }

    // Free display3DLUT
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Get/Set all user 3DLUT
void DemoAllUser3DLUT (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        // Generate data
        if (GenerateUser3DLUT_BW (displayService, display, DefaultNumOfPoints, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            printf ("  === SetAllUser3DLUT ===\n");

            res = display3DLUT->pVtbl->SetAllUser3DLUT (display3DLUT, tf, cs, DefaultNumOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === SetAllUser3DLUT successful ===\n");
            }
            else
                printf ("  === SetAllUser3DLUT failed ===\n");

            printf ("  === GetAllUser3DLUT ===\n");
            res = display3DLUT->pVtbl->GetAllUser3DLUT (display3DLUT, &tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === GetAllUser3DLUT succesful ===\n");
            }
            else
                printf ("  === GetAllUser3DLUT failed ===\n");

            // Clear
            display3DLUT->pVtbl->ClearUser3DLUT (display3DLUT);
            if (ADLX_SUCCEEDED (res))
            {
                printf ("  === Clear successful ===\n");
            }
            else
                printf ("  === Clear failed ===\n");
        }
    }

    // Free display3DLUT
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Get 3DLUT index
void GetUser3DLUTIndex (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display3DLUT
    IADLXDisplay3DLUT* display3DLUT = NULL;
    ADLX_RESULT res = displayService->pVtbl->Get3DLUT (displayService, display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        printf ("  === Get user 3DLUT index ===\n");;

        adlx_int index = 0;
        adlx_int lutSize = 6; //5 <= lutSize <= 17
        ADLX_UINT16_RGB rgb = { 0, 0, 0 };

        res = display3DLUT->pVtbl->GetUser3DLUTIndex (display3DLUT, lutSize, &rgb, &index);
        if (ADLX_SUCCEEDED (res))
        {
            printf ("  === Get user3 DLUT index successful, index: %d===\n", index);
        }
        else
            printf ("  === Get user 3DLUT index failed ===\n");;
    }

    // Free display3DLUT
    if (NULL != display3DLUT)
    {
        display3DLUT->pVtbl->Release (display3DLUT);
        display3DLUT = NULL;
    }
}

// Main menu
void MainMenu ()
{
    printf ("\tChoose from following options\n");

    printf ("\t->Press 1 to display 3DLUT support\n");

    printf ("\t->Press 2 to get 3DLUT state\n");

    printf ("\t->Press 3 to set current SCE to disabled\n");
    printf ("\t->Press 4 to set current SCE feature to Vivid Gaming preset\n");
    printf ("\t->Press 5 to set current SCE feature to Dynamic Contrast\n");

    printf ("\t->Press 6 to get user 3DLUT support\n");
    printf ("\t->Press 7 to clear user 3DLUT\n");
    printf ("\t->Press 8 to show how to set/get SDR user 3DLUT\n");
    printf ("\t->Press 9 to show how to set/get HDR user 3DLUT\n");
    printf ("\t->Press a to show how to set/get all user 3DLUT\n");
    printf ("\t->Press b to get 3DLUT index\n");

    printf ("\t->Press Q/q to terminate the application\n");
    printf ("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl (IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar ()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            ShowDisplay3DLUTSupport (displayService, display);
            break;
        case '2':
            Get3DLUTState (displayService, display);
            break;
        case '3':
        case '4':
        case '5':
            Set3DLUTState (displayService, display, num - '3');
            break;
        case '6':
            IsSupportedUser3DLUT (displayService, display);
            break;
        case '7':
            ClearUser3DLUT (displayService, display);
            break;
        case '8':
            DemoSDRUser3DLUT (displayService, display);
            break;
        case '9':
            DemoHDRUser3DLUT (displayService, display);
            break;
        case 'a':
            DemoAllUser3DLUT (displayService, display);
            break;
        case 'b':
            GetUser3DLUTIndex (displayService, display);
            break;
            // Display main menu options
        case 'm':
        case 'M':
            MainMenu ();
            break;
        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf ("%s\n", msg);

    system ("pause");
    return retCode;
}

int main ()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize ();
    if (ADLX_SUCCEEDED (res))
    {
        // Get system services
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
    printf ("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system ("pause");

    return 0;
}