//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainSync3DReceive.cpp
/// \brief Demonstrates how to receive notifications of changes in 3D settings using ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/I3DSettings.h"
#include "conio.h"
#include <iostream>
#include <string>
#include <map>
#include <thread>

// Use ADLX namespace.
using namespace adlx;

// ADLXHelper instance.
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// Block event to verify call back.
HANDLE blockEvent = nullptr;
HANDLE quitEvent = nullptr;

// AnisotropicFiltering level map
static const std::map<ADLX_ANISOTROPIC_FILTERING_LEVEL, const char*> levelMap =
{
    {AF_LEVEL_INVALID, "Invalid"},
    {AF_LEVEL_X2, "2X"},
    {AF_LEVEL_X4, "4X"},
    {AF_LEVEL_X8, "8X"},
    {AF_LEVEL_X16, "16X"} };

// WaitForVerticalRefresh mode
static const std::map<ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, const char*> vsyncMode =
{
    {WFVR_ALWAYS_OFF, "Always off"},
    {WFVR_OFF_UNLESS_APP_SPECIFIES, "Off, unless application specifies"},
    {WFVR_ON_UNLESS_APP_SPECIFIES, "On, unless application specifies"},
    {WFVR_ALWAYS_ON, "Always on"} };

// antiAliasing mode
static const std::map<ADLX_ANTI_ALIASING_MODE, const char*> antiAliasingMode =
{
    {AA_MODE_USE_APP_SETTINGS, "Use application settings"},
    {AA_MODE_ENHANCE_APP_SETTINGS, "Enhance application settings"},
    {AA_MODE_OVERRIDE_APP_SETTINGS, "Override application settings"} };

// antiAliasing method
static const std::map<ADLX_ANTI_ALIASING_METHOD, const char*> antiAliasingMethod =
{
    {AA_METHOD_MULTISAMPLING, "Muti-Sampling"},
    {AA_METHOD_ADAPTIVE_MULTISAMPLING, "Adaptive Muti-Sampling"},
    {AA_METHOD_SUPERSAMPLING, "Super Sampling"} };

// antiAliasing level
static const std::map<ADLX_ANTI_ALIASING_LEVEL, const char*> antiAliasingLevel =
{
    {AA_LEVEL_INVALID, "Level Invalid"},
    {AA_LEVEL_2X, "2X"},
    {AA_LEVEL_2XEQ, "2XEQ"},
    {AA_LEVEL_4X, "4X"},
    {AA_LEVEL_4XEQ, "4XEQ"},
    {AA_LEVEL_8X, "8X"},
    {AA_LEVEL_8XEQ, "8XEQ"} };

// TessellationMode mode
static const std::map<ADLX_TESSELLATION_MODE, const char*> Modes =
{
    {T_MODE_AMD_OPTIMIZED, "AMD optimized"},
    {T_MODE_USE_APP_SETTINGS, "Use application settings"},
    {T_MODE_OVERRIDE_APP_SETTINGS, "Override application settings"} };

// TessellationMode level
static const std::map<ADLX_TESSELLATION_LEVEL, const char*> Levels =
{
    {T_LEVEL_OFF, "Off"},
    {T_LEVEL_2X, "2X"},
    {T_LEVEL_4X, "4X"},
    {T_LEVEL_6X, "6X"},
    {T_LEVEL_8X, "8X"},
    {T_LEVEL_16X, "16X"},
    {T_LEVEL_32X, "32X"},
    {T_LEVEL_64X, "64X"} };

// Get the GPU unique name
void GPUUniqueName(IADLXGPUPtr gpu, char* uniqueName);

