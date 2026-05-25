from amd_perfmonitoring_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from functools import lru_cache
from typing import Tuple, Dict

def get_cpu_usage() -> str:
    """Get CPU usage information."""
    wrapper = ADLXAPIWrapper()
    response = str("CPU Usage Information:\n")

    try:
        system_metrics_support = wrapper.get_system_metrics_support()
        if not system_metrics_support.IsSupportedCPUUsage():
            response += "CPU usage metrics are not supported on this system."
        else:
            system_metrics = wrapper.get_system_metrics()
            cpu_usage = system_metrics.CPUUsage()
            response += f"Current CPU Usage: {cpu_usage}%\n"
    except Exception as e:
        response += f"Error retrieving CPU usage information: {str(e)}"

    return response

def get_smartshift_value() -> str:
    """Get SmartShift value."""
    wrapper = ADLXAPIWrapper()
    response = str("SmartShift Value Information:\n")

    try:
        system_metrics_support = wrapper.get_system_metrics_support()
        if not system_metrics_support.IsSupportedSmartShift():
            response += "SmartShift metrics are not supported on this system."
        else:
            system_metrics = wrapper.get_system_metrics()
            smartshift_value = system_metrics.SmartShift()
            response += f"Current SmartShift Value: {smartshift_value}\n"
    except Exception as e:
        response += f"Error retrieving SmartShift value information: {str(e)}"

    return response

def get_system_ram() -> str:
    """Get system RAM information."""
    wrapper = ADLXAPIWrapper()
    response = str("System RAM Information:\n")

    try:
        system_metrics_support = wrapper.get_system_metrics_support()
        if not system_metrics_support.IsSupportedSystemRAM():
            response += "RAM metrics are not supported on this system."
        else:
            system_metrics = wrapper.get_system_metrics()
            ram_usage = system_metrics.SystemRAM()
            response += f"Current RAM Usage: {ram_usage} MB\n"
    except Exception as e:
        response += f"Error retrieving RAM usage information: {str(e)}"

    return response

if __name__ == "__main__":
    # Example usage with better error handling
    try:
        print(get_cpu_usage())
        print(get_smartshift_value())
        print(get_system_ram())
    except Exception as e:
        print(f"Error: {e}")

