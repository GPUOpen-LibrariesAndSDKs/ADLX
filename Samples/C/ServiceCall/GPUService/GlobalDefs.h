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

BOOL ShmCreate (WCHAR* shmFileName, ULONG sharedFilesize);
VOID ShmDestory ();
BOOL ShmWriteBuffer (WCHAR* shmFileName, PVOID sharedBuffer, ULONG size);
BOOL ShmReadBuffer (WCHAR* shmFileName, PVOID sharedBuffer, ULONG size);

typedef BOOL (*AdlxExecutor) (WCHAR* resultBuffer);

typedef struct _Messager
{
    WCHAR* adlxEntityName;
    AdlxExecutor exector;
} Messager;

typedef struct _ResponseData
{
    int size;
    WCHAR executedResults[MAX_RESULT_LEN];
} ResponseData;

#endif //_GLOBAL_DEFS_H