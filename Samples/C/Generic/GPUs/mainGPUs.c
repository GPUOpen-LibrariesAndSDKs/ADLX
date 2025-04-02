//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUs.c
/// \brief Demonstrates how to enumerate GPUs, get GPU information, receive notifications when GPUs are enabled and disabled, and maintain GPU change event when programming with ADLX.
#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISystem2.h"
#include <stdio.h>

// Callback for GPU change event
adlx_bool ADLX_STD_CALL OnGPUListChanged(IADLXGPUsEventListener* pThis, IADLXGPUList* pNewGPUs)
{
    printf("GPU list change event received\n");
    if (pNewGPUs == NULL)
    {
        printf("GPU list does not exist\n");
        return false;
    }

    printf("GPU list size: %d\n", pNewGPUs->pVtbl->Size(pNewGPUs));

    return true;
}

// Display GPU information
void ShowGPUInfo(IADLXGPU* gpu);

// Show GPU hybrid graphic type
void ShowHybridGraphicType();

// Add event lister for GPU change
void AddGPUEventListener();

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPU* gpu);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

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

        // Get GPU list
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPU* gpu = NULL;
            res = gpus->pVtbl->At_GPUList(gpus, 0, &gpu);
            if (ADLX_SUCCEEDED(res))
            {
                // Display main menu options
                MainMenu();
                // Get and parse the selection
                MenuControl(gpu);
            }

            if (gpus != NULL)
            {
                gpus->pVtbl->Release(gpus);
            }
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Display GPU information
void ShowGPUInfo(IADLXGPU* gpu)
{
    if (gpu != NULL)
    {
        printf("\n==== GPU info ====\n");
        // Show GPU info
        const char* vendorId = NULL;
        ADLX_RESULT ret = gpu->pVtbl->VendorId(gpu, &vendorId);
        printf("VendorId: %s, return code is: %d(0 means success)\n", vendorId, ret);

        ADLX_ASIC_FAMILY_TYPE asicFamilyType = ASIC_UNDEFINED;
        ret = gpu->pVtbl->ASICFamilyType(gpu, &asicFamilyType);
        printf("ASICFamilyType: %d, return code is: %d(0 means success)\n", asicFamilyType, ret);

        ADLX_GPU_TYPE gpuType = GPUTYPE_UNDEFINED;
        ret = gpu->pVtbl->Type(gpu, &gpuType);
        printf("Type: %d, return code is: %d(0 means success)\n", gpuType, ret);

        adlx_bool isExternal = false;
        ret = gpu->pVtbl->IsExternal(gpu, &isExternal);
        printf("IsExternal: %d, return code is: %d(0 means success)\n", isExternal, ret);

        const char* gpuName = NULL;
        ret = gpu->pVtbl->Name(gpu, &gpuName);
        printf("Name: %s, return code is: %d(0 means success)\n", gpuName, ret);

        const char* driverPath = NULL;
        ret = gpu->pVtbl->DriverPath(gpu, &driverPath);
        printf("DriverPath: %s, return code is: %d(0 means success)\n", driverPath, ret);

        const char* pnpString = NULL;
        ret = gpu->pVtbl->PNPString(gpu, &pnpString);
        printf("PNPString: %s, return code is: %d(0 means success)\n", pnpString, ret);

        adlx_bool hasDesktops = false;
        ret = gpu->pVtbl->HasDesktops(gpu, &hasDesktops);
        printf("HasDesktops: %d, return code is: %d(0 means success)\n", hasDesktops, ret);

        adlx_uint totalVRAM = 0;
        ret = gpu->pVtbl->TotalVRAM(gpu, &totalVRAM);
        printf("TotalVRAM: %d MB, return code is: %d(0 means success)\n", totalVRAM, ret);

        adlx_int id;
        ret = gpu->pVtbl->UniqueId(gpu, &id);
        printf("UniqueId: %d, return code is: %d(0 means success)\n", id, ret);

        IADLXGPU1* gpu1 = NULL;
        ret = gpu->pVtbl->QueryInterface(gpu, IID_IADLXGPU1(), &gpu1);
        if (ADLX_SUCCEEDED(ret))
        {
            const char* productName = NULL;
            ret = gpu1->pVtbl->ProductName(gpu1, &productName);
            printf("ProductName: %s\n", productName);

            ADLX_MGPU_MODE mode = MGPU_NONE;
            ret = gpu1->pVtbl->MultiGPUMode(gpu1, &mode);
            printf("Multi-GPU Mode: ");
            if (mode == MGPU_PRIMARY)
                printf("GPU is the primary GPU\n");
            else if (mode == MGPU_SECONDARY)
                printf("GPU is the secondary GPU\n");
            else
                printf("GPU is not in Multi-GPU\n");

            ADLX_PCI_BUS_TYPE busType = UNDEFINED;
            ret = gpu1->pVtbl->PCIBusType(gpu1, &busType);
            printf("PCIBusType: %d\n", busType);

            adlx_uint laneWidth = 0;
            ret = gpu1->pVtbl->PCIBusLaneWidth(gpu1, &laneWidth);
            printf("PCIBusLaneWidth: %d\n", laneWidth);

            gpu1->pVtbl->Release(gpu1);
            gpu1 = NULL;
        }

        IADLXGPU2* gpu2 = NULL;
        ret = gpu->pVtbl->QueryInterface(gpu, IID_IADLXGPU2(), &gpu2);
        if (ADLX_SUCCEEDED(ret))
        {
            const char* driverInfo = NULL;
            ret = gpu2->pVtbl->AMDSoftwareEdition(gpu2, &driverInfo);
            printf("AMD software edition: %s\n", driverInfo);
            ret = gpu2->pVtbl->AMDSoftwareVersion(gpu2, &driverInfo);
            printf("AMD software version: %s\n", driverInfo);
            ret = gpu2->pVtbl->DriverVersion(gpu2, &driverInfo);
            printf("driver version: %s\n", driverInfo);
            ret = gpu2->pVtbl->AMDWindowsDriverVersion(gpu2, &driverInfo);
            printf("AMD Windows driver version: %s\n", driverInfo);
            adlx_uint year, month, day;
            ret = gpu2->pVtbl->AMDSoftwareReleaseDate(gpu2, &year, &month, &day);
            printf("AMD software release date: %d-%d-%d\n", year, month, day);

            ADLX_LUID luid;
            luid.lowPart = 0;
            luid.highPart = 0;
            ret = gpu2->pVtbl->LUID(gpu2, &luid);
            printf("LUID: lowPart: %lu , highPart: %ld\n", luid.lowPart, luid.highPart);

            gpu2->pVtbl->Release(gpu2);
            gpu2 = NULL;
        }

        gpu->pVtbl->Release(gpu);
        gpu = NULL;
    }
}

