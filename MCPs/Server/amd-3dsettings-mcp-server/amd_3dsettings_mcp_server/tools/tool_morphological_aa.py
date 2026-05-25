from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_morphological_aa_support(gpu_index: int = 0) -> bool:
    """
    Check if Morphological Anti-Aliasing is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_morphological_anti_aliasing_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Morphological Anti-Aliasing support: {str(e)}")

def get_morphological_aa_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Morphological Anti-Aliasing.
    
    Returns:
        str: A message indicating the current state of Morphological Anti-Aliasing.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_morphological_aa_support(gpu_index):
            return "Morphological Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        enabled = wrapper.is_morphological_anti_aliasing_enabled(gpu)
        return f"Current state of Morphological Anti-Aliasing is: {'enabled' if enabled else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Morphological Anti-Aliasing state: {str(e)}")

def set_morphological_aa_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Morphological Anti-Aliasing.
    
    Args:
        state (int): 0 to disable Morphological Anti-Aliasing, 1 to enable.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_morphological_aa_support(gpu_index):
            return "Morphological Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_morphological_anti_aliasing_enabled(gpu, bool(state)):
            return f"Morphological Anti-Aliasing {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Morphological Anti-Aliasing."
    except Exception as e:
        raise RuntimeError(f"Error setting Morphological Anti-Aliasing state: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_morphological_aa_state())
            
        print("\nEnabling Morphological Anti-Aliasing:")
        print(set_morphological_aa_state(1))
        print(get_morphological_aa_state())
            
        print("\nDisabling Morphological Anti-Aliasing:")
        print(set_morphological_aa_state(0))
        print(get_morphological_aa_state())
            
    except Exception as e:
        print(f"Error: {e}")
