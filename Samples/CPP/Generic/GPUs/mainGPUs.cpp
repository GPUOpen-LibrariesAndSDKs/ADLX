//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUs.cpp
/// \brief Demonstrates how to enumerate GPUs, get GPU information, receive notifications when GPUs are enabled and disabled, and maintain GPU change event when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include <chrono>
#include <iostream>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display GPU information
void ShowGPUInfo(const IADLXGPUPtr& gpu);

// Display GPU hybrid graphic type
void ShowHybridGraphicType();

// Add GPU change event listener
void AddGPUEventListener(const IADLXGPUPtr& gpu);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXGPUPtr& gpu);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// GPU event change handler definition
class GPUEventListener : public IADLXGPUsEventListener
{
    adlx_bool ADLX_STD_CALL OnGPUListChanged(IADLXGPUList* pNewGPUs)
    {
        std::cout << "GPU list change event received" << std::endl;
        if (pNewGPUs == nullptr)
        {
            std::cout << "GPU list does not exist" << std::endl;
            return false;
        }

        std::cout << "GPU list size: " << pNewGPUs->Size() << std::endl;

        return true;
    }
};

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU list
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_SUCCEEDED(res) && !gpus->Empty())
        {
            // Inspect for the first GPU in the list
            IADLXGPUPtr gpu;
            res = gpus->At(0, &gpu);
            if (ADLX_SUCCEEDED(res))
            {
                // Display main menu options
                MainMenu();
                // Get and parse the selection
                MenuControl(gpu);
            }
        }
        else
        {
            std::cout << "Failed to get the GPU list" << std::endl;
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

// Display GPU information
void ShowGPUInfo(const IADLXGPUPtr& gpu)
{
    std::cout << "\n==== GPU info ====" << std::endl;
    // Display GPU info
    const char* vendorId = nullptr;
    ADLX_RESULT ret = gpu->VendorId(&vendorId);
    std::cout << "VendorId: " << vendorId << std::endl;

    ADLX_ASIC_FAMILY_TYPE asicFamilyType = ASIC_UNDEFINED;
    ret = gpu->ASICFamilyType(&asicFamilyType);
    std::cout << "ASICFamilyType: " << asicFamilyType << std::endl;

    ADLX_GPU_TYPE gpuType = GPUTYPE_UNDEFINED;
    ret = gpu->Type(&gpuType);
    std::cout << "Type: " << gpuType << std::endl;

    adlx_bool isExternal = false;
    ret = gpu->IsExternal(&isExternal);
    std::cout << "IsExternal: " << isExternal << std::endl;

    const char* gpuName = nullptr;
    ret = gpu->Name(&gpuName);
    std::cout << "Name: " << gpuName << std::endl;

    const char* driverPath = nullptr;
    ret = gpu->DriverPath(&driverPath);
    std::cout << "DriverPath: " << driverPath << std::endl;

    const char* pnpString = nullptr;
    ret = gpu->PNPString(&pnpString);
    std::cout << "PNPString: " << pnpString << std::endl;

    adlx_bool hasDesktops = false;
    ret = gpu->HasDesktops(&hasDesktops);
    std::cout << "HasDesktops: " << hasDesktops << std::endl;

    adlx_uint totalVRAM;
    ret = gpu->TotalVRAM(&totalVRAM);
    std::cout << "TotalVRAM: " << totalVRAM << " MB" << std::endl;

    adlx_int id;
    ret = gpu->UniqueId(&id);
    std::cout << "UniqueId: " << id << std::endl;
}

void ShowHybridGraphicType()
{
    ADLX_HG_TYPE hgType = ADLX_HG_TYPE::NONE;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->HybridGraphicsType(&hgType);
    if (ADLX_SUCCEEDED(res))
    {
        switch (hgType)
        {
        case ADLX_HG_TYPE::NONE:
            std::cout << "GPU hybrid type is: "
                      << "ADLX_HG_TYPE::NONE" << std::endl;
            break;
        case ADLX_HG_TYPE::AMD:
            std::cout << "GPU hybrid type is: "
                      << "ADLX_HG_TYPE::AMD" << std::endl;
            break;
        case ADLX_HG_TYPE::OTHER:
            std::cout << "GPU hybrid type is: "
                      << "ADLX_HG_TYPE::OTHER" << std::endl;
            break;
        }
    }
}

// Add GPU change event listener
void AddGPUEventListener(const IADLXGPUPtr& gpu)
{
    GPUEventListener gpuListener;
    IADLXGPUsChangedHandlingPtr gpusChangedHandling;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetGPUsChangedHandling(&gpusChangedHandling);
    if (ADLX_SUCCEEDED(res) && gpusChangedHandling)
    {
        res = gpusChangedHandling->AddGPUsListEventListener(&gpuListener);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Addition of GPU event listener successful" << std::endl;
        }

        // Enable or disable a GPU device using Windows Device Manager
        std::this_thread::sleep_for(std::chrono::seconds(15));

        res = gpusChangedHandling->RemoveGPUsListEventListener(&gpuListener);
        if (ADLX_SUCCEEDED(res))
        {
            std::cout << "Removal of GPU event listener successful" << std::endl;
        }
    }
}

void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display GPU information" << std::endl;

    std::cout << "\t->Press 2 to add GPU event listener" << std::endl;

    std::cout << "\t->Press 3 to display GPU hybrid graphic type" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXGPUPtr& gpu)
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
            AddGPUEventListener(gpu);
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
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}
