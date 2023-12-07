//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainManualVRAMTuning.c
/// \brief Demonstrates how to control GPU manual VRAM tuning when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUManualVRAMTuning.h"
#include "SDK/Include/IGPUTuning.h"

// Display Memory Timing support
void ShowSupport(IADLXInterface* vramTuningIfc);

// Get VRAM state
void GetState(IADLXInterface* vramTuningIfc);

// Set Memory Timing Level
void SetTimingLevel(IADLXInterface* vramTuningIfc);

// Set VRAM state
void SetState(IADLXInterface* vramTuningIfc);

// Main menu
void MainMenu(IADLXInterface* vramTuningIfc);

// Menu action control
void MenuControl(IADLXInterface* vramTuningIfc);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get System Services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get GPU tuning service
        IADLXGPUTuningServices* gpuTuningService = NULL;
        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningService);

        if (ADLX_SUCCEEDED(res))
        {
                // Get GPU interface
            IADLXGPU* gpu = NULL;
            adlx_uint index = 0;
            res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

                    // Get ManualVRAMTuning support
            adlx_bool supported;
            gpuTuningService->pVtbl->IsSupportedManualVRAMTuning(gpuTuningService, gpu, &supported);
            printf("\tThe GPU support for manual VRAM tuning is: %d \n", supported);

            if (supported)
            {
                // Get ManualVRAMTuning interface
                IADLXInterface* vramTuningIfc = NULL;
                res = gpuTuningService->pVtbl->GetManualVRAMTuning(gpuTuningService, gpu, &vramTuningIfc);
                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu(vramTuningIfc);
                    MenuControl(vramTuningIfc);
                }
                // Release the vramTuningIfc interface
                if (vramTuningIfc != NULL)
                {
                    vramTuningIfc->pVtbl->Release(vramTuningIfc);
                    vramTuningIfc = NULL;
                }
            }
            else
            {
                printf("\tThis GPU Doesn't support Manual VRAM Tuning \n");
            }
           

            // Release the GPU interface
            if (gpu != NULL)
            {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else
        {
            printf("Failed to get GPU tuning service\n");
        }

        // Release the gpuTuningService interface
        if (gpuTuningService != NULL)
        {
            gpuTuningService->pVtbl->Release(gpuTuningService);
            gpuTuningService = NULL;
        }

        // Release the GPUs list interface
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

static const char* getDescStr(ADLX_MEMORYTIMING_DESCRIPTION desc)
{
    switch (desc)
    {
    case MEMORYTIMING_DEFAULT:
        return "Default";
    case MEMORYTIMING_FAST_TIMING:
        return "Fast Timing";
    case MEMORYTIMING_FAST_TIMING_LEVEL_2:
        return "Fast Timing Level2";
    case MEMORYTIMING_AUTOMATIC:
        return "Automatic";
    case MEMORYTIMING_MEMORYTIMING_LEVEL_1:
        return "Memory Timing Level1";
    case MEMORYTIMING_MEMORYTIMING_LEVEL_2:
        return "Memory Timing Level2";
    }
    return "Default";
};

void ShowSupport(IADLXInterface* vramTuningIfc)
{
    adlx_bool supported = false;
    IADLXManualVRAMTuning2* vramTuning2 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning2(), &vramTuning2);
    IADLXManualVRAMTuning1* vramTuning1 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning1(), &vramTuning1);
    ADLX_RESULT res = ADLX_FAIL;
    if (vramTuning2)
    {
        res = vramTuning2->pVtbl->IsSupportedMemoryTiming(vramTuning2, &supported);
    }
    else if (vramTuning1)
    {
        res = vramTuning1->pVtbl->IsSupportedMemoryTiming(vramTuning1, &supported);
    }

    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);

    // Release the ManualVRAMTuning2 interface
    if (vramTuning2 != NULL)
    {
        vramTuning2->pVtbl->Release(vramTuning2);
        vramTuning2 = NULL;
    }

    // Release the ManualVRAMTuning1 interface
    if (vramTuning1 != NULL)
    {
        vramTuning1->pVtbl->Release(vramTuning1);
        vramTuning1 = NULL;
    }
}

