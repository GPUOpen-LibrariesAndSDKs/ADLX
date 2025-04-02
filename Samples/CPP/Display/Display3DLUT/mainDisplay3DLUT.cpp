//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplay3DLUT.cpp
/// \brief Demonstrates how to obtain the display 3DLUT when programming with ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplay3DLUT.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>

// Use adlx namespace
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Constant value used to set size of user 3D LUT data
constexpr auto DEFAULT_NUM_OF_POINTS = MAX_USER_3DLUT_NUM_POINTS;

// Show display3DLUT support
void ShowDisplay3DLUTSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Get and show current display3DLUT state
void Get3DLUTState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Set display3DLUT
void Set3DLUTState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key);
// Get user 3DLUT support
void IsSupportedUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Clear user 3DLUT
void ClearUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Get or Set SDR user 3DLUT
void DemoSDRUser3DLUT (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Get or Set HDR user 3DLUT
void DemoHDRUser3DLUT (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Get or Set all user 3DLUT
void DemoAllUser3DLUT (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);
// Get 3DLUT index
void GetUser3DLUTIndex(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Helper functions

// Algorigthm to generate a value which ranges from 0 to 0xFFFF
inline double Inputvalue (int index, int bitDepth, int numOfPoints)
{
    return fmin (static_cast<float>(index * pow (2, bitDepth) / static_cast<float>(numOfPoints - 1)), pow (2, bitDepth) - 1);
}

// The 3DLUT are three axes of a 3-dimensional cube
// Generate 3DLut data bit wise: 17*17*17 triplets/lattice of RGB values.
// Each triplet contains the component of RGB values(16-bit depth) from 0 to 0xFFFF.
adlx_bool GenerateUser3DLUT_BW (const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, adlx_int numOfPoints, ADLX_3DLUT_Data* user3DLUT)
{
    adlx_bool ret = true;

    const int bitDepth = 16;

    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT (display, &display3DLUT);
    if (ADLX_SUCCEEDED (res))
    {
        ADLX_UINT16_RGB rgbCoordinate = { 0, 0, 0 };
        adlx_int index = 0;

        for (int r = 0; r < numOfPoints; r++)
        {
            for (int g = 0; g < numOfPoints; g++)
            {
                for (int b = 0; b < numOfPoints; b++)
                {
                    rgbCoordinate.red = r;
                    rgbCoordinate.green = g;
                    rgbCoordinate.blue = b;

                    //Recalculate 3DLUT based on the "Inputvalue" which ranges from 0 to 0xFFFF. The recalculated value falls in the same range of 0 to 0xFFFF to be more "random".
                    double temp = 0.25 * Inputvalue (r, bitDepth, numOfPoints) + 0.625 * Inputvalue (g, bitDepth, numOfPoints) + 0.125 * Inputvalue (b, bitDepth, numOfPoints);

                    // Get the index in the 3D LUT buffer corresponding to the RGB triplet.
                    res = display3DLUT->GetUser3DLUTIndex (numOfPoints, &rgbCoordinate, &index);

                    if (ADLX_SUCCEEDED (res))
                    {
                        adlx_uint16 tValue = static_cast<adlx_uint16>(temp);
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

EXIT:
    return ret;
}

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
            if (ADLX_SUCCEEDED(res))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplayPtr display;
                res = displayList->At(it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(displayService, display);
                }
            }
            else
            {
                std::cout << "Failed to get Display list" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get Display Services" << std::endl;
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

// Display display3DLUT support
void ShowDisplay3DLUTSupport(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === 3D LUT supported status ===" << std::endl;
        adlx_bool supported;
        ADLX_RESULT res = display3DLUT->IsSupportedSCE(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedSCE: " << supported << std::endl;
        res = display3DLUT->IsSupportedSCEVividGaming(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedSCE_VividGaming: " << supported << std::endl;
        res = display3DLUT->IsSupportedSCEDynamicContrast(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedSCEDynamicContrast: " << supported << std::endl;
        res = display3DLUT->IsSupportedUser3DLUT(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupportedUser3DLUT: " << supported << std::endl;
    }
}

// Get and display current display3DLUT state
void Get3DLUTState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get 3D LUT ===" << std::endl;
        adlx_bool applied = false;
        res = display3DLUT->IsCurrentSCEDisabled(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentSCEDisabled: " << applied << std::endl;
        res = display3DLUT->IsCurrentSCEVividGaming(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentSCEVividGaming: " << applied << std::endl;
        res = display3DLUT->IsCurrentSCEDynamicContrast(&applied);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentSCEDynamicContrast: " << applied << std::endl;
        if (applied)
        {
            ADLX_IntRange range;
            res =display3DLUT->GetSCEDynamicContrastRange(&range);
            std::cout << "\t\tDynamic Contrast range is: [ " << range.minValue << " , " << range.maxValue << " ]" << std::endl;
            adlx_int contrast;
            res = display3DLUT->GetSCEDynamicContrast(&contrast);
            std::cout << "\t\tDynamic Contrast is: " << contrast << std::endl;
        }
    }
}

// Set display3DLUT
void Set3DLUTState(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int key)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Set 3D LUT ===" << std::endl;
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
        // Set SCE disabled
        case 0:
            res = display3DLUT->SetSCEDisabled();
            break;

        // Set SCE Vivid Gaming
        case 1:
            res = display3DLUT->SetSCEVividGaming();
            break;
        // Set SCE Dynamic Contrast
        case 2:
            {
                ADLX_IntRange range;
                display3DLUT->GetSCEDynamicContrastRange(&range);
                adlx_int curContrast;
                display3DLUT->GetSCEDynamicContrast(&curContrast);
                adlx_int contrast;
                if (curContrast != range.minValue)
                {
                    contrast = range.minValue;
                    res = display3DLUT->SetSCEDynamicContrast(contrast);
                    std::cout << "\tUse minimum Dynamic Contrast" << std::endl;
                }
                else
                {
                    contrast = range.maxValue;
                    res = display3DLUT->SetSCEDynamicContrast(contrast);
                    std::cout << "\tUse maximum Dynamic Contrast" << std::endl;
                }
            }
            break;
        default:
            break;
        }
        std::cout << "\tReturn code is: " << res << " (0 means Success)" << std::endl;
    }
}

// Get user 3DLUT support
void IsSupportedUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === IsSupportedUser3DLUT ===" << std::endl;
        adlx_bool supported = false;
        res = display3DLUT->IsSupportedUser3DLUT(&supported);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "  === IsSupportedUser3DLUT: " << (supported ? "True" : "False") << std::endl;
        }
    }
}

// Clear user 3DLUT
void ClearUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === ClearUser3DLUT ===" << std::endl;
        res = display3DLUT->ClearUser3DLUT();
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "  === ClearUser3DLUT succeed ===" << std::endl;
        }
        else
            std::cout << "  === ClearUser3DLUT failed ===" << std::endl;
    }
}

// Get or Set SDR user 3DLUT
void DemoSDRUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        // Generate new 3D LUT data
        if (GenerateUser3DLUT_BW (displayService, display, DEFAULT_NUM_OF_POINTS, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            std::cout << "  === SetSDRUser3DLUT ===" << std::endl;
            res = display3DLUT->SetSDRUser3DLUT (tf, cs, DEFAULT_NUM_OF_POINTS, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === SetSDRUser3DLUT succeed ===" << std::endl;
            }
            else
                std::cout << "  === SetSDRUser3DLUT failed ===" << std::endl;

            std::cout << "  === GetSDRUser3DLUT ===" << std::endl;
            res = display3DLUT->GetSDRUser3DLUT (&tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === GetSDRUser3DLUT succeed ===" << std::endl;
            }
            else
                std::cout << "  === GetSDRUser3DLUT failed ===" << std::endl;

            // Clear 3DLUT
            res = display3DLUT->ClearUser3DLUT ();
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === Clear succeed ===" << std::endl;
            }
            else
                std::cout << "  === Clear failed ===" << std::endl;
        }
    }
}

