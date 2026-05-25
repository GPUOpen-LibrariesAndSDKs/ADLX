:: This batch file converts a Python script into a Windows executable.
@echo off
setlocal

where /q uv
if ERRORLEVEL 1 (
    echo uv is not installed or not found in PATH.
    echo Please install uv: https://docs.astral.sh/uv/getting-started/installation/
    exit /b 1
)

set DIST_DIR=dist
if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"

uv run pyinstaller ^
    --onefile ^
    --name amd-gpu-tunings-mcp-server ^
    --add-data "./amd_gputunings_mcp_server/tools/manifest.json:./tools/" ^
    --hidden-import="amd_gputunings_mcp_server.utils.log" ^
    --hidden-import="amd_gputunings_mcp_server.utils.adlxwrapper" ^
    --collect-all adlx ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_auto_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_manual_gfx_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_manual_vram_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_manual_fan_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_manual_power_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_preset_tuning" ^
    --hidden-import="amd_gputunings_mcp_server.tools.tool_tuning_services" ^
    --distpath "%DIST_DIR%" ^
    --paths "./" ^
    "./amd_gputunings_mcp_server/server.py"
if ERRORLEVEL 1 (
    echo Build failed
    exit /b 1
)

echo MCP can be found in the "%DIST_DIR%" directory
:: Copy output to Client/ADLX_Chatbot directory
if exist "%DIST_DIR%\amd-gpu-tunings-mcp-server.exe" (
    copy "%DIST_DIR%\amd-gpu-tunings-mcp-server.exe" "..\..\Client\mcp-integration-with-LLM-router\adlx_mcp_chatbot\servers\amd-gpu-tunings-mcp-server.exe"
    echo MCP executable copied to Client/ADLX_Chatbot directory
) else (
    echo MCP executable not found in the build directory
)

endlocal
exit /b 0