// Display GPU hybrid graphic type
void ShowHybridGraphicType()
{
    ADLX_HG_TYPE hgType = NONE;

    IADLXSystem* sys = ADLXHelper_GetSystemServices();
    ADLX_RESULT res = sys->pVtbl->GetHybridGraphicsType(sys, &hgType);
    if (ADLX_SUCCEEDED(res))
    {
        switch (hgType)
        {
        case NONE:
            printf("The GPU hybrid type is: NONE\n");
            break;
        case AMD:
            printf("The GPU hybrid type is: AMD\n");
            break;
        case OTHER:
            printf("The GPU hybrid type is: OTHER\n");
            break;
        }
    }
}

// Add GPU change event listener
void AddGPUEventListener()
{
    IADLXGPUsEventListenerVtbl GPUsEventListenerVtbl = {&OnGPUListChanged};
    IADLXGPUsEventListener gpuListener = {&GPUsEventListenerVtbl};

    IADLXGPUsChangedHandling* gpusChangedHandling = NULL;
    IADLXSystem* sys = ADLXHelper_GetSystemServices();
    ADLX_RESULT res = sys->pVtbl->GetGPUsChangedHandling(sys, &gpusChangedHandling);
    if (ADLX_SUCCEEDED(res) && gpusChangedHandling)
    {
        res = gpusChangedHandling->pVtbl->AddGPUsListEventListener(gpusChangedHandling, &gpuListener);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Addition of GPU event listener successful\n");
        }

        // Enable or disable a GPU device using Windows Device Manager
        Sleep(15 * 1000);

        res = gpusChangedHandling->pVtbl->RemoveGPUsListEventListener(gpusChangedHandling, &gpuListener);
        if (ADLX_SUCCEEDED(res))
        {
            printf("Removal of GPU event listener successful\n");
        }

        gpusChangedHandling->pVtbl->Release(gpusChangedHandling);
    }
}

// Main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to display GPU information\n");

    printf("\t->Press 2 to add GPU event listener\n");

    printf("\t->Press 3 to display GPU hybrid graphic type\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display the main menu options\n");
}

// Menu action control
void MenuControl(IADLXGPU* gpu)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display GPU information
        case '1':
            ShowGPUInfo(gpu);
            break;
            // Add GPU change event listener
        case '2':
            AddGPUEventListener();
            break;
            // Display GPU hybrid graphic type
        case '3':
            ShowHybridGraphicType();
            break;
            // Display main menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
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