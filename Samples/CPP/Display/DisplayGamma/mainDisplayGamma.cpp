//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayGamma.cpp
/// \brief Demonstrates how to obtain the display Gamma when programming with ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplayGamma.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <vector>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX destory.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Print Gamma ramp
static void ShowGammaRamp(const ADLX_GammaRamp& gammaRamp);

// Display Gamma support
void ShowDisplayGammaSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Get current Gamma state
void GetCurrentGammaState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

//  Set gamma by coefficient; if return value is 0, gamma coefficient is successfully set. Else an error occured.
ADLX_RESULT SetGammaWithCustomCoeffs(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Set Gamma
void SetGamma(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Create regamma ramp
ADLX_GammaRamp CreateReGammaRamp(const float fGamma);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get display service
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display list
            IADLXDisplayListPtr displayList;
            res = displayService->GetDisplays(&displayList);
            if (ADLX_SUCCEEDED (res))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplayPtr display;
                res = displayList->At(it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and parse the selection
                    MenuControl(displayService, display);
                }
            }
            else
            {
                std::cout << "Failed to get the display list" << std::endl;
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get the Display Services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the printout
    system("pause");

    return 0;
}

// Print gamma ramp
static void ShowGammaRamp(const ADLX_GammaRamp& gammaRamp)
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

// Display gamma support status
void ShowDisplayGammaSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display gamma
    IADLXDisplayGammaPtr displayGamma;
    ADLX_RESULT res = displayService->GetGamma(display, &displayGamma);
    adlx_bool support = false;
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Re-Gamma supported status ===" << std::endl;
        res = displayGamma->IsSupportedReGammaSRGB(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedReGammaSRGB: " << support << std::endl;
        res = displayGamma->IsSupportedReGammaBT709(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedReGammaBT709: " << support << std::endl;
        res = displayGamma->IsSupportedReGammaPQ(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedReGammaPQ: " << support << std::endl;
        res = displayGamma->IsSupportedReGammaPQ2084Interim(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedReGammaPQ2084Interim: " << support << std::endl;
        res = displayGamma->IsSupportedReGamma36(&support);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedReGamma36:" << support << std::endl;
    }
}

// Get current gamma state
void GetCurrentGammaState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display gamma
    IADLXDisplayGammaPtr displayGamma;
    ADLX_RESULT res = displayService->GetGamma(display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Current gamma state ===" << std::endl;
        adlx_bool applied = false;
        ADLX_RESULT res = ADLX_FAIL;
        ADLX_GammaRamp ramp;
        ADLX_RegammaCoeff coeff;

        res = displayGamma->IsCurrentReGammaSRGB(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentReGammaSRGB " << applied << std::endl;
        res = displayGamma->IsCurrentReGammaBT709(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentReGammaBT709 " << applied << std::endl;
        res = displayGamma->IsCurrentReGammaPQ(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentReGammaPQ " << applied << std::endl;
        res = displayGamma->IsCurrentReGammaPQ2084Interim(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentReGammaPQ2084Interim " << applied << std::endl;
        res = displayGamma->IsCurrentReGamma36(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentReGamma36 " << applied << std::endl;

        adlx_bool curCoeff;
        res = displayGamma->IsCurrentRegammaCoefficient(&curCoeff);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentRegammaCoefficient " << curCoeff << std::endl;

        adlx_bool reGammaRamp = false;
        adlx_bool deGammaRamp = false;
        res = displayGamma->IsCurrentReGammaRamp(&reGammaRamp);
        res = displayGamma->IsCurrentDeGammaRamp(&deGammaRamp);
        if (reGammaRamp)
        {
            displayGamma->GetGammaRamp(&ramp);
            std::cout << "\tcurrent reGammaRamp" << std::endl;
            ShowGammaRamp(ramp);
        }
        else if (deGammaRamp)
        {
            displayGamma->GetGammaRamp(&ramp);
            std::cout << "\tcurrent deGammaRamp" << std::endl;
            ShowGammaRamp(ramp);
        }
        else if (curCoeff)
        {
            displayGamma->GetGammaCoefficient(&coeff);
            std::cout << "\tcurrent coefficient" << std::endl;
            std::cout << "\tGetGammaCoefficient:\n"
                      << "\tCoefficientA0 " << coeff.coefficientA0 << ","
                      << "CoefficientA1 " << coeff.coefficientA1 << ", "
                      << "CoefficientA2 " << coeff.coefficientA2 << ", "
                      << "CoefficientA3 " << coeff.coefficientA3 << ", "
                      << "Gamma " << coeff.gamma << std::endl;
        }
    }
}

//  Set gamma by coefficient; if return value is 0, gamma coefficient is successfully set. Else an error occured.
ADLX_RESULT SetGammaWithCustomCoeffs(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display gamma
    IADLXDisplayGammaPtr displayGamma;
    ADLX_RESULT res = displayService->GetGamma(display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "\t\tPlease enter five integer numbers, separated by spaces. (eg: 31308 12920 55 55 2400)" << std::endl;

        ADLX_RESULT res = ADLX_OK;
        ADLX_RegammaCoeff coeff;
        int userKey = 0;
        std::vector<int> coeffs;
        while (std::cin >> userKey)
        {
            coeffs.push_back(userKey);
            if (coeffs.size() > 4)
                break;
        }
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        if (coeffs.size() > 4)
        {
            coeff.coefficientA0 = coeffs[0]; // 31308;
            coeff.coefficientA1 = coeffs[1]; // 12920;
            coeff.coefficientA2 = coeffs[2]; // 55;
            coeff.coefficientA3 = coeffs[3]; // 55;
            coeff.gamma = coeffs[4];         // 2400;
        }
        else
        {
            std::cout << "\t\tInvalid input, default value will be used." << std::endl;
            coeff.coefficientA0 = 31308;
            coeff.coefficientA1 = 12920;
            coeff.coefficientA2 = 55;
            coeff.coefficientA3 = 55;
            coeff.gamma = 2400;
        }
        res = displayGamma->SetReGammaCoefficient(coeff);
    }
    return res;
}

// Set Gamma
void SetGamma(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    // Get display Gamma
    IADLXDisplayGammaPtr displayGamma;
    ADLX_RESULT res = displayService->GetGamma(display, &displayGamma);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Set gamma ===" << std::endl;
        ADLX_RESULT res = ADLX_OK;

        switch (key)
        {
        // Use preset coefficients for ReGammaSRGB
        case 0:
            res = displayGamma->SetReGammaSRGB();
            break;

        // Use preset coefficients for DeGammaSRGB
        case 1:
            res = SetGammaWithCustomCoeffs(displayService, display);
            break;

        // use ramp form file, file path: ../output-night-light.txt
        case 2:
            res = displayGamma->SetReGammaRamp("../output-night-light.txt");
            break;

        // Use ramp from memory
        case 3:
        {
            const float reGammaF = 2.4f;
            ADLX_GammaRamp  ramp = CreateReGammaRamp(reGammaF);
            res = displayGamma->SetReGammaRamp(ramp);
        }
        break;

        // Reset ramp
        case 4:
            res = displayGamma->ResetGammaRamp();
            break;

        default:
            break;
        }
        std::cout << "\tReturn code is: " << res <<" (0 means success) "<< std::endl;
    }
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to show display gamma support" << std::endl;

    std::cout << "\t->Press 2 to display current gamma info" << std::endl;

    std::cout << "\t->Press 3 to set ReGammaSRGB using predefined coefficients" << std::endl;
    std::cout << "\t->Press 4 to set ReGamma using custom coefficients" << std::endl;
    std::cout << "\t->Press 5 to set ReGamma using ramp from file[file path: ../output-night-light.txt]" << std::endl;
    std::cout << "\t->Press 6 to set ReGamma using ramp from memory" << std::endl;
    std::cout << "\t->Press 7 to reset Gamma ramp" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Show Gamma support
        case '1':
            ShowDisplayGammaSupport(displayService, display);
            break;

        // Get current Gamma state
        case '2':
            GetCurrentGammaState(displayService, display);
            break;

        // Set Gamma
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            SetGamma(displayService, display, num - '3');
            break;

        // Show options again
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
    //  Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

ADLX_GammaRamp CreateReGammaRamp(const float fGamma)
{
    ADLX_GammaRamp ramp;
    double g_fGammaRemapRGB[3] = { 1,1,0.5 };
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 256; i++)
        {

            float nAdj = i / 255.0f;
            if (nAdj < 0.0031308f)
            {
                nAdj = nAdj * 12.92f;
            }
            else
            {
                nAdj = (1 + 0.055f) * powf(nAdj, 1 / fGamma) - 0.055f;
                if (nAdj < 0.0f)
                    nAdj = 0.0f;
            }
            ramp.gamma[i + j * 256] = (unsigned short)(1 * g_fGammaRemapRGB[j] * (int)(nAdj * 0xFFFF));
        }
    }
    return ramp;
}