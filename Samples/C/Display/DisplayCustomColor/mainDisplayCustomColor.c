//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayCustomColor.c
/// \brief Demonstrates how to use custom color for display when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"

// Custom color types
enum
{
    CUSTOM_COLOR_HUE = 1,
    CUSTOM_COLOR_SATURATION,
    CUSTOM_COLOR_BRIGHTNESS,
    CUSTOM_COLOR_CONTRAST,
    CUSTOM_COLOR_TEMPERATURE
};

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Handler for user input
void ExecuteCommand(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, const char* colorTypeString);

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
    printf("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

ADLX_RESULT GetSupport(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, adlx_bool* supported)
{
    switch (colorType_)
    {
    case CUSTOM_COLOR_HUE:
        return pDisplayColor_->pVtbl->IsHueSupported(pDisplayColor_, supported);
    case CUSTOM_COLOR_SATURATION:
        return pDisplayColor_->pVtbl->IsSaturationSupported(pDisplayColor_, supported);
    case CUSTOM_COLOR_BRIGHTNESS:
        return pDisplayColor_->pVtbl->IsBrightnessSupported(pDisplayColor_, supported);
    case CUSTOM_COLOR_CONTRAST:
        return pDisplayColor_->pVtbl->IsContrastSupported(pDisplayColor_, supported);
    case CUSTOM_COLOR_TEMPERATURE:
        return pDisplayColor_->pVtbl->IsTemperatureSupported(pDisplayColor_, supported);
    }
    return ADLX_FAIL;
}

ADLX_RESULT GetRange(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, ADLX_IntRange* range)
{
    switch (colorType_)
    {
    case CUSTOM_COLOR_HUE:
        return pDisplayColor_->pVtbl->GetHueRange(pDisplayColor_, range);
    case CUSTOM_COLOR_SATURATION:
        return pDisplayColor_->pVtbl->GetSaturationRange(pDisplayColor_, range);
    case CUSTOM_COLOR_BRIGHTNESS:
        return pDisplayColor_->pVtbl->GetBrightnessRange(pDisplayColor_, range);
    case CUSTOM_COLOR_CONTRAST:
        return pDisplayColor_->pVtbl->GetContrastRange(pDisplayColor_, range);
    case CUSTOM_COLOR_TEMPERATURE:
        return pDisplayColor_->pVtbl->GetTemperatureRange(pDisplayColor_, range);
    }
    return ADLX_FAIL;
}

ADLX_RESULT GetValue(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, adlx_int* value)
{
    switch (colorType_)
    {
    case CUSTOM_COLOR_HUE:
        return pDisplayColor_->pVtbl->GetHue(pDisplayColor_, value);
    case CUSTOM_COLOR_SATURATION:
        return pDisplayColor_->pVtbl->GetSaturation(pDisplayColor_, value);
    case CUSTOM_COLOR_BRIGHTNESS:
        return pDisplayColor_->pVtbl->GetBrightness(pDisplayColor_, value);
    case CUSTOM_COLOR_CONTRAST:
        return pDisplayColor_->pVtbl->GetContrast(pDisplayColor_, value);
    case CUSTOM_COLOR_TEMPERATURE:
        return pDisplayColor_->pVtbl->GetTemperature(pDisplayColor_, value);
    }
    return ADLX_FAIL;
}

ADLX_RESULT SetValue(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, adlx_int value)
{
    switch (colorType_)
    {
    case CUSTOM_COLOR_HUE:
        return pDisplayColor_->pVtbl->SetHue(pDisplayColor_, value);
    case CUSTOM_COLOR_SATURATION:
        return pDisplayColor_->pVtbl->SetSaturation(pDisplayColor_, value);
    case CUSTOM_COLOR_BRIGHTNESS:
        return pDisplayColor_->pVtbl->SetBrightness(pDisplayColor_, value);
    case CUSTOM_COLOR_CONTRAST:
        return pDisplayColor_->pVtbl->SetContrast(pDisplayColor_, value);
    case CUSTOM_COLOR_TEMPERATURE:
        return pDisplayColor_->pVtbl->SetTemperature(pDisplayColor_, value);
    }
    return ADLX_FAIL;
}

void ExecuteCommand(IADLXDisplayCustomColor* pDisplayColor_, int colorType_, const char* colorTypeString)
{
    printf("\tChoose from following options for %s settings\n", colorTypeString);
    printf("\t->Press 1 to display support\n");
    printf("\t->Press 2 to get range data\n");
    printf("\t->Press 3 to display current value\n");
    printf("\t->Press 4 to set current value\n");
    printf("\t->Press X/x to get back to main menu\n");

    int num = 0;
    while ((num = getchar()) != 'x' && num != 'X')
    {
        switch (num)
        {
        case '1':
        {
            adlx_bool supported = false;
            printf("  === Get %s  supported ===\n", colorTypeString);
            GetSupport(pDisplayColor_, colorType_, &supported);
            printf("\tIs %s supported: %s\n", colorTypeString, supported ? "true" : "false");
            break;
        }
        case '2':
        {
            ADLX_IntRange range = { 0 };
            printf("  === Get %s Range data ===\n", colorTypeString);
            GetRange(pDisplayColor_, colorType_, &range);
            printf("\tGet %s Range, minimum: %d, maximum: %d, step: %d\n", colorTypeString, range.minValue, range.maxValue, range.step);
            break;
        }
        case '3':
        {
            adlx_int value = 0;
            printf("  === Get current %s value ===\n", colorTypeString);
            GetValue(pDisplayColor_, colorType_, &value);
            printf("\tGet %s, value: %d\n", colorTypeString, value);
            break;
        }
        case '4':
        {
            ADLX_IntRange range = { 0 };
            GetRange(pDisplayColor_, colorType_, &range);
            adlx_int currentValue = 0;
            GetValue(pDisplayColor_, colorType_, &currentValue);
            adlx_int baseValue = (range.minValue + range.maxValue) / 2;
            adlx_int value = (currentValue == baseValue) ? baseValue + range.step : baseValue;
            printf("\tSet %s, value: %d\n", colorTypeString, value);
            auto res = SetValue(pDisplayColor_, colorType_, value);
            printf("\treturn code is: %d (0 means Success)\n", res);
            break;
        }
        default:
            break;
        }
    }

    MainMenu();
}

void ShowCustomColorSettings(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay, const int colorType)
{
    IADLXDisplayCustomColor* pDisplayCustomColor = NULL;
    ADLX_RESULT res = pDisplayService->pVtbl->GetCustomColor(pDisplayService, pDisplay, &pDisplayCustomColor);
    if (ADLX_SUCCEEDED(res))
    {
        switch (colorType)
        {
        case CUSTOM_COLOR_HUE:
            ExecuteCommand(pDisplayCustomColor, colorType, "Hue");
            break;
        case CUSTOM_COLOR_SATURATION:
            ExecuteCommand(pDisplayCustomColor, colorType, "Saturation");
            break;
        case CUSTOM_COLOR_BRIGHTNESS:
            ExecuteCommand(pDisplayCustomColor, colorType, "Brightness");
            break;
        case CUSTOM_COLOR_CONTRAST:
            ExecuteCommand(pDisplayCustomColor, colorType, "Contrast");
            break;
        case CUSTOM_COLOR_TEMPERATURE:
            ExecuteCommand(pDisplayCustomColor, colorType, "Temperature");
            break;
        }

        pDisplayCustomColor->pVtbl->Release(pDisplayCustomColor);
    }
    else
    {
        printf("Get custom color failed.\n");
    }
}

void MainMenu()
{
    printf("\tChoose from following options\n");

    printf("\t->Press 1 to enter Hue settings\n");
    printf("\t->Press 2 to enter Saturation settings\n");
    printf("\t->Press 3 to enter Brightness settings\n");
    printf("\t->Press 4 to enter Contrast settings\n");
    printf("\t->Press 5 to enter Temperature settings\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXDisplayServices* pDisplayService, IADLXDisplay* pDisplay)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            ShowCustomColorSettings(pDisplayService, pDisplay, CUSTOM_COLOR_HUE);
            break;
            // Display Saturation settings
        case '2':
            ShowCustomColorSettings(pDisplayService, pDisplay, CUSTOM_COLOR_SATURATION);
            break;
            // Display Brightness settings
        case '3':
            ShowCustomColorSettings(pDisplayService, pDisplay, CUSTOM_COLOR_BRIGHTNESS);
            break;
            // Display Contrast settings
        case '4':
            ShowCustomColorSettings(pDisplayService, pDisplay, CUSTOM_COLOR_CONTRAST);
            break;
            // Display Temperature settings
        case '5':
            ShowCustomColorSettings(pDisplayService, pDisplay, CUSTOM_COLOR_TEMPERATURE);
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

int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}