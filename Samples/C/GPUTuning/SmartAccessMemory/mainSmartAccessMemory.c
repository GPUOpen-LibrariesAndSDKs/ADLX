//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartAccessMemory.c
/// \brief Demonstrates how to control AMD SmartAccess Memory when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISmartAccessMemory.h"
#include "SDK/Include/IGPUTuning1.h"

static HANDLE SAMEvent = NULL;

static adlx_bool ADLX_STD_CALL OnGPUTuningChanged(IADLXGPUTuningChangedListener* pGPUTuningChangedListener, IADLXGPUTuningChangedEvent* pGPUTuningChangedEvent)
{
    IADLXGPUTuningChangedEvent1* pGPUTuningChangedEvent1 = NULL;
    pGPUTuningChangedEvent->pVtbl->QueryInterface(pGPUTuningChangedEvent, IID_IADLXGPUTuningChangedEvent1(), &pGPUTuningChangedEvent1);
    adlx_bool SAMChange = pGPUTuningChangedEvent1->pVtbl->IsSmartAccessMemoryChanged(pGPUTuningChangedEvent1);
    if (SAMChange)
    {
        adlx_bool enabled = false, completed = false;
        pGPUTuningChangedEvent1->pVtbl->GetSmartAccessMemoryStatus(pGPUTuningChangedEvent1, &enabled, &completed);
        pGPUTuningChangedEvent1->pVtbl->Release(pGPUTuningChangedEvent1);
        pGPUTuningChangedEvent1 = NULL;
    }

    SetEvent(SAMEvent);
    return true;
}
static IADLXGPUTuningChangedListenerVtbl gpuTuningChangedVtable = { &OnGPUTuningChanged };
static IADLXGPUTuningChangedListener gpuTuningChangedListener = { &gpuTuningChangedVtable };

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus);

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode);

// Find the first GPU index that supports AMD SmartAccess Memory. Return -1 if all GPUs are not supported
adlx_uint GetGPUIndexSupportSAM(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus);

// Display AMD SmartAccess Memory support status on a GPU
void ShowSmartAccessMemorySupport(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus);

// Display AMD SmartAccess Memory enabled status
void ShowSmartAccessMemoryState(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus);

// Set AMD SmartAccess Memory state
void SetSmartAccessMemoryState(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus);

int main ()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED (res))
    {
        IADLXSystem* sys = ADLXHelper_GetSystemServices();
        IADLXGPUTuningServices* gpuTuningService = NULL;
        IADLXGPUTuningServices1* gpuTuningService1 = NULL;
        IADLXGPUTuningChangedHandling* gpuTuningHandling = NULL;
        IADLXGPUList* gpus = NULL;
        if (sys != NULL)
        {
            res = sys->pVtbl->GetGPUTuningServices (sys, &gpuTuningService);
            if (ADLX_SUCCEEDED(res))
            { 
                // Get gpuTuningService1 via gpuTuningService::QueryInterface()
                res = gpuTuningService->pVtbl->QueryInterface(gpuTuningService, IID_IADLXGPUTuningServices1(), &gpuTuningService1);
                if (ADLX_SUCCEEDED(res))
                {
                    
                    res = gpuTuningService1->pVtbl->GetGPUTuningChangedHandling(gpuTuningService1, &gpuTuningHandling);
                    if (ADLX_SUCCEEDED(res))
                    {
                        // Add listener
                        SAMEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
                        ADLX_RESULT eventRes = gpuTuningHandling->pVtbl->AddGPUTuningEventListener(gpuTuningHandling, &gpuTuningChangedListener);

                        // Menu
                        res = sys->pVtbl->GetGPUs(sys, &gpus);
                        if (ADLX_SUCCEEDED(res))
                        {
                            // Display main menu options
                            MainMenu();

                            // Get and execute the choice
                            MenuControl(gpuTuningService1, gpus);
                        }
                        else
                            printf("Failed to get GPU list\n");

                        // Remove listener
                        if (ADLX_SUCCEEDED(eventRes))
                            eventRes = gpuTuningHandling->pVtbl->RemoveGPUTuningEventListener(gpuTuningHandling, &gpuTuningChangedListener);
                    }
                    else
                        printf("Failed to get GPU Tuning Changed Handling\n");
                }
                else
                    printf("Failed to get gpuTuningService1\n");
            }
            else
                printf("Failed to get gpuTuningService\n");
        }
        else
            printf("Failed to get systemService\n");
        // Free
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
        if (gpuTuningHandling != NULL)
        {
            gpuTuningHandling->pVtbl->Release(gpuTuningHandling);
            gpuTuningHandling = NULL;
        }
        if (gpuTuningService1 != NULL)
        {
            gpuTuningService1->pVtbl->Release(gpuTuningService1);
            gpuTuningService1 = NULL;
        }
        if (gpuTuningService != NULL)
        {
            gpuTuningService->pVtbl->Release(gpuTuningService);
            gpuTuningService = NULL;
        }
    }
    else
        return WaitAndExit ("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system ("pause");

    return 0;
}

