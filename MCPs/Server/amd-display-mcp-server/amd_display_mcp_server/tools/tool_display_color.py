from amd_display_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Tuple, Dict

def get_display_color_info(display_index: int) -> Dict[str, str]:
    """Get comprehensive color information for a display including brightness, contrast, hue, saturation, and color temperature."""
    wrapper = ADLXAPIWrapper()
    
    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])
        
        color_info = {
            "display_name": display_name,
            "brightness": "Not supported",
            "contrast": "Not supported", 
            "hue": "Not supported",
            "saturation": "Not supported",
            "color_temperature": "Not supported"
        }
        
        if not custom_color:
            return color_info
            
        # Get brightness info
        if custom_color.IsBrightnessSupported():
            brightness = custom_color.GetBrightness()
            brightness_range = custom_color.GetBrightnessRange()
            color_info["brightness"] = f"{brightness}%, range: {brightness_range.minValue} - {brightness_range.maxValue}% - {brightness_range.step}% step"
        
        # Get contrast info
        if custom_color.IsContrastSupported():
            contrast = custom_color.GetContrast()
            contrast_range = custom_color.GetContrastRange()
            color_info["contrast"] = f"{contrast}%, range: {contrast_range.minValue} - {contrast_range.maxValue}% - {contrast_range.step}% step"
        
        # Get hue info
        if custom_color.IsHueSupported():
            hue = custom_color.GetHue()
            hue_range = custom_color.GetHueRange()
            color_info["hue"] = f"{hue} degrees, range: {hue_range.minValue} - {hue_range.maxValue} degrees - {hue_range.step} degree step"
        
        # Get saturation info
        if custom_color.IsSaturationSupported():
            saturation = custom_color.GetSaturation()
            saturation_range = custom_color.GetSaturationRange()
            color_info["saturation"] = f"{saturation}%, range: {saturation_range.minValue} - {saturation_range.maxValue}% - {saturation_range.step}% step"
        
        # Get color temperature info
        if custom_color.IsTemperatureSupported():
            color_temp = custom_color.GetTemperature()
            color_temp_range = custom_color.GetTemperatureRange()
            color_info["color_temperature"] = f"{color_temp}K, range: {color_temp_range.minValue} - {color_temp_range.maxValue}K - {color_temp_range.step}K step"
        
        return color_info
        
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found.")

def set_color_brightness(display_index: int, brightness: int) -> str:
    """Set the brightness of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])

        if custom_color and custom_color.IsBrightnessSupported():
            brightness_range = custom_color.GetBrightnessRange()
            if not (brightness_range.minValue <= brightness <= brightness_range.maxValue):
                raise ValueError(f"Brightness value {brightness} is out of range ({brightness_range.minValue} - {brightness_range.maxValue}).")
            
            custom_color.SetBrightness(brightness)
            return f"Display:{display_name} Brightness set to {brightness}%."
        else:
            return f"Display:{display_name} Brightness control is not supported."
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found or brightness setting failed.")
      
def set_color_contrast(display_index: int, contrast: int) -> str:
    """Set the contrast of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])

        if custom_color and custom_color.IsContrastSupported():
            contrast_range = custom_color.GetContrastRange()
            if not (contrast_range.minValue <= contrast <= contrast_range.maxValue):
                raise ValueError(f"Contrast value {contrast} is out of range ({contrast_range.minValue} - {contrast_range.maxValue}).")
            
            custom_color.SetContrast(contrast)
            return f"Display:{display_name} Contrast set to {contrast}%."
        else:
            return f"Display:{display_name} Contrast control is not supported."
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found or contrast setting failed.")

def set_color_hue(display_index: int, hue: int) -> str:
    """Set the hue of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])

        if custom_color and custom_color.IsHueSupported():
            hue_range = custom_color.GetHueRange()
            if not (hue_range.minValue <= hue <= hue_range.maxValue):
                raise ValueError(f"Hue value {hue} is out of range ({hue_range.minValue} - {hue_range.maxValue}).")
            
            custom_color.SetHue(hue)
            return f"Display:{display_name} Hue set to {hue} degrees."
        else:
            return f"Display:{display_name} Hue control is not supported."
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found or hue setting failed.")

def set_color_saturation(display_index: int, saturation: int) -> str:
    """Set the saturation of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])

        if custom_color and custom_color.IsSaturationSupported():
            saturation_range = custom_color.GetSaturationRange()
            if not (saturation_range.minValue <= saturation <= saturation_range.maxValue):
                raise ValueError(f"Saturation value {saturation} is out of range ({saturation_range.minValue} - {saturation_range.maxValue}).")
            
            custom_color.SetSaturation(saturation)
            return f"Display:{display_name} Saturation set to {saturation}%."
        else:
            return f"Display:{display_name} Saturation control is not supported."
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found or saturation setting failed.")

def set_color_temperature(display_index: int, color_temp: int) -> str:
    """Set the color temperature of a display."""
    wrapper = ADLXAPIWrapper()

    try:
        display_list = wrapper.display_list
        display_name = display_list[display_index].Name()
        custom_color = wrapper.get_display_custom_color(display_list[display_index])

        if custom_color and custom_color.IsTemperatureSupported():
            color_temp_range = custom_color.GetTemperatureRange()
            if not (color_temp_range.minValue <= color_temp <= color_temp_range.maxValue):
                raise ValueError(f"Color temperature value {color_temp} is out of range ({color_temp_range.minValue} - {color_temp_range.maxValue}).")

            custom_color.SetTemperature(color_temp)
            return f"Display:{display_name} Color Temperature set to {color_temp}K."
        else:
            return f"Display:{display_name} Color Temperature control is not supported."
    except Exception as e:
        raise ValueError(f"Display with index '{display_index}' not found or color temperature setting failed.")

if __name__ == "__main__":
    # Example usage with the new unified function
    try:
        display_color_info = get_display_color_info(0)
        print(f"Display: {display_color_info['display_name']}")
        print(f"Brightness: {display_color_info['brightness']}")
        print(f"Contrast: {display_color_info['contrast']}")
        print(f"Hue: {display_color_info['hue']}")
        print(f"Saturation: {display_color_info['saturation']}")
        print(f"Color Temperature: {display_color_info['color_temperature']}")
        
        # Example of setting color temperature
        set_color_temperature(0, 6500)
    except Exception as e:
        print(f"Error: {e}")

