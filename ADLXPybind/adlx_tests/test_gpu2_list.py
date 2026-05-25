#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IADLXGPU2List API tests. """
# pylint: disable=I1101
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_gpu_connect_gpus_returns_gpu2_list(adlx):
    """Call GetGPUConnectGPUs() on IADLXPowerTuningServices. Expect IADLXGPU2List."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    power_tuning: ADLX.IADLXPowerTuningServices = system.GetPowerTuningServices()

    if not power_tuning.IsGPUConnectSupported():
        pytest.skip("GPU Connect not supported on this system")

    gpu2_list: ADLX.IADLXGPU2List = power_tuning.GetGPUConnectGPUs()
    assert gpu2_list is not None
    assert isinstance(gpu2_list, ADLX.IADLXGPU2List)


def test_gpu2_list_at(adlx):
    """Call At() on IADLXGPU2List. Expect valid GPU2 object at index 0."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    power_tuning: ADLX.IADLXPowerTuningServices = system.GetPowerTuningServices()

    if not power_tuning.IsGPUConnectSupported():
        pytest.skip("GPU Connect not supported on this system")

    gpu2_list: ADLX.IADLXGPU2List = power_tuning.GetGPUConnectGPUs()
    if gpu2_list is None or gpu2_list.Empty():
        pytest.skip("No GPU Connect GPUs available")

    gpu2 = gpu2_list.At(0)
    assert gpu2 is not None
