#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind Smart Access Memory tests. Tests for GetSmartAccessMemory and related interfaces. """
# pylint: disable=I1101
import pytest
from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_smart_access_memory(adlx):
    """Call GetSmartAccessMemory() on IADLXGPUTuningServices interface for each GPU."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sam: ADLX.IADLXSmartAccessMemory = tuning_services.GetSmartAccessMemory(gpu)
        if sam:
            assert isinstance(sam, ADLX.IADLXSmartAccessMemory)


def test_smart_access_memory_is_supported(adlx):
    """Call IsSupported() on IADLXSmartAccessMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sam: ADLX.IADLXSmartAccessMemory = tuning_services.GetSmartAccessMemory(gpu)
        if sam:
            supported = sam.IsSupported()
            if supported is not None:
                assert isinstance(supported, bool)


def test_smart_access_memory_is_enabled(adlx):
    """Call IsEnabled() on IADLXSmartAccessMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        sam: ADLX.IADLXSmartAccessMemory = tuning_services.GetSmartAccessMemory(gpu)
        if sam:
            enabled = sam.IsEnabled()
            if enabled is not None:
                assert isinstance(enabled, bool)
