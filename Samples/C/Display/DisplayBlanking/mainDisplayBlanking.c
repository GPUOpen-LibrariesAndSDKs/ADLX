//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayBlanking.c
/// \brief Demonstrates how to configure the display blanking options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays1.h"

// Thread to quit event
static HANDLE quitEvent = NULL;

// Thread to quit flag
static int g_quit = 0;

// Thread to timeout
static HANDLE thread = NULL;

// Thread to unblank display
DWORD WINAPI ThreadUnBlankDisplay(LPVOID lpParam);

// Check if display blanking is supported
void ShowDisplayBlankingSupport(IADLXDisplayServices1* displayService1, IADLXDisplay* display);

// Get the current state of display blanking
void GetDisplayBlankingState(IADLXDisplayServices1* displayService1, IADLXDisplay* display);

// Set the state of display blanking to "blanked" or "unblanked"
void SetDisplayBlankingState(IADLXDisplayServices1* displayService1, IADLXDisplay* display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXDisplayServices1* displayService1, IADLXDisplay* display);

// Select display
IADLXDisplay* SelectDisplay(IADLXDisplayList* displays);

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
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // Get System Services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get displayService
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);

        // Convert to displayService1
        IADLXDisplayServices1* displayService1 = NULL;
        displayService->pVtbl->QueryInterface(displayService, IID_IADLXDisplayServices1(), (void**)&displayService1);

        if (ADLX_SUCCEEDED(res) && displayService1)
        {
            // Get display list
            IADLXDisplayList* displayList = NULL;
            res = displayService1->pVtbl->GetDisplays(displayService1, &displayList);
            if (ADLX_SUCCEEDED(res))
            {
                // Select the display to config
                IADLXDisplay* display = SelectDisplay(displayList);
                if (display)
                {
                    // Display the main menu
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(displayService1, display);
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
        else
        {
            printf("Failed to get displayService1\n");
        }

        // Release the displayService1 interface
        if (NULL != displayService1)
        {
            displayService1->pVtbl->Release(displayService1);
            displayService1 = NULL;
        }

        // Release the displayService interface
        if (NULL != displayService)
        {
            displayService->pVtbl->Release(displayService);
            displayService = NULL;
        }

        // Quit thread
        if (thread)
        {
            SetEvent(quitEvent);
            g_quit = true;
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
            thread = NULL;
        }
        CloseHandle(quitEvent);
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

void ShowDisplayBlankingSupport(IADLXDisplayServices1* displayService1, IADLXDisplay* display)
{
    IADLXDisplayBlanking* displayBlanking;
    ADLX_RESULT res = displayService1->pVtbl->GetDisplayBlanking(displayService1, display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get state of display blanking support ===\n");
        adlx_bool supported = false;
        res = displayBlanking->pVtbl->IsSupported(displayBlanking , &supported);
        if (ADLX_SUCCEEDED(res))
            printf("\tIsSupported, result: %d supported: %s\n", res, (supported ? "true" : "false"));
        displayBlanking->pVtbl->Release(displayBlanking);
        displayBlanking = NULL;
    }
}

void GetDisplayBlankingState(IADLXDisplayServices1* displayService1, IADLXDisplay* display)
{
    IADLXDisplayBlanking* displayBlanking;
    ADLX_RESULT res = displayService1->pVtbl->GetDisplayBlanking(displayService1, display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get the current state of display blanking ===\n");
        adlx_bool blanked = false;
        res = displayBlanking->pVtbl->IsCurrentBlanked(displayBlanking, &blanked);
        if (ADLX_SUCCEEDED(res))
            printf("\tIsCurrentBlanked: %s\n", (blanked ? "true" : "false"));
        adlx_bool unBlanked = false;
        res = displayBlanking->pVtbl->IsCurrentUnblanked(displayBlanking, &unBlanked);
        if (ADLX_SUCCEEDED(res))
            printf("\tIsCurrentUnblanked: %s\n", (unBlanked ? "true" : "false"));
        displayBlanking->pVtbl->Release(displayBlanking);
        displayBlanking = NULL;
    }
}

void SetDisplayBlankingState(IADLXDisplayServices1* displayService1, IADLXDisplay* display, const int key)
{
    IADLXDisplayBlanking* displayBlanking;
    ADLX_RESULT res = displayService1->pVtbl->GetDisplayBlanking(displayService1, display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set display to blanked
        case 0:
            if (thread)
            {
                SetEvent(quitEvent);
                g_quit = true;
                WaitForSingleObject(thread, INFINITE);
                CloseHandle(thread);
                thread = NULL;
            }
            printf("  === Set display to blanked ===\n");
            res = displayBlanking->pVtbl->SetBlanked(displayBlanking);
            break;

            // Set display to unblanked
        case 1:
            printf("  === Set display to unblanked ===\n");
            res = displayBlanking->pVtbl->SetUnblanked(displayBlanking);
            break;

            // Set display to blanked for 20 seconds
        case 2:
            if (thread)
            {
                SetEvent(quitEvent);
                g_quit = true;
                WaitForSingleObject(thread, INFINITE);
                CloseHandle(thread);
                thread = NULL;
            }
            printf("  === Set display to blanked for 20 seconds ===\n");
            res = displayBlanking->pVtbl->SetBlanked(displayBlanking);
            thread = CreateThread(NULL, 0, ThreadUnBlankDisplay, displayBlanking, 0, NULL);
            g_quit = false;
            break;
        default:
            break;
        }
        printf("\tReturn code is: %d  (0 means Success)\n", res);
        displayBlanking->pVtbl->Release(displayBlanking);
        displayBlanking = NULL;
    }
}

DWORD WINAPI ThreadUnBlankDisplay(LPVOID lpParam)
{
    IADLXDisplayBlanking* displayBlanking = (IADLXDisplayBlanking*)(lpParam);
    if (displayBlanking)
    {
        int opt = 0;
        while (!g_quit)
        {
            displayBlanking->pVtbl->Acquire(displayBlanking);
            DWORD r = WaitForSingleObject(quitEvent, 20000);
            // Quit the thread
            if (r == WAIT_OBJECT_0)
            {
                ResetEvent(quitEvent);
                printf("\tThread quit.\n");
                displayBlanking->pVtbl->Release(displayBlanking);
                break;
            }
            // Restore display after 20 seconds
            if (r == WAIT_TIMEOUT && !opt)
            {
                ADLX_RESULT res = displayBlanking->pVtbl->SetUnblanked(displayBlanking);
                printf("\tRestore display after 20 seconds, return code is: %d (0 means success).\n", res);
                displayBlanking->pVtbl->Release(displayBlanking);
                opt = 1;
            }
        }
    }
}

void MainMenu()
{
    printf("\tChoose from the following options\n");

    printf("\t->Press 1 to check if display blanking is supported\n");

    printf("\t->Press 2 to get the current state of display blanking\n");

    printf("\t->Press 3 to set the state of display blanking to blanked\n");
    printf("\t->Press 4 to set the state of display blanking to unblanked\n");
    printf("\t->Press 5 to set display to blanked for 20 seconds\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display the main menu\n");
}

// Display action control
void MenuControl(IADLXDisplayServices1* displayService1, IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Check if display blanking is supported
        case '1':
            ShowDisplayBlankingSupport(displayService1, display);
            break;

            // Get the current state of display blanking
        case '2':
            GetDisplayBlankingState(displayService1, display);
            break;

            // Set the state of display blanking to "blanked" or "unblanked"
        case '3':
        case '4':
        case '5':
            SetDisplayBlankingState(displayService1, display, num - '3');
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

IADLXDisplay* SelectDisplay(IADLXDisplayList* displays)
{
    adlx_uint len = displays->pVtbl->Size(displays);
    if (len == 0)
        return NULL;

    IADLXDisplay* display = NULL;
    if (len < 2)
        displays->pVtbl->At_DisplayList(displays, 0, &display);
    else
    {
        printf("\tSelect the display using the key(from 1 to %d ).\n", len);
        for (adlx_uint it = 0; it < len; it++)
        {
            displays->pVtbl->At_DisplayList(displays, it, &display);
            const char* dispName;
            display->pVtbl->Name(display, &dispName);
            printf("\t->Press %d to select %s.\n", it + 1, dispName);
        }
        int num = 0;
        num = getchar() - 48;
        if (num < 1 || num > len)
            printf("\tInvalid key. The first display will be used.\n");
        else
            displays->pVtbl->At(displays, num - 1, &display);
    }
    return display;
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}