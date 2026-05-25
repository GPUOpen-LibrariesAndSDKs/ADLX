#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind API tests. Purpose of this file is to check if calling ADLX API does not report unexpected errors. """
# pylint: disable=I1101
import pytest
from typing import List, Tuple

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_initialize():
    """Initialize ADLX. Expecting ADLX_RESULT.ADLX_OK"""
    adlxHelper: ADLX = ADLX.ADLXHelper()
    ret: ADLX.ADLX_RESULT = adlxHelper.Initialize()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


def test_terminate():
    """Terminate ADLX"""
    adlxHelper: ADLX = ADLX.ADLXHelper()
    ret: ADLX.ADLX_RESULT = adlxHelper.Terminate()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


def test_initialize_terminate():
    """Initialize ADLX, then Terminate ADLX"""
    adlxHelper: ADLX = ADLX.ADLXHelper()
    ret: ADLX.ADLX_RESULT = adlxHelper.Initialize()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK

    ret2: ADLX.ADLX_RESULT = adlxHelper.Terminate()
    assert ret2 == ADLX.ADLX_RESULT.ADLX_OK


def test_get_system_services(adlx):
    """Call GetSystemServices on initialized adlx. Object should not be empty"""
    assert adlx.GetSystemServices()


def test_get_display_services(adlx):
    """Call GetDisplaysServices on ADLX.IADLXSystem object. Object should not be empty"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    assert system.GetDisplaysServices()


def test_get_displays(adlx):
    """Call GetDisplays on ADLX.IADLXDisplayServices. Expect at lest one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        assert isinstance(display, ADLX.IADLXDisplay)

    assert len(display_list) > 0


def test_query_full_version(adlx):
    """Call QueryFullVersion() on adlxHelper object. We expect non empty response."""
    assert adlx.QueryFullVersion()


def test_get_gpu_tuning_services(adlx):
    """Call GetGPUTuningServices() on adlx system object. We expect non empty response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    assert system.GetGPUTuningServices()


def test_get_gpus(adlx):
    """Call GetGPUs() on adlx system object. We expect at least one AMD GPU connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        assert isinstance(gpu, ADLX.IADLXGPU)

    assert len(gpus) > 0


def test_get_performance_monitoring_services(adlx):
    """call GetPerformanceMonitoringServices(). We expect non empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    assert system.GetPerformanceMonitoringServices()


def test_get_supported_system_metrics(adlx):
    """call GetSupportedSystemMetrics() on GetPerformanceMonitoringServices(). We expect non empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    assert ssm.GetSupportedSystemMetrics()
    isinstance(ssm, ADLX.IADLXPerformanceMonitoringServices)


def test_get_supported_gpu_metrics(adlx):
    """call GetSupportedGPUMetrics() on GetPerformanceMonitoringServices(). We expect non empty response. No errors"""
    system: ADLX.IADLXGPU = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        assert ssm.GetSupportedGPUMetrics(gpu)
        isinstance(ssm, ADLX.IADLXPerformanceMonitoringServices)


def test_get_current_fps_metrics(adlx):
    """Call GetCurrentFPS() on GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXFPS = ssm.GetCurrentFPS()
    assert csm
    assert isinstance(csm, ADLX.IADLXFPS)


def test_get_current_all_metrics(adlx):
    """Call GetCurrentAllMetrics() on GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXAllMetrics = ssm.GetCurrentAllMetrics()
    assert csm
    assert isinstance(csm, ADLX.IADLXAllMetrics)


def test_get_current_system_metrics(adlx):
    """Call GetCurrentSystemMetrics() on GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXSystemMetrics = ssm.GetCurrentSystemMetrics()
    assert csm
    assert isinstance(csm, ADLX.IADLXSystemMetrics)


def test_get_current_gpu_metrics(adlx):
    """Call GetCurrentGPUMetrics() on GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        cgm: ADLX.IADLXSystemMetrics = ssm.GetCurrentGPUMetrics(gpu)
        assert cgm
        assert isinstance(cgm, ADLX.IADLXGPUMetrics)


def test_get_3D_settings_services(adlx):
    """Call Get3DSettingsServices() on IADLXSystem interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    assert three_d_settings_services
    assert isinstance(three_d_settings_services, ADLX.IADLX3DSettingsServices)


def test_get_3D_settings_changed_handling(adlx):
    """Call Get3DSettingsChangedHandling() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    sch: ADLX.IADLX3DSettingsChangedHandling = three_d_settings_services.Get3DSettingsChangedHandling()
    assert sch
    assert isinstance(sch, ADLX.IADLX3DSettingsChangedHandling)


