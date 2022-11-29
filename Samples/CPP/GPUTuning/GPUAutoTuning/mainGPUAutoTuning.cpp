//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUAutoTuning.cpp
/// \brief Demonstrates how to control GPU auto-tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUAutoTuning.h"
#include "SDK/Include/IGPUTuning.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Event to verify call back.
HANDLE g_ADLXEvent = nullptr;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Check if current GPU tuning status is set to factory default
void CheckGPUTuningIsAtFactoryStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus);

// Restore GPU tuning status to factory default
void RestoreGPUTuningToFactoryStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus);

// Display GPU auto-tuning support status
void ShowGPUAutoTuningSupport(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus);

// Display current GPU status
void ShowCurrentGPUStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus);

// Derive from IADLXGPUAutoTuningCompleteListener
class GPUAutoTuningCompleteEvents;
// Start GPU auto-tuning
void StartGPUAutoTuning(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus, int num);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Create event
        g_ADLXEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ADLXEvent"));

        IADLXGPUTuningServicesPtr gpuTuningService;
        res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices(&gpuTuningService);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPUListPtr gpus;
            res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
            if (ADLX_SUCCEEDED(res))
            {
                // Display main menu options
                MainMenu();

                // Get and execute the choice
                MenuControl(gpuTuningService, gpus);
            }
            else
                std::cout << "\tGet GPU list failed" << std::endl;
        }
        else
            std::cout << "\tGet GPU tuning services failed" << std::endl;
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Close event
    if (g_ADLXEvent)
        CloseHandle(g_ADLXEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to check if current GPU tuning status is set to factory default" << std::endl;
    std::cout << "\t->Press 2 to restore the current GPU tuning status to factory default" << std::endl;
    std::cout << "\t->Press 3 to display GPU auto-tuning support" << std::endl;
    std::cout << "\t->Press 4 to display current GPU auto-tuning status" << std::endl;
    std::cout << "\t->Press 5 to start undervolt GPU tuning" << std::endl;
    std::cout << "\t->Press 6 to start overclock GPU tuning" << std::endl;
    std::cout << "\t->Press 7 to start overclock VRAM tuning" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Check if current GPU tuning status is set to factory default
        case '1':
            CheckGPUTuningIsAtFactoryStatus(gpuTuningService, gpus);
            break;

        // Restore GPU tuning status to factory default
        case '2':
            RestoreGPUTuningToFactoryStatus(gpuTuningService, gpus);
            break;

        // Display GPU auto-tuning support status
        case '3':
            ShowGPUAutoTuningSupport(gpuTuningService, gpus);
            break;

        // Display current GPU status
        case '4':
            ShowCurrentGPUStatus(gpuTuningService, gpus);
            break;

        // Start undervolt GPU tuning
        case '5':
        // Start overclock GPU tuning
        case '6':
        // Start overclock VRAM tuning
        case '7':
            StartGPUAutoTuning(gpuTuningService, gpus, num - 5);
            break;

        // Display menu options
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

// Check if current GPU tuning status is set to factory default
void CheckGPUTuningIsAtFactoryStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus)
{
    IADLXGPUPtr oneGPU;
    for (adlx_uint crt = gpus->Begin(); crt != gpus->End(); ++crt)
    {
        ADLX_RESULT res = gpus->At(crt, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == nullptr)
        {
            std::cout << "\tGet the GPU at location" << crt << " failed" << std::endl;
            break;
        }
        adlx_bool isFactory = false;
        res = gpuTuningService->IsAtFactory(oneGPU, &isFactory);
        if (ADLX_FAILED(res))
        {
            std::cout << "\tCheck of the GPU at location" << crt << " default tuning status failed" << std::endl;
            break;
        }
        std::cout << "\tThe GPU at location" << crt << " default status: " << isFactory << std::endl;
    }
}