// Get or Set HDR user 3DLUT
void DemoHDRUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        std::cout << "  === SetHDRUser3DLUT ===" << std::endl;

        // Generate new 3D LUT data
        if (GenerateUser3DLUT_BW (displayService, display, DEFAULT_NUM_OF_POINTS, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            res = display3DLUT->SetHDRUser3DLUT (tf, cs, DEFAULT_NUM_OF_POINTS, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === SetHDRUser3DLUT success ===" << std::endl;
            }
            else
                std::cout << "  === SetHDRUser3DLUT failed ===" << std::endl;

            std::cout << "  === GetHDRUser3DLUT ===" << std::endl;
            res = display3DLUT->GetHDRUser3DLUT (&tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === GetHDRUser3DLUT success ===" << std::endl;
            }
            else
                std::cout << "  === GetHDRUser3DLUT not avaiable ===" << std::endl;

            // Clear new 3D LUT data
            res = display3DLUT->ClearUser3DLUT ();
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === Clear success ===" << std::endl;
            }
            else
                std::cout << "  === Clear failed ===" << std::endl;
        }
    }
}

// Get or Set all user 3DLUT
void DemoAllUser3DLUT(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_3DLUT_TRANSFER_FUNCTION tf;
        ADLX_3DLUT_COLORSPACE cs;
        ADLX_3DLUT_Data data;
        adlx_int numOfPoints = 0;

        // Generate data
        if (GenerateUser3DLUT_BW (displayService, display, DEFAULT_NUM_OF_POINTS, &data))
        {
            tf = TF_SRGB;
            cs = CS_SRGB;

            std::cout << "  === SetAllUser3DLUT ===" << std::endl;
            res = display3DLUT->SetAllUser3DLUT (tf, cs, DEFAULT_NUM_OF_POINTS, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === SetAllUser3DLUT success ===" << std::endl;
            }
            else
                std::cout << "  === SetAllUser3DLUT failed ===" << std::endl;

            std::cout << "  === GetAllUser3DLUT ===" << std::endl;
            res = display3DLUT->GetAllUser3DLUT (&tf, &cs, &numOfPoints, &data);
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === GetAllUser3DLUT success ===" << std::endl;
            }
            else
                std::cout << "  === GetAllUser3DLUT failed ===" << std::endl;

            // Clear data
            res = display3DLUT->ClearUser3DLUT ();
            if (ADLX_SUCCEEDED (res))
            {
                std::cout << "  === Clear succeed ===" << std::endl;
            }
            else
                std::cout << "  === Clear failed ===" << std::endl;
        }
        else
        {
            std::cout << "  === GenerateUser3DLUT_BW failed ===" << std::endl;
        }
    }
}

