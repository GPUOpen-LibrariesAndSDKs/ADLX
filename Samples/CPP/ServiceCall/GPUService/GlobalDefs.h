#ifndef _GLOBAL_DEFS_H
#define _GLOBAL_DEFS_H
#pragma once

#include <stdio.h>

#define ADLX_FUNCTION_NAME       L"GPUInfo"
#define ADXL_EVENT_NAME          L"Global\\EventADLX_%s"
#define ADXL_SHAREMENORY_NAME    L"Global\\ShareMemoryADLX_%s"
#define SHARE_MEMORY_MAX_SIZE    (32 * 4 * 1024)

#define MAX_RESULT_LEN 512

#define MAX_DEBUG_STR_LEN 1024

void XTrace (wchar_t* lpszFormat, ...);

class ShareMem
{
public:
    ShareMem ();
    ~ShareMem ();

    bool Create (ULONG filesize, PCWCHAR filename);

    bool WriteBuffer (PVOID buffer, ULONG size);
    bool ReadBuffer (PVOID buffer, ULONG size);

private:
    HANDLE file_;
    PVOID buffer_;
    ULONG size_;
};

typedef BOOL (*AdlxExecutor) (WCHAR* resultBuffer);

struct Messager
{
    WCHAR* adlxEntityName;
    AdlxExecutor exector;
};

struct ResponseData
{
    int size;
    WCHAR executedResults[MAX_RESULT_LEN];
};

#endif //_GLOBAL_DEFS_H