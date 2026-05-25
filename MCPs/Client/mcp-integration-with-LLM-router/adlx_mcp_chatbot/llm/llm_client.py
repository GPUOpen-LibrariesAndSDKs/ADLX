import openai
from openai.types.chat import ChatCompletionMessageParam

from typing import List, Dict, Union, Sequence, cast
from .llm_base import BaseLLMClient

class LLMClient(BaseLLMClient):
    """Manages communication with the LLM provider."""

    def __init__(self, url: str, api_key: str) -> None:
        super().__init__()
        self.api_key: str = api_key
        self.client = openai.OpenAI(
            base_url=url,
            api_key=self.api_key
        )

    def _create_chat_messages(self, messages: Sequence[Union[ChatCompletionMessageParam, Dict[str, str]]]) -> List[ChatCompletionMessageParam]:
        result = []
        for msg in messages:
            if isinstance(msg, dict):
                role = msg.get("role")
                content = msg.get("content")
                if role and content and role in {"system", "user", "assistant"}:
                    result.append(cast(ChatCompletionMessageParam, msg))
                else:
                    raise ValueError(f"Invalid message: {msg}")
            else:
                result.append(msg)
        return result

    def remove_thinking_tags(self, text: str) -> str:
        """Remove QWen3 <think> and </think> tags from the text."""
        import re
        cleaned_text = re.sub(r'<think>.*?</think>', '', text, flags=re.DOTALL | re.IGNORECASE)
        # Clean up any extra whitespace that might be left
        cleaned_text = re.sub(r'\n\s*\n', '\n', cleaned_text).strip()
        return cleaned_text

    def get_response(self, messages: List[Dict[str, str]]) -> str:
        def _get_llm_response():
            completion = self.client.chat.completions.create(
                model="Qwen3.5-4B-GGUF",
                messages=self._create_chat_messages(messages),
                temperature=0
            )
            if not completion.choices:
                raise ValueError(f"LLM returned no choices. Full response: {completion}")
            content = completion.choices[0].message.content
            if content is None:
                raise ValueError("LLM returned empty content in choices[0].message.content")
            return self.remove_thinking_tags(content)
        
        return self._retry_with_backoff(_get_llm_response)