void GetState(IADLXInterface* vramTuningIfc)
{
    IADLXManualVRAMTuning2* vramTuning2 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning2(), &vramTuning2);
    IADLXManualVRAMTuning1* vramTuning1 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning1(), &vramTuning1);
    ADLX_MEMORYTIMING_DESCRIPTION desc;
    IADLXMemoryTimingDescriptionList* descList = NULL;
    if (vramTuning2)
    {
        vramTuning2->pVtbl->GetSupportedMemoryTimingDescriptionList(vramTuning2, &descList);
        vramTuning2->pVtbl->GetMemoryTimingDescription(vramTuning2, &desc);

        adlx_int freq;
        ADLX_IntRange rang;
        ADLX_RESULT res = vramTuning2->pVtbl->GetMaxVRAMFrequency(vramTuning2, &freq);
        printf("\tMaxVRAMFrequency is: %d, return code is: %d(0 means success)\n", freq, res);
        res = vramTuning2->pVtbl->GetMaxVRAMFrequencyRange(vramTuning2, &rang);
        printf("\tMaxVRAMFrequencyRange: [ %d, %d ], step: %d, return code is: %d(0 means success)\n", rang.minValue, rang.maxValue, rang.step, res);
    }
    else if (vramTuning1)
    {
        vramTuning1->pVtbl->GetSupportedMemoryTimingDescriptionList(vramTuning1, &descList);
        vramTuning1->pVtbl->GetMemoryTimingDescription(vramTuning1, &desc);

        IADLXManualTuningStateList* states = NULL;
        vramTuning1->pVtbl->GetVRAMTuningStates(vramTuning1, &states);
        adlx_uint s = states->pVtbl->Begin(states);
        printf("\tState is:\n");
        for (; s != states->pVtbl->End(states); s++)
        {
            IADLXManualTuningState* state = NULL;
            adlx_int frequency;
            adlx_int voltage;
            states->pVtbl->At_ManualTuningStateList(states, s, &state);
            state->pVtbl->GetFrequency(state, &frequency);
            state->pVtbl->GetVoltage(state, &voltage);
            printf("\t\tfrequency: %d, voltage: %d \n", frequency, voltage);
            if (state != NULL)
            {
                state->pVtbl->Release(state);
                state = NULL;
            }
        }
        if (states != NULL)
        {
            states->pVtbl->Release(states);
            states = NULL;
        }

        ADLX_IntRange frequencyRange;
        ADLX_IntRange voltageRange;
        ADLX_RESULT res = vramTuning1->pVtbl->GetVRAMTuningRanges(vramTuning1, &frequencyRange, &voltageRange);
        printf("\tFrequency Range: [ %d, %d ], step: %d, return code is: %d(0 means success)\n", frequencyRange.minValue, frequencyRange.maxValue, frequencyRange.step, res);
        printf("\tVoltage Range: [ %d, %d ], step: %d, return code is: %d(0 means success)\n", voltageRange.minValue, voltageRange.maxValue, voltageRange.step, res);
    }

    if (descList)
    {
        printf ("\tCurrent Timing desc is: %s\n", getDescStr (desc));
        printf ("\tSupported memory timing desc list:\n");
        for (adlx_uint s = 0; s != descList->pVtbl->End (descList); s++)
        {
            IADLXMemoryTimingDescription* item = NULL;
            descList->pVtbl->At_MemoryTimingDescriptionList (descList, s, &item);
            item->pVtbl->GetDescription (item, &desc);
            printf ("\t  %s\n", getDescStr (desc));

            // Release the IADLXMemoryTimingDescription interface
            if (item)
            {
                item->pVtbl->Release (item);
                item = NULL;
            }
        }
    }
    printf("\n");

    // Release the IADLXMemoryTimingDescriptionList interface
    if (descList != NULL)
    {
        descList->pVtbl->Release(descList);
        descList = NULL;
    }

    // Release the ManualVRAMTuning2 interface
    if (vramTuning2 != NULL)
    {
        vramTuning2->pVtbl->Release(vramTuning2);
        vramTuning2 = NULL;
    }

    // Release the ManualVRAMTuning1 interface
    if (vramTuning1 != NULL)
    {
        vramTuning1->pVtbl->Release(vramTuning1);
        vramTuning1 = NULL;
    }
}

