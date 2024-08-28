//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainGPUAutoTuning.c
/// \brief This document describes how to control the GPU auto tuning.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IGPUAutoTuning.h"
#include "SDK/Include/IGPUTuning.h"

// ADLX Event Listener
static HANDLE g_ADLXEvent = NULL;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode, IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Check GPU Tuning is at factory status
void CheckGPUTuningIsAtFactoryStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Restore the given GPU Tuning to factory status.
void RestoreGPUTuningToFactoryStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Show GPU auto tuning support
void ShowGPUAutoTuningSupport(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Show current GPU status
void ShowCurrentGPUStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus);

// Derive from IADLXGPUAutoTuningCompleteListener
adlx_bool ADLX_STD_CALL onGPUAutoTuningCompleteEvents(IADLXGPUAutoTuningCompleteListener* pGPUAutoTuningCompleteListener,
                                                      IADLXGPUAutoTuningCompleteEvent* pGPUAutoTuningCompleteEvents);
// Start GPU auto tuning
void StartGPUAutoTuning(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus, int num);

static IADLXGPUAutoTuningCompleteListenerVtbl vtable = { &onGPUAutoTuningCompleteEvents };
static IADLXGPUAutoTuningCompleteListener completeListener = { &vtable };

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Create event
        g_ADLXEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ADLXEvent"));

        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        IADLXGPUTuningServices* gpuTuningService = NULL;
        IADLXGPUList* gpus = NULL;

        res = sys->pVtbl->GetGPUTuningServices(sys, &gpuTuningService);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU tuning services failed", 0, gpuTuningService, gpus);

        res = sys->pVtbl->GetGPUs(sys, &gpus);
        if (ADLX_FAILED(res))
            return WaitAndExit("\tGet GPU list failed", 0, gpuTuningService, gpus);

        // Show a menu with options to chose from
        MainMenu();

        // Get the choice and interpet it
        MenuControl(gpuTuningService, gpus);

        // Free
        if (gpus != NULL)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
        if (gpuTuningService != NULL)
        {
            gpuTuningService->pVtbl->Release(gpuTuningService);
            gpuTuningService = NULL;
        }
    }
    else
    {
        printf("\tg_ADLXHelp initialize failed\n");
        system("pause");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Close event
    if (g_ADLXEvent)
        CloseHandle(g_ADLXEvent);

    // Pause for user see the print out
    system("pause");

    return 0;
}

// main menu
void MainMenu()
{
    printf("\tChoose one from the following options\n");

    printf("\t->Press 1 to check GPU Tuning is at factory status\n");
    printf("\t->Press 2 to restore the given GPU Tuning to factory status\n");
    printf("\t->Press 3 to show GPU auto tuning support\n");
    printf("\t->Press 4 to show current GPU status\n");
    printf("\t->Press 5 to start Undervolt GPU tuning\n");
    printf("\t->Press 6 to start Overclock GPU tuning\n");
    printf("\t->Press 7 to start Overclock VRAM tuning\n");

    printf("\t->Press Q/q to quit\n");
    printf("\t->Press M/m to show the options again\n");
}