// Call back to handl changed events
class CallBack3DSettingsChanged : public IADLX3DSettingsChangedListener
{
public:
    adlx_bool ADLX_STD_CALL On3DSettingsChanged(IADLX3DSettingsChangedEvent* p3DSettingsChangedEvent) override
    {
        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        // Get the GPU interface
        IADLXGPUPtr gpu;
        p3DSettingsChangedEvent->GetGPU(&gpu);
        //RadeonSuperResolution is a global feature (the GPU interface is nullptr); skip printing its name
        if (!p3DSettingsChangedEvent->IsRadeonSuperResolutionChanged())
        {
            char uniqueName[128] = "Unknown";
            GPUUniqueName(gpu, uniqueName);
            std::cout << "GPU: " << uniqueName << ", Get sync event, 3D settings changed event was fired" << std::endl;
        }
        ADLX_SYNC_ORIGIN origin = p3DSettingsChangedEvent->GetOrigin();
        if (origin == SYNC_ORIGIN_EXTERNAL)
        {
            if (p3DSettingsChangedEvent->IsAntiLagChanged())
            {
                // Get AntiLag interface
                IADLX3DAntiLagPtr d3dAntiLag;
                d3dSettingSrv->GetAntiLag(gpu, &d3dAntiLag);
                adlx_bool enabled;
                d3dAntiLag->IsEnabled(&enabled);
                std::cout <<"\tAntiLag changed\n\tIsEnabled: " << enabled << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsChillChanged())
            {
                // Get Chill interface
                IADLX3DChillPtr d3dChill;
                d3dSettingSrv->GetChill(gpu, &d3dChill);
                adlx_bool enabled;
                d3dChill->IsEnabled(&enabled);
                adlx_int minFPS, maxFPS;
                d3dChill->GetMinFPS(&minFPS);
                d3dChill->GetMaxFPS(&maxFPS);
                std::cout << "\tChill changed\n\tIsEnabled: " << enabled << " , FPS: [ " << minFPS << " , " << maxFPS << " ]" << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsBoostChanged())
            {
                // Get Boost interface
                IADLX3DBoostPtr d3dBoost;
                d3dSettingSrv->GetBoost(gpu, &d3dBoost);
                adlx_bool enabled;
                d3dBoost->IsEnabled(&enabled);
                adlx_int minRes;
                d3dBoost->GetResolution(&minRes);
                std::cout << "\tBoost changed\n\tIsEnabled: " << enabled << " , minResolution: " << minRes << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsImageSharpeningChanged())
            {
                // Get ImageSharpen interface
                IADLX3DImageSharpeningPtr d3dImageSharpen;
                d3dSettingSrv->GetImageSharpening(gpu, &d3dImageSharpen);
                adlx_bool enabled;
                d3dImageSharpen->IsEnabled(&enabled);
                adlx_int min;
                d3dImageSharpen->GetSharpness(&min);
                std::cout << "\tImageSharpening changed\n\tIsEnabled: " << enabled << " , Sharpness: " << min << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsEnhancedSyncChanged())
            {
                // Get EnhancedSync interface
                IADLX3DEnhancedSyncPtr d3dEnhancedSync;
                d3dSettingSrv->GetEnhancedSync(gpu, &d3dEnhancedSync);
                adlx_bool enabled;
                d3dEnhancedSync->IsEnabled(&enabled);
                std::cout << "\tEnhancedSync changed\n\tIsEnabled: " << enabled << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsWaitForVerticalRefreshChanged())
            {
                // Get Vsync interface
                IADLX3DWaitForVerticalRefreshPtr vsync;
                d3dSettingSrv->GetWaitForVerticalRefresh(gpu, &vsync);
                adlx_bool enabled;
                vsync->IsEnabled(&enabled);
                ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode = WFVR_ALWAYS_OFF;
                vsync->GetMode(&mode);
                std::cout << "\tWaitForVerticalRefresh changed\n\tIsEnabled: " << enabled << " , Mode: " << vsyncMode.find(mode)->second << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsFrameRateTargetControlChanged())
            {
                // Get FRTC interface
                IADLX3DFrameRateTargetControlPtr frtc;
                d3dSettingSrv->GetFrameRateTargetControl(gpu, &frtc);
                adlx_bool enabled;
                frtc->IsEnabled(&enabled);
                adlx_int fps;
                frtc->GetFPS(&fps);
                std::cout << "\tFRTC changed\n\tIsEnabled: " << enabled << " , fps: " << fps << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsAntiAliasingChanged())
            {
                // Get AntiAliasing interface
                IADLX3DAntiAliasingPtr antiAliasing;
                d3dSettingSrv->GetAntiAliasing(gpu, &antiAliasing);
                ADLX_ANTI_ALIASING_MODE mode;
                antiAliasing->GetMode(&mode);
                ADLX_ANTI_ALIASING_METHOD method;
                antiAliasing->GetMethod(&method);
                ADLX_ANTI_ALIASING_LEVEL level;
                antiAliasing->GetLevel(&level);
                std::cout << "\tAntiAliasing changed\n" << std::endl
                << "\tMode: " << antiAliasingMode.find(mode)->second << std::endl
                << "\tMethod: " << antiAliasingMethod.find(method)->second << std::endl
                << "\tLevel: " << antiAliasingLevel.find(level)->second << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsMorphologicalAntiAliasingChanged())
            {
                // Get MorphologicAntiAliasing interface
                IADLX3DMorphologicalAntiAliasingPtr mAntiAliasing;
                d3dSettingSrv->GetMorphologicalAntiAliasing(gpu, &mAntiAliasing);
                adlx_bool enabled;
                mAntiAliasing->IsEnabled(&enabled);
                std::cout << "\tMorphologicalAntiAliasing changed\n\tIsEnabled: " << enabled << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsAnisotropicFilteringChanged())
            {
                // Get AnisotropicFilteringPtr interface
                IADLX3DAnisotropicFilteringPtr anisotropicFiltering;
                d3dSettingSrv->GetAnisotropicFiltering(gpu, &anisotropicFiltering);
                adlx_bool enabled;
                anisotropicFiltering->IsEnabled(&enabled);
                ADLX_ANISOTROPIC_FILTERING_LEVEL level;
                anisotropicFiltering->GetLevel(&level);
                std::cout << "\tAnisotropicFiltering changed\n\tIsEnabled: " << enabled << std::endl
                << "\tLevel: " << levelMap.find(level)->second << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsTessellationModeChanged())
            {
                // Get IADLX3DTessellation interface
                IADLX3DTessellationPtr tessellation;
                d3dSettingSrv->GetTessellation(gpu, &tessellation);
                ADLX_TESSELLATION_MODE mode;
                tessellation->GetMode(&mode);
                ADLX_TESSELLATION_LEVEL level;
                tessellation->GetLevel(&level);
                std::cout << "\tTessellationMode changed\n" << std::endl
                << "\tMode: " << Modes.find(mode)->second << std::endl
                << "\tLevel: " << Levels.find(level)->second << std::endl;
            }
            else if (p3DSettingsChangedEvent->IsResetShaderCache())
            {
                std::cout << "\tResetShaderCache" << std::endl;
            }
        }

        if (origin == SYNC_ORIGIN_UNKNOWN)
        {
            if (p3DSettingsChangedEvent->IsRadeonSuperResolutionChanged())
            {
                // Get IADLX3DRadeonSuperResolution interface
                IADLX3DRadeonSuperResolutionPtr rsr;
                d3dSettingSrv->GetRadeonSuperResolution(&rsr);
                adlx_bool enabled = false;
                rsr->IsEnabled(&enabled);
                adlx_int sharpness;
                rsr->GetSharpness(&sharpness);
                std::cout << "\tRSR changed\n\tIsEnabled: " << enabled << " , Sharpness: " << sharpness <<  std::endl;
            }
        }

        SetEvent(blockEvent);

        // Return true for ADLX to continue notifying the next listener, or false to stop notification
        return true;
    }
};

