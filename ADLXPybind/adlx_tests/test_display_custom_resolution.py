#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind API tests IADLXDisplayCustomResolution.
Purpose of this file is to check if calling ADLX API does not report unexpected errors.
"""
# pylint: disable=I1101
import pytest
from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_custom_resolution(adlx):
    """call GetCustomResolution() on GetDisplaysServices interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        assert custom_res
        assert isinstance(custom_res, ADLX.IADLXDisplayCustomResolution)
        del custom_res
    del display_list, display_service, system


def test_is_supported_custom_resolution(adlx):
    """call IsSupported() on IADLXDisplayCustomResolution interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        ret: bool = custom_res.IsSupported()
        assert isinstance(ret, bool)
        del custom_res
    del display_list, display_service, system


def test_create_new_custom_resolution(adlx: ADLX.ADLXHelper):
    """Call CreateNewResolution() on IADLXDisplayCustomResolution . We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        ret: ADLX.ADLX_RESULT = custom_res.CreateNewResolution(current_display_res)
        assert isinstance(ret, ADLX.ADLX_RESULT)
        del current_display_res, custom_res
    del display_list, display_service, system


def test_get_current_applied_resolution(adlx):
    """call GetCurrentAppliedResolution() on IADLXDisplayCustomResolution . We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        assert isinstance(current_display_res, ADLX.IADLXDisplayResolution)
        del current_display_res, custom_res
    del display_list, display_service, system


def test_get_resolution_list_resolution(adlx):
    """call GetResolutionList() on IADLXDisplayCustomResolution . We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        ret: ADLX.ADLX_RESULT = custom_res.CreateNewResolution(current_display_res)
        assert isinstance(ret, ADLX.ADLX_RESULT)
        resolutions: List[ADLX.IADLXDisplayResolution] = custom_res.GetResolutionList()
        assert isinstance(resolutions, list)
        del resolutions, current_display_res, custom_res
    del display_list, display_service, system


def test_delete_resolution(adlx: ADLX.ADLXHelper):
    """Call DeleteResolution() on IADLXDisplayCustomResolution . We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        ret: ADLX.ADLX_RESULT = custom_res.CreateNewResolution(current_display_res)
        assert isinstance(ret, ADLX.ADLX_RESULT)

        ret_del: ADLX.ADLX_RESULT = custom_res.DeleteResolution(current_display_res)
        assert isinstance(ret_del, ADLX.ADLX_RESULT)
        del current_display_res, custom_res
    del display_list, display_service, system


def test_get_value_custom_resolution(adlx: ADLX.ADLXHelper):
    """call GetValue() on IADLXDisplayResolution interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        resolution_value: ADLX.ADLX_CustomResolution = current_display_res.GetValue()
        assert isinstance(resolution_value, ADLX.ADLX_CustomResolution)
        assert isinstance(resolution_value.resHeight, int)
        assert isinstance(resolution_value.refreshRate, int)
        assert isinstance(resolution_value.presentation, ADLX.ADLX_DISPLAY_SCAN_TYPE)
        assert isinstance(resolution_value.timingStandard, ADLX.ADLX_TIMING_STANDARD)
        assert isinstance(resolution_value.GPixelClock, int)
        assert isinstance(resolution_value.detailedTiming, ADLX.ADLX_TimingInfo)
        assert isinstance(resolution_value.detailedTiming.timingFlags, int)
        assert isinstance(resolution_value.detailedTiming.hTotal, int)
        assert isinstance(resolution_value.detailedTiming.vTotal, int)
        assert isinstance(resolution_value.detailedTiming.hDisplay, int)
        assert isinstance(resolution_value.detailedTiming.vDisplay, int)
        assert isinstance(resolution_value.detailedTiming.hFrontPorch, int)
        assert isinstance(resolution_value.detailedTiming.vFrontPorch, int)
        assert isinstance(resolution_value.detailedTiming.hSyncWidth, int)
        assert isinstance(resolution_value.detailedTiming.vSyncWidth, int)
        assert isinstance(resolution_value.detailedTiming.hPolarity, int)
        assert isinstance(resolution_value.detailedTiming.vPolarity, int)
        del resolution_value, current_display_res, custom_res
    del display_list, display_service, system


def test_set_value_custom_resolution(adlx: ADLX.ADLXHelper):
    """call SetValue() on IADLXDisplayResolution interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        custom_res: ADLX.IADLXDisplayCustomResolution = display_service.GetCustomResolution(display)
        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        if current_display_res is None:
            del custom_res
            continue
        resolution_value: ADLX.ADLX_CustomResolution = current_display_res.GetValue()
        ret: ADLX.ADLX_RESULT = current_display_res.SetValue(resolution_value)
        assert isinstance(ret, ADLX.ADLX_RESULT)
        del resolution_value, current_display_res, custom_res
    del display_list, display_service, system
