//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSmartShiftEco.cpp
/// \brief Demonstrates how to control AMD SmartShift Eco when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IPowerTuning1.h"
#include "SDK/Include/IApplications.h"
#include "SDK/Include/ISystem2.h"
#include "SDK/Include/IApplications.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Main menu
void MainMenu();

// Menu action control
void MenuControl(IADLXPowerTuningServices1Ptr powerTuningServices, IADLXSmartShiftEcoPtr smartShiftEco);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display AMD SmartShift Eco support
void ShowSmartShiftEcoSupport(IADLXSmartShiftEcoPtr smartShiftEco);

// Display AMD SmartShift Eco enabled state
void ShowSmartShiftEcoEnabledState(IADLXSmartShiftEcoPtr smartShiftEco);

// Set AMD SmartShift Eco enabled state
void SetSmartShiftEcoEnabledState(IADLXSmartShiftEcoPtr smartShiftEco);

// Display AMD SmartShift Eco active state
void ShowSmartShiftEcoInactiveState(IADLXSmartShiftEcoPtr smartShiftEco);

// Display AMD GPU connect support
void ShowGPUConnectSupport(IADLXPowerTuningServices1Ptr powerTuningService);

// Use functions of GPU connect
void UseGPUConnectFunctions(IADLXPowerTuningServices1Ptr powerTuningService, char num);

// Display GPU power state
void ShowGPUPowerState(IADLXGPU2Ptr gpu);

// Power on a GPU
void PowerOnGPU(IADLXGPU2Ptr gpu);

// Power off a GPU
void PowerOffGPU(IADLXGPU2Ptr gpu);

// Abort power off a GPU
void AbortPowerOffGPU(IADLXGPU2Ptr gpu);

// Set power control to default
void SetPowerControlToDefault(IADLXSmartShiftEcoPtr smartShiftEco);

// Display get application list support
void ShowGetApplicationListSupport(IADLXGPU2Ptr gpu);

// Get application list
void GetApplicationList(IADLXGPU2Ptr gpu);

class GPUAppsListChangedCallBack : public IADLXGPUAppsListEventListener
{
public:
    adlx_bool ADLX_STD_CALL OnGPUAppsListChanged(IADLXGPU2* pGPU, IADLXApplicationList* pApplications)
    {
        // Using pGPU ...
        // Using pApplications ...

        return true;
    }
};

HANDLE smartShiftEcoChangedBlockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

class SmartShiftEcoChangedCallBack : public IADLXPowerTuningChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnPowerTuningChanged(IADLXPowerTuningChangedEvent* pPowerTuningChangedEvent)
    {
        IADLXPowerTuningChangedEvent1Ptr pPowerTuningChangedEvent1 = nullptr;
        pPowerTuningChangedEvent->QueryInterface(IADLXPowerTuningChangedEvent1::IID(), reinterpret_cast<void**>(&pPowerTuningChangedEvent1));
        if (pPowerTuningChangedEvent1->IsSmartShiftEcoChanged())
        {
            std::cout << "\tSmartShiftEcoChanged" << std::endl;
        }
        SetEvent(smartShiftEcoChangedBlockEvent);
        return true;
    }
};

