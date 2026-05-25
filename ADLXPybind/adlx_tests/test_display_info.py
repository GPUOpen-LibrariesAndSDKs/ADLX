#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for testing display """
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "method,mtype",
    [
        ("Name", str),
        ("DisplayType", ADLX.ADLX_DISPLAY_TYPE),
        ("ConnectorType", ADLX.ADLX_DISPLAY_CONNECTOR_TYPE),
        ("ManufacturerID", int),
        ("EDID", str),
        ("NativeResolution", tuple),
        ("RefreshRate", float),
        ("PixelClock", int),
        ("ScanType", ADLX.ADLX_DISPLAY_SCAN_TYPE),
        ("GetGPU", object),
        ("UniqueId", int),
    ],
)
def test_display_info(adlx, method, mtype):
    """
    Call GetDisplays on ADLX.IADLXDisplayServices. Expect at lest one display connected.
    Check iof all display parameters are not empty.
    """
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")

    for display in display_list:
        param = getattr(display, method)()
        assert isinstance(param, mtype)
    del display_list, display_service, system


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
        ("TotalVRAM", int),
        ("VRAMType", str),
        ("BIOSInfo", tuple),
        ("DeviceId", str),
        ("RevisionId", str),
        ("SubSystemId", str),
        ("SubSystemVendorId", str),
        ("UniqueId", int),
    ],
)
def test_get_gpu_params_from_display(adlx, method, mtype):
    """
    Check if all gpu properties are not empty. Take gpu iterate through connected displays.
    Expect at least one display.
    """
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")

    for display in display_list:
        gpu: ADLX.IADLXGPU = display.GetGPU()
        param = getattr(gpu, method)()
        assert isinstance(param, mtype)
        del gpu
    del display_list, display_service, system
