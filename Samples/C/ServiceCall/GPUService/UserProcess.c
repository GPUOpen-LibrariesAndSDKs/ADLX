//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file UserProcess.c
/// \brief This document demonstrate how to create user process.

#include <Windows.h>
#include <TlHelp32.h>
#include "GlobalDefs.h"

// Get process id
static DWORD GetProcessIdOfWinLogon (DWORD id);

// Get token by name
static HANDLE GetTokenByName ();

// Invoke process
static BOOL InvokeProcess (LPCWSTR image, LPWSTR cmd);

// The thread to create user process
static DWORD WINAPI CreateUserProcess (LPVOID lpParam);

DWORD GetProcessIdOfWinLogon (DWORD id)
{
    HANDLE hSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
    {
        XTrace (L"ADLX Call Service: InvokeUserProcessGetProcessIdOfWinLogon: 'CreateToolhelp32Snapshot' failed.");
        return 0;
    }

    PROCESSENTRY32 ProcEntry = { 0 };
    ProcEntry.dwSize = sizeof (PROCESSENTRY32);

    if (!Process32First (hSnap, &ProcEntry))
    {
        CloseHandle (hSnap);
        XTrace (L"ADLX Call Service: InvokeUserProcessGetProcessIdOfWinLogon: 'Process32First' failed.");
        return 0;
    }

    DWORD processId = 0;
    for (;;)
    {
        if (strcmp (ProcEntry.szExeFile, "winlogon.exe") == 0)
        {
            DWORD logonSessionId = 0;
            if (!ProcessIdToSessionId (ProcEntry.th32ProcessID, &logonSessionId))
                continue;

            if (logonSessionId == id)
            {
                processId = ProcEntry.th32ProcessID;
                break;
            }
        }

        if (!Process32Next (hSnap, &ProcEntry))
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetProcessIdOfWinLogon: 'Process32Next' failed.");
            break;
        }
    }
    CloseHandle (hSnap);

    return processId;
}

HANDLE GetTokenByName ()
{
    typedef BOOL (WINAPI* LPWTSQUERYUSERTOKEN)(DWORD, PHANDLE);
    LPWTSQUERYUSERTOKEN fWTSQueryUserTokenPtr = NULL;

    HMODULE hLib = NULL;
    HANDLE hToken = NULL;

    do
    {
        DWORD sessionId = WTSGetActiveConsoleSessionId ();
        if (sessionId == 0xFFFFFFFF)
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName:WTSGetActiveConsoleSessionId: failed.");
            break;
        }

        if (fWTSQueryUserTokenPtr == NULL)
        {
            if (hLib == NULL)
                hLib = LoadLibrary ("WtsApi32.dll");

            if (hLib)
                fWTSQueryUserTokenPtr = (LPWTSQUERYUSERTOKEN)GetProcAddress (hLib, "WTSQueryUserToken");

            if (!fWTSQueryUserTokenPtr)
            {
                XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName: Get symbol 'WTSQueryUserToken' failed.");
                break;
            }
        }

        if (!fWTSQueryUserTokenPtr (sessionId, &hToken))
        {
            XTrace (L"ADLX Call Service: InvokeUserProcess::GetTokenByName: 'fWTSQueryUserTokenPtr' failed, error code: %d.", GetLastError ());
            break;
        }

        DWORD winLogonProcessId = GetProcessIdOfWinLogon (sessionId);
        HANDLE hWinlogon = OpenProcess (MAXIMUM_ALLOWED, FALSE, winLogonProcessId);
        if (hWinlogon == NULL)
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName: 'OpenProcess' failed.");
            break;
        }

        BOOL bResult = OpenProcessToken (hWinlogon, TOKEN_ALL_ACCESS, &hToken);
        CloseHandle (hWinlogon);

        if (!bResult)
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName: 'OpenProcessToken' failed.");
            break;
        }

        HANDLE hTokenDup = NULL;
        bResult = DuplicateTokenEx (hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hTokenDup);
        CloseHandle (hToken);
        hToken = NULL;

        if (!bResult)
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName: 'DuplicateTokenEx' failed.");
            break;
        }

        bResult = SetTokenInformation (hTokenDup, TokenSessionId, (void*)&sessionId, sizeof (DWORD));
        if (!bResult)
        {
            XTrace (L"ADLX Call Service: InvokeUserProcessGetTokenByName: 'SetTokenInformation' failed.");
            break;
        }

        TOKEN_PRIVILEGES TokenPriv = { 0 };
        LookupPrivilegeValue (NULL, SE_DEBUG_NAME, &TokenPriv.Privileges[0].Luid);

        TokenPriv.PrivilegeCount = 0;
        TokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges (hTokenDup, FALSE, &TokenPriv, sizeof (TokenPriv), NULL, NULL);

        hToken = hTokenDup;

    } while (0);

    if (hLib)
        FreeLibrary (hLib);

    return hToken;
}