int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get IADLXSystem1 interface via IADLXSystem::QueryInterface
        IADLXSystem2Ptr system2;
        res = g_ADLXHelp.GetSystemServices()->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));
        if (ADLX_SUCCEEDED(res))
        {
            // Add GPU applications list event listener
            IADLXGPUAppsListChangedHandlingPtr appsListHandle;
            res = system2->GetGPUAppsListChangedHandling(&appsListHandle);
            IADLXGPUAppsListEventListener* gpuAppsListChangedCallBack = new GPUAppsListChangedCallBack{};
            auto addListenerResult1 = ADLX_FAIL;
            if (ADLX_SUCCEEDED(res))
                addListenerResult1 = appsListHandle->AddGPUAppsListEventListener(gpuAppsListChangedCallBack);
            // Get power tuning service 
            IADLXPowerTuningServicesPtr powerTuningService;
            res = system2->GetPowerTuningServices(&powerTuningService);
            if (ADLX_SUCCEEDED(res))
            {
                // Get power tuning service 1
                IADLXPowerTuningServices1Ptr powerTuningService1;
                res = powerTuningService->QueryInterface(IADLXPowerTuningServices1::IID(), reinterpret_cast<void**>(&powerTuningService1));
                if (ADLX_SUCCEEDED(res))
                {
                    // Add power tuning changed listener
                    IADLXPowerTuningChangedHandlingPtr powerTuningChangedHandle;
                    res = powerTuningService1->GetPowerTuningChangedHandling(&powerTuningChangedHandle);
                    IADLXPowerTuningChangedListener* smartShiftEcoChangedCallBack = new SmartShiftEcoChangedCallBack{};
                    auto addListenerResult2 = ADLX_FAIL;
                    if (ADLX_SUCCEEDED(res))
                        addListenerResult2 = powerTuningChangedHandle->AddPowerTuningEventListener(smartShiftEcoChangedCallBack);
                    // Get AMD SmartShift Eco interface
                    IADLXSmartShiftEcoPtr smartShiftEco;
                    res = powerTuningService1->GetSmartShiftEco(&smartShiftEco);
                    if (ADLX_SUCCEEDED(res))
                    {
                        // Display main menu options
                        MainMenu();
                        // Get and execute the choice
                        MenuControl(powerTuningService1, smartShiftEco);
                    }
                    else
                        std::cout << "Failed to get AMD SmartShift Eco interface" << std::endl;
                    // Remove power tuning changed listener
                    if (ADLX_SUCCEEDED(addListenerResult2))
                        powerTuningChangedHandle->RemovePowerTuningEventListener(smartShiftEcoChangedCallBack);
                    delete smartShiftEcoChangedCallBack;
                    smartShiftEcoChangedCallBack = nullptr;
                }
                else
                    std::cout << "Failed to get power tuning service 1" << std::endl;
            }
            else
                std::cout << "Failed to get power tuning service" << std::endl;
            // Remove GPU applications list event listener
            if (ADLX_SUCCEEDED(addListenerResult1))
                appsListHandle->RemoveGPUAppsListEventListener(gpuAppsListChangedCallBack);
            delete gpuAppsListChangedCallBack;
            gpuAppsListChangedCallBack = nullptr;
        }
        else
            std::cout << "Failed to get IADLXSystem2" << std::endl;
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

void MainMenu()
{
    std::cout << "\tChoose from the following options:" << std::endl;
    std::cout << "\t->Press 1 to display AMD SmartShift Eco support" << std::endl;
    std::cout << "\t->Press 2 to display AMD SmartShift Eco enabled state" << std::endl;
    std::cout << "\t->Press 3 to set AMD SmartShift Eco enabled state" << std::endl;
    std::cout << "\t->Press 4 to display AMD SmartShift Eco inactive state" << std::endl;
    std::cout << "\t->Press 5 to display AMD GPU connect support" << std::endl;
    std::cout << "\t->Press 6 to display GPU power state" << std::endl;
    std::cout << "\t->Press 7 to power on a GPU" << std::endl;
    std::cout << "\t->Press 8 to power off a GPU" << std::endl;
    std::cout << "\t->Press 9 to abort power off a GPU" << std::endl;
    std::cout << "\t->Press A to set power control to default" << std::endl;
    std::cout << "\t->Press B to display get application list support" << std::endl;
    std::cout << "\t->Press C to get application list" << std::endl;
    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(IADLXPowerTuningServices1Ptr powerTuningServices, IADLXSmartShiftEcoPtr smartShiftEco)
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
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display AMD SmartShift Eco support
void ShowSmartShiftEcoSupport(IADLXSmartShiftEcoPtr smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIs AMD SmartShift Eco supported: " << supported << std::endl;
}

// Display AMD SmartShift Eco enabled state
void ShowSmartShiftEcoEnabledState(IADLXSmartShiftEcoPtr smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tIs AMD SmartShift Eco enabled: " << enabled << std::endl;
    }
}

// Set AMD SmartShift Eco enabled state
void SetSmartShiftEcoEnabledState(IADLXSmartShiftEcoPtr smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tCurrent AMD SmartShift Eco enable state is: " << enabled << std::endl;
        res = smartShiftEco->SetEnabled(!enabled);
        if (ADLX_SUCCEEDED(res))
        {
            WaitForSingleObject(smartShiftEcoChangedBlockEvent, 5000);
            ResetEvent(smartShiftEcoChangedBlockEvent);
            std::cout << "\tSet AMD SmartShift Eco enabled state to: " << !enabled << std::endl;
        }
        res = smartShiftEco->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res))
            std::cout << "\tAfter set, the AMD SmartShift Eco enable state is: " << enabled << std::endl;
    }
}

