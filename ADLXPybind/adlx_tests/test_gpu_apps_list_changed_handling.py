#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IADLXGPUAppsListChangedHandling API tests. """
# pylint: disable=I1101
from asyncio import sleep

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback factory for GPUAppsListEventListener
def create_gpu_apps_list_callback():
    """Factory function to create a callback that validates arguments"""
    def callback_gpu_apps_list_changed_listener(gpu, app_list) -> bool:
        assert gpu is not None
        assert app_list is not None
        return True

    return callback_gpu_apps_list_changed_listener


def test_add_and_remove_gpu_apps_list_event_listener(adlx):
    """Add then Remove a GPUAppsListEventListener. Expect both to succeed."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    handling: ADLX.IADLXGPUAppsListChangedHandling = system.GetGPUAppsListChangedHandling()

    callback: ADLX.PyGPUAppsListEventListenerCallback = ADLX.PyGPUAppsListEventListenerCallback()
    callback.call = create_gpu_apps_list_callback()

    ret_add: ADLX.ADLX_RESULT = handling.AddGPUAppsListEventListener(callback)
    assert ret_add == ADLX.ADLX_RESULT.ADLX_OK

    sleep(2)  # Sleep briefly to allow any asynchronous events to be processed

    ret_remove: ADLX.ADLX_RESULT = handling.RemoveGPUAppsListEventListener(callback)
    assert ret_remove == ADLX.ADLX_RESULT.ADLX_OK