// menu action control
void MenuControl(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Check GPU Tuning is at factory status
        case '1':
            CheckGPUTuningIsAtFactoryStatus(gpuTuningService, gpus);
            break;

        // Restore the given GPU Tuning to factory status.
        case '2':
            RestoreGPUTuningToFactoryStatus(gpuTuningService, gpus);
            break;

        // Show GPU auto tuning support
        case '3':
            ShowGPUAutoTuningSupport(gpuTuningService, gpus);
            break;

        // Show current GPU status
        case '4':
            ShowCurrentGPUStatus(gpuTuningService, gpus);
            break;

        // Start Undervolt GPU tuning
        case '5':
        // Start Overclock GPU tuning
        case '6':
        // Start Overclock VRAM tuning
        case '7':
            StartGPUAutoTuning(gpuTuningService, gpus, num - 5);
            break;

        // Show options again
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
int WaitAndExit(const char* msg, const int retCode, IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    // Printout the message and pause for user to see it then return the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    if (gpus != NULL)
    {
        gpus->pVtbl->Release(gpus);
        gpus = NULL;
    }
    if (gpuTuningService != NULL)
    {
        gpuTuningService->pVtbl->Release(gpuTuningService);
        gpuTuningService = NULL;
    }

    // Destroy ADLX
    ADLX_RESULT res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    system("pause");
    return retCode;
}

// Check GPU Tuning is at factory status
void CheckGPUTuningIsAtFactoryStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    IADLXGPU* oneGPU = NULL;
    for (adlx_uint crt = gpus->pVtbl->Begin(gpus); crt != gpus->pVtbl->End(gpus); ++crt)
    {
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, crt, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool isFactory = false;
            res = gpuTuningService->pVtbl->IsAtFactory(gpuTuningService, oneGPU, &isFactory);
            if (ADLX_SUCCEEDED(res))
            {
                printf("\tThe %dth GPU is at factory status: %d\n", crt, isFactory);
            }
            else
            {
                printf("\tCheck the %dth GPU Tuning is at factory status failed\n", crt);
            }
        }
        else
        {
            printf("\tGet %dth GPU failed\n", crt);
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

// Restore the given GPU Tuning to factory status.
void RestoreGPUTuningToFactoryStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    IADLXGPU* oneGPU = NULL;
    for (adlx_uint crt = gpus->pVtbl->Begin(gpus); crt != gpus->pVtbl->End(gpus); ++crt)
    {
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, crt, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool isFactory = false;
            res = gpuTuningService->pVtbl->ResetToFactory(gpuTuningService, oneGPU);
            if (ADLX_FAILED(res))
                printf("\tReset the %dth GPU Tuning to factory status failed\n", crt);
            else
                printf("\tReset the %dth GPU Tuning to factory status successfully\n", crt);
        }
        else
        {
            printf("\tGet %dth GPU failed\n", crt);
        }
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

// Show GPU auto tuning support
void ShowGPUAutoTuningSupport(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    IADLXGPU* oneGPU = NULL;
    IADLXInterface* autoTuningIfc = NULL;
    IADLXGPUAutoTuning* autoTuning = NULL;
    for (adlx_uint crt = gpus->pVtbl->Begin(gpus); crt != gpus->pVtbl->End(gpus); ++crt)
    {
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, crt, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool supported = false;
            res = gpuTuningService->pVtbl->IsSupportedAutoTuning(gpuTuningService, oneGPU, &supported);
            if (ADLX_FAILED(res) || supported == false)
            {
                printf("\tThe %dth GPU doesn't supported auto tuning\n", crt);
            }
            else
            {
                res = gpuTuningService->pVtbl->GetAutoTuning(gpuTuningService, oneGPU, &autoTuningIfc);
                if (ADLX_FAILED(res) || autoTuningIfc == NULL)
                {
                    printf("\tGet auto tuning of %dth GPU failed\n", crt);
                }
                else
                {
                    res = autoTuningIfc->pVtbl->QueryInterface(autoTuningIfc, IID_IADLXGPUAutoTuning(), (void**)(&autoTuning));
                    if (ADLX_SUCCEEDED(res) && autoTuning)
                    {
                        supported = false;
                        res = autoTuning->pVtbl->IsSupportedUndervoltGPU(autoTuning, &supported);
                        printf("\tIs the %dth GPU supported undervolt: %d\n", crt, supported);
                        supported = false;
                        res = autoTuning->pVtbl->IsSupportedOverclockGPU(autoTuning, &supported);
                        printf("\tIs the %dth GPU supported overclock: %d\n", crt, supported);
                        supported = false;
                        res = autoTuning->pVtbl->IsSupportedOverclockVRAM(autoTuning, &supported);
                        printf("\tIs the %dth GPU supported overclock VRAM: %d\n", crt, supported);
                    }

                    if (autoTuning != NULL)
                    {
                        autoTuning->pVtbl->Release(autoTuning);
                        autoTuning = NULL;
                    }
                }

                if (autoTuningIfc != NULL)
                {
                    autoTuningIfc->pVtbl->Release(autoTuningIfc);
                    autoTuningIfc = NULL;
                }
            }
        }
        else
        {
            printf("\tGet %dth GPU failed\n", crt);
        }
       
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

// Show current GPU status
void ShowCurrentGPUStatus(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus)
{
    IADLXGPU* oneGPU;
    IADLXInterface* autoTuningIfc = NULL;
    IADLXGPUAutoTuning* autoTuning = NULL;
    for (adlx_uint crt = gpus->pVtbl->Begin(gpus); crt != gpus->pVtbl->End(gpus); ++crt)
    {
        ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, crt, &oneGPU);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_bool supported = false;
            res = gpuTuningService->pVtbl->IsSupportedAutoTuning(gpuTuningService, oneGPU, &supported);
            if (ADLX_FAILED(res) || supported == false)
            {
                printf("\tThe %dth GPU doesn't supported auto tuning\n", crt);
            }
            else
            {
                res = gpuTuningService->pVtbl->GetAutoTuning(gpuTuningService, oneGPU, &autoTuningIfc);
                if (ADLX_FAILED(res) || autoTuningIfc == NULL)
                {
                    printf("\tGet auto tuning of %dth GPU failed\n", crt);
                }
                else
                {
                    res = autoTuningIfc->pVtbl->QueryInterface(autoTuningIfc, IID_IADLXGPUAutoTuning(), (void**)(&autoTuning));
                    adlx_bool applied = false;
                    if (ADLX_SUCCEEDED(res) && autoTuning)
                    {
                        applied = false;
                        res = autoTuning->pVtbl->IsCurrentUndervoltGPU(autoTuning, &applied);
                        printf("\tIs the %dth GPU undervolt applied: %d\n", crt, applied);
                        applied = false;
                        res = autoTuning->pVtbl->IsCurrentOverclockGPU(autoTuning, &applied);
                        printf("\tIs the %dth GPU overclock applied: %d\n", crt, applied);
                        applied = false;
                        res = autoTuning->pVtbl->IsCurrentOverclockVRAM(autoTuning, &applied);
                        printf("\tIs the %dth GPU overclock VRAM applied: %d\n", crt, applied);
                    }

                    if (autoTuning != NULL)
                    {
                        autoTuning->pVtbl->Release(autoTuning);
                        autoTuning = NULL;
                    }
                }

                if (autoTuningIfc != NULL)
                {
                    autoTuningIfc->pVtbl->Release(autoTuningIfc);
                    autoTuningIfc = NULL;
                }
            }
        }
        else
        {
            printf("\tGet %dth GPU failed\n", crt);
        }
        
        if (oneGPU != NULL)
        {
            oneGPU->pVtbl->Release(oneGPU);
            oneGPU = NULL;
        }
    }
}

adlx_bool ADLX_STD_CALL onGPUAutoTuningCompleteEvents(IADLXGPUAutoTuningCompleteListener* pGPUAutoTuningCompleteListener,
                                                      IADLXGPUAutoTuningCompleteEvent* pGPUAutoTuningCompleteEvent)
{
    adlx_bool change = false;
    change = pGPUAutoTuningCompleteEvent->pVtbl->IsOverclockGPUCompleted(pGPUAutoTuningCompleteEvent);
    printf("\tIs overclock GPU Completed: %d\n", change);
    change = pGPUAutoTuningCompleteEvent->pVtbl->IsUndervoltGPUCompleted(pGPUAutoTuningCompleteEvent);
    printf("\tIs undervolt GPU Completed: %d\n", change);
    change = pGPUAutoTuningCompleteEvent->pVtbl->IsOverclockVRAMCompleted(pGPUAutoTuningCompleteEvent);
    printf("\tIs overclock VRAM Completed: %d\n", change);
    SetEvent(g_ADLXEvent);
    return true;
};

void StartGPUAutoTuning(IADLXGPUTuningServices* gpuTuningService, IADLXGPUList* gpus, int num)
{
    IADLXGPU* oneGPU = NULL;
    // Set the first GPU auto tuning
    ADLX_RESULT res = gpus->pVtbl->At_GPUList(gpus, 0, &oneGPU);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_bool supported = false;
        res = gpuTuningService->pVtbl->IsSupportedAutoTuning(gpuTuningService, oneGPU, &supported);
        if (ADLX_FAILED(res) || supported == false)
        {
            printf("\tThe GPU doesn't supported auto tuning\n");
        }
        else
        {
            IADLXInterface* autoTuningIfc = NULL;
            res = gpuTuningService->pVtbl->GetAutoTuning(gpuTuningService, oneGPU, &autoTuningIfc);
            if (ADLX_FAILED(res) || autoTuningIfc == NULL)
            {
                printf("\tGet auto tuning of GPU failed\n");
            }
            else
            {
                IADLXGPUAutoTuning* autoTuning = NULL;
                res = autoTuningIfc->pVtbl->QueryInterface(autoTuningIfc, IID_IADLXGPUAutoTuning(), (void**)(&autoTuning));
                if (ADLX_SUCCEEDED(res) && autoTuning)
                {
                    switch (num)
                    {
                    case '0':

                        res = autoTuning->pVtbl->IsSupportedUndervoltGPU(autoTuning, &supported);
                        if (ADLX_SUCCEEDED(res) && supported)
                        {
                            res = autoTuning->pVtbl->StartUndervoltGPU(autoTuning, &completeListener);
                            WaitForSingleObject(g_ADLXEvent, 1000);
                            ResetEvent(g_ADLXEvent);
                            if (ADLX_SUCCEEDED(res))
                                printf("\tStart undervolt GPU successfully\n");
                            else
                                printf("\tStart undervolt GPU failed\n");
                        }
                        else
                        {
                            printf("\tUndervolt GPU is not supported\n");
                        }
                        break;
                    case '1':
                        res = autoTuning->pVtbl->IsSupportedOverclockGPU(autoTuning, &supported);
                        if (ADLX_SUCCEEDED(res) && supported)
                        {
                            res = autoTuning->pVtbl->StartOverclockGPU(autoTuning, &completeListener);
                            WaitForSingleObject(g_ADLXEvent, 1000);
                            ResetEvent(g_ADLXEvent);
                            if (ADLX_SUCCEEDED(res))
                                printf("\tStart overclock GPU successfully\n");
                            else
                                printf("\tStart overclock GPU failed\n");
                        }
                        else
                        {
                            printf("\tOverclock GPU is not supported\n");
                        }
                        break;
                    case '2':
                        res = autoTuning->pVtbl->IsSupportedOverclockVRAM(autoTuning, &supported);
                        if (ADLX_SUCCEEDED(res) && supported)
                        {
                            res = autoTuning->pVtbl->StartOverclockVRAM(autoTuning, &completeListener);
                            WaitForSingleObject(g_ADLXEvent, 1000);
                            ResetEvent(g_ADLXEvent);
                            if (ADLX_SUCCEEDED(res))
                                printf("\tStart overclock VRAM successfully\n");
                            else
                                printf("\tStart overclock VRAM failed\n");
                        }
                        else
                        {
                            printf("\tOverclock VRAM is not supported\n");
                        }
                        break;
                    default:
                        break;
                    }
                }

                if (autoTuning != NULL)
                {
                    autoTuning->pVtbl->Release(autoTuning);
                    autoTuning = NULL;
                }
            }
            
            if (autoTuningIfc != NULL)
            {
                autoTuningIfc->pVtbl->Release(autoTuningIfc);
                autoTuningIfc = NULL;
            }
        }
    }
    else
    {
        printf("\tGet GPU failed\n");
    }

    if (oneGPU != NULL)
    {
        oneGPU->pVtbl->Release(oneGPU);
        oneGPU = NULL;
    }
}
