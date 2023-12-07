//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfSystemMetrics.c
/// \brief Demonstrates how to control system metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring1.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display system metrics range
void ShowSystemMetricsRange(IADLXPerformanceMonitoringServices* perfMonitoringServices);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Display current system metrics
void ShowCurrentSystemMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices);

// Display historical system metrics
void ShowHistoricalSystemMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices);

 int main()
 {
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXSystem *sys = ADLXHelper_GetSystemServices();
        IADLXPerformanceMonitoringServices *perfMonitoringServices = NULL;
        ADLX_RESULT res = sys->pVtbl->GetPerformanceMonitoringServices(sys, &perfMonitoringServices);
        if (ADLX_SUCCEEDED(res))
        {
            // Display main menu options
            MainMenu();
            // Get and execute the choice
            MenuControl(perfMonitoringServices);
        }
        else
            printf("\tGet performance monitoring services failed\n");
        if (perfMonitoringServices != NULL)
        {
            perfMonitoringServices->pVtbl->Release(perfMonitoringServices);
            perfMonitoringServices = NULL;
        }
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

// Main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to display the system metrics range\n");
    printf("\t->Press 2 to display the current system metrics\n");
    printf("\t->Press 3 to display the historical system metrics\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices)
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

// Display system metrics range
void ShowSystemMetricsRange(IADLXPerformanceMonitoringServices* perfMonitoringServices)
{
    // Get system metrics support
    IADLXSystemMetricsSupport* systemMetricsSupport = NULL;
    ADLX_RESULT res = perfMonitoringServices->pVtbl->GetSupportedSystemMetrics(perfMonitoringServices, &systemMetricsSupport);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_int minValue = 0, maxValue = 0;

        // Get CPU usage range
        res = systemMetricsSupport->pVtbl->GetCPUUsageRange(systemMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The CPU usage range between %d%% and %d%%\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("CPU usage range not supported\n");

        // Get system RAM range
        res = systemMetricsSupport->pVtbl->GetSystemRAMRange(systemMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The system RAM range between %dMB and %dMB\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("System RAM range not supported\n");

        // Get SmartShift range
        res = systemMetricsSupport->pVtbl->GetSmartShiftRange(systemMetricsSupport, &minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            printf("The smart shift range between %d and %d\n", minValue, maxValue);
        else if (res == ADLX_NOT_SUPPORTED)
            printf("SmartShift range not supported\n");
    }
    if (systemMetricsSupport != NULL)
    {
        systemMetricsSupport->pVtbl->Release(systemMetricsSupport);
        systemMetricsSupport = NULL;
    }
}

// Display the system time stamp (in ms)
void GetTimeStamp(IADLXSystemMetrics *systemMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = systemMetrics->pVtbl->TimeStamp(systemMetrics, &timeStamp);
    if (ADLX_SUCCEEDED(res))
        printf("The system timp stamp is: %lldms\n", timeStamp);
}

// Display CPU usage (in %)
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

// Show SmartShift
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

// Show SmartShift Max
void ShowSmartShiftMax(IADLXSystemMetricsSupport* systemMetricsSupport, IADLXSystemMetrics* systemMetrics)
{
    IADLXSystemMetricsSupport1* sysMetricsSupport1 = NULL;
    ADLX_RESULT res = systemMetricsSupport->pVtbl->QueryInterface(systemMetricsSupport, IID_IADLXSystemMetricsSupport1(), (void**)&sysMetricsSupport1);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool supported = false;
        // Display power distribution support status
        res = sysMetricsSupport1->pVtbl->IsSupportedPowerDistribution(sysMetricsSupport1, &supported);
        if (ADLX_SUCCEEDED(res))
        {
            printf("PowerDistribution support status: %d\n", supported);
            if (supported)
            {
                IADLXSystemMetrics1* sysMetrics1 = NULL;
                res = systemMetrics->pVtbl->QueryInterface(systemMetrics, IID_IADLXSystemMetrics1(), (void*)&sysMetrics1);
                if (ADLX_SUCCEEDED(res))
                {
                    int apuShiftValue, gpuShiftValue, apuShiftLimit, gpuShiftLimit, totalShiftLimit;
                    res = sysMetrics1->pVtbl->PowerDistribution(sysMetrics1, &apuShiftValue, &gpuShiftValue, &apuShiftLimit, &gpuShiftLimit, &totalShiftLimit);
                    if (ADLX_SUCCEEDED(res))
                        printf("The PowerDistribution is:\n apuShiftValue: %d , gpuShiftValue: %d , apuShiftLimit: %d , gpuShiftLimit: %d , totalShiftLimit: %d\n"
                            , apuShiftValue, gpuShiftValue, apuShiftLimit, gpuShiftLimit, totalShiftLimit);

                    // Release IADLXSystemMetrics1 interface
                    sysMetrics1->pVtbl->Release(sysMetrics1);
                }
                else
                {
                    printf("\tGet IADLXSystemMetrics1Ptr failed\n");
                }
            }
        }

        // Release IADLXSystemMetricsSupport1 interface
        sysMetricsSupport1->pVtbl->Release(sysMetricsSupport1);
    }
    else
    {
        printf("\tGet IADLXSystemMetricsSupport1Ptr failed\n");
    }
}

// Display current system metrics
void ShowCurrentSystemMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices)
{
    // Get system metrics support
    IADLXSystemMetricsSupport* systemMetricsSupport = NULL;
    ADLX_RESULT res1 = perfMonitoringServices->pVtbl->GetSupportedSystemMetrics(perfMonitoringServices, &systemMetricsSupport);

    // Accumulate and display current metrics for each of the 10 loops
    IADLXSystemMetrics* systemMetrics = NULL;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current system metrics
        ADLX_RESULT res2 = perfMonitoringServices->pVtbl->GetCurrentSystemMetrics(perfMonitoringServices, &systemMetrics);

        // Display timestamp, CPU usage, system RAM, and SmartShift
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            printf("The current system metrics: \n");
            GetTimeStamp(systemMetrics);
            ShowCPUUsage(systemMetricsSupport, systemMetrics);
            ShowSystemRAM(systemMetricsSupport, systemMetrics);
            ShowSmartShift(systemMetricsSupport, systemMetrics);
            ShowSmartShiftMax(systemMetricsSupport, systemMetrics);
        }
        Sleep(1000);

        // Free
        if (systemMetrics != NULL)
        {
            systemMetrics->pVtbl->Release(systemMetrics);
            systemMetrics = NULL;
        }
    }

    // Free
    if (systemMetricsSupport != NULL)
    {
        systemMetricsSupport->pVtbl->Release(systemMetricsSupport);
        systemMetricsSupport = NULL;
    }

    MainMenu();
}

