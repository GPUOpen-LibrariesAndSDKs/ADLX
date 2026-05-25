import asyncio
import html
import streamlit as st
import time
from adlx_mcp_chatbot.config.config import Configuration
from adlx_mcp_chatbot.servers.server_manager import Server
from adlx_mcp_chatbot.llm.llm_client import LLMClient
from adlx_mcp_chatbot.logs.log import init_log_configuration, log_with_color
from adlx_mcp_chatbot.apps.chat_session import ChatSession

class StreamlitChatSession:
    """Streamlit-specific chat session handler."""
    
    def __init__(self, llm_api_key: str | None = None, llm_base_url: str | None = None):
        self.chat_session = None
        self.initialized = False
        self.llm_api_key = llm_api_key
        self.llm_base_url = llm_base_url
    
    async def initialize(self):
        """Initialize the chat session."""
        if not self.initialized:
            init_log_configuration()
            config = Configuration(self.llm_api_key, self.llm_base_url)
            server_config = config.load_config()
            servers = [
                Server(name, srv_config)
                for name, srv_config in server_config["mcpServers"].items()
            ]
            llm_client = LLMClient(config.llm_server_url, config.llm_api_key)
            self.chat_session = ChatSession(servers, llm_client)
            
            # Initialize servers and system message
            await self.chat_session.initialize_servers()
            await self.chat_session.init_messages()        
            self.initialized = True
    
    async def get_response(self, user_input: str) -> str:
        """Get response from the chat session."""
        # Note: initialization is now handled in handle_user_input()
        if self.chat_session is None:
            raise RuntimeError("Chat session is not initialized.")
        return await self.chat_session.generate_response(user_input)
    
    async def clear_history(self):
        """Clear chat history."""
        if self.chat_session:
            await self.chat_session.cleanup_messages()
    
    async def cleanup(self):
        """Clean up resources."""
        if self.chat_session:
            await self.chat_session.cleanup_servers()

def initialize_session_state():
    """Initialize Streamlit session state."""
    if "messages" not in st.session_state:
        st.session_state.messages = []
    if "chat_session" not in st.session_state:
        st.session_state.chat_session = StreamlitChatSession()
    if "initialized" not in st.session_state:
        st.session_state.initialized = False
    if "tools_by_server" not in st.session_state:
        st.session_state.tools_by_server = {}
    if "show_tools" not in st.session_state:
        st.session_state.show_tools = False
    if "expanded_servers" not in st.session_state:
        st.session_state.expanded_servers = set()
        
async def handle_user_input(user_input: str):
    """Handle user input and get response."""
    # Initialize chat session if not already done
    if not st.session_state.initialized:
        with st.spinner("Initializing chat session..."):
            await st.session_state.chat_session.initialize()
            st.session_state.initialized = True
    
    # Add user message to chat history
    st.session_state.messages.append({"role": "user", "content": user_input})
    
    # Display user message on the right with chat bubble styling and avatar
    safe_input = html.escape(user_input)
    st.markdown(
        f"""
        <div style="display: flex; justify-content: flex-end; align-items: flex-end; margin: 14px 0;">
            <div class="chat-bubble" style="background: linear-gradient(90deg, #007acc 0%, #4CAF50 100%); color: white; padding: 16px 22px; border-radius: 22px 22px 10px 22px; max-width: 70%; word-wrap: break-word; margin-right: 12px; font-size: 1.12em;">
                {safe_input}
            </div>
            <div style="width: 42px; height: 42px; background: #007acc; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                👤
            </div>
        </div>
        """,
        unsafe_allow_html=True
    )
    
    # Get and display assistant response on the left with chat bubble styling
    with st.spinner("Thinking..."):
        try:
            response = html.escape(await st.session_state.chat_session.get_response(user_input))
            st.markdown(
                f"""
                <div style="display: flex; justify-content: flex-start; align-items: flex-end; margin: 14px 0;">
                    <div style="width: 42px; height: 42px; background: #4CAF50; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; margin-right: 12px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                        🤖
                    </div>
                    <div class="chat-bubble" style="background: linear-gradient(90deg, #f0f0f0 0%, #e3f2fd 100%); color: #333; padding: 16px 22px; border-radius: 22px 22px 22px 10px; max-width: 70%; word-wrap: break-word; font-size: 1.12em;">
                        {response}
                    </div>
                </div>
                """,
                unsafe_allow_html=True
            )
            st.session_state.messages.append({"role": "assistant", "content": response})
        except Exception as e:
            error_msg = html.escape(f"Error: {str(e)}")
            st.markdown(
                f"""
                <div style="display: flex; justify-content: flex-start; align-items: flex-end; margin: 14px 0;">
                    <div style="width: 42px; height: 42px; background: #f44336; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; margin-right: 12px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                        ⚠️
                    </div>
                    <div class="chat-bubble" style="background: linear-gradient(90deg, #ffebee 0%, #ffcdd2 100%); color: #c62828; padding: 16px 22px; border-radius: 22px 22px 22px 10px; max-width: 70%; word-wrap: break-word; border: 1px solid #ef5350; font-size: 1.12em;">
                        {error_msg}
                    </div>
                </div>
                """,
                unsafe_allow_html=True
            )
            st.session_state.messages.append({"role": "assistant", "content": error_msg})

