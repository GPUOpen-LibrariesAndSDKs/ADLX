//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainFPSMetrics.c
/// \brief Demonstrates how to control FPS metrics when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPerformanceMonitoring.h"


// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices *perfMonitoringServices);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Display current FPS metrics
void ShowCurrentFPSMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices);

// Display historical FPS metrics
void ShowHistoricalFPSMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices);

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
        res = sys->pVtbl->GetPerformanceMonitoringServices(sys, &perfMonitoringServices);
        if (ADLX_SUCCEEDED(res))
        {
            // Display main menu options
            MainMenu();
            // Get and execute the choice
            MenuControl(perfMonitoringServices);
        }
        else
            printf("\tGet Performance Monitoring services failed\n");
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
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to display current FPS metrics\n");
    printf("\t->Press 2 to display historical FPS metrics\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display menu options\n");
}

// Menu action control
void MenuControl(IADLXPerformanceMonitoringServices* perfMonitoringServices)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display current metrics
        case '1':
            ShowCurrentFPSMetrics(perfMonitoringServices);
            break;

        // Display historical metrics
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
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

// Display current FPS metrics
void ShowCurrentFPSMetrics(IADLXPerformanceMonitoringServices* perfMonitoringServices)
{
    // Accumulate and display current metrics for each of the 10 loops
    IADLXFPS* oneFPS = NULL;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current FPS metrics
        ADLX_RESULT res = perfMonitoringServices->pVtbl->GetCurrentFPS(perfMonitoringServices, &oneFPS);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_int64 timeStamp = 0;
            res = oneFPS->pVtbl->TimeStamp(oneFPS, &timeStamp);
            if (ADLX_SUCCEEDED(res))
                printf("The current metric time stamp is: %lldms\n", timeStamp);
            adlx_int fpsData = 0;
            res = oneFPS->pVtbl->FPS(oneFPS, &fpsData);
            if (ADLX_SUCCEEDED(res))
                printf("The current metric FPS is: %d\n", fpsData);
            else if (res == ADLX_NOT_SUPPORTED)
                printf("FPS not supported\n");
        }
        Sleep(1000);
        if (oneFPS != NULL)
        {
            oneFPS->pVtbl->Release(oneFPS);
            oneFPS = NULL;
        }
    }

    MainMenu();
}

// Display historical FPS metrics
void ShowHistoricalFPSMetrics(IADLXPerformanceMonitoringServices *perfMonitoringServices)
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
        printf("Failed to start tracking performance metrics\n");
        return;
    }

    // Wait 10 seconds to accumulate metrics
    printf("Wait for 10 seconds to accumulate FPS...\n");
    Sleep(10000);

    // Get FPS metrics history from 10 seconds ago (10000 ms: the second parameter) to the present time (0 ms: the third parameter)
    IADLXFPSList* fpsList = NULL;
    res = perfMonitoringServices->pVtbl->GetFPSHistory(perfMonitoringServices, 10000, 0, &fpsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Display all the listed FPS metrics
        IADLXFPS* oneFPS = NULL;
        for (int i = fpsList->pVtbl->Begin(fpsList); i != fpsList->pVtbl->End(fpsList); ++i)
        {
            printf("********** historical FPS metrics %d: **********\n", i + 1);
            res = fpsList->pVtbl->At_FPSList(fpsList, i, &oneFPS);
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
                    printf("FPS not supported\n");
            }
            printf("\n");

            // Free
            if (oneFPS != NULL)
            {
                oneFPS->pVtbl->Release(oneFPS);
                oneFPS = NULL;
            }
        }
    }

    // Free
    if (fpsList != NULL)
    {
        fpsList->pVtbl->Release(fpsList);
        fpsList = NULL;
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->pVtbl->StopPerformanceMetricsTracking(perfMonitoringServices);
    if (ADLX_FAILED(res))
    {
        printf("Failed to stop tracking performance metrics\n");
        return;
    }
}