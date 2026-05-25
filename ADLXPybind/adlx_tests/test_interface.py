#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Tests for IADLXInterface APIs """
# pylint: disable=I1101
import pytest
from typing import List, Tuple
import time

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_interface_api_acquire(adlx):
    """Call Acquire() on GPU IADLXInterface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        num_acq: int = gpu.Acquire()
        assert num_acq
        assert isinstance(num_acq, int)
        assert num_acq > 0

        # cleanup
        gpu.Release()


def test_interface_api_release(adlx):
    """Call Release() on GPU IADLXInterface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        gpu.Acquire()

        num_release: int = gpu.Release()
        assert num_release
        assert isinstance(num_release, int)


def test_interface_api_query__interface(adlx):
    """Call QueryInterface() on GPU IADLXInterface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        gpu_interface: ADLX.IADLXGPU = gpu.QueryInterface("IADLXGPU")
        assert isinstance(gpu_interface, ADLX.IADLXGPU)


def test_query_interface_3d_settings(adlx):
    """Call QueryInterface() on IADLX3DSettingsServices interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    three_d_service_interface: ADLX.IADLX3DSettingsServices = three_d_settings_services.QueryInterface(
        "IADLX3DSettingsServices"
    )
    assert isinstance(three_d_service_interface, ADLX.IADLX3DSettingsServices)


def test_query_interface_3d_settings_services_get_radeon_super_resolution(adlx):
    """Call QueryInterface() on IADLX3DSettingsServices->GetRadeonSuperResolution interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    interface: ADLX.IADLX3DRadeonSuperResolution = rsr.QueryInterface("IADLX3DRadeonSuperResolution")
    assert isinstance(interface, ADLX.IADLX3DRadeonSuperResolution)


def test_query_interface_3d_settings_services_get_3D_settings_changed_handling(adlx):
    """Call QueryInterface() on IADLX3DSettingsServices->GetRadeonSuperResolution interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    sch: ADLX.IADLX3DSettingsChangedHandling = three_d_settings_services.Get3DSettingsChangedHandling()
    interface: ADLX.IADLX3DSettingsChangedHandling = sch.QueryInterface("IADLX3DSettingsChangedHandling")
    assert isinstance(interface, ADLX.IADLX3DSettingsChangedHandling)


@pytest.mark.parametrize(
    "method,interface_id",
    [
        ("GetAntiLag", "IADLX3DAntiLag"),
        ("GetChill", "IADLX3DChill"),
        ("GetBoost", "IADLX3DBoost"),
        ("GetImageSharpening", "IADLX3DImageSharpening"),
        ("GetEnhancedSync", "IADLX3DEnhancedSync"),
        ("GetWaitForVerticalRefresh", "IADLX3DWaitForVerticalRefresh"),
        ("GetFrameRateTargetControl", "IADLX3DFrameRateTargetControl"),
        ("GetAntiAliasing", "IADLX3DAntiAliasing"),
        ("GetMorphologicalAntiAliasing", "IADLX3DMorphologicalAntiAliasing"),
        ("GetAnisotropicFiltering", "IADLX3DAnisotropicFiltering"),
        ("GetTessellation", "IADLX3DTessellation"),
        ("GetResetShaderCache", "IADLX3DResetShaderCache"),
    ],
)
def test_query_interface_3d_settings_services_apis(adlx, method, interface_id):
    """Call QueryInterface() on IADLX3DSettingsServices->method interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        interface = getattr(three_d_settings_services, method)(gpu)
        query_interface = interface.QueryInterface(interface_id)
        assert isinstance(query_interface, getattr(ADLX, interface_id))


def test_query_interface_gpu_list(adlx):
    """Call QueryInterface() on List[ADLX.IADLXGPU] object."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    adlx_list: List[ADLX.IADLXGPU] = system.GetGPUsRaw()
    interface: ADLX.IADLXGPUList = adlx_list.QueryInterface("IADLXGPUList")
    assert isinstance(interface, ADLX.IADLXList)


def test_query_interface_3d_settings_services(adlx):
    """Call QueryInterface() on IADLX3DSettingsServices interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    interface: ADLX.IADLX3DSettingsServices = three_d_settings_services.QueryInterface("IADLX3DSettingsServices")
    assert isinstance(interface, ADLX.IADLX3DSettingsServices)


def test_query_interface_desktop_service(adlx):
    """Call QueryInterface() on GetDesktopsServices interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    interface: ADLX.IADLXDesktopServices = desktop_services.QueryInterface("IADLXDesktopServices")
    assert isinstance(interface, ADLX.IADLXDesktopServices)

