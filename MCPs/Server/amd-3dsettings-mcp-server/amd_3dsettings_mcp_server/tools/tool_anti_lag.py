from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_anti_lag_support(gpu_index: int = 0) -> bool:
    """
    Check if Anti-Lag is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_anti_lag_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Anti-Lag support: {str(e)}")

def set_anti_lag_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon Anti-Lag.
    
    Args:
        state (int): 0 to disable Anti-Lag, 1 to enable.
        gpu_index (int): The index of the GPU to modify (defaults to 0).

    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_lag_support(gpu_index):
            return "Radeon Anti-Lag is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_anti_lag_enabled(gpu, bool(state)):
            return f"Radeon Anti-Lag {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Anti-Lag."
    except Exception as e:
        raise RuntimeError(f"Error setting Anti-Lag state: {str(e)}")

def get_anti_lag_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon Anti-Lag.
    
    Returns:
        str: A message indicating the current state of Anti-Lag.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_lag_support(gpu_index):
            return "Radeon Anti-Lag is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of Radeon Anti-Lag is: {'enabled' if wrapper.is_anti_lag_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Anti-Lag state: {str(e)}")

# def get_anti_lag_level() -> str:
#     """
#     Get the current level for Radeon Anti-Lag.
    
#     Returns:
#         Dict[str, int]: A dictionary containing level information.
    
#     Raises:
#         RuntimeError: If Anti-Lag is not supported or operation fails.
#     """
#     is_supported, error = check_anti_lag_support()
#     if not is_supported:
#         raise RuntimeError(error or "Radeon Anti-Lag is not supported.")

#     try:
#         adlx = get_adlx_instance()
#         gpu = get_gpu()
#         return f"Current level of Radeon Anti-Lag is: {adlx.get_anti_lag_level(gpu)}."
#     except Exception as e:
#         raise RuntimeError(f"Error getting Anti-Lag level: {str(e)}")

# def set_anti_lag_level(level: int) -> str:
#     """
#     Set the level for Radeon Anti-Lag.
    
#     Args:
#         level (int): The level value to set.
#         The valid levels are:
#         - 0: ANTILAG
#         - 1: ANTILAGNEXT

#     Returns:
#         str: A message indicating the result of the operation.
    
#     Raises:
#         ValueError: If level is not an integer.
#         RuntimeError: If Anti-Lag is not supported or operation fails.
#     """
#     if not isinstance(level, int):
#         raise ValueError("Level value must be an integer.")

#     is_supported, error = check_anti_lag_support()
#     if not is_supported:
#         raise RuntimeError(error or "Radeon Anti-Lag is not supported.")

#     try:
#         adlx = get_adlx_instance()
#         gpu = get_gpu()
#         # Validate level
#         if level not in (0, 1):
#             raise ValueError("Invalid level. Valid levels are 0 (ANTILAG) and 1 (ANTILAGNEXT).")
        
#         #Transfer the int level to the ADLX value
#         level = ADLX.ADLX_ANTILAG_STATE.ANTILAG if level == 0 else ADLX.ADLX_ANTILAG_STATE.ANTILAGNEXT

#         if adlx.set_anti_lag_level(gpu, level):
#             return f"Radeon Anti-Lag level set to {level}."
#         else:
#             raise RuntimeError("Failed to set Radeon Anti-Lag level.")
#     except Exception as e:
#         raise RuntimeError(f"Error setting Anti-Lag level: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_anti_lag_state())
            
        print("\nEnabling Anti-Lag:")
        print(set_anti_lag_state(1))
        print(get_anti_lag_state())
            
        print("\nDisabling Anti-Lag:")
        print(set_anti_lag_state(0))
        print(get_anti_lag_state())
            
    except Exception as e:
        print(f"Error: {e}")
