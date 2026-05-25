# AMD Device Library eXtra — ADLX SDK

ADLX is a modern SDK designed to access features and functionality of AMD systems across Display, 3D Graphics, Performance Monitoring, GPU Tuning, and more. It is targeted at developers and partners building control and monitoring applications for AMD devices.

📖 Full documentation: [gpuopen.com/adlx](https://www.gpuopen.com/adlx)

---

## Key Features

- **Modern API design** — quality and reliability at the core
- **Multi-language support** — C, C++, C#, Java, Python
- **Driver compatible** — forward and backward compatible with AMD drivers
- **Global state synchronization** — consistent state across all callers
- **Broad feature coverage** — Display, 3D Graphics, Performance Monitoring, GPU Tuning, Power Tuning, and more
- **AI/LLM integration** — MCP servers for controlling AMD GPU settings via AI agents

---

## Repository Structure

```text
ADLX/
├── SDK/                  # Core ADLX interface headers and ADLXHelper wrappers (C / C++)
├── Samples/              # Code samples in C, C++, C#, Java, and Python
├── ADLXPybind/           # Python binding (.pyd) built with pybind11
├── MCPs/                 # MCP servers and client for AI agent integration
└── SDKDoc/               # SDK reference documentation
```

### SDK

The `SDK/` directory contains:

- **`SDK/Include/`** — ADLX interface headers (C and C++)
- **`SDK/ADLXHelper/Windows/C/`** — C helper for loading and initializing ADLX
- **`SDK/ADLXHelper/Windows/Cpp/`** — C++ helper for loading and initializing ADLX
- **`SDK/Platform/`** — Windows platform abstraction layer

### Samples

Code samples are organized by feature area. Each sample is available in multiple languages:

| Category | Description |
| --- | --- |
| 3DGraphics | Anti-aliasing, tessellation, FSR, AFMF, Radeon Boost, and more |
| Display | Resolution, color depth, refresh rate, FreeSync, custom resolutions |
| Desktop | Eyefinity multi-display configuration |
| GPUTuning | Auto/preset/manual GPU tuning |
| PerformanceMonitoring | FPS, GPU/CPU metrics, system info |
| PowerTuning | Power limit, TDP, fan control |
| MultiMedia | Video super resolution (VSR) |
| ReceivingEventsNotifications | Event and change notification callbacks |
| Generic | GPU enumeration, logging, stress test, service calls |
| I2C | I2C communication |
| VariableGraphicsMemory | Variable graphics memory (Smart Access Memory) |

### ADLXPybind

Python bindings for ADLX, exposing the full ADLX interface to Python via pybind11. Produces `adlx.pyd` and an installable wheel (`adlx-*.whl`).

### MCPs

MCP (Model Context Protocol) servers that expose AMD GPU controls as tools for AI agents and LLM applications.

| Component | Description |
| --- | --- |
| `Server/amd-3dsettings-mcp-server` | 3D graphics settings (RSR, AFMF, Anti-Lag, Chill, etc.) |
| `Server/amd-display-mcp-server` | Display settings (VSR, color, custom resolution) |
| `Server/amd-gputunings-mcp-server` | GPU tuning (auto/preset/manual, fan, power, VRAM) |
| `Server/amd-perfmonitoring-mcp-server` | GPU/system performance metrics |
| `Client/mcp-integration-with-LLM-router` | CLI and Streamlit chatbot client with LLM router |

---

## Requirements

### C / C++ Samples

| Item | Version |
| --- | --- |
| OS | Windows 10 (32/64-bit) or later |
| IDE | Visual Studio 2019 with C/C++ components |
| Build system | CMake 3.8+ (open via VS2019: File > Open > CMake) |
| AMD driver | ADLX-compatible AMD GPU driver |

### ADLXPybind (Python Binding)

| Item | Version |
| --- | --- |
| OS | Windows 11 (32/64-bit) |
| IDE | Visual Studio 2022 with C/C++ components |
| Python | 3.13 |
| Library | pybind11 |
| Environment variable | `PYHOME` pointing to Python 3.12 installation |

### MCPs

| Item | Version |
| --- | --- |
| OS | Windows 10 (64-bit) or later |
| Python | 3.13 |
| Package manager | [uv](https://github.com/astral-sh/uv) |
| AMD driver | ADLX-compatible AMD GPU driver |
| Python wheel | `adlx-1.0.0-py313-none-win_amd64.whl` (from ADLXPybind build) |

---

## Quick Start

### 1. C++ Sample

```bash
# Open in Visual Studio 2019 via File > Open > CMake
# Select Samples/CPP/CMakeLists.txt
# Build configuration: vs2019_Release_x64
```

### 2. Python via ADLXPybind

```bash
# Build the wheel (requires VS 2022 + Python 3.12 + pybind11)
cd ADLXPybind
# Open ADLXPybind.sln in Visual Studio 2022 and Rebuild
# Or build the wheel:
build_wheel.bat
pip install dist/adlx-*.whl
```

```python
import adlx
system, _ = adlx.helper.QueryFullVersion()
print(system)
```

### 3. MCP Servers (AI Agent Integration)

```bash
cd MCPs

# Start a server (example: 3D settings)
cd Server/amd-3dsettings-mcp-server
uv run server.py

# Or start the Streamlit chatbot client
cd Client/mcp-integration-with-LLM-router/adlx_mcp_chatbot
uv run streamlit run app.py
```

---

## License

ADLX SDK is distributed under the license included in [ADLX SDK License Agreement.pdf](ADLX%20SDK%20License%20Agreement.pdf) at the root of this repository.

## Attribution

- AMD, the AMD Arrow logo, Radeon, Crossfire, and combinations thereof are either registered trademarks or trademarks of Advanced Micro Devices, Inc. in the United States and/or other countries.
- Microsoft, DirectX, Visual Studio, and Windows are either registered trademarks or trademarks of Microsoft Corporation in the United States and/or other countries.
