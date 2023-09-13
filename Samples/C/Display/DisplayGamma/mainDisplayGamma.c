//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayGamma.c
/// \brief Demonstrates how to obtain the display gamma when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplayGamma.h"
#include "SDK/Include/IDisplays.h"

// Print gamma ramp
static void ShowGammaRamp(ADLX_GammaRamp gammaRamp)
{
    for (int j = 0; j < 3; j++)
    {
        printf("\nGetGammaRamp [%c]:\n", (j == 0) ? 'R' : ((j == 1) ? 'G' : (j == 2) ? 'B'
                                                                                     : 'E'));
        for (int i = 0; i < 256; i++)
        {
            printf("%05d ", gammaRamp.gamma[i + j * 256]);
            if (i % 10 == 9)
                printf("\n");
        }
    }
    printf("\n");
}

// Display gamma support
void ShowDisplayGammaSupport(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display gamma
    IADLXDisplayGamma* displayGamma = NULL;
    ADLX_RESULT res = displayService->pVtbl->GetGamma(displayService, display, &displayGamma);
    adlx_bool support = false;
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Re-Gamma supported status ===\n");
        res = displayGamma->pVtbl->IsSupportedReGammaSRGB(displayGamma, &support);
        printf("\tIs sRGB re-gamma supported on this display: %d\n", support);
        res = displayGamma->pVtbl->IsSupportedReGammaBT709(displayGamma, &support);
        printf("\tIs BT709 re-gamma supported on this display: %d\n", support);
        res = displayGamma->pVtbl->IsSupportedReGammaPQ(displayGamma, &support);
        printf("\tIs PQ re-gamma supported on this display: %d\n", support);
        res = displayGamma->pVtbl->IsSupportedReGammaPQ2084Interim(displayGamma, &support);
        printf("\tIs PQ2084Interim re-gamma supported on this display: %d\n", support);
        res = displayGamma->pVtbl->IsSupportedReGamma36(displayGamma, &support);
        printf("\tIs 3.6 re-gamma supported on this display:%d\n", support);
    }

    // Release the displayGamma interface
    if (NULL != displayGamma)
    {
        displayGamma->pVtbl->Release(displayGamma);
        displayGamma = NULL;
    }
}

// Get current gamma state
void GetCurrentGammaState(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get display gamma
    IADLXDisplayGamma* displayGamma;
    ADLX_RESULT res = displayService->pVtbl->GetGamma(displayService, display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Current gamma state ===\n");
        adlx_bool applied = false;
        ADLX_RESULT res = ADLX_FAIL;
        ADLX_GammaRamp ramp;
        ADLX_RegammaCoeff coeff;

        res = displayGamma->pVtbl->IsCurrentReGammaSRGB(displayGamma, &applied);
        printf("\t Is sRGB re-gamma used by this display: %d\n", applied);
        res = displayGamma->pVtbl->IsCurrentReGammaBT709(displayGamma, &applied);
        printf("\tIs BT709 re-gamma used by this display: %d\n", applied);
        res = displayGamma->pVtbl->IsCurrentReGammaPQ(displayGamma, &applied);
        printf("\tIs PQ re-gamma used by this display: %d\n", applied);
        res = displayGamma->pVtbl->IsCurrentReGammaPQ2084Interim(displayGamma, &applied);
        printf("\tIs PQ2084Interim re-gamma used by this display %d\n", applied);
        res = displayGamma->pVtbl->IsCurrentReGamma36(displayGamma, &applied);
        printf("\tIs 3.6 re-gamma used by this display %d\n", applied);

        adlx_bool curCoeff;
        res = displayGamma->pVtbl->IsCurrentRegammaCoefficient(displayGamma, &curCoeff);
        printf("\tIs re-gamma coefficient used by this display %d\n", curCoeff);

        adlx_bool reGammaRamp = false;
        adlx_bool deGammaRamp = false;
        displayGamma->pVtbl->IsCurrentReGammaRamp(displayGamma, &reGammaRamp);
        displayGamma->pVtbl->IsCurrentDeGammaRamp(displayGamma, &deGammaRamp);
        if (reGammaRamp)
        {
            displayGamma->pVtbl->GetGammaRamp(displayGamma, &ramp);
            printf("\tCurrent regamma ramp");
            ShowGammaRamp(ramp);
        }
        else if (deGammaRamp)
        {
            displayGamma->pVtbl->GetGammaRamp(displayGamma, &ramp);
            printf("\tCurrent degamma ramp");
            ShowGammaRamp(ramp);
        }
        else if (curCoeff)
        {
            displayGamma->pVtbl->GetGammaCoefficient(displayGamma, &coeff);
            printf("\tCurrent gamma coefficent");
            printf("\tGet gamma coefficient:\n"
                   "\tA0 %d, A1 %d, A2 %d, A3 %d, Gamma %d\n",
                   coeff.coefficientA0, coeff.coefficientA1,
                   coeff.coefficientA2, coeff.coefficientA3, coeff.gamma);
        }
    }

    // Release the displayGamma interface
    if (NULL != displayGamma)
    {
        displayGamma->pVtbl->Release(displayGamma);
        displayGamma = NULL;
    }
}

