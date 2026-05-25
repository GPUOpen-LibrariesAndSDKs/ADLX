:: This batch file setups a users environment to build an executable from a
:: Python script.
@echo off
setlocal

where /q uv
if ERRORLEVEL 1 (
    echo uv is not installed or not found in PATH.
    echo Please install uv: https://docs.astral.sh/uv/getting-started/installation/
    exit /b 1
)

uv sync
if ERRORLEVEL 1 (
    echo Setup failed
    exit /b 1
)

echo Setup complete
endlocal
exit /b 0
