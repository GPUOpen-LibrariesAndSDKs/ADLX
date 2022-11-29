//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfAllMetrics.c
/// \brief Demonstrates how to control all metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"


// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Display all current metrics
void ShowCurrentAllMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

// Display all historical metrics
void ShowHistoricalAllMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

// ASCII °
static const signed char g_degree = 248;

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXSystem *sys = ADLXHelper_GetSystemServices();
        IADLXPerformanceMonitoringServices *perfMonitoringService = NULL;
        res = sys->pVtbl->GetPerformanceMonitoringServices(sys, &perfMonitoringService);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPUList* gpus = NULL;
            // Get GPU list
            res = sys->pVtbl->GetGPUs(sys, &gpus);
            if (ADLX_SUCCEEDED(res))
            {
                // Use initial GPU
                IADLXGPU* oneGPU = NULL;
                res = gpus->pVtbl->At_GPUList(gpus, gpus->pVtbl->Begin(gpus), &oneGPU);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenu();
                    // Get and execute the choice
                    MenuControl(perfMonitoringService, oneGPU);
                }
                else
                    printf("\tGet particular GPU failed\n");
                if (oneGPU != NULL)
                {
                    oneGPU->pVtbl->Release(oneGPU);
                    oneGPU = NULL;
                }
            }
            else
                printf("\tGet GPU list failed\n");
            if (gpus != NULL)
            {
                gpus->pVtbl->Release(gpus);
                gpus = NULL;
            }
        }
        else
            printf("\tGet performance monitoring services failed\n");
        if (perfMonitoringService != NULL)
        {
            perfMonitoringService->pVtbl->Release(perfMonitoringService);
            perfMonitoringService = NULL;
        }
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    printf("\tChoose one of the following options\n");

    printf("\t->Press 1 to display all current metrics\n");
    printf("\t->Press 2 to display all historical metrics\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display menu options\n");
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

// Display the system time stamp (in ms)
void GetTimeStampBySystem(IADLXSystemMetrics *systemMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = systemMetrics->pVtbl->TimeStamp(systemMetrics, &timeStamp);
    if (ADLX_SUCCEEDED(res))
        printf("The system timp stamp is: %lldms\n", timeStamp);
}

// Display CPU usage(in %)
void ShowCPUUsage(IADLXSystemMetricsSupport *systemMetricsSupport, IADLXSystemMetrics *systemMetrics)
{
    adlx_bool supported = false;
    // Display CPU usage support status
    ADLX_RESULT res = systemMetricsSupport->pVtbl->IsSupportedCPUUsage(systemMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("CPU usage support status: %d\n", supported);
        if (supported)
        {
            adlx_double cpuUsage = 0;
            res = systemMetrics->pVtbl->CPUUsage(systemMetrics, &cpuUsage);
            if (ADLX_SUCCEEDED(res))
                printf("The CPU usage is: %f%%\n", cpuUsage);
        }
    }
}

// Display system RAM (in MB)
void ShowSystemRAM(IADLXSystemMetricsSupport *systemMetricsSupport, IADLXSystemMetrics *systemMetrics)
{
    adlx_bool supported = false;
    // Display system RAM usage support status
    ADLX_RESULT res = systemMetricsSupport->pVtbl->IsSupportedSystemRAM(systemMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("System RAM usage support status: %d\n", supported);
        if (supported)
        {
            adlx_int systemRAM = 0;
            res = systemMetrics->pVtbl->SystemRAM(systemMetrics, &systemRAM);
            if (ADLX_SUCCEEDED(res))
                printf("The system RAM is: %dMB\n", systemRAM);
        }
    }
}

// Display SmartShift
void ShowSmartShift(IADLXSystemMetricsSupport *systemMetricsSupport, IADLXSystemMetrics *systemMetrics)
{
    adlx_bool supported = false;
    // Display SmartShift support status
    ADLX_RESULT res = systemMetricsSupport->pVtbl->IsSupportedSmartShift(systemMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("SmartShift support status: %d\n", supported);
        if (supported)
        {
            adlx_int smartShift;
            res = systemMetrics->pVtbl->SmartShift(systemMetrics, &smartShift);
            if (ADLX_SUCCEEDED(res))
                printf("The smart shift is: %d\n", smartShift);
        }
    }
}

// Display the GPU metrics time stamp (in ms)
void GetTimeStampByGPU(IADLXGPUMetrics *gpuMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = gpuMetrics->pVtbl->TimeStamp(gpuMetrics, &timeStamp);
    if (ADLX_SUCCEEDED(res))
        printf("The GPU timp stamp is: %lldms\n", timeStamp);
}

