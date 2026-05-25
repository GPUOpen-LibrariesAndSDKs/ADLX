#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IADLXGPU StartPowerOff and StartStressTest API tests. """
# pylint: disable=I1101
import pytest
import time
import threading

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_start_power_off(adlx):
    """Call StartPowerOff() on IADLXGPU (QI to IADLXGPU2). Expect ADLX_RESULT."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    power_tuning: ADLX.IADLXPowerTuningServices = system.GetPowerTuningServices()

    if not power_tuning.IsGPUConnectSupported():
        pytest.skip("GPU Connect not supported on this system")

    gpu2_list: ADLX.IADLXGPU2List = power_tuning.GetGPUConnectGPUs()
    if gpu2_list is None or gpu2_list.Empty():
        pytest.skip("No GPU Connect GPUs available")

    callback: ADLX.PyGPUConnectChangedListenerCallback = ADLX.PyGPUConnectChangedListenerCallback()
    callback.call = lambda event: True

    # Attempt StartPowerOff on the first GPU Connect GPU via the base IADLXGPU binding
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if gpu.IsPowerOff():
            continue
        ret: ADLX.ADLX_RESULT = gpu.StartPowerOff(callback, 30)
        assert isinstance(ret, ADLX.ADLX_RESULT)
        break


# Callback factory that captures the event for synchronization
def create_stress_test_callback(completion_event: threading.Event):
    """Factory function to create a callback that signals the completion event"""
    def callback_stress_test_finished_listener(gpu_obj, result) -> bool:
        assert gpu_obj is not None
        assert isinstance(result, bool)

        # Signal the test function that callback has completed
        completion_event.set()

        return True

    return callback_stress_test_finished_listener


def test_start_stress_test(adlx):
    """Call StartStressTest() on IADLXGPU (QI to IADLXGPU3). Expect ADLX_RESULT."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if not gpu.IsSupportedStressTest():
            continue

        try:
            # Create a threading event for synchronization with callback
            completion_event = threading.Event()

            callback: ADLX.PyGPUStressTestFinishedListenerCallback = ADLX.PyGPUStressTestFinishedListenerCallback()
            callback.call = create_stress_test_callback(completion_event)

            ret: ADLX.ADLX_RESULT = gpu.StartStressTest(callback, 15)
            assert isinstance(ret, ADLX.ADLX_RESULT)

            # Wait for stress test completion if succeeded
            if ret == ADLX.ADLX_RESULT.ADLX_OK:
                # Wait for callback to signal completion (max 50 seconds)
                if completion_event.wait(timeout=50):
                    print("Stress test completed successfully")
                    time.sleep(5)  # Small delay to ensure stability
                else:
                    print("Stress test timed out after 50 seconds")

        except Exception as e:
            print(f"Exception occurred during stress test: {e}")
            raise

        break