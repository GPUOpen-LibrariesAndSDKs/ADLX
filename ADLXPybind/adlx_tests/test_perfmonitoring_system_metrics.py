#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""Test Related to PerformanceMonitoring Interfaces"""
# pylint: disable=I1101
from typing import Tuple

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "api_name",
    [
        ("IsSupportedCPUUsage"),
        ("IsSupportedSmartShift"),
        ("IsSupportedSystemRAM"),
    ],
)
def test_is_supported_system_metrics(adlx, api_name):
    """Call <api_name>() on GetSupportedSystemMetrics(). Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    sms: ADLX.IADLXSystemMetricsSupport = pms.GetSupportedSystemMetrics()
    is_supported_api_name: bool = getattr(sms, api_name)()
    assert isinstance(is_supported_api_name, bool)


@pytest.mark.parametrize(
    "api_name",
    [
        ("GetCPUUsageRange"),
        ("GetSmartShiftRange"),
        ("GetSystemRAMRange"),
    ],
)
def test_system_metrics_range(adlx, api_name):
    """Call <api_name> on GetSupportedSystemMetrics(). Expect Tuple(minValue: int, maxValue: int)"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    sms: ADLX.IADLXSystemMetricsSupport = pms.GetSupportedSystemMetrics()
    api_name_range: Tuple[int, int] = getattr(sms, api_name)()
    assert len(api_name_range) == 2
    assert isinstance(api_name_range[0], int)
    assert isinstance(api_name_range[1], int)


@pytest.mark.parametrize(
    "api_name,expected_type",
    [
        ("CPUUsage", float),
        ("SmartShift", int),
        ("SystemRAM", int),
        ("TimeStamp", int),
    ],
)
def test_system_metrics_apis(adlx, api_name, expected_type):
    """Call <api_name> on GetCurrentSystemMetrics(). Expect <expected_type> value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXSystemMetrics = pms.GetCurrentSystemMetrics()
    smart_shift: int = getattr(csm, api_name)()
    if smart_shift is not None:
        assert isinstance(smart_shift, expected_type)
