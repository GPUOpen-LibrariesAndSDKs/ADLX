:: This batch file sets up the Python virtual environment and installs dependencies using uv.
@echo off
setlocal

:: Check if uv is available
where /q uv
if ERRORLEVEL 1 (
	echo uv is not installed or not in your PATH.
	echo Install it from https://docs.astral.sh/uv/getting-started/installation/
	exit /b 1
)

echo Setting up virtual environment and installing dependencies...
uv sync
if ERRORLEVEL 1 (
	echo Failed to sync dependencies
	exit /b 1
)

echo Setup complete!
echo.
echo Available options:
echo - Run build.bat to build the executable
echo - Run run.bat to run the executable (after building)
echo.
exit /b 0
