import time
from adlx_mcp_chatbot.servers.server_manager import Server, CONNECTION_ERROR_KEYWORDS
from adlx_mcp_chatbot.llm.llm_base import BaseLLMClient
from adlx_mcp_chatbot.logs.log import log_with_color
from adlx_mcp_chatbot.config.prompt import SYSTEM_PROMPT

MAX_CHAT_HISTORY = 50

class ChatSession:
    """Orchestrates the interaction between user, LLM, and tools."""

    def __init__(self, servers: list[Server], llm_client: BaseLLMClient) -> None:
        self.servers: list[Server] = servers
        self.llm_client: BaseLLMClient = llm_client
        self.chat_messages: list[dict[str, str]] = []

    async def initialize_servers(self) -> None:
        """Initialize all servers."""
        for server in self.servers:
            try:
                await server.initialize()
                log_with_color(f"Server {server.name} initialized successfully.", "green")
            except Exception as e:
                await self.cleanup_servers()
                raise

    async def cleanup_servers(self) -> None:
        """Clean up all servers properly."""
        for server in reversed(self.servers):
            try:
                await server.cleanup()
            except Exception as e:
                log_with_color(f"Warning during final cleanup: {e}", "yellow")

    async def ensure_servers_healthy(self) -> None:
        """Ensure all servers are healthy and reinitialize if needed."""
        for server in self.servers:
            if not server.session or not await server.health_check():
                try:
                    log_with_color(f"Reinitializing server {server.name}...", "yellow")
                    await server.initialize()
                    log_with_color(f"Server {server.name} reinitialized successfully.", "green")
                except Exception as e:
                    log_with_color(f"Failed to reinitialize server {server.name}: {e}", "red")

    async def force_reinitialize_servers(self) -> None:
        """Force reinitialize all servers regardless of their current state."""
        log_with_color("Force reinitializing all servers...", "yellow")
        for server in self.servers:
            try:
                # Clean up existing session first
                if server.session:
                    await server.cleanup()
                
                # Reinitialize
                await server.initialize()
                log_with_color(f"Server {server.name} force reinitialized successfully.", "green")
            except Exception as e:
                log_with_color(f"Failed to force reinitialize server {server.name}: {e}", "red")

    async def init_messages(self) -> None:
        """Clear the chat messages."""
        self.chat_messages = []
        system_message = await self.get_system_message()
        await self.update_chat_messages("system", system_message)
        log_with_color("Initialize Chat history.", "yellow")

    async def cleanup_messages(self) -> None:
        """Clear the chat messages."""
        self.chat_messages = self.chat_messages[0:1]  # Keep only the system message
        log_with_color("Chat history cleaned up, only system message remains.", "yellow")
    
    async def update_chat_messages(self, role: str, content: str) -> None:
        """Update the chat messages with a new message."""
        self.chat_messages.append({"role": role, "content": content})
        # Keep chat history bounded to prevent exceeding LLM context window
        # Always preserve the system message (index 0)
        if len(self.chat_messages) > MAX_CHAT_HISTORY:
            self.chat_messages = [self.chat_messages[0]] + self.chat_messages[-(MAX_CHAT_HISTORY - 1):]


    async def process_llm_response(self, llm_response: str) -> str:
        """Process the LLM response and execute tools if needed.

        Args:
            llm_response: The response from the LLM.

        Returns:
            The result of tool execution or the original response.
        """
        import json

        try:
            tool_calls = json.loads(llm_response)
            if not isinstance(tool_calls, list):
                log_with_color("Invalid tool call format, expected a list.", "red")
                return llm_response

            tool_execution_results = []
            for tool_call in tool_calls:
                if "tool" in tool_call and "arguments" in tool_call:
                    log_with_color(f"Executing tool: {tool_call['tool']}", "blue")
                    log_with_color(f"With arguments: {tool_call['arguments']}", "blue")

                    tool_found = False
                    for server in self.servers:
                        try:
                            # Check if server session is still valid
                            if not server.session:
                                log_with_color(f"Server {server.name} session is not available, skipping...", "yellow")
                                continue
                                
                            tools = await server.list_tools()
                            if any(tool.name == tool_call["tool"] for tool in tools):
                                tool_found = True
                                try:
                                    result = await server.execute_tool(
                                        tool_call["tool"], tool_call["arguments"]
                                    )

                                    if isinstance(result, dict) and "progress" in result:
                                        progress = result["progress"]
                                        total = result["total"]
                                        percentage = (progress / total) * 100
                                        log_with_color(
                                            f"Progress: {progress}/{total} ({percentage:.1f}%)", "green"
                                        )

                                    tool_execution_results.append(f"Tool {tool_call['tool']} execution result: {result}")
                                    break  # Tool found and executed successfully, break out of server loop
                                except Exception as e:
                                    error_msg = f"Error executing tool on server {server.name}: {str(e)}"
                                    log_with_color(error_msg, "red")
                                    # If execution failed, try to reinitialize the server
                                    if any(keyword in str(e).lower() for keyword in CONNECTION_ERROR_KEYWORDS):
                                        log_with_color(f"Connection error detected, will reinitialize server {server.name}", "yellow")
                                        server.session = None
                                    continue
                        except Exception as e:
                            log_with_color(f"Error checking tools on server {server.name}: {str(e)}", "yellow")
                            # If listing tools failed, try to reinitialize the server
                            if any(keyword in str(e).lower() for keyword in CONNECTION_ERROR_KEYWORDS):
                                log_with_color(f"Connection error detected, will reinitialize server {server.name}", "yellow")
                                server.session = None
                            continue
                    
                    if not tool_found:
                        # Try to reinitialize all servers and retry once
                        log_with_color(f"Tool {tool_call['tool']} not found, attempting server reinitialization...", "yellow")
                        await self.ensure_servers_healthy()
                        
                        # Retry finding the tool after reinitialization
                        for server in self.servers:
                            try:
                                if not server.session:
                                    continue
                                    
                                tools = await server.list_tools()
                                if any(tool.name == tool_call["tool"] for tool in tools):
                                    tool_found = True
                                    try:
                                        result = await server.execute_tool(
                                            tool_call["tool"], tool_call["arguments"]
                                        )
                                        tool_execution_results.append(f"Tool {tool_call['tool']} execution result: {result}")
                                        break
                                    except Exception as e:
                                        error_msg = f"Error executing tool on server {server.name} after reinit: {str(e)}"
                                        log_with_color(error_msg, "red")
                                        continue
                            except Exception as e:
                                log_with_color(f"Error checking tools on server {server.name} after reinit: {str(e)}", "yellow")
                                continue
                    
                    if not tool_found:
                        error_msg = f"No server found with tool: {tool_call['tool']}"
                        log_with_color(error_msg, "red")
                        tool_execution_results.append(error_msg)

            return "\n".join(tool_execution_results) if tool_execution_results else "No tools were executed."
        except json.JSONDecodeError:
            # Not a tool call — LLM responded with plain text
            return llm_response
        except Exception as e:
            log_with_color(f"Error processing LLM response: {e}", "red")
            return llm_response

    async def get_system_message(self) -> str:
        """Generate the system message for the LLM."""
        # can be configured by external file to control the exposed tools
        all_tools = []
        for server in self.servers:
            tools = await server.list_tools()
            all_tools.extend(tools)

        tools_info = "\n".join([tool.format_for_llm() for tool in all_tools])
        system_message = SYSTEM_PROMPT.format(tools_description=tools_info)

        return system_message

    async def generate_response(self, user_input: str) -> str:
        """
        Generate a response from the LLM based on user input and chat history.
        """
        # Ensure servers are healthy before processing
        await self.ensure_servers_healthy()
        
        await self.update_chat_messages("user", user_input)

        start_time = time.time()
        llm_response = self.llm_client.get_response(self.chat_messages)
        end_time = time.time()
        log_with_color(f"Assistant Response for finding tools (takes {end_time - start_time:.2f} seconds): {llm_response}")

        start_time = time.time()
        result = await self.process_llm_response(llm_response)
        end_time = time.time()
        log_with_color(f"Execute tools takes {end_time - start_time:.2f} seconds, result: {result}")


        if result != llm_response:
            await self.update_chat_messages("assistant", llm_response)
            await self.update_chat_messages("user", f"[Tool Result]: {result}")

            start_time = time.time()
            final_response = self.llm_client.get_response(self.chat_messages)
            end_time = time.time()
            log_with_color(f"Final response (takes {end_time - start_time:.2f} seconds): {final_response}", "blue")
            await self.update_chat_messages("assistant", final_response)
            return final_response
        else:
            await self.update_chat_messages("assistant", llm_response)
            return llm_response

    async def start(self) -> None:
        """Main chat session handler."""
        try:
            await self.initialize_servers()
            await self.init_messages()

            while True:
                try:
                    user_input = input("You: ").strip()
                    if user_input.lower() in ["quit", "exit"]:
                        log_with_color("\nExiting...", "yellow")
                        break

                    if user_input.lower() in ["clear", "clean"]:
                        log_with_color("Chat history cleared.", "yellow")
                        await self.cleanup_messages()
                        continue

                    response = await self.generate_response(user_input)

                except KeyboardInterrupt:
                    log_with_color("\nExiting...", "yellow")
                    break

        finally:
            await self.cleanup_servers()