//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayCustomColor.cpp
/// \brief Demonstrates how to use Custom Color for display when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Use ADLX namespace
using namespace adlx;

// Types of Custom Color
constexpr auto CUSTOM_COLOR_HUE = 1;
constexpr auto CUSTOM_COLOR_SATURATION = 2;
constexpr auto CUSTOM_COLOR_BRIGHTNESS = 3;
constexpr auto CUSTOM_COLOR_CONTRAST = 4;
constexpr auto CUSTOM_COLOR_TEMPERATURE = 5;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX destory.
// so we use global variables to ensure the valid of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Executor class for getting and setting Custom Color properties
class CustomColorExecutor;

// Handler for user input
void ExecuteCommand(CustomColorExecutor& executor, const std::string& colorTypeString);

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
            std::cout << "Destroy ADLX result : " << res << std::endl;
            return WaitAndExit("Failed to get display services", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the printout
    system("Pause");

    return 0;
}

class CustomColorExecutor
{
  public:
    CustomColorExecutor() = default;
    CustomColorExecutor(IADLXDisplayCustomColorPtr pInst, int ct)
        : pDisplayColor_(pInst), colorType_(ct)
    {
        if (pInst == nullptr)
        {
            std::cout << "custom color executor: custom color instance is null!" << std::endl;
            std::exit(0);
        }
    }
    ADLX_RESULT GetSupport(adlx_bool* supported)
    {
        switch (colorType_)
        {
        case CUSTOM_COLOR_HUE:
            return pDisplayColor_->IsHueSupported(supported);
        case CUSTOM_COLOR_SATURATION:
            return pDisplayColor_->IsSaturationSupported(supported);
        case CUSTOM_COLOR_BRIGHTNESS:
            return pDisplayColor_->IsBrightnessSupported(supported);
        case CUSTOM_COLOR_CONTRAST:
            return pDisplayColor_->IsContrastSupported(supported);
        case CUSTOM_COLOR_TEMPERATURE:
            return pDisplayColor_->IsTemperatureSupported(supported);
        }
        return ADLX_FAIL;
    }
    ADLX_RESULT GetRange(ADLX_IntRange* range)
    {
        switch (colorType_)
        {
        case CUSTOM_COLOR_HUE:
            return pDisplayColor_->GetHueRange(range);
        case CUSTOM_COLOR_SATURATION:
            return pDisplayColor_->GetSaturationRange(range);
        case CUSTOM_COLOR_BRIGHTNESS:
            return pDisplayColor_->GetBrightnessRange(range);
        case CUSTOM_COLOR_CONTRAST:
            return pDisplayColor_->GetContrastRange(range);
        case CUSTOM_COLOR_TEMPERATURE:
            return pDisplayColor_->GetTemperatureRange(range);
        }
        return ADLX_FAIL;
    }
    ADLX_RESULT GetValue(adlx_int* value)
    {
        switch (colorType_)
        {
        case CUSTOM_COLOR_HUE:
            return pDisplayColor_->GetHue(value);
        case CUSTOM_COLOR_SATURATION:
            return pDisplayColor_->GetSaturation(value);
        case CUSTOM_COLOR_BRIGHTNESS:
            return pDisplayColor_->GetBrightness(value);
        case CUSTOM_COLOR_CONTRAST:
            return pDisplayColor_->GetContrast(value);
        case CUSTOM_COLOR_TEMPERATURE:
            return pDisplayColor_->GetTemperature(value);
        }
        return ADLX_FAIL;
    }
    ADLX_RESULT SetValue(adlx_int value)
    {
        switch (colorType_)
        {
        case CUSTOM_COLOR_HUE:
            return pDisplayColor_->SetHue(value);
        case CUSTOM_COLOR_SATURATION:
            return pDisplayColor_->SetSaturation(value);
        case CUSTOM_COLOR_BRIGHTNESS:
            return pDisplayColor_->SetBrightness(value);
        case CUSTOM_COLOR_CONTRAST:
            return pDisplayColor_->SetContrast(value);
        case CUSTOM_COLOR_TEMPERATURE:
            return pDisplayColor_->SetTemperature(value);
        }
        return ADLX_FAIL;
    }

  private:
    int colorType_;
    IADLXDisplayCustomColorPtr pDisplayColor_;
};

