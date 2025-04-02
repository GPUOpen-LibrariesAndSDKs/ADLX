//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualVRAMTuning.cpp
/// \brief Demonstrates how to control GPU manual VRAM tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IGPUManualVRAMTuning.h"
#include "SDK/Include/IGPUTuning.h"
#include <iostream>
#include <map>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Display Memory Timing support
void ShowSupport(IADLXInterfacePtr& vramTuningIfc);

// Get VRAM state
void GetState(IADLXInterfacePtr& vramTuningIfc);

// Set Memory Timing Level
void SetTimingLevel(IADLXInterfacePtr& vramTuningIfc);

// Set VRAM state
void SetState(IADLXInterfacePtr& vramTuningIfc);

// Main menu
void MainMenu(IADLXInterfacePtr& vramTuningIfc);

// Menu action control
void MenuControl(IADLXInterfacePtr vramTuningIfc);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get GPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
        if (ADLX_SUCCEEDED(res) && !gpus->Empty())
        {
            // Get GPU tuning service
            IADLXGPUTuningServicesPtr gpuTuningService;
            res = g_ADLXHelp.GetSystemServices()->GetGPUTuningServices(&gpuTuningService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get GPU interface
                IADLXGPUPtr gpu;
                adlx_uint index = 0;
                res = gpus->At(index, &gpu);
                if (ADLX_SUCCEEDED(res))
                {
                    // Get manual VRAM tuning support
                    adlx_bool supported;
                    res = gpuTuningService->IsSupportedManualVRAMTuning(gpu, &supported);
                    if (ADLX_SUCCEEDED(res))
                        std::cout << "\tGPU manual VRAM tuning support status: " << supported << std::endl;
                    if (supported)
                    {
                        // Get manual VRAM tuning interface
                        IADLXInterfacePtr vramTuningIfc;
                        res = gpuTuningService->GetManualVRAMTuning(gpu, &vramTuningIfc);
                        if (ADLX_SUCCEEDED(res))
                        {
                            MainMenu(vramTuningIfc);
                            MenuControl(vramTuningIfc);
                        }
                    }
                    else
                    {
                        return WaitAndExit("\nThis GPU Doesn't support Manual VRAM Tuning", 0);
                    }
                }
            }
            else
                std::cout << "Failed to get GPU tuning services" << std::endl;
        }
        else
            std::cout << "Failed to get GPU" << std::endl;
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

static std::map<ADLX_MEMORYTIMING_DESCRIPTION, const char*> descMap =
    {
        {MEMORYTIMING_DEFAULT, "Default"},
        {MEMORYTIMING_FAST_TIMING, "Fast Timing"},
        {MEMORYTIMING_FAST_TIMING_LEVEL_2, "Fast Timing Level2"},
        {MEMORYTIMING_AUTOMATIC, "Automatic"},
        {MEMORYTIMING_MEMORYTIMING_LEVEL_1, "Memory Timing Level1"},
        {MEMORYTIMING_MEMORYTIMING_LEVEL_2, "Memory Timing Level2"}};

void ShowSupport(IADLXInterfacePtr& vramTuningIfc)
{
    adlx_bool supported = false;
    IADLXManualVRAMTuning2Ptr vramTuning2(vramTuningIfc);
    IADLXManualVRAMTuning1Ptr vramTuning1(vramTuningIfc);
    ADLX_RESULT res = ADLX_FAIL;
    if (vramTuning2)
    {
        res = vramTuning2->IsSupportedMemoryTiming(&supported);
    }
    else if (vramTuning1)
    {
        res = vramTuning1->IsSupportedMemoryTiming(&supported);
    }
    std::cout << "\tIsSupported: " << supported << ", return code is: "<< res << "(0 means success)" << std::endl;
}

