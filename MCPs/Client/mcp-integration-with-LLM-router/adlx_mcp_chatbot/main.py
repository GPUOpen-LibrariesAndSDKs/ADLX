
import argparse
import asyncio
import subprocess
import sys
import os
from adlx_mcp_chatbot.apps.cli_app import main as cli_main
from adlx_mcp_chatbot.apps.streamlit_app import main as streamlit_main


def get_resource_path(relative_path):
    """Get absolute path to resource, works for dev and for PyInstaller."""
    try:
        # PyInstaller creates a temp folder and stores path in _MEIPASS
        if hasattr(sys, "_MEIPASS"):
            base_path = sys._MEIPASS  # type: ignore
        else:
            base_path = os.path.abspath(".")
    except Exception:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)


async def run_cli_app(llm_api_key: str | None = None, llm_base_url: str | None = None):
    """Run the CLI application.
    
    Args:
        llm_api_key: Optional LLM API key.
        llm_base_url: Optional LLM base URL.
    """
    await cli_main(llm_api_key, llm_base_url)


def run_streamlit_app(llm_api_key: str | None = None, llm_base_url: str | None = None):
    """Run the Streamlit application.
    
    Args:
        llm_api_key: Optional LLM API key.
        llm_base_url: Optional LLM base URL.
    """
    # Store credentials in environment for streamlit subprocess
    if llm_api_key:
        os.environ["LLM_API_KEY"] = llm_api_key
    if llm_base_url:
        os.environ["LLM_BASE_URL"] = llm_base_url
    
    # Check if running as a PyInstaller executable
    if getattr(sys, 'frozen', False):
        # Running as executable - call streamlit main directly
        try:
            # Set up streamlit arguments
            import streamlit.web.cli as stcli
            
            # Get the path to the streamlit_app.py file in the PyInstaller bundle
            streamlit_app_path = get_resource_path(os.path.join("adlx_mcp_chatbot", "apps", "streamlit_app.py"))
            
            # Set sys.argv to mimic streamlit run command (without port/address to avoid dev mode issues)
            sys.argv = [
                "streamlit", "run", streamlit_app_path,
                "--server.headless", "true",
                "--global.developmentMode", "false"
            ]
            
            # Call streamlit's main function directly
            stcli.main()
            
        except Exception as e:
            print(f"Error running Streamlit app: {e}")
            sys.exit(1)
    else:
        # Running in development - use subprocess
        current_dir = os.path.dirname(os.path.abspath(__file__))
        streamlit_app_path = os.path.join(current_dir, "apps", "streamlit_app.py")
        
        cmd = [
            sys.executable, "-m", "streamlit", "run", 
            streamlit_app_path,
            "--server.port", "8501",
            "--server.address", "localhost"
        ]
        
        try:
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error running Streamlit app: {e}")
            sys.exit(1)
        except FileNotFoundError:
            print("Streamlit is not installed. Please install it with: pip install streamlit")
            sys.exit(1)
    

def main():
    """Synchronous main entry point."""
    parser = argparse.ArgumentParser(
        description="Simple Chatbot MCP Client",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python main.py cli          # Run CLI interface
  python main.py streamlit    # Run Streamlit web interface
        """
    )
    
    parser.add_argument(
        "mode",
        choices=["cli", "streamlit"],
        help="Choose the interface mode"
    )
    
    parser.add_argument(
        "--llm-api-key",
        type=str,
        default=None,
        help="LLM API key (overrides LLM_API_KEY environment variable)"
    )
    
    parser.add_argument(
        "--llm-base-url",
        type=str,
        default=None,
        help="LLM base URL (overrides LLM_BASE_URL environment variable)"
    )
    
    args = parser.parse_args()
    
    if args.mode == "cli":
        asyncio.run(run_cli_app(args.llm_api_key, args.llm_base_url))
    elif args.mode == "streamlit":
        run_streamlit_app(args.llm_api_key, args.llm_base_url)


if __name__ == "__main__":
    main()