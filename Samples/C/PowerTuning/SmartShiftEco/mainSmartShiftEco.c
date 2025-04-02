//
// Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartShiftEco.c
/// \brief Demonstrates how to control AMD SmartShift Eco when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IPowerTuning1.h"
#include "SDK/Include/IApplications.h"
#include "SDK/Include/ISystem2.h"
#include "SDK/Include/IApplications.h"

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPowerTuningServices1* powerTuningServices, IADLXSmartShiftEco* smartShiftEco);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display AMD SmartShift Eco support
void ShowSmartShiftEcoSupport(IADLXSmartShiftEco* smartShiftEco);

// Display AMD SmartShift Eco enabled state
void ShowSmartShiftEcoEnabledState(IADLXSmartShiftEco* smartShiftEco);

// Set AMD SmartShift Eco enabled state
void SetSmartShiftEcoEnabledState(IADLXSmartShiftEco* smartShiftEco);

// Display AMD SmartShift Eco inactive state
void ShowSmartShiftEcoInactiveState(IADLXSmartShiftEco* smartShiftEco);

// Display AMD GPU connect support
void ShowGPUConnectSupport(IADLXPowerTuningServices1* powerTuningService);

// Use functions of GPU connect
void UseGPUConnectFunctions(IADLXPowerTuningServices1* powerTuningService, char num);

// Display GPU power state
void ShowGPUPowerState(IADLXGPU2* gpu);

// Power on a GPU
void PowerOnGPU(IADLXGPU2* gpu);

// Power off a GPU
void PowerOffGPU(IADLXGPU2* gpu);

// Abort power off a GPU
void AbortPowerOffGPU(IADLXGPU2* gpu);

// Set power control to default
void SetPowerControlToDefault(IADLXSmartShiftEco* smartShiftEco);

// Display get application list support
void ShowGetApplicationListSupport(IADLXGPU2* gpu);

// Get application list
void GetApplicationList(IADLXGPU2* gpu);

adlx_bool ADLX_STD_CALL OnGPUAppsListChanged(IADLXGPUAppsListEventListener* pThis, IADLXGPU2* pGPU, IADLXApplicationList* pApplications)
{
    // Using pGPU ...
    // Using pApplications ...

    return true;
}
static const IADLXGPUAppsListEventListenerVtbl gpuAppsListChangedCallBackVtbl = { &OnGPUAppsListChanged };
static IADLXGPUAppsListEventListener gpuAppsListChangedCallBack = { &gpuAppsListChangedCallBackVtbl };

HANDLE smartShiftEcoChangedBlockEvent = NULL;
adlx_bool ADLX_STD_CALL OnPowerTuningChanged(IADLXPowerTuningChangedListener* pThis, IADLXPowerTuningChangedEvent* pPowerTuningChangedEvent)
{
    IADLXPowerTuningChangedEvent1* pPowerTuningChangedEvent1 = NULL;
    pPowerTuningChangedEvent->pVtbl->QueryInterface(pPowerTuningChangedEvent, IID_IADLXPowerTuningChangedEvent1(), (void**)(&pPowerTuningChangedEvent1));
    if (pPowerTuningChangedEvent1->pVtbl->IsSmartShiftEcoChanged(pPowerTuningChangedEvent1))
    {
        printf("\tSmartShiftEcoChanged\n");
    }
    pPowerTuningChangedEvent1->pVtbl->Release(pPowerTuningChangedEvent1);
    SetEvent(smartShiftEcoChangedBlockEvent);
    return true;
}
static const IADLXPowerTuningChangedListenerVtbl smartShiftecochangedcallbackVtbl = { &OnPowerTuningChanged };
static IADLXPowerTuningChangedListener smartShiftEcoChangedCallBack = { &smartShiftecochangedcallbackVtbl };


