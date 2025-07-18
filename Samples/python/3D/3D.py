#<!--
# Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
#-->

import ADLXPybind as ADLX

# Iterate display and display event:plug and unplug the display
def afmfDemo():
    # Get ADLXHelp and ADLX initialization
    adlxHelper = ADLX.ADLXHelper()
    ret = adlxHelper.Initialize()

    if ret == ADLX.ADLX_RESULT.ADLX_OK:
        # Get system services
        system = adlxHelper.GetSystemServices()

        if system is not None:
            # Get display services
            displayService = system.GetDisplaysServices()
            if displayService is not None:
                count = displayService.GetNumberOfDisplays()
                print("display count: {}".format(count))
                disList = displayService.GetDisplays()
                if disList is not None:
                    foundDisplay = False
                    for index, display in enumerate(disList):
                        if display is not None and not foundDisplay:
                            foundDisplay = True
                            gpu = display.GetGPU()
                            gpuName = gpu.name()
                            vendorId = gpu.vendorId()
                            print(f"gpu name: {gpuName} vendor id: {vendorId}")
                            threeDSettingsServices = system.Get3DSettingsServices()

                            # AntiLag
                            antiLag = threeDSettingsServices.GetAntiLag(gpu)
                            antiLagSupported = antiLag.IsSupported()
                            antiLagEnabled = antiLag.IsEnabled()
                            print(f"support antilag: {antiLagSupported}, enable antilag: {antiLagEnabled}")
                            # antiLag.SetEnabled(False)

                            # Chill
                            chill = threeDSettingsServices.GetChill(gpu)
                            chillSupported = chill.IsSupported()
                            chillEnabled = chill.IsEnabled()
                            minFPS = chill.GetMinFPS()
                            maxFPS = chill.GetMaxFPS()
                            print(f"support chill: {chillSupported}, enable chill: {chillEnabled} minFPS: {minFPS} maxFPS: {maxFPS}")
                            # if not chillEnabled:
                            #     chill.SetEnabled(True)
                            # chill.SetMinFPS(30)
                            # chill.SetMaxFPS(60)

                            # Boost
                            boost = threeDSettingsServices.GetBoost(gpu)
                            boostSupported = boost.IsSupported()
                            boostEnabled = boost.IsEnabled()
                            boostResolution = boost.GetResolution() # Performance: 50, Quality: 84
                            # boost.SetEnabled(True)
                            print(f"support boost: {boostSupported}, enable boost: {boostEnabled} boost resolution: {boostResolution}")

                            # GPU Scaling
                            gpuScaling = displayService.GetGPUScaling(display)
                            gpuScalingSupported = gpuScaling.IsSupported()
                            gpuScalingEnabled = gpuScaling.IsEnabled()
                            print(f"support GPU scaling: {gpuScalingSupported}, enable GPU scaling: {gpuScalingEnabled}")
                            # gpuScaling.SetEnabled(True)

                            # Integer Scaling
                            integerScaling = displayService.GetIntegerScaling(display)
                            integerScalingSupported = integerScaling.IsSupported()
                            integerScalingEnabled = integerScaling.IsEnabled()
                            print(f"support integer scaling: {integerScalingSupported}, enable integer scaling: {integerScalingEnabled}")

                            # Scaling Mode
                            scalingMode = displayService.GetScalingMode(display)
                            scalingModeSupported = scalingMode.IsSupported()
                            scalingModeNow = scalingMode.GetMode()
                            print(f"support scaling mode: {scalingModeSupported}, scaling mode: {scalingModeNow}")

                            # Radeon Super Resolution
                            radeonSuperResolution = threeDSettingsServices.GetRadeonSuperResolution()
                            radeonSuperResolutionSupported = radeonSuperResolution.IsSupported()
                            radeonSuperResolutionEnabled = radeonSuperResolution.IsEnabled()
                            radeonSuperResolutionSharpness = radeonSuperResolution.GetSharpness()
                            print(f"support radeon super resolution: {radeonSuperResolutionSupported}, enabled: {radeonSuperResolutionEnabled}, sharpness: {radeonSuperResolutionSharpness}")
                            # radeonSuperResolution.SetEnabled(False)

                            # AMD Fluid Motion Frame
                            threeDSettingsServices1 = system.Get3DSettingsServices1()
                            amdFluidMotionFrame = threeDSettingsServices1.GetAMDFluidMotionFrame()
                            amdFluidMotionFrameSupported = amdFluidMotionFrame.IsSupported()
                            amdFluidMotionFrameEnabled = amdFluidMotionFrame.IsEnabled()
                            print(f"support AMD fluid motion frame: {amdFluidMotionFrameSupported}, enabled: {amdFluidMotionFrameEnabled}")
                            # amdFluidMotionFrame.SetEnabled(True)

    # Terminate ADLX
    ret = adlxHelper.Terminate()
    print("ADLX Terminate ret is: {}".format(ret))

afmfDemo()