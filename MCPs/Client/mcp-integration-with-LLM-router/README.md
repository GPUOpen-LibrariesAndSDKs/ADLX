# MCP Integration with LLM Router

A chatbot application that uses Large Language Models (LLM) to intelligently route user queries to appropriate Model Context Protocol (MCP) tool calls. This project demonstrates how to build an LLM-powered agent that can understand natural language requests and execute the corresponding MCP server tools.

## Overview

This project demonstrates a complete workflow for:
1. **LLM-Based Intent Recognition** - Use LLM to understand user queries and determine appropriate tool calls
2. **MCP Server Management** - Connect and manage multiple MCP servers
3. **Tool Execution** - Execute MCP tools based on LLM decisions
4. **Response Generation** - Transform tool results into natural language responses
5. **Multi-Interface Support** - CLI and Streamlit web UI

### Architecture

```
User Query → LLM (with Tools Context) → Tool Selection → MCP Tool Call → LLM Response
     ↓                ↓                      ↓                ↓              ↓
"Enable RSR"    Analyze Intent        JSON Tool Call    AMD Driver     Natural Reply
                + Available Tools     [{"tool":...}]    Execution
```

### Workflow Diagram

```
┌─────────────────────────────────────────────────────────────────────────────────┐
│                         MCP Integration with LLM Router                         │
├─────────────────────────────────────────────────────────────────────────────────┤
│                                                                                 │
│  ┌──────────┐    ┌─────────────────────────────────────────────────────────┐   │
│  │   User   │    │                    LLM Router                            │   │
│  │  Query   │───▶│  ┌─────────────┐   ┌─────────────┐   ┌──────────────┐  │   │
│  └──────────┘    │  │System Prompt│ + │Tools Schema │ → │ LLM Decision │  │   │
│                  │  │  (Context)  │   │(from MCPs)  │   │ (Tool Calls) │  │   │
│                  │  └─────────────┘   └─────────────┘   └──────┬───────┘  │   │
│                  └─────────────────────────────────────────────│──────────┘   │
│                                                                │               │
│                  ┌─────────────────────────────────────────────▼──────────┐   │
│                  │                  MCP Server Manager                     │   │
│                  │  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐       │   │
│                  │  │ 3D Settings │ │   Display   │ │ Performance │  ...  │   │
│                  │  │   Server    │ │   Server    │ │   Server    │       │   │
│                  │  └──────┬──────┘ └──────┬──────┘ └──────┬──────┘       │   │
│                  └─────────│───────────────│───────────────│──────────────┘   │
│                            │               │               │                   │
│                            ▼               ▼               ▼                   │
│                  ┌─────────────────────────────────────────────────────────┐   │
│                  │                    AMD ADLX Driver                       │   │
│                  └─────────────────────────────────────────────────────────┘   │
│                                                                                 │
└─────────────────────────────────────────────────────────────────────────────────┘
```

## Prerequisites

