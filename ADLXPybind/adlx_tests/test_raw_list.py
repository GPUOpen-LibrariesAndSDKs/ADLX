#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind structs tests.
Purpose of this file is to check if calling ADLX API strucs does not report unexpected errors.
"""
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
        ("Size", int),
        ("Empty", int),
        ("Begin", int),
        ("End", int),
        ("Remove_Back", ADLX.ADLX_RESULT),
    ],
)
def test_apis(adlx, api_name, expected_type):
    """Test <api_name> of List, return type should be <expected_type>."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    adlx_list: List[ADLX.IADLXGPU] = system.GetGPUsRaw()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    gpu = gpus[0]
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(gpu)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    returned_type = getattr(adlx_list, api_name)()
    assert isinstance(returned_type, expected_type)


def test_clear(adlx):
    """Test Clear a List, return type should ADLX_RESULT, List SHould be empty after api called."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    adlx_list: List[ADLX.IADLXGPU] = system.GetGPUsRaw()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    gpu = gpus[0]
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(gpu)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    returned_type = adlx_list.Clear()
    assert isinstance(returned_type, ADLX.ADLX_RESULT)
    assert adlx_list.Empty()


def test_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    adlx_list: List[ADLX.IADLXGPU] = system.GetGPUsRaw()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    gpu = gpus[0]
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(gpu)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    same_gpu = adlx_list.At(0)
    assert isinstance(same_gpu, ADLX.IADLXGPU)
    assert same_gpu == gpu


def test_add_back(adlx):
    """Test AddBack List, return type should ADLX_RESULT, Element should increase size when added."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    adlx_list: ADLX.IADLXGPU = system.GetGPUsRaw()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    gpu = gpus[0]
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(gpu)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


def test_display_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    displays: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not displays:
        del display_service
        pytest.skip("No Displays found")
    adlx_list: ADLX.IADLXDisplayList = display_service.GetDisplaysListRaw()
    display = displays[0]
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(display)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    same_gpu = adlx_list.At(0)
    assert isinstance(same_gpu, ADLX.IADLXDisplay)
    assert same_gpu == display


