#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for 3D Eyefinity tests """
import pytest

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_create_destroy_simple_eyefinity(adlx):
    """call Create() on IADLXSimpleEyefinity interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    simple_eyefinity: ADLX.IADLXSimpleEyefinity = desktop_services.GetSimpleEyefinity()
    eyefinity_desktop = simple_eyefinity.Create()

    '''sleep 5 seconds to wait for eyefinity desktop creation'''
    import time
    time.sleep(5)
    simple_eyefinity.Destroy(eyefinity_desktop)
    time.sleep(5)


def test_destroy_all_simple_eyefinity(adlx):
    """call DestroyAll() on IADLXSimpleEyefinity interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    simple_eyefinity: ADLX.IADLXSimpleEyefinity = desktop_services.GetSimpleEyefinity()
    ret_destroy_all: ADLX.ADLX_RESULT = simple_eyefinity.DestroyAll()
    assert ret_destroy_all == ADLX.ADLX_RESULT.ADLX_OK


def test_is_supported_simple_eyefinity(adlx):
    """call IsSupported() on IADLXSimpleEyefinity interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    simple_eyefinity: ADLX.IADLXSimpleEyefinity = desktop_services.GetSimpleEyefinity()
    supported: bool = simple_eyefinity.IsSupported()
    assert isinstance(supported, bool)


def test_get_displays_desktop(adlx):
    """call GetDisplays() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        displays = desktop.GetDisplays()
        assert isinstance(displays, list)


def test_get_number_of_displays_desktop(adlx):
    """call GetNumberOfDisplays() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        displays_num = desktop.GetNumberOfDisplays()
        assert isinstance(displays_num, int)


def test_orientation_desktop(adlx):
    """call Orientation() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        orientation = desktop.Orientation()
        assert isinstance(orientation, ADLX.ADLX_ORIENTATION)


def test_size_desktop(adlx):
    """call Size() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        size: Dict[str, int] = desktop.Size()
        assert size
        assert isinstance(size, dict)
        assert isinstance(size["width"], int)
        assert isinstance(size["height"], int)


def test_top_left_desktop(adlx):
    """call TopLeft() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        topleft: Dict[str, int] = desktop.TopLeft()
        assert topleft
        assert isinstance(topleft, dict)
        assert isinstance(topleft["x"], int)
        assert isinstance(topleft["y"], int)


def test_type_desktop(adlx):
    """call Type() on IADLXDesktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        assert isinstance(desktop_type, ADLX.ADLX_DESKTOP_TYPE)


def test_display_orientation_eyefinity_desktop(adlx):
    """call DisplayOrientation() on IADLXEyefinityDesktop desktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        if desktop_type == ADLX.ADLX_DESKTOP_TYPE.DESKTOP_EYEFINITY:
            ret_orientation = desktop.DisplayOrientation(1, 1)
            assert isinstance(ret_orientation, ADLX.ADLX_ORIENTATION)


def test_display_size_eyefinity_desktop(adlx):
    """call DisplaySize() on IADLXEyefinityDesktop desktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        if desktop_type == ADLX.ADLX_DESKTOP_TYPE.DESKTOP_EYEFINITY:
            display_size = desktop.DisplaySize(1, 1)
            assert isinstance(display_size, tuple)
            assert len(display_size) == 2


def test_display_top_left_eyefinity_desktop(adlx):
    """call DisplayTopLeft() on IADLXEyefinityDesktop desktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        if desktop_type == ADLX.ADLX_DESKTOP_TYPE.DESKTOP_EYEFINITY:
            display_top_left: Dict[str, int] = desktop.DisplayTopLeft(1, 1)
            assert isinstance(display_top_left, dict)
            assert isinstance(display_top_left["x"], int)
            assert isinstance(display_top_left["y"], int)


def test_get_display_eyefinity_desktop(adlx):
    """call GetDisplay() on IADLXEyefinityDesktop desktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        if desktop_type == ADLX.ADLX_DESKTOP_TYPE.DESKTOP_EYEFINITY:
            display = desktop.GetDisplay(1, 1)
            assert isinstance(display, ADLX.IADLXDisplay)


def test_grid_size_eyefinity_desktop(adlx):
    """call GridSize() on IADLXEyefinityDesktop desktop interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops = desktop_services.GetDesktops()
    for desktop in desktops:
        desktop_type = desktop.Type()
        if desktop_type == ADLX.ADLX_DESKTOP_TYPE.DESKTOP_EYEFINITY:
            grid_size: Dict[str, int] = desktop.GridSize()
            assert isinstance(grid_size, dict)
            assert isinstance(grid_size["rows"], int)
            assert isinstance(grid_size["col"], int)


def test_add_desktop_list_event_listener_eyefinity(adlx):
    """call AddDesktopListEventListener() on DesktopChangedHandling interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktop_change_handler: ADLX.IADLXDesktopChangedHandling = desktop_services.GetDesktopChangedHandling()

    desktop_cb: ADLX.PyDesktopListChangedListenerCallback = ADLX.PyDesktopListChangedListenerCallback()
    ret_add_desktop_listener: ADLX.ADLX_RESULT = desktop_change_handler.AddDesktopListEventListener(desktop_cb)
    assert ret_add_desktop_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_remove_desktop_list_event_listener_eyefinity(adlx):
    """call RemoveDesktopListEventListener() on DesktopChangedHandling interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktop_change_handler: ADLX.IADLXDesktopChangedHandling = desktop_services.GetDesktopChangedHandling()

    desktop_cb: ADLX.PyDesktopListChangedListenerCallback = ADLX.PyDesktopListChangedListenerCallback()
    ret_add_desktop_listener: ADLX.ADLX_RESULT = desktop_change_handler.AddDesktopListEventListener(desktop_cb)
    assert ret_add_desktop_listener == ADLX.ADLX_RESULT.ADLX_OK

    ret_remove_desktop_listener: ADLX.ADLX_RESULT = desktop_change_handler.RemoveDesktopListEventListener(desktop_cb)
    assert ret_remove_desktop_listener == ADLX.ADLX_RESULT.ADLX_OK