// Display AMD SmartShift Eco inactive state
void ShowSmartShiftEcoInactiveState(IADLXSmartShiftEcoPtr smartShiftEco)
{
    adlx_bool supported = false;
    ADLX_RESULT res = smartShiftEco->IsSupported(&supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        adlx_bool enabled = false;
        ADLX_RESULT res = smartShiftEco->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(res) && enabled)
        {
            adlx_bool inactive = false;
            ADLX_RESULT res = smartShiftEco->IsInactive(&inactive);
            std::cout << "\tIs AMD SmartShift Eco inactive: " << inactive << std::endl;
            if (inactive)
            {
                ADLX_SMARTSHIFT_ECO_INACTIVE_REASON reason = INACTIVE_REASON_UNKNOWN;
                ADLX_RESULT res = smartShiftEco->GetInactiveReason(&reason);
                if (ADLX_SUCCEEDED(res))
                {
                    std::cout << "\tAMD SmartShift Eco inactive reason: " << reason << std::endl;
                }
            }
        }
    }
}

// Display AMD GPU connect support
void ShowGPUConnectSupport(IADLXPowerTuningServices1Ptr powerTuningService)
{
    adlx_bool supported = false;
    ADLX_RESULT res = powerTuningService->IsGPUConnectSupported(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIs GPU connect supported: " << supported << std::endl;
}

// Use functions of GPU connect
void UseGPUConnectFunctions(IADLXPowerTuningServices1Ptr powerTuningService, char num)
{
    adlx_bool supported = false;
    ADLX_RESULT res = powerTuningService->IsGPUConnectSupported(&supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        IADLXGPU2ListPtr gpuList = nullptr;
        res = powerTuningService->GetGPUConnectGPUs(&gpuList);
        if (ADLX_SUCCEEDED(res) && !gpuList->Empty())
        {
            // Use the first GPU
            IADLXGPU2Ptr gpu = nullptr;
            res = gpuList->At(gpuList->Begin(), &gpu);
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
        }
        else
            std::cout << "\tNot found GPU support GPU connect" << std::endl;
    }
    else
        std::cout << "\tGPU connect is not supported" << std::endl;
}

// Display GPU power state
void ShowGPUPowerState(IADLXGPU2Ptr gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->IsPowerOff(&state);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIs GPU power off: " << state << std::endl;
}

// Power on a GPU
void PowerOnGPU(IADLXGPU2Ptr gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->IsPowerOff(&state);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tCurrent the GPU power state is: " << (state ? "OFF" : "ON") << std::endl;
    res = gpu->PowerOn();
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tPower on the GPU" << std::endl;
    res = gpu->IsPowerOff(&state);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tAfter set, the GPU power state is: " << (state ? "OFF" : "ON") << std::endl;
}

class GPUConnectChangedCallBack : public IADLXGPUConnectChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnGPUConnectChanged(IADLXGPUConnectChangedEvent* pGPUConnectChangedEvent)
    {
        if (pGPUConnectChangedEvent->IsGPUPowerChanged())
            std::cout << "\tGPU power changed" << std::endl;
        if (pGPUConnectChangedEvent->IsGPUAppsListChanged())
        {
            std::cout << "\tGPU applications list changed" << std::endl;
            IADLXGPU2Ptr gpu;
            ADLX_RESULT res = pGPUConnectChangedEvent->GetGPU(&gpu);
            if (ADLX_SUCCEEDED(res))
            {
                IADLXApplicationListPtr appList;
                res = gpu->GetApplications(&appList);
                if (ADLX_SUCCEEDED(res))
                {
                    for (auto it = appList->Begin(); it != appList->End(); ++it)
                    {
                        IADLXApplicationPtr app;
                        res = appList->At(it, &app);
                        if (ADLX_SUCCEEDED(res))
                        {
                            adlx_ulong pid = 0;
                            res = app->ProcessID(&pid);
                            if (ADLX_SUCCEEDED(res))
                                std::cout << "\tThe process ID of the process running on the GPU is: " << pid << std::endl;

                            const wchar_t* name = nullptr;
                            res = app->Name(&name);
                            if (ADLX_SUCCEEDED(res))
                                std::cout << "\tThe name of the process running on the GPU is: " << name << std::endl;

                            const wchar_t* fullPath = nullptr;
                            res = app->FullPath(&fullPath);
                            if (ADLX_SUCCEEDED(res))
                                std::cout << "\tThe full path of the process running on the GPU is: " << fullPath << std::endl;

                            ADLX_APP_GPU_DEPENDENCY type = ADLX_APP_GPU_DEPENDENCY::APP_GPU_UNKNOWN;
                            res = app->GPUDependencyType(&type);
                            if (ADLX_SUCCEEDED(res))
                            {
                                if (type == ADLX_APP_GPU_DEPENDENCY::APP_GPU_BOUND)
                                    std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_BOUND" << std::endl;
                                else if (type == ADLX_APP_GPU_DEPENDENCY::APP_GPU_NOT_BOUND)
                                    std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_NOT_BOUND" << std::endl;
                                else
                                    std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_UNKNOWN" << std::endl;
                            }
                        }
                    }
                }
            }
        }
        ADLX_RESULT res = ADLX_FAIL;
        if (pGPUConnectChangedEvent->IsGPUPowerChangeError(&res))
        {
            if (res == ADLX_TIMEOUT_OPERATION)
                std::cout << "\tGPU power change error, timeout operation" << std::endl;
            else
                std::cout << "\tGPU power change error, result is: " << res << std::endl;
        }

        return true;
    }
};

