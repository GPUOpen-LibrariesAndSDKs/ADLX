//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainLog.c
/// \brief Demonstrates how to enable log and get log data when programming with ADLX.
#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"

// CallBack to handle ADLX log
ADLX_RESULT ADLX_STD_CALL WriteLog(IADLXLog* pThis, const wchar_t* msg)
{
    wprintf(L"%s", msg);
    return ADLX_OK;
}

// Application's log struct demostration, application can capture ADLX log here
typedef struct AppHandlLog
{
    ADLX_RESULT(ADLX_STD_CALL* WriteLog)
    (IADLXLog* pThis, const wchar_t* msg);
} AppHandlLog;

// Local file, ADLX log data is saved to file
void UseLocalFile()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    // Log destination, severity, logfile
    ADLX_LOG_DESTINATION mode = LOCALFILE;
    ADLX_LOG_SEVERITY severity = LDEBUG;
    wchar_t logfile[] = L"./ADLX.log";

    // Enable log
    ADLX_RESULT res = sys->pVtbl->EnableLog(sys, mode, severity, NULL, logfile);
    printf("Enabled log result: %d (0 means success)\n", res);
}

// Configure ADLX log to send errors, warnings and debug information messages to the DebugView
void UseDebugView()
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    // Log destination, severity
    ADLX_LOG_DESTINATION mode = DBGVIEW;
    ADLX_LOG_SEVERITY severity = LDEBUG;

    // Enable log
    ADLX_RESULT res = sys->pVtbl->EnableLog(sys, mode, severity, NULL, NULL);
    printf("Enabled log result : %d (0 means Success)\n", res);
}

// Application handle log, application's callback will handle the ADLX log
void UseAppHandlLog(AppHandlLog** appHandlLog)
{
    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    // Log destination, severity
    ADLX_LOG_DESTINATION mode = APPLICATION;
    ADLX_LOG_SEVERITY severity = LDEBUG;

    // Enable log
    ADLX_RESULT res = sys->pVtbl->EnableLog(sys, mode, severity, (IADLXLog*)appHandlLog, NULL);
    printf("Enabled log result : %d (0 means Success)\n", res);
}

// Main menu
void MainMenu()
{
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to enable log with local file, file [./ADLX.log] will be created.\n");
    printf("\t->Press 2 to enable log with DebugView\n");
    printf("\t->Press 3 to enable log with app handle\n");
}

// Menu action control
void MenuControl(AppHandlLog** appHandlLog)
{
    int num = 0;
    num = getchar();
    switch (num)
    {
    // Local file
    case '1':
        UseLocalFile();
        break;

    // DebugView
    case '2':
        UseDebugView();
        break;

    // App handle
    case '3':
        UseAppHandlLog(appHandlLog);
        break;

    default:
        printf("Invalid input\n");
        break;
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

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // App create object to handle ADLX log
        AppHandlLog* appHandlLog = (AppHandlLog*)malloc(sizeof(AppHandlLog));
        appHandlLog->WriteLog = &WriteLog;

        // Menu
        MainMenu();
        MenuControl(&appHandlLog);

        // Try get log by using some interfaces
        // Get display service and display numbers
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_uint displayNum;
            displayService->pVtbl->GetNumberOfDisplays(displayService, &displayNum);
        }
        if (NULL != displayService)
        {
            displayService->pVtbl->Release(displayService);
            displayService = NULL;
        }

        // Destroy ADLX
        res = ADLXHelper_Terminate();
        printf("Destroy ADLX res: %d\n", res);

        // appHandlLog may be used throughout the life cycle of ADLX,
        // So destroy appHandlLog after destroying ADLX
        free(appHandlLog);
        appHandlLog = NULL;
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Pause for user see the print out
    system("pause");

    return 0;
}