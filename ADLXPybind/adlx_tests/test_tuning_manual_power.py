#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU Power Tuning tests  """
import pytest

from typing import List, Dict

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize("api_name", ["GetPowerLimit", "GetTDCLimit"])
def test_api_name_gpu_data_power_tuning(adlx, api_name):
    """call <api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        api_name_res: int = getattr(manual_power_tuning, api_name)()
        if api_name_res is not None:
            assert isinstance(api_name_res, int)


@pytest.mark.parametrize("api_name", ["GetPowerLimitRange", "GetTDCLimitRange"])
def test_api_name_gpu_range_data_power_tuning(adlx, api_name):
    """call <api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        ret_range: Dict = getattr(manual_power_tuning, api_name)()
        assert isinstance(ret_range["max_value"], int)
        assert isinstance(ret_range["min_value"], int)
        assert isinstance(ret_range["step"], int)


def test_is_supported_tdc_limit_power_tuning(adlx):
    """call IsSupportedTDCLimit() on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        supported_tdc_limit: bool = manual_power_tuning.IsSupportedTDCLimit()
        assert isinstance(supported_tdc_limit, bool)


@pytest.mark.parametrize(
    "get_api_name,set_api_name",
    [
        ["GetPowerLimit", "SetPowerLimit"],
        ["GetTDCLimit", "SetTDCLimit"],
    ],
)
def test_set_api_name_gfx_data_power_tuning(adlx, get_api_name, set_api_name):
    """call <set_api_name> on TuningService interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        manual_power_tuning: ADLX.IADLXManualPowerTuning = tuning_services.GetManualPowerTuning(gpu)
        if manual_power_tuning:
            get_res: int = getattr(manual_power_tuning, get_api_name)()
            if get_res is not None:
                set_res: ADLX.ADLX_RESULT = getattr(manual_power_tuning, set_api_name)(get_res)
                assert set_res == ADLX.ADLX_RESULT.ADLX_OK or set_res == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED