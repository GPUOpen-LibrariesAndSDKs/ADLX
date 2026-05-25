# -*- mode: python ; coding: utf-8 -*-
from PyInstaller.utils.hooks import collect_all

datas = [('./amd_perfmonitoring_mcp_server/tools/manifest.json', './tools/')]
binaries = []
hiddenimports = ['amd_perfmonitoring_mcp_server.utils.log', 'amd_perfmonitoring_mcp_server.utils.adlxwrapper', 'amd_perfmonitoring_mcp_server.tools.tool_gpu_metrics', 'amd_perfmonitoring_mcp_server.tools.tool_fps', 'amd_perfmonitoring_mcp_server.tools.tool_system_metrics']
tmp_ret = collect_all('adlx')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]


a = Analysis(
    ['amd_perfmonitoring_mcp_server\\server.py'],
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
    name='amd-performance-monitoring-mcp-server',
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
