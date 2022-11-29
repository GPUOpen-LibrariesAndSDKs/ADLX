//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFPSMetrics.cpp
/// \brief Demonstrates how to control FPS metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Show current FPS metrics
void ShowCurrentFPSMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

// Show historical FPS metrics
void ShowHistoricalFPSMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringServices;
        ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringServices);
        if (ADLX_SUCCEEDED(res))
        {
            // Display main menu options
            MainMenu();
            // Get and execute the choice
            MenuControl(perfMonitoringServices);
        }
        else
            std::cout << "\tGet performance monitoring services failed" << std::endl;
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display current FPS metrics" << std::endl;
    std::cout << "\t->Press 2 to display historical FPS metrics" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Show current metrics
        case '1':
            ShowCurrentFPSMetrics(perfMonitoringServices);
            break;

        // Show historical metrics
        case '2':
            ShowHistoricalFPSMetrics(perfMonitoringServices);
            break;

        // Display menu options
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

// Display current FPS metrics
void ShowCurrentFPSMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    // Accumulate and display current metrics for each of 10 loops
    IADLXFPSPtr oneFPS;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current FPS metrics
        ADLX_RESULT res = perfMonitoringServices->GetCurrentFPS(&oneFPS);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_int64 timeStamp = 0;
            res = oneFPS->TimeStamp(&timeStamp);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The current metric time stamp is: " << timeStamp << "ms\n";
            adlx_int fpsData = 0;
            res = oneFPS->FPS(&fpsData);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The current metric FPS is: " << fpsData << std::endl;
            else if (res == ADLX_NOT_SUPPORTED)
                std::cout << "Don't support FPS" << std::endl;
        }
        Sleep(1000);
    }

    MainMenu();
}

// Show historical FPS metrics
void ShowHistoricalFPSMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->ClearPerformanceMetricsHistory();
    if (ADLX_FAILED(res))
    {
        std::cout << "Clear historical data failed" << std::endl;
        return;
    }

    // Start tracking performance metrics
    res = perfMonitoringServices->StartPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Start tracking performance metrics failed" << std::endl;
        return;
    }

    // Wait for 10 seconds to accumulate metrics
    std::cout << "Wait for 10 seconds to accumulate metrics..." << std::endl;
    Sleep(10000);

    // Get FPS metrics history from 10 seconds ago (10000 ms: the first parameter) to the present time(0 ms: the second parameter)
    IADLXFPSListPtr fpsList;
    res = perfMonitoringServices->GetFPSHistory(10000, 0, &fpsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Display all listed FPS metrics
        IADLXFPSPtr oneFPS;
        for (int i = fpsList->Begin(); i != fpsList->End(); ++i)
        {
            std::cout << "********** historical FPS metrics "<< i + 1 << ": **********" << std::endl;
            res = fpsList->At(i, &oneFPS);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_int64 timeStamp = 0;
                res = oneFPS->TimeStamp(&timeStamp);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The time stamp is: " << timeStamp << "ms" << std::endl;
                adlx_int fpsData = 0;
                res = oneFPS->FPS(&fpsData);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The FPS is: " << fpsData << std::endl;
                else if (res == ADLX_NOT_SUPPORTED)
                    std::cout << "Don't support FPS" << std::endl;
            }
            std::cout << std::endl;
        }
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->StopPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Stop tracking performance metrics failed" << std::endl;
        return;
    }
}