#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind API tests IADLXDisplayCustomColor.
Purpose of this file is to check if calling ADLX API does not report unexpected errors.
"""
# pylint: disable=I1101
from typing import List

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_custom_color(adlx):
    """call GetCustomColor() on GetDesktopsServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_services: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_services.GetDisplays()
    if not display_list:
        del display_services, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_services.GetCustomColor(display)
        assert custom_color
        assert isinstance(custom_color, ADLX.IADLXDisplayCustomColor)
        del custom_color
    del display_list, display_services, system


@pytest.mark.parametrize(
    "api_name",
    [
        "IsBrightnessSupported",
        "IsContrastSupported",
        "IsHueSupported",
        "IsSaturationSupported",
        "IsTemperatureSupported",
    ],
)
def test_get_api_name_bool_custom_color(adlx, api_name):
    """call <api_name> on IADLXDisplayCustomColor interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_services: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_services.GetDisplays()
    if not display_list:
        del display_services, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_services.GetCustomColor(display)
        api_name_ret: bool = getattr(custom_color, api_name)()
        assert isinstance(api_name_ret, bool)
        del custom_color
    del display_list, display_services, system


@pytest.mark.parametrize(
    "api_name",
    ["GetBrightness", "GetContrast", "GetHue", "GetSaturation", "GetTemperature"],
)
def test_get_api_name_int_custom_color(adlx, api_name):
    """call <api_name> on IADLXDisplayCustomColor interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_services: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_services.GetDisplays()
    if not display_list:
        del display_services, system
        pytest.skip("No Displays found")
    # e.g. "GetBrightness" -> "IsBrightnessSupported"
    is_supported_name: str = "Is" + api_name[len("Get"):] + "Supported"
    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_services.GetCustomColor(display)
        if not getattr(custom_color, is_supported_name)():
            del custom_color
            continue
        api_name_ret: int = getattr(custom_color, api_name)()
        assert isinstance(api_name_ret, int)
        del custom_color
    del display_list, display_services, system


@pytest.mark.parametrize(
    "api_name",
    [
        "GetBrightnessRange",
        "GetContrastRange",
        "GetHueRange",
        "GetSaturationRange",
        "GetTemperatureRange",
    ],
)
def test_get_api_name_range_custom_color(adlx, api_name):
    """call <api_name> on IADLXDisplayCustomColor interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_services: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_services.GetDisplays()
    if not display_list:
        del display_services, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_services.GetCustomColor(display)
        api_name_range: ADLX.ADLX_IntRange = getattr(custom_color, api_name)()
        assert isinstance(api_name_range, ADLX.ADLX_IntRange)
        assert isinstance(api_name_range.maxValue, int)
        assert isinstance(api_name_range.minValue, int)
        assert isinstance(api_name_range.step, int)
        del custom_color
    del display_list, display_services, system


@pytest.mark.parametrize(
    "set_api_name,get_api_name",
    [
        ["SetBrightness", "GetBrightness"],
        ["SetContrast", "GetContrast"],
        ["SetHue", "GetHue"],
        ["SetSaturation", "GetSaturation"],
        ["SetTemperature", "GetTemperature"],
    ],
)
def test_api_name_int_custom_color(adlx, set_api_name, get_api_name):
    """call <set_api_name> on IADLXDisplayCustomColor interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_services: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_services.GetDisplays()
    if not display_list:
        del display_services, system
        pytest.skip("No Displays found")
    # e.g. "GetBrightness" -> "IsBrightnessSupported"
    is_supported_name: str = "Is" + get_api_name[len("Get"):] + "Supported"
    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_services.GetCustomColor(display)
        if not getattr(custom_color, is_supported_name)():
            del custom_color
            continue
        value_to_set: int = getattr(custom_color, get_api_name)()
        if value_to_set is None:
            del custom_color
            continue
        api_ret: ADLX.ADLX_RESULT = getattr(custom_color, set_api_name)(value_to_set)
        assert isinstance(api_ret, ADLX.ADLX_RESULT)
        del custom_color
    del display_list, display_services, system
