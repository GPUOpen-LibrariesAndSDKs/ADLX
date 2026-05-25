# -------------------------------------------------------------------------
# Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
# -------------------------------------------------------------------------

import traceback
from amd_gputunings_mcp_server.utils.adlxwrapper import ADLXAPIWrapper
from amd_gputunings_mcp_server.utils.log import log_with_color


# listeners for auto tuning completion
import threading

event = threading.Event()
is_overclock_gpu_completed : bool = False
is_overclock_vram_completed : bool = False
is_undervolt_gpu_completed : bool = False

def callback_auto_tuning_complete_listener(gpu_auto_tuning_complete_event) -> bool:
    is_overclock_gpu_completed = gpu_auto_tuning_complete_event.IsOverclockGPUCompleted()
    is_overclock_vram_completed = gpu_auto_tuning_complete_event.IsOverclockVRAMCompleted()
    is_undervolt_gpu_completed = gpu_auto_tuning_complete_event.IsUndervoltGPUCompleted()
    event.set()  # Signal that the auto tuning operation is complete
    log_with_color(f"Auto tuning complete: "
                   f"Overclock GPU: {is_overclock_gpu_completed}, "
                   f"Overclock VRAM: {is_overclock_vram_completed}, "
                   f"Undervolt GPU: {is_undervolt_gpu_completed}", "green")
    return True


##### Functions to be exposed for manifest.json #####
def get_auto_tuning_type(gpu_index: int) -> str:
    """Get the current auto tuning type for a GPU.

    Args:
        gpu_index: Index of the GPU (0-based)

    Returns:
        String indicating the current auto tuning type
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_auto_tuning_supported(gpu):
            return f"Auto tuning is not supported for GPU {gpu_index}"

        output_str = f"Auto tuning is supported for GPU {gpu_index}. "

        auto_tuning = wrapper.get_auto_tuning(gpu)
        if auto_tuning:
            if auto_tuning.IsSupportedUndervoltGPU() and auto_tuning.IsCurrentUndervoltGPU():
                output_str += f"Current auto tuning type for GPU {gpu_index}: Undervolt GPU"
            elif auto_tuning.IsSupportedOverclockGPU() and auto_tuning.IsCurrentOverclockGPU():
                output_str += f"Current auto tuning type for GPU {gpu_index}: Overclock GPU"
            elif auto_tuning.IsSupportedOverclockVRAM() and auto_tuning.IsCurrentOverclockVRAM():
                output_str += f"Current auto tuning type for GPU {gpu_index}: Overclock VRAM"
            else:
                output_str += f"Current auto tuning type for GPU {gpu_index}: None"
            return output_str
        else:
            return f"Auto tuning is not available for GPU {gpu_index}"
            
    except Exception as e:
        log_with_color(f"Error getting current auto tuning type for GPU {gpu_index}: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


def start_auto_tuning(gpu_index: int, tuning_type: str) -> str:
    """Start auto tuning for a GPU based on the specified tuning type.

    Args:
        gpu_index: Index of the GPU (0-based)
        tuning_type: Type of tuning to start ('undervolt_gpu', 'overclock_gpu', 'overclock_vram')

    Returns:
        String indicating the result of the operation
    """
    try:
        wrapper = ADLXAPIWrapper()
        gpus = wrapper.gpus
        
        if gpu_index >= len(gpus) or gpu_index < 0:
            return f"Error: GPU index {gpu_index} is out of range. Available GPUs: {len(gpus)}"
        
        gpu = gpus[gpu_index]
        if not wrapper.is_auto_tuning_supported(gpu):
            return f"Auto tuning is not supported for GPU {gpu_index}"

        auto_tuning = wrapper.get_auto_tuning(gpu)
        if auto_tuning:
            complete_listener = wrapper.get_gpu_auto_tuning_complete_listener(callback_auto_tuning_complete_listener)
            if tuning_type == 'undervolt_gpu':
                if not auto_tuning.IsSupportedUndervoltGPU():
                    return f"Error: Undervolt GPU is not supported for GPU {gpu_index}"
                result = auto_tuning.StartUndervoltGPU(complete_listener)
                is_set = event.wait(timeout=15)  # Wait for the auto tuning operation to complete
                event.clear()
                if not is_set:
                    return f"Error: Undervolt GPU tuning did not complete in time for GPU {gpu_index}"
                return f"Undervolt GPU tuning completed for GPU {gpu_index}, result: {result}"
            elif tuning_type == 'overclock_gpu':
                if not auto_tuning.IsSupportedOverclockGPU():
                    return f"Error: Overclock GPU is not supported for GPU {gpu_index}"
                result = auto_tuning.StartOverclockGPU(complete_listener)
                is_set = event.wait(timeout=15)  # Wait for the auto tuning operation to
                event.clear()
                if not is_set:
                    return f"Error: Overclock GPU tuning did not complete in time for GPU {gpu_index}"
                return f"Overclock GPU tuning completed for GPU {gpu_index}, result: {result}"
            elif tuning_type == 'overclock_vram':
                if not auto_tuning.IsSupportedOverclockVRAM():
                    return f"Error: Overclock VRAM is not supported for GPU {gpu_index}"
                result = auto_tuning.StartOverclockVRAM(complete_listener)
                is_set = event.wait(timeout=15)  # Wait for the auto tuning operation to complete
                event.clear()
                if not is_set:
                    return f"Error: Overclock VRAM tuning did not complete in time for GPU {gpu_index}"
                return f"Overclock VRAM tuning completed for GPU {gpu_index}, result: {result}"
            else:
                return f"Error: Invalid tuning type '{tuning_type}' specified, available options are 'undervolt_gpu', 'overclock_gpu', 'overclock_vram'"
        else:
            return f"Auto tuning is not available for GPU {gpu_index}"
        
    except Exception as e:
        log_with_color(f"Error starting auto tuning for GPU {gpu_index}: {e}", "red")
        log_with_color(traceback.format_exc(), "red")
        return f"Error: {str(e)}"


if __name__ == "__main__":
    # Example usage
    gpu_index = 1  # Change this to the GPU index you want to test
    print(get_auto_tuning_type(gpu_index))
    print(start_auto_tuning(gpu_index, 'undervolt_gpu'))
    print(start_auto_tuning(gpu_index, 'overclock_gpu'))
    print(start_auto_tuning(gpu_index, 'overclock_vram'))
