# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


##### Helper functions #####
def _validate_gpu_index(gpu_index: int, gpus) -> str:
    """Validate GPU index and return error message if invalid."""
    if gpu_index >= len(gpus) or gpu_index < 0:
        return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
    return None

def _get_fan_tuning_support_str(gpu_index: int):
    """Get the manual fan tuning support string for the specified GPU."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    
    # Validate GPU index
    error_msg = _validate_gpu_index(gpu_index, gpus)
    if error_msg:
        return error_msg
    
    gpu = gpus[gpu_index]
    # return empty string if manual fan tuning is not supported, since the caller will handle the error
    return f"Manual fan tuning is supported for GPU {gpu_index}. " if wrapper.is_manual_fan_tuning_supported(gpu) else ""

def _get_fan_tuning_interface(gpu_index: int):
    """Get the manual fan tuning interface for the specified GPU."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    
    # Validate GPU index
    error_msg = _validate_gpu_index(gpu_index, gpus)
    if error_msg:
        return None, error_msg
    
    gpu = gpus[gpu_index]
    if not wrapper.is_manual_fan_tuning_supported(gpu):
        return None, f"Manual fan tuning is not supported for GPU {gpu_index}"
    
    fan_tuning = wrapper.get_manual_fan_tuning(gpu)
    if not fan_tuning:
        return None, f"Manual fan tuning is not available for GPU {gpu_index}"
    
    return fan_tuning, None

