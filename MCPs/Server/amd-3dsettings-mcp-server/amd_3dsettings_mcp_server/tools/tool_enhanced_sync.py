from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_enhanced_sync_support(gpu_index: int = 0) -> bool:
    """
    Check if Enhanced Sync is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_enhanced_sync_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Enhanced Sync support: {str(e)}")

def set_enhanced_sync_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of Radeon Enhanced Sync.
    
    Args:
        state (int): 0 to disable Enhanced Sync, 1 to enable.
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
        
        if not check_enhanced_sync_support(gpu_index):
            return "Radeon Enhanced Sync is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_enhanced_sync_enabled(gpu, bool(state)):
            return f"Radeon Enhanced Sync {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Enhanced Sync."
    except Exception as e:
        raise RuntimeError(f"Error setting Enhanced Sync state: {str(e)}")

def get_enhanced_sync_state(gpu_index: int = 0) -> str:
    """
    Get the current state of Radeon Enhanced Sync.
    
    Returns:
        str: A message indicating the current state of Enhanced Sync.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_enhanced_sync_support(gpu_index):
            return "Radeon Enhanced Sync is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of Radeon Enhanced Sync is: {'enabled' if wrapper.is_enhanced_sync_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting Enhanced Sync state: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_enhanced_sync_state())
            
        print("\nEnabling Enhanced Sync:")
        print(set_enhanced_sync_state(1))
        print(get_enhanced_sync_state())

        print("\nDisabling Enhanced Sync:")
        print(set_enhanced_sync_state(0))
        print(get_enhanced_sync_state())
            
    except Exception as e:
        print(f"Error: {e}")
