//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPrimaryAdapter.c
/// \brief Demonstrates how to get the primary adapter when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDesktops.h"
#include "SDK/Include/IDisplays.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl();

// Display how to get primary adapter
void ShowPrimaryAdapter();

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
        // Display main menu options
        MainMenu();
        // Get and execute the choice
        MenuControl();
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to display the Primary Adapter\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl()
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display the Primary Adapter
        case '1':
            ShowPrimaryAdapter();
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

// Display how to get primary adapter
void ShowPrimaryAdapter()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    IADLXDesktopServices* desktopsInfo = NULL;
    ADLX_RESULT res = sys->pVtbl->GetDesktopsServices(sys, &desktopsInfo);
    if (ADLX_SUCCEEDED(res))
    {
        IADLXDesktopList* desktops = NULL;
        res = desktopsInfo->pVtbl->GetDesktops(desktopsInfo, &desktops);
        if (ADLX_SUCCEEDED(res))
        {
            for (adlx_uint crt = desktops->pVtbl->Begin(desktops); crt != desktops->pVtbl->End(desktops); ++crt)
            {
                IADLXDesktop* desktop = NULL;
                res = desktops->pVtbl->At_DesktopList(desktops, crt, &desktop);
                if (ADLX_SUCCEEDED(res))
                {
                    ADLX_Point point = { 0 };
                    res = desktop->pVtbl->TopLeft (desktop, &point);
                    if (ADLX_SUCCEEDED (res) && 0 == point.x && 0 == point.y)
                    {
                        IADLXDisplayList* displays = NULL;
                        res = desktop->pVtbl->GetDisplays (desktop, &displays);
                        if (ADLX_SUCCEEDED (res))
                        {
                            // Get the first display
                            IADLXDisplay* display = NULL;
                            res = displays->pVtbl->At_DisplayList (displays, 0, &display);
                            if (ADLX_SUCCEEDED (res))
                            {
                                IADLXGPU* gpu = NULL;
                                res = display->pVtbl->GetGPU (display, &gpu);
                                if (ADLX_SUCCEEDED(res))
                                {
                                    const char* gpuName;
                                    gpu->pVtbl->Name (gpu, &gpuName);
                                    printf("Primary Adapter: %s\n", gpuName);
                                }
                                if (gpu != NULL)
                                {
                                    gpu->pVtbl->Release(gpu);
                                    gpu = NULL;
                                }
                            }
                            if (display != NULL)
                            {
                                display->pVtbl->Release(display);
                                display = NULL;
                            }
                        }

                        if (displays != NULL)
                        {
                            displays->pVtbl->Release(displays);
                            displays = NULL;
                        }
                    }
                }
                else
                    printf("\tDesktop is NULL\n");

                if (desktop != NULL)
                {
                    desktop->pVtbl->Release(desktop);
                    desktop = NULL;
                }
            }
        }
        else
            printf("\tFailed to get the Desktop interface\n");

        if (desktops != NULL)
        {
            desktops->pVtbl->Release(desktops);
            desktops = NULL;
        }
    }
    else
        printf("\tFailed to get the Desktop Services interface\n");

    if (desktopsInfo != NULL)
    {
        desktopsInfo->pVtbl->Release(desktopsInfo);
        desktopsInfo = NULL;
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