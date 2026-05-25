# AMD MCP Package

Model Context Protocol (MCP) servers and clients for managing AMD GPUs through natural language. This package exposes AMD ADLX driver features -- 3D graphics settings, display configuration, GPU tuning, performance monitoring, and diagnostics -- as MCP tools that can be called by LLM-based agents.

## Prerequisites

- Windows 10 (64-bit) or later
- Python 3.13
- [uv](https://docs.astral.sh/uv/) package manager
- AMD GPU with ADLX-compatible drivers installed
- ADLX Python wheel (`adlx-1.0.0-py313-none-win_amd64.whl`, built from `ADLXPybind`)

The ADLX wheel path is declared in each server's `pyproject.toml` under `[tool.uv.sources]` and is installed automatically when you run `setup.bat` or `uv sync` inside a server directory.

## Package Structure

```
AMD_MCP_Package/
├── Server/                                    # MCP servers (expose AMD driver features)
│   ├── pyproject.toml                         # Meta-package for all servers
│   ├── build_all_servers.bat                  # Build all servers into executables
│   ├── amd-3dsettings-mcp-server/             # 3D graphics settings
│   ├── amd-display-mcp-server/                # Display settings
│   ├── amd-gputunings-mcp-server/             # GPU tuning controls
│   └── amd-perfmonitoring-mcp-server/         # Performance metrics
│
└── Client/                                    # MCP clients (natural language interfaces)
    └── mcp-integration-with-LLM-router/       # LLM-based chatbot (CLI + Streamlit)
```

## MCP Servers

Four MCP servers expose AMD driver functionality as callable tools. Each server can run via **stdio** (default, for subprocess communication) or **streamable HTTP** (port 8000, for network access).

| Server | Description | Example Tools |
|--------|-------------|---------------|
| **amd-3dsettings-mcp-server** | 3D graphics settings | RSR, AFMF, Anti-Lag, Boost, Chill, Image Sharpening, Enhanced Sync, FRTC, VSync, Anti-Aliasing, Tessellation, Shader Cache, FidelityFX FSR, FidelityFX Frame Gen |
| **amd-display-mcp-server** | Display configuration | VSR, custom resolution, color (brightness, contrast, hue, saturation, temperature) |
| **amd-gputunings-mcp-server** | GPU tuning | Auto tuning, preset tuning (Quiet/Balanced/Rage), manual fan/graphics/power/VRAM tuning |
| **amd-perfmonitoring-mcp-server** | Performance monitoring | GPU usage/clocks/temperature/power/VRAM/voltage, system CPU/RAM, FPS |

### Building the Servers

```powershell
cd Server
.\build_all_servers.bat
```

This runs `setup.bat` and `build.bat` for each server, producing standalone `.exe` files under each server's `dist/` folder.

### Running a Server Individually

```powershell
# Install dependencies
cd Server\amd-3dsettings-mcp-server
.\setup.bat

# Run via Python
uv run amd-3dsettings-mcp-server --enable_log

# Or run the built executable
.\dist\amd-3dsettings-mcp-server.exe --enable_log
```

### Tool Discovery

Each server uses a `manifest.json` file in its `tools/` directory to declare available tools. Tools are dynamically loaded at startup via `importlib`, so adding new tools requires only a new Python module and a manifest entry.

## MCP Client

### LLM Router Client

Uses a Large Language Model to interpret user intent, select the appropriate tool, and generate natural language responses.

```
User Query --> LLM (with tool schemas) --> Tool Selection --> MCP Tool Call --> LLM Response
```

See `Client/mcp-integration-with-LLM-router/README.md` for full details, including how to use Lemonade, an OpenAI-compatible LLM server.

## MCP Server Configuration

The client uses `mcp_config.json` to define which servers to connect to:

```json
{
  "mcpServers": {
    "amd-3dsettings-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-3dsettings-mcp-server.exe",
      "args": ["--enable_log"]
    },
    "amd-display-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-display-mcp-server.exe",
      "args": ["--enable_log"]
    },
    "amd-perfmonitoring-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-perfmonitoring-mcp-server.exe",
      "args": ["--enable_log"]
    },
    "amd-gputunings-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-gputunings-mcp-server.exe",
      "args": ["--enable_log"]
    }
  }
}
```

## Debugging with MCP Inspector

[MCP Inspector](https://modelcontextprotocol.io/docs/tools/inspector) is an interactive browser-based tool for testing and debugging MCP servers directly — without needing a full AI client. It lets you list tools, invoke them with custom arguments, and inspect responses in real time.

### Requirements

- [Node.js](https://nodejs.org/) (for `npx`)

### Connect to a Server via stdio

When using stdio transport, MCP Inspector launches the server process for you — do **not** start the server separately.

**Using the Python source (recommended for development):**

```powershell
npx @modelcontextprotocol/inspector uv --directory Server\amd-3dsettings-mcp-server run amd-3dsettings-mcp-server
```

**Using a built executable:**

```powershell
npx @modelcontextprotocol/inspector Server\amd-3dsettings-mcp-server\dist\amd-3dsettings-mcp-server.exe
```

Substitute the server name/path for whichever server you want to inspect:

| Server          | Source directory                      | Executable                          |
|-----------------|---------------------------------------|-------------------------------------|
| 3D Settings     | `Server\amd-3dsettings-mcp-server`    | `amd-3dsettings-mcp-server.exe`     |
| Display         | `Server\amd-display-mcp-server`       | `amd-display-mcp-server.exe`        |
| GPU Tuning      | `Server\amd-gputunings-mcp-server`    | `amd-gputunings-mcp-server.exe`     |
| Perf Monitoring | `Server\amd-perfmonitoring-mcp-server`| `amd-perfmonitoring-mcp-server.exe` |

### Connect to a Server via Streamable HTTP

First start the server in HTTP mode:

```powershell
uv run amd-3dsettings-mcp-server --transport streamable-http
```

Then open MCP Inspector and enter the server URL:

```
http://localhost:8000/mcp
```

Select **Streamable HTTP** as the transport type in the Inspector UI.

### Using the Inspector UI

Once started, open **[http://localhost:6274](http://localhost:6274)** in your browser.

1. **Tools tab** — lists all tools exposed by the server; click any tool to expand its input schema.
2. **Run a tool** — fill in the arguments and click **Run Tool** to invoke it and see the raw JSON response.
3. **Resources / Prompts tabs** — browse any resources or prompt templates the server exposes.

### Using Config File (multiple servers)

Pass the existing `mcp_config.json` to inspect all servers at once:

```powershell
npx @modelcontextprotocol/inspector --config Client\mcp-integration-with-LLM-router\mcp_config.json --server amd-3dsettings-mcp-server
```

### CLI Mode (CI/CD)

Run a quick tool-list check without launching the browser UI:

```powershell
npx @modelcontextprotocol/inspector --cli uv --directory Server\amd-3dsettings-mcp-server run amd-3dsettings-mcp-server --method tools/list
```

### Troubleshooting

| Issue                          | Cause                          | Fix                                                       |
|--------------------------------|--------------------------------|-----------------------------------------------------------|
| Connection refused             | Port conflict                  | Check nothing else is using ports **6274** or **6277**    |
| Server disconnects immediately | Non-JSON output to stdout      | Ensure `--enable_log` writes logs to a file, not stdout   |
| Wrong transport error          | Mismatched transport selection | stdio for local commands; Streamable HTTP for URLs        |

## Example Interaction

```
You: Enable Radeon Super Resolution

[LLM Analysis] User wants to enable RSR
[Tool Selection] {"tool": "set_rsr_state", "arguments": {"state": 1}}
[MCP Execution] amd-3dsettings-mcp-server -> set_rsr_state(state=1)
[Result] {"success": true, "message": "RSR enabled"}
```
