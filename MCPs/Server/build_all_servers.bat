@echo off
setlocal enabledelayedexpansion

echo ========================================
echo Building All ADLX MCP Servers
echo ========================================
echo.

:: Set the root server directory
set SERVER_ROOT=%~dp0

:: Define the server directories
set SERVERS=amd-3dsettings-mcp-server amd-display-mcp-server amd-gputunings-mcp-server amd-perfmonitoring-mcp-server

:: Initialize counters
set SUCCESS_COUNT=0
set TOTAL_COUNT=0
set FAILED_SERVERS=

echo Starting build process for all servers...
echo.

:: Loop through each server directory
for %%s in (%SERVERS%) do (
    set /a TOTAL_COUNT+=1
    echo ----------------------------------------
    echo Building %%s
    echo ----------------------------------------
    
    :: Check if directory exists
    if exist "%SERVER_ROOT%%%s" (
        cd /d "%SERVER_ROOT%%%s"
        
        echo Running setup for %%s...
        call setup.bat
        if !ERRORLEVEL! equ 0 (
            echo Setup completed successfully for %%s
            
            echo Running build for %%s...
            call build.bat
            if !ERRORLEVEL! equ 0 (
                echo Build completed successfully for %%s
                set /a SUCCESS_COUNT+=1
            ) else (
                echo ERROR: Build failed for %%s
                set FAILED_SERVERS=!FAILED_SERVERS! %%s
            )
        ) else (
            echo ERROR: Setup failed for %%s
            set FAILED_SERVERS=!FAILED_SERVERS! %%s
        )
    ) else (
        echo ERROR: Directory %%s does not exist
        set FAILED_SERVERS=!FAILED_SERVERS! %%s
    )
    
    echo.
)

:: Return to the original directory
cd /d "%SERVER_ROOT%"

echo ========================================
echo Build Summary
echo ========================================
echo Total servers: %TOTAL_COUNT%
echo Successful builds: %SUCCESS_COUNT%
echo Failed builds: 
if defined FAILED_SERVERS (
    echo %FAILED_SERVERS%
) else (
    echo None
)
echo ========================================

if %SUCCESS_COUNT% equ %TOTAL_COUNT% (
    echo All servers built successfully!
    exit /b 0
) else (
    echo Some servers failed to build. Check the output above for details.
    exit /b 1
)
