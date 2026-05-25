#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Tests for IADLXChangedEvent interface """
# pylint: disable=I1101
import pytest
from typing import List
import time

from test_display_gamma import create_re_gamma_ramp

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback Gamma
def callback_display_gamma_changed(p_display_gamma_changed_listener) -> bool:
    origin: ADLX.ADLX_SYNC_ORIGIN = p_display_gamma_changed_listener.GetOrigin()
    assert isinstance(origin, ADLX.ADLX_SYNC_ORIGIN)
    assert origin == ADLX.ADLX_SYNC_ORIGIN.SYNC_ORIGIN_INTERNAL

    return True


# Callback Tuning
def callback_tuning_changed_listener(p_gpu_tuning_changed_event) -> bool:
    origin: ADLX.ADLX_SYNC_ORIGIN = p_gpu_tuning_changed_event.GetOrigin()
    assert isinstance(origin, ADLX.ADLX_SYNC_ORIGIN)
    assert origin == ADLX.ADLX_SYNC_ORIGIN.SYNC_ORIGIN_INTERNAL

    return True


def test_gamma_changed_event_get_origin(adlx):
    """Trigger Gamma change. Expect even to kick in.
    Call GetOrigin() on the event and expect SYNC_ORIGIN_INTERNAL"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayGammaChangedListenerCallback = ADLX.PyDisplayGammaChangedListenerCallback()
    callback.call = callback_display_gamma_changed

    res_add_gamut_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayGammaEventListener(callback)
    assert res_add_gamut_listener == ADLX.ADLX_RESULT.ADLX_OK

    # test callback methods, trigger some gamma change
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_change_handler, display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        gamma_ramp_data: List[float] = create_re_gamma_ramp(2.4)

        ret_set: ADLX.ADLX_RESULT = gamma.SetReGammaRampMemory(gamma_ramp_data)
        assert isinstance(ret_set, ADLX.ADLX_RESULT)
        del gamma

    # currently in unit tests we have one thread, let's give callback some time to execute
    time.sleep(4)
    del display_list, display_change_handler, display_service, system


def test_gpu_tuning_auto_event_get_origin(adlx):
    """Trigger Tuning change by calling SetMinAcousticLimit. Expect even to kick in.
    Call GetOrigin() on the event and expect SYNC_ORIGIN_INTERNAL"""

    def _reset_tuning(tuning_services, gpu):
        if not tuning_services.IsAtFactory(gpu):
            ret_reset: ADLX.ADLX_RESULT = tuning_services.ResetToFactory(gpu)
            assert ret_reset == ADLX.ADLX_RESULT.ADLX_OK
            time.sleep(3)

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    tuning_handler: ADLX.IADLXGPUTuningChangedHandling = tuning_services.GetGPUTuningChangedHandling()

    callback: ADLX.PyGPUTuningChangedListenerCallback = ADLX.PyGPUTuningChangedListenerCallback()
    callback.call = callback_tuning_changed_listener

    ret_add: ADLX.ADLX_RESULT = tuning_handler.AddGPUTuningEventListener(callback)
    assert isinstance(ret_add, ADLX.ADLX_RESULT)
    assert ret_add == ADLX.ADLX_RESULT.ADLX_OK

    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue

        try:
            manual_fan_tuning: ADLX.IADLXManualFanTuning = tuning_services.GetManualFanTuning(gpu)
            if manual_fan_tuning.IsSupportedMinAcousticLimit():
                acustic_limit: int = manual_fan_tuning.GetMinAcousticLimit()

                api_ret: ADLX.ADLX_RESULT = manual_fan_tuning.SetMinAcousticLimit(acustic_limit + 10)
                assert api_ret == ADLX.ADLX_RESULT.ADLX_OK
                time.sleep(3)

            _reset_tuning(tuning_services, gpu)
        except:
            _reset_tuning(tuning_services, gpu)
            raise
        finally:
            del manual_fan_tuning

    del gpus, tuning_handler, tuning_services, system
