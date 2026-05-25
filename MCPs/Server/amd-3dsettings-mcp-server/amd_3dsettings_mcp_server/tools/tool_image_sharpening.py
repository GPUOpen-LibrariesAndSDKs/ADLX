from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_image_sharpening_support(gpu_index: int = 0) -> bool:
    """
    Check if Image Sharpening is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_image_sharpening_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Image Sharpening support: {str(e)}")

def set_image_sharpening_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon Image Sharpening.

    Args:
        state (int): 0 to disable Image Sharpening, 1 to enable.
        gpu_index (int): The index of the GPU to modify (defaults to first GPU).

    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_image_sharpening_support(gpu_index):
            return "Radeon Image Sharpening is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_image_sharpening_enabled(gpu, bool(state)):
            return f"Radeon Image Sharpening {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Image Sharpening."
    except Exception as e:
        raise RuntimeError(f"Error setting Image Sharpening state: {str(e)}")

def get_image_sharpening_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon Image Sharpening.
    
    Returns:
        str: A message indicating the current state of Image Sharpening.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_image_sharpening_support(gpu_index):
            return "Radeon Image Sharpening is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of Radeon Image Sharpening is: {'enabled' if wrapper.is_image_sharpening_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Image Sharpening state: {str(e)}")

def get_image_sharpness_range(gpu_index: int = 0) -> str:
    """
    Get the range of sharpness values for Radeon Image Sharpening.
    
    Returns:
        str: A message indicating the sharpness range or an error message.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_image_sharpening_support(gpu_index):
            return "Radeon Image Sharpening is not supported."

        gpu = wrapper.gpus[gpu_index]
        range_info = wrapper.get_image_sharpness_range(gpu)
        return f"Radeon Image Sharpening sharpness range: min={range_info['minValue']}, max={range_info['maxValue']}."
    except Exception as e:
        raise RuntimeError(f"Error getting Image Sharpening sharpness range: {str(e)}")

def get_image_sharpness(gpu_index: int = 0) -> str:
    """
    Get the current sharpness value for Radeon Image Sharpening.
    
    Returns:
        str: A message indicating the current sharpness value.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_image_sharpening_support(gpu_index):
            return "Radeon Image Sharpening is not supported."

        gpu = wrapper.gpus[gpu_index]
        sharpness = wrapper.get_image_sharpness(gpu)
        return f"Current Radeon Image Sharpening sharpness is: {sharpness}."
    except Exception as e:
        raise RuntimeError(f"Error getting Image Sharpening sharpness: {str(e)}")

def set_image_sharpness(sharpness: int, gpu_index: int = 0) -> str:
    """
    Set the sharpness value for Radeon Image Sharpening.
    
    Args:
        sharpness (int): The sharpness value to set.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(sharpness, int):
        return "Sharpness value must be an integer."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_image_sharpening_support(gpu_index):
            return "Radeon Image Sharpening is not supported."

        gpu = wrapper.gpus[gpu_index]
        sharpness_range = wrapper.get_image_sharpness_range(gpu)
        if not (sharpness_range['minValue'] <= sharpness <= sharpness_range['maxValue']):
            return f"Sharpness value must be between {sharpness_range['minValue']} and {sharpness_range['maxValue']}."

        if wrapper.set_image_sharpness(gpu, sharpness):
            return f"Radeon Image Sharpening sharpness set to {sharpness}."
        else:
            return "Failed to set Radeon Image Sharpening sharpness."
    except Exception as e:
        raise RuntimeError(f"Error setting Image Sharpening sharpness: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_image_sharpening_state())
            
        print("\nEnabling Image Sharpening:")
        print(set_image_sharpening_state(1))
        print(get_image_sharpening_state())

        print("\nCurrent sharpness value:")
        print(get_image_sharpness())
        print("\nCurrent Image Sharpening Sharpness Range:")
        print(get_image_sharpness_range())
        print("\nSetting Image Sharpening sharpness to 66:")
        print(set_image_sharpness(70))
        print("\nCurrent sharpness value after setting:")
        print(get_image_sharpness())
            
        print("\nDisabling Image Sharpening:")
        print(set_image_sharpening_state(0))
        print(get_image_sharpening_state())
            
    except Exception as e:
        print(f"Error: {e}")
