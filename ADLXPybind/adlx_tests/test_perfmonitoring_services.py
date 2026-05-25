#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""Test Related to PerformanceMonitoring Interfaces"""
# pylint: disable=I1101
import time
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "api_name",
    [
        ("GetSamplingIntervalRange"),
        ("GetMaxPerformanceMetricsHistorySizeRange"),
    ],
)
def test_perfmonitoring_services_range(adlx, api_name):
    """Call <api_name> on GetPerformanceMonitoringServices().

    Expect ADLX_IntRange (minValue: int, maxValue: int, step: int)
    """
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    # sms: ADLX.IADLXSystemMetricsSupport = pms.GetSupportedSystemMetrics()
    api_name_range: ADLX.ADLXIntRange = getattr(pms, api_name)()
    assert isinstance(api_name_range, ADLX.ADLX_IntRange)
    assert isinstance(api_name_range.minValue, int)
    assert isinstance(api_name_range.maxValue, int)
    assert isinstance(api_name_range.step, int)


@pytest.mark.parametrize(
    "api_name",
    [
        ("GetSamplingInterval"),
        ("GetMaxPerformanceMetricsHistorySize"),
        ("GetCurrentPerformanceMetricsHistorySize"),
    ],
)
def test_perfmonitoring_services_get(adlx, api_name):
    """Call <api_name> on GetPerformanceMonitoringServices(). Expect int"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    api_name_ret: int = getattr(pms, api_name)()
    assert isinstance(api_name_ret, int)


@pytest.mark.parametrize(
    "get_api_name,api_name",
    [
        ("GetSamplingInterval", "SetSamplingInterval"),
        ("GetMaxPerformanceMetricsHistorySize", "SetMaxPerformanceMetricsHistorySize"),
    ],
)
def test_perfmonitoring_services_set(adlx, get_api_name, api_name):
    """Call <api_name> on GetPerformanceMonitoringServices(). Expect ADLX.ADLX_RESULT"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    set_data: int = getattr(pms, get_api_name)()
    api_name_ret: ADLX.ADLX_RESULT = getattr(pms, api_name)(set_data)
    assert isinstance(api_name_ret, ADLX.ADLX_RESULT)


@pytest.mark.parametrize(
    "api_name",
    [
        ("ClearPerformanceMetricsHistory"),
        ("StartPerformanceMetricsTracking"),
        ("StopPerformanceMetricsTracking"),
    ],
)
def test_perfmonitoring_services_apis(adlx, api_name):
    """Call <api_name> on GetPerformanceMonitoringServices(). Expect ADLX.ADLX_RESULT"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    api_name_ret: ADLX.ADLX_RESULT = getattr(pms, api_name)()
    # Wait time to clear memory Specially when StartPerformanceMetricsTracking otherwise we get ORPHAN ObJECTS
    time.sleep(1)
    pms.StopPerformanceMetricsTracking()
    pms.ClearPerformanceMetricsHistory()
    assert isinstance(api_name_ret, ADLX.ADLX_RESULT)
