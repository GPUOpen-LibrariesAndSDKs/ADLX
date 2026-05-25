from adlx_mcp_chatbot.config.config import Configuration
from adlx_mcp_chatbot.servers.server_manager import Server
from adlx_mcp_chatbot.llm.llm_client import LLMClient
from adlx_mcp_chatbot.apps.chat_session import ChatSession
from adlx_mcp_chatbot.logs.log import init_log_configuration

async def main(llm_api_key: str | None = None, llm_base_url: str | None = None) -> None:
    """Initialize and run the chat session.
    
    Args:
        llm_api_key: Optional LLM API key.
        llm_base_url: Optional LLM base URL.
    """
    try:
        # Initialize logging configuration
        # This will set up the logging based on the configuration file
        # and environment variables
        init_log_configuration()
        config = Configuration(llm_api_key, llm_base_url)
        server_config = config.load_config()
        servers = [
            Server(name, srv_config)
            for name, srv_config in server_config["mcpServers"].items()
        ]
        llm_client = LLMClient(config.llm_server_url, config.llm_api_key)
        chat_session = ChatSession(servers, llm_client)
        await chat_session.start()
    except Exception as e:
        print(f"An error occurred: {e}")
        raise
