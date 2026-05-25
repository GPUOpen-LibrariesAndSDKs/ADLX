from abc import ABC, abstractmethod
from typing import List, Dict
from adlx_mcp_chatbot.logs.log import log_with_color


class BaseLLMClient(ABC):
    """Base class for LLM clients providing common interface and functionality."""
    
    def __init__(self) -> None:
        self.max_retries = 10
        
    @abstractmethod
    def get_response(self, messages: List[Dict[str, str]]) -> str:
        """
        Get a response from the LLM provider.
        
        Args:
            messages: List of message dictionaries with 'role' and 'content' keys
            
        Returns:
            str: The LLM response
        """
        pass
    
    def _retry_with_backoff(self, func, *args, **kwargs) -> str:
        """
        Common retry logic for LLM calls.
        
        Args:
            func: The function to retry
            *args: Arguments for the function
            **kwargs: Keyword arguments for the function
            
        Returns:
            str: The response from the function
        """
        response = ""
        count = 0
        
        while count < self.max_retries:
            count += 1
            try:
                response = func(*args, **kwargs)
                if len(response) > 0:
                    break
            except Exception as e:
                error_message = f"Error getting LLM response (attempt {count}): {str(e)}"
                log_with_color(error_message, color="red")
                if count == self.max_retries:
                    log_with_color(f"Max retries ({self.max_retries}) reached, returning empty response", color="red")
                    break
                    
        return response
