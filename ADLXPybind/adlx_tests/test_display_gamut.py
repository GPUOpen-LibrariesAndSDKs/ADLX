#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind API tests Display Gamut interface.
Purpose of this file is to check if calling ADLX API does not report unexpected errors.
"""
# pylint: disable=I1101
from typing import List

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback
def callback_display_gamut_changed(p_display_gamut_changed_event) -> bool:
    display: ADLX.IADLXDisplay = p_display_gamut_changed_event.GetDisplay()
    assert display
    color_space_changed: bool = p_display_gamut_changed_event.IsColorSpaceChanged()
    assert isinstance(color_space_changed, bool)
    white_point_changed: bool = p_display_gamut_changed_event.IsWhitePointChanged()
    assert isinstance(white_point_changed, bool)

    return True


def test_display_3d_lut_changed_add_gamut(adlx):
    """Test Gamut events AddDisplayGamutEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayServices = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayGamutChangedListenerCallback = ADLX.PyDisplayGamutChangedListenerCallback()
    callback.call = callback_display_gamut_changed

    res_add_gamut_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayGamutEventListener(callback)
    assert res_add_gamut_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_display_3d_lut_changed_remove_gamut(adlx):
    """Test Gamut events RemoveDisplayGamutEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayServices = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayGamutChangedListenerCallback = ADLX.PyDisplayGamutChangedListenerCallback()
    callback.call = callback_display_gamut_changed

    res_add_gamut_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayGamutEventListener(callback)
    assert res_add_gamut_listener == ADLX.ADLX_RESULT.ADLX_OK

    res_remove_display_listener: ADLX.ADLX_RESULT = display_change_handler.RemoveDisplayGamutEventListener(callback)
    assert res_remove_display_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_get_gamut_color_space_gamut(adlx):
    """call GetGamutColorSpace() on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        color_space: ADLX.ADLX_GamutColorSpace = gamut.GetGamutColorSpace()
        assert color_space
        assert isinstance(color_space, ADLX.ADLX_GamutColorSpace)
        assert isinstance(color_space.blue.x, int)
        assert isinstance(color_space.blue.y, int)
        assert isinstance(color_space.green.x, int)
        assert isinstance(color_space.green.y, int)
        assert isinstance(color_space.red.x, int)
        assert isinstance(color_space.red.y, int)


@pytest.mark.parametrize(
    "api_name",
    [
        "IsCurrent5000kWhitePoint",
        "IsCurrent6500kWhitePoint",
        "IsCurrent7500kWhitePoint",
        "IsCurrent9300kWhitePoint",
        "IsCurrentAdobeRgbColorSpace",
        "IsCurrentCCIR2020ColorSpace",
        "IsCurrentCCIR601ColorSpace",
        "IsCurrentCCIR709ColorSpace",
        "IsCurrentCIERgbColorSpace",
        "IsCurrentCustomColorSpace",
        "IsCurrentCustomWhitePoint",
        "IsSupported5000kWhitePoint",
        "IsSupported6500kWhitePoint",
        "IsSupported7500kWhitePoint",
        "IsSupported9300kWhitePoint",
        "IsSupportedAdobeRgbColorSpace",
        "IsSupportedCCIR2020ColorSpace",
        "IsSupportedCCIR601ColorSpace",
        "IsSupportedCCIR709ColorSpace",
        "IsSupportedCIERgbColorSpace",
        "IsSupportedCustomColorSpace",
        "IsSupportedCustomWhitePoint",
    ],
)
def test_bool_api_name_gamut(adlx, api_name):
    """call <api_name> on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        api_ret: bool = getattr(gamut, api_name)()
        assert isinstance(api_ret, bool)


def test_set_gamut1_gamut(adlx):
    """call SetGamut1() on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        color_space: ADLX.ADLX_GamutColorSpace = gamut.GetGamutColorSpace()

        ret_api: ADLX.RESULT = gamut.SetGamut1(ADLX.ADLX_RGB(), color_space)
        assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_set_gamut2_gamut(adlx):
    """call SetGamut2() on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        ret_api: ADLX.RESULT = gamut.SetGamut2(ADLX.ADLX_RGB(), ADLX.GAMUT_SPACE_CUSTOM)
        assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_set_gamut3_gamut(adlx):
    """call SetGamut3() on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        ret_api: ADLX.RESULT = gamut.SetGamut3(ADLX.WHITE_POINT_CUSTOM, gamut.GetGamutColorSpace())
        assert ret_api == ADLX.ADLX_RESULT.ADLX_OK


def test_set_gamut4_gamut(adlx):
    """call SetGamut4() on IADLXDisplayGamut interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        gamut: ADLX.IADLXDisplayGamut = display_service.GetGamut(display)
        ret_api: ADLX.RESULT = gamut.SetGamut4(ADLX.WHITE_POINT_CUSTOM, ADLX.GAMUT_SPACE_CUSTOM)
        assert ret_api == ADLX.ADLX_RESULT.ADLX_OK
