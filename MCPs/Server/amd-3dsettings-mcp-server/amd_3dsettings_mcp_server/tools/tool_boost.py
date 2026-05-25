from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Dict

@lru_cache(maxsize=1)
def check_boost_support(gpu_index: int = 0) -> bool:
    """
    Check if Boost is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_boost_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Boost support: {str(e)}")

def set_boost_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon Boost.
    
    Args:
        state (int): 0 to disable Boost, 1 to enable.
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
        
        if not check_boost_support(gpu_index):
            return "Radeon Boost is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.is_boost_supported(gpu) and wrapper.set_boost_enabled(gpu, bool(state)):
            return f"Radeon Boost {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Boost."
    except Exception as e:
        raise RuntimeError(f"Error setting Boost state: {str(e)}")

def get_boost_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon Boost.
    
    Returns:
        str: A message indicating the current state of Boost.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_boost_support(gpu_index):
            return "Radeon Boost is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.is_boost_supported(gpu):
            return f"Radeon Boost is {'enabled' if wrapper.is_boost_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Boost state: {str(e)}")

def get_boost_resolution_range(gpu_index: int = 0) -> str:
    """
    Get the range of resolution values for Radeon Boost.
    
    Returns:
        str: A message indicating the resolution range or an error message.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_boost_support(gpu_index):
            return "Radeon Boost is not supported."

        gpu = wrapper.gpus[gpu_index]
        range_info = wrapper.get_boost_resolution_range(gpu)
        return f"Radeon Boost resolution range: min={range_info['minValue']}, max={range_info['maxValue']}."
    except Exception as e:
        raise RuntimeError(f"Error getting Boost resolution range: {str(e)}")

def get_boost_resolution(gpu_index: int = 0) -> str:
    """
    Get the current resolution value for Radeon Boost.
    
    Returns:
        str: A message indicating the current resolution value.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_boost_support(gpu_index):
            return "Radeon Boost is not supported."

        gpu = wrapper.gpus[gpu_index]
        resolution = wrapper.get_boost_resolution(gpu)
        return f"Current Radeon Boost resolution is: {resolution}."
    except Exception as e:
        raise RuntimeError(f"Error getting Boost resolution: {str(e)}")

def set_boost_resolution(resolution: int, gpu_index: int = 0) -> str:
    """
    Set the resolution value for Radeon Boost.
    
    Args:
        resolution (int): The resolution value to set.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(resolution, int):
        return "Resolution value must be an integer."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_boost_support(gpu_index):
            return "Radeon Boost is not supported."

        gpu = wrapper.gpus[gpu_index]
        resolution_range = wrapper.get_boost_resolution_range(gpu)
        if not (resolution_range['minValue'] <= resolution <= resolution_range['maxValue']):
            return f"Resolution value must be between {resolution_range['minValue']} and {resolution_range['maxValue']}."

        if wrapper.set_boost_resolution(gpu, resolution):
            return f"Radeon Boost resolution set to {resolution}."
        else:
            return "Failed to set Radeon Boost resolution."
    except Exception as e:
        raise RuntimeError(f"Error setting Boost resolution: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_boost_state())
            
        print("\nEnabling Boost:")
        print(set_boost_state(1))
        print(get_boost_state())

    except Exception as e:
        print(f"Error: {e}")