// Display historical system metrics
void ShowHistoricalSystemMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->pVtbl->ClearPerformanceMetricsHistory(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to clear historical data\n");
        return;
    }

    // Get current max historical size (in s)
    adlx_int maxHistorySize = 0;
    res = perfMonitoringServices->pVtbl->GetMaxPerformanceMetricsHistorySize(perfMonitoringServices, &maxHistorySize);
    if (ADLX_SUCCEEDED(res))
        printf("The current max historical size is: %ds\n", maxHistorySize);
    // Get the max historical size range. The max historical size must be set within this range.
    ADLX_IntRange range;
    res = perfMonitoringServices->pVtbl->GetMaxPerformanceMetricsHistorySizeRange(perfMonitoringServices, &range);
    if (ADLX_SUCCEEDED(res))
        printf("The range of max historical size is: (%d, %d)s\n", range.minValue, range.maxValue);
    // Change max historical size to minimum value
    res = perfMonitoringServices->pVtbl->SetMaxPerformanceMetricsHistorySize(perfMonitoringServices, range.minValue);
    if (ADLX_SUCCEEDED(res))
    {
        perfMonitoringServices->pVtbl->GetMaxPerformanceMetricsHistorySize(perfMonitoringServices, &maxHistorySize);
        printf("Set max historical size to minimum value succeeded, the current max historical is: %ds\n", maxHistorySize);
    }

    // Get current sampling interval (in ms)
    adlx_int samplingInterval = 0;
    res = perfMonitoringServices->pVtbl->GetSamplingInterval(perfMonitoringServices, &samplingInterval);
    if (ADLX_SUCCEEDED(res))
        printf("The current sampling interval is: %dms\n", samplingInterval);
    // Get the sampling interval range. The sampling interval must be set within this range.
    res = perfMonitoringServices->pVtbl->GetSamplingIntervalRange(perfMonitoringServices, &range);
    if (ADLX_SUCCEEDED(res))
        printf("The range of sampling interval is: (%d, %d)ms\n", range.minValue, range.maxValue);
    // Change sampling interval to minimum value
    res = perfMonitoringServices->pVtbl->SetSamplingInterval(perfMonitoringServices, range.minValue);
    if (ADLX_SUCCEEDED(res))
    {
        perfMonitoringServices->pVtbl->GetSamplingInterval(perfMonitoringServices, &samplingInterval);
        printf("Set sampling interval to minimum value succeeded, the current sampling interval is: %dms\n", samplingInterval);
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

    // Check the current performance metrics historical size (in s) upon accumulation
    adlx_int currentHistorySize = 0;
    res = perfMonitoringServices->pVtbl->GetCurrentPerformanceMetricsHistorySize(perfMonitoringServices, &currentHistorySize);
    if (ADLX_SUCCEEDED(res))
        printf("The current historical size is: %ds\n", currentHistorySize);

    // Get system metrics history from 10 seconds ago(10000 ms: the second parameter) to the present time(0 ms: the third parameter)
    IADLXSystemMetricsList* systemMetricsList = NULL;
    res = perfMonitoringServices->pVtbl->GetSystemMetricsHistory(perfMonitoringServices, 10000, 0, &systemMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get the system metrics support
        IADLXSystemMetricsSupport* systemMetricsSupport = NULL;
        ADLX_RESULT res1 = perfMonitoringServices->pVtbl->GetSupportedSystemMetrics(perfMonitoringServices, &systemMetricsSupport);

        // Display all the system metrics in the list
        IADLXSystemMetrics* systemMetrics = NULL;
        for (int i = systemMetricsList->pVtbl->Begin(systemMetricsList); i != systemMetricsList->pVtbl->End(systemMetricsList); ++i)
        {
            printf("********** historical system metrics %d: **********\n", i + 1);
            ADLX_RESULT res2 = systemMetricsList->pVtbl->At_SystemMetricsList(systemMetricsList, i, &systemMetrics);
            // Display first system metrics time stamp, CPU usage, system RAM, and SmartShift
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                GetTimeStamp(systemMetrics);
                ShowCPUUsage(systemMetricsSupport, systemMetrics);
                ShowSystemRAM(systemMetricsSupport, systemMetrics);
                ShowSmartShift(systemMetricsSupport, systemMetrics);
                ShowSmartShiftMax(systemMetricsSupport, systemMetrics);
            }
            printf("\n");
            if (systemMetrics != NULL)
            {
                systemMetrics->pVtbl->Release(systemMetrics);
                systemMetrics = NULL;
            }
        }
        if (systemMetricsSupport != NULL)
        {
            systemMetricsSupport->pVtbl->Release(systemMetricsSupport);
            systemMetricsSupport = NULL;
        }
    }
    if (systemMetricsList != NULL)
    {
        systemMetricsList->pVtbl->Release(systemMetricsList);
        systemMetricsList = NULL;
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->pVtbl->StopPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to stop tracking performance metrics\n");
        return;
    }
}