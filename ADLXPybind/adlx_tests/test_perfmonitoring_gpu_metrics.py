#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""Test Related to PerformanceMonitoring Interfaces"""
# pylint: disable=I1101
from typing import List
from typing import Tuple

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "api_name",
    [
        ("IsSupportedGPUUsage"),
        ("IsSupportedGPUClockSpeed"),
        ("IsSupportedGPUVRAMClockSpeed"),
        ("IsSupportedGPUTemperature"),
        ("IsSupportedGPUHotspotTemperature"),
        ("IsSupportedGPUPower"),
        ("IsSupportedGPUTotalBoardPower"),
        ("IsSupportedGPUFanSpeed"),
        ("IsSupportedGPUVRAM"),
        ("IsSupportedGPUVoltage"),
    ],
)
def test_is_supported_gpu_metrics(adlx, api_name):
    """Call <api_name>() on GetSupportedGPUMetrics(). Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sms: ADLX.IADLXGPUMetricsSupport = pms.GetSupportedGPUMetrics(gpu)
        is_supported_api_name: bool = getattr(sms, api_name)()
        assert isinstance(is_supported_api_name, bool)


@pytest.mark.parametrize(
    "api_name",
    [
        ("GetGPUUsageRange"),
        ("GetGPUClockSpeedRange"),
        ("GetGPUVRAMClockSpeedRange"),
        ("GetGPUTemperatureRange"),
        ("GetGPUHotspotTemperatureRange"),
        ("GetGPUPowerRange"),
        ("GetGPUFanSpeedRange"),
        ("GetGPUVRAMRange"),
        ("GetGPUVoltageRange"),
        ("GetGPUTotalBoardPowerRange"),
    ],
)
def test_gpu_metrics_range(adlx, api_name):
    """Call <api_name> on GetSupportedGPUMetrics(). Expect Tuple(minValue: int, maxValue: int)"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sms: ADLX.IADLXGPUMetricsSupport = pms.GetSupportedGPUMetrics(gpu)
        api_name_range: Tuple[int, int] = getattr(sms, api_name)()
        assert len(api_name_range) == 2
        assert isinstance(api_name_range[0], int)
        assert isinstance(api_name_range[1], int)


@pytest.mark.parametrize(
    "api,expected_type",
    [
        ("GPUClockSpeed", int),
        ("GPUFanSpeed", int),
        ("GPUHotspotTemperature", float),
        ("GPUPower", float),
        ("GPUTemperature", float),
        ("GPUTotalBoardPower", float),
        ("GPUUsage", float),
        ("GPUVRAM", int),
        ("GPUVRAMClockSpeed", int),
        ("GPUVoltage", int),
        ("TimeStamp", int),
    ],
)
def test_gpu_metrics(adlx, api, expected_type):
    """Call GPUPower on CurrentGPUMetrics object. Expecting float value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    ssm: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        cgm: ADLX.IADLXSystemMetrics = ssm.GetCurrentGPUMetrics(gpu)

        param = getattr(cgm, api)()
        if param is not None:
            assert param or param == 0.0
            assert isinstance(param, expected_type)