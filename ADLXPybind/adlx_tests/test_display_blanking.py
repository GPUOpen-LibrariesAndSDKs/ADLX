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

def test_is_supported_display_blanking(adlx):
    """Call IsSupported on IADLXDisplayBlanking interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        is_Supported: bool = display_blanking.IsSupported()
        assert isinstance(is_Supported, bool)

def test_is_current_blanked_display_blanking(adlx):
    """Call IsCurrentBlanked on IADLXDisplayBlanking interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        is_current_blanked: bool = display_blanking.IsCurrentBlanked()
        if is_current_blanked is not None:
            assert isinstance(is_current_blanked, bool)

def test_is_current_unblanked_display_blanking(adlx):
    """Call IsCurrentUnblanked on IADLXDisplayBlanking interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        is_current_unblanked: bool = display_blanking.IsCurrentUnblanked()
        if is_current_unblanked is not None:
            assert isinstance(is_current_unblanked, bool)

def test_set_blanked_display_blanking(adlx):
    """Call SetBlanked on IADLXDisplayBlanking interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        set_blanked: ADLX.ADLX_RESULT = display_blanking.SetBlanked()
        assert isinstance(set_blanked, ADLX.ADLX_RESULT)

def test_set_unblanked_display_blanking(adlx):
    """Call SetUnblanked on IADLXDisplayBlanking interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        display_blanking: ADLX.IADLXDisplayBlanking = display_service.GetDisplayBlanking(display)
        set_unblanked: ADLX.ADLX_RESULT = display_blanking.SetUnblanked()
        assert isinstance(set_unblanked, ADLX.ADLX_RESULT)