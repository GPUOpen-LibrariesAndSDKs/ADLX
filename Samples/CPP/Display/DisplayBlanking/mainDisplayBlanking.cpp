//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayBlanking.cpp
/// \brief This document describes how to obtain the display blanking through ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays1.h"
#include <iostream>
#include <string>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// thread quit event
static HANDLE quitEvent = nullptr;

// thread quit flag
static std::atomic<bool>  g_quit = false;

// thread for timeout
static std::thread* g_thread = nullptr;

// thread to unblank display 
static void ThreadUnBlankDisplay(IADLXDisplayBlankingPtr displayBlanking);

// Display display blanking support
void ShowDisplayBlankingSupport(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display);

// Display current display blanking state
void GetDisplayBlankingState(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display);

// Set display blanked or unblaned
void SetDisplayBlankingState(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display);

// Select display
IADLXDisplayPtr SelectDisplay(const IADLXDisplayListPtr& displays);

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
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // Get display service
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        // Convert to display service1
        IADLXDisplayServices1Ptr displayService1(displayService);
        if (ADLX_SUCCEEDED(res) && displayService1)
        {
            // Get display list
            IADLXDisplayListPtr displayList;
            res = displayService1->GetDisplays(&displayList);
            if (ADLX_SUCCEEDED(res))
            {
                // Select the display to config
                IADLXDisplayPtr display = SelectDisplay(displayList);
                if (display)
                {
                    // Display main menu options
                    MainMenu();
                    // Get and parse the selection
                    MenuControl(displayService1, display);
                }
            }
            else
            {
                std::cout << "Failed to get the Displays list" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get the display services1" << std::endl;
        }
        
        // quit thread
        if (g_thread && g_thread->joinable())
        {
            SetEvent(quitEvent);
            g_quit = true;
            g_thread->join();
            delete g_thread;
            g_thread = nullptr;
        }
        CloseHandle(quitEvent);
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("Pause");

    return 0;
}

void ShowDisplayBlankingSupport(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display)
{
    IADLXDisplayBlankingPtr displayBlanking;
    ADLX_RESULT res = displayService1->GetDisplayBlanking(display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get display blanking supported ===" << std::endl;
        adlx_bool supported = false;
        res = displayBlanking->IsSupported(&supported);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsSupported, result: " << res << " supported: " << (supported ? "true" : "false") << std::endl;
    }
}

void GetDisplayBlankingState(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display)
{
    IADLXDisplayBlankingPtr displayBlanking;
    ADLX_RESULT res = displayService1->GetDisplayBlanking(display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "  === Get display blanking state ===" << std::endl;
        adlx_bool blanked = false;
        res = displayBlanking->IsCurrentBlanked(&blanked);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentBlanked: " << (blanked ? "true" : "false") << std::endl;
        adlx_bool unBlanked = false;
        res = displayBlanking->IsCurrentUnblanked(&unBlanked);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIsCurrentUnblanked: " << (unBlanked ? "true" : "false") << std::endl;
    }
}

void SetDisplayBlankingState(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display, const int key)
{
    IADLXDisplayBlankingPtr displayBlanking;
    ADLX_RESULT res = displayService1->GetDisplayBlanking(display, &displayBlanking);
    if (ADLX_SUCCEEDED(res))
    {
        ADLX_RESULT res = ADLX_FAIL;
        switch (key)
        {
            // Set display blanked
        case 0:
            if (g_thread && g_thread->joinable())
            {
                SetEvent(quitEvent);
                g_quit = true;
                g_thread->join();
                delete g_thread;
                g_thread = nullptr;
            }
            std::cout << "  === Set display blanked ===" << std::endl;
            res = displayBlanking->SetBlanked();
            break;

            // Set display unblanked
        case 1:
            std::cout << "  === Set display unBlanked ===" << std::endl;
            res = displayBlanking->SetUnblanked();
            break;

            // Set display blanked and restore after 20 sec
        case 2:
            if (g_thread && g_thread->joinable())
            {
                SetEvent(quitEvent);
                g_quit = true;
                g_thread->join();
                delete g_thread;
                g_thread = nullptr;
            }
            std::cout << "  === Set display blanked for 20 seconds ===" << std::endl;
            res = displayBlanking->SetBlanked();
            g_thread = new std::thread(ThreadUnBlankDisplay, displayBlanking);
            g_quit = false;
            break;
        default:
            break;
        }
        std::cout << "\tReturn code is: " << res <<" (0 means success)" << std::endl;
    }
}

void ThreadUnBlankDisplay(IADLXDisplayBlankingPtr displayBlanking)
{
    bool opt = false;
    while (!g_quit)
    {
        DWORD r = WaitForSingleObject(quitEvent, 20000);
        // quit the thread
        if (r == WAIT_OBJECT_0)
        {
            ResetEvent(quitEvent);
            std::cout << "\tThread quit." << std::endl;
            break;
        }
        // Restore display after 20 seconds
        if (r == WAIT_TIMEOUT && displayBlanking && !opt)
        {
            ADLX_RESULT res = displayBlanking->SetUnblanked();
            std::cout << "\tRestore display after 20 seconds, return code is: " << res << " (0 means success)." << std::endl;
            opt = true;
        }
    }
}

void MainMenu()
{
    std::cout << "\tChoose from following options" << std::endl;

    std::cout << "\t->Press 1 to show display blanking support" << std::endl;

    std::cout << "\t->Press 2 to get display blanking state" << std::endl;

    std::cout << "\t->Press 3 to set display blanked" << std::endl;
    std::cout << "\t->Press 4 to set display unblanked" << std::endl;
    std::cout << "\t->Press 5 to set display blanked for 20 seconds" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

IADLXDisplayPtr SelectDisplay(const IADLXDisplayListPtr& displays)
{
    adlx_uint len = displays->Size();
    if (len == 0)
        return nullptr;

    IADLXDisplayPtr display;
    if (len < 2)
        displays->At(0, &display);
    else
    {
        std::cout << "\tYou can select the display by the key(from 1 to " << len << " )." << std::endl;
        for (adlx_uint it = 0; it < len; it++)
        {
            displays->At(it, &display);
            const char* dispName;
            display->Name(&dispName);
            std::cout << "\t->Press " << it + 1 << " to select " << dispName <<"." << std::endl;
        }
        int num = 0;
        num = getchar() - 48;
        if (num < 1 || num > len)
            std::cout << "\tInvalid key. The first display will be used." << std::endl;
        else
            displays->At(num - 1, &display);
    }
    return display;
}
// Display action control
void MenuControl(const IADLXDisplayServices1Ptr& displayService1, const IADLXDisplayPtr& display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display display blanking support
        case '1':
            ShowDisplayBlankingSupport(displayService1, display);
            break;

            // Display current display blanking state
        case '2':
            GetDisplayBlankingState(displayService1, display);
            break;

            // Set display blanking or unblanking
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

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("Pause");
    return retCode;
}