from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from adlx import ADLX

@lru_cache(maxsize=1)
def check_anisotropic_filtering_support(gpu_index: int = 0) -> bool:
    """
    Check if Anisotropic Filtering is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_anisotropic_filtering_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Anisotropic Filtering support: {str(e)}")

def get_anisotropic_filtering_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Anisotropic Filtering.
    
    Returns:
        str: A message indicating the current state of Anisotropic Filtering.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anisotropic_filtering_support(gpu_index):
            return "Anisotropic Filtering is not supported."

        gpu = wrapper.gpus[gpu_index]
        enabled = wrapper.is_anisotropic_filtering_enabled(gpu)
        return f"Current state of Anisotropic Filtering is: {'enabled' if enabled else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Anisotropic Filtering state: {str(e)}")

def set_anisotropic_filtering_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Anisotropic Filtering.
    
    Args:
        state (int): 0 to disable Anisotropic Filtering, 1 to enable.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anisotropic_filtering_support(gpu_index):
            return "Anisotropic Filtering is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_anisotropic_filtering_enabled(gpu, bool(state)):
            return f"Anisotropic Filtering {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Anisotropic Filtering."
    except Exception as e:
        raise RuntimeError(f"Error setting Anisotropic Filtering state: {str(e)}")
    
def get_anisotropic_filtering_level(gpu_index: int = 0) -> str:
    """
    Get the current level of Anisotropic Filtering.
    
    Returns:
        str: A message indicating the current level of Anisotropic Filtering.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anisotropic_filtering_support(gpu_index):
            return "Anisotropic Filtering is not supported."

        gpu = wrapper.gpus[gpu_index]
        level = wrapper.get_anisotropic_filtering_level(gpu)
        return f"Current Anisotropic Filtering level is: {level}."
    except Exception as e:
        raise RuntimeError(f"Error getting Anisotropic Filtering level: {str(e)}")
    
def set_anisotropic_filtering_level(level: str, gpu_index: int = 0) -> str:
    """
    Set the level of Anisotropic Filtering.
    
    Args:
        level (str): The desired level of Anisotropic Filtering.
        The valid levels are:
        - "AF_LEVEL_X2"
        - "AF_LEVEL_X4"
        - "AF_LEVEL_X8"
        - "AF_LEVEL_X16"
    
    Returns:
        str: A message indicating the result of the operation.
    """
    level_map = {
        "AF_LEVEL_X2": ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X2,
        "AF_LEVEL_X4": ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X4,
        "AF_LEVEL_X8": ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X8,
        "AF_LEVEL_X16": ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X16,
    }
    
    if not isinstance(level, str) or level not in level_map:
        return "Level must be one of the following values: 'AF_LEVEL_X2', 'AF_LEVEL_X4', 'AF_LEVEL_X8', or 'AF_LEVEL_X16'."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anisotropic_filtering_support(gpu_index):
            return "Anisotropic Filtering is not supported."

        gpu = wrapper.gpus[gpu_index]
        # Set the Anisotropic Filtering level
        if wrapper.set_anisotropic_filtering_level(gpu, level_map[level]):
            return f"Anisotropic Filtering level set to {level}."
        else:
            return f"Failed to set Anisotropic Filtering level to {level}."
    except Exception as e:
        raise RuntimeError(f"Error setting Anisotropic Filtering level: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_anisotropic_filtering_state())
            
        print("\nEnabling Anisotropic Filtering:")
        print(set_anisotropic_filtering_state(1))
        print(get_anisotropic_filtering_state())

        print(get_anisotropic_filtering_level())
        print(set_anisotropic_filtering_level("AF_LEVEL_X8"))
        print(get_anisotropic_filtering_level())
            
    except Exception as e:
        print(f"Error: {e}")
