#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display service interfaces methods  """
# pylint: disable=I1101
from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_getmode_ds(adlx):
    """call GetMode() on IADLXDisplayScalingMode interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_scalin_mode: ADLX.IADLXDisplayPixelFormat = display_service.GetScalingMode(display)
        current_mode: ADLX.ADLX_SCALE_MODE = diplay_scalin_mode.GetMode()
        assert isinstance(current_mode, ADLX.ADLX_SCALE_MODE)


def test_is_supported_ds(adlx):
    """call IsSupported() on IADLXDisplayScalingMode interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_scalin_mode: ADLX.IADLXDisplayPixelFormat = display_service.GetScalingMode(display)
        supported: bool = diplay_scalin_mode.IsSupported()
        assert isinstance(supported, bool)


def test_set_mode_ds(adlx):
    """call SetMode() on IADLXDisplayScalingMode interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_scalin_mode: ADLX.IADLXDisplayPixelFormat = display_service.GetScalingMode(display)
        current_mode: ADLX.ADLX_SCALE_MODE = diplay_scalin_mode.GetMode()
        set_mode: ADLX.ADLX_RESULT = diplay_scalin_mode.SetMode(current_mode)
        assert isinstance(set_mode, ADLX.ADLX_RESULT)
