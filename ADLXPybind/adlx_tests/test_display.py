#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display service interfaces methods  """
# pylint: disable=I1101
import threading
import time

import pytest

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback factory that captures the event for synchronization
def create_display_settings_callback(completion_event: threading.Event):
    """Factory function to create a callback that signals the completion event"""
    def callback_display_settings_changed_listener(p_display_setting_changed_event) -> bool:
        display: ADLX.IADLXDisplay = p_display_setting_changed_event.GetDisplay()
        assert isinstance(display, ADLX.IADLXDisplay)

        is_color_depth_changed: bool = p_display_setting_changed_event.IsColorDepthChanged()
        assert isinstance(is_color_depth_changed, bool)
        is_custom_color_brightness_changed: bool = p_display_setting_changed_event.IsCustomColorBrightnessChanged()
        assert isinstance(is_custom_color_brightness_changed, bool)
        is_custom_color_contrast_changed: bool = p_display_setting_changed_event.IsCustomColorContrastChanged()
        assert isinstance(is_custom_color_contrast_changed, bool)
        is_custom_color_hue_changed: bool = p_display_setting_changed_event.IsCustomColorHueChanged()
        assert isinstance(is_custom_color_hue_changed, bool)
        is_custom_color_saturation_changed: bool = p_display_setting_changed_event.IsCustomColorSaturationChanged()
        assert isinstance(is_custom_color_saturation_changed, bool)
        is_custom_color_temperature_changed: bool = p_display_setting_changed_event.IsCustomColorTemperatureChanged()
        assert isinstance(is_custom_color_temperature_changed, bool)
        is_custom_resolution_changed: bool = p_display_setting_changed_event.IsCustomResolutionChanged()
        assert isinstance(is_custom_resolution_changed, bool)
        is_free_sync_changed: bool = p_display_setting_changed_event.IsFreeSyncChanged()
        assert isinstance(is_free_sync_changed, bool)
        is_gpu_scaling_changed: bool = p_display_setting_changed_event.IsGPUScalingChanged()
        assert isinstance(is_gpu_scaling_changed, bool)
        is_hdcp_changed: bool = p_display_setting_changed_event.IsHDCPChanged()
        assert isinstance(is_hdcp_changed, bool)
        is_integer_scaling_changed: bool = p_display_setting_changed_event.IsIntegerScalingChanged()
        assert isinstance(is_integer_scaling_changed, bool)
        is_pixel_format_changed: bool = p_display_setting_changed_event.IsPixelFormatChanged()
        assert isinstance(is_pixel_format_changed, bool)
        is_scaling_mode_changed: bool = p_display_setting_changed_event.IsScalingModeChanged()
        assert isinstance(is_scaling_mode_changed, bool)
        is_vsr_changed: bool = p_display_setting_changed_event.IsVSRChanged()
        assert isinstance(is_vsr_changed, bool)
        is_vari_bright_changed: bool = p_display_setting_changed_event.IsVariBrightChanged()
        assert isinstance(is_vari_bright_changed, bool)
        is_display_blanking_changed: bool = p_display_setting_changed_event.IsDisplayBlankingChanged()
        assert isinstance(is_display_blanking_changed, bool)
        is_display_connectivity_experience_changed: bool = p_display_setting_changed_event.IsDisplayConnectivityExperienceChanged()
        assert isinstance(is_display_connectivity_experience_changed, bool)
        is_display_dynamic_refresh_rate_control_changed: bool = p_display_setting_changed_event.IsDisplayDynamicRefreshRateControlChanged()
        assert isinstance(is_display_dynamic_refresh_rate_control_changed, bool)
        is_freesync_color_accuracy_changed: bool = p_display_setting_changed_event.IsFreeSyncColorAccuracyChanged()
        assert isinstance(is_freesync_color_accuracy_changed, bool)

        completion_event.set()

        return True

    return callback_display_settings_changed_listener


def callback_display_list_changed_listener(p_display_list) -> bool:
    """Callback when the Disaplay List Changes"""
    for display in p_display_list:
        assert isinstance(display, ADLX.IADLXDisplay)

    return True


