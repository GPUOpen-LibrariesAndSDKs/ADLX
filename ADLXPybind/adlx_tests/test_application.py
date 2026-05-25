#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" ADLXPybind IDLAXApplication interface API tests. """
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX

@pytest.mark.parametrize(
    "method,mtype",
    [
        ("ProcessID", int),
        ("Name", str),
        ("FullPath", str),
        ("GPUDependencyType", ADLX.ADLX_APP_GPU_DEPENDENCY),
    ],
)
def test_application_params(adlx, method, mtype):
    """Call ProcessID() method on application. Expect non-empty response"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        if gpu.IsSupportedApplicationList():
            applications: List[ADLX.IADLXApplication] = gpu.GetApplications()
            if applications:
                assert isinstance(applications, list)
                for app in applications:
                    param = getattr(app, method)()
                    if mtype is bool:
                        assert isinstance(param, mtype)
                    else:
                        # only check if param is not None
                        # because some params can be empty strings
                        # or empty tuples, but not None
                        assert param is not None
                        # check if param is of expected type
                        assert isinstance(param, mtype)