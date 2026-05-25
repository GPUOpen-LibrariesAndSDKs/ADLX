#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for GPU Tunning tests """
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback
def callback_tuning_changed_listener(p_gpu_tuning_changed_event) -> bool:
    gpu = p_gpu_tuning_changed_event.GetGPU()
    assert gpu
    assert isinstance(gpu, ADLX.IADLXGPU)

    is_automatic_tuning_changed: bool = p_gpu_tuning_changed_event.IsAutomaticTuningChanged()
    assert isinstance(is_automatic_tuning_changed, bool)

    is_manual_fan_tuning_changed: bool = p_gpu_tuning_changed_event.IsManualFanTuningChanged()
    assert isinstance(is_manual_fan_tuning_changed, bool)

    is_manual_gpu_clk_tuning_changed: bool = p_gpu_tuning_changed_event.IsManualGPUCLKTuningChanged()
    assert isinstance(is_manual_gpu_clk_tuning_changed, bool)

    is_manual_power_tuning_changed: bool = p_gpu_tuning_changed_event.IsManualPowerTuningChanged()
    assert isinstance(is_manual_power_tuning_changed, bool)

    is_manual_vram_tuning_changed: bool = p_gpu_tuning_changed_event.IsManualVRAMTuningChanged()
    assert isinstance(is_manual_vram_tuning_changed, bool)

    is_reset_tuning_changed: bool = p_gpu_tuning_changed_event.IsPresetTuningChanged()
    assert isinstance(is_reset_tuning_changed, bool)

    # IADLXGPUTuningChangedEvent1
    is_smart_access_memory_changed: bool = p_gpu_tuning_changed_event.IsSmartAccessMemoryChanged()
    assert isinstance(is_smart_access_memory_changed, bool)

    smart_access_memory_status: tuple = p_gpu_tuning_changed_event.GetSmartAccessMemoryStatus()
    assert isinstance(smart_access_memory_status, tuple)
    assert len(smart_access_memory_status) == 2

    return True


@pytest.mark.parametrize(
    "method,mtype",
    [
        ("IsAtFactory", bool),
        ("IsSupportedAutoTuning", bool),
        ("IsSupportedManualFanTuning", bool),
        ("IsSupportedManualGFXTuning", bool),
        ("IsSupportedManualPowerTuning", bool),
        ("IsSupportedManualVRAMTuning", bool),
        ("IsSupportedPresetTuning", bool),
    ],
)
def test_tuning_service_params(adlx, method, mtype):
    """Check if all Tuning Service methods return non empty objects."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        param = getattr(tuning_services, method)(gpu)
        if mtype is bool:
            assert isinstance(param, mtype)
        else:
            assert param
            assert isinstance(param, mtype)


def test_tuning_service_reset_to_factory(adlx):
    """Call ResetToFactory() method and expect no errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        ret_reset: ADLX.ADLX_RESULT = tuning_services.ResetToFactory(gpu)
        assert ret_reset == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize(
    "method,mtype",
    [
        ("VendorId", str),
        ("ASICFamilyType", ADLX.ADLX_ASIC_FAMILY_TYPE),
        ("Type", ADLX.ADLX_GPU_TYPE),
        ("IsExternal", bool),
        ("Name", str),
        ("DriverPath", str),
        ("PNPString", str),
        ("HasDesktops", bool),
        ("TotalVRAM", int),
        ("VRAMType", str),
        ("BIOSInfo", tuple),
        ("DeviceId", str),
        ("RevisionId", str),
        ("SubSystemId", str),
        ("SubSystemVendorId", str),
        ("UniqueId", int),
        ("PCIBusType", ADLX.ADLX_PCI_BUS_TYPE),
        ("PCIBusLaneWidth", int),
        ("MultiGPUMode", ADLX.ADLX_MGPU_MODE),
        ("ProductName", str),
        ("AMDSoftwareReleaseDate", tuple),
        ("AMDSoftwareVersion",str),
        ("DriverVersion", str),
        ("AMDWindowsDriverVersion", str),
        ("IsSupportedApplicationList", bool),
        ("LUID", ADLX.ADLX_LUID),
        # IADLXGPU2
        ("IsPowerOff", bool),
        # IADLXGPU3
        ("MicroArchitecture", str),
        ("HighestVRAMBandwidth", int),
        ("InvisibleVRAM", int),
        ("VisibleVRAM", int),
        ("VRAMVendorRevId", int),
        ("VRAMBandwidth", int),
        ("VRAMBitRate", int),
        ("IsSupportedStressTest", bool),
    ],
)
def test_gpu_params(adlx, method, mtype):
    """Check all GPU params. Expect no errors and correct type"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        param = getattr(gpu, method)()
        if mtype in (bool, int):
            assert isinstance(param, mtype)
        else:
            assert param is not None
            assert isinstance(param, mtype)


def test_get_applications(adlx):
    """Call GetApplications() method on GPU. Expect non-empty response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        applications: List[ADLX.IADLXApplication] = gpu.GetApplications()
        if applications:
            assert isinstance(applications, list)
            for app in applications:
                assert isinstance(app, ADLX.IADLXApplication)

def test_vendor_id(adlx):
    """Call VendorId() method on gpu. Expect AMD vendor id: 1002"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        vendor_id: str = gpu.VendorId()
        assert vendor_id == "1002"


def test_add_gpu_tuning_event_listener_tuning(adlx):
    """call AddGPUTuningEventListener() on GPU Tuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    tuning_handler: ADLX.IADLXGPUTuningChangedHandling = tuning_services.GetGPUTuningChangedHandling()

    callback: ADLX.PyGPUTuningChangedListenerCallback = ADLX.PyGPUTuningChangedListenerCallback()
    callback.call = callback_tuning_changed_listener

    ret_add: ADLX.RESULT = tuning_handler.AddGPUTuningEventListener(callback)
    assert ret_add
    assert ret_add == ADLX.ADLX_RESULT.ADLX_OK


def test_remove_gpu_tuning_event_listener_tuning(adlx):
    """call RemoveGPUTuningEventListener() on GPU Tuning interface. We expect non-empty response. No errors"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    tuning_handler: ADLX.IADLXGPUTuningChangedHandling = tuning_services.GetGPUTuningChangedHandling()

    callback: ADLX.PyGPUTuningChangedListenerCallback = ADLX.PyGPUTuningChangedListenerCallback()
    callback.call = callback_tuning_changed_listener

    ret_add: ADLX.RESULT = tuning_handler.AddGPUTuningEventListener(callback)
    assert ret_add
    assert ret_add == ADLX.ADLX_RESULT.ADLX_OK

    ret_remove: ADLX.RESULT = tuning_handler.RemoveGPUTuningEventListener(callback)
    assert ret_remove
    assert ret_remove == ADLX.ADLX_RESULT.ADLX_OK
