from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from adlx import ADLX

@lru_cache(maxsize=1)
def check_anti_aliasing_support(gpu_index: int = 0) -> bool:
    """
    Check if Anti-Aliasing is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_anti_aliasing_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Anti-Aliasing support: {str(e)}")

def get_anti_aliasing_mode(gpu_index: int = 0) -> str:
    """
    Get the current mode of Anti-Aliasing.

    Returns:
        str: A message indicating the current mode of Anti-Aliasing.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_aliasing_support(gpu_index):
            return "Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        mode = wrapper.get_anti_aliasing_mode(gpu)
        return f"Current Anti-Aliasing mode: {mode}"
    except Exception as e:
        raise RuntimeError(f"Error getting Anti-Aliasing state: {str(e)}")

def set_anti_aliasing_mode(mode: str, gpu_index: int = 0) -> str:
    """
    Set the mode of Anti-Aliasing.
    
    Args:
        mode (str): The Anti-Aliasing mode to set. Accepts:
            - 'use_app_settings': Use application settings
            - 'enhance_app_settings': Enhance application settings
            - 'override_app_settings': Override application settings
        gpu_index (int): The index of the GPU to modify (defaults to 0).
    
    Returns:
        str: A message indicating the result of the operation.
    """
    # Map mode parameter directly to ADLX enum
    mode_map = {
        'use_app_settings': (ADLX.AA_MODE_USE_APP_SETTINGS, "Use App Settings"),
        'enhance_app_settings': (ADLX.AA_MODE_ENHANCE_APP_SETTINGS, "Enhance App Settings"),
        'override_app_settings': (ADLX.AA_MODE_OVERRIDE_APP_SETTINGS, "Override App Settings"),
    }
    
    # Normalize string input to lowercase
    lookup_key = mode.lower().strip() if isinstance(mode, str) else ""
    
    if lookup_key not in mode_map:
        return (
            f"Invalid Anti-Aliasing mode: '{mode}'. "
            f"Accepted values: 'use_app_settings', 'enhance_app_settings', 'override_app_settings'"
        )

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_aliasing_support(gpu_index):
            return "Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        adlx_mode, mode_name = mode_map[lookup_key]
        
        if wrapper.set_anti_aliasing_mode(gpu, adlx_mode):
            return f"Anti-Aliasing mode set to {mode_name}."
        else:
            return "Failed to set Anti-Aliasing mode."
    except Exception as e:
        raise RuntimeError(f"Error setting Anti-Aliasing mode: {str(e)}")

def get_anti_aliasing_level(gpu_index: int = 0) -> str:
    """
    Get the current level of Anti-Aliasing.
    This function only take effect when the mode is set to override app settings.

    Returns:
        str: A message indicating the current level of Anti-Aliasing.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_aliasing_support(gpu_index):
            return "Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        level = wrapper.get_anti_aliasing_level(gpu)
        return f"Current Anti-Aliasing level: {level}"
    except Exception as e:
        raise RuntimeError(f"Error getting Anti-Aliasing level: {str(e)}")

def set_anti_aliasing_level(level: str, gpu_index: int = 0) -> str:
    """
    Set the level of Anti-Aliasing.
    This function only take effect when the mode is set to override app settings.

    Args:
        level (str): The Anti-Aliasing level to set. Accepts:
            - '2x': 2x Multi-Sampling
            - '2xeq': 2x Multi-Sampling with Enhanced Quality
            - '4x': 4x Multi-Sampling
            - '4xeq': 4x Multi-Sampling with Enhanced Quality
            - '8x': 8x Multi-Sampling
            - '8xeq': 8x Multi-Sampling with Enhanced Quality
        gpu_index (int): The index of the GPU to modify (defaults to 0).
    
    Returns:
        str: A message indicating the result of the operation.
    """
    # Map level parameter to ADLX enum
    level_map = {
        '2x': (ADLX.AA_LEVEL_2X, "2x"),
        '2xeq': (ADLX.AA_LEVEL_2XEQ, "2x Enhanced Quality"),
        '4x': (ADLX.AA_LEVEL_4X, "4x"),
        '4xeq': (ADLX.AA_LEVEL_4XEQ, "4x Enhanced Quality"),
        '8x': (ADLX.AA_LEVEL_8X, "8x"),
        '8xeq': (ADLX.AA_LEVEL_8XEQ, "8x Enhanced Quality"),
    }
    
    # Normalize string input to lowercase
    lookup_key = level.lower().strip() if isinstance(level, str) else ""
    
    if lookup_key not in level_map:
        return (
            f"Invalid Anti-Aliasing level: '{level}'. "
            f"Accepted values: '2x', '2xeq', '4x', '4xeq', '8x', '8xeq'"
        )

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_anti_aliasing_support(gpu_index):
            return "Anti-Aliasing is not supported."

        gpu = wrapper.gpus[gpu_index]
        adlx_level, level_name = level_map[lookup_key]
        
        if wrapper.set_anti_aliasing_level(gpu, adlx_level):
            return f"Anti-Aliasing level set to {level_name}."
        else:
            return "Failed to set Anti-Aliasing level."
    except Exception as e:
        raise RuntimeError(f"Error setting Anti-Aliasing level: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial mode:")
        print(get_anti_aliasing_mode())
            
        print("\nSetting Anti-Aliasing mode to override_app_settings:")
        print(set_anti_aliasing_mode('override_app_settings'))
        print(get_anti_aliasing_mode())

        print("\nGetting Anti-Aliasing level:")
        print(get_anti_aliasing_level())
        print("\nSetting Anti-Aliasing level to 4x:")
        print(set_anti_aliasing_level('4x'))
        print(get_anti_aliasing_level())

        print("\nSetting Anti-Aliasing mode to use_app_settings:")
        print(set_anti_aliasing_mode('use_app_settings'))
        print(get_anti_aliasing_mode())

    except Exception as e:
        print(f"Error: {e}")
