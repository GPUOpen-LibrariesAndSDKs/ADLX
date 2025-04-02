//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUServiceDirect.c
/// \brief This document demonstrate how to use windows service call to get GPU information.

#pragma warning(suppress: 6248)

#include <Windows.h>
#include <TlHelp32.h>
#include <wchar.h>
#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISystem.h"
#include <stdio.h>

#define MAX_DEBUG_STR_LEN 1024

void XTrace (wchar_t* lpszFormat, ...)
{
    va_list args;
    va_start (args, lpszFormat);
    int nBuf;
    WCHAR szBuffer[MAX_DEBUG_STR_LEN];
    nBuf = _vsnwprintf_s (szBuffer, MAX_DEBUG_STR_LEN, _TRUNCATE, lpszFormat, args);
    OutputDebugStringW (szBuffer);
    va_end (args);
}

// Service name
#define ADLX_SERVICE_NAME  L"ADLX GPU Service"

// Global variables for service routine
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
SERVICE_STATUS        g_ServiceStatus = { 0 };
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

// Service routine
VOID WINAPI  ServiceMain (DWORD argc, LPTSTR* argv);
VOID WINAPI  ServiceCtrlHandler (DWORD);
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam);

// Install/unistall this service
// N.B: Need admin permission
// User can also install/unistall this service by windows command line
// Usage: SC CREATE "ADLX GPU Service" "GPUServiceDirect.exe -install"
//        SC DELETE "ADLX GPU Service" "GPUServiceDirect.exe -remove"
void InstallService ();
void RemoveService ();

// Usage
void Usage ()
{
    printf ("\n");
    printf ("\tThis exe is a service executable, you can install/unistall it with:\n");
    printf ("\t    SC CREATE 'ADLX GPU Service' 'GPUService.exe'\n");
    printf ("\t    SC DELETE 'ADLX GPU Service'\n");
    printf ("\n");
    printf ("\tOr use the executable itself to install/uninstall:\n");
    printf ("\t    GPUService.exe -install or GPUService.exe /install\n");
    printf ("\t    GPUService.exe -remove or GPUService.exe /remove\n");
    printf ("\n");
    printf ("\t    Use GPUService.exe -help, GPUService.exe /help to show this usage, or GPUService.exe ?\n");
    printf ("\n");
}

int wmain (int argc, wchar_t* argv[])
{
    XTrace (L"ADLX Call Service: Main: Entry");
    XTrace (L"ADLX Call Service: Main: Args:%s", GetCommandLineW ());

    if ((argc > 1))
    {
        if (((*argv[1] == '-') || (*argv[1] == '/')))
        {
            if (_wcsicmp (L"install", argv[1] + 1) == 0)
            {
                InstallService ();
                return 0;
            }
            else if (_wcsicmp (L"remove", argv[1] + 1) == 0)
            {
                RemoveService ();
                return 0;
            }
            else if (_wcsicmp (L"help", argv[1] + 1) == 0)
            {
                Usage ();
                return 0;
            }
        }
        else if (_wcsicmp (L"?", argv[1]) == 0)
        {
            Usage ();
            return 0;
        }
    }

    SERVICE_TABLE_ENTRYW ServiceTable[] =
    {
        { ADLX_SERVICE_NAME, (LPSERVICE_MAIN_FUNCTIONW)ServiceMain },
        { NULL, NULL }
    };

    if (StartServiceCtrlDispatcherW (ServiceTable) == FALSE)
    {
        XTrace (L"ADLX Call Service: Main: StartServiceCtrlDispatcher returned error.");
        return GetLastError ();
    }

    XTrace (L"ADLX Call Service: Main: Exit");

    return 0;
}

VOID WINAPI ServiceMain (DWORD argc, LPTSTR* argv)
{
    DWORD Status = E_FAIL;

    XTrace (L"ADLX Call Service: ServiceMain: Entry");

    g_StatusHandle = RegisterServiceCtrlHandlerW (ADLX_SERVICE_NAME, ServiceCtrlHandler);
    if (g_StatusHandle == NULL)
    {
        XTrace (L"ADLX Call Service: ServiceMain: RegisterServiceCtrlHandler returned error");
        goto EXIT;
    }

    // Tell the service controller we are starting
    ZeroMemory (&g_ServiceStatus, sizeof (g_ServiceStatus));
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        XTrace (L"ADLX Call Service: ServiceMain: SetServiceStatus returned error");
    }

    /*
     * Perform tasks neccesary to start the service here
     */
    XTrace (L"ADLX Call Service: ServiceMain: Performing Service Start Operations");

    // Create stop event to wait on later.
    g_ServiceStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL)
    {
        XTrace (L"ADLX Call Service: ServiceMain: CreateEvent(g_ServiceStopEvent) returned error");

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError ();
        g_ServiceStatus.dwCheckPoint = 1;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
        {
            XTrace (L"ADLX Call Service: ServiceMain: SetServiceStatus returned error");
        }
        goto EXIT;
    }

    // Tell the service controller we are started
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        XTrace (L"ADLX Call Service: ServiceMain: SetServiceStatus returned error");
    }

    // Start the thread that will perform the main task of the service
    HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);

    XTrace (L"ADLX Call Service: ServiceMain: Waiting for Worker Thread to complete");

    if (hThread)
    {
        // Wait until our worker thread exits effectively signaling that the service needs to stop
        WaitForSingleObject(hThread, INFINITE);

        XTrace(L"ADLX Call Service: ServiceMain: Worker Thread Stop Event signaled");
    }
    /*
     * Perform any cleanup tasks
     */
    XTrace (L"ADLX Call Service: ServiceMain: Performing Cleanup Operations");

    CloseHandle (g_ServiceStopEvent);

    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
        XTrace (L"ADLX Call Service: ServiceMain: SetServiceStatus returned error");
    }

