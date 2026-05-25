#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU Manual Tuning tests  """
import pytest

from typing import List, Dict

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_empty_fan_tuning_states_m_fan_tuning(adlx):
    """call GetEmptyFanTuningStates() on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        empty_fan_tuning_states: list = manual_fan_tuning.GetEmptyFanTuningStates()
        if not empty_fan_tuning_states:
            continue
        assert empty_fan_tuning_states
        assert isinstance(empty_fan_tuning_states, list)
        for state in empty_fan_tuning_states:
            assert isinstance(state, ADLX.IADLXManualFanTuningState)


def test_get_fan_tuning_ranges_m_fan_tuning(adlx):
    """call GetFanTuningRanges() on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        fan_tuning_ranges: Dict = manual_fan_tuning.GetFanTuningRanges()
        assert fan_tuning_ranges["speed_range"]
        assert isinstance(fan_tuning_ranges["speed_range"]["max_value"], int)
        assert isinstance(fan_tuning_ranges["speed_range"]["min_value"], int)
        assert isinstance(fan_tuning_ranges["speed_range"]["step"], int)
        assert fan_tuning_ranges["temperature_range"]
        assert isinstance(fan_tuning_ranges["temperature_range"]["max_value"], int)
        assert isinstance(fan_tuning_ranges["temperature_range"]["min_value"], int)
        assert isinstance(fan_tuning_ranges["temperature_range"]["step"], int)


def test_get_fan_tuning_states_m_fan_tuning(adlx):
    """call GetFanTuningStates() on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        fan_tuning_states = manual_fan_tuning.GetFanTuningStates()
        assert fan_tuning_states
        assert isinstance(fan_tuning_states, list)
        for state in fan_tuning_states:
            assert isinstance(state, ADLX.IADLXManualFanTuningState)


@pytest.mark.parametrize("api_name", ["GetMinAcousticLimit", "GetMinFanSpeed", "GetTargetFanSpeed"])
def test_get_api_name_int_m_fan_tuning(adlx, api_name):
    """call <api_name> on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        api_name_ret: int = getattr(manual_fan_tuning, api_name)()
        assert isinstance(api_name_ret, int)


@pytest.mark.parametrize(
    "api_name",
    ["GetMinAcousticLimitRange", "GetMinFanSpeedRange", "GetTargetFanSpeedRange"],
)
def test_get_api_name_range_m_fan_tuning(adlx, api_name):
    """call <api_name> on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        api_name_range: Dict = getattr(manual_fan_tuning, api_name)()
        assert api_name_range
        assert isinstance(api_name_range["max_value"], int)
        assert isinstance(api_name_range["min_value"], int)
        assert isinstance(api_name_range["step"], int)


@pytest.mark.parametrize(
    "api_name",
    [
        "GetZeroRPMState",
        "IsSupportedMinAcousticLimit",
        "IsSupportedMinFanSpeed",
        "IsSupportedTargetFanSpeed",
        "IsSupportedZeroRPM",
    ],
)
def test_get_api_name_bool_m_fan_tuning(adlx, api_name):
    """call <api_name> on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        api_name_ret: bool = getattr(manual_fan_tuning, api_name)()
        assert isinstance(api_name_ret, bool)


def test_is_valid_fan_tuning_states_m_fan_tuning(adlx):
    """call IsValidFanTuningStates() on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)

        fan_tuning_states = manual_fan_tuning.GetFanTuningStates()
        if not fan_tuning_states:
            continue

        valid_fan_tuning_states: int = manual_fan_tuning.IsValidFanTuningStates(fan_tuning_states)
        assert valid_fan_tuning_states
        assert isinstance(valid_fan_tuning_states, int)


def test_set_fan_tuning_states_m_fan_tuning(adlx):
    """call SetFanTuningStates() on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)

        fan_tuning_states = manual_fan_tuning.GetFanTuningStates()

        ret_fan_tuning_states: ADLX.ADLX_RESULT = manual_fan_tuning.SetFanTuningStates(fan_tuning_states)
        assert isinstance(ret_fan_tuning_states, ADLX.ADLX_RESULT)
        assert ret_fan_tuning_states == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize(
    "api_name,value_to_set",
    [
        ["SetMinAcousticLimit", 570],
        # ["SetMinFanSpeed", 700 - 100], # dangerous, use with caution
        ["SetTargetFanSpeed", 3600],
    ],
)
def test_api_name_int_m_fan_tuning(adlx, api_name, value_to_set):
    """call <api_name> on ManualFanTuning interface. We expect non-empty response. No errors"""

    def _reset_tuning(tuning_services, gpu):
        ret_reset: ADLX.ADLX_RESULT = tuning_services.ResetToFactory(gpu)
        assert ret_reset == ADLX.ADLX_RESULT.ADLX_OK

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        try:
            manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
            api_ret: ADLX.ADLX_RESULT = getattr(manual_fan_tuning, api_name)(value_to_set)
            assert isinstance(api_ret, ADLX.ADLX_RESULT)
            assert api_ret == ADLX.ADLX_RESULT.ADLX_OK or api_ret == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED

            _reset_tuning(tuning_services, gpu)
        except:
            _reset_tuning(tuning_services, gpu)
            raise


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_zero_rpm_state_m_fan_tuning(adlx, adlx_bool):
    """call SetZeroRPMState() on ManualFanTuning interface. We expect non-empty response. No errors"""

    def _reset_tuning(tuning_services, gpu):
        ret_reset: ADLX.ADLX_RESULT = tuning_services.ResetToFactory(gpu)
        assert ret_reset == ADLX.ADLX_RESULT.ADLX_OK

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        try:
            manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)

            api_ret: ADLX.ADLX_RESULT = manual_fan_tuning.SetZeroRPMState(adlx_bool)
            assert isinstance(api_ret, ADLX.ADLX_RESULT)
            assert api_ret == ADLX.ADLX_RESULT.ADLX_OK

            _reset_tuning(tuning_services, gpu)
        except:
            _reset_tuning(tuning_services, gpu)
            raise


@pytest.mark.parametrize(
    "get_api_name,set_api_name",
    [
        ["GetFanSpeed", "SetFanSpeed"],
        ["GetTemperature", "SetTemperature"],
    ],
)
def test_callback_apis_api_name_fan_tuning(adlx, get_api_name, set_api_name):
    """call <get_api_name> <set_api_name> on ManualFanTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not tuning_services.IsSupportedManualFanTuning(gpu):
            continue
        manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
        fan_tuning_states = manual_fan_tuning.GetFanTuningStates()

        for state in fan_tuning_states:
            ret_get: int = getattr(state, get_api_name)()
            assert isinstance(ret_get, int)

            ret_set: ADLX.RESULT = getattr(state, set_api_name)(ret_get)
            assert ret_set == ADLX.ADLX_OK
