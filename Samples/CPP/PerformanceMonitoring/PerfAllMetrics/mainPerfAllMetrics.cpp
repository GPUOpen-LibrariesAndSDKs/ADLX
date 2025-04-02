//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfAllMetrics.cpp
/// \brief Demonstrates how to control all metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"
#include "SDK/Include/IPerformanceMonitoring2.h"
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

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Display all current metrics
void ShowCurrentAllMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Display all historical metrics
void ShowHistoricalAllMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringService;
        ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringService);
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

    std::cout << "\t->Press 1 to display current all metrics" << std::endl;
    std::cout << "\t->Press 2 to display historical all metrics" << std::endl;

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
        // Display all current metrics
        case '1':
            ShowCurrentAllMetrics(perfMonitoringServices, oneGPU);
            break;

        // Display all historical metrics
        case '2':
            ShowHistoricalAllMetrics(perfMonitoringServices, oneGPU);
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
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display the system time stamp (in ms)
void GetTimeStamp(IADLXSystemMetricsPtr systemMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = systemMetrics->TimeStamp(&timeStamp);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The system time stamp is: " << timeStamp << "ms" << std::endl;
}

// Show CPU usage(in %)
void ShowCPUUsage(IADLXSystemMetricsSupportPtr systemMetricsSupport, IADLXSystemMetricsPtr systemMetrics)
{
    adlx_bool supported = false;
    // Display CPU usage support status
    ADLX_RESULT res = systemMetricsSupport->IsSupportedCPUUsage(&supported);
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

// Display SmartShift
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

// Display the GPU metrics time stamp (in ms)
void GetTimeStamp(IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = gpuMetrics->TimeStamp(&timeStamp);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The GPU time stamp is: " << timeStamp << "ms" << std::endl;
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
        std::cout << "Get if the GPU clock speed is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_int gpuClock = 0;
            res = gpuMetrics->GPUClockSpeed(&gpuClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU clock speed is: " << gpuClock << "MHz" << std::endl;
        }
    }
}

// Show GPU VRAM clock speed(MHz)
void ShowGPUVRAMClockSpeed(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU VRAM clock speed is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAMClockSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU VRAM clock speed is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_int memoryClock = 0;
            res = gpuMetrics->GPUVRAMClockSpeed(&memoryClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM clock speed is: " << memoryClock << "MHz" << std::endl;
        }
    }
}

// Show GPU temperature(°C)
void ShowGPUTemperature(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU tempetature is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU temperture is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_double temperature = 0;
            res = gpuMetrics->GPUTemperature(&temperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU temperature is: " << temperature << g_degree << "C" << std::endl;
        }
    }
}

// Show GPU hotspot temperature(°C)
void ShowGPUHotspotTemperature(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU hotspot temperature is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUHotspotTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU hotspot temperature is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_double hotspotTemperature = 0;
            res = gpuMetrics->GPUHotspotTemperature(&hotspotTemperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU hotspot temperature is: " << hotspotTemperature << g_degree << "C" << std::endl;
        }
    }
}

// Show GPU power(W)
void ShowGPUPower(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU power is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUPower(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU power is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->GPUPower(&power);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU power is: " << power << "W" << std::endl;
        }
    }
}

// Show GPU fan speed(RPM)
void ShowGPUFanSpeed(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU fan speed is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUFanSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU fan speed is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_int fanSpeed = 0;
            res = gpuMetrics->GPUFanSpeed(&fanSpeed);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU fan speed is: " << fanSpeed << "RPM" << std::endl;
        }
    }
}

// Show GPU VRAM(MB)
void ShowGPUVRAM(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU VRAM is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAM(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU VRAM is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_int VRAM = 0;
            res = gpuMetrics->GPUVRAM(&VRAM);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM is: " << VRAM << "MB" << std::endl;
        }
    }
}