// Display GPU usage (in %)
void ShowGPUUsage(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU usage support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUUsage(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU usage support status: %d\n", supported);
        if (supported)
        {
            adlx_double usage = 0;
            res = gpuMetrics->pVtbl->GPUUsage(gpuMetrics, &usage);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU usage is: %f%%\n", usage);
        }
    }
}

// Display GPU clock speed (in MHz)
void ShowGPUClockSpeed(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUClockSpeed(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU system clock support status: %d\n", supported);
        if (supported)
        {
            adlx_int systemClock = 0;
            res = gpuMetrics->pVtbl->GPUClockSpeed(gpuMetrics, &systemClock);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU system clock is: %dMHz\n", systemClock);
        }
    }
}

// Display GPU VRAM clock speed (in MHz)
void ShowGPUVRAMClockSpeed(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU VRAM clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUVRAMClockSpeed(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU memory clock support status: %d\n", supported);
        if (supported)
        {
            adlx_int memoryClock = 0;
            res = gpuMetrics->pVtbl->GPUVRAMClockSpeed(gpuMetrics, &memoryClock);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU memory clock is: %dMHz\n", memoryClock);
        }
    }
}

// Display GPU temperature(in °C)
void ShowGPUTemperature(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU temperature support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUTemperature(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU temperture support status: %d\n", supported);
        if (supported)
        {
            adlx_double temperature = 0;
            res = gpuMetrics->pVtbl->GPUTemperature(gpuMetrics, &temperature);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU temperature is: %f%cC\n", temperature, g_degree);
        }
    }
}

// Display GPU hotspot temperature(in °C)
void ShowGPUHotspotTemperature(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU hotspot temperature support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUHotspotTemperature(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU hotspot temperature support status: %d\n", supported);
        if (supported)
        {
            adlx_double hotspotTemperature = 0;
            res = gpuMetrics->pVtbl->GPUHotspotTemperature(gpuMetrics, &hotspotTemperature);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU hotspot temperature is: %f%cC\n", hotspotTemperature, g_degree);
        }
    }
}

// Display GPU power (in W)
void ShowGPUPower(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU power support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUPower(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU power support status: %d\n", supported);
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->pVtbl->GPUPower(gpuMetrics, &power);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU power is: %fW\n", power);
        }
    }
}

// Display GPU fan speed (in RPM)
void ShowGPUFanSpeed(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU fan speed support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUFanSpeed(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU fan speed support status: %d\n", supported);
        if (supported)
        {
            adlx_int fanSpeed = 0;
            res = gpuMetrics->pVtbl->GPUFanSpeed(gpuMetrics, &fanSpeed);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU fan speed is: %dRPM\n", fanSpeed);
        }
    }
}

// Display GPU VRAM (in MB)
void ShowGPUVRAM(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU VRAM support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUVRAM(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU VRAM support status: %d\n", supported);
        if (supported)
        {
            adlx_int VRAM = 0;
            res = gpuMetrics->pVtbl->GPUVRAM(gpuMetrics, &VRAM);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU VRAM is: %dMB\n", VRAM);
        }
    }
}

// Display GPU Voltage (in mV)
void ShowGPUVoltage(IADLXGPUMetricsSupport* gpuMetricsSupport, IADLXGPUMetrics* gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU voltage support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUVoltage(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU voltage support status: %d\n", supported);
        if (supported)
        {
            adlx_int Voltage = 0;
            res = gpuMetrics->pVtbl->GPUVoltage(gpuMetrics, &Voltage);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU Voltage is: %dmV\n", Voltage);
        }
    }
}

