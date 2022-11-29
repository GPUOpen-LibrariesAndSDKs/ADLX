//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfGPUMetrics.c
/// \brief Demonstrates how to control GPU metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Show GPU metrics range
void ShowGPUMetricsRange(IADLXPerformanceMonitoringServices* perfMonitoringServices, IADLXGPU* oneGPU);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Show current GPU metrics
void ShowCurrentGPUMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

// Show historical GPU metrics
void ShowHistoricalGPUMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU);

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
            printf("\tGet Performance Monitoring services failed\n");
        if (perfMonitoringService != NULL)
        {
            perfMonitoringService->pVtbl->Release(perfMonitoringService);
            perfMonitoringService = NULL;
        }
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialization failed", 0);

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
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to display the GPU metrics range\n");
    printf("\t->Press 2 to display the current GPU metrics\n");
    printf("\t->Press 3 to display the historical GPU metrics\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

// Display GPU metrics range
void ShowGPUMetricsRange(IADLXPerformanceMonitoringServices* perfMonitoringServices, IADLXGPU* oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupport* gpuMetricsSupport = NULL;
    ADLX_RESULT res = perfMonitoringServices->pVtbl->GetSupportedGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetricsSupport);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_int minValue = 0, maxValue = 0;

        // Get GPU usage range
        res = gpuMetricsSupport->pVtbl->GetGPUUsageRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU usage range between %d%% and %d%%\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU usage range not supported\n");

        // Get GPU clock speed range
        res = gpuMetricsSupport->pVtbl->GetGPUClockSpeedRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU clock speed range between %dMHz and %dMHz\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU clock speed range not supported\n");

        // Get GPU VRAM clock speed range
        res = gpuMetricsSupport->pVtbl->GetGPUVRAMClockSpeedRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU VRAM clock speed range between %dMHz and %dMHz\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU VRAM clock speed range not supported\n");

        // Get GPU temperature range
        res = gpuMetricsSupport->pVtbl->GetGPUTemperatureRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU temperature range between %d%cC and %d%cC\n", minValue, g_degree, maxValue, g_degree);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU temperature range not supported\n");

        // Get GPU hotspot temperature range
        res = gpuMetricsSupport->pVtbl->GetGPUHotspotTemperatureRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU hotspot temperature range between %d%cC and %d%cC\n", minValue, g_degree, maxValue, g_degree);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU hotspot temperature range not supported\n");

        // Get GPU power range
        res = gpuMetricsSupport->pVtbl->GetGPUPowerRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU power range between %dW and %dW\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU power range not supported\n");

        // Get GPU fan speed range
        res = gpuMetricsSupport->pVtbl->GetGPUFanSpeedRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU fan speed range between %dRPM and %dRPM\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU fan speed range not supported\n");

        // Get GPU VRAM range
        res = gpuMetricsSupport->pVtbl->GetGPUVRAMRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU VRAM range between %dMB and %dMB\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU VRAM range not supported\n");

        // Get GPU voltage range
        res = gpuMetricsSupport->pVtbl->GetGPUVoltageRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU voltage range between %dmV and %dmV\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU voltage range not supported\n");

        // Get GPU total board power range
        res = gpuMetricsSupport->pVtbl->GetGPUTotalBoardPowerRange(gpuMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The GPU total board power range between %dW and %dW\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("GPU total board power range not supported\n");
    }
    if (gpuMetricsSupport != NULL)
    {
        gpuMetricsSupport->pVtbl->Release(gpuMetricsSupport);
        gpuMetricsSupport = NULL;
    }
}

// Display the system time stamp (in ms)
void GetTimeStamp(IADLXGPUMetrics *gpuMetrics)
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
        printf("GPU clock speed support status: %d\n", supported);
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
    // Display the GPU VRAM clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUVRAMClockSpeed(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU VRAM clock speed support status: %d\n", supported);
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
    // Display the GPU temperature support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUTemperature(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU temperature support status: %d\n", supported);
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

// Display GPU power(in W)
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

