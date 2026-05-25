import importlib
import traceback
from typing import Dict, Optional, List
import logging
import json
import os
from functools import lru_cache
from mcp.shared.exceptions import McpError
from mcp.server import Server
from mcp.server.stdio import stdio_server
from mcp.server.streamable_http import StreamableHTTPServerTransport
from starlette.applications import Starlette
from starlette.routing import Mount

import mcp.types as types
from mcp.types import (
    ErrorData,
    TextContent,
    Tool,
    INVALID_PARAMS,
    INTERNAL_ERROR,
)
from amd_perfmonitoring_mcp_server.utils.log import log_with_color, init_log_configuration


@lru_cache(maxsize=1)
def load_tools_manifest() -> List[Dict]:
    """Load and cache the tools manifest."""
    tools_manifest = os.path.join(
        os.path.dirname(os.path.realpath(__file__)), "tools", "manifest.json"
    )
    try:
        if os.path.exists(tools_manifest):
            with open(tools_manifest, "r") as f:
                return json.load(f)["tools"]
        else:
            log_with_color(f"Tools manifest not found at {tools_manifest}", "yellow")
            return []
    except Exception as e:
        log_with_color(f"Error loading tools manifest: {e}", "red")
        return []


@lru_cache(maxsize=1)
def get_tools_map() -> Dict:
    """Get and cache the mapping of tool names to their configurations."""
    return {tool["name"]: tool for tool in load_tools_manifest()}



def create_error_response(error: Exception, name: str = "") -> McpError:
    """Create a standardized error response."""
    error_msg = str(error)
    
    return McpError(
        ErrorData(
            code=INTERNAL_ERROR,
            message=f"Error {'calling tool ' + name if name else ''}: {error_msg}"
        )
    )


async def serve(transport: str = "stdio") -> None:
    """Run the performance monitoring MCP server with optimized performance.
    
    Args:
        transport: Communication transport mode - either 'stdio' or 'streamable_http'
    """
    server = Server("mcp-performance-monitoring")

    @server.list_tools()
    async def list_tools() -> List[Tool]:
        """List available tools with caching."""
        return [
            types.Tool(
                name=tool["name"],
                description=tool["description"],
                inputSchema=tool.get("inputSchema", {}),
            )
            for tool in load_tools_manifest()
        ]

    @server.call_tool()
    async def call_tool(name: str, arguments: Dict) -> List[TextContent]:
        """Call a tool with improved error handling and logging."""
        tools_map = get_tools_map()

        if name not in tools_map:
            raise create_error_response(ValueError(f"Tool {name} not found"))

        try:
            # Import tool module
            tool_info = tools_map[name]
            module_path = f"tools.{tool_info['tool']}"

            log_with_color(f"Calling tool {name} with arguments: {arguments}", "blue")

            try:
                tool_module = importlib.import_module(module_path)
                tool_function = getattr(tool_module, name)
            except (ImportError, AttributeError) as e:
                raise create_error_response(
                    ImportError(f"Failed to import tool {name}: {str(e)}"), name
                )

            if not callable(tool_function):
                raise create_error_response(
                    ValueError(f"Tool {name} is not callable"), name
                )

            # Call the tool function
            response = tool_function(**arguments)
            return [types.TextContent(type="text", text=str(response))]

        except Exception as e:
            log_with_color(f"Error in tool {name}: {e}", "red")
            log_with_color(traceback.format_exc(), "red")
            raise create_error_response(e, name)

    options = server.create_initialization_options()
    
    if transport == "stdio":
        async with stdio_server() as (read_stream, write_stream):
            await server.run(read_stream, write_stream, options, raise_exceptions=True)
    elif transport == "streamable_http":
        # Create StreamableHTTP transport
        transport_instance = StreamableHTTPServerTransport(
            mcp_session_id=None,
            is_json_response_enabled=False
        )
        
        # Create Starlette app - mount the transport as an ASGI app
        app = Starlette(
            routes=[
                Mount("/mcp", app=transport_instance.handle_request),
            ]
        )
        
        # Run server with transport
        async with transport_instance.connect() as (read_stream, write_stream):
            import uvicorn
            import asyncio
            config = uvicorn.Config(app, host="127.0.0.1", port=8000, log_level="info")
            server_instance = uvicorn.Server(config)

            # Run both the MCP server and HTTP server concurrently
            await asyncio.gather(
                server.run(read_stream, write_stream, options, raise_exceptions=True),
                server_instance.serve()
            )
    else:
        raise ValueError(f"Unsupported transport mode: {transport}")


def main():
    """MCP AMD performance monitoring Server entry point"""
    import argparse
    import asyncio

    parser = argparse.ArgumentParser(
        description="Give a model the ability to monitor AMD performance metrics.",
    )
    parser.add_argument("--enable_log", default=False, action="store_true", help="Enable logging")
    parser.add_argument(
        "--transport",
        type=str,
        choices=["stdio", "streamable_http"],
        default="stdio",
        help="Transport mode: stdio (default) or streamable_http (bidirectional HTTP streaming)"
    )
    args = parser.parse_args()

    if args.enable_log:
        init_log_configuration()
        log_with_color("Logging enabled", "green")
    
    if args.transport == "streamable_http":
        log_with_color("Starting MCP server with Streamable HTTP transport on http://127.0.0.1:8000/mcp", "green")

    try:
        asyncio.run(serve(transport=args.transport))
    except KeyboardInterrupt:
        log_with_color("Server shutting down...", "yellow")
    except Exception as e:
        log_with_color(f"Server error: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        raise


if __name__ == "__main__":
    main()
