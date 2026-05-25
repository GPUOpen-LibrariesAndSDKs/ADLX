# -*- mode: python ; coding: utf-8 -*-
from PyInstaller.utils.hooks import collect_all

datas = [('./amd_3dsettings_mcp_server/tools/manifest.json', './tools/')]
binaries = []
hiddenimports = ['amd_3dsettings_mcp_server.utils.log', 'amd_3dsettings_mcp_server.utils.adlxwrapper', 'amd_3dsettings_mcp_server.tools.tool_anisotropic_filtering', 'amd_3dsettings_mcp_server.tools.tool_anti_aliasing', 'amd_3dsettings_mcp_server.tools.tool_anti_lag', 'amd_3dsettings_mcp_server.tools.tool_boost', 'amd_3dsettings_mcp_server.tools.tool_chill', 'amd_3dsettings_mcp_server.tools.tool_enhanced_sync', 'amd_3dsettings_mcp_server.tools.tool_fidelityfx_frame_gen_upgrade', 'amd_3dsettings_mcp_server.tools.tool_fidelityfx_super_resolution', 'amd_3dsettings_mcp_server.tools.tool_frtc', 'amd_3dsettings_mcp_server.tools.tool_image_sharpening', 'amd_3dsettings_mcp_server.tools.tool_morphological_aa', 'amd_3dsettings_mcp_server.tools.tool_rsr', 'amd_3dsettings_mcp_server.tools.tool_shader_cache', 'amd_3dsettings_mcp_server.tools.tool_tessellation', 'amd_3dsettings_mcp_server.tools.tool_vertical_refresh', 'amd_3dsettings_mcp_server.tools.tool_afmf']
tmp_ret = collect_all('adlx')
datas += tmp_ret[0]; binaries += tmp_ret[1]; hiddenimports += tmp_ret[2]


a = Analysis(
    ['amd_3dsettings_mcp_server\\server.py'],
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
    name='amd-3dsettings-mcp-server',
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
