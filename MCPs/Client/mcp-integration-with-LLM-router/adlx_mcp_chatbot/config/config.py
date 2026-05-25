import os
import json
from typing import Any

class Configuration:
    """Manages configuration and environment variables for the MCP client."""

    def __init__(self, llm_api_key: str | None = None, llm_base_url: str | None = None) -> None:
        """Initialize configuration with optional parameters.
        
        Args:
            llm_api_key: Optional API key. If not provided, will use environment variable.
            llm_base_url: Optional base URL. If not provided, will use environment variable.
        """
        self._llm_api_key = llm_api_key
        self._llm_base_url = llm_base_url


    @staticmethod
    def load_config() -> dict[str, Any]:
        """Load server configuration from JSON file.

        Args:
            file_path: Path to the JSON configuration file.

        Returns:
            Dict containing server configuration.

        Raises:
            FileNotFoundError: If configuration file doesn't exist.
            JSONDecodeError: If configuration file is invalid JSON.
        """
        config_path = os.path.join(os.path.dirname(__file__), "mcp_config.json")
        with open(config_path, "r") as f:
            return json.load(f)

    @property
    def llm_api_key(self) -> str:
        """Get the LLM API key.

        Returns:
            The API key as a string.

        Raises:
            ValueError: If the API key is not found in environment variables or constructor.
        """
        api_key = self._llm_api_key or os.getenv("LLM_API_KEY")
        if not api_key:
            raise ValueError("LLM_API_KEY not found in environment variables or arguments")
        return api_key
    
    @property
    def llm_server_url(self) -> str:
        """Get the LLM server base URL.

        Returns:
            The LLM server base URL as a string.

        Raises:
            ValueError: If the LLM server base URL is not found in environment variables or constructor.
        """
        url = self._llm_base_url or os.getenv("LLM_BASE_URL")
        if not url:
            raise ValueError("LLM_BASE_URL not found in environment variables or arguments")
        return url