# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


def is_gpu_tuning_default(gpu_index: int) -> str:
    """Check if GPU tuning settings are at default for a specific GPU.
    
    Use this function to verify if all GPU tuning settings (graphics, VRAM, fan, power) 
    are currently at their factory default values. This is useful for determining if 
    any custom tuning has been applied to the GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating whether GPU tuning settings are at default
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        
        # Check if GPU tuning settings are at default
        is_default = wrapper.is_gpu_tuning_default(gpu)
        
        status = "at factory defaults" if is_default else "modified from defaults"
        return f"GPU {gpu_index} tuning settings are {status}"
        
    except Exception as e:
        log_with_color(f"Error checking if GPU tuning is at default: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def reset_gpu_tuning(gpu_index: int) -> str:
    """Reset GPU tuning settings to factory defaults for a specific GPU.
    
    Use this function to restore all GPU tuning settings (graphics, VRAM, fan, power) 
    to their original factory default values. This will undo any custom tuning that 
    has been applied to the GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating the result of the reset operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        
        # Reset GPU tuning settings to factory defaults
        result = wrapper.reset_gpu_tuning(gpu)
        
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} tuning settings successfully reset to factory defaults"
        else:
            return f"Failed to reset GPU {gpu_index} tuning settings to factory defaults"
        
    except Exception as e:
        log_with_color(f"Error resetting GPU tuning to defaults: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Test the functions
    print("=== GPU Tuning Services Test ===")
    
    # Test with GPU 0
    gpu_index = 1
    
    print(f"\n=== GPU {gpu_index} Default Status Check ===")
    print(is_gpu_tuning_default(gpu_index))
    
    print(f"\n=== GPU {gpu_index} Reset to Defaults ===")
    print(reset_gpu_tuning(gpu_index))
    
    print(f"\n=== GPU {gpu_index} Default Status Check After Reset ===")
    print(is_gpu_tuning_default(gpu_index))
