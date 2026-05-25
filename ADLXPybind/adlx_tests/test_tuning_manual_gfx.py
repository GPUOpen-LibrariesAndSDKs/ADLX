#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU GFX Tuning tests  """
import pytest

from typing import List, Dict

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_empty_gpu_tuning_states_gfx_tuning(adlx):
    """call GetEmptyGPUTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            manual_tuning_state_list: ADLX.IADLXManualTuningStateList = manual_gfx_tuning.GetEmptyGPUTuningStates()
            assert manual_tuning_state_list
            assert isinstance(manual_tuning_state_list, ADLX.IADLXManualTuningStateList)


def test_get_gpu_tuning_ranges_gfx_tuning(adlx):
    """call GetGPUTuningRanges() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            gpu_tuning_ranges: Dict = manual_gfx_tuning.GetGPUTuningRanges()
            assert gpu_tuning_ranges["frequency_range"]
            assert isinstance(gpu_tuning_ranges["frequency_range"]["max_value"], int)
            assert isinstance(gpu_tuning_ranges["frequency_range"]["min_value"], int)
            assert isinstance(gpu_tuning_ranges["frequency_range"]["step"], int)
            assert gpu_tuning_ranges["voltage_range"]
            assert isinstance(gpu_tuning_ranges["voltage_range"]["max_value"], int)
            assert isinstance(gpu_tuning_ranges["voltage_range"]["min_value"], int)
            assert isinstance(gpu_tuning_ranges["voltage_range"]["step"], int)


def test_is_valid_gpu_tuning_states_gfx_tuning(adlx):
    """call IsValidGPUTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            valid_gpu_states: int = manual_gfx_tuning.IsValidGPUTuningStates()
            assert valid_gpu_states
            assert isinstance(valid_gpu_states, int)


def test_get_gpu_tuning_states_gfx_tuning(adlx):
    """call GetGPUTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            tuning_sates_list: ADLX.IADLXManualTuningStateList = manual_gfx_tuning.GetGPUTuningStates()
            assert tuning_sates_list
            assert isinstance(tuning_sates_list, ADLX.IADLXManualTuningStateList)


def test_set_gpu_tuning_states_gfx_tuning(adlx):
    """call SetGPUTuningStates() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning1 = tuning_services.GetManualGFXTuning1(gpu)
        if manual_gfx_tuning:
            tuning_sates_list: ADLX.IADLXManualTuningStateList = manual_gfx_tuning.GetGPUTuningStates()
            ret_api: ADLX.ADLX_RESULT = manual_gfx_tuning.SetGPUTuningStates(tuning_sates_list)
            assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize("api_name", ["GetGPUMaxFrequency", "GetGPUMinFrequency", "GetGPUVoltage"])
def test_api_name_gpu_data_gfx_tuning(adlx, api_name):
    """call <api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning2 = tuning_services.GetManualGFXTuning2(gpu)
        if manual_gfx_tuning:
            api_name_res: int = getattr(manual_gfx_tuning, api_name)()
            if api_name_res is not None:
                assert isinstance(api_name_res, int)


@pytest.mark.parametrize(
    "api_name",
    ["GetGPUMaxFrequencyRange", "GetGPUMinFrequencyRange", "GetGPUVoltageRange"],
)
def test_api_name_gpu_range_data_gfx_tuning(adlx, api_name):
    """call <api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning2 = tuning_services.GetManualGFXTuning2(gpu)
        if manual_gfx_tuning:
            ret_range: Dict = getattr(manual_gfx_tuning, api_name)()
            if ret_range:
                assert isinstance(ret_range["max_value"], int)
                assert isinstance(ret_range["min_value"], int)
                assert isinstance(ret_range["step"], int)


@pytest.mark.parametrize(
    "get_api_name,set_api_name",
    [
        ["GetGPUMaxFrequency", "SetGPUMaxFrequency"],
        ["GetGPUMinFrequency", "SetGPUMinFrequency"],
        ["GetGPUVoltage", "SetGPUVoltage"],
    ],
)
def test_set_api_name_gfx_data_gfx_tuning(adlx, get_api_name, set_api_name):
    """call <set_api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_gfx_tuning: ADLX.IADLXManualGraphicsTuning2 = tuning_services.GetManualGFXTuning2(gpu)
        if manual_gfx_tuning:
            get_res: int = getattr(manual_gfx_tuning, get_api_name)()
            if get_res is not None:
                set_res: ADLX.ADLX_RESULT = getattr(manual_gfx_tuning, set_api_name)(get_res)
                assert set_res == ADLX.ADLX_RESULT.ADLX_OK