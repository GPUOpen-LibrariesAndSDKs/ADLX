from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from adlx import ADLX

@lru_cache(maxsize=1)
def check_tessellation_support(gpu_index: int = 0) -> bool:
    """
    Check if Tessellation is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpu = wrapper.gpus[gpu_index]
        return wrapper.is_tessellation_supported(gpu)
    except Exception as e:
        raise RuntimeError(f"Error checking Tessellation support: {str(e)}")

def get_tessellation_mode(gpu_index: int = 0) -> str:
    """
    Get the current mode of Tessellation.

    Returns:
        str: A message indicating the current mode of Tessellation.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_tessellation_support(gpu_index):
            return "Tessellation is not supported."

        gpu = wrapper.gpus[gpu_index]
        mode = wrapper.get_tessellation_mode(gpu)
        return f"Current mode of Tessellation is: {mode}."
    except Exception as e:
        raise RuntimeError(f"Error getting Tessellation mode: {str(e)}")

def set_tessellation_mode(mode: str, gpu_index: int = 0) -> str:
    """
    Set the mode of Tessellation.

    Args:
        mode (str): The Tessellation mode to set. Accepts:
            - 'amd_optimized': AMD optimized
            - 'use_app_settings': Use application settings
            - 'override': Override application settings
        gpu_index (int): The index of the GPU to modify (defaults to 0).

    Returns:
        str: A message indicating the result of the operation.
    """
    # Map mode parameter directly to ADLX enum
    mode_map = {
        'amd_optimized': (ADLX.ADLX_TESSELLATION_MODE.T_MODE_AMD_OPTIMIZED, "AMD Optimized"),
        'use_app_settings': (ADLX.ADLX_TESSELLATION_MODE.T_MODE_USE_APP_SETTINGS, "Use App Settings"),
        'override': (ADLX.ADLX_TESSELLATION_MODE.T_MODE_OVERRIDE_APP_SETTINGS, "Override App Settings"),
    }
    
    # Normalize string input to lowercase
    lookup_key = mode.lower().strip() if isinstance(mode, str) else ""
    
    if lookup_key not in mode_map:
        return f"Invalid Tessellation mode: '{mode}'. Accepted values: 'amd_optimized', 'use_app_settings', 'override'"

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_tessellation_support(gpu_index):
            return "Tessellation is not supported."

        gpu = wrapper.gpus[gpu_index]
        adlx_mode, mode_name = mode_map[lookup_key]
        
        if wrapper.set_tessellation_mode(gpu, adlx_mode):
            return f"Tessellation mode set to {mode_name}."
        else:
            return f"Failed to set Tessellation mode to {mode_name}."
    except Exception as e:
        raise RuntimeError(f"Error setting Tessellation mode: {str(e)}")
    
def set_tessellation_level(level: str, gpu_index: int = 0) -> str:
    """
    Set the level of Tessellation.

    Args:
        level (str): The level of Tessellation to set. Accepts:
            - 'off': Tessellation Off
            - '2x': 2x Tessellation
            - '4x': 4x Tessellation
            - '6x': 6x Tessellation
            - '8x': 8x Tessellation
            - '16x': 16x Tessellation
            - '32x': 32x Tessellation
            - '64x': 64x Tessellation
        gpu_index (int): The index of the GPU to modify (defaults to 0).
        Note: Only takes effect when the mode is set to 'override'.

    Returns:
        str: A message indicating the result of the operation.
    """
    # Map level parameter to ADLX enum
    level_map = {
        'off': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_OFF, "Off"),
        '2x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_2X, "2x"),
        '4x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_4X, "4x"),
        '6x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_6X, "6x"),
        '8x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_8X, "8x"),
        '16x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_16X, "16x"),
        '32x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_32X, "32x"),
        '64x': (ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_64X, "64x"),
    }
    
    # Normalize string input to lowercase
    lookup_key = level.lower().strip() if isinstance(level, str) else ""
    
    if lookup_key not in level_map:
        return f"Invalid Tessellation level: '{level}'. Accepted values: 'off', '2x', '4x', '6x', '8x', '16x', '32x', '64x'"

    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_tessellation_support(gpu_index):
            return "Tessellation is not supported."

        gpu = wrapper.gpus[gpu_index]
        adlx_level, level_name = level_map[lookup_key]

        if wrapper.set_tessellation_level(gpu, adlx_level):
            return f"Tessellation level set to {level_name}."
        else:
            return f"Failed to set Tessellation level to {level_name}."
    except Exception as e:
        raise RuntimeError(f"Error setting Tessellation level: {str(e)}")

def get_tessellation_level(gpu_index: int = 0) -> str:
    """
    Get the current level of Tessellation.

    Returns:
        str: A message indicating the current level of Tessellation.
    """
    try:
        wrapper = ADLXAPIWrapper()
        if gpu_index >= len(wrapper.gpus) or gpu_index < 0:
            return f"GPU index {gpu_index} is out of range. Available GPUs: {len(wrapper.gpus)}"
        
        if not check_tessellation_support(gpu_index):
            return "Tessellation is not supported."

        gpu = wrapper.gpus[gpu_index]
        level = wrapper.get_tessellation_level(gpu)
        return f"Current Tessellation level is: {level}."
    except Exception as e:
        raise RuntimeError(f"Error getting Tessellation level: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_tessellation_mode())
        print(set_tessellation_mode('override'))  # Set to override mode
        print(get_tessellation_mode())

        print(get_tessellation_level())
        print(set_tessellation_level('6x'))  # Set Tessellation level to 6x
        print(get_tessellation_level())
            
    except Exception as e:
        print(f"Error: {e}")
