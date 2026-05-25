#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IDLAXI2C interface API tests. """
# pylint: disable=I1101
from typing import List, Tuple

import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "line",
    (
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OD_CONTROL,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM2,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM3,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM4,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM5,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM6,
    ),
)
def test_i2c_is_supportred(adlx, line):
    """Call isSupported() on IDLAXI2C interface. Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        is_supported: bool = i2e_services.IsSupported(line, 1)
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize(
    "line",
    (
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OD_CONTROL,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM2,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM3,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM4,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM5,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM6,
    ),
)
def test_i2c_read(adlx, line):
    """Call Read() on IDLAXI2C interface. Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        ret_read: Tuple = i2e_services.Read(line, 100, 0x93, 0x30, 2)
        assert ret_read
        assert isinstance(ret_read[0], ADLX.ADLX_RESULT)
        assert isinstance(ret_read[1], list)


@pytest.mark.parametrize(
    "line",
    (
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OD_CONTROL,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM2,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM3,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM4,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM5,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM6,
    ),
)
def test_i2c_repeated_start_read(adlx, line):
    """Call RepeatedStartRead() on IDLAXI2C interface. Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        ret_read: Tuple = i2e_services.RepeatedStartRead(line, 100, 0x93, 0x30, 2)
        assert ret_read
        assert isinstance(ret_read[0], ADLX.ADLX_RESULT)
        assert isinstance(ret_read[1], list)


@pytest.mark.parametrize(
    "line",
    (
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OD_CONTROL,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM2,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM3,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM4,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM5,
        ADLX.ADLX_I2C_LINE.I2C_LINE_OEM6,
    ),
)
def test_i2c_write(adlx, line):
    """Call Write() on IDLAXI2C interface. Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        ret_read: ADLX.ADLX_RESULT = i2e_services.Write(line, 100, 0x93, 0x30, 2, b"\xb0")
        assert ret_read
        assert isinstance(ret_read, ADLX.ADLX_RESULT)


def test_i2c_version(adlx):
    """Call Version() on IDLAXI2C interface. Expect bool response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        i2e_services: ADLX.IADLXI2C = system.GetI2C(gpu)
        version: str = i2e_services.Version()
        assert isinstance(version, str)
        assert version != "0.0"