int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get IADLXSystem1 interface via IADLXSystem::QueryInterface
        IADLXSystem2* system2 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem2(), (void**)(&system2));
        if (ADLX_SUCCEEDED(res))
        {
            smartShiftEcoChangedBlockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            // Add GPU applications list event listener
            IADLXGPUAppsListChangedHandling* appsListHandle = NULL;
            res = system2->pVtbl->GetGPUAppsListChangedHandling(system2, &appsListHandle);
            ADLX_RESULT addListenerResult1 = ADLX_FAIL;
            if (ADLX_SUCCEEDED(res))
                addListenerResult1 = appsListHandle->pVtbl->AddGPUAppsListEventListener(appsListHandle, &gpuAppsListChangedCallBack);
            // Get power tuning service 
            IADLXPowerTuningServices* powerTuningService = NULL;
            res = system2->pVtbl->GetPowerTuningServices(system2, &powerTuningService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get power tuning service 1
                IADLXPowerTuningServices1* powerTuningService1 = NULL;
                res = powerTuningService->pVtbl->QueryInterface(powerTuningService, IID_IADLXPowerTuningServices1(), (void**)(&powerTuningService1));
                if (ADLX_SUCCEEDED(res))
                {
                    // Add power tuning changed listener
                    IADLXPowerTuningChangedHandling* powerTuningChangedHandle = NULL;
                    res = powerTuningService1->pVtbl->GetPowerTuningChangedHandling(powerTuningService1, &powerTuningChangedHandle);
                    auto addListenerResult2 = ADLX_FAIL;
                    if (ADLX_SUCCEEDED(res))
                        addListenerResult2 = powerTuningChangedHandle->pVtbl->AddPowerTuningEventListener(powerTuningChangedHandle, &smartShiftEcoChangedCallBack);
                    // Get AMD SmartShift Eco interface
                    IADLXSmartShiftEco* smartShiftEco = NULL;
                    res = powerTuningService1->pVtbl->GetSmartShiftEco(powerTuningService1, &smartShiftEco);
                    if (ADLX_SUCCEEDED(res))
                    {
                        // Display main menu options
                        MainMenu();
                        // Get and execute the choice
                        MenuControl(powerTuningService1, smartShiftEco);
                    }
                    else
                        printf("Failed to get AMD SmartShift Eco interface\n");
                    // Remove power tuning changed listener
                    if (ADLX_SUCCEEDED(addListenerResult2))
                        powerTuningChangedHandle->pVtbl->RemovePowerTuningEventListener(powerTuningChangedHandle, &smartShiftEcoChangedCallBack);
                    if (smartShiftEco != NULL)
                    {
                        smartShiftEco->pVtbl->Release(smartShiftEco);
                        smartShiftEco= NULL;
                    }
                    if (powerTuningChangedHandle != NULL)
                    {
                        powerTuningChangedHandle->pVtbl->Release(powerTuningChangedHandle);
                        powerTuningChangedHandle= NULL;
                    }
                }
                else
                    printf("Failed to get power tuning service 1\n");
                if (powerTuningService1 != NULL)
                {
                    powerTuningService1->pVtbl->Release(powerTuningService1);
                    powerTuningService1= NULL;
                }
            }
            else
                printf("Failed to get power tuning service\n");
            // Remove GPU applications list event listener
            if (ADLX_SUCCEEDED(addListenerResult1))
                appsListHandle->pVtbl->RemoveGPUAppsListEventListener(appsListHandle, &gpuAppsListChangedCallBack);
            if (powerTuningService != NULL)
            {
                powerTuningService->pVtbl->Release(powerTuningService);
                powerTuningService = NULL;
            }
            if (appsListHandle != NULL)
            {
                appsListHandle->pVtbl->Release(appsListHandle);
                appsListHandle = NULL;
            }
        }
        else
            printf("Failed to get IADLXSystem2\n");
        if (system2 != NULL)
        {
            system2->pVtbl->Release(system2);
            system2 = NULL;
        }
    }
    else
        return WaitAndExit("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");
    printf("\t->Press 1 to display AMD SmartShift Eco support\n");
    printf("\t->Press 2 to display AMD SmartShift Eco enabled state\n");
    printf("\t->Press 3 to set AMD SmartShift Eco enabled state\n");
    printf("\t->Press 4 to display AMD SmartShift Eco inactive state\n");
    printf("\t->Press 5 to display AMD GPU connect support\n");
    printf("\t->Press 6 to display GPU power state\n");
    printf("\t->Press 7 to power on a GPU\n");
    printf("\t->Press 8 to power off a GPU\n");
    printf("\t->Press 9 to abort power off a GPU\n");
    printf("\t->Press A to set power control to defaul\n");
    printf("\t->Press B to display get application list support\n");
    printf("\t->Press C to get application list\n");
    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXPowerTuningServices1* powerTuningServices, IADLXSmartShiftEco* smartShiftEco)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        case '1':  // Display AMD SmartShift Eco support
            ShowSmartShiftEcoSupport(smartShiftEco);
            break;

        case '2':  // Display AMD SmartShift Eco enabled state
            ShowSmartShiftEcoEnabledState(smartShiftEco);
            break;

        case '3':  // Set AMD SmartShift Eco enabled state
            SetSmartShiftEcoEnabledState(smartShiftEco);
            break;

        case '4':  // Display AMD SmartShift Eco inactive state
            ShowSmartShiftEcoInactiveState(smartShiftEco);
            break;

        case '5':  // Display AMD GPU connect support
            ShowGPUConnectSupport(powerTuningServices);
            break;

        case 'A':  // Set power control to default
            SetPowerControlToDefault(smartShiftEco);
            break;

        case '6':
        case '7':
        case '8':
        case '9':
        case 'B':
        case 'C':
            UseGPUConnectFunctions(powerTuningServices, num);
            break;

        case 'm':  // Display menu options
        case 'M':
            MainMenu();
            break;

        default:
            break;
        }
    }
}