void GetState(IADLXInterfacePtr& vramTuningIfc)
{
    IADLXManualVRAMTuning2Ptr vramTuning2(vramTuningIfc);
    IADLXManualVRAMTuning1Ptr vramTuning1(vramTuningIfc);
    ADLX_MEMORYTIMING_DESCRIPTION desc;
    IADLXMemoryTimingDescriptionListPtr descList;
    if (vramTuning2)
    {
        vramTuning2->GetSupportedMemoryTimingDescriptionList(&descList);
        vramTuning2->GetMemoryTimingDescription(&desc);

        adlx_int freq;
        ADLX_IntRange rang;
        ADLX_RESULT res = vramTuning2->GetMaxVRAMFrequency(&freq);
        std::cout << "\tMax VRAM frequency: " << freq << ", return code is: "<< res << "(0 means success)" << std::endl;
        res = vramTuning2->GetMaxVRAMFrequencyRange(&rang);
        std::cout << "\tMax VRAM frequency range: [" << rang.minValue << " , " << rang.maxValue << " ], step: " << rang.step 
                  << ", return code is: "<< res << "(0 means success)" << std::endl;
        IADLXManualVRAMTuning2_1Ptr vramTuning2_1(vramTuning2);
        if (vramTuning2_1)
        {
            res = vramTuning2_1->GetMaxVRAMFrequencyDefault(&freq);
            std::cout << "\tDefault Max VRAM frequency: " << freq << ", return code is: " << res << "(0 means success)" << std::endl;

        }

    }
    else if (vramTuning1)
    {
        vramTuning1->GetSupportedMemoryTimingDescriptionList(&descList);
        vramTuning1->GetMemoryTimingDescription(&desc);

        IADLXManualTuningStateListPtr states;
        vramTuning1->GetVRAMTuningStates(&states);
        adlx_uint s = states->Begin();
        std::cout << "\tState is:" << std::endl;
        for (; s != states->End(); s++)
        {
            IADLXManualTuningStatePtr state;
            adlx_int frequency;
            adlx_int voltage;
            states->At(s, &state);
            state->GetFrequency(&frequency);
            state->GetVoltage(&voltage);
            std::cout << "\t\tfrequency: " << frequency << " voltage: " << voltage << std::endl;
        }

        ADLX_IntRange frequencyRange;
        ADLX_IntRange voltageRange;
        ADLX_RESULT res = vramTuning1->GetVRAMTuningRanges(&frequencyRange, &voltageRange);
        std::cout << "\tFrequency range: [" << frequencyRange.minValue << " , " << frequencyRange.maxValue << " ], step: " << frequencyRange.step 
                  << ", return code is: "<< res << "(0 means success)" << std::endl;
        std::cout << "\tVoltage range: [" << voltageRange.minValue << " , " << voltageRange.maxValue << " ], step: " << voltageRange.step 
                  << ", return code is: "<< res << "(0 means success)" << std::endl;
    }
    if (descList)
    {
        std::cout << "\tCurrent timing desc: " << descMap[desc] << std::endl;
        std::cout << "\tSupported Memory Timing desc list:" << std::endl;
        for (adlx_uint s = 0; s != descList->End (); s++)
        {
            IADLXMemoryTimingDescriptionPtr item;
            descList->At (s, &item);
            item->GetDescription (&desc);
            std::cout << "\t  " << descMap[desc] << std::endl;
        }
    }
    std::cout << std::endl;
}

void SetTimingLevel(IADLXInterfacePtr& vramTuningIfc)
{
    ADLX_RESULT res;
    IADLXManualVRAMTuning2Ptr vramTuning2(vramTuningIfc);
    IADLXManualVRAMTuning1Ptr vramTuning1(vramTuningIfc);
    ADLX_MEMORYTIMING_DESCRIPTION desc, currentDesc;
    IADLXMemoryTimingDescriptionListPtr descList;
    bool supported = false;
    if (vramTuning2)
    {
        //If MemoryTiming is supported, then only will get the MemoryTimingDescriptionList
        res = vramTuning2->IsSupportedMemoryTiming(&supported);
        if (supported)
        {
            vramTuning2->GetSupportedMemoryTimingDescriptionList(&descList);
            if (descList)
            {
                vramTuning2->GetMemoryTimingDescription(&currentDesc);
                for (adlx_uint s = 0; s != descList->End(); s++)
                {
                    IADLXMemoryTimingDescriptionPtr item;
                    descList->At(s, &item);
                    item->GetDescription(&desc);
                    if (currentDesc != desc)
                    {
                        res = vramTuning2->SetMemoryTimingDescription(desc);
                        std::cout << "\tSet Memory Timing description to " << descMap[desc] << ": return code is: " << res << " (0 means success)" << std::endl;
                        break;
                    }
                }
            }
            else
            {
                std::cout << "\tFailed to get the Supported Memory Timing Description List." << std::endl;
            }
        }
        else
        {
            std::cout << "\tMemory Timing Level not Supported, so cannot set Memory Timing Description List." << std::endl;
        }
    }
    else if (vramTuning1)
    {
        //If MemoryTiming is supported, then only will get the MemoryTimingDescriptionList
        res = vramTuning1->IsSupportedMemoryTiming(&supported);
        if (supported)
        {
            vramTuning1->GetSupportedMemoryTimingDescriptionList(&descList);
            if (descList)
            {
                vramTuning1->GetMemoryTimingDescription(&currentDesc);
                for (adlx_uint s = 0; s != descList->End(); s++)
                {
                    IADLXMemoryTimingDescriptionPtr item;
                    descList->At(s, &item);
                    item->GetDescription(&desc);
                    if (currentDesc != desc)
                    {
                        res = vramTuning1->SetMemoryTimingDescription(desc);
                        std::cout << "\tSet Memory Timing description to " << descMap[desc] << ": return code is: " << res << " (0 means success)" << std::endl;
                        break;
                    }
                }
            }
            else
            {
                std::cout << "\tFailed to get the Supported Memory Timing Description List." << std::endl;
            }
        }
        else
        {
            std::cout << "\tMemory Timing Level not Supported, so cannot set Memory Timing Description List." << std::endl;
        }
    }
}

