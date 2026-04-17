//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVariableGraphicsMemory.c
/// \brief Demonstrates how to obtain Variable Graphics Memory when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISystem3.h"


// Display Variable Graphics Memory support information
void ShowVariableGraphicsMemorySupport(IADLXVariableGraphicsMemory* vgm);

// Get Variable Graphics Memory default option
void GetVariableGraphicsMemoryDefaultOption(IADLXVariableGraphicsMemory* vgm);

// Get Variable Graphics Memory current option
void GetVariableGraphicsMemoryCurrentOption(IADLXVariableGraphicsMemory* vgm);

// Get Variable Graphics Memory available options
void GetVariableGraphicsMemoryAvailableOptions(IADLXVariableGraphicsMemory* vgm);

// Set Variable Graphics Memory option
void SetVariableGraphicsMemoryOption(IADLXVariableGraphicsMemory* vgm);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLXVariableGraphicsMemory* vgm);

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
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();
        // Get system3
        IADLXSystem3* system3 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem3(), (void**)&system3);
        if (ADLX_SUCCEEDED(res))
        {
            // Get Variable Graphics Memory interface
            IADLXVariableGraphicsMemory* vgm = NULL;
            res = system3->pVtbl->GetVariableGraphicsMemory(system3, &vgm);
            if (ADLX_SUCCEEDED(res) && vgm != NULL)
            {
                MainMenu();
                MenuControl(vgm);
                
                // Release Variable Graphics Memory interface
                if (vgm != NULL)
                {
                    vgm->pVtbl->Release(vgm);
                    vgm = NULL;
                }
            }
            else
            {
                // Release system3 interface before returning
                if (system3 != NULL)
                {
                    system3->pVtbl->Release(system3);
                    system3 = NULL;
                }
                return WaitAndExit("Failed to get Variable Graphics Memory interface", res);
            }
            
            // Release system3 interface
            if (system3 != NULL)
            {
                system3->pVtbl->Release(system3);
                system3 = NULL;
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
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}


void ShowVariableGraphicsMemorySupport(IADLXVariableGraphicsMemory* vgm)
{
    // Check if Variable Graphics Memory is supported
    adlx_bool isSupported = false;
    ADLX_RESULT res = vgm->pVtbl->IsSupported(vgm, &isSupported);
    if (ADLX_SUCCEEDED(res))
    {
        if (isSupported)
        {
            printf("Variable Graphics Memory is supported.\n");
        }
        else
        {
            printf("Variable Graphics Memory is not supported.\n");
        }
    }
    else
    {
        printf("Failed to check Variable Graphics Memory support: %d\n", res);
    }
}

void GetVariableGraphicsMemoryDefaultOption(IADLXVariableGraphicsMemory* vgm)
{
    // Get the default Variable Graphics Memory option
    IADLXVariableGraphicsMemoryOption* defaultOption = NULL;
    ADLX_RESULT res = vgm->pVtbl->GetDefaultOption(vgm, &defaultOption);
    if (ADLX_SUCCEEDED(res) && defaultOption != NULL)
    {
        const char* optionName = NULL;
        res = defaultOption->pVtbl->Name(defaultOption, &optionName);
        if (ADLX_SUCCEEDED(res) && optionName != NULL)
        {
            printf("Default Variable Graphics Memory option: %s\n", optionName);
        }
        else
        {
            printf("Failed to get default Variable Graphics Memory option name: %d\n", res);
        }

        ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
        res = defaultOption->pVtbl->Mode(defaultOption, &mode);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Default Variable Graphics Memory mode: %d\n", mode);
        }
        else
        {
            printf("Failed to get default Variable Graphics Memory mode: %d\n", res);
        }

        adlx_double memoryCarved = 0.0;
        res = defaultOption->pVtbl->MemoryCarved(defaultOption, &memoryCarved);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Default Variable Graphics Memory carved size: %.2f GB\n", memoryCarved);
        }
        else
        {
            printf("Failed to get default Variable Graphics Memory carved size: %d\n", res);
        }

        adlx_double memoryRemaining = 0.0;
        res = defaultOption->pVtbl->MemoryRemaining(defaultOption, &memoryRemaining);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Default Variable Graphics Memory remaining size: %.2f GB\n", memoryRemaining);
        }
        else
        {
            printf("Failed to get default Variable Graphics Memory remaining size: %d\n", res);
        }
        
        // Release the default option interface
        if (defaultOption != NULL)
        {
            defaultOption->pVtbl->Release(defaultOption);
            defaultOption = NULL;
        }
    }
    else
    {
        printf("Failed to get default Variable Graphics Memory option: %d\n", res);
    }
}