@pytest.mark.parametrize(
    "method,interface_id",
    [
        ("GetDesktopChangedHandling", "IADLXDesktopChangedHandling"),
        ("GetSimpleEyefinity", "IADLXSimpleEyefinity")
    ],
)
def test_query_interface_desktop(adlx, method, interface_id):
    """Call QueryInterface() on GetDesktopsServices->method interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    interface = getattr(desktop_services, method)()
    assert isinstance(interface, getattr(ADLX, interface_id))


def test_query_interface_display_raw(adlx):
    """Call QueryInterface() on IADLXDisplayServices interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    query_interface: ADLX.IADLXDisplayServices = display_service.QueryInterface("IADLXDisplayServices")
    assert isinstance(query_interface, ADLX.IADLXDisplayServices)


def test_query_interface_display_changed_handling(adlx):
    """Call QueryInterface() on GetDisplaysServices->GetDisplayChangedHandling interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()
    query_interface: ADLX.IADLXDisplayChangedHandling = display_change_handler.QueryInterface(
        "IADLXDisplayChangedHandling"
    )
    assert isinstance(query_interface, ADLX.IADLXDisplayChangedHandling)


def test_query_interface_display_get_current_applied_resolution(adlx):
    """Call QueryInterface() on GetDisplaysServices->GetCurrentAppliedResolution interface. ."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        query_interface: ADLX.IADLXDisplayResolution = current_display_res.QueryInterface("IADLXDisplayResolution")
        assert isinstance(query_interface, ADLX.IADLXDisplayResolution)
        del query_interface, current_display_res, custom_res
    del display_list, display_service, system


@pytest.mark.parametrize(
    "method,interface_id",
    [
        ("Get3DLUT", "IADLXDisplay3DLUT"),
        ("GetGamma", "IADLXDisplayGamma"),
        ("GetGamut", "IADLXDisplayGamut"),
        ("GetFreeSync", "IADLXDisplayFreeSync"),
        ("GetVirtualSuperResolution", "IADLXDisplayVSR"),
        ("GetGPUScaling", "IADLXDisplayGPUScaling"),
        ("GetScalingMode", "IADLXDisplayScalingMode"),
        ("GetIntegerScaling", "IADLXDisplayIntegerScaling"),
        ("GetColorDepth", "IADLXDisplayColorDepth"),
        ("GetPixelFormat", "IADLXDisplayPixelFormat"),
        ("GetCustomColor", "IADLXDisplayCustomColor"),
        ("GetHDCP", "IADLXDisplayHDCP"),
        ("GetFreeSync", "IADLXDisplayFreeSync"),
        ("GetVariBright", "IADLXDisplayVariBright"),
    ],
)
def test_query_interface_display(adlx, method, interface_id):
    """Call QueryInterface() on ADLX.IADLXDisplayServices->method. Expect at lest one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        interface = getattr(display_service, method)(display)
        query_interface = interface.QueryInterface(interface_id)
        assert isinstance(query_interface, getattr(ADLX, interface_id))
        del query_interface, interface
    del display_list, display_service, system


def test_get_auto_tuning_query_interface(adlx):
    """call QueryInterface() on IADLXGPUTuningServices->GetAutoTuning"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        auto_tuning_service: ADLX.IADLXGPUAutoTuning = tuning_services.GetAutoTuning(gpu)
        query_interface = auto_tuning_service.QueryInterface("IADLXGPUAutoTuning")
        assert isinstance(query_interface, ADLX.IADLXGPUAutoTuning)


def test_get_i2c_query_interface(adlx):
    """call QueryInterface() on GetI2C() interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        query_interface = i2e_services.QueryInterface("IADLXI2C")
        assert isinstance(query_interface, ADLX.IADLXI2C)


def test_get_gpu_tuning_changed_handling_query_interface(adlx):
    """call QueryInterface() on GetGPUTuningChangedHandling() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    tuning_handler: ADLX.IADLXGPUTuningChangedHandling = tuning_services.GetGPUTuningChangedHandling()
    query_interface = tuning_handler.QueryInterface("IADLXGPUTuningChangedHandling")
    assert isinstance(query_interface, ADLX.IADLXGPUTuningChangedHandling)


