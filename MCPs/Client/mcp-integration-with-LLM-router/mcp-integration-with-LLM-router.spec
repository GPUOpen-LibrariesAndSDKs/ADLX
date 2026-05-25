# -*- mode: python ; coding: utf-8 -*-
from PyInstaller.utils.hooks import collect_all

datas = [('./adlx_mcp_chatbot/config/mcp_config.json', './adlx_mcp_chatbot/config/'), ('./adlx_mcp_chatbot/servers/*.exe', './adlx_mcp_chatbot/servers/'), ('./adlx_mcp_chatbot/apps/streamlit_app.py', './adlx_mcp_chatbot/apps/')]
binaries = []
hiddenimports = ['adlx_mcp_chatbot.apps.cli_app', 'adlx_mcp_chatbot.apps.streamlit_app', 'adlx_mcp_chatbot.apps.chat_session', 'adlx_mcp_chatbot.config.config', 'adlx_mcp_chatbot.servers.server_manager', 'adlx_mcp_chatbot.servers.tool', 'adlx_mcp_chatbot.logs.log', 'adlx_mcp_chatbot.llm.llm_base', 'adlx_mcp_chatbot.llm.llm_client', 'adlx_mcp_chatbot.llm', 'langchain_openai', 'pydantic', 'openai', 'termcolor', 'mcp', 'mcp.client', 'mcp.client.session', 'mcp.client.stdio', 'mcp.types', 'streamlit', 'streamlit.web.cli', 'streamlit.web.bootstrap', 'streamlit.runtime', 'streamlit.runtime.scriptrunner', 'streamlit.runtime.caching', 'streamlit.components.v1', 'altair', 'plotly', 'pandas', 'numpy', 'tornado', 'click', 'watchdog', 'requests', 'uvicorn']
tmp_ret = collect_all('streamlit')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('altair')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('plotly')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('pandas')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('numpy')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('tornado')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('click')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]
tmp_ret = collect_all('watchdog')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]


a = Analysis(
    ['adlx_mcp_chatbot\\main.py'],
    pathex=['./'],
    binaries=binaries,
    datas=datas,
    hiddenimports=hiddenimports,
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)
pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,
    [],
    name='mcp-integration-with-LLM-router',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
