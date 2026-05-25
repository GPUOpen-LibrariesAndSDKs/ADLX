#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IADLXGPUsChangedHandling API tests. """
import os
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_log_callback(adlx):
    """Enable ADLX callback logging."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    log_callback: ADLX.PyLogCallback = ADLX.PyLogCallback()
    ret: ADLX.ADLX_RESULT = system.EnableLog(ADLX.ADLX_LOG_DESTINATION(2), ADLX.ADLX_LOG_SEVERITY(0), log_callback, "")
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


def test_AddGPUsListEventListener_gpu_handling(adlx):
    """Call AddGPUsListEventListener() on GetGPUsChangedHandling() interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    get_gpus_changed_handling: ADLX.IADLXGPUsChangedHandling = system.GetGPUsChangedHandling()
    gpus_event_listener_callback: ADLX.PyGPUsEventListenerCallback = ADLX.PyGPUsEventListenerCallback()
    ret_add_gpu: ADLX.ADLX_RESULT = get_gpus_changed_handling.AddGPUsListEventListener(gpus_event_listener_callback)
    assert isinstance(ret_add_gpu, ADLX.ADLX_RESULT)
    assert ret_add_gpu == ADLX.ADLX_RESULT.ADLX_OK
    # Clean up: remove listener to avoid ADLX_ORPHAN_OBJECTS on Terminate()
    get_gpus_changed_handling.RemoveGPUsListEventListener(gpus_event_listener_callback)