// If 0 is retuned SetGammaWithCustomcoeffient is succesfully set else an error occured.
ADLX_RESULT SetGammaWithCustomCoeffs(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    // Get displayGamma
    IADLXDisplayGamma* displayGamma;
    ADLX_RESULT res = displayService->pVtbl->GetGamma(displayService, display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        printf("\t\tPlease enter five integer numbers, separated by spaces(eg: 31308 12920 55 55 2400): \n ");

        ADLX_RESULT res = ADLX_OK;
        ADLX_RegammaCoeff coeff = {0};
        int userKey = 0;
        int coeffs[5] = {31308, 12920, 55, 55, 2400};

        for (int i = 0; i < 5; i++)
        {
            scanf_s("%d", &coeffs[i]);
        }
        coeff.coefficientA0 = coeffs[0];
        coeff.coefficientA1 = coeffs[1];
        coeff.coefficientA2 = coeffs[2];
        coeff.coefficientA3 = coeffs[3];
        coeff.gamma = coeffs[4];
        res = displayGamma->pVtbl->SetReGammaCoefficient(displayGamma, coeff);
    }

    // Release the displayGamma interface
    if (NULL != displayGamma)
    {
        displayGamma->pVtbl->Release(displayGamma);
        displayGamma = NULL;
    }

    return res;
}

// Set Gamma
void SetGamma(IADLXDisplayServices* displayService, IADLXDisplay* display, int key)
{
    // Get displayGamma
    IADLXDisplayGamma* displayGamma = NULL;
    ADLX_RESULT res = displayService->pVtbl->GetGamma(displayService, display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Set gamma ===\n");
        ADLX_RESULT res = ADLX_OK;

        switch (key)
        {
        // Use preset coefficients for ReGammaSRGB
        case 0:
            res = displayGamma->pVtbl->SetReGammaSRGB(displayGamma);
            break;

        // Use custom coefficients
        case 1:
            res = SetGammaWithCustomCoeffs(displayService, display);
            break;

        // Use ramp form file, file path: ../output-night-light.txt
        case 2:
            res = displayGamma->pVtbl->SetReGammaRamp_File(displayGamma, "../output-night-light.txt");
            break;

        // Use ramp from memory
        case 3:
        {
            ADLX_GammaRamp gammaRamp;
            for (unsigned int i = 0; i < 256 * 3; i++)
            {
                gammaRamp.gamma[i] = 255;
            }
            res = displayGamma->pVtbl->SetReGammaRamp_Memory(displayGamma, gammaRamp);
        }
        break;

        // Reset gamma ramp
        case 4:
            res = displayGamma->pVtbl->ResetGammaRamp(displayGamma);
            break;

        default:
            break;
        }
        printf("\treturn is: %d (0 means Success)\n", res);
    }

    // Release the  displayGamma interface
    if (NULL != displayGamma)
    {
        displayGamma->pVtbl->Release(displayGamma);
        displayGamma = NULL;
    }
}

// Main menu
void MainMenu()
{
    printf("\tChoose from following options\n");

    printf("\t->Press 1 to show display gamma support\n");

    printf("\t->Press 2 to display current gamma info\n");

    printf("\t->Press 3 to set ReGammaSRGB using predefined coefficients\n");
    printf("\t->Press 4 to set ReGamma using custom coefficients\n");
    printf("\t->Press 5 to set ReGamma using ramp from file[file path: ../output-night-light.txt]\n");
    printf("\t->Press 6 to set ReGamma using ramp from memory\n");
    printf("\t->Press 7 to reset gamma ramp\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXDisplayServices* displayService, IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display gamma support
        case '1':
            ShowDisplayGammaSupport(displayService, display);
            break;

        // Get current gamma state
        case '2':
            GetCurrentGammaState(displayService, display);
            break;

        // Set gamma
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            SetGamma(displayService, display, num - '3');
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

        // Release the displayService inetrface
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
