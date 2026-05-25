#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display3DLUT settings tests """
# pylint: disable=I1101
import pytest

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.fixture(autouse=True)
def display_3d_settings_reset(adlx):
    """Fixture reset display 3d settings"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        three_d_lut_display: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        three_d_lut_display.ClearUser3DLUT()
        del three_d_lut_display
        del display
    yield
    for display in display_list:
        three_d_lut_display: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        three_d_lut_display.ClearUser3DLUT()
        del three_d_lut_display
        del display
    del display_list
    del display_service
    del system


def test_clear_user_3d_lut(adlx):
    """Call ClearUser3DLUT on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        ret: ADLX.ADLX_RESULT = three_d_lut.ClearUser3DLUT()
        assert isinstance(ret, ADLX.ADLX_RESULT)
        del three_d_lut
    del display_list, display_service, system


def test_is_supported_sce_3d_lut(adlx):
    """Call IsSupportedSCE on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        supported: bool = three_d_lut.IsSupportedSCE()
        assert isinstance(supported, bool)
        del three_d_lut
    del display_list, display_service, system


@pytest.mark.parametrize(
    "api_name",
    [
        "IsCurrentSCEDisabled",
        "IsCurrentSCEDynamicContrast",
        "IsCurrentSCEVividGaming",
        "IsSupportedSCEDynamicContrast",
        "IsSupportedSCEVividGaming",
        "IsSupportedUser3DLUT",
    ],
)
def test_is_api_lut(adlx, api_name):
    """Call <api_name> on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        if not three_d_lut.IsSupportedSCE():
            del three_d_lut
            continue
        is_api_res: bool = getattr(three_d_lut, api_name)()
        assert isinstance(is_api_res, bool)
        del three_d_lut
    del display_list, display_service, system


@pytest.mark.parametrize(
    "api_name",
    [
        "SetSCEDisabled",
        "SetSCEVividGaming",
    ],
)
def test_set_api_lut(adlx, api_name):
    """Call <api_name> on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        set_api_res: ADLX.ADLX_RESULT = getattr(three_d_lut, api_name)()
        assert isinstance(set_api_res, ADLX.ADLX_RESULT)
        del three_d_lut
    del display_list, display_service, system


@pytest.mark.parametrize("api_name", ["GetAllUser3DLUT", "GetHDRUser3DLUT", "GetSDRUser3DLUT"])
def test_get_api_user_3d_lut(adlx, api_name):
    """Call <api_name> on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        all_user_3dlut: Dict[int, int, int] = getattr(three_d_lut, api_name)()
        assert len(all_user_3dlut) == 4
        assert "transferFunction" in all_user_3dlut.keys()
        assert "colorSpace" in all_user_3dlut.keys()
        assert "pointsNumber" in all_user_3dlut.keys()
        assert "data" in all_user_3dlut.keys()
        assert "red" in all_user_3dlut["data"]
        assert isinstance(all_user_3dlut["data"]["red"], int)
        assert "green" in all_user_3dlut["data"]
        assert isinstance(all_user_3dlut["data"]["green"], int)
        assert "blue" in all_user_3dlut["data"]
        assert isinstance(all_user_3dlut["data"]["blue"], int)
        del three_d_lut
    del display_list, display_service, system


def test_set_all_user_3d_lut(adlx):
    """Call SetAllUser3DLUT on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        all_user_3dlut: Dict[int, int, int] = three_d_lut.GetAllUser3DLUT()
        transfer_function = all_user_3dlut["transferFunction"]
        color_space = all_user_3dlut["colorSpace"]
        points_number = all_user_3dlut["pointsNumber"]
        data = all_user_3dlut["data"]
        ret_set_all_user_3dlut: ADLX.ADLX_RESULT = three_d_lut.SetAllUser3DLUT(
            transfer_function, color_space, points_number, data
        )
        assert isinstance(ret_set_all_user_3dlut, ADLX.ADLX_RESULT)
        del three_d_lut
    del display_list, display_service, system


def test_set_hdr_user_3d_lut(adlx):
    """Call SetHDRUser3DLUT on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        all_user_3dlut: Dict[int, int, int] = three_d_lut.GetHDRUser3DLUT()
        transfer_function = all_user_3dlut["transferFunction"]
        color_space = all_user_3dlut["colorSpace"]
        points_number = all_user_3dlut["pointsNumber"]
        data = all_user_3dlut["data"]
        ret_set_all_user_3dlut: ADLX.ADLX_RESULT = three_d_lut.SetHDRUser3DLUT(
            transfer_function, color_space, points_number, data
        )
        assert isinstance(ret_set_all_user_3dlut, ADLX.ADLX_RESULT)
        del three_d_lut
    del display_list, display_service, system


def test_set_sdr_user_3d_lut(adlx):
    """Call SetSDRUser3DLUT on 3DLUT interface. Expect at least one display connected."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        three_d_lut: ADLX.IADLXDisplay3DLUT = display_service.Get3DLUT(display)
        all_user_3dlut: Dict[int, int, int] = three_d_lut.GetSDRUser3DLUT()
        transfer_function = all_user_3dlut["transferFunction"]
        color_space = all_user_3dlut["colorSpace"]
        points_number = all_user_3dlut["pointsNumber"]
        data = all_user_3dlut["data"]
        ret_set_all_user_3dlut: ADLX.ADLX_RESULT = three_d_lut.SetSDRUser3DLUT(
            transfer_function, color_space, points_number, data
        )
        assert isinstance(ret_set_all_user_3dlut, ADLX.ADLX_RESULT)
        del three_d_lut
    del display_list, display_service, system
