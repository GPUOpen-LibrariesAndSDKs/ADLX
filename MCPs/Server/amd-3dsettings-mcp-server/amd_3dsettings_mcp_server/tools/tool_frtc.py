from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_frtc_support(gpu_index: int = 0) -> bool:
    """
    Check if FRTC (Frame Rate Target Control) is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_frtc_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking FRTC support: {str(e)}")

def set_frtc_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon FRTC (Frame Rate Target Control).
    
    Args:
        state (int): 0 to disable FRTC, 1 to enable.
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
        
        if not check_frtc_support(gpu_index):
            return "Radeon FRTC is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_frtc_enabled(gpu, bool(state)):
            return f"Radeon FRTC {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon FRTC."
    except Exception as e:
        raise RuntimeError(f"Error setting FRTC state: {str(e)}")

def get_frtc_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon FRTC (Frame Rate Target Control).
    
    Returns:
        str: A message indicating the current state of FRTC.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_frtc_support(gpu_index):
            return "Radeon FRTC is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of Radeon FRTC is: {'enabled' if wrapper.is_frtc_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting FRTC state: {str(e)}")

def get_frtc_fps_range(gpu_index: int = 0) -> str:
    """
    Get the range of FPS values for Radeon FRTC.
    
    Returns:
        str: A message indicating the FPS range or an error message.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_frtc_support(gpu_index):
            return "Radeon FRTC is not supported."

        gpu = wrapper.gpus[gpu_index]
        range_info = wrapper.get_frtc_fps_range(gpu)
        return f"Radeon FRTC FPS range: min={range_info['minValue']}, max={range_info['maxValue']}."
    except Exception as e:
        raise RuntimeError(f"Error getting FRTC FPS range: {str(e)}")

def get_frtc_fps(gpu_index: int = 0) -> str:
    """
    Get the current FPS value for Radeon FRTC.
    
    Returns:
        str: A message indicating the current FPS value.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_frtc_support(gpu_index):
            return "Radeon FRTC is not supported."

        gpu = wrapper.gpus[gpu_index]
        fps = wrapper.get_frtc_fps(gpu)
        return f"Current Radeon FRTC FPS is: {fps}."
    except Exception as e:
        raise RuntimeError(f"Error getting FRTC FPS: {str(e)}")

def set_frtc_fps(fps: int, gpu_index: int = 0) -> str:
    """
    Set the FPS value for Radeon FRTC.
    
    Args:
        fps (int): The FPS value to set.
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
        
        if not check_frtc_support(gpu_index):
            return "Radeon FRTC is not supported."

        gpu = wrapper.gpus[gpu_index]
        fps_range = wrapper.get_frtc_fps_range(gpu)
        if not (fps_range['minValue'] <= fps <= fps_range['maxValue']):
            return f"FPS value must be between {fps_range['minValue']} and {fps_range['maxValue']}."

        if wrapper.set_frtc_fps(gpu, fps):
            return f"Radeon FRTC FPS set to {fps}."
        else:
            return "Failed to set Radeon FRTC FPS."
    except Exception as e:
        raise RuntimeError(f"Error setting FRTC FPS: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_frtc_state())
            
        print("\nEnabling FRTC:")
        print(set_frtc_state(1))
        print(get_frtc_state())


        print("\nFRTC FPS Range:", get_frtc_fps_range())
        print(f"Current FRTC FPS: {get_frtc_fps()}")
        print("\nSetting FRTC FPS to 70:")
        print(set_frtc_fps(70))
        print(f"Current FRTC FPS: {get_frtc_fps()}")

        print("\nDisabling FRTC:")
        print(set_frtc_state(0))
        print(get_frtc_state())
            
    except Exception as e:
        print(f"Error: {e}")
