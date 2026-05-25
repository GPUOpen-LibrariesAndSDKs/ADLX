@page page_sample_rust Rust Samples

<!--
# Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
This document describes how to build and run the ADLX Rust samples. The ADLX Rust samples demonstrate how to program with ADLX in a Rust application.

Unlike the C#, Java, and Python samples, the Rust samples do not require a separate C/C++ binding project. Rust binds to the ADLX C interface directly through FFI. The shared `amd-adlx` crate declares the required ADLX interfaces (vtables) and provides a small `AdlxHelper` loader that mirrors `SDK/ADLXHelper/Windows/C/ADLXHelper.c`.

<h2>Supported Operating Systems</h2>

Windows® 10 (32- and 64-bit versions) and up.

<h2>Build Tool</h2>

[Rust toolchain](https://www.rust-lang.org/tools/install) (`cargo` and `rustc`) with the MSVC toolchain on Windows.

<h2>Prerequisites</h2>

- <b>ADLX SDK</b> is installed.
- <b>Rust 1.70</b> (or newer) with the <b>x86_64-pc-windows-msvc</b> toolchain is installed.

<b>Note:</b> The ADLX library (`amdadlx64.dll` / `amdadlx32.dll`) is installed along with the AMD display driver and is loaded at runtime. No import library or header is needed to build the samples.

<h2>Project Layout</h2>

- `amd-adlx` &ndash; ADLX FFI bindings and the `AdlxHelper` runtime loader.
- `DisplayInfo` &ndash; Enumerates the displays and prints their information.
- `DisplayEvents` &ndash; Registers a listener and reports display list changes.
- `GPUInfo` &ndash; Enumerates the GPUs and prints their information.
- `GPUStressTest` &ndash; Queries GPU stress-test support via `IADLXGPU3`.
- `PerfGPUMetrics` &ndash; Reads current GPU performance metrics and their ranges.
- `Log` &ndash; Enables ADLX logging and captures log data via an application callback.
- `AntiLag` &ndash; Queries and toggles AMD Radeon Anti-Lag.
- `SmartAccessMemory` &ndash; Queries and toggles AMD SmartAccess Memory (SAM).
- `PerfSystemMetrics` &ndash; Reads current system performance metrics and their ranges.
- `PerfFPSMetrics` &ndash; Reads the current FPS metric.
- `ManualFanTuning` &ndash; Reads GPU manual fan tuning ranges and current settings.
- `DisplayFreeSync` &ndash; Queries AMD FreeSync support/state per display.
- `DisplayVSR` &ndash; Queries Virtual Super Resolution support/state per display.
- `DisplayGPUScaling` &ndash; Queries GPU scaling support/state per display.
- `DisplayIntegerScaling` &ndash; Queries integer scaling support/state per display.
- `EnhancedSync` &ndash; Queries AMD Radeon Enhanced Sync support/state.
- `Boost` &ndash; Queries AMD Radeon Boost support/state and resolution range.
- `Chill` &ndash; Queries AMD Radeon Chill support/state and FPS range.
- `ImageSharpening` &ndash; Queries AMD Radeon Image Sharpening support/state and sharpness.
- `RSR` &ndash; Queries AMD Radeon Super Resolution support/state and sharpness.
- `AnisotropicFiltering` &ndash; Queries anisotropic filtering support/state and level.
- `Tessellation` &ndash; Queries tessellation support, mode, and level.
- `ResetShaderCache` &ndash; Resets the GPU shader cache.
- `AntiAliasing` &ndash; Queries anti-aliasing mode, level, and method.
- `MorphologicAntiAliasing` &ndash; Queries Morphological Anti-Aliasing support/state.
- `WaitForVerticalRefresh` &ndash; Queries the Wait for Vertical Refresh (VSync) mode.
- `FRTC` &ndash; Queries Frame Rate Target Control support/state and FPS range.
- `DisplayHDCP` &ndash; Queries HDCP support/state per display.
- `DisplayScalingMode` &ndash; Queries the display scaling mode.
- `DisplayColorDepth` &ndash; Queries the display color depth and supported BPC values.
- `DisplayPixelFormat` &ndash; Queries the display pixel format and supported formats.
- `DisplayVariBright` &ndash; Queries AMD VariBright support/state and current mode per display.
- `Desktops` &ndash; Enumerates desktops and prints their orientation, size, type, and displays.
- `SmartShiftMax` &ndash; Queries AMD SmartShift Max support, bias mode, range, and current bias.
- `VideoSuperResolution` &ndash; Queries AMD Video Super Resolution support/state.
- `Videoupscale` &ndash; Queries AMD Video Upscale support/state and sharpness.
- `VariableGraphicsMemory` &ndash; Queries Variable Graphics Memory support and options.
- `ManualPowerTuning` &ndash; Reads GPU manual power tuning (power limit and TDC limit).
- `GPUPresetTuning` &ndash; Queries GPU preset tuning (power saver, quiet, balanced, turbo, rage).
- `DisplayBlanking` &ndash; Queries display blanking support/state per display.
- `AFMF` &ndash; Queries AMD Fluid Motion Frames support/state.
- `PrimaryAdapter` &ndash; Identifies the primary adapter (GPU driving the primary desktop).
- `InvalidObject` &ndash; Demonstrates `ADLX_INVALID_OBJECT` error handling.
- `DisplayDynamicRefreshRateControl` &ndash; Queries Dynamic Refresh Rate Control per display.
- `DisplayFreeSyncColorAccuracy` &ndash; Queries FreeSync Color Accuracy per display.
- `DisplayConnectivityExperience` &ndash; Queries HDMI/DP link connectivity details per display.
- `DisplayCustomColor` &ndash; Queries hue, saturation, brightness, contrast, and temperature per display.
- `DisplaySDRToHDR` &ndash; Queries display SDR-to-HDR support/state and adjustments.
- `DisplayCustomResolution` &ndash; Queries custom resolution support per display.
- `GPUAutoTuning` &ndash; Queries GPU automatic tuning (undervolt/overclock support and state).
- `I2C` &ndash; Reads the I2C interface version for a GPU.
- `ManualGraphicsTuning` &ndash; Reads GPU manual graphics tuning (min/max frequency, voltage).
- `ManualVRAMTuning` &ndash; Reads GPU manual VRAM tuning (memory timing, max VRAM frequency).
- `FidelityFXSuperResolution` &ndash; Queries AMD FidelityFX Super Resolution support/state.
- `FidelityFXFrameGenUpgrade` &ndash; Reads FidelityFX Frame Generation Upgrade state and available ratios.
- `DesktopsEvent` &ndash; Registers a listener and reports desktop configuration changes.
- `Display3DLUT` &ndash; Queries display 3D-LUT source color enhancement (SCE) presets.
- `3DSettingsEvent` &ndash; Registers a listener and reports 3D settings changes.
- `SmartShiftEco` &ndash; Queries AMD SmartShift Eco support/state and inactive reason.
- `DisplayGamut` &ndash; Queries supported gamut color spaces and white points per display.
- `DisplayGamma` &ndash; Queries display gamma current mode and re-gamma preset support.
- `Eyefinity` &ndash; Queries AMD Eyefinity support.
- `SyncGPUTuning` &ndash; Receives synchronous GPU tuning change notifications.
- `SyncPowerTuning` &ndash; Receives synchronous power tuning change notifications.
- `SyncMultimedia` &ndash; Receives synchronous multimedia change notifications.
- `SyncDisplayReceive` &ndash; Receives synchronous display change notifications.

<b>Note:</b> `amd-adlx` is structured as a standalone, publishable crate (see `amd-adlx/README.md`) so it can be reused outside these samples.

<h2>Smoke Tests</h2>
The `smoke-tests` crate builds every sample and runs each one with a closed standard
input, asserting that it exits cleanly (no panic, abort, or hang). The samples fail
gracefully when the ADLX runtime is unavailable, so the tests pass with or without an
AMD GPU present.

<ol>
    <li> Run all sample smoke tests: `cargo test -p smoke-tests`.</li>
    <li> Show each sample as it runs: `cargo test -p smoke-tests -- --nocapture`.</li>
</ol>

<h2>Build Instructions</h2>
<ol>
    <li> Open a terminal in `~ADLX\drivers\ADLX\Samples\rust`.</li>
    <li> Build all samples: `cargo build --release`.</li>
</ol>

<h2>Run Instructions</h2>
<ol>
    <li> Run the <b>DisplayInfo</b> sample: `cargo run --release --bin DisplayInfo`.</li>
    <li> Run the <b>DisplayEvents</b> sample: `cargo run --release --bin DisplayEvents`.</li>
    <li> Run the <b>GPUInfo</b> sample: `cargo run --release --bin GPUInfo`.</li>
    <li> Run the <b>GPUStressTest</b> sample: `cargo run --release --bin GPUStressTest`.</li>
    <li> Run the <b>PerfGPUMetrics</b> sample: `cargo run --release --bin PerfGPUMetrics`.</li>
    <li> Run the <b>Log</b> sample: `cargo run --release --bin Log`.</li>
    <li> Run the <b>AntiLag</b> sample: `cargo run --release --bin AntiLag`.</li>
    <li> Run the <b>SmartAccessMemory</b> sample: `cargo run --release --bin SmartAccessMemory`.</li>
    <li> Run the <b>PerfSystemMetrics</b> sample: `cargo run --release --bin PerfSystemMetrics`.</li>
    <li> Run the <b>PerfFPSMetrics</b> sample: `cargo run --release --bin PerfFPSMetrics`.</li>
    <li> Run the <b>ManualFanTuning</b> sample: `cargo run --release --bin ManualFanTuning`.</li>
    <li> Run the <b>DisplayFreeSync</b> sample: `cargo run --release --bin DisplayFreeSync`.</li>
    <li> Run the <b>DisplayVSR</b> sample: `cargo run --release --bin DisplayVSR`.</li>
    <li> Run the <b>DisplayGPUScaling</b> sample: `cargo run --release --bin DisplayGPUScaling`.</li>
    <li> Run the <b>DisplayIntegerScaling</b> sample: `cargo run --release --bin DisplayIntegerScaling`.</li>
    <li> Run the <b>EnhancedSync</b> sample: `cargo run --release --bin EnhancedSync`.</li>
    <li> Run the <b>Boost</b> sample: `cargo run --release --bin Boost`.</li>
    <li> Run the <b>Chill</b> sample: `cargo run --release --bin Chill`.</li>
    <li> Run the <b>ImageSharpening</b> sample: `cargo run --release --bin ImageSharpening`.</li>
    <li> Run the <b>RSR</b> sample: `cargo run --release --bin RSR`.</li>
    <li> Run the <b>AnisotropicFiltering</b> sample: `cargo run --release --bin AnisotropicFiltering`.</li>
    <li> Run the <b>Tessellation</b> sample: `cargo run --release --bin Tessellation`.</li>
    <li> Run the <b>ResetShaderCache</b> sample: `cargo run --release --bin ResetShaderCache`.</li>
    <li> Run the <b>AntiAliasing</b> sample: `cargo run --release --bin AntiAliasing`.</li>
    <li> Run the <b>MorphologicAntiAliasing</b> sample: `cargo run --release --bin MorphologicAntiAliasing`.</li>
    <li> Run the <b>WaitForVerticalRefresh</b> sample: `cargo run --release --bin WaitForVerticalRefresh`.</li>
    <li> Run the <b>FRTC</b> sample: `cargo run --release --bin FRTC`.</li>
    <li> Run the <b>DisplayHDCP</b> sample: `cargo run --release --bin DisplayHDCP`.</li>
    <li> Run the <b>DisplayScalingMode</b> sample: `cargo run --release --bin DisplayScalingMode`.</li>
    <li> Run the <b>DisplayColorDepth</b> sample: `cargo run --release --bin DisplayColorDepth`.</li>
    <li> Run the <b>DisplayPixelFormat</b> sample: `cargo run --release --bin DisplayPixelFormat`.</li>
    <li> Run the <b>DisplayVariBright</b> sample: `cargo run --release --bin DisplayVariBright`.</li>
    <li> Run the <b>Desktops</b> sample: `cargo run --release --bin Desktops`.</li>
    <li> Run the <b>SmartShiftMax</b> sample: `cargo run --release --bin SmartShiftMax`.</li>
    <li> Run the <b>VideoSuperResolution</b> sample: `cargo run --release --bin VideoSuperResolution`.</li>
    <li> Run the <b>Videoupscale</b> sample: `cargo run --release --bin Videoupscale`.</li>
    <li> Run the <b>VariableGraphicsMemory</b> sample: `cargo run --release --bin VariableGraphicsMemory`.</li>
    <li> Run the <b>ManualPowerTuning</b> sample: `cargo run --release --bin ManualPowerTuning`.</li>
    <li> Run the <b>GPUPresetTuning</b> sample: `cargo run --release --bin GPUPresetTuning`.</li>
    <li> Run the <b>DisplayBlanking</b> sample: `cargo run --release --bin DisplayBlanking`.</li>
    <li> Run the <b>AFMF</b> sample: `cargo run --release --bin AFMF`.</li>
    <li> Run the <b>PrimaryAdapter</b> sample: `cargo run --release --bin PrimaryAdapter`.</li>
    <li> Run the <b>InvalidObject</b> sample: `cargo run --release --bin InvalidObject`.</li>
    <li> Run the <b>DisplayDynamicRefreshRateControl</b> sample: `cargo run --release --bin DisplayDynamicRefreshRateControl`.</li>
    <li> Run the <b>DisplayFreeSyncColorAccuracy</b> sample: `cargo run --release --bin DisplayFreeSyncColorAccuracy`.</li>
    <li> Run the <b>DisplayConnectivityExperience</b> sample: `cargo run --release --bin DisplayConnectivityExperience`.</li>
    <li> Run the <b>DisplayCustomColor</b> sample: `cargo run --release --bin DisplayCustomColor`.</li>
    <li> Run the <b>DisplaySDRToHDR</b> sample: `cargo run --release --bin DisplaySDRToHDR`.</li>
    <li> Run the <b>DisplayCustomResolution</b> sample: `cargo run --release --bin DisplayCustomResolution`.</li>
    <li> Run the <b>GPUAutoTuning</b> sample: `cargo run --release --bin GPUAutoTuning`.</li>
    <li> Run the <b>I2C</b> sample: `cargo run --release --bin I2C`.</li>
    <li> Run the <b>ManualGraphicsTuning</b> sample: `cargo run --release --bin ManualGraphicsTuning`.</li>
    <li> Run the <b>ManualVRAMTuning</b> sample: `cargo run --release --bin ManualVRAMTuning`.</li>
    <li> Run the <b>FidelityFXSuperResolution</b> sample: `cargo run --release --bin FidelityFXSuperResolution`.</li>
    <li> Run the <b>FidelityFXFrameGenUpgrade</b> sample: `cargo run --release --bin FidelityFXFrameGenUpgrade`.</li>
    <li> Run the <b>DesktopsEvent</b> sample: `cargo run --release --bin DesktopsEvent`.</li>
    <li> Run the <b>Display3DLUT</b> sample: `cargo run --release --bin Display3DLUT`.</li>
    <li> Run the <b>3DSettingsEvent</b> sample: `cargo run --release --bin 3DSettingsEvent`.</li>
    <li> Run the <b>SmartShiftEco</b> sample: `cargo run --release --bin SmartShiftEco`.</li>
    <li> Run the <b>DisplayGamut</b> sample: `cargo run --release --bin DisplayGamut`.</li>
    <li> Run the <b>DisplayGamma</b> sample: `cargo run --release --bin DisplayGamma`.</li>
    <li> Run the <b>Eyefinity</b> sample: `cargo run --release --bin Eyefinity`.</li>
    <li> Run the <b>SyncGPUTuning</b> sample: `cargo run --release --bin SyncGPUTuning`.</li>
    <li> Run the <b>SyncPowerTuning</b> sample: `cargo run --release --bin SyncPowerTuning`.</li>
    <li> Run the <b>SyncMultimedia</b> sample: `cargo run --release --bin SyncMultimedia`.</li>
    <li> Run the <b>SyncDisplayReceive</b> sample: `cargo run --release --bin SyncDisplayReceive`.</li>
</ol>

<b>Note:</b> Build for the same architecture as the installed driver. On a 64-bit driver use the default `x86_64-pc-windows-msvc` target; for a 32-bit driver build with `--target i686-pc-windows-msvc`.
