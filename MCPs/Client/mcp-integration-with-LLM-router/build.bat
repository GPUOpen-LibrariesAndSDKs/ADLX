:: This batch file converts a Python script into a Windows executable.
@echo off
setlocal

:: Check if uv is available
where /q uv
if ERRORLEVEL 1 (
	echo uv is not installed or not in your PATH.
	echo Install it from https://docs.astral.sh/uv/getting-started/installation/
	exit /b 1
)

:: Verify the setup script has been run
set VENV=.venv
set DIST_DIR=dist
set CHATBOT_DIR=%DIST_DIR%
if exist %VENV% (
	:: Ensure chatbot subfolder exists
	if not exist "%CHATBOT_DIR%" mkdir "%CHATBOT_DIR%"

	uv run pyinstaller ^
		--onefile ^
		--name mcp-integration-with-LLM-router ^
		--add-data "./adlx_mcp_chatbot/config/mcp_config.json;./adlx_mcp_chatbot/config/" ^
		--add-data "./adlx_mcp_chatbot/servers/*.exe;./adlx_mcp_chatbot/servers/" ^
		--add-data "./adlx_mcp_chatbot/apps/streamlit_app.py;./adlx_mcp_chatbot/apps/" ^
		--collect-all streamlit ^
		--collect-all altair ^
		--collect-all plotly ^
		--collect-all pandas ^
		--collect-all numpy ^
		--collect-all tornado ^
		--collect-all click ^
		--collect-all watchdog ^
		--hidden-import="adlx_mcp_chatbot.apps.cli_app" ^
		--hidden-import="adlx_mcp_chatbot.apps.streamlit_app" ^
		--hidden-import="adlx_mcp_chatbot.apps.chat_session" ^
		--hidden-import="adlx_mcp_chatbot.config.config" ^
		--hidden-import="adlx_mcp_chatbot.servers.server_manager" ^
		--hidden-import="adlx_mcp_chatbot.servers.tool" ^
		--hidden-import="adlx_mcp_chatbot.logs.log" ^
		--hidden-import="adlx_mcp_chatbot.llm.llm_base" ^
		--hidden-import="adlx_mcp_chatbot.llm.llm_client" ^
		--hidden-import="adlx_mcp_chatbot.llm" ^
		--hidden-import="langchain_openai" ^
		--hidden-import="pydantic" ^
		--hidden-import="openai" ^
		--hidden-import="termcolor" ^
		--hidden-import="mcp" ^
		--hidden-import="mcp.client" ^
		--hidden-import="mcp.client.session" ^
		--hidden-import="mcp.client.stdio" ^
		--hidden-import="mcp.types" ^
		--hidden-import="streamlit" ^
		--hidden-import="streamlit.web.cli" ^
		--hidden-import="streamlit.web.bootstrap" ^
		--hidden-import="streamlit.runtime" ^
		--hidden-import="streamlit.runtime.scriptrunner" ^
		--hidden-import="streamlit.runtime.caching" ^
		--hidden-import="streamlit.components.v1" ^
		--hidden-import="altair" ^
		--hidden-import="plotly" ^
		--hidden-import="pandas" ^
		--hidden-import="numpy" ^
		--hidden-import="tornado" ^
		--hidden-import="click" ^
		--hidden-import="watchdog" ^
		--hidden-import="requests" ^
		--hidden-import="uvicorn" ^
		--distpath "%CHATBOT_DIR%" ^
		--paths "./" ^
		"./adlx_mcp_chatbot/main.py"

	echo.
	echo Build complete! MCP Integration with LLM Router executable can be found in the "%CHATBOT_DIR%" directory
	echo.
	echo - Use run.bat to run the executable
	echo.
	exit /b 0
) else (
	echo Please run setup.bat before attempting to build
	exit /b 1
)
