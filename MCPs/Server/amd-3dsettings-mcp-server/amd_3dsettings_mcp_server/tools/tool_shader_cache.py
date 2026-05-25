from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_reset_shader_cache_support(gpu_index: int = 0) -> bool:
    """
    Check if Reset Shader Cache is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_reset_shader_cache_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Reset Shader Cache support: {str(e)}")

def reset_shader_cache(gpu_index: int = 0) -> str:
    """
    Reset the shader cache.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_reset_shader_cache_support(gpu_index):
            return "Reset Shader Cache is not supported."

        gpu = wrapper.gpus[gpu_index]
        if wrapper.reset_shader_cache(gpu):
            return "Shader cache has been reset successfully."
        else:
            return "Failed to reset shader cache."
    except Exception as e:
        raise RuntimeError(f"Error resetting shader cache: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Resetting shader cache:")
        print(reset_shader_cache())
            
    except Exception as e:
        print(f"Error: {e}")