int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

// Display AMD SmartShift Eco support
void ShowSmartShiftEcoSupport(IADLXSmartShiftEco* smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->pVtbl->IsSupported(smartShiftEco, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIs AMD SmartShift Eco supported: %d\n", supported);
}

// Display AMD SmartShift Eco enabled state
void ShowSmartShiftEcoEnabledState(IADLXSmartShiftEco* smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->pVtbl->IsSupported(smartShiftEco, &supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->pVtbl->IsEnabled(smartShiftEco, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tIs AMD SmartShift Eco enabled: %d\n", enabled);
    }
}

// Set AMD SmartShift Eco enabled state
void SetSmartShiftEcoEnabledState(IADLXSmartShiftEco* smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->pVtbl->IsSupported(smartShiftEco, &supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->pVtbl->IsEnabled(smartShiftEco, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tCurrent AMD SmartShift Eco enable state is: %d\n", enabled);
        res = smartShiftEco->pVtbl->SetEnabled(smartShiftEco, !enabled);
        if (ADLX_SUCCEEDED(res))
        {
            WaitForSingleObject(smartShiftEcoChangedBlockEvent, 5000);
            ResetEvent(smartShiftEcoChangedBlockEvent);
            printf("\tSet AMD SmartShift Eco enabled state to: %d\n", !enabled);
        }
        res = smartShiftEco->pVtbl->IsEnabled(smartShiftEco, &enabled);
        if (ADLX_SUCCEEDED(res))
            printf("\tAfter set, the AMD SmartShift Eco enable state is: %d\n", enabled);
    }
}

// Display AMD SmartShift Eco inactive state
void ShowSmartShiftEcoInactiveState(IADLXSmartShiftEco* smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->pVtbl->IsSupported(smartShiftEco, &supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->pVtbl->IsEnabled(smartShiftEco, &enabled);
        if (ADLX_SUCCEEDED(res) && enabled)
        {
            adlx_bool inactive = false;
            ADLX_RESULT res = smartShiftEco->pVtbl->IsInactive(smartShiftEco, &inactive);
            printf("\tIs AMD SmartShift Eco inactive: %d\n", inactive);
            if (inactive)
            {
                ADLX_SMARTSHIFT_ECO_INACTIVE_REASON reason = INACTIVE_REASON_UNKNOWN;
                ADLX_RESULT res = smartShiftEco->pVtbl->GetInactiveReason(smartShiftEco, &reason);
                printf("\tIs AMD SmartShift Eco inactive reason: %d\n", reason);
            }
        }
    }
}

// Display AMD GPU connect support
void ShowGPUConnectSupport(IADLXPowerTuningServices1* powerTuningService)
{
    adlx_bool supported = false;
    ADLX_RESULT res = powerTuningService->pVtbl->IsGPUConnectSupported(powerTuningService, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIs GPU connect supported: %d\n", supported);
}

// Use functions of GPU connect
void UseGPUConnectFunctions(IADLXPowerTuningServices1* powerTuningService, char num)
{
    adlx_bool supported = false;
    ADLX_RESULT res = powerTuningService->pVtbl->IsGPUConnectSupported(powerTuningService, &supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        IADLXGPU2List* gpuList = NULL;
        res = powerTuningService->pVtbl->GetGPUConnectGPUs(powerTuningService, &gpuList);
        if (ADLX_SUCCEEDED(res) && !gpuList->pVtbl->Empty(gpuList))
        {
            // Use the first GPU
            IADLXGPU2* gpu = NULL;
            res = gpuList->pVtbl->At_GPU2List(gpuList, gpuList->pVtbl->Begin(gpuList), &gpu);
            if (ADLX_SUCCEEDED(res))
            {
                switch (num)
                {
                case '6':  // Display GPU power state
                    ShowGPUPowerState(gpu);
                    break;

                case '7':  // Power on a GPU
                    PowerOnGPU(gpu);
                    break;

                case '8':  // Power off a GPU
                    PowerOffGPU(gpu);
                    break;

                case '9':  // Abort power off a GPU
                    AbortPowerOffGPU(gpu);
                    break;

                case 'B':  // Display get application list support
                    ShowGetApplicationListSupport(gpu);
                    break;

                case 'C':  // Get application list
                    GetApplicationList(gpu);
                    break;

                default:
                    break;
                }

            }
            if (gpu != NULL)
            {
                gpu->pVtbl->Release(gpu);
                gpu = NULL;
            }
        }
        else
            printf("\tNot found GPU support GPU connect\n");
        if (gpuList != NULL)
        {
            gpuList->pVtbl->Release(gpuList);
            gpuList = NULL;
        }
    }
    else
        printf("\tGPU connect is not supported\n");
}

// Display GPU power state
void ShowGPUPowerState(IADLXGPU2* gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->pVtbl->IsPowerOff(gpu, &state);
    if (ADLX_SUCCEEDED(res))
        printf("\tIs GPU power off: %d\n", state);
}

// Power on a GPU
void PowerOnGPU(IADLXGPU2* gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->pVtbl->IsPowerOff(gpu, &state);
    if (ADLX_SUCCEEDED(res))
        printf("\tCurrent the GPU power state is: %s\n", (state ? "OFF" : "ON"));
    res = gpu->pVtbl->PowerOn(gpu);
    if (ADLX_SUCCEEDED(res))
        printf("\tPower on the GPU\n");
    res = gpu->pVtbl->IsPowerOff(gpu, &state);
    if (ADLX_SUCCEEDED(res))
        printf("\tAfter set, the GPU power state is: %s\n", (state ? "OFF" : "ON"));
}

adlx_bool ADLX_STD_CALL OnGPUConnectChanged(IADLXGPUConnectChangedListener* pThis, IADLXGPUConnectChangedEvent* pGPUConnectChangedEvent)
{
    if (pGPUConnectChangedEvent->pVtbl->IsGPUPowerChanged(pGPUConnectChangedEvent))
        printf("\tGPU power changed\n");
    if (pGPUConnectChangedEvent->pVtbl->IsGPUAppsListChanged(pGPUConnectChangedEvent))
    {
        printf("\tGPU applications list changed\n");
        IADLXGPU2* gpu = NULL;
        ADLX_RESULT res = pGPUConnectChangedEvent->pVtbl->GetGPU(pGPUConnectChangedEvent, &gpu);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXApplicationList* appList = NULL;
            res = gpu->pVtbl->GetApplications(gpu, &appList);
            if (ADLX_SUCCEEDED(res))
            {
                for (adlx_uint it = appList->pVtbl->Begin(appList); it != appList->pVtbl->End(appList); ++it)
                {
                    IADLXApplication* app = NULL;
                    res = appList->pVtbl->At_ApplicationList(appList, it, &app);
                    if (ADLX_SUCCEEDED(res))
                    {
                        adlx_ulong pid = 0;
                        res = app->pVtbl->ProcessID(app, &pid);
                        if (ADLX_SUCCEEDED(res))
                            printf("\tThe process ID of the process running on the GPU is: %d\n", pid);

                        const wchar_t* name = NULL;
                        res = app->pVtbl->Name(app, &name);
                        if (ADLX_SUCCEEDED(res))
                            printf("\tThe name of the process running on the GPU is: %ls\n", name);

                        const wchar_t* fullPath = NULL;
                        res = app->pVtbl->Name(app, &fullPath);
                        if (ADLX_SUCCEEDED(res))
                            printf("\tThe full path of the process running on the GPU is: %ls\n", fullPath);

                        ADLX_APP_GPU_DEPENDENCY type = APP_GPU_UNKNOWN;
                        res = app->pVtbl->GPUDependencyType(app, &type);
                        if (ADLX_SUCCEEDED(res))
                        {
                            if (type == APP_GPU_BOUND)
                                printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_BOUND\n");
                            else if (type == APP_GPU_NOT_BOUND)
                                printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_NOT_BOUND\n");
                            else
                                printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_UNKNOWN\n");
                        }
                    }
                    if (app != NULL)
                    {
                        app->pVtbl->Release(app);
                        app = NULL;
                    }
                }
            }
            if (appList != NULL)
            {
                appList->pVtbl->Release(appList);
                appList = NULL;
            }
        }
        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }
    }
    ADLX_RESULT res = ADLX_FAIL;
    if (pGPUConnectChangedEvent->pVtbl->IsGPUPowerChangeError(pGPUConnectChangedEvent, &res))
    {
        if (res == ADLX_TIMEOUT_OPERATION)
            printf("\tGPU power change error, timeout operation\n");
        else
            printf("\tGPU power change error, result is: %d\n", res);
    }

    return true;
}

static const IADLXGPUConnectChangedListenerVtbl gpuConnectChangedListenerVtbl = { &OnGPUConnectChanged };
static IADLXGPUConnectChangedListener gpuConnectChangedListener = { &gpuConnectChangedListenerVtbl };

// Power off a GPU
void PowerOffGPU(IADLXGPU2* gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->pVtbl->IsPowerOff(gpu , &state);
    if (ADLX_SUCCEEDED(res))
        printf("\tCurrent the GPU power state is: %s\n", (state ? "OFF" : "ON"));

    res = gpu->pVtbl->StartPowerOff(gpu, &gpuConnectChangedListener, 10000);
    if (ADLX_SUCCEEDED(res))
        printf("\tPower off the GPU\n");
    else if (res == ADLX_GPU_IN_USE)
    {
        printf("\tStart power off the GPU, but GPU is in use, wait for 10 seconds\n");
        printf("\tPress 9 can abort power off GPU during this time\n");
    }
}

// Abort power off a GPU
void AbortPowerOffGPU(IADLXGPU2* gpu)
{
    ADLX_RESULT res = gpu->pVtbl->AbortPowerOff(gpu);
    if (ADLX_SUCCEEDED(res))
        printf("\tAbort power off GPU successfully\n");
}

// Set power control to default
void SetPowerControlToDefault(IADLXSmartShiftEco* smartShiftEco)
{
    // The default power control policy is to enable AMD SmartShift Eco
    ADLX_RESULT res = smartShiftEco->pVtbl->SetEnabled(smartShiftEco, true);
    if (ADLX_SUCCEEDED(res))
        printf("\tSet Power control to default\n");
}

// Display get application list support
void ShowGetApplicationListSupport(IADLXGPU2* gpu)
{
    adlx_bool supported = false;
    ADLX_RESULT res = gpu->pVtbl->IsSupportedApplicationList(gpu, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIs application list Supported: %d\n", supported);
}

// Get application list
void GetApplicationList(IADLXGPU2* gpu)
{
    adlx_bool supported = false;
    ADLX_RESULT res = gpu->pVtbl->IsSupportedApplicationList(gpu, &supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        IADLXApplicationList* appList = NULL;
        res = gpu->pVtbl->GetApplications(gpu, &appList);
        if (ADLX_SUCCEEDED(res))
        {
            for (adlx_uint it = appList->pVtbl->Begin(appList); it != appList->pVtbl->End(appList); ++it)
            {
                IADLXApplication* app = NULL;
                res = appList->pVtbl->At_ApplicationList(appList, it, &app);
                if (ADLX_SUCCEEDED(res))
                {
                    adlx_ulong pid = 0;
                    res = app->pVtbl->ProcessID(app, &pid);
                    if (ADLX_SUCCEEDED(res))
                        printf("\tThe process ID of the process running on the GPU is: %d\n", pid);

                    const wchar_t* name = NULL;
                    res = app->pVtbl->Name(app, &name);
                    if (ADLX_SUCCEEDED(res))
                        printf("\tThe name of the process running on the GPU is: %ls\n", name);

                    const wchar_t* fullPath = NULL;
                    res = app->pVtbl->Name(app, &fullPath);
                    if (ADLX_SUCCEEDED(res))
                        printf("\tThe full path of the process running on the GPU is: %ls\n", fullPath);

                    ADLX_APP_GPU_DEPENDENCY type = APP_GPU_UNKNOWN;
                    res = app->pVtbl->GPUDependencyType(app, &type);
                    if (ADLX_SUCCEEDED(res))
                    {
                        if (type == APP_GPU_BOUND)
                            printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_BOUND\n");
                        else if (type == APP_GPU_NOT_BOUND)
                            printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_NOT_BOUND\n");
                        else
                            printf("\tThe GPU dependency type of the process running on the GPU is: APP_GPU_UNKNOWN\n");
                    }
                }
                if (app != NULL)
                {
                    app->pVtbl->Release(app);
                    app = NULL;
                }
            }
        }
        if (appList != NULL)
        {
            appList->pVtbl->Release(appList);
            appList = NULL;
        }
    }
}