// Main menu
void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display AMD SmartAccess Memory supported GPUs\n");
    printf("\t->Press 2 to display AMD SmartAccess Memory enabled status\n");
    printf("\t->Press 3 to set the AMD SmartAccess Memory state\n");
    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus)
{
    int num = 0;
    while ((num = getchar ()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Display AMD SmartAccess Memory support status on a GPU
        case '1':
            ShowSmartAccessMemorySupport(gpuTuningService1, gpus);
            break;

        // Display AMD SmartAccess Memory enabled status
        case '2':
            ShowSmartAccessMemoryState(gpuTuningService1, gpus);
            break;

        // Set AMD SmartAccess Memory state
        case '3':
            SetSmartAccessMemoryState(gpuTuningService1, gpus);
            break;

        // Display menu options
        case 'm':
        case 'M':
            MainMenu ();
            break;
        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system ("pause");
    return retCode;
}

// Find the first GPU index that supports AMD SmartAccess Memory. Return -1 if all GPUs are not supported
adlx_uint GetGPUIndexSupportSAM(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus)
{
    adlx_uint supportedIndex= -1;
    IADLXGPU* oneGPU = NULL;
    IADLXSmartAccessMemory* smartAccessMemory = NULL;
    for (auto index = gpus->pVtbl->Begin(gpus); index != gpus->pVtbl->End(gpus); ++index)
    {
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            // Get the AMD SmartAccess Memory interface
            res = gpuTuningService1->pVtbl->GetSmartAccessMemory(gpuTuningService1, oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool supported = false;
                ADLX_RESULT res = smartAccessMemory->pVtbl->IsSupported(smartAccessMemory, &supported);
                if (ADLX_SUCCEEDED(res) && supported)
                {
                    supportedIndex = index;
                    smartAccessMemory->pVtbl->Release(smartAccessMemory);
                    oneGPU->pVtbl->Release(oneGPU);
                    break;
                }
            }
        }
        if (smartAccessMemory != NULL)
        {
            smartAccessMemory->pVtbl->Release(smartAccessMemory);
            smartAccessMemory = NULL;
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
    return supportedIndex;
}

// Display AMD SmartAccess Memory support status on a GPU
void ShowSmartAccessMemorySupport(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        printf("All GPUs doesn't support AMD SmartAccess Memory\n");
    else
        printf("The %dth GPU support AMD SmartAccess Memory\n", (index + 1));
}

// Display AMD SmartAccess Memory enabled status
void ShowSmartAccessMemoryState(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        printf("All GPUs doesn't support AMD SmartAccess Memory\n");
    else
    {
        IADLXGPU* oneGPU = NULL;
        IADLXSmartAccessMemory* smartAccessMemory = NULL;
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            res = gpuTuningService1->pVtbl->GetSmartAccessMemory(gpuTuningService1, oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool enabled = false;
                res = smartAccessMemory->pVtbl->IsEnabled(smartAccessMemory, &enabled);
                if (ADLX_SUCCEEDED(res))
                    printf("The AMD SmartAccess Memory is %s on the %dth GPU\n", (enabled ? "enabled" : "disabled"), (index + 1));
                else
                    printf("Call IsEnabled() failed\n");
            }
            else
                printf("Failed to get smartAccessMemory\n");
        }
        else
            printf("Failed to get the GPU\n");

        if (smartAccessMemory != NULL)
        {
            smartAccessMemory->pVtbl->Release(smartAccessMemory);
            smartAccessMemory = NULL;
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

// Set AMD SmartAccess Memory state
void SetSmartAccessMemoryState(IADLXGPUTuningServices1* gpuTuningService1, IADLXGPUList* gpus)
{
    auto index = GetGPUIndexSupportSAM(gpuTuningService1, gpus);
    if (index == -1)
        printf("All GPUs doesn't support AMD SmartAccess Memory\n");
    else
    {
        IADLXGPU* oneGPU = NULL;
        IADLXSmartAccessMemory* smartAccessMemory = NULL;
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, index, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            res = gpuTuningService1->pVtbl->GetSmartAccessMemory(gpuTuningService1, oneGPU, &smartAccessMemory);
            if (ADLX_SUCCEEDED(res))
            {
                adlx_bool enabled = false;
                res = smartAccessMemory->pVtbl->IsEnabled(smartAccessMemory, &enabled);
                if (ADLX_SUCCEEDED(res))
                    printf("Currently AMD SmartAccess Memory is %s on %dth GPU\n", (enabled ? "enabled" : "disabled"), (index + 1));
                else
                    printf("Call IsEnabled() failed\n");
                res = smartAccessMemory->pVtbl->SetEnabled(smartAccessMemory, !enabled);
                if (ADLX_SUCCEEDED(res))
                    printf("Set AMD SmartAccess Memory to %s for %dth GPU\n", (!enabled ? "enabled" : "disabled"), (index + 1));
                else
                    printf("Call SetEnabled() failed\n");

                // First event received quickly before SAM start
                WaitForSingleObject(SAMEvent, 2000);

                // When receive the first event, avoid calling any other ADLX method, and if any UI application is running, we must close it to avoid crashing
                // Close(application)......

                // Second event received after SAM completed, the maximum consuming time less than 20 seconds.
                WaitForSingleObject(SAMEvent, 20000);

                // Now SAM completed, we can restart the UI application, and continue to call ADLX function
                // Start(application)......

                res = smartAccessMemory->pVtbl->IsEnabled(smartAccessMemory, &enabled);
                if (ADLX_SUCCEEDED(res))
                    printf("After setting, AMD SmartAccess Memory is %s on %dth GPU\n", (enabled ? "enabled" : "disabled"), (index + 1));
                else
                    printf("Call IsEnabled() failed\n");
            }
            else
                printf("Failed to get smartAccessMemory\n");
        }
        else
            printf("Failed to get the GPU\n");

        if (smartAccessMemory != NULL)
        {
            smartAccessMemory->pVtbl->Release(smartAccessMemory);
            smartAccessMemory = NULL;
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}