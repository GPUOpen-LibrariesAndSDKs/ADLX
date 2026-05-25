#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind Variable Graphics Memory tests. Tests for GetVariableGraphicsMemory and related interfaces. """
# pylint: disable=I1101
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def test_get_variable_graphics_memory(adlx):
    """Call GetVariableGraphicsMemory() on IADLXSystem interface. Object may be None if unsupported."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        assert isinstance(vgm, ADLX.IADLXVariableGraphicsMemory)


def test_variable_graphics_memory_is_supported(adlx):
    """Call IsSupported() on IADLXVariableGraphicsMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        supported = vgm.IsSupported()
        if supported is not None:
            assert isinstance(supported, bool)


def test_variable_graphics_memory_get_default_option(adlx):
    """Call GetDefaultOption() on IADLXVariableGraphicsMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetDefaultOption()
        if opt:
            assert isinstance(opt, ADLX.IADLXVariableGraphicsMemoryOption)


def test_variable_graphics_memory_get_option(adlx):
    """Call GetOption() on IADLXVariableGraphicsMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetOption()
        if opt:
            assert isinstance(opt, ADLX.IADLXVariableGraphicsMemoryOption)


def test_variable_graphics_memory_get_available_options(adlx):
    """Call GetAvailableOptions() on IADLXVariableGraphicsMemory interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opts: ADLX.IADLXVariableGraphicsMemoryOptionList = vgm.GetAvailableOptions()
        if opts:
            assert isinstance(opts, ADLX.IADLXVariableGraphicsMemoryOptionList)


def test_variable_graphics_memory_option_name(adlx):
    """Call Name() on IADLXVariableGraphicsMemoryOption from GetDefaultOption()."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetDefaultOption()
        if opt:
            name = opt.Name()
            if name is not None:
                assert isinstance(name, str)


def test_variable_graphics_memory_option_mode(adlx):
    """Call Mode() on IADLXVariableGraphicsMemoryOption from GetDefaultOption()."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetDefaultOption()
        if opt:
            mode = opt.Mode()
            if mode is not None:
                assert isinstance(mode, ADLX.ADLX_VARIABLE_GRAPHICS_MEMORY_MODE)


def test_variable_graphics_memory_option_memory_carved(adlx):
    """Call MemoryCarved() on IADLXVariableGraphicsMemoryOption from GetDefaultOption()."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetDefaultOption()
        if opt:
            carved = opt.MemoryCarved()
            if carved is not None:
                assert isinstance(carved, float)


def test_variable_graphics_memory_option_memory_remaining(adlx):
    """Call MemoryRemaining() on IADLXVariableGraphicsMemoryOption from GetDefaultOption()."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opt: ADLX.IADLXVariableGraphicsMemoryOption = vgm.GetDefaultOption()
        if opt:
            remaining = opt.MemoryRemaining()
            if remaining is not None:
                assert isinstance(remaining, float)


def test_variable_graphics_memory_available_options_iteration(adlx):
    """Iterate available options and check each option's properties."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    vgm: ADLX.IADLXVariableGraphicsMemory = system.GetVariableGraphicsMemory()
    if vgm:
        opts: ADLX.IADLXVariableGraphicsMemoryOptionList = vgm.GetAvailableOptions()
        if opts and opts.Size() > 0:
            for i in range(opts.Size()):
                opt: ADLX.IADLXVariableGraphicsMemoryOption = opts.At(i)
                assert isinstance(opt, ADLX.IADLXVariableGraphicsMemoryOption)