##### Fan Tuning Functions #####
def get_fan_tuning_ranges(gpu_index: int) -> str:
    """Get the fan tuning ranges for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with fan tuning range information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        range_info = fan_tuning.GetFanTuningRanges()
        return f"GPU {gpu_index} fan tuning range: {range_info}"
        
    except Exception as e:
        log_with_color(f"Error getting fan tuning ranges: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_fan_tuning_states(gpu_index: int) -> str:
    """Get the current fan tuning states for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with fan tuning states information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        states = fan_tuning.GetFanTuningStates()
        out: str = ""
        for (index, state) in enumerate(states):
            out += f"State {index}: Speed={state.GetFanSpeed()}, Temperature={state.GetTemperature()}\n"
        return f"GPU {gpu_index} fan tuning states:\n{out}"
        
    except Exception as e:
        log_with_color(f"Error getting fan tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_fan_tuning_states(gpu_index: int, states: dict[str, tuple[int, int]] = None) -> str:
    """Set the fan tuning states for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        states: Dictionary with state indices as keys and (fan_speed, temperature) tuples as values.
                If None, sets to default states.

    Returns:
        String indicating the result of the operation
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if states is None:
            default_states = fan_tuning.GetFanTuningStates()
            result = fan_tuning.SetFanTuningStates(default_states)
        else:
            states_list = fan_tuning.GetFanTuningStates()
            ranges = fan_tuning.GetFanTuningRanges()
            
            for state_index, (fan_speed, temperature) in states.items():
                state_index = int(state_index)  # Convert key to int
                if state_index < 0 or state_index >= len(states_list):
                    return f"Error: State index {state_index} is out of range. Available states: {len(states_list)}"
                
                # Validate fan speed range
                if fan_speed < ranges["speed_range"]["min_value"] or fan_speed > ranges["speed_range"]["max_value"]:
                    return f"Error: Fan speed {fan_speed} is out of range. Valid range: {ranges['speed_range']['min_value']} - {ranges['speed_range']['max_value']}"
                
                # Validate temperature range
                if temperature < ranges["temperature_range"]["min_value"] or temperature > ranges["temperature_range"]["max_value"]:
                    return f"Error: Temperature {temperature} is out of range. Valid range: {ranges['temperature_range']['min_value']} - {ranges['temperature_range']['max_value']}"
                
                states_list[state_index].SetFanSpeed(fan_speed)
                states_list[state_index].SetTemperature(temperature)

            # make sure the curve is ascending
            for i in range(1, len(states_list)):
                if states_list[i].GetTemperature() < states_list[i - 1].GetTemperature():
                    swap_temp = states_list[i].GetTemperature()
                    states_list[i].SetTemperature(states_list[i - 1].GetTemperature())
                    states_list[i - 1].SetTemperature(swap_temp)
                elif states_list[i].GetTemperature() == states_list[i - 1].GetTemperature():
                    states_list[i].SetTemperature(states_list[i - 1].GetTemperature() + 5)  # 5 based on ADLX
                if states_list[i].GetFanSpeed() < states_list[i - 1].GetFanSpeed():
                    swap_speed = states_list[i].GetFanSpeed()
                    states_list[i].SetFanSpeed(states_list[i - 1].GetFanSpeed())
                    states_list[i - 1].SetFanSpeed(swap_speed)
            
            # Validate states before setting
            error_index = fan_tuning.IsValidFanTuningStates(states_list)
            if error_index != -1:
                return f"Error: Invalid fan tuning state at index {error_index}. Please check the values."
            
            result = fan_tuning.SetFanTuningStates(states_list)
        
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} fan tuning states set successfully"
        else:
            return f"Failed to set GPU {gpu_index} fan tuning states. Error code: {result}"
        
    except Exception as e:
        log_with_color(f"Error setting fan tuning states: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

##### Zero RPM Functions #####
def get_zero_rpm_state(gpu_index: int) -> str:
    """Get the current Zero RPM state for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with Zero RPM state information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedZeroRPM():
            return f"Zero RPM is not supported for GPU {gpu_index}"
        
        is_set = fan_tuning.GetZeroRPMState()
        return f"GPU {gpu_index} Zero RPM state: {'enabled' if is_set else 'disabled'}"
        
    except Exception as e:
        log_with_color(f"Error getting Zero RPM state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_zero_rpm_state(gpu_index: int, enabled: bool = None) -> str:
    """Set the Zero RPM state for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        enabled: Boolean indicating if Zero RPM should be enabled. If None, sets to default.

    Returns:
        String indicating the result of the operation
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedZeroRPM():
            return f"Zero RPM is not supported for GPU {gpu_index}"
        
        if enabled is None:
            enabled = fan_tuning.GetDefaultZeroRPMState()
        
        result = fan_tuning.SetZeroRPMState(enabled)
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} Zero RPM {'enabled' if enabled else 'disabled'}"
        else:
            return f"Failed to set GPU {gpu_index} Zero RPM state. Error code: {result}"
        
    except Exception as e:
        log_with_color(f"Error setting Zero RPM state: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

##### Minimum Acoustic Limit Functions #####
def get_min_acoustic_limit_range(gpu_index: int) -> str:
    """Get the minimum acoustic limit range for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with minimum acoustic limit range information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinAcousticLimit():
            return f"Minimum acoustic limit is not supported for GPU {gpu_index}"
        
        range_info = fan_tuning.GetMinAcousticLimitRange()
        return f"GPU {gpu_index} minimum acoustic limit range: {range_info}"
        
    except Exception as e:
        log_with_color(f"Error getting minimum acoustic limit range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_min_acoustic_limit(gpu_index: int) -> str:
    """Get the current minimum acoustic limit for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with current minimum acoustic limit information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinAcousticLimit():
            return f"Minimum acoustic limit is not supported for GPU {gpu_index}"
        
        value = fan_tuning.GetMinAcousticLimit()
        return f"GPU {gpu_index} current minimum acoustic limit: {value}"
        
    except Exception as e:
        log_with_color(f"Error getting minimum acoustic limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_min_acoustic_limit(gpu_index: int, value: int = None) -> str:
    """Set the minimum acoustic limit for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        value: Minimum acoustic limit value. If None, sets to default.

    Returns:
        String indicating the result of the operation
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinAcousticLimit():
            return f"Minimum acoustic limit is not supported for GPU {gpu_index}"
        
        if value is None:
            value = fan_tuning.GetMinAcousticLimitDefault()
        
        # Validate range
        ranges = fan_tuning.GetMinAcousticLimitRange()
        if value < ranges["min_value"] or value > ranges["max_value"]:
            return f"Error: Minimum acoustic limit value {value} is out of range. Valid range: {ranges['min_value']} - {ranges['max_value']}"
        
        result = fan_tuning.SetMinAcousticLimit(value)
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} minimum acoustic limit set to {value}"
        else:
            return f"Failed to set GPU {gpu_index} minimum acoustic limit. Error code: {result}"
        
    except Exception as e:
        log_with_color(f"Error setting minimum acoustic limit: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

##### Minimum Fan Speed Functions #####
def get_min_fan_speed_range(gpu_index: int) -> str:
    """Get the minimum fan speed range for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with minimum fan speed range information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinFanSpeed():
            return f"Minimum fan speed is not supported for GPU {gpu_index}"
        
        range_info = fan_tuning.GetMinFanSpeedRange()
        return f"GPU {gpu_index} minimum fan speed range: {range_info}"
        
    except Exception as e:
        log_with_color(f"Error getting minimum fan speed range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_min_fan_speed(gpu_index: int) -> str:
    """Get the current minimum fan speed for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with current minimum fan speed information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinFanSpeed():
            return f"Minimum fan speed is not supported for GPU {gpu_index}"
        
        value = fan_tuning.GetMinFanSpeed()
        return f"GPU {gpu_index} current minimum fan speed: {value}%"
        
    except Exception as e:
        log_with_color(f"Error getting minimum fan speed: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_min_fan_speed(gpu_index: int, value: int = None) -> str:
    """Set the minimum fan speed for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        value: Minimum fan speed value (percentage). If None, sets to default.

    Returns:
        String indicating the result of the operation
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedMinFanSpeed():
            return f"Minimum fan speed is not supported for GPU {gpu_index}"
        
        if value is None:
            value = fan_tuning.GetMinFanSpeedDefault()
        
        # Validate range
        ranges = fan_tuning.GetMinFanSpeedRange()
        if value < ranges["min_value"] or value > ranges["max_value"]:
            return f"Error: Minimum fan speed value {value} is out of range. Valid range: {ranges['min_value']} - {ranges['max_value']}"
        
        result = fan_tuning.SetMinFanSpeed(value)
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} minimum fan speed set to {value}%"
        else:
            return f"Failed to set GPU {gpu_index} minimum fan speed. Error code: {result}"
        
    except Exception as e:
        log_with_color(f"Error setting minimum fan speed: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

##### Target Fan Speed Functions #####
def get_target_fan_speed_range(gpu_index: int) -> str:
    """Get the target fan speed range for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with target fan speed range information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedTargetFanSpeed():
            return f"Target fan speed is not supported for GPU {gpu_index}"
        
        range_info = fan_tuning.GetTargetFanSpeedRange()
        return f"GPU {gpu_index} target fan speed range: {range_info}"
        
    except Exception as e:
        log_with_color(f"Error getting target fan speed range: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def get_target_fan_speed(gpu_index: int) -> str:
    """Get the current target fan speed for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        
    Returns:
        String with current target fan speed information
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedTargetFanSpeed():
            return f"Target fan speed is not supported for GPU {gpu_index}"
        
        value = fan_tuning.GetTargetFanSpeed()
        return f"GPU {gpu_index} current target fan speed: {value}%"
        
    except Exception as e:
        log_with_color(f"Error getting target fan speed: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"

def set_target_fan_speed(gpu_index: int, value: int = None) -> str:
    """Set the target fan speed for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        value: Target fan speed value (percentage). If None, sets to default.

    Returns:
        String indicating the result of the operation
    """
    try:
        fan_tuning, error_msg = _get_fan_tuning_interface(gpu_index)
        if error_msg:
            return error_msg
        
        if not fan_tuning.IsSupportedTargetFanSpeed():
            return f"Target fan speed is not supported for GPU {gpu_index}"
        
        if value is None:
            value = fan_tuning.GetTargetFanSpeedDefault()
        
        # Validate range
        ranges = fan_tuning.GetTargetFanSpeedRange()
        if value < ranges["min_value"] or value > ranges["max_value"]:
            return f"Error: Target fan speed value {value} is out of range. Valid range: {ranges['min_value']} - {ranges['max_value']}"
        
        result = fan_tuning.SetTargetFanSpeed(value)
        if result in [0, 1, 2]:
            return f"GPU {gpu_index} target fan speed set to {value}%"
        else:
            return f"Failed to set GPU {gpu_index} target fan speed. Error code: {result}"
        
    except Exception as e:
        log_with_color(f"Error setting target fan speed: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


##### Functions to be exposed for manifest.json #####
def get_manual_fan_tuning_range(gpu_index: int, setting: str) -> str:
    """Get the range of a specific manual fan tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the range ('fan_tuning', 'min_acoustic_limit', 'min_fan_speed', 'target_fan_speed')
        
    Returns:
        String with the range information
    """
    output_str = _get_fan_tuning_support_str(gpu_index)
    if setting == 'fan_tuning':
        output_str += get_fan_tuning_ranges(gpu_index)
    elif setting == 'min_acoustic_limit':
        output_str += get_min_acoustic_limit_range(gpu_index)
    elif setting == 'min_fan_speed':
        output_str += get_min_fan_speed_range(gpu_index)
    elif setting == 'target_fan_speed':
        output_str += get_target_fan_speed_range(gpu_index)
    else:
        output_str += f"Error: Unsupported setting '{setting}'"
    return output_str

def get_manual_fan_tuning_state(gpu_index: int, setting: str) -> str:
    """Get the current state of a specific manual fan tuning setting for a GPU.
    
    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to get the state ('fan_tuning', "zero_rpm", 'min_acoustic_limit', 'min_fan_speed', 'target_fan_speed')
        
    Returns:
        String with the specific state information
    """
    output_str = _get_fan_tuning_support_str(gpu_index)
    if setting == 'fan_tuning':
        output_str += get_fan_tuning_states(gpu_index)
    elif setting == 'zero_rpm':
        output_str += get_zero_rpm_state(gpu_index)
    elif setting == 'min_acoustic_limit':
        output_str += get_min_acoustic_limit(gpu_index)
    elif setting == 'min_fan_speed':
        output_str += get_min_fan_speed(gpu_index)
    elif setting == 'target_fan_speed':
        output_str += get_target_fan_speed(gpu_index)
    else:
        output_str += f"Error: Unsupported setting '{setting}'"
    return output_str

def set_manual_fan_tuning_state(gpu_index: int, setting: str, value: dict[str, tuple[int, int]] | bool | int = None) -> str:
    """Set the state of a specific manual fan tuning setting for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)
        setting: The setting to set ('fan_tuning', "zero_rpm", 'min_acoustic_limit', 'min_fan_speed', 'target_fan_speed')
        value: The value to set for the specified setting.
               If setting is 'fan_tuning', a dictionary with state indices as keys and (fan_speed, temperature) tuples as values.
               If setting is 'zero_rpm', a boolean indicating if Zero RPM is enabled.
               If setting is 'min_acoustic_limit', 'min_fan_speed' or 'target_fan_speed', an integer value to set.
               If value is None, it will set the default state for the specified setting.

    Returns:
        String indicating the result of the operation
    """
    if setting == 'fan_tuning':
        return set_fan_tuning_states(gpu_index, value)
    elif setting == 'zero_rpm':
        return set_zero_rpm_state(gpu_index, value)
    elif setting == 'min_acoustic_limit':
        return set_min_acoustic_limit(gpu_index, value)
    elif setting == 'min_fan_speed':
        return set_min_fan_speed(gpu_index, value)
    elif setting == 'target_fan_speed':
        return set_target_fan_speed(gpu_index, value)
    else:
        return f"Error: Unsupported setting '{setting}'"


if __name__ == "__main__":
    # Example usage
    gpu_index = 1  # Change this to the desired GPU index

    print(get_manual_fan_tuning_range(gpu_index, 'fan_tuning'))
    print(get_manual_fan_tuning_state(gpu_index, 'fan_tuning'))
    print(set_manual_fan_tuning_state(gpu_index, 'fan_tuning', {0: (30, 50), 1: (40, 55), 2: (50, 60), 3: (60, 65), 4: (70, 70)}))  # Example states
    print(set_manual_fan_tuning_state(gpu_index, 'fan_tuning'))  # Reset to default

    print(get_manual_fan_tuning_state(gpu_index, 'zero_rpm'))
    print(set_manual_fan_tuning_state(gpu_index, 'zero_rpm', True))  # Enable Zero RPM
    print(set_manual_fan_tuning_state(gpu_index, 'zero_rpm'))  # Reset to default

    print(get_manual_fan_tuning_range(gpu_index, 'min_acoustic_limit'))
    print(get_manual_fan_tuning_state(gpu_index, 'min_acoustic_limit'))
    print(set_manual_fan_tuning_state(gpu_index, 'min_acoustic_limit', 30))  # Set to 30%   
    print(set_manual_fan_tuning_state(gpu_index, 'min_acoustic_limit'))  # Reset to default

    print(get_manual_fan_tuning_range(gpu_index, 'min_fan_speed'))
    print(get_manual_fan_tuning_state(gpu_index, 'min_fan_speed'))
    print(set_manual_fan_tuning_state(gpu_index, 'min_fan_speed', 20))  # Set to 20%
    print(set_manual_fan_tuning_state(gpu_index, 'min_fan_speed'))  # Reset to default

    print(get_manual_fan_tuning_range(gpu_index, 'target_fan_speed'))
    print(get_manual_fan_tuning_state(gpu_index, 'target_fan_speed'))
    print(set_manual_fan_tuning_state(gpu_index, 'target_fan_speed', 50))  # Set to 50%
    print(set_manual_fan_tuning_state(gpu_index, 'target_fan_speed'))  # Reset to default