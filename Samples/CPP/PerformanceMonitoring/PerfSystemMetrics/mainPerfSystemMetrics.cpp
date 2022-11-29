//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfSystemMetrics.cpp
/// \brief Demonstrates how to control system metrics when programming with ADLX.

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

// Display system metrics range
void ShowSystemMetricsRange(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Display current system metrics
void ShowCurrentSystemMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

// Display historical system metrics
void ShowHistoricalSystemMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringServices;
        res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringServices);
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

    std::cout << "\t->Press 1 to display the system metrics range" << std::endl;
    std::cout << "\t->Press 2 to display the current system metrics" << std::endl;
    std::cout << "\t->Press 3 to display the historical system metrics" << std::endl;

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
        // Display system metrics range
        case '1':
            ShowSystemMetricsRange(perfMonitoringServices);
            break;

        // Display current metrics
        case '2':
            ShowCurrentSystemMetrics(perfMonitoringServices);
            break;

        // Display historical metrics
        case '3':
            ShowHistoricalSystemMetrics(perfMonitoringServices);
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

// Display system metrics range
void ShowSystemMetricsRange(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    // Get system metrics support
    IADLXSystemMetricsSupportPtr systemMetricsSupport;
    ADLX_RESULT res = perfMonitoringServices->GetSupportedSystemMetrics(&systemMetricsSupport);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_int minValue = 0, maxValue = 0;

        // Get CPU usage range
        res = systemMetricsSupport->GetCPUUsageRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The CPU usage range between " << minValue << "% and " << maxValue << "%" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support CPU usage range" << std::endl;

        // Get system RAM range
        res = systemMetricsSupport->GetSystemRAMRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The system RAM range between " << minValue << "MB and " << maxValue << "MB" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support system RAM range" << std::endl;

        // Get SmartShift range
        res = systemMetricsSupport->GetSmartShiftRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The smart shift range between " << minValue << " and " << maxValue << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support smart shift range" << std::endl;
    }
}

// Display the system time stamp (in ms)
void GetTimeStamp(IADLXSystemMetricsPtr systemMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = systemMetrics->TimeStamp(&timeStamp);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The system time stamp is: " << timeStamp << "ms" << std::endl;
}

// Show CPU usage (in %)
void ShowCPUUsage(IADLXSystemMetricsSupportPtr systemMetricsSupport, IADLXSystemMetricsPtr systemMetrics)
{
    adlx_bool supported = false;
    // Display CPU usage support status
    ADLX_RESULT res =  systemMetricsSupport->IsSupportedCPUUsage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "CPU usage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double cpuUsage = 0;
            res = systemMetrics->CPUUsage(&cpuUsage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The CPU usage is: " << cpuUsage << "%" << std::endl;
        }
    }
}

// Display system RAM (in MB)
void ShowSystemRAM(IADLXSystemMetricsSupportPtr systemMetricsSupport, IADLXSystemMetricsPtr systemMetrics)
{
    adlx_bool supported = false;
    // Display system RAM usage support status
    ADLX_RESULT res = systemMetricsSupport->IsSupportedSystemRAM(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "System RAM usage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int systemRAM = 0;
            res = systemMetrics->SystemRAM(&systemRAM);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The system RAM is: " << systemRAM << "MB" << std::endl;
        }
    }
}

// Show SmartShift
void ShowSmartShift(IADLXSystemMetricsSupportPtr systemMetricsSupport, IADLXSystemMetricsPtr systemMetrics)
{
    adlx_bool supported = false;
    // Display SmartShift support status
    ADLX_RESULT res = systemMetricsSupport->IsSupportedSmartShift(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "SmartShift support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int smartShift;
            res = systemMetrics->SmartShift(&smartShift);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The SmartShift is: " << smartShift << std::endl;
        }
    }
}