def test_get_anisotropic_filtering(adlx):
    """Call GetAnisotropicFiltering() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        af: ADLX.IADLX3DAnisotropicFiltering = three_d_settings_services.GetAnisotropicFiltering(gpu)
        assert af
        assert isinstance(af, ADLX.IADLX3DAnisotropicFiltering)


def test_get_anti_aliasing(adlx):
    """Call GetAntiAliasing() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        aa: ADLX.IADLX3DAntiAliasing = three_d_settings_services.GetAntiAliasing(gpu)
        assert aa
        assert isinstance(aa, ADLX.IADLX3DAntiAliasing)


def test_get_anti_lag(adlx):
    """Call GetAntiLag() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        al: ADLX.IADLX3DAntiLag = three_d_settings_services.GetAntiLag(gpu)
        assert al
        assert isinstance(al, ADLX.IADLX3DAntiLag)


def test_get_boost(adlx):
    """Call GetBoost() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        assert boost
        assert isinstance(boost, ADLX.IADLX3DBoost)

def test_get_chill(adlx):
    """Call GetChill() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        assert chill
        assert isinstance(chill, ADLX.IADLX3DChill)


def test_get_enhanced_sync(adlx):
    """Call GetEnhancedSync() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        enhanced_sync: ADLX.IADLX3DEnhancedSync = three_d_settings_services.GetEnhancedSync(gpu)
        assert enhanced_sync
        assert isinstance(enhanced_sync, ADLX.IADLX3DEnhancedSync)


def test_get_frame_rate_tc(adlx):
    """Call GetFrameRateTargetControl() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        assert frame_rate_tc
        assert isinstance(frame_rate_tc, ADLX.IADLX3DFrameRateTargetControl)


def test_get_image_sharpening(adlx):
    """Call GetImageSharpening() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        assert image_sharpening
        assert isinstance(image_sharpening, ADLX.IADLX3DImageSharpening)

def test_get_image_sharpen_desktop(adlx):
    """Call GetImageSharpenDesktop() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpen_desktop: ADLX.IADLX3DImageSharpenDesktop = three_d_settings_services.GetImageSharpenDesktop(gpu)
        assert image_sharpen_desktop
        assert isinstance(image_sharpen_desktop, ADLX.IADLX3DImageSharpenDesktop)

def test_get_fidelity_fx_super_resolution(adlx):
    """Call GetFidelityFXSuperResolution() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        fsr: ADLX.IADLX3DFidelityFXSuperResolution = three_d_settings_services.GetFidelityFXSuperResolution(gpu)
        assert fsr
        assert isinstance(fsr, ADLX.IADLX3DFidelityFXSuperResolution)

def test_get_fidelity_fx_frame_gen_upgrade(adlx):
    """Call GetFidelityFXFrameGenUpgrade() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        ffgu: ADLX.IADLX3DFidelityFXFrameGenUpgrade = three_d_settings_services.GetFidelityFXFrameGenUpgrade(gpu)
        assert ffgu
        assert isinstance(ffgu, ADLX.IADLX3DFidelityFXFrameGenUpgrade)

def test_get_morphological_aa(adlx):
    """Call GetMorphologicalAntiAliasing() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        morphological_aa: ADLX.IADLX3DMorphologicalAntiAliasing = (
            three_d_settings_services.GetMorphologicalAntiAliasing(gpu)
        )
        assert morphological_aa
        assert isinstance(morphological_aa, ADLX.IADLX3DMorphologicalAntiAliasing)


def test_get_radeon_super_resolution_rsr(adlx):
    """Call GetRadeonSuperResolution() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    assert rsr
    assert isinstance(rsr, ADLX.IADLX3DRadeonSuperResolution)


def test_get_reset_shader_cache(adlx):
    """Call GetResetShaderCache() on IADLX3DResetShaderCache interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        shader_cache: ADLX.IADLX3DResetShaderCache = three_d_settings_services.GetResetShaderCache(gpu)
        assert shader_cache
        assert isinstance(shader_cache, ADLX.IADLX3DResetShaderCache)


