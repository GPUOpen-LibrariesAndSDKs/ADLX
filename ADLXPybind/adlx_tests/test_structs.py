#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

"""
ADLXPybind structs tests.
Purpose of this file is to check if calling ADLX API strucs does not report unexpected errors.
"""
# pylint: disable=I1101
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("maxValue", int),
        ("minValue", int),
        ("step", int),
    ],
)
def test_adlx_intrange(property_name, expected_type):
    """Create struct object ADLX_IntRange. Expect all properties of the right type"""
    adlx_intrange: ADLX.ADLX_IntRange = ADLX.ADLX_IntRange()
    assert isinstance(adlx_intrange, ADLX.ADLX_IntRange)
    property_value = getattr(adlx_intrange, property_name)
    assert isinstance(property_value, expected_type)

@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("red", int),
        ("green", int),
        ("blue", int),
    ],
)
def test_adlx_uint16_rgb(property_name, expected_type):
    """Create struct object ADLX_Uint16RGB. Expect all properties of the right type"""
    adlx_uint16_rgb: ADLX.ADLX_UINT16_RGB = ADLX.ADLX_UINT16_RGB()
    assert isinstance(adlx_uint16_rgb, ADLX.ADLX_UINT16_RGB)
    property_value = getattr(adlx_uint16_rgb, property_name)
    assert isinstance(property_value, expected_type)
   

@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("resWidth", int),
        ("resHeight", int),
        ("refreshRate", int),
        ("presentation", ADLX.ADLX_DISPLAY_SCAN_TYPE),
        ("timingStandard", ADLX.ADLX_TIMING_STANDARD),
        ("GPixelClock", int),
        ("detailedTiming", ADLX.ADLX_TimingInfo),
    ],
)
def test_adlx_customresolution(property_name, expected_type):
    """Create struct object ADLX_CustomResolution. Expect all properties of the right type"""
    adlx_customresolution: ADLX.ADLX_CustomResolution = ADLX.ADLX_CustomResolution()
    assert isinstance(adlx_customresolution, ADLX.ADLX_CustomResolution)
    property_value = getattr(adlx_customresolution, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("timingFlags", int),
        ("hTotal", int),
        ("vTotal", int),
        ("hDisplay", int),
        ("vDisplay", int),
        ("hFrontPorch", int),
        ("vFrontPorch", int),
        ("hSyncWidth", int),
        ("vSyncWidth", int),
        ("hPolarity", int),
        ("vPolarity", int),
    ],
)
def test_adlx_timinginfo(property_name, expected_type):
    """Create struct object ADLX_TimingInfo. Expect all properties of the right type"""
    adlx_timinginfo: ADLX.ADLX_TimingInfo = ADLX.ADLX_TimingInfo()
    assert isinstance(adlx_timinginfo, ADLX.ADLX_TimingInfo)
    property_value = getattr(adlx_timinginfo, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("coefficientA0", int),
        ("coefficientA1", int),
        ("coefficientA2", int),
        ("coefficientA3", int),
        ("gamma", int),
    ],
)
def test_adlx_regammacoeff(property_name, expected_type):
    """Create struct object ADLX_RegammaCoeff. Expect all properties of the right type"""
    adlx_regammacoeff: ADLX.ADLX_RegammaCoeff = ADLX.ADLX_RegammaCoeff()
    assert isinstance(adlx_regammacoeff, ADLX.ADLX_RegammaCoeff)
    property_value = getattr(adlx_regammacoeff, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("blue", ADLX.ADLX_Point),
        ("green", ADLX.ADLX_Point),
        ("red", ADLX.ADLX_Point),
    ],
)
def test_adlx_gamutcolorspace(property_name, expected_type):
    """Create struct object ADLX_GamutColorSpace. Expect all properties of the right type"""
    adlx_gamutcolorspace: ADLX.ADLX_GamutColorSpace = ADLX.ADLX_GamutColorSpace()
    assert isinstance(adlx_gamutcolorspace, ADLX.ADLX_GamutColorSpace)
    property_value = getattr(adlx_gamutcolorspace, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("x", int),
        ("y", int),
    ],
)
def test_adlx_point(property_name, expected_type):
    """Create struct object ADLX_Point. Expect all properties of the right type"""
    adlx_point: ADLX.ADLX_Point = ADLX.ADLX_Point()
    assert isinstance(adlx_point, ADLX.ADLX_Point)
    property_value = getattr(adlx_point, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("gamutB", float),
        ("gamutG", float),
        ("gamutR", float),
    ],
)
def test_adlx_rgb(property_name, expected_type):
    """Create struct object ADLX_RGB. Expect all properties of the right type"""
    adlx_rgb: ADLX.ADLX_RGB = ADLX.ADLX_RGB()
    assert isinstance(adlx_rgb, ADLX.ADLX_RGB)
    property_value = getattr(adlx_rgb, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("adapterIndex", int),
        ("VidPnSourceId", int),
        ("bus", int),
        ("device", int),
        ("function", int),
    ],
)
def test_pyadlidsfromadlx(property_name, expected_type):
    """Create struct object PyADLIdsFromADLX. Expect all properties of the right type"""
    adlx_pyadlidsfromadlx: ADLX.PyADLIdsFromADLX = ADLX.PyADLIdsFromADLX()
    assert isinstance(adlx_pyadlidsfromadlx, ADLX.PyADLIdsFromADLX)
    property_value = getattr(adlx_pyadlidsfromadlx, property_name)
    assert isinstance(property_value, expected_type)


@pytest.mark.parametrize(
    "property_name,expected_type",
    [
        ("bus", int),
        ("device", int),
        ("function", int),
    ],
)
def test_pybdffromadlxgpu(property_name, expected_type):
    """Create struct object PyBdfFromADLXGPU. Expect all properties of the right type"""
    adlx_pybdffromadlxgpu: ADLX.PyBdfFromADLXGPU = ADLX.PyBdfFromADLXGPU()
    assert isinstance(adlx_pybdffromadlxgpu, ADLX.PyBdfFromADLXGPU)
    property_value = getattr(adlx_pybdffromadlxgpu, property_name)
    assert isinstance(property_value, expected_type)