def test_display_list_raw_add_back(adlx):
    """Test AddBack List, return type should ADLX_RESULT, Element should increase size when added."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    displays: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not displays:
        del display_service
        pytest.skip("No Displays found")
    adlx_list: List[ADLX.IADLXDisplay] = display_service.GetDisplaysListRaw()
    display = displays[0]
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(display)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


def test_display_resolution_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    displays: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not displays:
        del display_service
        pytest.skip("No Displays found")
    custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(displays[0])
    adlx_list: ADLX.IADLXDisplayResolutionList = custom_res.GetResolutionListRaw()
    if adlx_list is None:
        del custom_res, displays, display_service, system
        pytest.skip("GetResolutionListRaw returned None")
    current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(current_display_res)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    same_res = adlx_list.At(0)
    assert isinstance(same_res, ADLX.IADLXDisplayResolution)
    assert same_res == current_display_res
    del same_res, current_display_res, adlx_list, custom_res, displays, display_service, system


def test_display_resolution_list_raw_add_back(adlx):
    """Test AddBack List, return type should ADLX_RESULT, Element should increase size when added."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    displays: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not displays:
        del display_service
        pytest.skip("No Displays found")
    custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(displays[0])
    adlx_list: ADLX.IADLXDisplayResolutionList = custom_res.GetResolutionListRaw()
    if adlx_list is None:
        del custom_res, displays, display_service, system
        pytest.skip("GetResolutionListRaw returned None")
    current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(current_display_res)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1
    del current_display_res, adlx_list, custom_res, displays, display_service, system


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_fan_tuning_states_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            del tuning_services
            continue
        man_fan_tunning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        adlx_list: ADLX.IADLXManualFanTuningStateList = man_fan_tunning.GetFanTuningStatesRaw()
        if adlx_list is not None:
            empty_man_fan_tuning_state: ADLX.IADLXManualFanTuningState = man_fan_tunning.GetEmptyFanTuningStates()[0]
            ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_fan_tuning_state)
            assert ret_add_back
            assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

            size = adlx_list.Size()
            same_res = adlx_list.At(size - 1)
            assert isinstance(same_res, ADLX.IADLXManualFanTuningState)
            assert same_res == empty_man_fan_tuning_state
            del same_res, adlx_list, empty_man_fan_tuning_state
        del man_fan_tunning, tuning_services


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_fan_tuning_states_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        man_fan_tunning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        adlx_list: ADLX.IADLXManualFanTuningStateList = man_fan_tunning.GetFanTuningStatesRaw()
        empty_fan_tuning_states: list = man_fan_tunning.GetEmptyFanTuningStates()
        empty_man_fan_tuning_state: ADLX.IADLXManualFanTuningState = man_fan_tunning.GetEmptyFanTuningStates()[0]
        size_before_add = adlx_list.Size()
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_fan_tuning_state)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
        size_after_add = adlx_list.Size()
        assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_gpu_tuning_states_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        man_gpu_tunning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if not man_gpu_tunning:
            gpu_name: str = gpu.Name()
            del man_gpu_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXManualTuningStateList = man_gpu_tunning.GetGPUTuningStatesRaw()
        empty_man_gpu_tuning_state: ADLX.IADLXManualTuningState = man_gpu_tunning.GetEmptyGPUTuningStates()[0]
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_gpu_tuning_state)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

        size = adlx_list.Size()
        same_res = adlx_list.At(size - 1)
        assert isinstance(same_res, ADLX.IADLXManualTuningState)
        assert same_res == empty_man_gpu_tuning_state


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_gpu_tuning_states_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        man_gpu_tunning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if not man_gpu_tunning:
            gpu_name: str = gpu.Name()
            del man_gpu_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXManualTuningStateList = man_gpu_tunning.GetGPUTuningStatesRaw()
        empty_man_gpu_tuning_state: ADLX.IADLXManualTuningState = man_gpu_tunning.GetEmptyGPUTuningStates()[0]
        size_before_add = adlx_list.Size()
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_gpu_tuning_state)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
        size_after_add = adlx_list.Size()
        assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_vram_tuning_states_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXManualTuningStateList = man_vram_tunning.GetVRAMTuningStatesRaw()
        empty_man_gpu_tuning_state: ADLX.IADLXManualTuningState = man_vram_tunning.GetEmptyVRAMTuningStates()[0]
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_gpu_tuning_state)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

        size = adlx_list.Size()
        same_res = adlx_list.At(size - 1)
        assert isinstance(same_res, ADLX.IADLXManualTuningState)
        assert same_res == empty_man_gpu_tuning_state


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_vram_tuning_states_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXManualTuningStateList = man_vram_tunning.GetVRAMTuningStatesRaw()
        empty_man_gpu_tuning_state: ADLX.IADLXManualTuningState = man_vram_tunning.GetEmptyVRAMTuningStates()[0]
        size_before_add = adlx_list.Size()
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(empty_man_gpu_tuning_state)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
        size_after_add = adlx_list.Size()
        assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_memory_timing_description_list_raw_2_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning2(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXMemoryTimingDescriptionList = man_vram_tunning.GetSupportedMemoryTimingDescriptionListRaw()
        mem_time_memory_list_item: ADLX.IADLXMemoryTimingDescription = (
            man_vram_tunning.GetSupportedMemoryTimingDescriptionList()[0]
        )
        size_before_add = adlx_list.Size()
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(mem_time_memory_list_item)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
        size_after_add = adlx_list.Size()
        assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_memory_timing_description_list_raw_2_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning2(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXMemoryTimingDescriptionList = man_vram_tunning.GetSupportedMemoryTimingDescriptionListRaw()
        mem_time_memory_list_item: ADLX.IADLXMemoryTimingDescription = (
            man_vram_tunning.GetSupportedMemoryTimingDescriptionList()[0]
        )
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(mem_time_memory_list_item)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

        size = adlx_list.Size()
        same_res = adlx_list.At(size - 1)
        assert isinstance(same_res, ADLX.IADLXMemoryTimingDescription)
        assert same_res == mem_time_memory_list_item


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_memory_timing_description_list_raw_1_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXMemoryTimingDescriptionList = man_vram_tunning.GetSupportedMemoryTimingDescriptionListRaw()
        mem_time_memory_list_item: ADLX.IADLXMemoryTimingDescription = (
            man_vram_tunning.GetSupportedMemoryTimingDescriptionList()[0]
        )
        size_before_add = adlx_list.Size()
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(mem_time_memory_list_item)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
        size_after_add = adlx_list.Size()
        assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("tuning_factory_reset")
def test_man_memory_timing_description_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        man_vram_tunning: ADLX.IADLXManualVRAMTuning1 = tuning_services.GetManualVRAMTuning1(gpu)
        if not man_vram_tunning:
            gpu_name: str = gpu.Name()
            del man_vram_tunning
            del tuning_services
            del gpu
            del gpus
            pytest.skip(f"gpu: {gpu_name} isn't Pre-Navi")
        adlx_list: ADLX.IADLXMemoryTimingDescriptionList = man_vram_tunning.GetSupportedMemoryTimingDescriptionListRaw()
        mem_time_memory_list_item: ADLX.IADLXMemoryTimingDescription = (
            man_vram_tunning.GetSupportedMemoryTimingDescriptionList()[0]
        )
        ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(mem_time_memory_list_item)
        assert ret_add_back
        assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

        size = adlx_list.Size()
        same_res = adlx_list.At(size - 1)
        assert isinstance(same_res, ADLX.IADLXMemoryTimingDescription)
        assert same_res == mem_time_memory_list_item


@pytest.mark.usefixtures("clear_perf_history")
def test_allmetrics_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    # start_time = int(time.time())
    # end_time = start_time + time_monitoring
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXAllMetricsList = pms.GetAllMetricsHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXAllMetrics = pms.GetCurrentAllMetrics()
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("clear_perf_history")
def test_allmetrics_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXAllMetricsList = pms.GetAllMetricsHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXAllMetrics = pms.GetCurrentAllMetrics()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    size = adlx_list.Size()
    same_res = adlx_list.At(size - 1)
    assert isinstance(same_res, ADLX.IADLXAllMetrics)
    assert same_res == all_metrics_item


@pytest.mark.usefixtures("clear_perf_history")
def test_gpumetrics_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXGPUMetricsList = pms.GetGPUMetricsHistoryRaw(gpus[0], time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXGPUMetrics = pms.GetCurrentGPUMetrics(gpus[0])
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("clear_perf_history")
def test_gpumetrics_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXGPUMetricsList = pms.GetGPUMetricsHistoryRaw(gpus[0], time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXGPUMetrics = pms.GetCurrentGPUMetrics(gpus[0])
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    size = adlx_list.Size()
    same_res = adlx_list.At(size - 1)
    assert isinstance(same_res, ADLX.IADLXGPUMetrics)
    assert same_res == all_metrics_item


@pytest.mark.usefixtures("clear_perf_history")
def test_systemmetrics_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXSystemMetricsList = pms.GetSystemMetricsHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXSystemMetrics = pms.GetCurrentSystemMetrics()
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("clear_perf_history")
def test_systemmetrics_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXSystemMetricsList = pms.GetSystemMetricsHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXSystemMetrics = pms.GetCurrentSystemMetrics()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    size = adlx_list.Size()
    same_res = adlx_list.At(size - 1)
    assert isinstance(same_res, ADLX.IADLXSystemMetrics)
    assert same_res == all_metrics_item


@pytest.mark.usefixtures("clear_perf_history")
def test_fps_list_raw_add_back(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXFPSList = pms.GetFPSHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXFPS = pms.GetCurrentFPS()
    size_before_add = adlx_list.Size()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)
    size_after_add = adlx_list.Size()
    assert size_after_add == size_before_add + 1


@pytest.mark.usefixtures("clear_perf_history")
def test_fps_list_raw_at(adlx):
    """Test At List, return type should ADLX_RESULT, Return element should be appropiate."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    time_monitoring = 2
    pms: ADLX.IADLXPerformanceMonitoringServices = system.GetPerformanceMonitoringServices()
    pms.StartPerformanceMetricsTracking()
    time.sleep(time_monitoring + 1)
    adlx_list: ADLX.IADLXFPSList = pms.GetFPSHistoryRaw(time_monitoring * 1000, 0)
    all_metrics_item: ADLX.IADLXFPS = pms.GetCurrentFPS()
    ret_add_back: ADLX.ADLX_RESULT = adlx_list.Add_Back(all_metrics_item)
    assert ret_add_back
    assert isinstance(ret_add_back, ADLX.ADLX_RESULT)

    size = adlx_list.Size()
    same_res = adlx_list.At(size - 1)
    assert isinstance(same_res, ADLX.IADLXFPS)
    assert same_res == all_metrics_item
