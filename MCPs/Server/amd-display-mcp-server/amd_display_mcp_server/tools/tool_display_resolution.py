from amd_display_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Tuple, Dict
from adlx import ADLX

def create_new_display_custom_resolution(display_index: int, width: int, height: int, refresh_rate: int = 60) -> str:
    """Create a new custom resolution for a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_res = wrapper.get_display_custom_resolution(display_list[display_index])

        if not custom_res.IsSupported():
            return f"Display:{display_name} Custom Resolution is not supported."

        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        resolution_value: ADLX.ADLX_CustomResolution = current_display_res.GetValue()
        #print resolution values
        print(f"Current Resolution: {resolution_value.resWidth}x{resolution_value.resHeight}@{resolution_value.refreshRate}Hz")

        resolution_value.resWidth = width
        resolution_value.resHeight = height
        resolution_value.refreshRate = refresh_rate
        # Set the timing standard to CVT (Coordinated Video Timing)
        # Not support for now, but can be added later
        resolution_value.timingStandard = ADLX.ADLX_TIMING_STANDARD.CVT
        ret: ADLX.ADLX_RESULT = current_display_res.SetValue(resolution_value)
        if ret != ADLX.ADLX_RESULT.ADLX_OK:
            return f"Failed to set resolution: {ret}"
        
        ret: ADLX.ADLX_RESULT = custom_res.CreateNewResolution(current_display_res)
        if ret != ADLX.ADLX_RESULT.ADLX_OK:
            return f"Failed to create new resolution: {ret}"

        return f"Custom resolution {width}x{height}@{refresh_rate}Hz added to Display:{display_name}."
    except Exception as e:
        return f"Error creating custom resolution: {str(e)}"
    
def get_current_display_custom_resolution(display_index: int) -> str:
    """Get the current custom resolution of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_res = wrapper.get_display_custom_resolution(display_list[display_index])

        if not custom_res.IsSupported():
            raise ValueError(f"Display:{display_name} Custom Resolution is not supported.")

        current_display_res: ADLX.IADLXDisplayResolution = custom_res.GetCurrentAppliedResolution()
        resolution_value: ADLX.ADLX_CustomResolution = current_display_res.GetValue()
        return f"Current custom resolution for Display:{display_name} is {resolution_value.resWidth}x{resolution_value.resHeight}@{resolution_value.refreshRate}Hz."
    except Exception as e:
        raise RuntimeError(f"Error getting current custom resolution: {str(e)}")
    
def delete_display_custom_resolution(display_index: int, resolution_index: int) -> str:
    """Delete a custom resolution from a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_res = wrapper.get_display_custom_resolution(display_list[display_index])

        if not custom_res.IsSupported():
            raise ValueError(f"Display:{display_name} Custom Resolution is not supported.")

        resolutions = custom_res.GetResolutionList()
        if resolution_index < 0 or resolution_index >= len(resolutions):
            raise IndexError("Invalid resolution index.")

        ret: ADLX.ADLX_RESULT = custom_res.DeleteResolution(resolutions[resolution_index])
        if ret != ADLX.ADLX_RESULT.ADLX_OK:
            return f"Failed to delete resolution: {ret}"

        return f"Custom resolution at index {resolution_index} deleted from Display:{display_name}."
    except Exception as e:
        return f"Error deleting custom resolution: {str(e)}"


if __name__ == "__main__":
    # Example usage with better error handling
    try:
        display_index = 0  # Example display index
        print(create_new_display_custom_resolution(display_index, 3840, 2160, 60))
        print(get_current_display_custom_resolution(display_index))
        print(delete_display_custom_resolution(display_index, 0))  # Example resolution index
    except Exception as e:
        print(f"Error: {e}")

