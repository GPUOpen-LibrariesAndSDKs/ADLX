from typing import Any
import shutil
import os
from adlx_mcp_chatbot.logs.log import log_with_color
from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client
import asyncio
from contextlib import AsyncExitStack
from adlx_mcp_chatbot.servers.tool import Tool

CONNECTION_ERROR_KEYWORDS = ["closed", "connection", "broken", "pipe", "eof", "process", "terminated"]

class Server:
    """Manages MCP server connections and tool execution."""

    def __init__(self, name: str, config: dict[str, Any]) -> None:
        self.name: str = name
        self.config: dict[str, Any] = config
        self.stdio_context: Any | None = None
        self.session: ClientSession | None = None
        self._cleanup_lock: asyncio.Lock = asyncio.Lock()
        self.exit_stack: AsyncExitStack = AsyncExitStack()

    async def initialize(self) -> None:
        """Initialize the server connection."""
        command = (
            shutil.which("npx")
            if self.config["command"] == "npx"
            else self.config["command"]
        )
        if command is None:
            raise ValueError("The command must be a valid string and cannot be None.")
        command = os.path.join(os.path.dirname(__file__), command)
        
        server_params = StdioServerParameters(
            command=command,
            args=self.config["args"],
            env={**os.environ, **self.config["env"]}
            if self.config.get("env")
            else None,
        )
        try:
            stdio_transport = await self.exit_stack.enter_async_context(
                stdio_client(server_params)
            )
            read, write = stdio_transport
            session = await self.exit_stack.enter_async_context(
                ClientSession(read, write)
            )
            await session.initialize()
            self.session = session
        except Exception as e:
            log_with_color(f"Error initializing server {self.name}: {e}", "red")
            await self.cleanup()
            raise

    async def list_tools(self) -> list[Any]:
        """List available tools from the server.

        Returns:
            A list of available tools.

        Raises:
            RuntimeError: If the server is not initialized.
        """
        if not self.session:
            raise RuntimeError(f"Server {self.name} not initialized")

        try:
            tools_response = await self.session.list_tools()
            tools = []

            for item in tools_response:
                if isinstance(item, tuple) and item[0] == "tools":
                    tools.extend(
                        Tool(tool.name, tool.description, tool.inputSchema, tool.title)
                        for tool in item[1]
                    )

            return tools
        except Exception as e:
            error_msg = str(e)
            log_with_color(f"Error listing tools for server {self.name}: {error_msg}", "red")
            
            # Only mark session as invalid for specific connection-related errors
            if any(keyword in error_msg.lower() for keyword in CONNECTION_ERROR_KEYWORDS):
                log_with_color(f"Connection error detected, marking session as invalid for server {self.name}", "yellow")
                self.session = None
            
            raise

    async def execute_tool(
        self,
        tool_name: str,
        arguments: dict[str, Any],
        retries: int = 2,
        delay: float = 1.0,
    ) -> Any:
        """Execute a tool with retry mechanism.

        Args:
            tool_name: Name of the tool to execute.
            arguments: Tool arguments.
            retries: Number of retry attempts.
            delay: Delay between retries in seconds.

        Returns:
            Tool execution result.

        Raises:
            RuntimeError: If server is not initialized.
            Exception: If tool execution fails after all retries.
        """
        if not self.session:
            raise RuntimeError(f"Server {self.name} not initialized")

        attempt = 0
        while attempt < retries:
            try:
                log_with_color(f"Executing {tool_name}...", "blue")
                if self.session is None:
                    raise RuntimeError(f"Server {self.name} session is not available for tool execution")
                result = await self.session.call_tool(tool_name, arguments)
                
                # Add a small delay after successful execution to prevent connection issues
                await asyncio.sleep(0.1)
                
                return result

            except Exception as e:
                attempt += 1
                log_with_color(
                    f"Error executing tool: {e}. Attempt {attempt} of {retries}.", "yellow"
                )
                
                # If it's a connection-related error, mark session as invalid
                if any(keyword in str(e).lower() for keyword in CONNECTION_ERROR_KEYWORDS):
                    log_with_color(f"Connection error detected, marking session as invalid for server {self.name}", "yellow")
                    self.session = None
                
                if attempt < retries:
                    log_with_color(f"Retrying in {delay} seconds...", "yellow")
                    await asyncio.sleep(delay)
                else:
                    log_with_color("Max retries reached. Failing.", "red")
                    raise

    def is_healthy(self) -> bool:
        """Check if the server connection is healthy."""
        return self.session is not None

    async def health_check(self) -> bool:
        """Perform a health check by trying to list tools."""
        if not self.session:
            return False
        
        try:
            await self.list_tools()
            return True
        except Exception as e:
            log_with_color(f"Health check failed for server {self.name}: {e}", "yellow")
            return False

    async def cleanup(self) -> None:
        """Clean up server resources."""
        async with self._cleanup_lock:
            try:
                await self.exit_stack.aclose()
                self.exit_stack = AsyncExitStack()
                log_with_color(f"Server {self.name} cleaned up successfully.", "green")
                self.session = None
                self.stdio_context = None
            except Exception as e:
                self.exit_stack = AsyncExitStack()
                log_with_color(f"Error during cleanup of server {self.name}: {e}", "red")