void GetVariableGraphicsMemoryCurrentOption(IADLXVariableGraphicsMemory* vgm)
{
    // Get the current Variable Graphics Memory option
    IADLXVariableGraphicsMemoryOption* currentOption = NULL;
    ADLX_RESULT res = vgm->pVtbl->GetOption(vgm, &currentOption);
    if (ADLX_SUCCEEDED(res) && currentOption != NULL)
    {
        const char* optionName = NULL;
        res = currentOption->pVtbl->Name(currentOption, &optionName);
        if (ADLX_SUCCEEDED(res) && optionName != NULL)
        {
            printf("Current Variable Graphics Memory option: %s\n", optionName);
        }
        else
        {
            printf("Failed to get current Variable Graphics Memory option name: %d\n", res);
        }

        ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
        res = currentOption->pVtbl->Mode(currentOption, &mode);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Current Variable Graphics Memory mode: %d\n", mode);
        }
        else
        {
            printf("Failed to get current Variable Graphics Memory mode: %d\n", res);
        }

        adlx_double memoryCarved = 0.0;
        res = currentOption->pVtbl->MemoryCarved(currentOption, &memoryCarved);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Current Variable Graphics Memory carved size: %.2f GB\n", memoryCarved);
        }
        else
        {
            printf("Failed to get current Variable Graphics Memory carved size: %d\n", res);
        }

        adlx_double memoryRemaining = 0.0;
        res = currentOption->pVtbl->MemoryRemaining(currentOption, &memoryRemaining);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Current Variable Graphics Memory remaining size: %.2f GB\n", memoryRemaining);
        }
        else
        {
            printf("Failed to get current Variable Graphics Memory remaining size: %d\n", res);
        }
        
        // Release the current option interface
        if (currentOption != NULL)
        {
            currentOption->pVtbl->Release(currentOption);
            currentOption = NULL;
        }
    }
    else
    {
        printf("Failed to get current Variable Graphics Memory option: %d\n", res);
    }
}