void SetState(IADLXInterfacePtr& vramTuningIfc)
{
    ADLX_RESULT res;
    IADLXManualVRAMTuning2Ptr vramTuning2(vramTuningIfc);
    IADLXManualVRAMTuning1Ptr vramTuning1(vramTuningIfc);
    bool supported = false;
    if (vramTuning2)
    {
        //If MemoryTiming is supported, then only will set the MemoryTimingState
        res = vramTuning2->IsSupportedMemoryTiming(&supported);
        if (supported)
        {
            adlx_int freq;
            ADLX_IntRange rang;
            vramTuning2->GetMaxVRAMFrequency(&freq);
            vramTuning2->GetMaxVRAMFrequencyRange(&rang);
            if (freq != rang.minValue)
            {
                res = vramTuning2->SetMaxVRAMFrequency(rang.minValue);
                std::cout << "\tUse min Frequency to set, return code(0 is Success) is: " << res << std::endl;
            }
            else
            {
                res = vramTuning2->SetMaxVRAMFrequency(rang.minValue + rang.step * 2);
                std::cout << "\tUse max Frequency to set, return code(0 is Success) is: " << res << std::endl;
            }
        }
        else
        {
            std::cout << "\tTuning not Supported, so cannot change the State." << std::endl;
        }
    }
    else if (vramTuning1)
    {
        //If MemoryTiming is supported, then only will set the MemoryTimingState
        res = vramTuning1->IsSupportedMemoryTiming(&supported);
        if (supported)
        {
            ADLX_IntRange frequencyRange;
            ADLX_IntRange voltageRange;
            vramTuning1->GetVRAMTuningRanges(&frequencyRange, &voltageRange);
            IADLXManualTuningStateListPtr states;
            vramTuning1->GetVRAMTuningStates(&states);
            adlx_uint s = states->Size() - 1;
            for (; s != states->End(); s++)
            {
                IADLXManualTuningStatePtr state;
                adlx_int frequency;
                adlx_int voltage;
                states->At(s, &state);
                state->GetFrequency(&frequency);
                state->GetVoltage(&voltage);
                // Only change the last
                res = state->SetFrequency(frequencyRange.maxValue - frequencyRange.step * 10);
                res = state->SetVoltage(voltageRange.maxValue - voltageRange.step * 10);
                break;
            }
            res = vramTuning1->SetVRAMTuningStates(states);
            std::cout << "\tChange VRAM tuning states, return code(0 is Success) is: " << res << std::endl;
        }
        else
        {
            std::cout << "\tTuning not Supported, so cannot change the State." << std::endl;
        }
    }
}

void MainMenu(IADLXInterfacePtr& vramTuningIfc)
{
    // Acquire to ManualVRAMTuning1
    IADLXManualVRAMTuning1Ptr vramTuning1(vramTuningIfc);
    // Acquire to ManualVRAMTuning2
    IADLXManualVRAMTuning2Ptr vramTuning2(vramTuningIfc);

    std::cout << "\tChoose from the following options:" << std::endl;

    std::cout << "\t->Press 1 to display Memory Timing support" << std::endl;
    if (vramTuning2)
        std::cout << "\t->Press 2 to get Memory Timing level and frequency range" << std::endl;
    else if (vramTuning1)
        std::cout << "\t->Press 2 to get Memory Timing level, VRAM frequency, and the voltage global range for all states" << std::endl;

    std::cout << "\t->Press 3 to change current Memory Timing Level" << std::endl;

    if (vramTuning2)
        std::cout << "\t->Press 4 to change current VRAM max frequency value" << std::endl;
    else if (vramTuning1)
        std::cout << "\t->Press 4 to change VRAM states" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(IADLXInterfacePtr vramTuningIfc)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Get Memory Timing support
        case '1':
            ShowSupport(vramTuningIfc);
            break;

        // Get VRAM state
        case '2':
            GetState(vramTuningIfc);
            break;

        // Set timing level
        case '3':
            SetTimingLevel(vramTuningIfc);
            break;

        // Set VRAM state
        case '4':
            SetState(vramTuningIfc);
            break;

        // Display menu options
        case 'm':
        case 'M':
            MainMenu(vramTuningIfc);
            break;
        default:
            break;
        }
    }
}

int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}