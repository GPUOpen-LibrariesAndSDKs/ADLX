# ADLXPybind

ADLXPybind provides Python bindings for the AMD Device Library eXtra (ADLX). This document explains how to build the extension module, run its tests, and use the installed Python package.

For the native ADLX C++ API, see the [ADLX API documentation](https://gpuopen.com/manuals/adlx/adlx-page_interfaces/).

## 1. Requirements

- 64-bit Windows
- Visual Studio 2022 with the **Desktop development with C++** workload
- Python 3.13 (64-bit)
- [pybind11](https://pybind11.readthedocs.io/)
- An ADLX-compatible AMD display driver

Install pybind11 into the Python environment used for the build:

```powershell
py -3.13 -m pip install pybind11
```

Set the `PYHOME` environment variable to the root of that Python 3.13 installation. The directory must contain `include`, `libs`, and `Lib\site-packages\pybind11\include`.

For example, set it for the current Windows user from PowerShell, then restart Visual Studio so that it sees the new value:

```powershell
$pythonHome = Split-Path -Parent (py -3.13 -c "import sys; print(sys.executable)")
[Environment]::SetEnvironmentVariable("PYHOME", $pythonHome, "User")
```

The ADLX runtime library is installed with the AMD display driver. The ADLX headers and helper sources used by this project are included in the repository under `SDK`.

## 2. Build the extension

1. Open [`ADLXPybind/ADLXPybind.sln`](./ADLXPybind/ADLXPybind.sln) in Visual Studio 2022.
2. Select the `Release` configuration and the `x64` platform.
3. Build or rebuild the solution.

The project produces the Python extension module `ADLX.pyd`. The filename must remain consistent with the module declaration `PYBIND11_MODULE(ADLX, m)`.

## 3. Run the tests

The tests support either a directly built `ADLX.pyd` or the installed `amd-adlx` package from PyPI.

### Test the extension directly

1. Copy the compiled `ADLX.pyd` into [`adlx_tests`](./adlx_tests/).
2. Create and activate a Python 3.13 virtual environment.
3. Install pytest and run the test suite.

```powershell
cd adlx_tests
py -3.13 -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install pytest
python -m pytest -vs
```

### Test an installed wheel

```powershell
cd adlx_tests
py -3.13 -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install pytest amd-adlx
python -m pytest -vs
```

See [`adlx_tests/_readme.txt`](./adlx_tests/_readme.txt) for additional test instructions and troubleshooting information.

## 4. Usage example

Install the package from PyPI into the active Python environment:

```powershell
python -m pip install amd-adlx
```

Then import and use the binding:

```python
import gc

from adlx import ADLX


def check_tuning_services(system: ADLX.IADLXSystem) -> None:
    """Print whether each GPU supports automatic tuning."""
    tuning_services = system.GetGPUTuningServices()

    for gpu in system.GetGPUs():
        asic_name = gpu.Name()
        if tuning_services.IsSupportedAutoTuning(gpu):
            print(f"GPU auto-tuning is supported on ASIC: {asic_name}")
        else:
            print(f"GPU auto-tuning is not supported on ASIC: {asic_name}")


def main() -> None:
    helper = ADLX.ADLXHelper()
    result = helper.Initialize()
    if result != ADLX.ADLX_RESULT.ADLX_OK:
        raise RuntimeError(f"Failed to initialize ADLX: {result}")

    system = None
    try:
        system = helper.GetSystemServices()
        check_tuning_services(system)
    finally:
        # Release wrapper objects before shutting down the native ADLX system.
        del system
        gc.collect()
        result = helper.Terminate()
        if result != ADLX.ADLX_RESULT.ADLX_OK:
            raise RuntimeError(f"Failed to terminate ADLX: {result}")


if __name__ == "__main__":
    main()
```

When using the unpackaged extension directly, place `ADLX.pyd` on `sys.path` and replace the import above with:

```python
import ADLX
```

## 5. Contribution process

1. Add the binding to the appropriate `bind_*.cpp` source file. The module entry point is [`bind.cpp`](./ADLXPybind/ADLXPybind/bind.cpp).
2. Add pytest coverage under [`adlx_tests`](./adlx_tests/).
3. Build `ADLX.pyd` in the `Release|x64` configuration.
4. Run the new tests and the complete regression test suite where possible.
5. Build and validate the wheel using the project's release packaging process, incrementing the package version when required.
6. Open a pull request that describes the exposed API and includes the relevant test results.
7. After the pull request is approved, publish the validated wheel through the project's release process.