EXIT:
    XTrace (L"ADLX Call Service: ServiceMain: Exit");

    return;
}

VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    XTrace (L"ADLX Call Service: ServiceCtrlHandler: Entry");

    switch (CtrlCode)
    {
    case SERVICE_CONTROL_STOP:

        XTrace (L"ADLX Call Service: ServiceCtrlHandler: SERVICE_CONTROL_STOP Request");

        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
            break;

        /*
         * Perform tasks neccesary to stop the service here
         */

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
        {
            XTrace (L"ADLX Call Service: ServiceCtrlHandler: SetServiceStatus returned error");
        }

        // This will signal the worker thread to shut down
        SetEvent (g_ServiceStopEvent);
        break;

    default:
        break;
    }

    XTrace (L"ADLX Call Service: ServiceCtrlHandler: Exit");
}

DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    XTrace (L"ADLX Call Service: ServiceWorkerThread: Entry");

    if (ADLX_FAILED(ADLXHelper_Initialize()))
    {
        XTrace(L"ADLX Call Service: GetAdlxGpuInfo: ADLX helper initalize failed.");
        return FALSE;
    }

    BOOL ret = FALSE;

    IADLXSystem* sys = ADLXHelper_GetSystemServices();
    IADLXGPUList* gpus = NULL;
    ADLX_RESULT res = sys->pVtbl->GetGPUs(sys, &gpus);
    if (ADLX_SUCCEEDED(res) && !gpus->pVtbl->Empty(gpus))
    {
        IADLXGPU* gpu = NULL;
        res = gpus->pVtbl->At_GPUList(gpus, 0, &gpu);
        if (ADLX_SUCCEEDED(res) && gpu)
        {
            const char* vendorId = NULL;
            res = gpu->pVtbl->VendorId(gpu, &vendorId);
            if (ADLX_SUCCEEDED(res))
            {
                XTrace(L"VenderId=%hs ", vendorId);
            }

            const char* gpuName = NULL;
            res = gpu->pVtbl->Name(gpu, &gpuName);
            if (ADLX_SUCCEEDED(res))
            {
                XTrace(L"GpuName=%hs", gpuName);
            }

            gpu->pVtbl->Release(gpu);
            ret = TRUE;
        }

        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
        }
    }

    Sleep(3000);
    ADLXHelper_Terminate();

    XTrace (L"ADLX Call Service: ServiceWorkerThread: Exit");

    return ERROR_SUCCESS;
}

void InstallService ()
{
    WCHAR path[512] = { 0 };
    if (GetModuleFileNameW (NULL, path, 512) == 0)
    {
        XTrace (L"ADLX Call Service: InstallService: Cannot get g_SharedFile path.");
        return;
    }

    SC_HANDLE serviceManager = OpenSCManager (NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
    if (serviceManager)
    {
        SC_HANDLE serviceHandle = CreateServiceW (
            serviceManager, ADLX_SERVICE_NAME, ADLX_SERVICE_NAME, SERVICE_QUERY_STATUS,
            SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
            SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, path,
            NULL, NULL, L"", NULL, NULL);

        if (serviceHandle)
        {
            CloseServiceHandle (serviceHandle);
        }
        else
        {
            XTrace (L"ADLX Call Service: InstallService: Cannot create service.");
        }

        CloseServiceHandle (serviceManager);
    }
    else
    {
        XTrace (L"ADLX Call Service: InstallService: Cannot open service.");
    }
}

void RemoveService ()
{
    SC_HANDLE serviceManager = OpenSCManager (NULL, NULL, SC_MANAGER_CONNECT);
    if (!serviceManager)
    {
        XTrace (L"ADLX Call Service: RemoveService: Cannot open service manager.");
        return;
    }

    SC_HANDLE serviceHandle = OpenServiceW (serviceManager, ADLX_SERVICE_NAME, DELETE | SERVICE_STOP);
    if (!serviceHandle)
    {
        CloseServiceHandle (serviceManager);
        XTrace (L"ADLX Call Service: RemoveService: Cannot open service.");
        return;
    }

    if (!DeleteService (serviceHandle))
    {
        CloseServiceHandle (serviceHandle);
        CloseServiceHandle (serviceManager);
        XTrace (L"ADLX Call Service: RemoveService: Delete service failed.");
        return;
    }

    XTrace (L"ADLX Call Service: RemoveService: Deleted service.");

    SERVICE_STATUS serviceStatus = { 0 };
    ControlService (serviceHandle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&serviceStatus);

    CloseServiceHandle (serviceHandle);
    CloseServiceHandle (serviceManager);
}