void SetTimingLevel(IADLXInterface* vramTuningIfc)
{
    ADLX_RESULT res;
    IADLXManualVRAMTuning2* vramTuning2 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning2(), &vramTuning2);
    IADLXManualVRAMTuning1* vramTuning1 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning1(), &vramTuning1);
    ADLX_MEMORYTIMING_DESCRIPTION desc, currentDesc;
    IADLXMemoryTimingDescriptionList* descList = NULL;
    IADLXMemoryTimingDescription* item = NULL;
    adlx_bool supported = false;
    if (vramTuning2)
    {
        //If MemoryTiming is supported, then only will set the MemoryTiming
        res = vramTuning2->pVtbl->IsSupportedMemoryTiming(vramTuning2, &supported);
        if (supported)
        {
            res = vramTuning2->pVtbl->GetSupportedMemoryTimingDescriptionList(vramTuning2, &descList);
            if (descList)
            {
                vramTuning2->pVtbl->GetMemoryTimingDescription(vramTuning2, &currentDesc);
                for (adlx_uint s = 0; s != descList->pVtbl->End(descList); s++)
                {
                    descList->pVtbl->At_MemoryTimingDescriptionList(descList, s, &item);
                    item->pVtbl->GetDescription(item, &desc);
                    if (desc != currentDesc)
                    {
                        res = vramTuning2->pVtbl->SetMemoryTimingDescription(vramTuning2, desc);
                        printf("\tSet Memory Timing description to %s: return code is: %d (0 means success)\n", getDescStr(desc), res);
                        break;
                    }
                }
            }
            else
            {
                printf("\tFailed to get the Supported Memory Timing Description List.\n");
            }
        }
        else
        {

            printf("\tMemory Timing level not supported, so cannot set Memory Timing Description List\n");
        }
    }
    else if (vramTuning1)
    {
        //If MemoryTiming is supported, then only will set the MemoryTiming
        res = vramTuning1->pVtbl->IsSupportedMemoryTiming(vramTuning1, &supported);
        if (supported)
        {
            res = vramTuning1->pVtbl->GetSupportedMemoryTimingDescriptionList(vramTuning1, &descList);
            if (descList)
            {
                vramTuning1->pVtbl->GetMemoryTimingDescription(vramTuning1, &currentDesc);
                for (adlx_uint s = 0; s != descList->pVtbl->End(descList); s++)
                {
                    descList->pVtbl->At_MemoryTimingDescriptionList(descList, s, &item);
                    item->pVtbl->GetDescription(item, &desc);
                    if (desc != currentDesc)
                    {
                        res = vramTuning1->pVtbl->SetMemoryTimingDescription(vramTuning1, desc);
                        printf("\tSet Memory Timing description to %s: return code is: %d (0 means success)\n", getDescStr(desc), res);
                        break;
                    }
                }
            }
            else
            {
                printf("\tFailed to get the Supported Memory Timing Description List.\n");
            }
        }
        else
        {
            printf("\tMemory Timing level not supported, so cannot set Memory Timing Description List\n");
        }
    }

    // Release the IADLXMemoryTimingDescription interface
    if (item != NULL)
    {
        item->pVtbl->Release(item);
        item = NULL;
    }

    // Release the IADLXMemoryTimingDescriptionList interface
    if (descList != NULL)
    {
        descList->pVtbl->Release(descList);
        descList = NULL;
    }

    // Release the ManualVRAMTuning2 interface
    if (vramTuning2 != NULL)
    {
        vramTuning2->pVtbl->Release(vramTuning2);
        vramTuning2 = NULL;
    }

    // Release the ManualVRAMTuning1 interface
    if (vramTuning1 != NULL)
    {
        vramTuning1->pVtbl->Release(vramTuning1);
        vramTuning1 = NULL;
    }
}

