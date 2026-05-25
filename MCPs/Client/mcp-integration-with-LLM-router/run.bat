@echo off
setlocal

:: Check if the executable exists
if not exist "dist\mcp-integration-with-LLM-router.exe" (
    echo Error: mcp-integration-with-LLM-router.exe not found in dist folder
    echo Please run build.bat first to create the executable
    pause
    exit /b 1
)

:: Check for command line arguments
if "%1"=="" (
    echo Usage: run.bat [cli^|streamlit] [--llm-api-key KEY] [--llm-base-url URL]
    echo.
    echo Examples:
    echo   run.bat cli                                    # Run CLI interface
    echo   run.bat streamlit                              # Run Streamlit web interface
    echo   run.bat cli --llm-api-key YOUR_KEY             # Run with API key
    echo   run.bat cli --llm-base-url http://localhost    # Run with base URL
    echo.
    pause
    exit /b 1
)

:: Validate the mode argument
if not "%1"=="cli" if not "%1"=="streamlit" (
    echo Error: Invalid mode '%1'
    echo Valid modes are: cli, streamlit
    echo.
    pause
    exit /b 1
)

:: Check if environment variables are set (only warn if not passed as arguments)
set "HAS_API_KEY_ARG="
set "HAS_BASE_URL_ARG="

:: Check if --llm-api-key is in arguments
echo %* | findstr /C:"--llm-api-key" >nul
if not errorlevel 1 set HAS_API_KEY_ARG=1

:: Check if --llm-base-url is in arguments
echo %* | findstr /C:"--llm-base-url" >nul
if not errorlevel 1 set HAS_BASE_URL_ARG=1

if "%LLM_BASE_URL%"=="" if not defined HAS_BASE_URL_ARG (
    echo Warning: LLM_BASE_URL environment variable is not set and --llm-base-url not provided
    echo Please set it as environment variable or pass --llm-base-url argument
)

if "%LLM_API_KEY%"=="" if not defined HAS_API_KEY_ARG (
    echo Warning: LLM_API_KEY environment variable is not set and --llm-api-key not provided
    echo Please set it as environment variable or pass --llm-api-key argument
)

:: Run the executable with all arguments
echo Starting MCP Integration with LLM Router in %1 mode...
echo.
dist\mcp-integration-with-LLM-router.exe %*

:: Check if the executable ran successfully
if errorlevel 1 (
    echo.
    echo Error: Application exited with error code %errorlevel%
    pause
    exit /b %errorlevel%
)

echo.
echo Application finished successfully.
pause
