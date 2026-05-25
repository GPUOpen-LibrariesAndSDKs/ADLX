from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_chill_support(gpu_index: int = 0) -> bool:
    """
    Check if Chill is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_chill_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Chill support: {str(e)}")

def set_chill_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon Chill.
    
    Args:
        state (int): 0 to disable Chill, 1 to enable.
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
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_chill_enabled(gpu, bool(state)):
            return f"Radeon Chill {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Chill."
    except Exception as e:
        raise RuntimeError(f"Error setting Chill state: {str(e)}")

def get_chill_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon Chill.
    
    Returns:
        str: A message indicating the current state of Chill.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of Radeon Chill is: {'enabled' if wrapper.is_chill_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Chill state: {str(e)}")

def get_chill_fps_range(gpu_index: int = 0) -> str:
    """
    Get the range of FPS values for Radeon Chill.
    
    Returns:
        str: A message indicating the FPS range or an error message.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        range_info = wrapper.get_chill_fps_range(gpu)
        return f"Radeon Chill FPS range: min={range_info['minValue']}, max={range_info['maxValue']}."
    except Exception as e:
        raise RuntimeError(f"Error getting Chill FPS range: {str(e)}")

def get_chill_max_fps(gpu_index: int = 0) -> str:
    """
    Get the current maximum FPS value for Radeon Chill.
    
    Returns:
        str: A message indicating the current maximum FPS value.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        max_fps = wrapper.get_chill_max_fps(gpu)
        return f"Current Radeon Chill maximum FPS is: {max_fps}."
    except Exception as e:
        raise RuntimeError(f"Error getting Chill max FPS: {str(e)}")

def set_chill_max_fps(fps: int, gpu_index: int = 0) -> str:
    """
    Set the maximum FPS value for Radeon Chill.
    
    Args:
        fps (int): The maximum FPS value to set.
        gpu_index (int): The index of the GPU to modify (defaults to 0).
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(fps, int):
        return "FPS value must be an integer."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        fps_range = wrapper.get_chill_fps_range(gpu)
        if not (fps_range['minValue'] <= fps <= fps_range['maxValue']):
            return f"FPS value must be between {fps_range['minValue']} and {fps_range['maxValue']}."

        if wrapper.set_chill_max_fps(gpu, fps):
            return f"Radeon Chill maximum FPS set to {fps}."
        else:
            return "Failed to set Radeon Chill maximum FPS."
    except Exception as e:
        raise RuntimeError(f"Error setting Chill max FPS: {str(e)}")

def get_chill_min_fps(gpu_index: int = 0) -> str:
    """
    Get the current minimum FPS value for Radeon Chill.
    
    Returns:
        str: A message indicating the current minimum FPS value.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        min_fps = wrapper.get_chill_min_fps(gpu)
        return f"Current Radeon Chill minimum FPS is: {min_fps}."
    except Exception as e:
        raise RuntimeError(f"Error getting Chill min FPS: {str(e)}")

def set_chill_min_fps(fps: int, gpu_index: int = 0) -> str:
    """
    Set the minimum FPS value for Radeon Chill.
    
    Args:
        fps (int): The minimum FPS value to set.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(fps, int):
        return "FPS value must be an integer."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_chill_support(gpu_index):
            return "Radeon Chill is not supported."

        gpu = wrapper.gpus[gpu_index]
        fps_range = wrapper.get_chill_fps_range(gpu)
        if not (fps_range['minValue'] <= fps <= fps_range['maxValue']):
            return f"FPS value must be between {fps_range['minValue']} and {fps_range['maxValue']}."

        if wrapper.set_chill_min_fps(gpu, fps):
            return f"Radeon Chill minimum FPS set to {fps}."
        else:
            return "Failed to set Radeon Chill minimum FPS."
    except Exception as e:
        raise RuntimeError(f"Error setting Chill min FPS: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_chill_state())
            
        print("\nEnabling Chill:")
        print(set_chill_state(1))
        print(get_chill_state())

        print("\nCurrent Chill FPS Range:")
        print(get_chill_fps_range())
        print("\nCurrent Chill Max FPS:", get_chill_max_fps())
        print("\nCurrent Chill Min FPS:", get_chill_min_fps())
        print("\nSetting Chill Max FPS to 60:")
        print(set_chill_max_fps(60))
        print("\nSetting Chill Min FPS to 30:")
        print(set_chill_min_fps(30))
            
        print("\nDisabling Chill:")
        print(set_chill_state(0))
        print(get_chill_state())
            
    except Exception as e:
        print(f"Error: {e}")