// Display all current metrics
void ShowCurrentAllMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
{
    // Get system metrics support
    IADLXSystemMetricsSupport *systemMetricsSupport = NULL;
    ADLX_RESULT res2 = perfMonitoringServices->pVtbl->GetSupportedSystemMetrics(perfMonitoringServices, &systemMetricsSupport);
    // Get GPU metrics support
    IADLXGPUMetricsSupport *gpuMetricsSupport = NULL;
    res2 = perfMonitoringServices->pVtbl->GetSupportedGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetricsSupport);

    // Accumulate and display current metrics for each of 10 loops
    IADLXAllMetrics *allMetrics = NULL;
    IADLXSystemMetrics *systemMetrics = NULL;
    IADLXGPUMetrics *gpuMetrics = NULL;
    IADLXFPS *oneFPS = NULL;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get all current metrics
        ADLX_RESULT res1 = perfMonitoringServices->pVtbl->GetCurrentAllMetrics(perfMonitoringServices, &allMetrics);
        if (ADLX_SUCCEEDED(res1))
        {
            printf("The current all metrics: \n");
            // Get current system metrics
            res1 = allMetrics->pVtbl->GetSystemMetrics(allMetrics, &systemMetrics);
            // Display timestamp, CPU usage, system RAM, and SmartShift
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                GetTimeStampBySystem(systemMetrics);
                ShowCPUUsage(systemMetricsSupport, systemMetrics);
                ShowSystemRAM(systemMetricsSupport, systemMetrics);
                ShowSmartShift(systemMetricsSupport, systemMetrics);
            }
            // Free
            if (systemMetrics != NULL)
            {
                systemMetrics->pVtbl->Release(systemMetrics);
                systemMetrics = NULL;
            }
            // Get current GPU metrics
            res1 = allMetrics->pVtbl->GetGPUMetrics(allMetrics, oneGPU, &gpuMetrics);
            // Display timestamp and GPU metrics
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                GetTimeStampByGPU(gpuMetrics);
                ShowGPUUsage(gpuMetricsSupport, gpuMetrics);
                ShowGPUClockSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMClockSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUTemperature(gpuMetricsSupport, gpuMetrics);
                ShowGPUHotspotTemperature(gpuMetricsSupport, gpuMetrics);
                ShowGPUPower(gpuMetricsSupport, gpuMetrics);
                ShowGPUFanSpeed(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAM(gpuMetricsSupport, gpuMetrics);
                ShowGPUVoltage(gpuMetricsSupport, gpuMetrics);
            }
            // Free
            if (gpuMetrics != NULL)
            {
                gpuMetrics->pVtbl->Release(gpuMetrics);
                gpuMetrics = NULL;
            }
            // Get current FPS metrics
            res1 = allMetrics->pVtbl->GetFPS(allMetrics, &oneFPS);
            if (ADLX_SUCCEEDED(res1))
            {
                adlx_int64 timeStamp = 0;
                res1 = oneFPS->pVtbl->TimeStamp(oneFPS, &timeStamp);
                if (ADLX_SUCCEEDED(res1))
                    printf("The current metric time stamp is: %lldms\n", timeStamp);
                adlx_int fpsData = 0;
                res1 = oneFPS->pVtbl->FPS(oneFPS, &fpsData);
                if (ADLX_SUCCEEDED(res1))
                    printf("The current metric FPS is: %d\n", fpsData);
                else if (res1 == ADLX_NOT_SUPPORTED)
                    printf("FPS not supported\n");
            }
            // Free
            if (oneFPS != NULL)
            {
                oneFPS->pVtbl->Release(oneFPS);
                oneFPS = NULL;
            }
        }
        Sleep(1000);
        // Free
        if (allMetrics != NULL)
        {
            allMetrics->pVtbl->Release(allMetrics);
            allMetrics = NULL;
        }
    }
    // Free
    if (systemMetricsSupport != NULL)
    {
        systemMetricsSupport->pVtbl->Release(systemMetricsSupport);
        systemMetricsSupport = NULL;
    }
    if (gpuMetricsSupport != NULL)
    {
        gpuMetricsSupport->pVtbl->Release(gpuMetricsSupport);
        gpuMetricsSupport = NULL;
    }

    MainMenu();
}

