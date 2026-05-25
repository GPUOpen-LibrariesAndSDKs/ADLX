#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display3DLUTChangedListener tests  """
import pytest

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback
def callback_display_3d_lut_changed(p_display_3d_lut_changed_event) -> bool:
    display: ADLX.IADLXDisplay = p_display_3d_lut_changed_event.GetDisplay()
    assert display
    is_custom_3d_lut_changed: bool = p_display_3d_lut_changed_event.IsCustom3DLUTChanged()
    assert isinstance(is_custom_3d_lut_changed, bool)
    is_sce_changed: bool = p_display_3d_lut_changed_event.IsSCEChanged()
    assert isinstance(is_sce_changed, bool)

    return True


def test_display_3d_lut_changed_add(adlx):
    """Test Display3DLUT events AddDisplay3DLUTEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayServices = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplay3DLUTChangedListenerCallback = ADLX.PyDisplay3DLUTChangedListenerCallback()
    callback.call = callback_display_3d_lut_changed

    res_add_display_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplay3DLUTEventListener(callback)
    assert res_add_display_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_display_3d_lut_changed_remove(adlx):
    """Test Display3DLUT events AddDisplay3DLUTEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayServices = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplay3DLUTChangedListenerCallback = ADLX.PyDisplay3DLUTChangedListenerCallback()
    callback.call = callback_display_3d_lut_changed

    res_add_display_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplay3DLUTEventListener(callback)
    assert res_add_display_listener == ADLX.ADLX_RESULT.ADLX_OK

    res_remove_display_listener: ADLX.ADLX_RESULT = display_change_handler.RemoveDisplay3DLUTEventListener(callback)
    assert res_remove_display_listener == ADLX.ADLX_RESULT.ADLX_OK
