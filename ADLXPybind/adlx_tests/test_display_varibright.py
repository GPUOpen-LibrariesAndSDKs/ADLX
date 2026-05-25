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


def test_iscurrent_balanced_vb(adlx):
    """call IsCurrentBalanced() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        balanced: bool = diplay_varibright.IsCurrentBalanced()
        if balanced is not None:
            assert isinstance(balanced, bool)


def test_is_current_maximize_battery_vb(adlx):
    """call IsCurrentMaximizeBattery() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        maximize_battery: bool = diplay_varibright.IsCurrentMaximizeBattery()
        if maximize_battery is not None:
            assert isinstance(maximize_battery, bool)


def test_is_current_maximize_brightness_vb(adlx):
    """call IsCurrentMaximizeBrightness() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        maximize_brightness: bool = diplay_varibright.IsCurrentMaximizeBrightness()
        if maximize_brightness is not None:
            assert isinstance(maximize_brightness, bool)


def test_is_current_optimize_battery_vb(adlx):
    """call IsCurrentOptimizeBattery() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        optimize_battery: bool = diplay_varibright.IsCurrentOptimizeBattery()
        if optimize_battery is not None:
            assert isinstance(optimize_battery, bool)


def test_is_current_optimize_brightness_vb(adlx):
    """call IsCurrentOptimizeBrightness() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        optimize_brightness: bool = diplay_varibright.IsCurrentOptimizeBrightness()
        if optimize_brightness is not None:
            assert isinstance(optimize_brightness, bool)


def test_is_enabled_vb(adlx):
    """call IsEnabled() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        is_enalbed: bool = diplay_varibright.IsEnabled()
        if is_enalbed is not None:
            assert isinstance(is_enalbed, bool)


def test_is_supported_vb(adlx):
    """call IsSupported() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        is_supported: bool = diplay_varibright.IsSupported()
        assert isinstance(is_supported, bool)


def test_set_balanced_vb(adlx):
    """call SetBalanced() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        set_balanced: ADLX.ADLX_RESULT = diplay_varibright.SetBalanced()
        assert isinstance(set_balanced, ADLX.ADLX_RESULT)


def test_set_enabled_vb(adlx):
    """call SetEnabled() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        is_enalbed: bool = diplay_varibright.IsEnabled()
        set_enabled: ADLX.ADLX_RESULT = diplay_varibright.SetEnabled(is_enalbed)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)


def test_set_maximize_battery_vb(adlx):
    """call SetMaximizeBattery() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        set_max_battery: ADLX.ADLX_RESULT = diplay_varibright.SetMaximizeBattery()
        assert isinstance(set_max_battery, ADLX.ADLX_RESULT)


def test_set_maximize_brigtness_vb(adlx):
    """call SetMaximizeBrightness() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        set_max_brightness: ADLX.ADLX_RESULT = diplay_varibright.SetMaximizeBrightness()
        assert isinstance(set_max_brightness, ADLX.ADLX_RESULT)


def test_set_optimize_battery_vb(adlx):
    """call SetOptimizeBattery() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        set_optimize_battery: ADLX.ADLX_RESULT = diplay_varibright.SetOptimizeBattery()
        assert isinstance(set_optimize_battery, ADLX.ADLX_RESULT)


def test_set_optimize_brightness_vb(adlx):
    """call SetOptimizeBrightness() on IADLXDisplayVariBright interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        set_optimize_brightness: ADLX.ADLX_RESULT = diplay_varibright.SetOptimizeBrightness()
        assert isinstance(set_optimize_brightness, ADLX.ADLX_RESULT)


# IADLXDisplayVariBright1 tests

def test_is_backlight_adaptive_supported_vb(adlx):
    """call IsBacklightAdaptiveSupported() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        supported: bool = diplay_varibright.IsBacklightAdaptiveSupported()
        assert isinstance(supported, bool)


def test_is_backlight_adaptive_enabled_vb(adlx):
    """call IsBacklightAdaptiveEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsBacklightAdaptiveEnabled()
        assert isinstance(enabled, bool)


def test_set_backlight_adaptive_enabled_vb(adlx):
    """call SetBacklightAdaptiveEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsBacklightAdaptiveEnabled()
        result: ADLX.ADLX_RESULT = diplay_varibright.SetBacklightAdaptiveEnabled(enabled)
        assert isinstance(result, ADLX.ADLX_RESULT)


def test_is_battery_life_supported_vb(adlx):
    """call IsBatteryLifeSupported() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        supported: bool = diplay_varibright.IsBatteryLifeSupported()
        assert isinstance(supported, bool)


def test_is_battery_life_enabled_vb(adlx):
    """call IsBatteryLifeEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsBatteryLifeEnabled()
        assert isinstance(enabled, bool)


def test_set_battery_life_enabled_vb(adlx):
    """call SetBatteryLifeEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsBatteryLifeEnabled()
        result: ADLX.ADLX_RESULT = diplay_varibright.SetBatteryLifeEnabled(enabled)
        assert isinstance(result, ADLX.ADLX_RESULT)


def test_is_windows_power_mode_supported_vb(adlx):
    """call IsWindowsPowerModeSupported() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        supported: bool = diplay_varibright.IsWindowsPowerModeSupported()
        assert isinstance(supported, bool)


def test_is_windows_power_mode_enabled_vb(adlx):
    """call IsWindowsPowerModeEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsWindowsPowerModeEnabled()
        assert isinstance(enabled, bool)


def test_set_windows_power_mode_enabled_vb(adlx):
    """call SetWindowsPowerModeEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsWindowsPowerModeEnabled()
        result: ADLX.ADLX_RESULT = diplay_varibright.SetWindowsPowerModeEnabled(enabled)
        assert isinstance(result, ADLX.ADLX_RESULT)


def test_is_full_screen_video_supported_vb(adlx):
    """call IsFullScreenVideoSupported() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        supported: bool = diplay_varibright.IsFullScreenVideoSupported()
        assert isinstance(supported, bool)


def test_is_full_screen_video_enabled_vb(adlx):
    """call IsFullScreenVideoEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsFullScreenVideoEnabled()
        assert isinstance(enabled, bool)


def test_set_full_screen_video_enabled_vb(adlx):
    """call SetFullScreenVideoEnabled() on IADLXDisplayVariBright1 interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_varibright: ADLX.IADLXDisplayVariBright = display_service.GetVariBright(display)
        enabled: bool = diplay_varibright.IsFullScreenVideoEnabled()
        result: ADLX.ADLX_RESULT = diplay_varibright.SetFullScreenVideoEnabled(enabled)
        assert isinstance(result, ADLX.ADLX_RESULT)
