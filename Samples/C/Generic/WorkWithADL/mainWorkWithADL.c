//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainWorkWithADL.c
/// \brief Demonstartes how to work with ADLX along ADL when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"

// ADL dll name
#ifndef _WIN64
#define ADL_DLL_Name L"atiadlxy.dll"
#else // WIN32
#define ADL_DLL_Name L"atiadlxx.dll"
#endif

typedef void*(__stdcall* ADL_MALLOC_CALL)(int);
typedef int (*ADL_MAIN_CONTROL_CREATE)(ADL_MALLOC_CALL, int iEnumConnectedAdapter, void** context, int);
typedef int (*ADL_MAIN_CONTROL_DESTROY)(void*);

// Memory allocation callback for ADL
// iSize_ - number of bytes to be allocated
static void* __stdcall ADL_Client_Main_Memory_Alloc(int iSize_)
{
    void* lpBuffer = malloc(iSize_);
    return lpBuffer;
}

// Callback ADL for memory release
// lpBuffer_ - the memory buffer to dealocate and make NULL
static void __stdcall ADL_Main_Memory_Free_Client(void** lpBuffer_)
{
    if (NULL != lpBuffer_ && NULL != *lpBuffer_)
    {
        free(*lpBuffer_);
        *lpBuffer_ = NULL;
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    //Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("Pause");
    return retCode;
}

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Define ADL context and ADL dll handle
    void* adlContext = NULL;
    HINSTANCE adlDll = NULL;

    // Initialize ADL
    adlDll = LoadLibraryW(ADL_DLL_Name);
    if (NULL == adlDll)
        return WaitAndExit("ADL initialization failed", 0);
    ADL_MAIN_CONTROL_CREATE adlCreate = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(adlDll, "ADL2_Main_ControlX2_Create");
    if (adlCreate)
        adlCreate(ADL_Client_Main_Memory_Alloc, 1, &adlContext, 1);
    printf("ADL initialized successfully\n");

    // Initialize ADLX
    res = ADLXHelper_InitializeWithCallerAdl(adlContext, ADL_Main_Memory_Free_Client);
    if (ADLX_SUCCEEDED(res))
    {
        printf("ADLX initialized successfully\n");
    }
    else
    {
        printf("ADLX initialization failed\n");
    }

    const char* adlxVersion = ADLXHelper_QueryVersion();
    printf("ADLX version: %s\n", adlxVersion);
    adlx_uint64 adlxFullVersion = ADLXHelper_QueryFullVersion();
    printf("ADLX full version: %lld\n", adlxFullVersion);

    // Demonstrates mapping between ADL and ADLX data
    IADLXSystem* systemService = ADLXHelper_GetSystemServices();
    IADLMapping* adlMapping = ADLXHelper_GetAdlMapping();

    if (systemService && adlMapping)
    {
        adlx_uint totalRAM = 0;
        systemService->pVtbl->TotalSystemRAM(systemService, &totalRAM);
        printf("Total System RAM: %d MB\n", totalRAM);
        // Map ADLX to ADL
        IADLXGPUList* gpus = NULL;
        systemService->pVtbl->GetGPUs(systemService, &gpus);
        IADLXGPU* gpu = NULL;
        adlx_uint it = 0;
        gpus->pVtbl->At_GPUList(gpus, it, &gpu);
        const char* name = NULL;
        gpu->pVtbl->Name(gpu, &name);
        adlx_int adapterIndex;
        adlMapping->pVtbl->AdlAdapterIndexFromADLXGPU(adlMapping, gpu, &adapterIndex);
        printf("ADL AdapterIndex from ADLXGPU: %s, adapterIndex is : %d\n", name, adapterIndex);
        adlx_int bus = 0;
        adlx_int device = 0;
        adlx_int function = 0;
        res = adlMapping->pVtbl->BdfFromADLXGPU (adlMapping, gpu, &bus, &device, &function);
        printf("Get BDF from ADLXGPU bus: %d, device: %d, function: %d\n", bus, device, function);

        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }

        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }

        // Map ADL to ADLX, get adapterIndex via ADL
        IADLXGPU* gpuInfo = NULL;
        adlMapping->pVtbl->GetADLXGPUFromAdlAdapterIndex(adlMapping, adapterIndex, &gpuInfo);
        gpuInfo->pVtbl->Name(gpuInfo, &name);
        printf(" ADLXGPU from adapterIndex: %d, the GPU name is : %s\n", adapterIndex, name);

        if (gpuInfo != NULL)
        {
            gpuInfo->pVtbl->Release(gpuInfo);
            gpuInfo = NULL;
        }
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX result: %d\n", res);

    // Destroy ADL
    ADL_MAIN_CONTROL_DESTROY adlDestroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(adlDll, "ADL2_Main_Control_Destroy");
    if (NULL != adlDestroy)
        adlDestroy(adlContext);
    FreeLibrary(adlDll);
    adlDll = NULL;
    adlContext = NULL;
    printf("Destroy ADL\n");

    // Pause to see the print out
    system("Pause");
    return 0;
}