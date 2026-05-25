#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Pytest config file. """
# pylint: disable=I1101
import gc
import time
from typing import List

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.fixture
def adlx():
    """Fixture providing main adlx helper interface"""
    adlxHelper: ADLX = ADLX.ADLXHelper()  # pylint: disable=C0103
    ret: ADLX.ADLX_RESULT = adlxHelper.Initialize()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK
    yield adlxHelper

    # Force GC before Terminate() so that all pybind11 ADLX wrapper objects
    # are destroyed while the native ADLX system is still alive.  Without
    # this, debugpy keeps frame references alive and deferred GC of those
    # wrappers after Terminate() causes an access-violation crash.
    gc.collect()

    ret: ADLX.ADLX_RESULT = adlxHelper.Terminate()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


@pytest.fixture
def tuning_factory_reset(adlx):  # pylint: disable=W0621
    """Fixture reset all GPU tunnings before and after test"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    for gpu in gpus:  # loop each gpu to do the performace test
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        print("Tuning Factory reset before test")
        tuning_services.ResetToFactory(gpu)
        del gpu
    del gpus, tuning_services
    yield
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    for gpu in gpus:  # loop each gpu to do the performace test
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services.ResetToFactory(gpu)
        print("Tuning Factory reset after test")
        del gpu
    del gpus, tuning_services


@pytest.fixture()
def clear_perf_history(adlx):  # pylint: disable=W0621
    """Fixture Clear all performance Hostory before and after test"""
    wait_clear_perf_metrics_history = 0.5
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    # pms.ClearPerformanceMetricsHistory()
    del pms
    # Wait time to clear memory Specially when StartPerformanceMetricsTracking otherwise we get ORPHAN ObJECTS
    time.sleep(wait_clear_perf_metrics_history)
    yield
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    time.sleep(wait_clear_perf_metrics_history)
    pms.StopPerformanceMetricsTracking()
    # pms.ClearPerformanceMetricsHistory()
    time.sleep(wait_clear_perf_metrics_history)
    del pms
