//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVariableGraphicsMemory.cpp
/// \brief Demonstrates how to obtain Variable Graphics Memory when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/ISystem3.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display Variable Graphics Memory support information
void ShowVariableGraphicsMemorySupport(const IADLXVariableGraphicsMemoryPtr& vgm);

// Get Variable Graphics Memory default option
void GetVariableGraphicsMemoryDefaultOption(const IADLXVariableGraphicsMemoryPtr& vgm);

// Get Variable Graphics Memory current option
void GetVariableGraphicsMemoryCurrentOption(const IADLXVariableGraphicsMemoryPtr& vgm);

// Get Variable Graphics Memory available options
void GetVariableGraphicsMemoryAvailableOptions(const IADLXVariableGraphicsMemoryPtr& vgm);

// Set Variable Graphics Memory option
void SetVariableGraphicsMemoryOption(const IADLXVariableGraphicsMemoryPtr& vgm);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLXVariableGraphicsMemoryPtr& vgm);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system3
        IADLXSystem3Ptr system3;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem3::IID(), (void**)&system3);
        if (ADLX_SUCCEEDED(res))
        {
            // Get Variable Graphics Memory interface
            IADLXVariableGraphicsMemoryPtr vgm;
            res = system3->GetVariableGraphicsMemory(&vgm);
            if (ADLX_SUCCEEDED(res) && vgm != nullptr)
            {
                MainMenu();
                MenuControl(vgm);
            }
            else
            {
                return WaitAndExit("Failed to get Variable Graphics Memory interface", res);
            }
        }
        else
        {
            return WaitAndExit("Failed to get IADLXSystem3 interface", res);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}


void ShowVariableGraphicsMemorySupport(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    // Check if Variable Graphics Memory is supported
    adlx_bool isSupported = false;
    ADLX_RESULT res = vgm->IsSupported(&isSupported);
    if (ADLX_SUCCEEDED(res))
    {
        if (isSupported)
        {
            std::cout << "Variable Graphics Memory is supported." << std::endl;
        }
        else
        {
            std::cout << "Variable Graphics Memory is not supported." << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to check Variable Graphics Memory support: " << res << std::endl;
    }
}

void GetVariableGraphicsMemoryDefaultOption(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    // Get the default Variable Graphics Memory option
    IADLXVariableGraphicsMemoryOptionPtr defaultOption;
    ADLX_RESULT res = vgm->GetDefaultOption(&defaultOption);
    if (ADLX_SUCCEEDED(res) && defaultOption != nullptr)
    {
        const char* optionName = nullptr;
        res = defaultOption->Name(&optionName);
        if (ADLX_SUCCEEDED(res) && optionName != nullptr)
        {
            std::cout << "Default Variable Graphics Memory option: " << optionName << std::endl;
        }
        else
        {
            std::cout << "Failed to get default Variable Graphics Memory option name: " << res << std::endl;
        }

        ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
        res = defaultOption->Mode(&mode);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Default Variable Graphics Memory mode: " << mode << std::endl;
        }
        else
        {
            std::cout << "Failed to get default Variable Graphics Memory mode: " << res << std::endl;
        }

        adlx_double memoryCarved = 0.0;
        res = defaultOption->MemoryCarved(&memoryCarved);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Default Variable Graphics Memory carved size: " << memoryCarved << " GB" << std::endl;
        }
        else
        {
            std::cout << "Failed to get default Variable Graphics Memory carved size: " << res << std::endl;
        }

        adlx_double memoryRemaining = 0.0;
        res = defaultOption->MemoryRemaining(&memoryRemaining);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Default Variable Graphics Memory remaining size: " << memoryRemaining << " GB" << std::endl;
        }
        else
        {
            std::cout << "Failed to get default Variable Graphics Memory remaining size: " << res << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to get default Variable Graphics Memory option: " << res << std::endl;
    }
}

void GetVariableGraphicsMemoryCurrentOption(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    // Get the current Variable Graphics Memory option
    IADLXVariableGraphicsMemoryOptionPtr currentOption;
    ADLX_RESULT res = vgm->GetOption(&currentOption);
    if (ADLX_SUCCEEDED(res) && currentOption != nullptr)
    {
        const char* optionName = nullptr;
        res = currentOption->Name(&optionName);
        if (ADLX_SUCCEEDED(res) && optionName != nullptr)
        {
            std::cout << "Current Variable Graphics Memory option: " << optionName << std::endl;
        }
        else
        {
            std::cout << "Failed to get current Variable Graphics Memory option name: " << res << std::endl;
        }

        ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
        res = currentOption->Mode(&mode);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Current Variable Graphics Memory mode: " << mode << std::endl;
        }
        else
        {
            std::cout << "Failed to get current Variable Graphics Memory mode: " << res << std::endl;
        }

        adlx_double memoryCarved = 0.0;
        res = currentOption->MemoryCarved(&memoryCarved);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Current Variable Graphics Memory carved size: " << memoryCarved << " GB" << std::endl;
        }
        else
        {
            std::cout << "Failed to get current Variable Graphics Memory carved size: " << res << std::endl;
        }

        adlx_double memoryRemaining = 0.0;
        res = currentOption->MemoryRemaining(&memoryRemaining);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Current Variable Graphics Memory remaining size: " << memoryRemaining << " GB" << std::endl;
        }
        else
        {
            std::cout << "Failed to get current Variable Graphics Memory remaining size: " << res << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to get current Variable Graphics Memory option: " << res << std::endl;
    }
}

