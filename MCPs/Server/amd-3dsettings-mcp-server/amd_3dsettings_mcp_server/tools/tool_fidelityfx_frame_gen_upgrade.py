from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_fidelityfx_frame_gen_upgrade_support(gpu_index: int = 0) -> bool:
    """
    Check if FidelityFX Frame Generation Upgrade is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_fidelityfx_frame_gen_upgrade_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking FidelityFX Frame Generation Upgrade support: {str(e)}")

def set_fidelityfx_frame_gen_upgrade_state(state: int, gpu_index: int = 0) -> str:
    """
    Set the state of FidelityFX Frame Generation Upgrade.
    
    Args:
        state (int): 0 to disable FidelityFX Frame Generation Upgrade, 1 to enable.
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
        
        if not check_fidelityfx_frame_gen_upgrade_support(gpu_index):
            return "FidelityFX Frame Generation Upgrade is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.set_fidelityfx_frame_gen_upgrade_enabled(gpu, bool(state)):
            return f"FidelityFX Frame Generation Upgrade {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} FidelityFX Frame Generation Upgrade."
    except Exception as e:
        raise RuntimeError(f"Error setting FidelityFX Frame Generation Upgrade state: {str(e)}")

def get_fidelityfx_frame_gen_upgrade_state(gpu_index: int = 0) -> str:
    """
    Get the current state of FidelityFX Frame Generation Upgrade.
    
    Args:
        gpu_index (int): The index of the GPU to query (defaults to 0).
    
    Returns:
        str: A message indicating the current state of FidelityFX Frame Generation Upgrade.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_fidelityfx_frame_gen_upgrade_support(gpu_index):
            return "FidelityFX Frame Generation Upgrade is not supported."

        gpu = wrapper.gpus[gpu_index]
        return f"Current state of FidelityFX Frame Generation Upgrade is: {'enabled' if wrapper.is_fidelityfx_frame_gen_upgrade_enabled(gpu) else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting FidelityFX Frame Generation Upgrade state: {str(e)}")


if __name__ == "__main__":
    # Example usage
    gpu_index = 0
    try:
        print("Checking FidelityFX Frame Generation Upgrade support...")
        if check_fidelityfx_frame_gen_upgrade_support(gpu_index):
            print("FidelityFX Frame Generation Upgrade is supported.")
            
            # Get current state
            print("\nGetting current state:")
            print(get_fidelityfx_frame_gen_upgrade_state(gpu_index))

            # Set state
            print("\nEnabling FidelityFX Frame Generation Upgrade:")
            print(set_fidelityfx_frame_gen_upgrade_state(1, gpu_index))

            # Verify changes
            print("\nVerifying changes:")
            print(get_fidelityfx_frame_gen_upgrade_state(gpu_index))
        else:
            print("FidelityFX Frame Generation Upgrade is not supported.")
    except Exception as e:
        print(f"Error: {e}")
