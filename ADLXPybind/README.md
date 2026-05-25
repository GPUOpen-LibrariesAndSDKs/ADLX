# ADLXPybind

This document describes how to build the Python bindings for ADLX, as well as the environment in which they can be executed.

Documentation to C/Cpp ADLX can be found in https://gpuopen.com/manuals/adlx/adlx-page_interfaces/

## 1. Building

**Supported Operating Systems**
- Windows® 11 (32- and 64-bit versions) and up.

**Build Tool**
- Visual Studio 2022 with C and C++ components for desktop.

**Build Prerequisites**
- ADLX SDK is installed.
- Python 3.12 is installed.
- pybind11 is installed.

The path to the Python 3.12 installation is set to the PYHOME system environment variable.

**Note**: The ADLX library is installed along with the AMD display driver.

**Build Instructions**
- Run Visual Studio 2022.
- Open ~ADLXPybind\ADLXPybind.sln.
- Rebuild the project.

## 2. Packing into wheel
**Note**: before packing bindings into wheel please copy compiled ADLXPybind.pyd file to unit test folder: `~ADLXPybind\adlx_tests`
and run the unit tests, be sure that all tests passed, infomation how to run unit tests can be found here: `~ADLXPybind\adlx_tests\_readme.txt `
- copy ADLXPybind.pyd file into: `~ADLXPybind\build_wheel\adlxpybind`
- update bidnings verion in file: `~ADLXPybind\build_wheel\libversion.txt`
- run bat file: `~ADLXPybind\build_wheel\build_wheel.bat`
- wheel file will be generated in folder: `~ADLXPybind\build_wheel\build_wheel\dist`

## 3. Usage example
- install wheel in your Python environment, example: `$pip install <path_to_wheel>`
- now you can import and use the bindings:

```python
from typing import List
import adlxpybind.ADLXPybind as ADLX


def check_tunning_services(system:ADLX.IADLXSystem):
    """Prints if gpu support autotingin

    :param system: ADLX System Interface
    :type system: ADLX.IADLXSystem
    """
    tuning_services: ADLX.IADLXGPUTuningServices = system.GetGPUTuningServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    
    for gpu in gpus:
        is_supported_auto_tuning = tuning_services.IsSupportedAutoTuning(gpu)
        asic_name = gpu.Name()
        if is_supported_auto_tuning:
            print(f"GPU Auto Tuning is supported on asic: {asic_name}")
        else:
            print(f"GPU Auto Tuning is NOT supported on asic: {asic_name}")


def main():
    adlx: ADLX = ADLX.ADLXHelper()
    ret: ADLX.ADLX_RESULT = adlx.Initialize()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK

    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    check_tunning_services(system=system)
    ret: ADLX.ADLX_RESULT = adlx.Terminate()
    assert ret == ADLX.ADLX_RESULT.ADLX_OK

if __name__ == "__main__":
    main()
```


## Contribution process
 * Expose the desired API [(C++ bind.cpp)](./ADLXPybind/ADLXPybind/bind.cpp) 
 * Write pytest tests for the added API [~ADLXPybind\adlxtest](./adlx_tests/)
 * Build the `.pyd` binary and store it in [~ADLXPybind\adlxtest](./adlx_tests/) 
 * Run the new API test and if possible, run regression tests
 * Create wheel package, don't forgate to increase version number
 * Create a PR in this repo, showing the test case passed
 * after PR is approved, deploy the .whl package in the [ADLX](https://github.com/GPUOpen-LibrariesAndSDKs/ADLX)