def test_is_enabled_integer_scaling(adlx):
    """call IsEnabled() on IADLXDisplayIntegerScaling interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intscale: ADLX.IADLXDisplayIntegerScaling = display_service.GetIntegerScaling(display)
        is_enabled: bool = intscale.IsEnabled()
        if is_enabled is not None:
            assert isinstance(is_enabled, bool)


def test_is_supported_integer_scaling(adlx):
    """Call IsSupported on IADLXDisplayIntegerScaling interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intscale: ADLX.IADLXDisplayIntegerScaling = display_service.GetIntegerScaling(display)
        is_Supported: bool = intscale.IsSupported()
        assert isinstance(is_Supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_integer_scaling(adlx, adlx_bool):
    """Call SetEnabled on IADLXDisplayIntegerScaling interface.We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intscale: ADLX.IADLXDisplayIntegerScaling = display_service.GetIntegerScaling(display)
        is_Supported: ADLX.ADLX_RESULT = intscale.SetEnabled(adlx_bool)
        assert isinstance(is_Supported, ADLX.ADLX_RESULT)


def test_is_enabled_Freesync(adlx):
    """call IsEnabled() on IADLXDisplayFreeSync interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intfreesync: ADLX.IADLXDisplayFreeSync = display_service.GetFreeSync(display)
        is_enabled: bool = intfreesync.IsEnabled()
        if is_enabled is not None:
            assert isinstance(is_enabled, bool)


def test_is_supported_Freesync(adlx):
    """Call IsSupported on IADLXDisplayFreeSync interface.Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intfreesync: ADLX.IADLXDisplayFreeSync = display_service.GetFreeSync(display)
        is_Supported: bool = intfreesync.IsSupported()
        assert isinstance(is_Supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_Freesync(adlx, adlx_bool):
    """Call SetEnabled on IADLXDisplayFreeSync interface.We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        intfreesync: ADLX.IADLXDisplayFreeSync = display_service.GetFreeSync(display)
        is_Supported: ADLX.ADLX_RESULT = intfreesync.SetEnabled(adlx_bool)
        assert isinstance(is_Supported, ADLX.ADLX_RESULT)


def test_add_display_settings_event_listener(adlx):
    """Test Display Settings events AddDisplaySettingsEventListener() and RemoveDisplaySettingsEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()

    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()

    completion_event = threading.Event()

    callback: ADLX.PyDisplaySettingsChangedListenerCallback = ADLX.PyDisplaySettingsChangedListenerCallback()
    callback.call = create_display_settings_callback(completion_event)

    res_add_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplaySettingsEventListener(callback)
    assert res_add_listener == ADLX.ADLX_RESULT.ADLX_OK

    for display in display_list:
        custom_color: ADLX.IADLXDisplayCustomColor = display_service.GetCustomColor(display)
        current_saturation: int = custom_color.GetSaturation()
        new_saturation = 50 if current_saturation != 50 else 100

        set_result: ADLX.ADLX_RESULT = custom_color.SetSaturation(new_saturation)
        if set_result == ADLX.ADLX_RESULT.ADLX_OK:
            if completion_event.wait(timeout=50):
                print(f"Display settings changed callback received")
                time.sleep(5)
            else:
                print(f"Display settings change timed out after 50 seconds")

    res_remove_listener: ADLX.ADLX_RESULT = display_change_handler.RemoveDisplaySettingsEventListener(callback)
    assert res_remove_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_add_display_list_event_listener(adlx):
    """Test Display List events AddDisplayListEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayListChangedListenerCallback = ADLX.PyDisplayListChangedListenerCallback()
    callback.call = callback_display_list_changed_listener

    res_add_display_list_event_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayListEventListener(callback)
    assert res_add_display_list_event_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_remove_display_list_event_listener(adlx):
    """Test isplay List events RemoveDisplayListEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayListChangedListenerCallback = ADLX.PyDisplayListChangedListenerCallback()
    callback.call = callback_display_list_changed_listener

    res_add_display_list_event_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayListEventListener(callback)
    assert res_add_display_list_event_listener == ADLX.ADLX_RESULT.ADLX_OK

    res_remove_display_list_event_listener: ADLX.ADLX_RESULT = display_change_handler.RemoveDisplayListEventListener(
        callback
    )
    assert res_remove_display_list_event_listener == ADLX.ADLX_RESULT.ADLX_OK
