//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file ShareMemory.cpp
/// \brief This document demonstrate how to use shared memory.

#include <Windows.h>
#include "GlobalDefs.h"

// Constructor
ShareMem::ShareMem ()
    : file_ (NULL), buffer_ (NULL), size_ (0)
{
}

// Destructor
ShareMem::~ShareMem ()
{
    if (file_)
    {
        CloseHandle (file_);
        file_ = NULL;
    }

    if (buffer_)
    {
        UnmapViewOfFile (buffer_);
        buffer_ = NULL;
    }
}

// Create shared memory
bool ShareMem::Create (ULONG filesize, PCWCHAR filename)
{
    DWORD errCode = 0;

    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;
    size_ = filesize;

    // After setting this permission, the general application does not have administrator privileges
    // In order to start to open mapping file Otherwise Access Denny
    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, (PACL)NULL, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = &sd;

    // Create a mapped file
    file_ = CreateFileMappingW (INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, filesize, filename);
    if (file_ == NULL)
    {
        XTrace (L"ADLX Call Service: ShareMem::Create: CreateFileMappingW, error: %d\n", GetLastError());
        return false;
    }

    // In the external function can be directly manipulate the variables to get the memory-mapped file.
    if (buffer_)
    {
        UnmapViewOfFile (buffer_);
        buffer_ = NULL;
    }

    buffer_ = MapViewOfFile (file_, FILE_MAP_ALL_ACCESS, 0, 0, filesize);
    if (buffer_ == NULL)
    {
        XTrace (L"ADLX Call Service: ShareMem::Create: MapViewOfFile, error: %d\n", GetLastError ());
        return false;
    }

    XTrace (L"ADLX Call Service: ShareMem::Create: OK\n");

    return true;
}

// Write data to shared memory
bool ShareMem::WriteBuffer (PVOID buffer, ULONG size)
{
    if (buffer && size > 0)
    {
        memcpy_s (buffer_, size, buffer, size);
        return true;
    }

    return false;
}

// Read data from shared memory
bool ShareMem::ReadBuffer (PVOID buffer, ULONG size)
{
    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;
    bool ret = false;
    InitializeSecurityDescriptor (&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl (&sd, TRUE, (PACL)NULL, FALSE);

    sa.nLength = sizeof (SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = &sd;

    if (file_)
    {
        if (buffer_)
        {
            memcpy_s (buffer, size, buffer_, size);
            ret = true;
        }
    }

    return ret;
}