// Show GPU Voltage(mV)
void ShowGPUVoltage(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Get if the GPU voltage is supported
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVoltage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "Get if the GPU voltage is supported: " << supported << std::endl;
        if (supported)
        {
            adlx_int voltage = 0;
            res = gpuMetrics->GPUVoltage(&voltage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU voltage is: " << voltage << "mV" << std::endl;
        }
    }
}

// Display GPU memory temperature(in °C)
void ShowGPUMemoryTemperature(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    IADLXGPUMetricsSupport1Ptr gpuMetricsSupport1(gpuMetricsSupport);
    IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
    if (gpuMetricsSupport1 && gpuMetrics1)
    {
        // Display the GPU memory support status
        ADLX_RESULT res = gpuMetricsSupport1->IsSupportedGPUMemoryTemperature(&supported);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "GPU memory temperature support status: " << supported << std::endl;
            if (supported)
            {
                adlx_double temperature = 0;
                res = gpuMetrics1->GPUMemoryTemperature(&temperature);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The GPU memory temperature is: " << temperature << g_degree << "C" << std::endl;
            }
        }
    }
}

// Display the NPU activity level(in %)
void ShowNPUActivityLevel(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    IADLXGPUMetricsSupport1Ptr gpuMetricsSupport1(gpuMetricsSupport);
    IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
    if (gpuMetricsSupport1 && gpuMetrics1)
    {
        // Display the NPU activity level support status
        ADLX_RESULT res = gpuMetricsSupport1->IsSupportedNPUActivityLevel(&supported);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "NPU activity level support status: " << supported << std::endl;
            if (supported)
            {
                adlx_int level = 0;
                res = gpuMetrics1->NPUActivityLevel(&level);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The NPU activity level is: " << level << "%" << std::endl;
            }
        }
    }
}

// Display the NPU frequency(in MHz)
void ShowNPUFrequency(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    IADLXGPUMetricsSupport1Ptr gpuMetricsSupport1(gpuMetricsSupport);
    IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
    if (gpuMetricsSupport1 && gpuMetrics1)
    {
        // Display the NPU frequency support status
        ADLX_RESULT res = gpuMetricsSupport1->IsSupportedNPUFrequency(&supported);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "NPU frequency support status: " << supported << std::endl;
            if (supported)
            {
                adlx_int frequency = 0;
                res = gpuMetrics1->NPUFrequency(&frequency);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "The NPU frequency is: " << frequency << "MHz" << std::endl;
            }
        }
    }
}

// Show current all metrics
void ShowCurrentAllMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Get system metrics support
    IADLXSystemMetricsSupportPtr systemMetricsSupport;
    ADLX_RESULT res2 = perfMonitoringServices->GetSupportedSystemMetrics(&systemMetricsSupport);
    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    res2 = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

    // Loop 10 time to accumulate data and show the current metrics in each loop
    IADLXAllMetricsPtr allMetrics;
    IADLXSystemMetricsPtr systemMetrics;
    IADLXGPUMetricsPtr gpuMetrics;
    IADLXFPSPtr oneFPS;
    for (int i = 0; i < 10; ++i)
    {
        // clear screen when show current metrics
        system("cls");
        // Get current All metrics
        ADLX_RESULT res1 = perfMonitoringServices->GetCurrentAllMetrics(&allMetrics);
        if (ADLX_SUCCEEDED(res1))
        {
            std::cout << "The current all metrics: " << std::endl;
            // Get current system metrics.
            res1 = allMetrics->GetSystemMetrics(&systemMetrics);
            // Show timestamp, CPU usage, system RAM and smart shift
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                std::cout << std::boolalpha;  // display bool variable as true of false
                GetTimeStamp(systemMetrics);
                ShowCPUUsage(systemMetricsSupport, systemMetrics);
                ShowSystemRAM(systemMetricsSupport, systemMetrics);
                ShowSmartShift(systemMetricsSupport, systemMetrics);
                std::cout << std::noboolalpha;
            }
            // Get current GPU metrics
            res1 = allMetrics->GetGPUMetrics(oneGPU, &gpuMetrics);
            // Show timestamp and GPU metrics
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                std::cout << std::boolalpha;  // display bool variable as true of false
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
                ShowGPUMemoryTemperature(gpuMetricsSupport, gpuMetrics);
                ShowNPUActivityLevel(gpuMetricsSupport, gpuMetrics);
                ShowNPUFrequency(gpuMetricsSupport, gpuMetrics);
                std::cout << std::noboolalpha;
            }
            // Get current FPS metrics
            res1 = allMetrics->GetFPS(&oneFPS);
            if (ADLX_SUCCEEDED(res1))
            {
                adlx_int64 timeStamp = 0;
                res1 = oneFPS->TimeStamp(&timeStamp);
                if (ADLX_SUCCEEDED(res1))
                    std::cout << "The current metric time stamp is: " << timeStamp << "ms\n";
                adlx_int fpsData = 0;
                res1 = oneFPS->FPS(&fpsData);
                if (ADLX_SUCCEEDED(res1))
                    std::cout << "The current metric FPS is: " << fpsData << std::endl;
                else if (res1 == ADLX_NOT_SUPPORTED)
                    std::cout << "Don't support FPS" << std::endl;
            }
        }
        Sleep(1000);
    }

    MainMenu();
}

