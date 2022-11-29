//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfGPUMetrics.cpp
/// \brief Demonstrates how to control GPU metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// ASCII °
static const signed char g_degree = 248;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Show GPU metrics range
void ShowGPUMetricsRange(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Show current GPU metrics
void ShowCurrentGPUMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Show historical GPU metrics
void ShowHistoricalGPUMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringService;
        res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringService);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPUListPtr gpus;
            // Get GPU list
            res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
            if (ADLX_SUCCEEDED(res))
            {
                // Use the first GPU in the list
                IADLXGPUPtr oneGPU;
                res = gpus->At(gpus->Begin(), &oneGPU);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(perfMonitoringService, oneGPU);
                }
                else
                    std::cout << "\tGet particular GPU failed" << std::endl;
            }
            else
                std::cout << "\tGet GPU list failed" << std::endl;
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

    std::cout << "\t->Press 1 to display GPU metrics range" << std::endl;
    std::cout << "\t->Press 2 to display current GPU metrics" << std::endl;
    std::cout << "\t->Press 3 to display historical GPU metrics" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Show GPU metrics range
        case '1':
            ShowGPUMetricsRange(perfMonitoringServices, oneGPU);
            break;

        // Display current GPU metrics
        case '2':
            ShowCurrentGPUMetrics(perfMonitoringServices, oneGPU);
            break;

        // Display historical GPU metrics
        case '3':
            ShowHistoricalGPUMetrics(perfMonitoringServices, oneGPU);
            break;

        // 	Display menu options
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

// Display GPU metrics range
void ShowGPUMetricsRange(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    ADLX_RESULT res = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_int minValue = 0, maxValue = 0;

        // Get GPU usage range
        res = gpuMetricsSupport->GetGPUUsageRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU usage range between " << minValue << "% and " << maxValue << "%" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU usage range" << std::endl;

        // Get GPU clock speed range
        res = gpuMetricsSupport->GetGPUClockSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU clock speed range between " << minValue << "MHz and " << maxValue << "MHz" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU clock speed range" << std::endl;

        // Get GPU VRAM clock speed range
        res = gpuMetricsSupport->GetGPUVRAMClockSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU VRAM clock speed range between " << minValue << "MHz and " << maxValue << "MHz" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU VRAM clock speed range" << std::endl;

        // Get GPU temperature range
        res = gpuMetricsSupport->GetGPUTemperatureRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU temperature range between " << minValue << g_degree << "C and " << maxValue << g_degree << "C" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU temperature range" << std::endl;

        // Get GPU hotspot temperature range
        res = gpuMetricsSupport->GetGPUHotspotTemperatureRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU hotspot temperature range between " << minValue << g_degree << "C and " << maxValue << g_degree << "C" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU hotspot temperature range" << std::endl;

        // Get GPU power range
        res = gpuMetricsSupport->GetGPUPowerRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU power range between " << minValue << "W and " << maxValue << "W" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU power range" << std::endl;

        // Get GPU fan speed range
        res = gpuMetricsSupport->GetGPUFanSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU fan speed range between " << minValue << "RPM and " << maxValue << "RPM" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU fan speed range" << std::endl;

        // Get GPU VRAM range
        res = gpuMetricsSupport->GetGPUVRAMRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU VRAM range between " << minValue << "MB and " << maxValue << "MB" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU VRAM range" << std::endl;

        // Get GPU voltage range
        res = gpuMetricsSupport->GetGPUVoltageRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU voltage range between " << minValue << "mV and " << maxValue << "mV" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU voltage range" << std::endl;

        // Get GPU total board power range
        res = gpuMetricsSupport->GetGPUTotalBoardPowerRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU total board power range between " << minValue << "W and " << maxValue << "W" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU total board power range" << std::endl;
    }
}

// Display the system time stamp (in ms)
void GetTimeStamp(IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = gpuMetrics->TimeStamp(&timeStamp);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The GPU timp stamp is: " << timeStamp << "ms" << std::endl;
}

// Display GPU usage (in %)
void ShowGPUUsage(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU usage support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUUsage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU usage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double usage = 0;
            res = gpuMetrics->GPUUsage(&usage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU usage is: " << usage << "%" << std::endl;
        }
    }
}

// Display GPU clock speed (in MHz)
void ShowGPUClockSpeed(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUClockSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU clock speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int gpuClock = 0;
            res = gpuMetrics->GPUClockSpeed(&gpuClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU clock speed is: " << gpuClock << "MHz" << std::endl;
        }
    }
}

// Display GPU VRAM clock speed (in MHz)
void ShowGPUVRAMClockSpeed(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display the GPU VRAM clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAMClockSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU VRAM clock speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int memoryClock = 0;
            res = gpuMetrics->GPUVRAMClockSpeed(&memoryClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM clock speed is: " << memoryClock << "MHz" << std::endl;
        }
    }
}