async def show_available_tools():
    """Show all available tools for each server."""
    # Initialize chat session if not already done
    if not st.session_state.initialized:
        with st.spinner("Initializing chat session..."):
            await st.session_state.chat_session.initialize()
            st.session_state.initialized = True
    
    # Get tools from all servers and organize by server
    tools_by_server = {}
    
    try:
        chat_session = st.session_state.chat_session.chat_session
        if chat_session and chat_session.servers:
            # Ensure servers are healthy
            await chat_session.ensure_servers_healthy()
            
            for server in chat_session.servers:
                try:
                    tools = await server.list_tools()
                    server_tools = []
                    
                    if tools:
                        for tool in tools:
                            tool_info = {
                                "name": tool.name,
                                "description": getattr(tool, 'description', ''),
                                "input_schema": getattr(tool, 'input_schema', '')
                            }
                            server_tools.append(tool_info)
                    
                    tools_by_server[server.name] = {
                        "tools": server_tools,
                        "error": None
                    }
                        
                except Exception as e:
                    tools_by_server[server.name] = {
                        "tools": [],
                        "error": str(e)
                    }
        else:
            # No servers initialized
            pass
            
    except Exception as e:
        # General error - will be handled in the UI
        pass
    
    # Store the tools by server in session state
    st.session_state.tools_by_server = tools_by_server

