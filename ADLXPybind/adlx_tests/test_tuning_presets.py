#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU Preset Tuning tests  """
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_preset_tuning(adlx):
    """call GetPresetTuning() on IADLXGPUTuningServices"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        preset_tuning_service: ADLX.IADLXGPUPresetTuning = tuning_services.GetPresetTuning(gpu)
        assert preset_tuning_service
        assert isinstance(preset_tuning_service, ADLX.IADLXGPUPresetTuning)


@pytest.mark.parametrize(
    "api_name",
    [
        "IsCurrentBalanced",
        "IsCurrentPowerSaver",
        "IsCurrentQuiet",
        "IsCurrentRage",
        "IsCurrentTurbo",
        "IsSupportedBalanced",
        "IsSupportedPowerSaver",
        "IsSupportedQuiet",
        "IsSupportedRage",
        "IsSupportedTurbo",
    ],
)
def test_is_supported_api_name_preset_tuning(adlx, api_name):
    """call <api_name> PresetTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        preset_tuning_service: ADLX.IADLXGPUPresetTuning = tuning_services.GetPresetTuning(gpu)
        api_name_res: bool = getattr(preset_tuning_service, api_name)()
        if api_name_res:
            assert isinstance(api_name_res, bool)


@pytest.mark.parametrize(
    "api_name",
    [
        "SetBalanced",
        "SetPowerSaver",
        "SetQuiet",
        "SetRage",
        "SetTurbo",
    ],
)
def test_set_api_name_preset_tuning(adlx, api_name):
    """call <api_name> AuPresetTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        preset_tuning_service: ADLX.IADLXGPUPresetTuning = tuning_services.GetPresetTuning(gpu)
        api_name_res: ADLX.ADLX_RESULT = getattr(preset_tuning_service, api_name)()
        assert api_name_res
        assert isinstance(api_name_res, ADLX.ADLX_RESULT)
