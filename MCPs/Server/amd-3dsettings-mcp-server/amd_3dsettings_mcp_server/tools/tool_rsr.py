from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache

@lru_cache(maxsize=1)
def check_rsr_support() -> bool:
    """
    Check if RSR is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        return wrapper.is_rsr_supported()
    except Exception as e:
        raise RuntimeError(f"Error checking RSR support: {str(e)}")

def set_rsr_state(state: int) -> str:
    """
    Set the state of Radeon Super Resolution (RSR).
    
    Args:
        state (int): 0 to disable RSR, 1 to enable.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        if not check_rsr_support():
            return "Radeon Super Resolution is not supported. Please try it again after you install and launch the AMD Radeon Software."

        wrapper = ADLXAPIWrapper()
        if wrapper.set_rsr_enabled(bool(state)):
            return f"Radeon Super Resolution {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} Radeon Super Resolution."
    except Exception as e:
        raise RuntimeError(f"Error setting RSR state: {str(e)}")

def get_rsr_state() -> str:
    """
    Get the current state of Radeon Super Resolution (RSR).
    
    Returns:
        str: A message indicating the current state of RSR.
    """
    try:
        if not check_rsr_support():
            return "Radeon Super Resolution is not supported. Please try it again after you install and launch the AMD Radeon Software."

        wrapper = ADLXAPIWrapper()
        return f"Current state of Radeon Super Resolution is: {'enabled' if wrapper.is_rsr_enabled() else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error getting RSR state: {str(e)}")

def get_rsr_sharpness_range() -> str:
    """
    Get the range of sharpness values for Radeon Super Resolution (RSR).
    
    Returns:
        str: A message indicating the sharpness range or an error message.
    """
    try:
        if not check_rsr_support():
            return "Radeon Super Resolution is not supported."

        wrapper = ADLXAPIWrapper()
        range_info = wrapper.get_rsr_sharpness_range()
        return f"Radeon Super Resolution sharpness range: min={range_info['minValue']}, max={range_info['maxValue']}."
    except Exception as e:
        raise RuntimeError(f"Error getting RSR sharpness range: {str(e)}")

def get_rsr_sharpness() -> str:
    """
    Get the current sharpness value for Radeon Super Resolution (RSR).
    
    Returns:
        str: A message indicating the current sharpness value.
    """
    try:
        if not check_rsr_support():
            return "Radeon Super Resolution is not supported."

        wrapper = ADLXAPIWrapper()
        sharpness = wrapper.get_rsr_sharpness()
        return f"Current Radeon Super Resolution sharpness is: {sharpness}."
    except Exception as e:
        raise RuntimeError(f"Error getting RSR sharpness: {str(e)}")

def set_rsr_sharpness(sharpness: int) -> str:
    """
    Set the sharpness value for Radeon Super Resolution (RSR).
    
    Args:
        sharpness (int): The sharpness value to set.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(sharpness, int):
        return "Sharpness value must be an integer."

    try:
        if not check_rsr_support():
            return "Radeon Super Resolution is not supported."

        wrapper = ADLXAPIWrapper()
        sharpness_range = wrapper.get_rsr_sharpness_range()
        if not (sharpness_range['minValue'] <= sharpness <= sharpness_range['maxValue']):
            return f"Sharpness value must be between {sharpness_range['minValue']} and {sharpness_range['maxValue']}."

        if wrapper.set_rsr_sharpness(sharpness):
            return f"Radeon Super Resolution sharpness set to {sharpness}."
        else:
            return "Failed to set Radeon Super Resolution sharpness."
    except Exception as e:
        raise RuntimeError(f"Error setting RSR sharpness: {str(e)}")

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print("Initial state:")
        print(get_rsr_state())
            
        print("\nEnabling RSR:")
        print(set_rsr_state(1))
        print(get_rsr_state())
            
        print("\nDisabling RSR:")
        print(set_rsr_state(0))
        print(get_rsr_state())
            
    except Exception as e:
        print(f"Error: {e}")

