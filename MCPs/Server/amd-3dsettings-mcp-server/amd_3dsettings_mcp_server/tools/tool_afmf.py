from amd_3dsettings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache


@lru_cache(maxsize=1)
def check_afmf_supported() -> bool:
    """
    Check if AMD Fluid Motion Frames (AFMF) is supported with caching.
    Returns True if supported, False otherwise.
    """
    try:
        wrapper = ADLXAPIWrapper()
        return wrapper.is_afmf_supported()
    except Exception as e:
        raise RuntimeError(f"Error checking AFMF support: {str(e)}")
    
def get_afmf_state() -> str:
    """
    Check if AMD Fluid Motion Frames (AFMF) is enabled.
    Returns a string with the current state or an error message.
    """
    try:
        if not check_afmf_supported():
            return "AMD Fluid Motion Frames is not supported."

        wrapper = ADLXAPIWrapper()
        return f"Current state of AMD Fluid Motion Frames is: {'enabled' if wrapper.is_afmf_enabled() else 'disabled'}."
    except Exception as e:
        raise RuntimeError(f"Error checking AFMF enabled state: {str(e)}")
    
def set_afmf_state(state: int) -> str:
    """
    Set the state of AMD Fluid Motion Frames (AFMF).
    
    Args:
        state (int): 0 to disable AFMF, 1 to enable.
    
    Returns:
        str: A message indicating the result of the operation.
    """
    if not isinstance(state, int) or state not in (0, 1):
        return "State must be an integer (0 or 1)."

    try:
        if not check_afmf_supported():
            return "AMD Fluid Motion Frames is not supported."

        wrapper = ADLXAPIWrapper()
        if wrapper.set_afmf_enabled(bool(state)):
            return f"AMD Fluid Motion Frames {'enabled' if state else 'disabled'}."
        else:
            return f"Failed to {'enable' if state else 'disable'} AMD Fluid Motion Frames."
    except Exception as e:
        raise RuntimeError(f"Error setting AFMF state: {str(e)}")
    
if __name__ == "__main__":
    # Example usage
    try:
        print("Checking AFMF support...")
        supported = check_afmf_supported()
        if supported:
            print("AFMF is supported.")
            print("Setting AFMF to enabled...")
            print(set_afmf_state(1))
            print("Checking AFMF enabled state...")
            print(get_afmf_state())
        else:
            print("AFMF is not supported.")
    except Exception as e:
        print(f"Error: {e}")