static GPUConnectChangedCallBack callBack;

// Power off a GPU
void PowerOffGPU(IADLXGPU2Ptr gpu)
{
    adlx_bool state = false;
    ADLX_RESULT res = gpu->IsPowerOff(&state);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tCurrent the GPU power state is: " << (state ? "OFF" : "ON") << std::endl;

    res = gpu->StartPowerOff(&callBack, 10000);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tPower off the GPU" << std::endl;
    else if (res == ADLX_GPU_IN_USE)
    {
        std::cout << "\tStart power off the GPU, but GPU is in use, wait for 10 seconds" << std::endl;
        std::cout << "\tPress 9 can abort power off GPU during this time" << std::endl;
    }
}

// Abort power off a GPU
void AbortPowerOffGPU(IADLXGPU2Ptr gpu)
{
    ADLX_RESULT res = gpu->AbortPowerOff();
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tAbort power off GPU successfully" << std::endl;
}

// Set power control to default
void SetPowerControlToDefault(IADLXSmartShiftEcoPtr smartShiftEco)
{
    // The default power control policy is to enable AMD SmartShift Eco
    ADLX_RESULT res = smartShiftEco->SetEnabled(true);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tSet Power control to default" << std::endl;
}

// Display get application list support
void ShowGetApplicationListSupport(IADLXGPU2Ptr gpu)
{
    adlx_bool supported = false;
    ADLX_RESULT res = gpu->IsSupportedApplicationList(&supported);
    if (ADLX_SUCCEEDED(res))
        std::cout << "\tIs application list Supported: " << supported << std::endl;
}

// Get application list
void GetApplicationList(IADLXGPU2Ptr gpu)
{
    adlx_bool supported = false;
    ADLX_RESULT res = gpu->IsSupportedApplicationList(&supported);
    if (ADLX_SUCCEEDED(res) && supported)
    {
        IADLXApplicationListPtr appList;
        res = gpu->GetApplications(&appList);
        if (ADLX_SUCCEEDED(res))
        {
            for (auto it = appList->Begin(); it != appList->End(); ++it)
            {
                IADLXApplicationPtr app;
                res = appList->At(it, &app);
                if (ADLX_SUCCEEDED(res))
                {
                    adlx_ulong pid = 0;
                    res = app->ProcessID(&pid);
                    if (ADLX_SUCCEEDED(res))
                        std::cout << "\tThe process ID of the process running on the GPU is: " << pid << std::endl;

                    const wchar_t* name = nullptr;
                    res = app->Name(&name);
                    if (ADLX_SUCCEEDED(res))
                        std::cout << "\tThe name of the process running on the GPU is: " << name << std::endl;

                    const wchar_t* fullPath = nullptr;
                    res = app->FullPath(&fullPath);
                    if (ADLX_SUCCEEDED(res))
                        std::cout << "\tThe full path of the process running on the GPU is: " << fullPath << std::endl;

                    ADLX_APP_GPU_DEPENDENCY type = ADLX_APP_GPU_DEPENDENCY::APP_GPU_UNKNOWN;
                    res = app->GPUDependencyType(&type);
                    if (ADLX_SUCCEEDED(res))
                    {
                        if (type == ADLX_APP_GPU_DEPENDENCY::APP_GPU_BOUND)
                            std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_BOUND" << std::endl;
                        else if (type == ADLX_APP_GPU_DEPENDENCY::APP_GPU_NOT_BOUND)
                            std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_NOT_BOUND" << std::endl;
                        else
                            std::cout << "\tThe GPU dependency type of the process running on the GPU is: APP_GPU_UNKNOWN" << std::endl;
                    }
                }
            }
        }
    }
}