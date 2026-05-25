from amd_perfmonitoring_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Tuple, Dict

def get_gpu_usage() -> str:
    """Get GPU usage information."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Usage Information:\n")
    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUUsage():
                response += f"GPU {gpu.Name()} does not support usage metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                response += f"GPU {gpu.Name()} Usage: {gpu_metrics.GPUUsage()}%\n"
    except Exception as e:
        response += f"Error retrieving GPU usage information: {str(e)}"
    return response

def get_gpu_clock_speed() -> str:
    """Get GPU clock speed."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Clock Speed Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUClockSpeed():
                response += f"GPU {gpu.Name()} does not support clock speed metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                clock_speed = gpu_metrics.GPUClockSpeed()
                response += f"GPU {gpu.Name()} Clock Speed: {clock_speed} MHz"
    except Exception as e:
        response += f"Error retrieving GPU clock speed information: {str(e)}"

    return response


def get_gpu_fan_speed() -> str:
    """Get GPU fan speed."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Fan Speed Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUFanSpeed():
                response += f"GPU {gpu.Name()} does not support fan speed metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                fan_speed = gpu_metrics.GPUFanSpeed()
                response += f"GPU {gpu.Name()} Fan Speed: {fan_speed} RPM"
    except Exception as e:
        response += f"Error retrieving GPU fan speed information: {str(e)}"

    return response

def get_gpu_temperature() -> str:
    """Get GPU temperature."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Temperature Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUTemperature():
                response += f"GPU {gpu.Name()} does not support temperature metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                temperature = gpu_metrics.GPUTemperature()
                response += f"GPU {gpu.Name()} Temperature: {temperature} °C"
    except Exception as e:
        response += f"Error retrieving GPU temperature information: {str(e)}"

    return response

def get_gpu_hotspot_temperature() -> str:
    """Get GPU hotspot temperature."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Hotspot Temperature Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUHotspotTemperature():
                response += f"GPU {gpu.Name()} does not support hotspot temperature metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                hotspot_temp = gpu_metrics.GPUHotspotTemperature()
                response += f"GPU {gpu.Name()} Hotspot Temperature: {hotspot_temp} °C"
    except Exception as e:
        response += f"Error retrieving GPU hotspot temperature information: {str(e)}"

    return response

def get_gpu_power() -> str:
    """Get GPU power consumption."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Power Consumption Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUPower():
                response += f"GPU {gpu.Name()} does not support power consumption metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                power = gpu_metrics.GPUPower()
                response += f"GPU {gpu.Name()} Power Consumption: {power} W"
    except Exception as e:
        response += f"Error retrieving GPU power consumption information: {str(e)}"

    return response

def get_gpu_totalboard_power() -> str:
    """Get GPU total board power."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Total Board Power Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUTotalBoardPower():
                response += f"GPU {gpu.Name()} does not support total board power metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                total_board_power = gpu_metrics.GPUTotalBoardPower()
                response += f"GPU {gpu.Name()} Total Board Power: {total_board_power} W"
    except Exception as e:
        response += f"Error retrieving GPU total board power information: {str(e)}"

    return response


def get_gpu_vram() -> str:
    """Get GPU VRAM usage."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU VRAM Usage Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUVRAM():
                response += f"GPU {gpu.Name()} does not support VRAM usage metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                vram = gpu_metrics.GPUVRAM()
                response += f"GPU {gpu.Name()} VRAM: {vram} MB"
    except Exception as e:
        response += f"Error retrieving GPU VRAM information: {str(e)}"

    return response

def get_gpu_vram_clock_speed() -> str:
    """Get GPU VRAM clock speed."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU VRAM Clock Speed Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUVRAMClockSpeed():
                response += f"GPU {gpu.Name()} does not support VRAM clock speed metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                vram_clock_speed = gpu_metrics.GPUVRAMClockSpeed()
                response += f"GPU {gpu.Name()} VRAM Clock Speed: {vram_clock_speed} MHz"
    except Exception as e:
        response += f"Error retrieving GPU VRAM clock speed information: {str(e)}"

    return response

def get_gpu_voltage() -> str:
    """Get GPU voltage."""
    wrapper = ADLXAPIWrapper()
    gpus = wrapper.gpus
    response = str("GPU Voltage Information:\n")

    try:
        for gpu in gpus:
            supported_metrics = wrapper.get_gpu_metrics_support(gpu)
            if not supported_metrics.IsSupportedGPUVoltage():
                response += f"GPU {gpu.Name()} does not support voltage metrics."
            else:
                gpu_metrics = wrapper.get_gpu_metrics(gpu)
                voltage = gpu_metrics.GPUVoltage()
                response += f"GPU {gpu.Name()} Voltage: {voltage} mV"
    except Exception as e:
        response += f"Error retrieving GPU voltage information: {str(e)}"

    return response

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print(get_gpu_usage())
        print(get_gpu_clock_speed())
        print(get_gpu_fan_speed())
        print(get_gpu_temperature())
        print(get_gpu_hotspot_temperature())
        print(get_gpu_power())
        print(get_gpu_totalboard_power())
        print(get_gpu_vram())
        print(get_gpu_vram_clock_speed())
        print(get_gpu_voltage())
    except Exception as e:
        print(f"Error: {e}")

