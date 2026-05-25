#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind API tests IADLXDisplayColorDepth.
Purpose of this file is to check if calling ADLX API does not report unexpected errors.
"""
# pylint: disable=I1101
from typing import List

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_color_depth(adlx: ADLX.ADLXHelper):
    """call GetColorDepth() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        color_depth: ADLX.IADLXDisplayColorDepth = display_service.GetColorDepth(display)
        assert color_depth
        assert isinstance(color_depth, ADLX.IADLXDisplayColorDepth)
        del color_depth
    del display_list, display_service, system


def test_get_value_color_depth(adlx: ADLX.ADLXHelper):
    """call GetColorDepth() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        color_depth: ADLX.IADLXDisplayColorDepth = display_service.GetColorDepth(display)
        if not color_depth.IsSupported():
            del color_depth
            continue
        value: ADLX.ADLX_COLOR_DEPTH = color_depth.GetValue()
        assert isinstance(value, ADLX.ADLX_COLOR_DEPTH)
        del color_depth
    del display_list, display_service, system


@pytest.mark.parametrize(
    "api_name",
    [
        "IsSupported",
        "IsSupportedBPC_10",
        "IsSupportedBPC_12",
        "IsSupportedBPC_14",
        "IsSupportedBPC_16",
        "IsSupportedBPC_6",
        "IsSupportedBPC_8",
    ],
)
def test_is_supported_api_name_display_color_depth(adlx: ADLX.ADLXHelper, api_name):
    """call <api_name> IADLXDisplayColorDepth interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        color_depth: ADLX.IADLXDisplayColorDepth = display_service.GetColorDepth(display)
        api_name_res: bool = getattr(color_depth, api_name)()
        assert isinstance(api_name_res, bool)
        del color_depth
    del display_list, display_service, system


@pytest.mark.parametrize(
    "color_depth_value",
    [
        ADLX.ADLX_COLOR_DEPTH.BPC_6,
        ADLX.ADLX_COLOR_DEPTH.BPC_8,
        ADLX.ADLX_COLOR_DEPTH.BPC_10,
        ADLX.ADLX_COLOR_DEPTH.BPC_12,
        ADLX.ADLX_COLOR_DEPTH.BPC_14,
        ADLX.ADLX_COLOR_DEPTH.BPC_16,
    ],
)
def test_is_supported_color_depth_display_color_depth(adlx: ADLX.ADLXHelper, color_depth_value):
    """call IsSupportedColorDepth in  IADLXDisplayColorDepth interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        color_depth: ADLX.IADLXDisplayColorDepth = display_service.GetColorDepth(display)
        is_color_depth_supported: bool = color_depth.IsSupportedColorDepth(color_depth_value)
        assert isinstance(is_color_depth_supported, bool)
        del color_depth
    del display_list, display_service, system


@pytest.mark.parametrize(
    "color_depth_value",
    [
        ADLX.ADLX_COLOR_DEPTH.BPC_6,
        ADLX.ADLX_COLOR_DEPTH.BPC_8,
        ADLX.ADLX_COLOR_DEPTH.BPC_10,
        ADLX.ADLX_COLOR_DEPTH.BPC_12,
        ADLX.ADLX_COLOR_DEPTH.BPC_14,
        ADLX.ADLX_COLOR_DEPTH.BPC_16,
    ],
)
def test_set_value_color_depth_display_color_depth(adlx: ADLX.ADLXHelper, color_depth_value):
    """call SetValue in  IADLXDisplayColorDepth interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        color_depth: ADLX.IADLXDisplayColorDepth = display_service.GetColorDepth(display)
        ret_set_color_depth_value: ADLX.ADLX_RESULT = color_depth.SetValue(color_depth_value)
        assert isinstance(ret_set_color_depth_value, ADLX.ADLX_RESULT)
        del color_depth
    del display_list, display_service, system