void GetUser3DLUTIndex(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    // Get display3DLUT
    IADLXDisplay3DLUTPtr display3DLUT;
    ADLX_RESULT res = displayService->Get3DLUT(display, &display3DLUT);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === GetUser3DLUTIndex ===" << std::endl;

        adlx_int index = 0;
        adlx_int lutSize = 6; //5 <= lutSize <= 17
        ADLX_UINT16_RGB rgb = { 0, 0, 0 };

        res = display3DLUT->GetUser3DLUTIndex(lutSize, &rgb, &index);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "  === GetUser3DLUTIndex success, index: ===" << index << std::endl;
        }
        else
            std::cout << "  === GetUser3DLUTIndex failed ===" << std::endl;
    }
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display 3DLUT support" << std::endl;

    std::cout << "\t->Press 2 to get 3DLUT state" << std::endl;

    std::cout << "\t->Press 3 to set current SCE to disabled" << std::endl;
    std::cout << "\t->Press 4 to set current SCE feature to Vivid Gaming profile" << std::endl;
    std::cout << "\t->Press 5 to set current SCE feature to Dynamic Contrast" << std::endl;

    std::cout << "\t->Press 6 to get user 3DLUT support" << std::endl;
    std::cout << "\t->Press 7 to clear user 3DLUT" << std::endl;
    std::cout << "\t->Press 8 to show how to set/get SDR user 3DLUT" << std::endl;
    std::cout << "\t->Press 9 to show how to set/get HDR user 3DLUT" << std::endl;
    std::cout << "\t->Press a to show how to set/get all user 3DLUT" << std::endl;
    std::cout << "\t->Press b to get 3DLUT index" << std::endl;

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
        case '1':
            ShowDisplay3DLUTSupport(displayService, display);
            break;
        case '2':
            Get3DLUTState(displayService, display);
            break;
        case '3':
        case '4':
        case '5':
            Set3DLUTState(displayService, display, num - '3');
            break;
        case '6':
            IsSupportedUser3DLUT(displayService, display);
            break;
        case '7':
            ClearUser3DLUT(displayService, display);
            break;
        case '8':
            DemoSDRUser3DLUT(displayService, display);
            break;
        case '9':
            DemoHDRUser3DLUT(displayService, display);
            break;
        case 'a':
            DemoAllUser3DLUT(displayService, display);
            break;
        case 'b':
            GetUser3DLUTIndex(displayService, display);
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
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}