void ExecuteCommand(CustomColorExecutor& executor, const std::string& colorTypeString)
{
    std::cout << "\tChoose from the following options:" << colorTypeString.c_str() << " settings" << std::endl;
    std::cout << "\t->Press 1 to display support" << std::endl;
    std::cout << "\t->Press 2 to get range data" << std::endl;
    std::cout << "\t->Press 3 to display current value" << std::endl;
    std::cout << "\t->Press 4 to set current value" << std::endl;
    std::cout << "\t->Press X/x to get back to main menu" << std::endl;

    int num = 0;
    while ((num = getchar()) != 'x' && num != 'X')
    {
        switch (num)
        {
        case '1':
        {
            std::string str1 = "  === Get " + colorTypeString + " Supported ===";
            std::string str2 = "\tIs " + colorTypeString + " Supported: ";
            adlx_bool supported = false;
            std::cout << str1.c_str() << std::endl;
            executor.GetSupport(&supported);
            std::cout << str2.c_str() << supported << std::endl;
            break;
        }
        case '2':
        {
            std::string str1 = "  === Get " + colorTypeString + " Range data ===";
            std::string str2 = "\tGet" + colorTypeString + "Range: ";
            ADLX_IntRange range  = {0};
            std::cout << "  === Get Hue Range data ===" << std::endl;
            executor.GetRange(&range);
            std::cout << str2.c_str() << " min: " << range.minValue << " max: " << range.maxValue << " step: " << range.step << std::endl;
            break;
        }
        case '3':
        {
            std::string str1 = "  === Get current " + colorTypeString + " value ===";
            std::string str2 = "\tGet" + colorTypeString + ": ";
            adlx_int value = 0;
            std::cout << str1.c_str() << std::endl;
            executor.GetValue(&value);
            std::cout << str2.c_str() << " value: " << value << std::endl;
            break;
        }
        case '4':
        {
            ADLX_IntRange range  = {0};
            executor.GetRange(&range);
            adlx_int currentValue = 0;
            executor.GetValue(&currentValue);
            adlx_int baseValue = (range.minValue + range.maxValue) / 2;
            adlx_int value = (currentValue == baseValue) ? baseValue + range.step : baseValue;
            std::string str1 = "\tSet" + colorTypeString + ": ";
            std::cout << str1.c_str() << " value: " << value << std::endl;
            auto res = executor.SetValue(value);
            std::cout << "\tReturn code(0 is Success) is: " << res <<"(0 means success)" << std::endl;
            break;
        }
        default:
            break;
        }
    }
    MainMenu();
}

void ShowCustomColorSettings(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display, const int colorType)
{
    static const std::unordered_map<int, std::string> colorTypeStringMap =
        {
            {CUSTOM_COLOR_HUE, "Hue"},
            {CUSTOM_COLOR_SATURATION, "Saturation"},
            {CUSTOM_COLOR_BRIGHTNESS, "Brightness"},
            {CUSTOM_COLOR_CONTRAST, "Contrast"},
            {CUSTOM_COLOR_TEMPERATURE, "Temperature"}};

    IADLXDisplayCustomColorPtr displayCustomColor;
    ADLX_RESULT res = displayService->GetCustomColor(display, &displayCustomColor);
    if (ADLX_SUCCEEDED(res))
    {
        auto executor = CustomColorExecutor(displayCustomColor, colorType);
        try
        {
            ExecuteCommand(executor, colorTypeStringMap.at(colorType));
        } catch (...)
        {
            std::cout << "Show custom color settings: color type is invalid!" << std::endl;
        }
    }
    else
    {
        std::cout << "GetCustomColor: failed." << std::endl;
    }
}

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to enter Hue settings" << std::endl;
    std::cout << "\t->Press 2 to enter Saturation settings" << std::endl;
    std::cout << "\t->Press 3 to enter Brightness settings" << std::endl;
    std::cout << "\t->Press 4 to enter Contrast settings" << std::endl;
    std::cout << "\t->Press 5 to enter Temperature settings" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the command prompt menu" << std::endl;
}

void MenuControl(const IADLXDisplayServicesPtr& displayService, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':
            ShowCustomColorSettings(displayService, display, CUSTOM_COLOR_HUE);
            break;
            // Display Saturation settings
        case '2':
            ShowCustomColorSettings(displayService, display, CUSTOM_COLOR_SATURATION);
            break;
            // Display Brightness settings
        case '3':
            ShowCustomColorSettings(displayService, display, CUSTOM_COLOR_BRIGHTNESS);
            break;
            // Display Contrast settings
        case '4':
            ShowCustomColorSettings(displayService, display, CUSTOM_COLOR_CONTRAST);
            break;
            // Display Temperature settings
        case '5':
            ShowCustomColorSettings(displayService, display, CUSTOM_COLOR_TEMPERATURE);
            break;
            // Display  main menu options
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
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("Pause");
    return retCode;
}