#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU VRAM Tuning tests  """
import pytest

from typing import List, Dict

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_empty_vram_tuning_states_vram_tuning1(adlx):
    """call GetEmptyVRAMTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            empty_vram_tuning_states: list = manual_vram_tuning.GetEmptyVRAMTuningStates()
            if not empty_vram_tuning_states:
                continue
            assert empty_vram_tuning_states
            assert isinstance(empty_vram_tuning_states, list)
            for state in empty_vram_tuning_states:
                assert isinstance(state, ADLX.IADLXManualTuningState)


def test_get_memory_timing_description_vram_tuning1(adlx):
    """call GetMemoryTimingDescription() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            memory_timing_desc: ADLX.ADLX_MEMORYTIMING_DESCRIPTION = manual_vram_tuning.GetMemoryTimingDescription()
            assert memory_timing_desc
            assert isinstance(memory_timing_desc, ADLX.ADLX_MEMORYTIMING_DESCRIPTION)


def test_get_supported_memory_timing_description_list_vram_tuning1(adlx):
    """call GetSupportedMemoryTimingDescriptionList() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            memory_timing_desc_list: list = manual_vram_tuning.GetSupportedMemoryTimingDescriptionList()

            assert memory_timing_desc_list
            assert isinstance(memory_timing_desc_list, list)
            for state in memory_timing_desc_list:
                assert isinstance(state, ADLX.IADLXMemoryTimingDescription)


def test_get_vram_tuning_ranges_vram_tuning1(adlx):
    """call GetVRAMTuningRanges() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            vram_tuning_ranges: Dict = manual_vram_tuning.GetVRAMTuningRanges()
            assert vram_tuning_ranges["frequency_range"]
            assert isinstance(vram_tuning_ranges["frequency_range"]["max_value"], int)
            assert isinstance(vram_tuning_ranges["frequency_range"]["min_value"], int)
            assert isinstance(vram_tuning_ranges["frequency_range"]["step"], int)
            assert vram_tuning_ranges["voltage_range"]
            assert isinstance(vram_tuning_ranges["voltage_range"]["max_value"], int)
            assert isinstance(vram_tuning_ranges["voltage_range"]["min_value"], int)
            assert isinstance(vram_tuning_ranges["voltage_range"]["step"], int)


def test_get_vram_tuning_states_vram_tuning1(adlx):
    """call GetVRAMTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            vram_tuning_states_list: list = manual_vram_tuning.GetVRAMTuningStates()
            assert vram_tuning_states_list
            assert isinstance(vram_tuning_states_list, list)
            for state in vram_tuning_states_list:
                assert isinstance(state, ADLX.IADLXManualTuningState)


def test_is_supported_memory_timing_vram_tuning1(adlx):
    """call IsSupportedMemoryTiming() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            supported_mem_timing: bool = manual_vram_tuning.IsSupportedMemoryTiming()
            assert isinstance(supported_mem_timing, bool)


def test_is_valid_vram_tuning_states_vram_tuning1(adlx):
    """call IsValidVRAMTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            vram_tuning_states_list: ADLX.IADLXManualTuningStateList = manual_vram_tuning.GetVRAMTuningStates()
            valid_vram_tuning_states: int = manual_vram_tuning.IsValidVRAMTuningStates(vram_tuning_states_list)
            assert valid_vram_tuning_states
            assert isinstance(valid_vram_tuning_states, int)
            for state in vram_tuning_states_list:
                assert isinstance(state, ADLX.IADLXManualTuningState)


def test_set_memory_timing_level_vram_tuning1(adlx):
    """call SetMemoryTimingLevel() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            ret_api: ADLX.ADLX_RESULT = manual_vram_tuning.SetMemoryTimingLevel(ADLX.MEMORYTIMING_AUTOMATIC)
            assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_set_vram_tuning_states_vram_tuning1(adlx):
    """call SetVRAMTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning1(gpu)
        if manual_vram_tuning:
            vram_tuning_states_list: ADLX.IADLXManualTuningStateList = manual_vram_tuning.GetVRAMTuningStates()
            ret_api: ADLX.ADLX_RESULT = manual_vram_tuning.SetVRAMTuningStates(vram_tuning_states_list)
            assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_get_max_vram_frequency_vram_tuning2(adlx):
    """call GetMaxVRAMFrequency() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            max_vram_freq: int = manual_vram_tuning.GetMaxVRAMFrequency()
            assert isinstance(max_vram_freq, int)


def test_get_max_vram_frequency_range_vram_tuning2(adlx):
    """call GetMaxVRAMFrequencyRange() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            max_vram_freq_range: Dict = manual_vram_tuning.GetMaxVRAMFrequencyRange()
            assert isinstance(max_vram_freq_range["max_value"], int)
            assert isinstance(max_vram_freq_range["min_value"], int)
            assert isinstance(max_vram_freq_range["step"], int)


def test_get_memory_timing_description_vram_tuning2(adlx):
    """call GetMemoryTimingDescription() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            memory_timing_desc: ADLX.ADLX_MEMORYTIMING_DESCRIPTION = manual_vram_tuning.GetMemoryTimingDescription()
            assert memory_timing_desc
            assert isinstance(memory_timing_desc, ADLX.ADLX_MEMORYTIMING_DESCRIPTION)


def test_get_supported_memory_timing_description_list_vram_tuning2(adlx):
    """call GetSupportedMemoryTimingDescriptionList() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            memory_timing_desc_list: list = manual_vram_tuning.GetSupportedMemoryTimingDescriptionList()
            assert memory_timing_desc_list
            assert isinstance(memory_timing_desc_list, list)
            for state in memory_timing_desc_list:
                assert isinstance(state, ADLX.IADLXMemoryTimingDescription)


def test_is_supported_memory_timing_vram_tuning2(adlx):
    """call IsSupportedMemoryTiming() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            supported_mem_timing: bool = manual_vram_tuning.IsSupportedMemoryTiming()
            assert isinstance(supported_mem_timing, bool)


def test_set_max_vram_frequency_vram_tuning2(adlx):
    """call SetMaxVRAMFrequency() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualVRAMTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            max_vram_freq: int = manual_vram_tuning.GetMaxVRAMFrequency()
            ret_api: ADLX.ADLX_RESULT = manual_vram_tuning.SetMaxVRAMFrequency(max_vram_freq)
            assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_set_memory_timing_level_vram_tuning2(adlx):
    """call SetMemoryTimingLevel() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualVRAMTuning(gpu):
            continue
        manual_vram_tuning: ADLX.IADLXManualVRAMTuning2 = tuning_services.GetManualVRAMTuning2(gpu)
        if manual_vram_tuning:
            ret_api: ADLX.ADLX_RESULT = manual_vram_tuning.SetMemoryTimingDescription(ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_DEFAULT)
            assert ret_api == ADLX.ADLX_RESULT.ADLX_OK
