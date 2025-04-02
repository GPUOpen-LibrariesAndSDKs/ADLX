//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainWorkWithADL.cpp
/// \brief Demontrates how to initialize ADLX with ADL and then use the mapping interface to map between ADL and ADLX code.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include <iostream>

// ADL dll name
#ifndef _WIN64
#define ADL_DLL_Name L"atiadlxy.dll"
#else // WIN32
#define ADL_DLL_Name L"atiadlxx.dll"
#endif

typedef void*(__stdcall* ADL_MALLOC_CALL)(int);
typedef int (*ADL_MAIN_CONTROL_CREATE)(ADL_MALLOC_CALL, int iEnumConnectedAdapter, void** context, int);
typedef int (*ADL_MAIN_CONTROL_DESTROY)(void*);

// Callback ADL for memory allocation
// iSize_ - Number of bytes to be allocated
static void* __stdcall ADL_Client_Main_Memory_Alloc(int iSize_)
{
    void* lpBuffer = malloc(iSize_);
    return lpBuffer;
}

// Callback ADL for memory release
// lpBuffer_ - The memory buffer to dealocate and to make NULL.
static void __stdcall ADL_Main_Memory_Free_Client(void** lpBuffer_)
{
    if (nullptr != lpBuffer_ && nullptr != *lpBuffer_)
    {
        free(*lpBuffer_);
        *lpBuffer_ = nullptr;
    }
}

// Use ADLX namespace
using namespace adlx;

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("Pause");
    return retCode;
}

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Create ADLXHelper instance
    ADLXHelper ADLXHelp;

    // Define ADL context and ADL dll handl
    void* adlContext = nullptr;
    HINSTANCE adlDll = nullptr;

    // Initialize ADL
    adlDll = LoadLibraryW(ADL_DLL_Name);
    if (nullptr == adlDll)
        return WaitAndExit("ADL initialization failed", 0);
    ADL_MAIN_CONTROL_CREATE adlCreate = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(adlDll, "ADL2_Main_ControlX2_Create");
    if (adlCreate)
        adlCreate(ADL_Client_Main_Memory_Alloc, 1, &adlContext, 1);
    std::cout << "ADL initialized successfully" << std::endl;

    // Initialize ADLX
    res = ADLXHelp.InitializeWithCallerAdl(adlContext, ADL_Main_Memory_Free_Client);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "ADLX initialized successfully" << std::endl;
    }
    else
    {
        std::cout << "ADLX initialization failed" << std::endl;
    }

    const char* adlxVersion = ADLXHelp.QueryVersion();
    std::cout << "ADLX version: " << adlxVersion << std::endl;
    adlx_uint64 adlxfullVersion = ADLXHelp.QueryFullVersion();
    std::cout << "ADLX full version: " << adlxfullVersion << std::endl;

    // Demonstrates mapping between ADL and ADLX data
    IADLXSystem* systemService = ADLXHelp.GetSystemServices();
    IADLMapping* adlMapping = ADLXHelp.GetAdlMapping();

    if (systemService && adlMapping)
    {
        adlx_uint totalRAM = 0;
        systemService->TotalSystemRAM(&totalRAM);
        std::cout << "Total System RAM: " << totalRAM << " MB" << std::endl;

        // Map ADLX to ADL
        IADLXGPUListPtr gpus;
        systemService->GetGPUs(&gpus);
        IADLXGPUPtr gpu;
        adlx_uint it = 0;
        gpus->At(it, &gpu);
        const char* name = nullptr;
        gpu->Name(&name);
        adlx_int adapterIndex;
        adlMapping->AdlAdapterIndexFromADLXGPU(gpu, &adapterIndex);
        std::cout << "ADL get adapterIndex from ADLXGPU named: " << name << ", adapterIndex is : " << adapterIndex << std::endl;

        // Map ADL to ADLX, to get adapterIndex via ADL
        IADLXGPUPtr gpuInfo;
        adlMapping->GetADLXGPUFromAdlAdapterIndex(adapterIndex, &gpuInfo);
        gpuInfo->Name(&name);
        std::cout << "ADLX get ADLXGPU from adapterIndex: " << adapterIndex << ", the gpu name is : " << name << std::endl;

        adlx_int bus = 0;
        adlx_int device = 0;
        adlx_int function = 0;
        res = adlMapping->BdfFromADLXGPU (gpu, &bus, &device, &function);
        std::cout << "Get BDF from ADLXGPU bus: " << bus << ", device: " << device << ", function: " << function << std::endl;
    }

    // Destroy ADLX
    res = ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Destroy ADL
    ADL_MAIN_CONTROL_DESTROY adlDestroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(adlDll, "ADL2_Main_Control_Destroy");
    if (nullptr != adlDestroy)
        adlDestroy(adlContext);
    FreeLibrary(adlDll);
    adlDll = nullptr;
    adlContext = nullptr;
    std::cout << "Destroy ADL" << std::endl;

    // Pause to see the print out
    system("pause");
    return 0;
}