void GetVariableGraphicsMemoryAvailableOptions(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    // Get the available Variable Graphics Memory options
    IADLXVariableGraphicsMemoryOptionListPtr availableOptionList;
    ADLX_RESULT res = vgm->GetAvailableOptions(&availableOptionList);
    if (ADLX_SUCCEEDED(res) && availableOptionList != nullptr)
    {
        adlx_uint size = availableOptionList->Size();
        std::cout << "Available Variable Graphics Memory options count: " << size << std::endl;

        for (adlx_uint i = 0; i < size; ++i)
        {
            IADLXVariableGraphicsMemoryOptionPtr option;
            res = availableOptionList->At(i, &option);
            if (ADLX_SUCCEEDED(res) && option != nullptr)
            {
                std::cout << "Option " << i + 1 << ": " << std::endl;
                const char* optionName = nullptr;
                res = option->Name(&optionName);
                if (ADLX_SUCCEEDED(res) && optionName != nullptr)
                {
                    std::cout << "Name: " << optionName << std::endl;
                }
                else
                {
                    std::cout << "Failed to get option name for index " << i << ": " << res << std::endl;
                }
                ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
                res = option->Mode(&mode);
                if (ADLX_SUCCEEDED(res))
                {
                    std::cout << "Mode: " << mode << std::endl;
                }
                else
                {
                    std::cout << "Failed to get mode for option at index " << i << ": " << res << std::endl;
                }
                adlx_double memoryCarved = 0.0;
                res = option->MemoryCarved(&memoryCarved);
                if (ADLX_SUCCEEDED(res))
                {
                    std::cout << "Carved Size: " << memoryCarved << " GB" << std::endl;
                }
                else
                {
                    std::cout << "Failed to get carved size for option at index " << i << ": " << res << std::endl;
                }
                adlx_double memoryRemaining = 0.0;
                res = option->MemoryRemaining(&memoryRemaining);
                if (ADLX_SUCCEEDED(res))
                {
                    std::cout << "Remaining Size: " << memoryRemaining << " GB" << std::endl;
                }
                else
                {
                    std::cout << "Failed to get remaining size for option at index " << i << ": " << res << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to get Variable Graphics Memory option at index " << i << ": " << res << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Failed to get available Variable Graphics Memory options: " << res << std::endl;
    }
}

void SetVariableGraphicsMemoryOption(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    // Get the available Variable Graphics Memory options
    IADLXVariableGraphicsMemoryOptionListPtr availableOptionList;
    ADLX_RESULT res = vgm->GetAvailableOptions(&availableOptionList);
    if (ADLX_SUCCEEDED(res) && availableOptionList != nullptr)
    {
        adlx_uint size = availableOptionList->Size();
        if (size > 0)
        {
            // Set the first available option as the current option
            IADLXVariableGraphicsMemoryOptionPtr option;
            res = availableOptionList->At(0, &option);
            if (ADLX_SUCCEEDED(res) && option != nullptr)
            {
                res = vgm->SetOption(option);
                // Will restart, following code will not be executed
                if (ADLX_SUCCEEDED(res))
                {
                    std::cout << "Variable Graphics Memory option set successfully." << std::endl;
                }
                else
                {
                    std::cout << "Failed to set Variable Graphics Memory option: " << res << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to get Variable Graphics Memory option at index 0: " << res << std::endl;
            }
        }
        else
        {
            std::cout << "No available Variable Graphics Memory options to set." << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to get available Variable Graphics Memory options: " << res << std::endl;
    }
}

void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display Variable Graphics Memory support information" << std::endl;
    std::cout << "\t->Press 2 to get Variable Graphics Memory default option" << std::endl;
    std::cout << "\t->Press 3 to get Variable Graphics Memory current option" << std::endl;
    std::cout << "\t->Press 4 to get available Variable Graphics Memory options" << std::endl;
    std::cout << "\t->Press 5 to set Variable Graphics Memory option" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(const IADLXVariableGraphicsMemoryPtr& vgm)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display Variable Graphics Memory support information
        case '1':
            ShowVariableGraphicsMemorySupport(vgm);
            break;

        // Get Variable Graphics Memory default option
        case '2':
            GetVariableGraphicsMemoryDefaultOption(vgm);
            break;

        // Get Variable Graphics Memory current option
        case '3':
            GetVariableGraphicsMemoryCurrentOption(vgm);
            break;

        // Get available Variable Graphics Memory options
        case '4':
            GetVariableGraphicsMemoryAvailableOptions(vgm);
            break;

        // Set Variable Graphics Memory option
        case '5':
            SetVariableGraphicsMemoryOption(vgm);
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