void GetVariableGraphicsMemoryAvailableOptions(IADLXVariableGraphicsMemory* vgm)
{
    // Get the available Variable Graphics Memory options
    IADLXVariableGraphicsMemoryOptionList* availableOptionList = NULL;
    ADLX_RESULT res = vgm->pVtbl->GetAvailableOptions(vgm, &availableOptionList);
    if (ADLX_SUCCEEDED(res) && availableOptionList != NULL)
    {
        adlx_uint size = availableOptionList->pVtbl->Size(availableOptionList);
        printf("Available Variable Graphics Memory options count: %u\n", size);

        for (adlx_uint i = 0; i < size; ++i)
        {
            IADLXVariableGraphicsMemoryOption* option = NULL;
            res = availableOptionList->pVtbl->At_OptionList(availableOptionList, i, &option);
            if (ADLX_SUCCEEDED(res) && option != NULL)
            {
                printf("Option %u:\n", i + 1);
                const char* optionName = NULL;
                res = option->pVtbl->Name(option, &optionName);
                if (ADLX_SUCCEEDED(res) && optionName != NULL)
                {
                    printf("Name: %s\n", optionName);
                }
                else
                {
                    printf("Failed to get option name for index %u: %d\n", i, res);
                }

                ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
                res = option->pVtbl->Mode(option, &mode);
                if (ADLX_SUCCEEDED(res))
                {
                    printf("Mode: %d\n", mode);
                }
                else
                {
                    printf("Failed to get mode for option at index %u: %d\n", i, res);
                }

                adlx_double memoryCarved = 0.0;
                res = option->pVtbl->MemoryCarved(option, &memoryCarved);
                if (ADLX_SUCCEEDED(res))
                {
                    printf("Carved Size: %.2f GB\n", memoryCarved);
                }
                else
                {
                    printf("Failed to get carved size for option at index %u: %d\n", i, res);
                }

                adlx_double memoryRemaining = 0.0;
                res = option->pVtbl->MemoryRemaining(option, &memoryRemaining);
                if (ADLX_SUCCEEDED(res))
                {
                    printf("Remaining Size: %.2f GB\n", memoryRemaining);
                }
                else
                {
                    printf("Failed to get remaining size for option at index %u: %d\n", i, res);
                }
                
                // Release the option interface
                if (option != NULL)
                {
                    option->pVtbl->Release(option);
                    option = NULL;
                }
            }
            else
            {
                printf("Failed to get Variable Graphics Memory option at index %u: %d\n", i, res);
            }
        }
        
        // Release the available option list
        if (availableOptionList != NULL)
        {
            availableOptionList->pVtbl->Release(availableOptionList);
            availableOptionList = NULL;
        }
    }
    else
    {
        printf("Failed to get available Variable Graphics Memory options: %d\n", res);
    }
}

void SetVariableGraphicsMemoryOption(IADLXVariableGraphicsMemory* vgm)
{
    // Get the available Variable Graphics Memory options
    IADLXVariableGraphicsMemoryOptionList* availableOptionList = NULL;
    ADLX_RESULT res = vgm->pVtbl->GetAvailableOptions(vgm, &availableOptionList);
    if (ADLX_SUCCEEDED(res) && availableOptionList != NULL)
    {
        adlx_uint size = availableOptionList->pVtbl->Size(availableOptionList);
        if (size > 0)
        {
            // Set the second available option as the current option
            IADLXVariableGraphicsMemoryOption* option = NULL;
            res = availableOptionList->pVtbl->At_OptionList(availableOptionList, 1, &option);
            if (ADLX_SUCCEEDED(res) && option != NULL)
            {
                res = vgm->pVtbl->SetOption(vgm, option);
                // Will restart, following code will not be executed
                if (ADLX_SUCCEEDED(res))
                {
                    printf("Variable Graphics Memory option set successfully.\n");
                }
                else
                {
                    printf("Failed to set Variable Graphics Memory option: %d\n", res);
                }
                
                // Release the option interface
                if (option != NULL)
                {
                    option->pVtbl->Release(option);
                    option = NULL;
                }
            }
            else
            {
                printf("Failed to get Variable Graphics Memory option at index 0: %d\n", res);
            }
        }
        else
        {
            printf("No available Variable Graphics Memory options to set.\n");
        }
        
        // Release the available option list
        if (availableOptionList != NULL)
        {
            availableOptionList->pVtbl->Release(availableOptionList);
            availableOptionList = NULL;
        }
    }
    else
    {
        printf("Failed to get available Variable Graphics Memory options: %d\n", res);
    }
}

void MainMenu()
{
    printf("\tChoose from following options\n");

    printf("\t->Press 1 to display Variable Graphics Memory support information\n");
    printf("\t->Press 2 to get Variable Graphics Memory default option\n");
    printf("\t->Press 3 to get Variable Graphics Memory current option\n");
    printf("\t->Press 4 to get available Variable Graphics Memory options\n");
    printf("\t->Press 5 to set Variable Graphics Memory option\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXVariableGraphicsMemory* vgm)
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}
