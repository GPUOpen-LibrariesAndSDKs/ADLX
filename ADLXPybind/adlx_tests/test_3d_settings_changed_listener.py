#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display3DLUTChangedListener tests  """
import threading
import time

import pytest

from typing import List

from test_3d_settings import is_feature_supported

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback factory that captures the event for synchronization
def create_3d_settings_callback(completion_event: threading.Event):
    """Factory function to create a callback that signals the completion event"""
    def callback_3d_settings_changed_listener(p_3d_settings_changed_event) -> bool:
        is_anti_lag_changed: bool = p_3d_settings_changed_event.IsAntiLagChanged()
        assert isinstance(is_anti_lag_changed, bool)
        is_chill_changed: bool = p_3d_settings_changed_event.IsChillChanged()
        assert isinstance(is_chill_changed, bool)
        is_fsr_changed: bool = p_3d_settings_changed_event.IsFidelityFXSuperResolutionChanged()
        assert isinstance(is_fsr_changed, bool)

        # Signal the test function that callback has completed
        completion_event.set()

        return True

    return callback_3d_settings_changed_listener


def test_3d_settings_changed(adlx):
    """Test 3D settings events Remove3DSettingsEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()

    # Get the changed handling object — listener methods live here, not on the services object
    changed_handling: ADLX.IADLX3DSettingsChangedHandling = three_d_settings_services.Get3DSettingsChangedHandling()

    # Create a threading event for synchronization with callback
    completion_event = threading.Event()

    callback: ADLX.Py3DSettingsChangedListenerCallback = ADLX.Py3DSettingsChangedListenerCallback()
    callback.call = create_3d_settings_callback(completion_event)

    res_add_listener: ADLX.ADLX_RESULT = changed_handling.Add3DSettingsEventListener(callback)
    assert res_add_listener == ADLX.ADLX_RESULT.ADLX_OK


    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        chill_enabled: bool = chill.IsEnabled()
        set_enabled: ADLX.ADLX_RESULT = chill.SetEnabled(not chill_enabled)
        # Wait for chill event to trigger and callback to signal completion
        if set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            # Wait for callback to signal completion (max 50 seconds)
            if completion_event.wait(timeout=50):
                print(f"Chill changed")

                time.sleep(5)  # Small delay to ensure stability before resetting tuning
            else:
                print(f"Chill change timed out after 50 seconds")

        fsr: ADLX.IADLX3DFidelityFXSuperResolution = three_d_settings_services.GetFidelityFXSuperResolution(gpu)

        if not fsr.IsSupported():
            continue
        is_enabled: bool = fsr.IsEnabled()
        set_enabled: ADLX.ADLX_RESULT = fsr.SetEnabled(not is_enabled)
        # Wait for FSR event to trigger and callback to signal completion
        if set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            # Wait for callback to signal completion (max 50 seconds)
            if completion_event.wait(timeout=50):
                print(f"FSR changed")

                time.sleep(5)  # Small delay to ensure stability before resetting tuning
            else:
                print(f"FSR change timed out after 50 seconds")

    res_remove_listener: ADLX.ADLX_RESULT = changed_handling.Remove3DSettingsEventListener(callback)
    assert res_remove_listener == ADLX.ADLX_RESULT.ADLX_OK