def test_get_tessellation(adlx):
    """Call GetTessellation() on IADLX3DResetShaderCache interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tessellation: ADLX.IADLX3DTessellation = three_d_settings_services.GetTessellation(gpu)
        assert tessellation
        assert isinstance(tessellation, ADLX.IADLX3DTessellation)


def test_get_wait_for_vertical_refresh(adlx):
    """Call GetWaitForVerticalRefresh() on IADLX3DResetShaderCache interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        wait_for_vertical_refresh: ADLX.IADLX3DWaitForVerticalRefresh = (
            three_d_settings_services.GetWaitForVerticalRefresh(gpu)
        )
        assert wait_for_vertical_refresh
        assert isinstance(wait_for_vertical_refresh, ADLX.IADLX3DWaitForVerticalRefresh)

def test_get_AMDFluidMotionFrames_afmf(adlx):
    """Call GetAMDFluidMotionFrames() on IADLX3DSettingsServices interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    assert afmf
    assert isinstance(afmf, ADLX.IADLX3DAMDFluidMotionFrames)


def test_get_desktops_services(adlx):
    """call GetDesktopsServices(). We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    assert desktop_services
    assert isinstance(desktop_services, ADLX.IADLXDesktopServices)


def test_get_desktops(adlx):
    """call GetDesktops() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops: ADLX.IADLXDesktopList = desktop_services.GetDesktops()
    assert isinstance(desktops, list)

def test_at_desktop_list(adlx):
    """call At() on IADLXDesktopList interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktop_list: List[ADLX.IADLXDesktopList] = desktop_services.GetDesktops()
    for desktop in desktop_list:
        displayCount: int = desktop.GetNumberOfDisplays()
        assert isinstance(displayCount, int)

    for idx, _ in enumerate(desktop_list):
        desk: ADLX.IADLXDesktop = desktop_list[idx]
        assert desk
        assert isinstance(desk, ADLX.IADLXDesktop)


def test_get_number_of_desktops(adlx):
    """call GetNumberOfDesktops() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops: int = desktop_services.GetNumberOfDesktops()
    assert isinstance(desktops, int)


def test_get_3d_lut(adlx):
    """Call Get3DLUT on ADLX.IADLXDisplayServices. Expect at lest one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        assert isinstance(three_d_lut, ADLX.IADLXDisplay3DLUT)


def test_get_simple_eyefinity(adlx):
    """call GetNumberOfDesktops() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    simple_eyefinity: ADLX.IADLXSimpleEyefinity = desktop_services.GetSimpleEyefinity()
    assert simple_eyefinity
    assert isinstance(simple_eyefinity, ADLX.IADLXSimpleEyefinity)


def test_get_free_sync(adlx):
    """call GetFreeSync() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        free_sync: ADLX.IADLXDisplayCustomResolution = display_service.GetFreeSync(display)
        assert free_sync
        assert isinstance(free_sync, ADLX.IADLXDisplayFreeSync)


def test_get_gpu_scaling(adlx):
    """call GetGPUScaling() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gpu_scaling: ADLX.IADLXDisplayGPUScaling = display_service.GetGPUScaling(display)
        assert gpu_scaling
        assert isinstance(gpu_scaling, ADLX.IADLXDisplayGPUScaling)


def test_is_enabled_gpu_scaling(adlx):
    """call IsEnabled () on IADLXDisplayGPUScaling interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gpu_scaling: ADLX.IADLXDisplayGPUScaling = display_service.GetGPUScaling(display)
        if not gpu_scaling.IsSupported():
            continue
        ret_is_enabled: bool = gpu_scaling.IsEnabled()
        assert isinstance(ret_is_enabled, bool)
    del display_list, display_service, system


def test_is_supported_gpu_scaling(adlx):
    """call IsSupported() on IADLXDisplayGPUScaling interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gpu_scaling: ADLX.IADLXDisplayGPUScaling = display_service.GetGPUScaling(display)
        supported: bool = gpu_scaling.IsSupported()
        assert isinstance(supported, bool)
    del display_list, display_service, system


@pytest.mark.parametrize("gpu_scaling_param", [False, True])
def test_set_enabled__gpu_scaling(adlx, gpu_scaling_param):
    """call SetEnabled() on IADLXDisplayGPUScaling interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gpu_scaling: ADLX.IADLXDisplayGPUScaling = display_service.GetGPUScaling(display)
        set_enabled: ADLX.ADLX_RESULT = gpu_scaling.SetEnabled(gpu_scaling_param)
        assert set_enabled
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED


def test_get_gamma(adlx):
    """call GetGamma() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert gamma
        assert isinstance(gamma, ADLX.IADLXDisplayGamma)


def test_get_gamut(adlx):
    """call GetGamut() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        assert gamut
        assert isinstance(gamut, ADLX.IADLXDisplayGamut)


def test_get_hdcp(adlx):
    """call GetHDCP() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        hdcp: ADLX.IADLXDisplayCustomResolution = display_service.GetHDCP(display)
        assert hdcp
        assert isinstance(hdcp, ADLX.IADLXDisplayHDCP)


#
def test_is_enabled_hdcp(adlx):
    """call IsEnabled () on IADLXDisplayHDCP interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        hdcp: ADLX.IADLXDisplayCustomResolution = display_service.GetHDCP(display)
        if not hdcp.IsSupported():
            continue
        ret_is_enabled: bool = hdcp.IsEnabled()
        assert isinstance(ret_is_enabled, bool)
    del display_list, display_service, system


def test_is_supported_hdcp(adlx):
    """call IsSupported() on IADLXDisplayHDCP interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        hdcp: ADLX.IADLXDisplayCustomResolution = display_service.GetHDCP(display)
        supported: bool = hdcp.IsSupported()
        assert isinstance(supported, bool)
    del display_list, display_service, system


@pytest.mark.parametrize("hdcp_param", [False, True])
def test_set_enabled__hdcp(adlx, hdcp_param):
    """call SetEnabled() on IADLXDisplayHDCP interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        hdcp: ADLX.IADLXDisplayCustomResolution = display_service.GetHDCP(display)
        set_enabled: ADLX.ADLX_RESULT = hdcp.SetEnabled(hdcp_param)
        assert set_enabled
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED


def test_get_integer_scaling(adlx):
    """call GetIntegerScaling() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        integer_scaling: ADLX.IADLXDisplayIntegerScaling = display_service.GetIntegerScaling(display)
        assert integer_scaling
        assert isinstance(integer_scaling, ADLX.IADLXDisplayIntegerScaling)


def test_get_number_of_displays(adlx):
    """call GetNumberOfDisplays() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    dis_num: int = display_service.GetNumberOfDisplays()
    assert dis_num
    assert isinstance(dis_num, int)


def test_get_pixel_format(adlx):
    """call GetPixelFormat() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        pixel_format: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        assert pixel_format
        assert isinstance(pixel_format, ADLX.IADLXDisplayPixelFormat)


def test_get_scaling_mode(adlx):
    """call GetScalingMode() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        scaling_mode: ADLX.IADLXDisplayScalingMode = display_service.GetScalingMode(display)
        assert scaling_mode
        assert isinstance(scaling_mode, ADLX.IADLXDisplayScalingMode)


def test_get_vari_bright(adlx):
    """call GetVariBright() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        vari_bright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        assert vari_bright
        assert isinstance(vari_bright, ADLX.IADLXDisplayVariBright)


def test_get_virtual_super_resolution(adlx):
    """call GetVirtualSuperResolution() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        virtual_vsr: ADLX.IADLXDisplayVSR = display_service.GetVirtualSuperResolution(display)
        assert virtual_vsr
        assert isinstance(virtual_vsr, ADLX.IADLXDisplayVSR)


def test_get_display_blanking(adlx):
    """call GetDisplayBlanking() on IADLXDisplayServices1 interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        assert display_blanking
        assert isinstance(display_blanking, ADLX.IADLXDisplayBlanking)


def test_get_display_connectivity_experience(adlx):
    """call GetDisplayConnectivityExperience() on IADLXDisplayServices2 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        connectivity_experience: ADLX.IADLXDisplayConnectivityExperience = display_service.GetDisplayConnectivityExperience(display)
        if connectivity_experience:
            assert isinstance(connectivity_experience, ADLX.IADLXDisplayConnectivityExperience)
            assert isinstance(connectivity_experience.IsSupportedHDMIQualityDetection(), bool)
            assert isinstance(connectivity_experience.IsSupportedDPLink(), bool)
            assert isinstance(connectivity_experience.IsEnabledHDMIQualityDetection(), bool)
            assert isinstance(connectivity_experience.IsEnabledLinkProtection(), bool)
            assert isinstance(connectivity_experience.GetNumberOfActiveLanes(), int)
            assert isinstance(connectivity_experience.GetNumberOfTotalLanes(), int)
            assert isinstance(connectivity_experience.GetRelativePreEmphasis(), int)
            assert isinstance(connectivity_experience.GetRelativeVoltageSwing(), int)