def test_get_manual_fan_tuning_query_interface(adlx):
    """call QueryInterface() on GetManualFanTuning() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        query_interface = manual_fan_tuning.QueryInterface("IADLXManualFanTuning")
        assert isinstance(query_interface, ADLX.IADLXManualFanTuning)


def test_get_manual_gfx_tuning1_query_interface(adlx):
    """call QueryInterface() on GetManualGFXTuning1() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            assert isinstance(manual_gfx_tuning, ADLX.IADLXManualGraphicsTuning1)
            query_interface = manual_gfx_tuning.QueryInterface("IADLXManualGraphicsTuning1")
            assert isinstance(query_interface, ADLX.IADLXManualGraphicsTuning1)


def test_get_manual_gfx_tuning2_query_interface(adlx):
    """call QueryInterface() on GetManualGFXTuning2() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning2 = tuning_services.GetManualGFXTuning2(gpu)
        if manual_gfx_tuning:
            query_interface = manual_gfx_tuning.QueryInterface("IADLXManualGraphicsTuning2")
            assert isinstance(query_interface, ADLX.IADLXManualGraphicsTuning2)


def test_get_manual_power_tuning_query_interface(adlx):
    """call QueryInterface() on GetManualPowerTuning() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        query_interface = manual_power_tuning.QueryInterface("IADLXManualPowerTuning")
        assert isinstance(query_interface, ADLX.IADLXManualPowerTuning)


def test_get_manual_vram_tuning1_query_interface(adlx):
    """call QueryInterface() on GetManualVRAMTuning1() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            query_interface = manual_vram_tuning.QueryInterface("IADLXManualVRAMTuning1")
            assert isinstance(query_interface, ADLX.IADLXManualVRAMTuning1)


def test_get_manual_vram_tuning2_query_interface(adlx):
    """call QueryInterface() on GetManualVRAMTuning2() on TuningService interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            query_interface = manual_vram_tuning.QueryInterface("IADLXManualVRAMTuning2")
            assert isinstance(query_interface, ADLX.IADLXManualVRAMTuning2)


def test_get_performance_monitoring_services_query_interface(adlx):
    """call QueryInterface() on GetPerformanceMonitoringServices."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    query_interface = pms.QueryInterface("IADLXPerformanceMonitoringServices")
    assert isinstance(query_interface, ADLX.IADLXPerformanceMonitoringServices)


def test_get_supported_gpu_metrics_query_interface(adlx):
    """call QueryInterface() on GetPerformanceMonitoringServices->GetSupportedGPUMetrics."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sms: ADLX.IADLXGPUMetricsSupport = pms.GetSupportedGPUMetrics(gpu)
        query_interface = sms.QueryInterface("IADLXGPUMetricsSupport")
        assert isinstance(query_interface, ADLX.IADLXGPUMetricsSupport)


def test_GetSupportedSystemMetrics_query_interface(adlx):
    """call QueryInterface() on test_GetSupportedSystemMetrics_query_interface->GetSupportedSystemMetrics."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    sms: ADLX.IADLXSystemMetricsSupport = pms.GetSupportedSystemMetrics()
    query_interface = sms.QueryInterface("IADLXSystemMetricsSupport")
    assert isinstance(query_interface, ADLX.IADLXSystemMetricsSupport)


def test_get_current_system_metrics_query_interface(adlx):
    """call QueryInterface() on test_GetSupportedSystemMetrics_query_interface->GetSupportedSystemMetrics."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXSystemMetrics = ssm.GetCurrentSystemMetrics()
    query_interface = csm.QueryInterface("IADLXSystemMetrics")
    assert isinstance(query_interface, ADLX.IADLXSystemMetrics)


def test_get_current_fps_metrics_query_interface(adlx):
    """call QueryInterface() on GetCurrentFPS->GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXFPS = ssm.GetCurrentFPS()
    query_interface = csm.QueryInterface("IADLXFPS")
    assert isinstance(query_interface, ADLX.IADLXFPS)


def test_get_current_all_metrics_query_interface(adlx):
    """call QueryInterface() on GetCurrentAllMetrics->GetPerformanceMonitoringServices()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXAllMetrics = ssm.GetCurrentAllMetrics()
    query_interface = csm.QueryInterface("IADLXAllMetrics")
    assert isinstance(query_interface, ADLX.IADLXAllMetrics)