// Display current system metrics
void ShowCurrentSystemMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    // Get system metrics support
    IADLXSystemMetricsSupportPtr systemMetricsSupport;
    ADLX_RESULT res1 = perfMonitoringServices->GetSupportedSystemMetrics(&systemMetricsSupport);

    // Accumulate and display current metrics for each of the 10 loops
    IADLXSystemMetricsPtr systemMetrics;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current system metrics
        ADLX_RESULT res2 = perfMonitoringServices->GetCurrentSystemMetrics(&systemMetrics);

        // Display timestamp, CPU usage, system RAM, and SmartShift
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            std::cout << "The current system metrics: " << std::endl;
            std::cout << std::boolalpha;  // Display boolean variable as true or false
            GetTimeStamp(systemMetrics);
            ShowCPUUsage(systemMetricsSupport, systemMetrics);
            ShowSystemRAM(systemMetricsSupport, systemMetrics);
            ShowSmartShift(systemMetricsSupport, systemMetrics);
            std::cout << std::noboolalpha;
        }
        Sleep(1000);
    }

    MainMenu();
}

// Display historical system metrics
void ShowHistoricalSystemMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->ClearPerformanceMetricsHistory();
    if (ADLX_FAILED(res))
    {
        std::cout << "Clear historical data failed" << std::endl;
        return;
    }

    // Get current max historical size (in s)
    adlx_int maxHistorySize = 0;
    res = perfMonitoringServices->GetMaxPerformanceMetricsHistorySize(&maxHistorySize);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The current max historical size is: " << maxHistorySize << "s" << std::endl;
    // Get the configurable maximum historical size range
    ADLX_IntRange range;
    res = perfMonitoringServices->GetMaxPerformanceMetricsHistorySizeRange(&range);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The range of max historical size is: (" << range.minValue << ", " << range.maxValue << ")s" << std::endl;
    // Change max historical size to minimum value
    res = perfMonitoringServices->SetMaxPerformanceMetricsHistorySize(range.minValue);
    if (ADLX_SUCCEEDED(res))
    {
        perfMonitoringServices->GetMaxPerformanceMetricsHistorySize(&maxHistorySize);
        std::cout << "Set max historical size to minimum value successfully, the current max historical is: " << maxHistorySize << "s" << std::endl;
    }

    // Get current sampling interval (in ms)
    adlx_int samplingInterval = 0;
    res = perfMonitoringServices->GetSamplingInterval(&samplingInterval);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The current sampling interval is: " << samplingInterval << "ms" << std::endl;
    // Get the sampling interval range. The sampling interval must be set within this range.
    res = perfMonitoringServices->GetSamplingIntervalRange(&range);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The range of sampling interval is: (" << range.minValue << ", " << range.maxValue << ")ms" << std::endl;
    // Change sampling interval to minimum value
    res = perfMonitoringServices->SetSamplingInterval(range.minValue);
    if (ADLX_SUCCEEDED(res))
    {
        perfMonitoringServices->GetSamplingInterval(&samplingInterval);
        std::cout << "Set sampling interval to minimum value successfully, the current sampling interval is: " << samplingInterval << "ms" << std::endl;
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

    // Check the current performance metrics historical size (in s) upon accumulation
    adlx_int currentHistorySize = 0;
    res = perfMonitoringServices->GetCurrentPerformanceMetricsHistorySize(&currentHistorySize);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The current historical size is: " << currentHistorySize << "s" << std::endl;

    // Get system metrics history from 10 seconds ago(10000 ms: the first parameter) to the present time(0 ms: the second parameter)
    IADLXSystemMetricsListPtr systemMetricsList;
    res = perfMonitoringServices->GetSystemMetricsHistory(10000, 0, &systemMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get the system metrics support
        IADLXSystemMetricsSupportPtr systemMetricsSupport;
        ADLX_RESULT res1 = perfMonitoringServices->GetSupportedSystemMetrics(&systemMetricsSupport);

        // Display all the system metrics in the list
        IADLXSystemMetricsPtr systemMetrics;
        for (int i = systemMetricsList->Begin(); i != systemMetricsList->End(); ++i)
        {
            std::cout << "********** historical system metrics " << i + 1 << ": **********" << std::endl;
            ADLX_RESULT res2 = systemMetricsList->At(i, &systemMetrics);
            // Display first system metrics time stamp, CPU usage, system RAM, and SmartShift
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                std::cout << std::boolalpha;  // Display boolean variable as true or false
                GetTimeStamp(systemMetrics);
                ShowCPUUsage(systemMetricsSupport, systemMetrics);
                ShowSystemRAM(systemMetricsSupport, systemMetrics);
                ShowSmartShift(systemMetricsSupport, systemMetrics);
                std::cout << std::noboolalpha;
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