// Wait for quit signal
void QuitWait(adlx_bool* loopFlag)
{
    while (true)
    {
        // Non-blocking checking if the I/O cache has characters
        if (_kbhit())
        {
            char c;
            if ((c = getchar()) == 'q' || c == 'Q')
            {
                *loopFlag = false;
                SetEvent(quitEvent);
                break;
            }
        }
        Sleep(100);
    }
}

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Create block event
        blockEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create quit event
        quitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Create event array
        HANDLE eventArray[] = { blockEvent, quitEvent };

        // Get 3DSettings service
        IADLX3DSettingsServicesPtr d3dSettingSrv;
        res = g_ADLXHelp.GetSystemServices()->Get3DSettingsServices(&d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
            // Get Change handle
            IADLX3DSettingsChangedHandlingPtr changeHandle;
            res = d3dSettingSrv->Get3DSettingsChangedHandling(&changeHandle);
            if (ADLX_SUCCEEDED(res))
            {
                // Create call back
                IADLX3DSettingsChangedListener* call = new CallBack3DSettingsChanged;

                // Add call back
                changeHandle->Add3DSettingsEventListener(call);

                // Create a thread to check quit event
                bool loopFlag = true;
                std::thread t{ QuitWait, &loopFlag};

                std::cout << "\nWaiting for 3DSetting change event... Press Q/q to quit" << std::endl;
                while (true)
                {
                    // Wait for change event or request to quit
                    DWORD waitRet = WaitForMultipleObjects(2, eventArray, FALSE, INFINITE);
                    if (!loopFlag)
                    {
                        if (t.joinable())
                        {
                            t.join();
                        }
                        break;
                    }
                    ResetEvent(blockEvent);
                }

                // Remove call back
                changeHandle->Remove3DSettingsEventListener(call);

                // Delete call back
                delete call;
                call = nullptr;
            }
        }
        else
        {
            std::cout << "Failed to get the 3DSettings Services" << std::endl;
        }
    }
    else
    {
        std::cout << "ADLX initialization failed" << std::endl;
        return 0;
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Close event
    if (blockEvent)
        CloseHandle(blockEvent);
    if (quitEvent)
        CloseHandle(quitEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}

void GPUUniqueName(IADLXGPUPtr gpu, char* uniqueName)
{
    if (nullptr != gpu && nullptr != uniqueName)
    {
        const char* gpuName = nullptr;
        gpu->Name(&gpuName);
        adlx_int id;
        gpu->UniqueId(&id);
        sprintf_s(uniqueName, 128, "name:%s, id:%d", gpuName, id);
    }
}