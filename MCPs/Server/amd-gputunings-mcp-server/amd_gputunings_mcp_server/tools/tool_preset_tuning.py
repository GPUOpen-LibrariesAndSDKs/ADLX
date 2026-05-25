# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


##### Helper functions #####
# Current preset functions
def is_current_quiet(gpu_index: int) -> str:
    """Check if Favor Efficiency preset is currently active for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating if Favor Efficiency preset is currently active
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            if not preset_tuning.IsSupportedQuiet():
                return f"Favor Efficiency preset is not supported for GPU {gpu_index}"
            is_current = preset_tuning.IsCurrentQuiet()
            return f"Favor Efficiency preset is currently {'active' if is_current else 'inactive'} for GPU {gpu_index}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error checking current Favor Efficiency preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def is_current_balanced(gpu_index: int) -> str:
    """Check if Balanced preset is currently active for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating if Balanced preset is currently active
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            if not preset_tuning.IsSupportedBalanced():
                return f"Balanced preset is not supported for GPU {gpu_index}"
            is_current = preset_tuning.IsCurrentBalanced()
            return f"Balanced preset is currently {'active' if is_current else 'inactive'} for GPU {gpu_index}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error checking current Balanced preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def is_current_rage(gpu_index: int) -> str:
    """Check if Favor Performance preset is currently active for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating if Favor Performance preset is currently active
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            if not preset_tuning.IsSupportedRage():
                return f"Favor Performance preset is not supported for GPU {gpu_index}"
            is_current = preset_tuning.IsCurrentRage()
            return f"Favor Performance preset is currently {'active' if is_current else 'inactive'} for GPU {gpu_index}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error checking current Favor Performance preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

# Set preset functions
def set_quiet(gpu_index: int) -> str:
    """Set the Favor Efficiency preset for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            # Check if Favor Efficiency preset is supported
            if not preset_tuning.IsSupportedQuiet():
                return f"Favor Efficiency preset is not supported for GPU {gpu_index}"
            
            result = preset_tuning.SetQuiet()
            if result in [0, 1, 2]:
                return f"Favor Efficiency preset set successfully for GPU {gpu_index}"
            else:
                return f"Failed to set Favor Efficiency preset for GPU {gpu_index}. Error code: {result}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting Favor Efficiency preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_balanced(gpu_index: int) -> str:
    """Set the Balanced preset for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            # Check if Balanced preset is supported
            if not preset_tuning.IsSupportedBalanced():
                return f"Balanced preset is not supported for GPU {gpu_index}"
            
            result = preset_tuning.SetBalanced()
            if result in [0, 1, 2]:
                return f"Balanced preset set successfully for GPU {gpu_index}"
            else:
                return f"Failed to set Balanced preset for GPU {gpu_index}. Error code: {result}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting Balanced preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_rage(gpu_index: int) -> str:
    """Set the Favor Performance preset for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            # Check if Favor Performance preset is supported
            if not preset_tuning.IsSupportedRage():
                return f"Favor Performance preset is not supported for GPU {gpu_index}"
            
            result = preset_tuning.SetRage()
            if result in [0, 1, 2]:
                return f"Favor Performance preset set successfully for GPU {gpu_index}"
            else:
                return f"Failed to set Favor Performance preset for GPU {gpu_index}. Error code: {result}"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting Favor Performance preset: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


##### Functions to be exposed for manifest.json #####
def get_preset_tuning_mode(gpu_index: int, mode: str=None) -> str:
    """Get the preset tuning mode for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        mode: Preset mode to check ('Quiet', 'Balanced', 'Rage'), if None, returns all modes
        
    Returns:
        String indicating if the specified preset mode is supported or not
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        output_str = f"Preset tuning is supported for GPU {gpu_index}. "
        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            if mode == 'Quiet':
                output_str += is_current_quiet(gpu_index)
            elif mode == 'Balanced':
                output_str += is_current_balanced(gpu_index)
            elif mode == 'Rage':
                output_str += is_current_rage(gpu_index)
            else:
                output_str += "\n".join([
                    is_current_quiet(gpu_index),
                    is_current_balanced(gpu_index),
                    is_current_rage(gpu_index)
                ])
            return output_str
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting preset tuning mode: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def set_preset_tuning_mode(gpu_index: int, mode: str) -> str:
    """Set the preset tuning mode for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        mode: Preset mode to set ('Quiet', 'Balanced', 'Rage')
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_preset_tuning_supported(gpu):
            return f"Preset tuning is not supported for GPU {gpu_index}"

        preset_tuning = wrapper.get_preset_tuning(gpu)
        if preset_tuning:
            if mode == 'Quiet':
                return set_quiet(gpu_index)
            elif mode == 'Balanced':
                return set_balanced(gpu_index)
            elif mode == 'Rage':
                return set_rage(gpu_index)
            else:
                return f"Error: Unknown preset mode '{mode}'"
        else:
            return f"Preset tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting preset tuning mode: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Example usage
    gpu_index = 1  # Change this to the desired GPU index
    print("=== Preset Tuning Test ===")
    
    print("\n=== Get Preset Tuning Mode ===")
    for mode in ['Quiet', 'Balanced', 'Rage', None]:
        print(f"{mode}: {get_preset_tuning_mode(gpu_index, mode)}")
    
    print("\n=== Set Preset Tuning Mode ===")
    for mode in ['Quiet', 'Balanced', 'Rage']:
        print(f"Setting {mode} preset: {set_preset_tuning_mode(gpu_index, mode)}")