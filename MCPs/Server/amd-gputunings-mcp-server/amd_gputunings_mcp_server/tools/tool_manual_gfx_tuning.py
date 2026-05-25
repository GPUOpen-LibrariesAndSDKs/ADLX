# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


##### Helper functions #####
def _get_graphics_tuning_support_str(gpu_index: int) -> str:
    """Get the support string for manual graphics tuning for a specific GPU."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    
    if gpu_index >= len(gpus) or gpu_index < 0:
        return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
    
    gpu = gpus[gpu_index]
    # return empty string if manual graphics tuning is not supported, since the caller will handle the error
    return f"Manual graphics tuning is supported for GPU {gpu_index}. " if wrapper.is_manual_gfx_tuning_supported(gpu) else ""

def _get_graphics_tuning_interface(gpu):
    """Get the appropriate graphics tuning interface (1 or 2)."""
    wrapper = ADLXAPIWrapper()
    
    # Try interface 2 first (post-RDNA)
    try:
        gfx_tuning2 = wrapper.get_manual_gfx_tuning2(gpu)
        if gfx_tuning2:
            return gfx_tuning2, 2
    except:
        pass
    
    # Fall back to interface 1 (pre-RDNA)
    try:
        gfx_tuning1 = wrapper.get_manual_gfx_tuning1(gpu)
        if gfx_tuning1:
            return gfx_tuning1, 1
    except:
        pass
    
    return None, 0

# Interface 1 functions (pre-RDNA)
def get_gpu_tuning_ranges(gpu_index: int) -> str:
    """Get the GPU tuning ranges (frequency and voltage) for a GPU using Interface 1.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with GPU tuning ranges information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 1:
            frequency_range, voltage_range = graphics_tuning.GetGPUTuningRanges()
            return f"GPU {gpu_index} current tuning ranges (pre-RDNA) - Frequency: {frequency_range}, Voltage: {voltage_range}"
        else:
            return f"get_gpu_tuning_ranges is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU tuning ranges: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_tuning_states(gpu_index: int, default: bool=False) -> str:
    """Get the current or default GPU tuning states for a GPU using Interface 1.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default states; otherwise, get current states
        
    Returns:
        String with current or default GPU tuning states information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 1:
            if default:
                # Get default states - Interface 1 doesn't have a direct GetDefaultStates method,
                # so we'll get the current states which should represent defaults if not modified
                states = graphics_tuning.GetGPUTuningStates()
                states_info = []
                for i, state in enumerate(states):
                    frequency = state.GetFrequency()
                    voltage = state.GetVoltage()
                    states_info.append(f"State {i}: Freq={frequency}MHz, Volt={voltage}mV")
                return f"GPU {gpu_index} default tuning states (pre-RDNA): {'; '.join(states_info)}"
            else:
                states = graphics_tuning.GetGPUTuningStates()
                # Return all states with their frequency and voltage values
                states_info = []
                for i, state in enumerate(states):
                    frequency = state.GetFrequency()
                    voltage = state.GetVoltage()
                    states_info.append(f"State {i}: Freq={frequency}MHz, Volt={voltage}mV")
                return f"GPU {gpu_index} current tuning states (pre-RDNA): {'; '.join(states_info)}"
        else:
            return f"get_gpu_tuning_states is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_gpu_tuning_states(gpu_index: int, states: dict[int, tuple[int, int]]) -> str:
    """Set the GPU tuning states for a GPU using Interface 1.

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
        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        
        if graphics_tuning and interface_type == 1:
            # Get current states list to modify
            states_list = graphics_tuning.GetGPUTuningStates()
            # Set the specified states
            for state_index, (frequency, voltage) in states.items():
                if state_index >= 0 and state_index < len(states_list):
                    states_list[state_index].SetFrequency(frequency)
                    states_list[state_index].SetVoltage(voltage)
                else:
                    return f"Error: State index {state_index} is out of range. Available states: {len(states_list)}"
            # Validate the states before setting
            error_index = graphics_tuning.IsValidGPUTuningStates(states_list)
            if error_index != -1:
                return f"Error: Invalid tuning state at index {error_index}"
            # Set the states
            result = graphics_tuning.SetGPUTuningStates(states_list)
            
            if result in [0, 1, 2]:
                return f"GPU {gpu_index} tuning states set successfully (pre-RDNA)"
            else:
                return f"Failed to set GPU {gpu_index} tuning states. Error code: {result}"
        else:
            return f"set_gpu_tuning_states is not supported for GPU {gpu_index}"

    except Exception as e:
        log_with_color(f"Error setting GPU tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

# Interface 2 functions (post-RDNA)
def get_gpu_min_frequency_range(gpu_index: int) -> str:
    """Get the GPU minimum frequency range for a GPU using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with GPU minimum frequency range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            min_freq_range = graphics_tuning.GetGPUMinFrequencyRange()
            return f"GPU {gpu_index} minimum frequency range (post-RDNA): {min_freq_range}"
        else:
            return f"get_gpu_min_frequency_range is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU minimum frequency range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_min_frequency(gpu_index: int, default: bool=False) -> str:
    """Get the current or default GPU minimum frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default frequency; otherwise, get current frequency
        
    Returns:
        String with current or default GPU minimum frequency
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            if default:
                min_freq = graphics_tuning.GetGPUMinFrequencyDefault()
                return f"GPU {gpu_index} default minimum frequency (post-RDNA): {min_freq}MHz"
            else:
                min_freq = graphics_tuning.GetGPUMinFrequency()
                return f"GPU {gpu_index} current minimum frequency (post-RDNA): {min_freq}MHz"
        else:
            return f"get_gpu_min_frequency is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU minimum frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_gpu_min_frequency(gpu_index: int, min_freq: int=None) -> str:
    """Set the GPU minimum frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        min_freq: Minimum frequency in MHz. If None, set to default frequency.
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        
        if graphics_tuning and interface_type == 2:
            if min_freq is None:
                # Set to default frequency
                min_freq = graphics_tuning.GetGPUMinFrequencyDefault()
                if min_freq is None:
                    return f"Failed to reset GPU {gpu_index} minimum frequency to default."
                result = graphics_tuning.SetGPUMinFrequency(min_freq)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} minimum frequency reset to default {min_freq}MHz (post-RDNA)"
                else:
                    return f"Failed to reset GPU {gpu_index} minimum frequency to default. Error code: {result}"
            else:
                # Check if frequency is within valid range
                min_freq_range = graphics_tuning.GetGPUMinFrequencyRange()
                if min_freq_range is None:
                    return f"Failed to set GPU {gpu_index} minimum frequency."
                range_min = min_freq_range["min_value"]
                range_max = min_freq_range["max_value"]
                if min_freq < range_min or min_freq > range_max:
                    return f"Error: Minimum frequency {min_freq}MHz is out of range. Valid range: {range_min}MHz - {range_max}MHz"
                # Set the minimum frequency
                result = graphics_tuning.SetGPUMinFrequency(min_freq)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} minimum frequency set to {min_freq}MHz (post-RDNA)"
                else:
                    return f"Failed to set GPU {gpu_index} minimum frequency. Error code: {result}"
        else:
            return f"set_gpu_min_frequency is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting GPU minimum frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_max_frequency_range(gpu_index: int) -> str:
    """Get the GPU maximum frequency range for a GPU using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with GPU maximum frequency range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            max_freq_range = graphics_tuning.GetGPUMaxFrequencyRange()
            return f"GPU {gpu_index} maximum frequency range (post-RDNA): {max_freq_range}"
        else:
            return f"get_gpu_max_frequency_range is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU maximum frequency range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_max_frequency(gpu_index: int, default: bool=False) -> str:
    """Get the current or default GPU maximum frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default frequency; otherwise, get current frequency
        
    Returns:
        String with current or default GPU maximum frequency
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            if default:
                max_freq = graphics_tuning.GetGPUMaxFrequencyDefault()
                return f"GPU {gpu_index} default maximum frequency (post-RDNA): {max_freq}MHz"
            else:
                max_freq = graphics_tuning.GetGPUMaxFrequency()
                return f"GPU {gpu_index} current maximum frequency (post-RDNA): {max_freq}MHz"
        else:
            return f"get_gpu_max_frequency is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU maximum frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_gpu_max_frequency(gpu_index: int, max_freq: int=None) -> str:
    """Set the GPU maximum frequency using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        max_freq: Maximum frequency in MHz. If None, set to default frequency.
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        
        if graphics_tuning and interface_type == 2:
            if max_freq is None:
                # Set to default frequency
                max_freq = graphics_tuning.GetGPUMaxFrequencyDefault()
                if max_freq is None:
                    return f"Failed to reset GPU {gpu_index} maximum frequency to default."
                result = graphics_tuning.SetGPUMaxFrequency(max_freq)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} maximum frequency reset to default {max_freq}MHz (post-RDNA)"
                else:
                    return f"Failed to reset GPU {gpu_index} maximum frequency to default. Error code: {result}"
            else:
                # Check if frequency is within valid range
                max_freq_range = graphics_tuning.GetGPUMaxFrequencyRange()
                if max_freq_range is None:
                    return f"Failed to set GPU {gpu_index} maximum frequency."
                range_min = max_freq_range["min_value"]
                range_max = max_freq_range["max_value"]
                if max_freq < range_min or max_freq > range_max:
                    return f"Error: Maximum frequency {max_freq}MHz is out of range. Valid range: {range_min}MHz - {range_max}MHz"
                # Set the maximum frequency
                result = graphics_tuning.SetGPUMaxFrequency(max_freq)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} maximum frequency set to {max_freq}MHz (post-RDNA)"
                else:
                    return f"Failed to set GPU {gpu_index} maximum frequency. Error code: {result}"
        else:
            return f"set_gpu_max_frequency is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting GPU maximum frequency: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_voltage_range(gpu_index: int) -> str:
    """Get the GPU voltage range for a GPU using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with GPU voltage range information
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            voltage_range = graphics_tuning.GetGPUVoltageRange()
            return f"GPU {gpu_index} voltage range (post-RDNA): {voltage_range}"
        else:
            return f"get_gpu_voltage_range is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU voltage range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_gpu_voltage(gpu_index: int, default: bool=False) -> str:
    """Get the current or default GPU voltage using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        default: If True, get default voltage; otherwise, get current voltage
        
    Returns:
        String with current or default GPU voltage
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_manual_gfx_tuning_supported(gpu):
            return f"Manual graphics tuning is not supported for GPU {gpu_index}"

        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        if graphics_tuning and interface_type == 2:
            if default:
                voltage = graphics_tuning.GetGPUVoltageDefault()
                return f"GPU {gpu_index} default voltage (post-RDNA): {voltage}mV"
            else:
                voltage = graphics_tuning.GetGPUVoltage()
                return f"GPU {gpu_index} current voltage (post-RDNA): {voltage}mV"
        else:
            return f"get_gpu_voltage is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting GPU voltage: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_gpu_voltage(gpu_index: int, voltage: int=None) -> str:
    """Set the GPU voltage using Interface 2.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        voltage: GPU voltage in mV. If None, set to default voltage.
        
    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        graphics_tuning, interface_type = _get_graphics_tuning_interface(gpu)
        
        if graphics_tuning and interface_type == 2:
            if voltage is None:
                # Set to default voltage
                voltage = graphics_tuning.GetGPUVoltageDefault()
                if voltage is None:
                    return f"Failed to reset GPU {gpu_index} voltage to default."
                result = graphics_tuning.SetGPUVoltage(voltage)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} voltage reset to default {voltage}mV (post-RDNA)"
                else:
                    return f"Failed to reset GPU {gpu_index} voltage to default. Error code: {result}"
            else:
                # Check if voltage is within valid range
                voltage_range = graphics_tuning.GetGPUVoltageRange()
                if voltage_range is None:
                    return f"Failed to set GPU {gpu_index} voltage."
                range_min = voltage_range["min_value"]
                range_max = voltage_range["max_value"]
                if voltage < range_min or voltage > range_max:
                    return f"Error: Voltage {voltage}mV is out of range. Valid range: {range_min}mV - {range_max}mV"
                # Set the voltage
                result = graphics_tuning.SetGPUVoltage(voltage)
                if result in [0, 1, 2]:
                    return f"GPU {gpu_index} voltage set to {voltage}mV (post-RDNA)"
                else:
                    return f"Failed to set GPU {gpu_index} voltage. Error code: {result}"
        else:
            return f"set_gpu_voltage is not supported for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error setting GPU voltage: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


##### Functions to be exposed for manifest.json #####
def get_manual_graphics_tuning_range(gpu_index: int, setting: str) -> str:
    """Get the range of a specific manual graphics tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the range ('gpu_tuning', 'min_frequency', 'max_frequency', 'voltage')
        
    Returns:
        String with the range information
    """
    output_str = _get_graphics_tuning_support_str(gpu_index)
    try:
        if setting == 'gpu_tuning':
            output_str += get_gpu_tuning_ranges(gpu_index)
        elif setting == 'min_frequency':
            output_str += get_gpu_min_frequency_range(gpu_index)
        elif setting == 'max_frequency':
            output_str += get_gpu_max_frequency_range(gpu_index)
        elif setting == 'voltage':
            output_str += get_gpu_voltage_range(gpu_index)
        else:
            output_str += f"Error: Unsupported setting '{setting}'. Available settings: 'gpu_tuning', 'min_frequency', 'max_frequency', 'voltage'"
        return output_str
            
    except Exception as e:
        log_with_color(f"Error getting manual graphics tuning range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def get_manual_graphics_tuning_state(gpu_index: int, setting: str) -> str:
    """Get the current state of a specific manual graphics tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the state ('gpu_tuning', 'min_frequency', 'max_frequency', 'voltage')
        
    Returns:
        String with the specific state information
    """
    output_str = _get_graphics_tuning_support_str(gpu_index)
    try:
        if setting == 'gpu_tuning':
            output_str += get_gpu_tuning_states(gpu_index)
        elif setting == 'min_frequency':
            output_str += get_gpu_min_frequency(gpu_index)
        elif setting == 'max_frequency':
            output_str += get_gpu_max_frequency(gpu_index)
        elif setting == 'voltage':
            output_str += get_gpu_voltage(gpu_index)
        else:
            output_str += f"Error: Unsupported setting '{setting}'. Available settings: 'gpu_tuning', 'min_frequency', 'max_frequency', 'voltage'"
        return output_str
            
    except Exception as e:
        log_with_color(f"Error getting manual graphics tuning state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def set_manual_graphics_tuning_state(gpu_index: int, setting: str, value: dict[int, tuple[int, int]] | int=None) -> str:
    """Set the state of a specific manual graphics tuning setting for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to set ('gpu_tuning', 'min_frequency', 'max_frequency', 'voltage')
        value: The value to set for the specified setting.
               If setting is 'gpu_tuning', a dictionary with state indices as keys and (frequency, voltage) tuples as values.
               If setting is 'min_frequency', 'max_frequency' or 'voltage', an integer value to set.
               If value is None, it will set the default state for the specified setting.

    Returns:
        String indicating the result of the operation
    """
    try:
        if setting == 'gpu_tuning':
            if value is None:
                return "Error: 'gpu_tuning' setting requires a value to set. Provide a dictionary with state indices and (frequency, voltage) tuples."
            else:
                return set_gpu_tuning_states(gpu_index, value)
        elif setting == 'min_frequency':
            return set_gpu_min_frequency(gpu_index, value)
        elif setting == 'max_frequency':
            return set_gpu_max_frequency(gpu_index, value)
        elif setting == 'voltage':
            return set_gpu_voltage(gpu_index, value)
        else:
            return f"Error: Unsupported setting '{setting}'. Available settings: 'gpu_tuning', 'min_frequency', 'max_frequency', 'voltage'"
            
    except Exception as e:
        log_with_color(f"Error setting manual graphics tuning state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Example usage
    gpu_index = 1  # Change this to the desired GPU index
    print("=== Manual Graphics Tuning Test ===")
    
    print("\n=== Get Tuning Ranges ===")
    print(get_manual_graphics_tuning_range(gpu_index, 'gpu_tuning'))
    print(get_manual_graphics_tuning_range(gpu_index, 'min_frequency'))
    print(get_manual_graphics_tuning_range(gpu_index, 'max_frequency'))
    print(get_manual_graphics_tuning_range(gpu_index, 'voltage'))
    
    print("\n=== Get Current States ===")
    print(get_manual_graphics_tuning_state(gpu_index, 'gpu_tuning'))
    print(get_manual_graphics_tuning_state(gpu_index, 'min_frequency'))
    print(get_manual_graphics_tuning_state(gpu_index, 'max_frequency'))
    print(get_manual_graphics_tuning_state(gpu_index, 'voltage'))
    
    print("\n=== Set Tuning States ===")
    print(set_manual_graphics_tuning_state(gpu_index, 'gpu_tuning', {0: (1500, 950), 1: (1600, 1000)}))  # Set state 0 to 1500MHz/950mV and state 1 to 1600MHz/1000mV
    print(set_manual_graphics_tuning_state(gpu_index, 'min_frequency', 800))  # Set to 800MHz
    print(set_manual_graphics_tuning_state(gpu_index, 'max_frequency', 2000))  # Set to 2000MHz
    print(set_manual_graphics_tuning_state(gpu_index, 'voltage', -100))  # Set to -100mV
    
    print("\n=== Reset to Defaults ===")
    print(set_manual_graphics_tuning_state(gpu_index, 'min_frequency', None))  # Reset to default
    print(set_manual_graphics_tuning_state(gpu_index, 'max_frequency', None))  # Reset to default
    print(set_manual_graphics_tuning_state(gpu_index, 'voltage', None))  # Reset to default