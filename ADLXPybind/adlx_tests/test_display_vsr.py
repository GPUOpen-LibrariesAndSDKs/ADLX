#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display service interfaces methods  """
# pylint: disable=I1101
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_is_enabled_VSR(adlx):
    """call IsEnabled() on IADLXDisplayVSR interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        display_vsr: ADLX.IADLXDisplayVSR = display_service.GetVirtualSuperResolution(display)
        if not display_vsr.IsSupported():
            del display_vsr
            continue
        is_enabled: bool = display_vsr.IsEnabled()
        assert isinstance(is_enabled, bool)
        del display_vsr
    del display_list, display_service, system


def test_is_supported_VSR(adlx):
    """Call IsSupported on IADLXDisplayVSR interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        display_vsr: ADLX.IADLXDisplayVSR = display_service.GetVirtualSuperResolution(display)
        is_supported: bool = display_vsr.IsSupported()
        assert isinstance(is_supported, bool)
        del display_vsr
    del display_list, display_service, system


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_VSR(adlx, adlx_bool):
    """Call SetEnabled on IADLXDisplayVSR interface.We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        display_vsr: ADLX.IADLXDisplayVSR = display_service.GetVirtualSuperResolution(display)
        ret: ADLX.ADLX_RESULT = display_vsr.SetEnabled(adlx_bool)
        assert isinstance(ret, ADLX.ADLX_RESULT)
        del display_vsr
    del display_list, display_service, system