// Show historical all metrics
void ShowHistoricalAllMetrics(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
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

    // Grab the all metrics history from 10 seconds ago(10000 ms: the first parameter) to the present time(0 ms: the second parameter)
    IADLXAllMetricsListPtr allMetricsList;
    res = perfMonitoringServices->GetAllMetricsHistory(10000, 0, &allMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get system metrics support
        IADLXSystemMetricsSupportPtr systemMetricsSupport;
        ADLX_RESULT systemRes = perfMonitoringServices->GetSupportedSystemMetrics(&systemMetricsSupport);

        // Get GPU metrics support
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        ADLX_RESULT gpuRes = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

        // Display each all metrics in the list
        IADLXAllMetricsPtr allMetrics;
        IADLXSystemMetricsPtr systemMetrics;
        IADLXGPUMetricsPtr gpuMetrics;
        IADLXFPSPtr oneFPS;
        for (int i = allMetricsList->Begin(); i != allMetricsList->End(); ++i)
        {
            std::cout << "********** historical system metrics " << i + 1 << ": **********" << std::endl;
            res = allMetricsList->At(i, &allMetrics);
            if (ADLX_SUCCEEDED(res))
            {
                res = allMetrics->GetSystemMetrics(&systemMetrics);
                // Show time stamp, CPU usage, system RAM, smart shift of first system metrics
                if (ADLX_SUCCEEDED(systemRes) && ADLX_SUCCEEDED(res))
                {
                    std::cout << std::boolalpha;  // display bool variable as true of false
                    GetTimeStamp(systemMetrics);
                    ShowCPUUsage(systemMetricsSupport, systemMetrics);
                    ShowSystemRAM(systemMetricsSupport, systemMetrics);
                    ShowSmartShift(systemMetricsSupport, systemMetrics);
                    std::cout << std::noboolalpha;
                }
                res = allMetrics->GetGPUMetrics(oneGPU, &gpuMetrics);
                // Show timestamp and GPU metrics
                if (ADLX_SUCCEEDED(gpuRes) && ADLX_SUCCEEDED(res))
                {
                    std::cout << std::boolalpha;  // display bool variable as true of false
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
                    ShowGPUMemoryTemperature(gpuMetricsSupport, gpuMetrics);
                    ShowNPUActivityLevel(gpuMetricsSupport, gpuMetrics);
                    ShowNPUFrequency(gpuMetricsSupport, gpuMetrics);
                    std::cout << std::noboolalpha;
                }
                res = allMetrics->GetFPS(&oneFPS);
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
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->StopPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Stop tracking performance metrics failed" << std::endl;
        return;
    }
}