// Show all historical metrics
void ShowHistoricalAllMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->pVtbl->ClearPerformanceMetricsHistory(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Clear historical data failed\n");
        return;
    }

    // Start tracking performance metrics
    res = perfMonitoringServices->pVtbl->StartPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Start tracking performance metrics failed\n");
        return;
    }

    // Wait for 10 seconds to accumulate metrics
    printf("Wait for 10 seconds to accumulate metrics...\n");
    Sleep(10000);

    // Get all metrics history from 10 seconds ago(10000 ms: the second parameter) to the present time(0 ms: the third parameter)
    IADLXAllMetricsList *allMetricsList = NULL;
    res = perfMonitoringServices->pVtbl->GetAllMetricsHistory(perfMonitoringServices, 10000, 0, &allMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get system metrics support
        IADLXSystemMetricsSupport *systemMetricsSupport = NULL;
        ADLX_RESULT systemRes = perfMonitoringServices->pVtbl->GetSupportedSystemMetrics(perfMonitoringServices, &systemMetricsSupport);

        // Get GPU metrics support
        IADLXGPUMetricsSupport *gpuMetricsSupport = NULL;
        ADLX_RESULT gpuRes = perfMonitoringServices->pVtbl->GetSupportedGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetricsSupport);

        // Display all the metrics in the list
        IADLXAllMetrics *allMetrics = NULL;
        IADLXSystemMetrics *systemMetrics = NULL;
        IADLXGPUMetrics *gpuMetrics = NULL;
        IADLXFPS *oneFPS = NULL;
        for (int i = allMetricsList->pVtbl->Begin(allMetricsList); i != allMetricsList->pVtbl->End(allMetricsList); ++i)
        {
            printf("********** historical system metrics %d: **********\n", i + 1);
            res = allMetricsList->pVtbl->At_AllMetricsList(allMetricsList, i, &allMetrics);
            if (ADLX_SUCCEEDED(res))
            {
                res = allMetrics->pVtbl->GetSystemMetrics(allMetrics, &systemMetrics);
                // Display first system metrics time stamp, CPU usage, system RAM, and SmartShift
                if (ADLX_SUCCEEDED(systemRes) && ADLX_SUCCEEDED(res))
                {
                    GetTimeStampBySystem(systemMetrics);
                    ShowCPUUsage(systemMetricsSupport, systemMetrics);
                    ShowSystemRAM(systemMetricsSupport, systemMetrics);
                    ShowSmartShift(systemMetricsSupport, systemMetrics);
                }
                // Free
                if (systemMetrics != NULL)
                {
                    systemMetrics->pVtbl->Release(systemMetrics);
                    systemMetrics = NULL;
                }
                res = allMetrics->pVtbl->GetGPUMetrics(allMetrics, oneGPU, &gpuMetrics);
                // Display timestamp and GPU metrics
                if (ADLX_SUCCEEDED(gpuRes) && ADLX_SUCCEEDED(res))
                {
                    GetTimeStampByGPU(gpuMetrics);
                    ShowGPUUsage(gpuMetricsSupport, gpuMetrics);
                    ShowGPUClockSpeed(gpuMetricsSupport, gpuMetrics);
                    ShowGPUVRAMClockSpeed(gpuMetricsSupport, gpuMetrics);
                    ShowGPUTemperature(gpuMetricsSupport, gpuMetrics);
                    ShowGPUHotspotTemperature(gpuMetricsSupport, gpuMetrics);
                    ShowGPUPower(gpuMetricsSupport, gpuMetrics);
                    ShowGPUFanSpeed(gpuMetricsSupport, gpuMetrics);
                    ShowGPUVRAM(gpuMetricsSupport, gpuMetrics);
                    ShowGPUVoltage(gpuMetricsSupport, gpuMetrics);
                }
                // Free
                if (gpuMetrics != NULL)
                {
                    gpuMetrics->pVtbl->Release(gpuMetrics);
                    gpuMetrics = NULL;
                }
                res = allMetrics->pVtbl->GetFPS(allMetrics, &oneFPS);
                if (ADLX_SUCCEEDED(res))
                {
                    adlx_int64 timeStamp = 0;
                    res = oneFPS->pVtbl->TimeStamp(oneFPS, &timeStamp);
                    if (ADLX_SUCCEEDED(res))
                        printf("The time stamp is: %lldms\n", timeStamp);
                    adlx_int fpsData = 0;
                    res = oneFPS->pVtbl->FPS(oneFPS, &fpsData);
                    if (ADLX_SUCCEEDED(res))
                        printf("The FPS is: %d\n", fpsData);
                    else if (res == ADLX_NOT_SUPPORTED)
                        printf("Don't support FPS\n");
                }
                // Free
                if (oneFPS != NULL)
                {
                    oneFPS->pVtbl->Release(oneFPS);
                    oneFPS = NULL;
                }
                printf("\n");
            }
            // Free
            if (allMetrics != NULL)
            {
                allMetrics->pVtbl->Release(allMetrics);
                allMetrics = NULL;
            }
        }
        // Free
        if (systemMetricsSupport != NULL)
        {
            systemMetricsSupport->pVtbl->Release(systemMetricsSupport);
            systemMetricsSupport = NULL;
        }
        if (gpuMetricsSupport != NULL)
        {
            gpuMetricsSupport->pVtbl->Release(gpuMetricsSupport);
            gpuMetricsSupport = NULL;
        }
    }
    // Free
    if (allMetricsList != NULL)
    {
        allMetricsList->pVtbl->Release(allMetricsList);
        allMetricsList = NULL;
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->pVtbl->StopPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Stop tracking performance metrics failed\n");
        return;
    }
}