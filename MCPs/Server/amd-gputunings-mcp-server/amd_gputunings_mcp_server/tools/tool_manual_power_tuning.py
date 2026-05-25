# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


##### helper functions #####
def _get_graphics_tuning_support_str(gpu_index: int) -> str:
    """Get the support string for manual graphics tuning for a specific GPU."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    
    if gpu_index >= len(gpus) or gpu_index < 0:
        return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
    
    gpu = gpus[gpu_index]
    # return empty string if manual power tuning is not supported, since the caller will handle the error
    return f"Manual power tuning is supported for GPU {gpu_index}. " if wrapper.is_manual_power_tuning_supported(gpu) else ""

# Power Limit functions
def get_power_limit_range(gpu_index: int) -> str:
    """Get the power limit range for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with power limit range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            power_limit_range = power_tuning.GetPowerLimitRange()
            return f"GPU {gpu_index} power limit range: {power_limit_range}"
        else:
            return f"get_power_limit_range is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting power limit range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_power_limit(gpu_index: int, default: bool=False) -> str:
    """Get the current or default power limit for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default limit; otherwise, get current limit
        
    Returns:
        String with current or default power limit
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            if default:
                power_limit = power_tuning.GetPowerLimitDefault()
                return f"GPU {gpu_index} default power limit: {power_limit}"
            else:
                power_limit = power_tuning.GetPowerLimit()
                return f"GPU {gpu_index} current power limit: {power_limit}"
        else:
            return f"get_power_limit is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting power limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_power_limit(gpu_index: int, power_limit: int=None) -> str:
    """Set the power limit for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        power_limit: Power limit percentage. If None, set to default limit.
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            if power_limit is None:
                # Set to default power limit
                power_limit = power_tuning.GetPowerLimitDefault()
                if power_limit is None:
                    return f"Failed to reset GPU {gpu_index} power limit to default."
                result = power_tuning.SetPowerLimit(power_limit)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} power limit reset to default {power_limit}"
                else:
                    return f"Failed to reset GPU {gpu_index} power limit to default. Error code: {result}"
            else:
                # Check if power limit is within valid range
                power_limit_range = power_tuning.GetPowerLimitRange()
                if power_limit_range is None:
                    return f"Failed to set GPU {gpu_index} power limit."
                range_min = power_limit_range["min_value"]
                range_max = power_limit_range["max_value"]
                
                if power_limit < range_min or power_limit > range_max:
                    return f"Error: Power limit {power_limit} is out of range. Valid range: {range_min} - {range_max}"
                
                result = power_tuning.SetPowerLimit(power_limit)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} power limit set to {power_limit}"
                else:
                    return f"Failed to set GPU {gpu_index} power limit. Error code: {result}"
        else:
            return f"set_power_limit is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting power limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

# TDC Limit functions
def get_tdc_limit_range(gpu_index: int) -> str:
    """Get the TDC limit range for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with TDC limit range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            # Check if TDC limit is supported first
            if not power_tuning.IsSupportedTDCLimit():
                return f"TDC limit is not supported for GPU {gpu_index}"
            
            tdc_limit_range = power_tuning.GetTDCLimitRange()
            return f"GPU {gpu_index} TDC limit range: {tdc_limit_range}"
        else:
            return f"get_tdc_limit_range is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting TDC limit range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_tdc_limit(gpu_index: int, default: bool=False) -> str:
    """Get the current or default TDC limit for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default limit; otherwise, get current limit
        
    Returns:
        String with current or default TDC limit
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            # Check if TDC limit is supported first
            if not power_tuning.IsSupportedTDCLimit():
                return f"TDC limit is not supported for GPU {gpu_index}"
            
            if default:
                tdc_limit = power_tuning.GetTDCLimitDefault()
                return f"GPU {gpu_index} default TDC limit: {tdc_limit}"
            else:
                tdc_limit = power_tuning.GetTDCLimit()
                return f"GPU {gpu_index} current TDC limit: {tdc_limit}"
        else:
            return f"get_tdc_limit is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting TDC limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_tdc_limit(gpu_index: int, tdc_limit: int=None) -> str:
    """Set the TDC limit for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        tdc_limit: TDC limit in Amperes. If None, set to default limit.
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_power_tuning_supported(gpu):
            return f"Manual power tuning is not supported for GPU {gpu_index}"

        power_tuning = wrapper.get_manual_power_tuning(gpu)
        
        if power_tuning:
            # Check if TDC limit is supported first
            if not power_tuning.IsSupportedTDCLimit():
                return f"TDC limit is not supported for GPU {gpu_index}"
            
            if tdc_limit is None:
                # Set to default TDC limit
                tdc_limit = power_tuning.GetTDCLimitDefault()
                if tdc_limit is None:
                    return f"Failed to reset GPU {gpu_index} TDC limit to default."
                result = power_tuning.SetTDCLimit(tdc_limit)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} TDC limit reset to default {tdc_limit}"
                else:
                    return f"Failed to reset GPU {gpu_index} TDC limit to default. Error code: {result}"
            else:
                # Check if TDC limit is within valid range
                tdc_limit_range = power_tuning.GetTDCLimitRange()
                if tdc_limit_range is None:
                    return f"Failed to set GPU {gpu_index} TDC limit."
                range_min = tdc_limit_range["min_value"]
                range_max = tdc_limit_range["max_value"]
                
                if tdc_limit < range_min or tdc_limit > range_max:
                    return f"Error: TDC limit {tdc_limit} is out of range. Valid range: {range_min} - {range_max}"
                
                result = power_tuning.SetTDCLimit(tdc_limit)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} TDC limit set to {tdc_limit}"
                else:
                    return f"Failed to set GPU {gpu_index} TDC limit. Error code: {result}"
        else:
            return f"set_tdc_limit is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting TDC limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


##### Functions to be exposed for manifest.json #####
def get_manual_power_tuning_range(gpu_index: int, setting: str) -> str:
    """Get the range of a specific manual power tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the range ('power_limit', 'tdc_limit')
        
    Returns:
        String with the range information
    """
    output_str = _get_graphics_tuning_support_str(gpu_index)
    try:
        if setting == 'power_limit':
            output_str += get_power_limit_range(gpu_index)
        elif setting == 'tdc_limit':
            output_str += get_tdc_limit_range(gpu_index)
        else:
            output_str += f"Error: Unsupported setting '{setting}'. Available settings: 'power_limit', 'tdc_limit'"
        return output_str
            
    except Exception as e:
        log_with_color(f"Error getting manual power tuning range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def get_manual_power_tuning_state(gpu_index: int, setting: str) -> str:
    """Get the current state of a specific manual power tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the state ('power_limit', 'tdc_limit')
        
    Returns:
        String with the specific state information
    """
    output_str = _get_graphics_tuning_support_str(gpu_index)
    try:
        if setting == 'power_limit':
            output_str += get_power_limit(gpu_index)
        elif setting == 'tdc_limit':
            output_str += get_tdc_limit(gpu_index)
        else:
            output_str += f"Error: Unsupported setting '{setting}'. Available settings: 'power_limit', 'tdc_limit'"
        return output_str
            
    except Exception as e:
        log_with_color(f"Error getting manual power tuning state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def set_manual_power_tuning_state(gpu_index: int, setting: str, value: int=None) -> str:
    """Set the state of a specific manual power tuning setting for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to set ('power_limit', 'tdc_limit')
        value: The value to set for the specified setting.
               If value is None, it will set the default state for the specified setting.

    Returns:
        String indicating the result of the operation
    """
    try:
        if setting == 'power_limit':
            return set_power_limit(gpu_index, value)
        elif setting == 'tdc_limit':
            return set_tdc_limit(gpu_index, value)
        else:
            return f"Error: Unsupported setting '{setting}'. Available settings: 'power_limit', 'tdc_limit'"
            
    except Exception as e:
        log_with_color(f"Error setting manual power tuning state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Example usage - using only functions exposed for manifest.json
    gpu_index = 1  # Change this to the desired GPU index
    print("=== Manual Power Tuning Test ===")
    
    print("\n=== Get Tuning Ranges ===")
    print(get_manual_power_tuning_range(gpu_index, 'power_limit'))
    print(get_manual_power_tuning_range(gpu_index, 'tdc_limit'))
    
    print("\n=== Get Current States ===")
    print(get_manual_power_tuning_state(gpu_index, 'power_limit'))
    print(get_manual_power_tuning_state(gpu_index, 'tdc_limit'))
    
    print("\n=== Set Tuning States ===")
    print(set_manual_power_tuning_state(gpu_index, 'power_limit', -10))  # Set to -10
    print(set_manual_power_tuning_state(gpu_index, 'tdc_limit', 150))  # Set to 150A
    
    print("\n=== Reset to Defaults ===")
    print(set_manual_power_tuning_state(gpu_index, 'power_limit', None))  # Reset to default
    print(set_manual_power_tuning_state(gpu_index, 'tdc_limit', None))  # Reset to default