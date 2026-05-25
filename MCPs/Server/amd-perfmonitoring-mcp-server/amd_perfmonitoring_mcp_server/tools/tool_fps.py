from amd_perfmonitoring_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Tuple, Dict

def get_fps() -> str:
    """Get FPS information."""
    wrapper = ADLXAPIWrapper()
    response = str("FPS Information:\n")

    try:
        fps_metrics = wrapper.get_current_fps()
        response += f"Current FPS: {fps_metrics.FPS()}\n"
    except Exception as e:
        response += f"Error retrieving FPS information: {str(e)}"

    return response

def get_fps_timestamp() -> str:
    """Get FPS timestamp."""
    wrapper = ADLXAPIWrapper()
    response = str("FPS Timestamp Information:\n")

    try:
        fps_metrics = wrapper.get_current_fps()
        response += f"FPS Timestamp: {fps_metrics.TimeStamp()} ms\n"
    except Exception as e:
        response += f"Error retrieving FPS timestamp information: {str(e)}"

    return response

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        fps_info = get_fps()
        print(fps_info)
        
        fps_timestamp_info = get_fps_timestamp()
        print(fps_timestamp_info)
    except Exception as e:
        print(f"Error: {e}")

