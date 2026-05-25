#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for ADL Mapping service interfaces methods  """
# pylint: disable=I1101
import pytest
import time

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_adl_mapping(adlx):
    """Gets the ADL Mapping interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    #= adlx.QueryFullVersion()
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    assert adl_mapping
    assert isinstance(adl_mapping, ADLX.IADLMapping)


def test_adlidsfromadlxdesktop(adlx):
    """Gets the ADL Adapter index, Vid source ID, the PCIE bus number,
    device number, and function number corresponding to desktop with the
    specified IADLXDesktop interface."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops: List[ADLX.IADLXDesktop] = desktop_services.GetDesktops()
    for desktop in desktops:
        adlidsfromadlxdesktop: ADLX.PyADLIdsFromADLX = adl_mapping.ADLIdsFromADLXDesktop(desktop)
        assert isinstance(adlidsfromadlxdesktop, ADLX.PyADLIdsFromADLX)
        assert isinstance(adlidsfromadlxdesktop.adapterIndex, int)
        assert isinstance(adlidsfromadlxdesktop.VidPnSourceId, int)
        assert isinstance(adlidsfromadlxdesktop.bus, int)
        assert isinstance(adlidsfromadlxdesktop.device, int)
        assert isinstance(adlidsfromadlxdesktop.function, int)


def test_adlidsfromadlxdisplay(adlx):
    """Gets the ADL Adapter index, display index, the PCI bus number,
    device number, and function number corresponding to the display with the
    specified IADLXDisplay interface."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        adlidsfromadlxdisplay: ADLX.PyADLIdsFromADLX = adl_mapping.ADLIdsFromADLXDisplay(display)
        assert isinstance(adlidsfromadlxdisplay, ADLX.PyADLIdsFromADLX)
        assert isinstance(adlidsfromadlxdisplay.adapterIndex, int)
        assert isinstance(adlidsfromadlxdisplay.VidPnSourceId, int)
        assert isinstance(adlidsfromadlxdisplay.bus, int)
        assert isinstance(adlidsfromadlxdisplay.device, int)
        assert isinstance(adlidsfromadlxdisplay.function, int)


def test_adladapterindexfromadlxgpu(adlx):
    """Gets the ADL Adapter index corresponding to the GPU with
    the specified IADLXGPU interface."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        adladapterindexfromadlxgpu: int = adl_mapping.AdlAdapterIndexFromADLXGPU(gpu)
        assert isinstance(adladapterindexfromadlxgpu, int)


def test_bdffromadlxgpu(adlx):
    """Gets the PCI bus number, device number, and function number
    corresponding to the GPU with the specified IADLXGPU interface."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        bdffromadlxgpu: ADLX.PyBdfFromADLXGPU = adl_mapping.BdfFromADLXGPU(gpu)
        assert isinstance(bdffromadlxgpu, ADLX.PyBdfFromADLXGPU)
        assert isinstance(bdffromadlxgpu.bus, int)
        assert isinstance(bdffromadlxgpu.device, int)
        assert isinstance(bdffromadlxgpu.function, int)


def test_getadlxdesktopfromadlids(adlx):
    """Gets the reference counted IADLXDesktop interface corresponding to
    the desktop with the specified ADL adapter index, VidPnSource ID,
    the PCI bus number, device number, and function number."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    desktop_services: ADLX.IADLXDesktopServices = system.GetDesktopsServices()
    desktops: List[ADLX.IADLXDesktop] = desktop_services.GetDesktops()
    for desktop in desktops:
        adlidsfromadlxdesktop: ADLX.PyADLIdsFromADLX = adl_mapping.ADLIdsFromADLXDesktop(desktop)

        getadlxdesktopfromadlids: ADLX.IADLXDesktop = adl_mapping.GetADLXDesktopFromADLIds(
            adlidsfromadlxdesktop.adapterIndex,
            adlidsfromadlxdesktop.VidPnSourceId,
            adlidsfromadlxdesktop.bus,
            adlidsfromadlxdesktop.device,
            adlidsfromadlxdesktop.function,
        )
        assert isinstance(getadlxdesktopfromadlids, ADLX.IADLXDesktop)
        assert getadlxdesktopfromadlids == desktop


def test_getadlxdisplayfromadlids(adlx):
    """Gets the reference counted IADLXDisplay interface corresponding to
    the display with the specified ADL adapter index, display index,
    PCI bus number, device number, and function number."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        adlidsfromadlxdisplay: ADLX.PyADLIdsFromADLX = adl_mapping.ADLIdsFromADLXDisplay(display)

        getadlxdisplayfromadlids: ADLX.IADLXDesktop = adl_mapping.GetADLXDisplayFromADLIds(
            adlidsfromadlxdisplay.adapterIndex,
            adlidsfromadlxdisplay.VidPnSourceId,
            adlidsfromadlxdisplay.bus,
            adlidsfromadlxdisplay.device,
            adlidsfromadlxdisplay.function,
        )
        assert isinstance(getadlxdisplayfromadlids, ADLX.IADLXDisplay)
        assert getadlxdisplayfromadlids == display


def test_getadlxgpufromadladapterindex(adlx):
    """Gets the reference counted IADLXGPU interface corresponding to
    the GPU with the specified ADL adapter index."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        adladapterindexfromadlxgpu: int = adl_mapping.AdlAdapterIndexFromADLXGPU(gpu)

        getadlxgpufromadladapterindex: ADLX.IADLXGPU = adl_mapping.GetADLXGPUFromAdlAdapterIndex(
            adladapterindexfromadlxgpu
        )
        assert isinstance(getadlxgpufromadladapterindex, ADLX.IADLXGPU)
        assert getadlxgpufromadladapterindex == gpu


def test_getadlxgpufrombdf(adlx):
    """Gets the reference counted IADLXGPU interface corresponding
    to the GPU with the specified PCI bus number, device number,
    and function number."""
    adl_mapping: ADLX.IADLMapping = adlx.GetAdlMapping()
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        bdffromadlxgpu: ADLX.PyBdfFromADLXGPU = adl_mapping.BdfFromADLXGPU(gpu)

        getadlxgpufrombdf: ADLX.IADLXGPU = adl_mapping.GetADLXGPUFromBdf(
            bdffromadlxgpu.bus, bdffromadlxgpu.device, bdffromadlxgpu.function
        )
        assert isinstance(getadlxgpufrombdf, ADLX.IADLXGPU)
        assert getadlxgpufrombdf == gpu