- Python 3.13
- [uv](https://docs.astral.sh/uv/) package manager (recommended) or pip
- [Lemonade](https://github.com/amd/lemonade) - AMD's local LLM inference server (provides OpenAI-compatible API)
- AMD GPU with ADLX-compatible drivers (for MCP server functionality)

## Project Structure

```
mcp-integration-with-LLM-router/
├── adlx_mcp_chatbot/
│   ├── main.py                    # Application entry point
│   ├── requirements.txt           # Python dependencies
│   ├── apps/
│   │   ├── cli_app.py             # CLI interface
│   │   ├── streamlit_app.py       # Streamlit web interface
│   │   └── chat_session.py        # Core chat session logic
│   ├── config/
│   │   ├── config.py              # Configuration management
│   │   ├── mcp_config.json        # MCP servers configuration
│   │   └── prompt.py              # System prompt template
│   ├── llm/
│   │   ├── __init__.py             # LLM module exports
│   │   ├── llm_base.py            # LLM client base class
│   │   └── llm_client.py          # OpenAI-compatible LLM client
│   ├── servers/
│   │   ├── server_manager.py      # MCP server connection manager
│   │   ├── tool.py                # Tool representation
│   │   └── *.exe                  # MCP server binaries
│   └── logs/
│       └── log.py                 # Logging utilities
├── build.bat                      # Build script for Windows executable
├── run.bat                        # Run script for built executable
├── setup.bat                      # Environment setup script
├── pyproject.toml                 # Project configuration
└── README.md
```

## Quick Start

### 1. Install Dependencies

```powershell
# Clone the repository
git clone <repository-url>
cd mcp-integration-with-LLM-router

# Option 1: Using uv (recommended)
uv sync

# Option 2: Using setup.bat
.\setup.bat

# Option 3: Using pip manually
python -m venv .venv
.\.venv\Scripts\activate
pip install -r adlx_mcp_chatbot/requirements.txt
```

### 2. Set Up Lemonade LLM Backend

This project uses [Lemonade](https://github.com/amd/lemonade) as the local LLM inference backend. Lemonade runs models on AMD GPUs and exposes an OpenAI-compatible API.

#### Install and Start Lemonade

```powershell
# Install Lemonade (see https://github.com/amd/lemonade for full instructions)
pip install lemonade

# Start the Lemonade server with a compatible model
# Important: Set --ctx-size to at least 8192 to fit the system prompt with tool descriptions
lemonade -i Qwen3.5-4B-GGUF load-model --device igpu serve --port 13305 --ctx-size 8192
```

#### Configure Environment Variables

```powershell
# Set LLM server URL (Lemonade's OpenAI-compatible endpoint)
$env:LLM_BASE_URL = "http://127.0.0.1:13305/api/v1"

# Set API key (use "lemonade" for local Lemonade server)
$env:LLM_API_KEY = "lemonade"
```

> **Note:** Ensure the `--ctx-size` is large enough (≥8192) to accommodate the system prompt which includes all MCP tool descriptions. If you see `exceed_context_size_error`, increase this value.

### 3. Configure MCP Servers

Edit `adlx_mcp_chatbot/config/mcp_config.json` to configure available MCP servers:

```json
{
  "mcpServers": {
    "amd-3dsettings-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-3dsettings-mcp-server.exe",
      "args": ["--enable_log"]
    },
    "amd-display-settings-mcp-server": {
      "transport": "stdio",
      "command": "../servers/amd-display-settings-mcp-server.exe",
      "args": ["--enable_log"]
    }
  }
}
```

### 4. Run the Application

#### CLI Mode

```powershell
# Using Python directly with Lemonade backend
python adlx_mcp_chatbot/main.py cli --llm-base-url http://127.0.0.1:13305/api/v1 --llm-api-key lemonade

# Or with environment variables set
python adlx_mcp_chatbot/main.py cli
```

#### Streamlit Web UI

```powershell
# Using Python directly with Lemonade backend
python adlx_mcp_chatbot/main.py streamlit --llm-base-url http://127.0.0.1:13305/api/v1 --llm-api-key lemonade

# Or run Streamlit directly
streamlit run adlx_mcp_chatbot/apps/streamlit_app.py
```

Open `http://localhost:8501` in your browser.

## Usage

### How LLM Router Works

1. **User Input**: User enters a natural language query like "Enable Radeon Super Resolution"

2. **Context Building**: The system builds a prompt containing:
   - System instructions for the LLM
   - Available tools schema (automatically collected from all MCP servers)
   - User's query

3. **LLM Decision**: The LLM analyzes the query and returns a JSON response:
   ```json
   [
     {
       "tool": "set_rsr_state",
       "arguments": {
         "state": 1
       }
     }
   ]
   ```

4. **Tool Execution**: The system:
   - Parses the JSON response
   - Finds the appropriate MCP server with the requested tool
   - Executes the tool with provided arguments

5. **Response Generation**: The LLM transforms the tool result into a natural language response

### Example Interaction

```
You: Enable RSR
   ↓
[LLM Analysis] User wants to enable Radeon Super Resolution
   ↓
[Tool Selection] {"tool": "set_rsr_state", "arguments": {"state": 1}}
   ↓
[MCP Execution] amd-3dsettings-mcp-server.exe → set_rsr_state(state=1)
   ↓
[Result] {"success": true, "message": "RSR enabled"}
   ↓
Assistant: Radeon Super Resolution has been successfully enabled.
```

### Supported Commands

The available commands depend on the MCP servers configured. With the default ADLX MCP servers:

| Category | Example Commands |
|----------|------------------|
| 3D Settings | "Enable RSR", "Get anti-aliasing mode", "Set tessellation to 64x" |
| Display | "Get display resolution", "Enable FreeSync" |
| Performance | "Get GPU temperature", "Show fan speed" |
| GPU Tuning | "Get GPU clock speed", "Set power limit" |

## Building Executable

Build a standalone Windows executable:

```powershell
# Run the build script
.\build.bat

# The executable will be created in the dist/ folder
.\run.bat cli --llm-api-key lemonade --llm-base-url http://127.0.0.1:13305/api/v1
```

## Configuration

### System Prompt

The system prompt in `adlx_mcp_chatbot/config/prompt.py` defines how the LLM should behave:

```python
SYSTEM_PROMPT = """
You are a helpful assistant with access to these tools:
{tools_description}

Your task is to find appropriate tools based on the user's question.
When you need to use tools, respond with JSON format:
[{"tool": "tool_name", "arguments": {...}}]
"""
```

### LLM Client Configuration

The LLM client uses OpenAI-compatible API. Modify `adlx_mcp_chatbot/llm/llm_client.py` for custom configurations:

```python
class LLMClient(BaseLLMClient):
    def __init__(self, url: str, api_key: str) -> None:
        self.client = openai.OpenAI(
            base_url=url,
            api_key=api_key
        )
```

## VS Code Integration

The project includes VS Code launch configurations in `.vscode/launch.json`:

| Configuration | Description |
|---------------|-------------|
| Debug simple chatbot mcp cli client | Run CLI with debugger |
| Debug simple chatbot mcp streamlit client | Run Streamlit with debugger |

## Extending the Project

### Adding New MCP Servers

1. Place your MCP server binary in `adlx_mcp_chatbot/servers/`
2. Add server configuration to `mcp_config.json`:
   ```json
   {
     "mcpServers": {
       "your-new-server": {
         "transport": "stdio",
         "command": "../servers/your-new-server.exe",
         "args": []
       }
     }
   }
   ```
3. Restart the application - tools will be automatically discovered

### Custom LLM Providers

Implement `BaseLLMClient` for custom LLM providers:

```python
from adlx_mcp_chatbot.llm.llm_base import BaseLLMClient

class CustomLLMClient(BaseLLMClient):
    def get_response(self, messages: List[Dict[str, str]]) -> str:
        # Your implementation here
        pass
```

## Troubleshooting

### Common Issues

**LLM server not responding:**
- Verify Lemonade is running (`http://127.0.0.1:13305/api/v1`)
- Check if the model is loaded (look for "Model loaded" in Lemonade output)
- Ensure `LLM_BASE_URL` and `LLM_API_KEY` are set correctly

**Context size exceeded (exceed_context_size_error):**
- The system prompt with all tool descriptions exceeds the server's context window
- Restart Lemonade with a larger `--ctx-size` (e.g., `--ctx-size 16384`)
- Or reduce the number of MCP servers in `mcp_config.json`

**MCP server connection failed:**
- Check if the MCP server executable exists
- Verify the path in `mcp_config.json`
- Check MCP server logs in `adlx_mcp_chatbot/servers/logs/`

**Tool not found:**
- Ensure the MCP server is properly initialized
- Check if the tool name matches exactly
- Restart the application to reinitialize servers

**Empty LLM responses:**
- Check LLM server health
- Verify the prompt format is compatible with your LLM
- Enable logging to debug the conversation

## Comparison with Semantic Router

| Feature | LLM Router | Semantic Router |
|---------|------------|-----------------|
| Intent Recognition | LLM-based reasoning | Embedding similarity |
| Latency | Higher (LLM inference) | Lower (vector search) |
| Flexibility | High (understands context) | Medium (pattern matching) |
| Setup Complexity | Simple (just LLM server) | Complex (fine-tuning, DB) |
| Accuracy | Depends on LLM quality | ~98% with fine-tuned model |

## License

MIT License - See LICENSE file for details.

## References

- [Model Context Protocol (MCP)](https://modelcontextprotocol.io/)
- [Lemonade - AMD Local LLM Server](https://github.com/amd/lemonade)
- [OpenAI API](https://platform.openai.com/docs/api-reference)
- [Streamlit](https://streamlit.io/)
- [AMD ADLX SDK](https://gpuopen.com/adlx/)
