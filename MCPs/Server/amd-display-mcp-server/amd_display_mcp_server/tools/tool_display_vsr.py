from amd_display_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from adlx import ADLX

def get_display_vsr_state(display_index: int = 0) -> str:
    """Check if Virtual Super Resolution (VSR) is enabled for a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        if display_index >= len(display_list) or display_index < 0:
            raise RuntimeError(f"Display index {display_index} is out of range. Available displays: {len(display_list)}")

        display_name = display_list[display_index].Name()
        vsr_service = wrapper.get_display_vsr(display_list[display_index])

        if not vsr_service.IsSupported():
            return f"Display:{display_name} Virtual Super Resolution is not supported."

        is_enabled = vsr_service.IsEnabled()
        return f"Display:{display_name} Virtual Super Resolution is {'enabled' if is_enabled else 'disabled'}."
    except Exception as e:
        return f"Error checking VSR status: {str(e)}"
    
def set_display_vsr_state(state: int, display_index: int = 0) -> str:
    """
    Set the state of Virtual Super Resolution (VSR) for a display.

    Args:
        state (int): 0 to disable VSR, 1 to enable.
        display_index (int): The index of the display to modify (defaults to 0).

    Returns:
        str: A message indicating the result of the operation.

    Raises:
        ValueError: If state is not 0 or 1.
        RuntimeError: If Virtual Super Resolution (VSR) is not supported or operation fails.
    """
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        if display_index >= len(display_list) or display_index < 0:
            raise RuntimeError(f"Display index {display_index} is out of range. Available displays: {len(display_list)}")

        display_name = display_list[display_index].Name()
        vsr_service = wrapper.get_display_vsr(display_list[display_index])

        if not vsr_service.IsSupported():
            return f"Display:{display_name} Virtual Super Resolution is not supported."

        if vsr_service.SetEnabled(bool(state)) in [ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED]:
            return f"Virtual Super Resolution {'enabled' if state else 'disabled'} on Display:{display_name}."
        else:
            return RuntimeError(f"Failed to {'enable' if state else 'disable'} Virtual Super Resolution on Display:{display_name}.")
    except Exception as e:
        raise f"Error setting VSR: {str(e)}"
    

if __name__ == "__main__":
    try:
        display_index = 0  # Example display index
        print(get_display_vsr_state())
        print(set_display_vsr_state(1))  # Enable VSR
        print(get_display_vsr_state())
        print(set_display_vsr_state(0))  # Disable VSR
        print(get_display_vsr_state())
    except Exception as e:
        print(f"Error: {str(e)}")