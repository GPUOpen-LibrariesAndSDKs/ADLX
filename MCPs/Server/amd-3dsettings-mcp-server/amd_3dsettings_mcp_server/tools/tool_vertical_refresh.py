from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from adlx import ADLX

@lru_cache(maxsize=1)
def check_vertical_refresh_support(gpu_index: int = 0) -> bool:
    """
    Check if Wait for Vertical Refresh is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_wait_for_vertical_refresh_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Wait for Vertical Refresh support: {str(e)}")

def set_vertical_refresh_mode(mode: str, gpu_index: int = 0) -> str:
    """
    Set the mode for Wait for Vertical Refresh.
    
    Args:
        mode (str): The vertical refresh mode to set. Accepts:
            - 'always_off': Always off
            - 'off_unless_app_specifies': Off unless application specifies
            - 'on_unless_app_specifies': On unless application specifies
            - 'always_on': Always on
        gpu_index (int): The index of the GPU to modify (defaults to 0).

    Returns:
        str: A message indicating the result of the operation.
    """
    # Map mode parameter directly to ADLX enum
    mode_map = {
        'always_off': (ADLX.WFVR_ALWAYS_OFF, "Always Off"),
        'off_unless_app_specifies': (ADLX.WFVR_OFF_UNLESS_APP_SPECIFIES, "Off Unless App Specifies"),
        'on_unless_app_specifies': (ADLX.WFVR_ON_UNLESS_APP_SPECIFIES, "On Unless App Specifies"),
        'always_on': (ADLX.WFVR_ALWAYS_ON, "Always On"),
    }
    
    # Normalize string input to lowercase
    lookup_key = mode.lower().strip() if isinstance(mode, str) else ""
    
    if lookup_key not in mode_map:
        return f"Invalid Vertical Refresh mode: '{mode}'. Accepted values: 'always_off', 'off_unless_app_specifies', 'on_unless_app_specifies', 'always_on'"

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_vertical_refresh_support(gpu_index):
            return "Wait for Vertical Refresh is not supported."

        gpu = wrapper.gpus[gpu_index]
        adlx_mode, mode_name = mode_map[lookup_key]
        
        if wrapper.set_wait_for_vertical_refresh_mode(gpu, adlx_mode):
            return f"Wait for Vertical Refresh mode set to {mode_name}."
        else:
            return "Failed to set Wait for Vertical Refresh mode."
    except Exception as e:
        raise RuntimeError(f"Error setting Vertical Refresh mode: {str(e)}")

def get_vertical_refresh_mode(gpu_index: int = 0) -> str:
    """
    Get the current mode for Wait for Vertical Refresh.
    
    Returns:
        str: A message indicating the current vertical refresh mode.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_vertical_refresh_support(gpu_index):
            return "Wait for Vertical Refresh is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current Wait for Vertical Refresh mode: {wrapper.get_wait_for_vertical_refresh_mode(gpu)}"
    except Exception as e:
        raise RuntimeError(f"Error getting Vertical Refresh mode: {str(e)}")

def get_vertical_refresh_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Wait for Vertical Refresh.
    
    Returns:
        str: A message indicating the current state of Wait for Vertical Refresh.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_vertical_refresh_support(gpu_index):
            return "Wait for Vertical Refresh is not supported."

        gpu = wrapper.gpus[gpu_index]
        enabled = wrapper.is_wait_for_vertical_refresh_enabled(gpu)
        mode = wrapper.get_wait_for_vertical_refresh_mode(gpu)
        return f"Wait for Vertical Refresh is {'enabled' if enabled else 'disabled'} with mode {mode}."
    except Exception as e:
        raise RuntimeError(f"Error getting Vertical Refresh state: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        # test all functions
        gpu_index = 0  # Change this to test different GPUs if available
        print(get_vertical_refresh_state(gpu_index))
        print(get_vertical_refresh_mode(gpu_index))
        print(set_vertical_refresh_mode('always_off', gpu_index))
        print(get_vertical_refresh_mode(gpu_index))

    except Exception as e:
        print(f"Error: {e}")