void SetState(IADLXInterface* vramTuningIfc)
{
    ADLX_RESULT res;
    IADLXManualVRAMTuning2* vramTuning2 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning2(), &vramTuning2);
    IADLXManualVRAMTuning1* vramTuning1 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning1(), &vramTuning1);
    adlx_bool supported = false;
    if (vramTuning2)
    {
        //If MemoryTiming is supported, then only will set the state
        res = vramTuning2->pVtbl->IsSupportedMemoryTiming(vramTuning2, &supported);
        if (supported)
        {
            adlx_int freq;
            ADLX_IntRange rang;
            vramTuning2->pVtbl->GetMaxVRAMFrequency(vramTuning2, &freq);
            vramTuning2->pVtbl->GetMaxVRAMFrequencyRange(vramTuning2, &rang);
            if (freq != rang.minValue)
            {
                res = vramTuning2->pVtbl->SetMaxVRAMFrequency(vramTuning2, rang.minValue);
                printf("\tSet minimum frequency: return code is: %d (0 means success)\n", res);
            }
            else
            {
                res = vramTuning2->pVtbl->SetMaxVRAMFrequency(vramTuning2, rang.minValue + rang.step * 2);
                printf("\tSet maximum frequency: return code is: %d (0 means success)\n", res);
            }
        }
        else
        {
            printf("\tTuning not supported, cannot set the state\n");
        }
    }
    else if (vramTuning1)
    {
        //If MemoryTiming is supported, then only will set the state
        res = vramTuning1->pVtbl->IsSupportedMemoryTiming(vramTuning1, &supported);
        if (supported)
        {
            ADLX_IntRange frequencyRange;
            ADLX_IntRange voltageRange;
            vramTuning1->pVtbl->GetVRAMTuningRanges(vramTuning1, &frequencyRange, &voltageRange);
            IADLXManualTuningStateList* states = NULL;
            vramTuning1->pVtbl->GetVRAMTuningStates(vramTuning1, &states);
            adlx_uint s = states->pVtbl->Begin(states);
            for (; s != states->pVtbl->End(states); s++)
            {
                IADLXManualTuningState* state = NULL;
                adlx_int frequency;
                adlx_int voltage;
                states->pVtbl->At_ManualTuningStateList(states, s, &state);
                state->pVtbl->GetFrequency(state, &frequency);
                state->pVtbl->GetVoltage(state, &voltage);
                // Only change the first
                res = state->pVtbl->SetFrequency(state, frequency != frequencyRange.minValue ? frequencyRange.minValue : frequencyRange.maxValue);
                res = state->pVtbl->SetVoltage(state, voltage != voltageRange.minValue ? voltageRange.minValue : voltageRange.maxValue);
                break;
            }
            res = vramTuning1->pVtbl->SetVRAMTuningStates(vramTuning1, states);
            printf("\tChange VRAM tuning states: return code is: %d (0 means success)\n", res);
        }
        else
        {
            printf("\tTuning not supported, cannot set the state\n");
        }
    }

    // Release the ManualVRAMTuning2 interface
    if (vramTuning2 != NULL)
    {
        vramTuning2->pVtbl->Release(vramTuning2);
        vramTuning2 = NULL;
    }

    // Release the ManualVRAMTuning1 interface
    if (vramTuning1 != NULL)
    {
        vramTuning1->pVtbl->Release(vramTuning1);
        vramTuning1 = NULL;
    }
}

void MainMenu(IADLXInterface* vramTuningIfc)
{
    IADLXManualVRAMTuning2* vramTuning2 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning2(), &vramTuning2);
    IADLXManualVRAMTuning1* vramTuning1 = NULL;
    vramTuningIfc->pVtbl->QueryInterface(vramTuningIfc, IID_IADLXManualVRAMTuning1(), &vramTuning1);
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display Memory Timing support\n");
    if (vramTuning2)
        printf("\t->Press 2 to display Memory Timing level and frequency range\n");
    else if (vramTuning1)
        printf("\t->Press 2 to display Memory Timing level, VRAM frequency, and the voltage global range for all states\n");

    printf("\t->Press 3 to change current Memory Timing Level\n");
    if (vramTuning2)
        printf("\t->Press 4 to change current VRAM maximum frequency value\n");
    else if (vramTuning1)
        printf("\t->Press 4 to change VRAM states\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");

    // Release the ManualVRAMTuning2 interface
    if (vramTuning2 != NULL)
    {
        vramTuning2->pVtbl->Release(vramTuning2);
        vramTuning2 = NULL;
    }

    // Release the ManualVRAMTuning1 interface
    if (vramTuning1 != NULL)
    {
        vramTuning1->pVtbl->Release(vramTuning1);
        vramTuning1 = NULL;
    }
}

void MenuControl(IADLXInterface* vramTuningIfc)
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