def test_get_dynamic_refresh_rate_control(adlx):
    """call GetDynamicRefreshRateControl() on IADLXDisplayServices3 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        drrc: ADLX.IADLXDisplayDynamicRefreshRateControl = display_service.GetDynamicRefreshRateControl(display)
        if drrc:
            assert isinstance(drrc, ADLX.IADLXDisplayDynamicRefreshRateControl)
            assert isinstance(drrc.IsSupported(), bool)
            assert isinstance(drrc.IsEnabled(), bool)


def test_get_free_sync_color_accuracy(adlx):
    """call GetFreeSyncColorAccuracy() on IADLXDisplayServices3 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        fsca: ADLX.IADLXDisplayFreeSyncColorAccuracy = display_service.GetFreeSyncColorAccuracy(display)
        if fsca:
            assert isinstance(fsca, ADLX.IADLXDisplayFreeSyncColorAccuracy)
            assert isinstance(fsca.IsSupported(), bool)
            assert isinstance(fsca.IsEnabled(), bool)


def test_get_i2c(adlx):
    """call GetI2C() on GetSystemServices() interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        assert i2e_services
        assert isinstance(i2e_services, ADLX.IADLXI2C)


def test_total_system_ram_system(adlx):
    """call TotalSystemRAM() on GetSystemServices() interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    total_system_ram: int = system.TotalSystemRAM()
    assert total_system_ram > 0
    assert isinstance(total_system_ram, int)


def test_hybrid_graphics_type_system(adlx):
    """call HybridGraphicsType() on GetSystemServices() interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    hybrid_graphics_type: ADLX.ADLX_HG_TYPE = system.HybridGraphicsType()
    assert hybrid_graphics_type
    assert isinstance(hybrid_graphics_type, ADLX.ADLX_HG_TYPE)


def test_query_interface_system(adlx):
    """call QueryInterface() on GetSystemServices() interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    query_interface = system.QueryInterface("1")


def test_get_gpus_changed_handling_system(adlx):
    """call GetGPUsChangedHandling() on GetSystemServices() interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    get_gpus_changed_handling: ADLX.IADLXGPUsChangedHandling = system.GetGPUsChangedHandling()
    assert get_gpus_changed_handling
    assert isinstance(get_gpus_changed_handling, ADLX.IADLXGPUsChangedHandling)


def test_get_desktop_changed_handling(adlx):
    """call GetDesktopChangedHandling() on DesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktop_change_handler: ADLX.IADLXDesktopChangedHandling = desktop_services.GetDesktopChangedHandling()
    assert desktop_change_handler
    assert isinstance(desktop_change_handler, ADLX.IADLXDesktopChangedHandling)


def test_get_gpu_tuning_changed_handling(adlx):
    """call GetGPUTuningChangedHandling() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    tuning_handler: ADLX.IADLXGPUTuningChangedHandling = tuning_services.GetGPUTuningChangedHandling()
    assert tuning_handler
    assert isinstance(tuning_handler, ADLX.IADLXGPUTuningChangedHandling)


def test_get_manual_fan_tuning(adlx):
    """call GetManualFanTuning() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        assert manual_fan_tuning
        assert isinstance(manual_fan_tuning, ADLX.IADLXManualFanTuning)


def test_get_manual_gfx_tuning1(adlx):
    """call GetManualGFXTuning1() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            assert isinstance(manual_gfx_tuning, ADLX.IADLXManualGraphicsTuning1)


def test_get_manual_gfx_tuning2(adlx):
    """call GetManualGFXTuning2() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning2(gpu)
        if manual_gfx_tuning:
            assert isinstance(manual_gfx_tuning, ADLX.IADLXManualGraphicsTuning2)


def test_get_manual_power_tuning(adlx):
    """call GetManualPowerTuning() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        assert manual_power_tuning
        assert isinstance(manual_power_tuning, ADLX.IADLXManualPowerTuning)


def test_get_manual_vram_tuning1(adlx):
    """call GetManualVRAMTuning1() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            assert isinstance(manual_vram_tuning, ADLX.IADLXManualVRAMTuning1)


def test_get_manual_vram_tuning2(adlx):
    """call GetManualVRAMTuning2() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            assert isinstance(manual_vram_tuning, ADLX.IADLXManualVRAMTuning2)