// Reset the current GPU tuning status to factory default
void RestoreGPUTuningToFactoryStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus)
{
    IADLXGPUPtr oneGPU;
    for (adlx_uint crt = gpus->Begin(); crt != gpus->End(); ++crt)
    {
        ADLX_RESULT res = gpus->At(crt, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == nullptr)
        {
            std::cout << "\tGet the GPU at location" << crt << " failed" << std::endl;
            break;
        }
        adlx_bool isFactory = false;
        res = gpuTuningService->ResetToFactory(oneGPU);
        if (ADLX_FAILED(res))
            std::cout << "\tReset the GPU at location" << crt << " to default failed" << std::endl;
        else
            std::cout << "\tReset the GPU at location" << crt << " to default successful" << std::endl;
    }
}

// Display GPU auto-tuning support status
void ShowGPUAutoTuningSupport(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus)
{
    IADLXGPUPtr oneGPU;
    for (adlx_uint crt = gpus->Begin(); crt != gpus->End(); ++crt)
    {
        ADLX_RESULT res = gpus->At(crt, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == nullptr)
        {
            std::cout << "\tGet the GPU at location" << crt << " failed" << std::endl;
            break;
        }
        adlx_bool supported = false;
        res = gpuTuningService->IsSupportedAutoTuning(oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
        {
            std::cout << "\tThe GPU at location" << crt << " does not support auto-tuning" << std::endl;
            break;
        }
        IADLXInterfacePtr autoTuningIfc;
        res = gpuTuningService->GetAutoTuning(oneGPU, &autoTuningIfc);
        if (ADLX_FAILED(res) || autoTuningIfc == nullptr)
        {
            std::cout << "\tGet auto-tuning for the GPU at location" << crt << " failed" << std::endl;
            break;
        }
        IADLXGPUAutoTuningPtr autoTuning(autoTuningIfc);
        if (autoTuning)
        {
            // If ret != ADLX_OK, return default value(false).
            supported = false;
            res = autoTuning->IsSupportedUndervoltGPU(&supported);
            std::cout << "\tIs the GPU at location" << crt << " supported undervolt: " << supported << std::endl;
            supported = false;
            res = autoTuning->IsSupportedOverclockGPU(&supported);
            std::cout << "\tIs the GPU at location" << crt << " supported overclock: " << supported << std::endl;
            supported = false;
            res = autoTuning->IsSupportedOverclockVRAM(&supported);
            std::cout << "\tIs the GPU at location" << crt << " supported overclock VRAM: " << supported << std::endl;
        }
    }
}

// Display current GPU status
void ShowCurrentGPUStatus(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus)
{
    IADLXGPUPtr oneGPU;
    for (adlx_uint crt = gpus->Begin(); crt != gpus->End(); ++crt)
    {
        ADLX_RESULT res = gpus->At(crt, &oneGPU);
        if (ADLX_FAILED(res) || oneGPU == nullptr)
        {
            std::cout << "\tGet GPU at location" << crt << " failed" << std::endl;
            break;
        }
        adlx_bool supported = false;
        res = gpuTuningService->IsSupportedAutoTuning(oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
        {
            std::cout << "\tThe GPU at location" << crt << " does not support auto-tuning" << std::endl;
            break;
        }
        IADLXInterfacePtr autoTuningIfc;
        res = gpuTuningService->GetAutoTuning(oneGPU, &autoTuningIfc);
        if (ADLX_FAILED(res) || autoTuningIfc == nullptr)
        {
            std::cout << "\tGet auto-tuning for the GPU at location" << crt << " failed" << std::endl;
            break;
        }
        IADLXGPUAutoTuningPtr autoTuning(autoTuningIfc);
        adlx_bool applied = false;
        if (autoTuning)
        {
            // If ret != ADLX_OK, return default value(false).
            applied = false;
            res = autoTuning->IsCurrentUndervoltGPU(&applied);
            std::cout << "\tIs the GPU at location" << crt << " undervolt applied: " << applied << std::endl;
            applied = false;
            res = autoTuning->IsCurrentOverclockGPU(&applied);
            std::cout << "\tIs the GPU at location" << crt << " overclock applied: " << applied << std::endl;
            applied = false;
            res = autoTuning->IsCurrentOverclockVRAM(&applied);
            std::cout << "\tIs the GPU at location" << crt << " overclock VRAM applied: " << applied << std::endl;
        }
    }
}

class GPUAutoTuningCompleteEvents : public IADLXGPUAutoTuningCompleteListener
{
public:
    adlx_bool ADLX_STD_CALL OnGPUAutoTuningComplete(IADLXGPUAutoTuningCompleteEvent* pGPUAutoTuningCompleteEvent)
    {
        adlx_bool change = false;
        change = pGPUAutoTuningCompleteEvent->IsUndervoltGPUCompleted();
        change = pGPUAutoTuningCompleteEvent->IsOverclockGPUCompleted();
        change = pGPUAutoTuningCompleteEvent->IsOverclockVRAMCompleted();
        SetEvent(g_ADLXEvent);
        return true;
    }
};

GPUAutoTuningCompleteEvents gpuAutoTuningCompleteEvents;

void StartGPUAutoTuning(IADLXGPUTuningServicesPtr gpuTuningService, IADLXGPUListPtr gpus, int num)
{
    IADLXGPUPtr oneGPU;
    // Set the first GPU auto-tuning
    ADLX_RESULT res = gpus->At(0, &oneGPU);
    if (ADLX_FAILED(res) || oneGPU == nullptr)
    {
        std::cout << "\tGet GPU failed" << std::endl;
        return;
    }
    adlx_bool supported = false;
    res = gpuTuningService->IsSupportedAutoTuning(oneGPU, &supported);
    if (ADLX_FAILED(res) || supported == false)
    {
        std::cout << "\tThe GPU does not support auto-tuning" << std::endl;
        return;
    }
    IADLXInterfacePtr autoTuningIfc;
    res = gpuTuningService->GetAutoTuning(oneGPU, &autoTuningIfc);
    if (ADLX_FAILED(res) || autoTuningIfc == nullptr)
    {
        std::cout << "\tGet GPU auto-tuning failed" << std::endl;
        return;
    }
    IADLXGPUAutoTuningPtr autoTuning(autoTuningIfc);
    if (autoTuning)
    {
        bool modeIsSupported = false;
        switch (num)
        {
        case '0':
            res = autoTuning->IsSupportedUndervoltGPU(&modeIsSupported);
            if (!modeIsSupported) {
                std::cout << "\tUndervolt profile is not supported" << std::endl;
            }
            else {
                res = autoTuning->StartUndervoltGPU(&gpuAutoTuningCompleteEvents);
                WaitForSingleObject(g_ADLXEvent, 1000);
                ResetEvent(g_ADLXEvent);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "\tStart undervolt GPU successful" << std::endl;
                else
                    std::cout << "\tStart undervolt GPU failed" << std::endl;
            }
            break;
        case '1':
            res = autoTuning->IsSupportedOverclockGPU(&modeIsSupported);
            if (!modeIsSupported) {
                std::cout << "\tGPU Overclock profile is not supported" << std::endl;
            }
            else {
                res = autoTuning->StartOverclockGPU(&gpuAutoTuningCompleteEvents);
                WaitForSingleObject(g_ADLXEvent, 1000);
                ResetEvent(g_ADLXEvent);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "\tStart overclock GPU successful" << std::endl;
                else
                    std::cout << "\tStart overclock GPU failed" << std::endl;
            }
            break;
        case '2':
            res = autoTuning->IsSupportedOverclockVRAM(&modeIsSupported);
            if (!modeIsSupported) {
                std::cout << "\tVRAM overclock profile is not supported" << std::endl;
            }
            else {
                res = autoTuning->StartOverclockVRAM(&gpuAutoTuningCompleteEvents);
                WaitForSingleObject(g_ADLXEvent, 1000);
                ResetEvent(g_ADLXEvent);
                if (ADLX_SUCCEEDED(res))
                    std::cout << "\tStart overclock VRAM successful" << std::endl;
                else
                    std::cout << "\tStart overclock VRAM failed" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}