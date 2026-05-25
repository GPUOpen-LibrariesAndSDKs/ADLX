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


def test_getvalue_pf(adlx):
    """call GetValue() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        pixel_format: ADLX.ADLX_PIXEL_FORMAT = diplay_pixelformat.GetValue()
        assert isinstance(pixel_format, ADLX.ADLX_PIXEL_FORMAT)


def test_issupported_pf(adlx):
    """call IsSupported() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        supported: bool = diplay_pixelformat.IsSupported()
        assert isinstance(supported, bool)


def test_issupportedpixelformat_pf(adlx):
    """call IsSupportedPixelFormat() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        pixel_format: ADLX.ADLX_PIXEL_FORMAT = diplay_pixelformat.GetValue()
        supported: bool = diplay_pixelformat.IsSupportedPixelFormat(pixel_format)
        assert isinstance(supported, bool)


def test_issupportedrgb444full_pf(adlx):
    """call IsSupportedRGB444Full() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        supported: bool = diplay_pixelformat.IsSupportedRGB444Full()
        assert isinstance(supported, bool)


def test_issupportedrgb444limited_pf(adlx):
    """call IsSupportedRGB444Limited() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        supported: bool = diplay_pixelformat.IsSupportedRGB444Limited()
        assert isinstance(supported, bool)


def test_issupportedycbcr420_pf(adlx):
    """call IsSupportedYCbCr420() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        supported: bool = diplay_pixelformat.IsSupportedYCbCr420()
        assert isinstance(supported, bool)


def test_issupportedycbcr422_pf(adlx):
    """call IsSupportedYCbCr422() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        supported: bool = diplay_pixelformat.IsSupportedYCbCr422()
        assert isinstance(supported, bool)


def test_setvalue_pf(adlx):
    """call SetValue() on IADLXDisplayPixelFormat interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    for display in display_list:
        diplay_pixelformat: ADLX.IADLXDisplayPixelFormat = display_service.GetPixelFormat(display)
        pixel_format: ADLX.ADLX_PIXEL_FORMAT = diplay_pixelformat.GetValue()
        set_pixel_format: ADLX.ADLX_RESULT = diplay_pixelformat.SetValue(pixel_format)
        assert isinstance(set_pixel_format, ADLX.ADLX_RESULT)
