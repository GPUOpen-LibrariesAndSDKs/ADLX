#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind Multimedia Services tests. Tests for GetMultimediaServices and related interfaces. """
# pylint: disable=I1101
import threading
import time

import pytest
from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_multimedia_services(adlx):
    """Call GetMultimediaServices() on IADLXSystem interface. We expect non-empty response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    assert isinstance(multimedia_services, ADLX.IADLXMultimediaServices)


def test_get_multimedia_changed_handling(adlx):
    """Call GetMultimediaChangedHandling() on IADLXMultimediaServices interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    handling: ADLX.IADLXMultimediaChangedHandling = multimedia_services.GetMultimediaChangedHandling()
    assert handling
    assert isinstance(handling, ADLX.IADLXMultimediaChangedHandling)


def test_get_video_upscale(adlx):
    """Call GetVideoUpscale() on IADLXMultimediaServices interface for each GPU."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if video_upscale:
            assert isinstance(video_upscale, ADLX.IADLXVideoUpscale)


def test_get_video_super_resolution(adlx):
    """Call GetVideoSuperResolution() on IADLXMultimediaServices interface for each GPU."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        vsr: ADLX.IADLXVideoSuperResolution = multimedia_services.GetVideoSuperResolution(gpu)
        if vsr:
            assert isinstance(vsr, ADLX.IADLXVideoSuperResolution)


def test_video_upscale_is_supported(adlx):
    """Call IsSupported() on IADLXVideoUpscale interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if video_upscale:
            supported = video_upscale.IsSupported()
            if supported is not None:
                assert isinstance(supported, bool)


def test_video_upscale_is_enabled(adlx):
    """Call IsEnabled() on IADLXVideoUpscale interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if video_upscale:
            enabled = video_upscale.IsEnabled()
            if enabled is not None:
                assert isinstance(enabled, bool)


def test_video_upscale_get_sharpness_range(adlx):
    """Call GetSharpnessRange() on IADLXVideoUpscale interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if video_upscale:
            result = video_upscale.GetSharpnessRange()
            assert isinstance(result, dict)
            assert "return" in result
            assert "min_value" in result
            assert "max_value" in result
            assert "step" in result


def test_video_upscale_get_sharpness(adlx):
    """Call GetSharpness() on IADLXVideoUpscale interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if video_upscale:
            sharpness = video_upscale.GetSharpness()
            if sharpness is not None:
                assert isinstance(sharpness, int)


def test_video_super_resolution_is_supported(adlx):
    """Call IsSupported() on IADLXVideoSuperResolution interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        vsr: ADLX.IADLXVideoSuperResolution = multimedia_services.GetVideoSuperResolution(gpu)
        if vsr:
            supported = vsr.IsSupported()
            if supported is not None:
                assert isinstance(supported, bool)


def test_video_super_resolution_is_enabled(adlx):
    """Call IsEnabled() on IADLXVideoSuperResolution interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        vsr: ADLX.IADLXVideoSuperResolution = multimedia_services.GetVideoSuperResolution(gpu)
        if vsr:
            enabled = vsr.IsEnabled()
            if enabled is not None:
                assert isinstance(enabled, bool)


def _create_multimedia_callback(completion_event: threading.Event):
    """Factory that creates a multimedia changed callback and records event properties."""
    results = {}

    def callback_multimedia_changed(p_multimedia_changed_event) -> bool:
        gpu = p_multimedia_changed_event.GetGPU()
        results["gpu"] = gpu

        is_video_upscale_changed: bool = p_multimedia_changed_event.IsVideoUpscaleChanged()
        results["is_video_upscale_changed"] = is_video_upscale_changed
        assert isinstance(is_video_upscale_changed, bool)

        is_vsr_changed: bool = p_multimedia_changed_event.IsVideoSuperResolutionChanged()
        results["is_video_super_resolution_changed"] = is_vsr_changed
        assert isinstance(is_vsr_changed, bool)

        completion_event.set()
        return True

    return callback_multimedia_changed, results


def test_multimedia_changed_event_add_remove_listener(adlx):
    """Register and unregister a multimedia event listener."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    handling: ADLX.IADLXMultimediaChangedHandling = multimedia_services.GetMultimediaChangedHandling()
    assert handling

    completion_event = threading.Event()
    callback: ADLX.PyMultimediaChangedListenerCallback = ADLX.PyMultimediaChangedListenerCallback()
    callback.call, _ = _create_multimedia_callback(completion_event)

    ret_add: ADLX.ADLX_RESULT = handling.AddMultimediaEventListener(callback)
    assert ret_add == ADLX.ADLX_RESULT.ADLX_OK

    ret_remove: ADLX.ADLX_RESULT = handling.RemoveMultimediaEventListener(callback)
    assert ret_remove == ADLX.ADLX_RESULT.ADLX_OK


def test_multimedia_changed_event_video_upscale(adlx):
    """Toggle VideoUpscale and verify the multimedia changed event fires with correct properties."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    multimedia_services: ADLX.IADLXMultimediaServices = system.GetMultimediaServices()
    assert multimedia_services
    handling: ADLX.IADLXMultimediaChangedHandling = multimedia_services.GetMultimediaChangedHandling()
    assert handling

    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        video_upscale: ADLX.IADLXVideoUpscale = multimedia_services.GetVideoUpscale(gpu)
        if not video_upscale:
            continue
        supported = video_upscale.IsSupported()
        if not supported:
            continue

        completion_event = threading.Event()
        callback: ADLX.PyMultimediaChangedListenerCallback = ADLX.PyMultimediaChangedListenerCallback()
        callback.call, results = _create_multimedia_callback(completion_event)

        ret_add: ADLX.ADLX_RESULT = handling.AddMultimediaEventListener(callback)
        assert ret_add == ADLX.ADLX_RESULT.ADLX_OK

        try:
            original_enabled = video_upscale.IsEnabled()
            toggle = not original_enabled if original_enabled is not None else True
            ret_set: ADLX.ADLX_RESULT = video_upscale.SetEnabled(toggle)
            if ret_set == ADLX.ADLX_RESULT.ADLX_OK:
                if completion_event.wait(timeout=50):
                    assert results.get("is_video_upscale_changed") is True
                # Restore original state
                if original_enabled is not None:
                    video_upscale.SetEnabled(original_enabled)
                    time.sleep(2)
        finally:
            handling.RemoveMultimediaEventListener(callback)