// Display GPU total board power(in W)
void ShowGPUTotalBoardPower(IADLXGPUMetricsSupport *gpuMetricsSupport, IADLXGPUMetrics *gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU total board power support status
    ADLX_RESULT res = gpuMetricsSupport->pVtbl->IsSupportedGPUTotalBoardPower(gpuMetricsSupport, &supported);
    if (ADLX_SUCCEEDED(res))
    {
        printf("GPU total board power support status: %d\n", supported);
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->pVtbl->GPUTotalBoardPower(gpuMetrics, &power);
            if (ADLX_SUCCEEDED(res))
                printf("The GPU total board power is: %fW\n", power);
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

// Display current GPU metrics
void ShowCurrentGPUMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupport *gpuMetricsSupport = NULL;
    ADLX_RESULT res1 = perfMonitoringServices->pVtbl->GetSupportedGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetricsSupport);

    // Accumulate and display current metrics for each of 10 loops
    IADLXGPUMetrics *gpuMetrics = NULL;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current GPU metrics
        ADLX_RESULT res2 = perfMonitoringServices->pVtbl->GetCurrentGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetrics);

        // Display timestamp and GPU metrics
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            printf("The current GPU metrics: \n");
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
        }
        Sleep(1000);

        // Free
        if (gpuMetrics != NULL)
        {
            gpuMetrics->pVtbl->Release(gpuMetrics);
            gpuMetrics = NULL;
        }
    }

    // Free
    if (gpuMetricsSupport != NULL)
    {
        gpuMetricsSupport->pVtbl->Release(gpuMetricsSupport);
        gpuMetricsSupport = NULL;
    }

    MainMenu();
}

// Display historical GPU Metrics
void ShowHistoricalGPUMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices, IADLXGPU *oneGPU)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->pVtbl->ClearPerformanceMetricsHistory(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to clear historical data\n");
        return;
    }

    // Start tracking performance metrics
    res = perfMonitoringServices->pVtbl->StartPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to start tracking performance metrics\n");
        return;
    }

    // Wait for 10 seconds to accumulate metrics
    printf("Wait for 10 seconds to accumulate metrics...\n");
    Sleep(10000);

    // Get GPU metrics history from 10 seconds ago(10000 ms: the third parameter) to the present time(0 ms: the fourth parameter)
    IADLXGPUMetricsList* gpuMetricsList = NULL;
    res = perfMonitoringServices->pVtbl->GetGPUMetricsHistory(perfMonitoringServices, oneGPU, 10000, 0, &gpuMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU metrics support
        IADLXGPUMetricsSupport* gpuMetricsSupport = NULL;
        ADLX_RESULT res1 = perfMonitoringServices->pVtbl->GetSupportedGPUMetrics(perfMonitoringServices, oneGPU, &gpuMetricsSupport);

        // Display all the GPU metrics in the list
        IADLXGPUMetrics* gpuMetrics = NULL;
        for (int i = gpuMetricsList->pVtbl->Begin(gpuMetricsList); i != gpuMetricsList->pVtbl->End(gpuMetricsList); ++i)
        {
            printf("********** historical GPU metrics %d: **********\n", i + 1);
            ADLX_RESULT res2 = gpuMetricsList->pVtbl->At_GPUMetricsList(gpuMetricsList, i, &gpuMetrics);
            // Display timestamp and GPU metrics
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
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
            }
            printf("\n");
            if (gpuMetrics != NULL)
            {
                gpuMetrics->pVtbl->Release(gpuMetrics);
                gpuMetrics = NULL;
            }
        }
        if (gpuMetricsSupport != NULL)
        {
            gpuMetricsSupport->pVtbl->Release(gpuMetricsSupport);
            gpuMetricsSupport = NULL;
        }
    }
    if (gpuMetricsList != NULL)
    {
        gpuMetricsList->pVtbl->Release(gpuMetricsList);
        gpuMetricsList = NULL;
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->pVtbl->StopPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to stop tracking performance metrics\n");
        return;
    }
}