def main():
    """Main application."""
    st.set_page_config(
        page_title="MCP Simple Chatbot",
        page_icon="🤖",
        layout="wide",
        initial_sidebar_state="expanded"
    )

    # Initialize session state
    initialize_session_state()

    # Sidebar
    with st.sidebar:
        st.title("🤖 ADLX MCP Chatbot")
        st.markdown("---")
        
        st.markdown("""
        <div style="background: linear-gradient(90deg, #007acc 0%, #4CAF50 100%); border-radius: 12px; padding: 18px 20px; margin-bottom: 10px; box-shadow: 0 2px 8px rgba(0,0,0,0.07);">
            <h3 style="color: #fff; margin-top: 0; margin-bottom: 12px; font-size: 1.3rem; font-weight: 700; letter-spacing: 0.5px;">✨ How to Use</h3>
            <ul style="color: #f0f0f0; font-size: 1.08rem; margin-left: 0; padding-left: 18px;">
                <li style="margin-bottom: 8px;">Type your message in the chat input below <span style="font-size:1.1em;">💬</span></li>
                <li style="margin-bottom: 8px;">The chatbot can access AMD tools for:</li>
                <ul style="margin-left: 0; padding-left: 18px;">
                    <li>🎮 <b>3D Settings</b></li>
                    <li>🖥️ <b>Display Settings</b></li>
                    <li>📊 <b>Performance Monitoring</b></li>
                    <li>🎛️ <b>GPU Tuning</b></li>
                </ul>
                <li style="margin-bottom: 8px;">Use <b>sidebar buttons</b> to clear chat or view available tools <span style="font-size:1.1em;">🧹🔧</span></li>
            </ul>
        </div>
        """, unsafe_allow_html=True)

        st.divider()
        # Show available tools button
        button_text = "🔧 Hide Available Tools" if st.session_state.show_tools else "🔧 Show Available Tools"
        if st.button(button_text, use_container_width=True):
            if not st.session_state.show_tools:
                asyncio.run(show_available_tools())
                st.session_state.show_tools = True
            else:
                st.session_state.show_tools = False
                st.session_state.tools_by_server = {}
            st.rerun()

        # Display available tools in sidebar with collapsible sections (beautified)
        if st.session_state.show_tools and st.session_state.tools_by_server:
            st.divider()
            st.markdown("""
            <div style="margin-bottom: 10px;">
                <h3 style="color: #007acc; margin-bottom: 8px; font-size: 1.18rem; font-weight: 700; letter-spacing: 0.5px;">🔧 Available Tools</h3>
            </div>
            """, unsafe_allow_html=True)
            for server_name, server_data in st.session_state.tools_by_server.items():
                expander_key = f"server_{server_name.replace(' ', '_').replace('-', '_').lower()}"
                with st.expander(f"🖥️ {server_name}", expanded=False):
                    if server_data.get("error"):
                        st.error(f"Error: {server_data['error']}")
                    elif server_data.get("tools"):
                        for tool in server_data["tools"]:
                            # Build parameters HTML safely
                            params_html = ""
                            schema = tool.get('input_schema')
                            if schema and schema.get('properties'):
                                params_html += '<div style="margin-bottom: 6px;"><span style="font-weight:500; color:#007acc;">Parameters:</span></div>'
                                params_html += '<ul style="margin-left:0; padding-left:18px;">'
                                for param_name, param_info in schema['properties'].items():
                                    param_type = param_info.get('type', 'unknown')
                                    param_desc = param_info.get('description', 'No description')
                                    required_mark = ' <span style="color:#d32f2f; font-weight:500;">(required)</span>' if param_name in schema.get('required', []) else ''
                                    params_html += f'<li style="margin-bottom:4px;"><span style="font-weight:600; color:#4CAF50;">{param_name}</span> '
                                    params_html += f'<span style="color:#888;">({param_type})</span>{required_mark}: <span style="color:#333;">{param_desc}</span></li>'
                                params_html += '</ul>'

                            description_html = ''
                            if tool.get('description'):
                                description_html = f'<div style="margin-bottom: 6px;"><span style="font-weight:500; color:#4CAF50;">Description:</span> <span style="color:#333;">{tool["description"]}</span></div>'

                            st.markdown(f"""
                            <div style="background: linear-gradient(90deg, #e3f2fd 0%, #f0fff0 100%); border-radius: 10px; padding: 12px 16px; margin-bottom: 10px; box-shadow: 0 1px 4px rgba(0,0,0,0.04);">
                                <div style="display: flex; align-items: center; margin-bottom: 6px;">
                                    <span style="font-size: 1.2em; margin-right: 8px;">🛠️</span>
                                    <span style="font-weight: 600; color: #007acc; font-size: 1.08em;">{tool['name']}</span>
                                </div>
                                {description_html}
                                {params_html}
                            </div>
                            """, unsafe_allow_html=True)
                    else:
                        st.info("No tools available for this server.")

        st.divider()
        # Clear chat button
        if st.button("🗑️ Clear Chat History", use_container_width=True):
            st.session_state.initialized = True
            st.session_state.messages = []
            # Clear the actual chat session history
            if (hasattr(st.session_state, 'chat_session') and 
                st.session_state.chat_session and 
                st.session_state.chat_session.chat_session):
                asyncio.run(st.session_state.chat_session.clear_history())
            st.rerun()
    
    # Main chat interface
    st.title("Chat with ADLX MCP Chatbot")
    
    # Display chat messages
    for message in st.session_state.messages:
        if message["role"] == "user":
            safe_content = html.escape(message["content"])
            st.markdown(
                f"""
                <div style="display: flex; justify-content: flex-end; align-items: flex-end; margin: 14px 0;">
                    <div class="chat-bubble" style="background: linear-gradient(90deg, #007acc 0%, #4CAF50 100%); color: white; padding: 16px 22px; border-radius: 22px 22px 10px 22px; max-width: 70%; word-wrap: break-word; margin-right: 12px; font-size: 1.12em;">
                        {safe_content}
                    </div>
                    <div style="width: 42px; height: 42px; background: #007acc; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                        👤
                    </div>
                </div>
                """,
                unsafe_allow_html=True
            )
        else:
            safe_content = html.escape(message["content"])
            if message["content"].startswith("Error:"):
                st.markdown(
                    f"""
                    <div style="display: flex; justify-content: flex-start; align-items: flex-end; margin: 14px 0;">
                        <div style="width: 42px; height: 42px; background: #f44336; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; margin-right: 12px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                            ⚠️
                        </div>
                        <div class="chat-bubble" style="background: linear-gradient(90deg, #ffebee 0%, #ffcdd2 100%); color: #c62828; padding: 16px 22px; border-radius: 22px 22px 22px 10px; max-width: 70%; word-wrap: break-word; border: 1px solid #ef5350; font-size: 1.12em;">
                            {safe_content}
                        </div>
                    </div>
                    """,
                    unsafe_allow_html=True
                )
            else:
                st.markdown(
                    f"""
                    <div style="display: flex; justify-content: flex-start; align-items: flex-end; margin: 14px 0;">
                        <div style="width: 42px; height: 42px; background: #4CAF50; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-size: 22px; margin-right: 12px; flex-shrink: 0; box-shadow: 0 2px 8px rgba(0,0,0,0.10);">
                            🤖
                        </div>
                        <div class="chat-bubble" style="background: linear-gradient(90deg, #f0f0f0 0%, #e3f2fd 100%); color: #333; padding: 16px 22px; border-radius: 22px 22px 22px 10px; max-width: 70%; word-wrap: break-word; font-size: 1.12em;">
                            {safe_content}
                        </div>
                    </div>
                    """,
                    unsafe_allow_html=True
                )
    
    # Chat input
    if prompt := st.chat_input("What would you like to know about your AMD settings?"):
        # Process regular user input
        asyncio.run(handle_user_input(prompt))
        st.rerun()


if __name__ == "__main__":
    main()