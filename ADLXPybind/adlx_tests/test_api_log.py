#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind logging API tests. """
import os
import pytest

try:
    import ADLX
except ImportError:
    from adlx import ADLX


@pytest.mark.parametrize(
    "severity",
    (
        ADLX.ADLX_LOG_SEVERITY.LDEBUG,
        ADLX.ADLX_LOG_SEVERITY.LWARNING,
        ADLX.ADLX_LOG_SEVERITY.LERROR,
    ),
)
def test_enable_log_to_file(adlx, severity):
    """Enable ADLX logging to file with different severity. Check if calling function EnableLog was successfull. Check if log file was created."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    mode: ADLX.ADLX_LOG_DESTINATION = ADLX.ADLX_LOG_DESTINATION(0)  # to file

    current_dir: str = os.path.dirname(os.path.abspath(__file__))
    log_file_full_path: str = os.path.join(current_dir, "test_enable_log_to_file.log")
    if os.path.exists(log_file_full_path):
        os.remove(log_file_full_path)
    ret: ADLX.ADLX_RESULT = system.EnableLog(mode, severity, None, log_file_full_path)
    assert ret == ADLX.ADLX_RESULT.ADLX_OK
    assert os.path.exists(log_file_full_path)


@pytest.mark.parametrize(
    "severity",
    (
        ADLX.ADLX_LOG_SEVERITY.LDEBUG,
        ADLX.ADLX_LOG_SEVERITY.LWARNING,
        ADLX.ADLX_LOG_SEVERITY.LERROR,
    ),
)
def test_enable_log_to_debugger(adlx, severity):
    """Enable ADLX logging to debugger window with different severity. Check if calling function EnableLog was successfull."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    mode: ADLX.ADLX_LOG_DESTINATION = ADLX.ADLX_LOG_DESTINATION(1)  # to debugger window

    ret: ADLX.ADLX_RESULT = system.EnableLog(mode, severity, None, "")
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize(
    "severity",
    (
        ADLX.ADLX_LOG_SEVERITY.LDEBUG,
        ADLX.ADLX_LOG_SEVERITY.LWARNING,
        ADLX.ADLX_LOG_SEVERITY.LERROR,
    ),
)
def test_enable_log_to_file_nullptr(adlx, severity):
    """Enable ADLX logging to file with different severity, pass fileName as nullptr. Check if calling function EnableLog failed."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    mode: ADLX.ADLX_LOG_DESTINATION = ADLX.ADLX_LOG_DESTINATION(0)  # to file

    ret: ADLX.ADLX_RESULT = system.EnableLog(mode, severity, None, "")
    assert ret == ADLX.ADLX_RESULT.ADLX_FAIL


def test_log_callback(adlx):
    """Enable ADLX callback logging."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    log_callback: ADLX.PyLogCallback = ADLX.PyLogCallback()
    ret: ADLX.ADLX_RESULT = system.EnableLog(ADLX.ADLX_LOG_DESTINATION(2), ADLX.ADLX_LOG_SEVERITY(0), log_callback, "")
    assert ret == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize(
    "mode,severity,plogger,filename",
    # fmt: off
    [
        (ADLX.ADLX_LOG_DESTINATION(0), ADLX.ADLX_LOG_SEVERITY.LDEBUG, None, "test_enable_log_twice.log"), 
        (ADLX.ADLX_LOG_DESTINATION(0), ADLX.ADLX_LOG_SEVERITY.LWARNING, None, "test_enable_log_twice.log"), 
        (ADLX.ADLX_LOG_DESTINATION(0), ADLX.ADLX_LOG_SEVERITY.LERROR, None, "test_enable_log_twice.log"), 

        (ADLX.ADLX_LOG_DESTINATION(1), ADLX.ADLX_LOG_SEVERITY.LDEBUG, None, "test_enable_log_twice.log"), 
        (ADLX.ADLX_LOG_DESTINATION(1), ADLX.ADLX_LOG_SEVERITY.LWARNING, None, "test_enable_log_twice.log"), 
        (ADLX.ADLX_LOG_DESTINATION(1), ADLX.ADLX_LOG_SEVERITY.LERROR, None, "test_enable_log_twice.log"), 

        (ADLX.ADLX_LOG_DESTINATION(2), ADLX.ADLX_LOG_SEVERITY.LDEBUG, ADLX.PyLogCallback(), ""), 
        (ADLX.ADLX_LOG_DESTINATION(2), ADLX.ADLX_LOG_SEVERITY.LWARNING, ADLX.PyLogCallback(), ""), 
        (ADLX.ADLX_LOG_DESTINATION(2), ADLX.ADLX_LOG_SEVERITY.LERROR, ADLX.PyLogCallback(), ""),         
    ],
    # fmt: on
)
def test_enable_log_twice(adlx, mode, severity, plogger, filename):
    """Enabling log more than once shoult result in ADLX_ALREADY_ENABLED."""
    if filename:
        if os.path.exists(filename):
            os.remove(filename)

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    ret: ADLX.ADLX_RESULT = system.EnableLog(mode, severity, plogger, filename)
    assert ret == ADLX.ADLX_RESULT.ADLX_OK

    ret2: ADLX.ADLX_RESULT = system.EnableLog(mode, severity, plogger, filename)
    assert ret2 == ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED
