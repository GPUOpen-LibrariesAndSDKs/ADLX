# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


##### Helper functions #####
def _get_vram_tuning_interface(gpu):
    """Get the appropriate VRAM tuning interface (1 or 2)."""
    wrapper = ADLXAPIWrapper()
    
    # Try interface 2 first (post-RDNA)
    try:
        vram_tuning2 = wrapper.get_manual_vram_tuning2(gpu)
        if vram_tuning2:
            return vram_tuning2, 2
    except:
        pass
    
    # Fall back to interface 1 (pre-RDNA)
    try:
        vram_tuning1 = wrapper.get_manual_vram_tuning1(gpu)
        if vram_tuning1:
            return vram_tuning1, 1
    except:
        pass
    
    return None, 0


##### Functions to be exposed for manifest.json #####
# Shared functions (available in both interfaces)
def get_supported_memory_timing_description_list(gpu_index: int) -> str:
    """Get the list of supported memory timing descriptions for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with supported memory timing descriptions
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning:
            if not vram_tuning.IsSupportedMemoryTiming():
                return f"Memory timing is not supported for GPU {gpu_index} (Interface {interface_type})"
            description_list = vram_tuning.GetSupportedMemoryTimingDescriptionList()
            descriptions = []
            for description in description_list:
                descriptions.append(f"{description.GetDescription()}")
            return f"GPU {gpu_index} supported memory timing descriptions (Interface {interface_type}): {', '.join(descriptions)}"
        else:
            return f"Manual VRAM tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting supported memory timing descriptions: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_memory_timing_description(gpu_index: int) -> str:
    """Get the current memory timing description for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with memory timing description
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning:
            if not vram_tuning.IsSupportedMemoryTiming():
                return f"Memory timing is not supported for GPU {gpu_index} (Interface {interface_type})"
            description = vram_tuning.GetMemoryTimingDescription()
            return f"GPU {gpu_index} memory timing description (Interface {interface_type}): {description}"
        else:
            return f"Manual VRAM tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting memory timing description: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_memory_timing_description(gpu_index: int, description: str) -> str:
    """Set the memory timing description for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        description: Memory timing description to set
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning:
            if not vram_tuning.IsSupportedMemoryTiming():
                return f"Memory timing is not supported for GPU {gpu_index} (Interface {interface_type})"
            result = vram_tuning.SetMemoryTimingDescription(wrapper.memory_timing_description[description])
            if result in [0, 1, 2]:
                return f"GPU {gpu_index} memory timing description ({description}) set successfully (Interface {interface_type})"
            else:
                return f"Failed to set GPU {gpu_index} memory timing description. Error code: {result}"
        else:
            return f"Manual VRAM tuning is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting memory timing description: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

# Interface 1 functions (pre-RDNA)
def get_vram_tuning_ranges(gpu_index: int) -> str:
    """Get the VRAM tuning ranges (frequency and voltage) for a GPU using Interface 1.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with VRAM tuning ranges information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 1:
            frequency_range, voltage_range = vram_tuning.GetVRAMTuningRanges()
            return f"GPU {gpu_index} VRAM tuning ranges (Interface 1) - Frequency: {frequency_range}, Voltage: {voltage_range}"
        else:
            return f"Manual VRAM tuning Interface 1 is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting VRAM tuning ranges: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_vram_tuning_states(gpu_index: int, state_index: int = -1) -> str:
    """Get the current VRAM tuning states for a GPU using Interface 1.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        state_index: Index of the state to retrieve (-1 for all states)
        
    Returns:
        String with VRAM tuning states information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 1:
            states = vram_tuning.GetVRAMTuningStates()
            
            # Return specific state if state_index is provided
            if state_index >= 0:
                if state_index >= len(states):
                    return f"Error: State index {state_index} is out of range. Available states: {len(states)}"
                state = states[state_index]
                frequency = state.GetFrequency()
                voltage = state.GetVoltage()
                return f"GPU {gpu_index} VRAM tuning state {state_index} (Interface 1): Freq={frequency}MHz, Volt={voltage}mV"
            
            # Return all states with their frequency and voltage values
            states_info = []
            for i, state in enumerate(states):
                frequency = state.GetFrequency()
                voltage = state.GetVoltage()
                states_info.append(f"State {i}: Freq={frequency}MHz, Volt={voltage}mV")
            return f"GPU {gpu_index} all VRAM tuning states (Interface 1): {'; '.join(states_info)}"
        else:
            return f"Manual VRAM tuning Interface 1 is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting VRAM tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_vram_tuning_states(gpu_index: int, states: dict[int, tuple[int, int]]) -> str:
    """Set the VRAM tuning states for a GPU using Interface 1.

    Args:
        gpu_index: Index of the GPU (0-based)
        states: Dictionary with state indices (0-based) as keys and (frequency, voltage) tuples as values

    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 1:
            # Get empty states list to modify
            states_list = vram_tuning.GetVRAMTuningStates()
            # Set the specified states
            for state_index, (frequency, voltage) in states.items():
                if state_index >= 0 and state_index < len(states_list):
                    states_list[state_index].SetFrequency(frequency)
                    states_list[state_index].SetVoltage(voltage)
                else:
                    return f"Error: State index {state_index} is out of range. Available states: {len(states_list)}"
            # Validate the states before setting
            error_index = vram_tuning.IsValidVRAMTuningStates(states_list)
            if error_index != -1:
                return f"Error: Invalid VRAM tuning state at index {error_index}"
            # Set the states
            result = vram_tuning.SetVRAMTuningStates(states_list)
            
            if result in [0, 1, 2]:
                return f"GPU {gpu_index} VRAM tuning states set successfully (Interface 1)"
            else:
                return f"Failed to set GPU {gpu_index} VRAM tuning states. Error code: {result}"
        else:
            return f"Manual VRAM tuning Interface 1 is not supported for GPU {gpu_index}"

    except Exception as e:
        log_with_color(f"Error setting VRAM tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

# Interface 2 functions (post-RDNA)
def get_max_vram_frequency_range(gpu_index: int) -> str:
    """Get the maximum VRAM frequency range for a GPU using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with maximum VRAM frequency range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 2:
            max_freq_range = vram_tuning.GetMaxVRAMFrequencyRange()
            return f"GPU {gpu_index} maximum VRAM frequency range (Interface 2): {max_freq_range}"
        else:
            return f"Manual VRAM tuning Interface 2 is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting maximum VRAM frequency range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_max_vram_frequency(gpu_index: int, default: bool=False) -> str:
    """Get the current or default maximum VRAM frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default maximum frequency; otherwise, get current maximum frequency
        
    Returns:
        String with current or default maximum VRAM frequency
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 2:
            if default:
                max_freq = vram_tuning.GetMaxVRAMFrequencyDefault()
                return f"GPU {gpu_index} default maximum VRAM frequency (Interface 2): {max_freq}MHz"
            else:
                max_freq = vram_tuning.GetMaxVRAMFrequency()
                return f"GPU {gpu_index} current maximum VRAM frequency (Interface 2): {max_freq}MHz"
        else:
            return f"Manual VRAM tuning Interface 2 is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting maximum VRAM frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_max_vram_frequency(gpu_index: int, max_freq: int) -> str:
    """Set the maximum VRAM frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        max_freq: Maximum frequency in MHz
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_vram_tuning_supported(gpu):
            return f"Error: Manual VRAM tuning is not supported for GPU {gpu_index}"

        vram_tuning, interface_type = _get_vram_tuning_interface(gpu)
        if vram_tuning and interface_type == 2:
            # Check if frequency is within valid range
            max_freq_range = vram_tuning.GetMaxVRAMFrequencyRange()
            range_min = max_freq_range["min_value"]
            range_max = max_freq_range["max_value"]
            
            if max_freq < range_min or max_freq > range_max:
                return f"Error: Maximum VRAM frequency {max_freq}MHz is out of range. Valid range: {range_min}MHz - {range_max}MHz"
            
            result = vram_tuning.SetMaxVRAMFrequency(max_freq)
            if result in [0, 1, 2]:
                return f"GPU {gpu_index} maximum VRAM frequency set to {max_freq}MHz (Interface 2)"
            else:
                return f"Failed to set GPU {gpu_index} maximum VRAM frequency. Error code: {result}"
        else:
            return f"Manual VRAM tuning Interface 2 is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting maximum VRAM frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Example usage
    gpu_index = 1  # Change this to the desired GPU index
    print("=== Manual VRAM Tuning Test ===")
    
    print("\n=== Shared Functions (both interfaces) ===")
    print(get_memory_timing_description(gpu_index))
    print(set_memory_timing_description(gpu_index, "MEMORYTIMING_DEFAULT"))
    print(get_supported_memory_timing_description_list(gpu_index))
    
    print("\n=== Interface 1 Functions (pre-RDNA) ===")
    print(get_vram_tuning_ranges(gpu_index))
    print(get_vram_tuning_states(gpu_index))
    print(set_vram_tuning_states(gpu_index, {0: (1500, 950), 1: (1600, 1000)}))  # Set state 0 to 1500MHz/950mV and state 1 to 1600MHz/1000mV
    
    print("\n=== Interface 2 Functions (post-RDNA) ===")
    print(get_max_vram_frequency_range(gpu_index))
    print(get_max_vram_frequency(gpu_index))  # Get current maximum VRAM frequency
    print(get_max_vram_frequency(gpu_index, default=True))  # Get default maximum VRAM frequency
    print(set_max_vram_frequency(gpu_index, 2600))  # Set maximum VRAM frequency to 2600MHz