#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADLX GPU AutoTuning tests  """
import pytest
import time
import threading

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback factory that captures the event for synchronization
def create_auto_tuning_callback(completion_event: threading.Event):
    """Factory function to create a callback that signals the completion event"""
    def callback_auto_tuning_complete_listener(p_gpu_auto_tuning_complete_event) -> bool:
        is_overclock_gpu_completed: bool = p_gpu_auto_tuning_complete_event.IsOverclockGPUCompleted()
        assert isinstance(is_overclock_gpu_completed, bool)
        is_overclock_vram_completed: bool = p_gpu_auto_tuning_complete_event.IsOverclockVRAMCompleted()
        assert isinstance(is_overclock_vram_completed, bool)
        is_undervolt_gpu_completed: bool = p_gpu_auto_tuning_complete_event.IsUndervoltGPUCompleted()
        assert isinstance(is_undervolt_gpu_completed, bool)
        
        # Signal the test function that callback has completed
        completion_event.set()
        
        return True
    
    return callback_auto_tuning_complete_listener


def test_get_auto_tuning(adlx):
    """call GetAutoTuning() on IADLXGPUTuningServices"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        auto_tuning_service: ADLX.IADLXGPUAutoTuning = tuning_services.GetAutoTuning(gpu)
        assert auto_tuning_service
        assert isinstance(auto_tuning_service, ADLX.IADLXGPUAutoTuning)


@pytest.mark.parametrize(
    "api_name",
    [
        "IsCurrentOverclockGPU",
        "IsCurrentOverclockVRAM",
        "IsCurrentUndervoltGPU",
        "IsSupportedOverclockGPU",
        "IsSupportedOverclockVRAM",
        "IsSupportedUndervoltGPU",
    ],
)
def test_is_supported_undervolt_gpu(adlx, api_name):
    """call <api_name> AutoTuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        auto_tuning_service: ADLX.IADLXGPUAutoTuning = tuning_services.GetAutoTuning(gpu)
        api_name_res: bool = getattr(auto_tuning_service, api_name)()
        if api_name_res:
            assert isinstance(api_name_res, bool)


@pytest.mark.parametrize(
    "api_name",
    # fmt: off
                        [
                             "StartOverclockGPU", # this API is dangerous, disabling it for normal ut run, use it carefully
                             #"StartOverclockVRAM", # this API is dangerous, disabling it for normal ut run, use it carefully
                             #"StartUndervoltGPU"  # this API is dangerous, disabling it for normal ut run, use it carefully
                        ],
    # fmt: on
)
def test_overclocks_api_name_gpu_auto_tuning(adlx, api_name):
    """call StartOverclockGPU() on AutoTuning interface"""

    def _reset_tuning(tuning_services, gpu):
        ret_reset: ADLX.ADLX_RESULT = tuning_services.ResetToFactory(gpu)
        assert ret_reset == ADLX.ADLX_RESULT.ADLX_OK

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()

    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        try:
            auto_tuning_service: ADLX.IADLXGPUAutoTuning = tuning_services.GetAutoTuning(gpu)

            # Create a threading event for synchronization with callback
            completion_event = threading.Event()
            
            callback: ADLX.PyGPUAutoTuningCompleteListenerCallback = ADLX.PyGPUAutoTuningCompleteListenerCallback()
            callback.call = create_auto_tuning_callback(completion_event)

            ret_start: ADLX.ADLX_RESULT = getattr(auto_tuning_service, api_name)(callback)

            # Wait for auto-tuning completion if succeeded
            if ret_start == ADLX.ADLX_RESULT.ADLX_OK:
                # Wait for callback to signal completion (max 50 seconds)
                if completion_event.wait(timeout=50):
                    print(f"Auto-tuning completed for {api_name}")

                    time.sleep(5)  # Small delay to ensure stability before resetting tuning
                    _reset_tuning(tuning_services, gpu)  # Reset tuning to factory settings after test
                else:
                    print(f"Auto-tuning timed out after 50 seconds for {api_name}")

        except Exception as e:
            print(f"Exception occurred during auto-tuning for {api_name}: {e}")
            raise