// Display GPU temperature(in °C)
void ShowGPUTemperature(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    // Display the GPU temperature support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU temperature support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double temperature = 0;
            res = gpuMetrics->GPUTemperature(&temperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU temperature is: " << temperature << g_degree <<"C" << std::endl;
        }
    }
}

// Display GPU hotspot temperature(in °C)
void ShowGPUHotspotTemperature(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    // Display GPU hotspot temperature support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUHotspotTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU hotspot temperature support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double hotspotTemperature = 0;
            res = gpuMetrics->GPUHotspotTemperature(&hotspotTemperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU hotspot temperature is: " << hotspotTemperature << g_degree <<"C" << std::endl;
        }
    }
}

// Display GPU power(in W)
void ShowGPUPower(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU power support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUPower(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU power support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->GPUPower(&power);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU power is: " << power << "W" << std::endl;
        }
    }
}

// Display GPU total board power(in W)
void ShowGPUTotalBoardPower(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU total board power support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTotalBoardPower(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU total board power support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->GPUTotalBoardPower(&power);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU total board power is: " << power << "W" << std::endl;
        }
    }
}

// Display GPU fan speed (in RPM)
void ShowGPUFanSpeed(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU fan speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUFanSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU fan speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int fanSpeed = 0;
            res = gpuMetrics->GPUFanSpeed(&fanSpeed);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU fan speed is: " << fanSpeed << "RPM" << std::endl;
        }
    }
}

// Display GPU VRAM (in MB)
void ShowGPUVRAM(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU VRAM support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAM(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU VRAM support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int VRAM = 0;
            res = gpuMetrics->GPUVRAM(&VRAM);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM is: " << VRAM << "MB" << std::endl;
        }
    }
}

// Display GPU Voltage (in mV)
void ShowGPUVoltage(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU voltage support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVoltage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU voltage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int voltage = 0;
            res = gpuMetrics->GPUVoltage(&voltage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU voltage is: " << voltage << "mV" << std::endl;
        }
    }
}

// Display current GPU metrics
void ShowCurrentGPUMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    ADLX_RESULT res1 = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

    // Accumulate and display current metrics for each of 10 loops
    IADLXGPUMetricsPtr gpuMetrics;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current GPU metrics
        ADLX_RESULT res2 = perfMonitoringServices->GetCurrentGPUMetrics(oneGPU, &gpuMetrics);

        // Display timestamp and GPU metrics
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            std::cout << "The current GPU metrics: " << std::endl;
            std::cout << std::boolalpha;  // Display boolean variable as true or false
            GetTimeStamp(gpuMetrics);
            ShowGPUUsage(gpuMetricsSupport, gpuMetrics);
            ShowGPUClockSpeed(gpuMetricsSupport, gpuMetrics);
            ShowGPUVRAMClockSpeed(gpuMetricsSupport, gpuMetrics);
            ShowGPUTemperature(gpuMetricsSupport, gpuMetrics);
            ShowGPUHotspotTemperature(gpuMetricsSupport, gpuMetrics);
            ShowGPUPower(gpuMetricsSupport, gpuMetrics);
            ShowGPUFanSpeed(gpuMetricsSupport, gpuMetrics);
            ShowGPUVRAM(gpuMetricsSupport, gpuMetrics);
            ShowGPUVoltage(gpuMetricsSupport, gpuMetrics);
            ShowGPUTotalBoardPower(gpuMetricsSupport, gpuMetrics);
            std::cout << std::noboolalpha;
        }
        Sleep(1000);
    }

    MainMenu();
}

// Display historical GPU Metrics
void ShowHistoricalGPUMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
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

    // Get GPU metrics history from 10 seconds ago(10000 ms: the second parameter) to the present time(0 ms: the third parameter)
    IADLXGPUMetricsListPtr gpuMetricsList;
    res = perfMonitoringServices->GetGPUMetricsHistory(oneGPU, 10000, 0, &gpuMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU metrics support
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        ADLX_RESULT res1 = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

        // Display all the GPU metrics in the list
        IADLXGPUMetricsPtr gpuMetrics;
        for (int i = gpuMetricsList->Begin(); i != gpuMetricsList->End(); ++i)
        {
            std::cout << "********** historical GPU metrics " << i + 1 << ": **********" << std::endl;
            ADLX_RESULT res2 = gpuMetricsList->At(i, &gpuMetrics);
            // Display timestamp and GPU metrics
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                std::cout << std::boolalpha;  // Display boolean variable as true or false
                GetTimeStamp(gpuMetrics);
                ShowGPUUsage(gpuMetricsSupport, gpuMetrics);
                ShowGPUClockSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMClockSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUTemperature(gpuMetricsSupport, gpuMetrics);
                ShowGPUHotspotTemperature(gpuMetricsSupport, gpuMetrics);
                ShowGPUPower(gpuMetricsSupport, gpuMetrics);
                ShowGPUFanSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAM(gpuMetricsSupport, gpuMetrics);
                ShowGPUVoltage(gpuMetricsSupport, gpuMetrics);
                ShowGPUTotalBoardPower(gpuMetricsSupport, gpuMetrics);
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