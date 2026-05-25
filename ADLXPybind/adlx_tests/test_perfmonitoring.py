#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""Test Related to PerformanceMonitoring Interfaces"""
# pylint: disable=I1101
import time
from typing import List
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "api_name,expected_type",
    [
        ("FPS", int),
        ("TimeStamp", int),
    ],
)
def test_fps_metrics_apis(adlx, api_name, expected_type):
    """Call <api_name> on GetCurrentFPS(). Expect <expected_type> value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXFPS = pms.GetCurrentFPS()
    param = getattr(csm, api_name)()
    if param is not None:
        assert param or param == 0.0
        assert isinstance(param, expected_type)


@pytest.mark.parametrize(
    "api_name,expected_type",
    [
        ("GetSystemMetrics", ADLX.IADLXSystemMetrics),
        ("GetFPS", ADLX.IADLXFPS),
        ("TimeStamp", int),
    ],
)
def test_all_metrics_apis(adlx, api_name, expected_type):
    """Call <api_name> on GetCurrentAllMetrics(). Expect <expected_type> value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXAllMetrics = pms.GetCurrentAllMetrics()
    param = getattr(csm, api_name)()
    assert param
    assert isinstance(param, expected_type)


def test_get_gpumetrics(adlx):
    """Call GetIADLXGPUMetrics on GetCurrentAllMetrics(). Expect ADLX.IADLXIADLXGPUMetrics"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus = system.GetGPUs()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    csm: ADLX.IADLXAllMetrics = pms.GetCurrentAllMetrics()
    param: ADLX.IADLXIADLXGPUMetrics = csm.GetGPUMetrics(gpus[0])
    assert param
    assert isinstance(param, ADLX.IADLXGPUMetrics)


@pytest.mark.usefixtures("clear_perf_history")
def test_allmetrics_history(adlx):
    """Test get history, return type should list of AllMetrics, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    metrics: List[ADLX.IADLXAllMetrics] = pms.GetAllMetricsHistory(time_monitoring * 1000, 0)
    for metric in metrics:
        assert isinstance(metric, ADLX.IADLXAllMetrics)
    assert len(metrics) > 0


@pytest.mark.usefixtures("clear_perf_history")
def test_gpumetrics_history(adlx):
    """Test get history, return type should list of GPUMetrics, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    metrics: List[ADLX.IADLXGPUMetrics] = pms.GetGPUMetricsHistory(gpus[0], time_monitoring * 1000, 0)
    for metric in metrics:
        assert isinstance(metric, ADLX.IADLXGPUMetrics)
    assert len(metrics) > 0


@pytest.mark.usefixtures("clear_perf_history")
def test_systemmetrics_history(adlx):
    """Test get history, return type should list of SystemMetrics, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    metrics: List[ADLX.IADLXSystemMetrics] = pms.GetSystemMetricsHistory(time_monitoring * 1000, 0)
    for metric in metrics:
        assert isinstance(metric, ADLX.IADLXSystemMetrics)
    assert len(metrics) > 0


@pytest.mark.usefixtures("clear_perf_history")
def test_fps_history(adlx):
    """Test get history, return type should list of FPS, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    metrics: List[ADLX.IADLXFPS] = pms.GetFPSHistory(time_monitoring * 1000, 0)
    for metric in metrics:
        assert isinstance(metric, ADLX.IADLXFPS)
    assert len(metrics) > 0
