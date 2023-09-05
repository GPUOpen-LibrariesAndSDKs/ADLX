//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainLog.cpp
/// \brief Demonstartes how to enable log and get log data when programming in ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/ILog.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Demonstrates how applications capture ADLX log
// The log class may get used throughout the liftime of ADLX.
// Global variables are used as they hold their value throughout the lifetime of ADLX.
class AppHandlLog : public IADLXLog
{
  public:
    ADLX_RESULT ADLX_STD_CALL WriteLog(const wchar_t* msg)
    {
        wprintf(L"%s", msg);
        return ADLX_OK;
    }
};

// Application creates object to handle ADLX log
static AppHandlLog g_appHandlLog;

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Local file
void UseLocalFile();

// Output window of the application debugger
void UseWindowDebugger();

// Application handle log
void UseAppHandlLog();

// Main menu
void MainMenu();

// Menu action control
void MenuControl();

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Menu
        MainMenu();
        MenuControl();

        // Call ADLX methods to generate log entries
        // Get display service and the number of displays
        IADLXDisplayServicesPtr displayService;
        res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_uint displayNum;
            displayService->GetNumberOfDisplays(&displayNum);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");
    return 0;
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Local file, ADLX log data will be saved to file
void UseLocalFile()
{
    // Log destination, severity, logfile
    ADLX_LOG_DESTINATION mode = LOCALFILE;
    ADLX_LOG_SEVERITY severity = LDEBUG;
    wchar_t logfile[] = L"./ADLX.log";

    // Enable log
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->EnableLog(mode, severity, nullptr, logfile);
    std::cout << "Enabled log res: " << res << "(0 means success)" << std::endl;
}

// Configure ADLX log to send errors, warnings and debug information messages to the DebugView.
void UseDebugView()
{
    // Log destination, severity
    ADLX_LOG_DESTINATION mode = DBGVIEW;
    ADLX_LOG_SEVERITY severity = LDEBUG;

    // Enable log
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->EnableLog(mode, severity, nullptr, nullptr);
    std::cout << "Enabled log result : " << res << "(0 means success)" << std::endl;
}

// Application handle log, app's callback will handle the ADLX log
void UseAppHandlLog()
{
    // Log destination, severity
    ADLX_LOG_DESTINATION mode = APPLICATION;
    ADLX_LOG_SEVERITY severity = LDEBUG;

    // Enable log
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->EnableLog(mode, severity, &g_appHandlLog, nullptr);
    std::cout << "Enabled log result: " << res << "(0 means success)" << std::endl;
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;
    std::cout << "\t->Press 1 to enable log with local file, file [./ADLX.log] will be created." << std::endl;
    std::cout << "\t->Press 2 to enable log with DebugView" << std::endl;
    std::cout << "\t->Press 3 to enable log with app handle" << std::endl;
}

// Menu action control
void MenuControl()
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

    // Application handle
    case '3':
        UseAppHandlLog();
        break;

    default:
        std::cout << "Invalid input" << std::endl;
        break;
    }
}