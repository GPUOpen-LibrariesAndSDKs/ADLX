//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainEyefinity.c
/// \brief Demonstrates how to create an AMD Eyefinity desktop when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDesktops.h"
#include "SDK/Include/IDisplays.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl();

// Display Eyefinity support
void ShowEyefinitySupport();

// Create an Eyefinity desktop
void CreateEyefinityDesktop();

// Destroy all the Eyefinity desktops
void DestroyAllEyefinityDesktop();

// Destroy the given Eyefinity desktop
void DestroyGivenEyefinityDesktop();

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

    printf("\t->Press 1 to display Eyefinity support\n");
    printf("\t->Press 2 to create an Eyefinity desktop with all the enabled displays\n");
    printf("\t->Press 3 to destroy all the Eyefinity desktops\n");
    printf("\t->Press 4 to destroy the given Eyefinity desktop\n");

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
            // Display Eyefinity support
        case '1':
            ShowEyefinitySupport();
            break;

            // Create an Eyefinity desktop
        case '2':
            CreateEyefinityDesktop();
            break;

            // Destroy all the Eyefinity desktops
        case '3':
            DestroyAllEyefinityDesktop();
            break;

            // Destroy the given Eyefinity desktop
        case '4':
            DestroyGivenEyefinityDesktop();
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

// Display Eyefinity support status
void ShowEyefinitySupport()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    IADLXDesktopServices* desktopsInfo = NULL;
    ADLX_RESULT res = sys->pVtbl->GetDesktopsServices(sys, &desktopsInfo);
    if (ADLX_SUCCEEDED(res))
    {
        IADLXSimpleEyefinity* eyefinity = NULL;
        res = desktopsInfo->pVtbl->GetSimpleEyefinity(desktopsInfo, &eyefinity);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool supported = 0;
            res = eyefinity->pVtbl->IsSupported(eyefinity, &supported);
            if (ADLX_SUCCEEDED(res))
                printf("\t Eyefinity is supported on the desktop: %s\n", supported ? "Yes" : "No");
        }
        else
            printf("\tFailed to get simple Eyefinity\n");

        if (eyefinity != NULL)
        {
            eyefinity->pVtbl->Release(eyefinity);
            eyefinity = NULL;
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

// Create an Eyefinity desktop
void CreateEyefinityDesktop()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    IADLXDesktopServices* desktopsInfo = NULL;
    ADLX_RESULT res = sys->pVtbl->GetDesktopsServices(sys, &desktopsInfo);
    if (ADLX_SUCCEEDED(res))
    {
        IADLXSimpleEyefinity* eyefinity = NULL;
        res = desktopsInfo->pVtbl->GetSimpleEyefinity(desktopsInfo, &eyefinity);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXEyefinityDesktop* eyefinityDesktop = NULL;
            res = eyefinity->pVtbl->Create(eyefinity, &eyefinityDesktop);
            printf("\treturn code is: %d (0 means Success)\n", res);
            if (eyefinityDesktop != NULL)
            {
                eyefinityDesktop->pVtbl->Release(eyefinityDesktop);
                eyefinityDesktop = NULL;
            }
        }
        else
            printf("\tFailed to get simple Eyefinity\n");

        if (eyefinity != NULL)
        {
            eyefinity->pVtbl->Release(eyefinity);
            eyefinity = NULL;
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

// Destroy all the Eyefinity desktops
void DestroyAllEyefinityDesktop()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    IADLXDesktopServices* desktopsInfo = NULL;
    ADLX_RESULT res = sys->pVtbl->GetDesktopsServices(sys, &desktopsInfo);
    if (ADLX_SUCCEEDED(res))
    {
        IADLXSimpleEyefinity* eyefinity = NULL;
        res = desktopsInfo->pVtbl->GetSimpleEyefinity(desktopsInfo, &eyefinity);
        if (ADLX_SUCCEEDED(res))
        {
            res = eyefinity->pVtbl->DestroyAll(eyefinity);
            printf("\treturn code is: %d (0 means success)\n", res);
        }
        else
            printf("\tFailed to get simple Eyefinity\n");

        if (eyefinity != NULL)
        {
            eyefinity->pVtbl->Release(eyefinity);
            eyefinity = NULL;
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

// Destroy the given Eyefinity desktop
void DestroyGivenEyefinityDesktop()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    IADLXDesktopServices* desktopsInfo = NULL;
    ADLX_RESULT res = sys->pVtbl->GetDesktopsServices(sys, &desktopsInfo);
    if (ADLX_SUCCEEDED(res))
    {
        IADLXSimpleEyefinity* eyefinity = NULL;
        res = desktopsInfo->pVtbl->GetSimpleEyefinity(desktopsInfo, &eyefinity);
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
                        IADLXEyefinityDesktop* eyefinityDesktop = NULL;
                        void* pInterf = NULL;
                        res = desktop->pVtbl->QueryInterface(desktop, IID_IADLXEyefinityDesktop(), &pInterf);
                        if (ADLX_SUCCEEDED(res))
                        {
                            eyefinityDesktop = (IADLXEyefinityDesktop*)pInterf;
                            res = eyefinity->pVtbl->Destroy(eyefinity, eyefinityDesktop);
                            printf("\tReturn code for destroying Desktop %d is: %d (0 means Success)\n", crt, res);
                        }
                        else
                            printf("\tEyefinityDesktop is NULL\n");

                        if (eyefinityDesktop != NULL)
                        {
                            eyefinityDesktop->pVtbl->Release(eyefinityDesktop);
                            eyefinityDesktop = NULL;
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
            printf("\t Failed to get simple Eyefinity \n");

        if (eyefinity != NULL)
        {
            eyefinity->pVtbl->Release(eyefinity);
            eyefinity = NULL;
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