BOOL InvokeProcess (LPCWSTR image, LPWSTR cmd)
{
    if (image == NULL || cmd == NULL)
    {
        XTrace (L"ADLX Call Service: InvokeUserProcessInvokeProcess: parameter(s) invalid.");
        return FALSE;
    }

    HANDLE hToken = GetTokenByName();
    if (hToken == NULL) // "SVCHOST.EXE"
    {
        XTrace (L"ADLX Call Service: InvokeUserProcessInvokeProcess: GetTokenByName failed.");
        return FALSE;
    }

    XTrace (L"ADLX Call Service: InvokeUserProcessInvokeProcess: 'GetTokenByName', hToken:%d.", hToken);
    XTrace (L"ADLX Call Service: InvokeUserProcessInvokeProcess: 'GetTokenByName', image:%s, cmd:%s", image, cmd);

    STARTUPINFOW si;
    ZeroMemory (&si, sizeof (STARTUPINFOW));
    si.cb = sizeof (STARTUPINFOW);
    si.lpDesktop = L"winsta0\\default";

    PROCESS_INFORMATION pi;
    BOOL ret = CreateProcessAsUserW (hToken, image, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    if (!ret)
    {
        XTrace (L"ADLX Call Service: InvokeUserProcessInvokeProcess: 'CreateProcessAsUserW' failed, error code:%d.", GetLastError());
        return FALSE;
    }

    return ret;
}

DWORD WINAPI CreateUserProcess (LPVOID lpParam)
{
    if (lpParam == NULL)
        return FALSE;

    wchar_t imagePath[MAX_RESULT_LEN] = { 0 };
    GetModuleFileNameW (NULL, imagePath, MAX_PATH);

    InvokeProcess (imagePath, (WCHAR*)lpParam);

    return TRUE;
}

BOOL GetUserProcessData (Messager* messager, ResponseData* responseData)
{
    if (messager == NULL)
    {
        XTrace (L"ADLX Call Service: GetUserProcessData: invalid messager");
        return FALSE;
    }

    if (responseData == NULL)
    {
        XTrace (L"ADLX Call Service: GetUserProcessData: NULL responseData");
        return FALSE;
    }

    WCHAR eventPath[MAX_PATH] = { 0 };
    WCHAR shmPath[MAX_PATH] = { 0 };

    swprintf_s (eventPath, MAX_PATH, ADXL_EVENT_NAME, messager->adlxEntityName);
    swprintf_s (shmPath, MAX_PATH, ADXL_SHAREMENORY_NAME, messager->adlxEntityName);

    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;

    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, (PACL)NULL, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = &sd;

    HANDLE finishEvent = CreateEventW (&sa, FALSE, FALSE, eventPath);

    XTrace (L"ADLX Call Service: Main: GetUserProcessData, evt: %s, shmpath: %s\n", eventPath, shmPath);

    if (ShmCreate (shmPath, SHARE_MEMORY_MAX_SIZE))
    {
        if (ShmWriteBuffer (shmPath, (PVOID)messager, sizeof (Messager)))
        {
            // Create user process to call ADLX function
            DWORD threadId = 0;
            CreateThread (NULL, 0, CreateUserProcess, (LPVOID)messager->adlxEntityName, 0, &threadId);
            // Wait user process to write result to shared memory
            if (WAIT_TIMEOUT == WaitForSingleObject (finishEvent, INFINITE))
            {
                return FALSE;
            }
            // Get template structure from shared memory
            if (ShmReadBuffer (shmPath, (PVOID)responseData, sizeof (ResponseData)))
            {
                XTrace (L"ADLX Call Service: Main: GetUserProcessData: Readback result: %s", responseData->executedResults);
                ShmDestory ();
                return TRUE;
            }
        }
    }
    return FALSE;
}