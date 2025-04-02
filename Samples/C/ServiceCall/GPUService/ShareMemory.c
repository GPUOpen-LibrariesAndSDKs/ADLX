//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file ShareMemory.c
/// \brief This document demonstrate how to use shared memory.

#include <Windows.h>
#include "GlobalDefs.h"

static HANDLE g_SharedFile = NULL;
static PVOID  g_SharedBuffer = NULL;

// Create shared memory
BOOL ShmCreate (WCHAR* shmFileName, ULONG sharedFilesize)
{
    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;

    // N.B: After setting this permission, the general application does not have administrator privileges
    // In order to start to open mapping g_SharedFile Otherwise Access Denny
    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, (PACL)NULL, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = &sd;

    HANDLE g_SharedFile = CreateFileMappingW (INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, sharedFilesize, shmFileName);
    if (g_SharedFile == NULL)
    {
        XTrace (L"ADLX Call Service: ShareMem::Create: CreateFileMappingW, error: %d\n", GetLastError());
        return FALSE;
    }

    LPVOID g_SharedBuffer = MapViewOfFile (g_SharedFile, FILE_MAP_ALL_ACCESS, 0, 0, sharedFilesize);
    if (g_SharedBuffer == NULL)
    {
        XTrace (L"ADLX Call Service: ShareMem::Create: MapViewOfFile, error: %d\n", GetLastError ());
        return FALSE;
    }

    XTrace (L"ADLX Call Service: ShareMem::Create: OK\n");

    return TRUE;
}

// Destory shared memory
VOID ShmDestory ()
{
    if (g_SharedBuffer)
    {
        UnmapViewOfFile (g_SharedBuffer);
        g_SharedBuffer = NULL;
    }

    if (g_SharedFile)
    {
        CloseHandle (g_SharedFile);
        g_SharedFile = NULL;
    }
}

// Write data to shared memory
BOOL ShmWriteBuffer (WCHAR* shmFileName, PVOID buffer, ULONG size)
{
    HANDLE shmFile = OpenFileMappingW (FILE_MAP_ALL_ACCESS, FALSE, shmFileName);
    if (shmFile)
    {
        LPVOID g_SharedBuffer = MapViewOfFile (shmFile, FILE_MAP_ALL_ACCESS, 0, 0, size);
        if (g_SharedBuffer)
        {
            memcpy_s (g_SharedBuffer, size, buffer, size);
            return TRUE;
        }
    }
    return FALSE;
}

// Read data from shared memory
BOOL ShmReadBuffer (WCHAR* shmFileName, PVOID buffer, ULONG size)
{
    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;

    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, (PACL)NULL, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = &sd;

    BOOL result = FALSE;
    HANDLE g_SharedFile = OpenFileMappingW (FILE_MAP_ALL_ACCESS, FALSE, shmFileName);
    if (g_SharedFile)
    {
        g_SharedBuffer = MapViewOfFile (g_SharedFile, FILE_MAP_ALL_ACCESS, 0, 0, size);
        if (g_SharedBuffer)
        {
            memcpy_s (buffer, size, g_SharedBuffer, size);
            result = TRUE;
        }
    }

    return result;
}