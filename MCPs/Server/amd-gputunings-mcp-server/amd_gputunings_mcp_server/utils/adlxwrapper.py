from adlx import ADLX
from typing import List, Optional, Dict

class ADLXAPIWrapper:
    """Wrapper for ADLX API with optimized caching and resource management for GPU tunings."""

    _instance = None
    adlx_helper = ADLX.ADLXHelper()

    memory_timing_description = {
        "MEMORYTIMING_AUTOMATIC": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_AUTOMATIC,
        "MEMORYTIMING_DEFAULT": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_DEFAULT,
        "MEMORYTIMING_FAST_TIMING": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_FAST_TIMING,
        "MEMORYTIMING_FAST_TIMING_LEVEL_2": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_FAST_TIMING_LEVEL_2,
        "MEMORYTIMING_MEMORYTIMING_LEVEL_1": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_MEMORYTIMING_LEVEL_1,
        "MEMORYTIMING_MEMORYTIMING_LEVEL_2": ADLX.ADLX_MEMORYTIMING_DESCRIPTION.MEMORYTIMING_MEMORYTIMING_LEVEL_2
    }
    
    def __new__(cls):
        """Implement singleton pattern to avoid multiple initializations."""
        if cls._instance is None:
            cls._instance = super(ADLXAPIWrapper, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self):
        """Initialize ADLX with caching."""
        if not self._initialized:
            self.adlx_helper.Initialize()
            self._system: Optional[ADLX.IADLXSystem] = None
            self._gpu_tuning_service: Optional[ADLX.IADLXGPUTuningServices] = None
            self._initialized = True
    
    def __del__(self):
        """Clean up ADLX resources."""
        if hasattr(self, '_initialized') and self._initialized:
            self.adlx_helper.Terminate()
            self._initialized = False
    
    @property
    def system(self) -> ADLX.IADLXSystem:
        """Cached system services."""
        if self._system is None:
            self._system = self.adlx_helper.GetSystemServices()
        return self._system
    
    @property
    def gpus(self) -> List[ADLX.IADLXGPU]:
        """Cached list of GPUs."""
        self._gpus = []
        for gpu in self.system.GetGPUs():
            if gpu.Type() != ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
                self._gpus.append(gpu)
        return self._gpus
    
    @property
    def gpu_tuning_service(self) -> ADLX.IADLXGPUTuningServices:
        """Cached GPU tuning services."""
        if self._gpu_tuning_service is None:
            self._gpu_tuning_service = self.system.GetGPUTuningServices()
        return self._gpu_tuning_service

    def is_auto_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if auto tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedAutoTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_auto_tuning(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXGPUAutoTuning:
        """Get auto tuning interface for a specific GPU."""
        auto_tuning = self.gpu_tuning_service.GetAutoTuning(gpu)
        assert isinstance(auto_tuning, ADLX.IADLXGPUAutoTuning)
        return auto_tuning

    def is_manual_gfx_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if manual graphics tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedManualGFXTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_manual_gfx_tuning1(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualGraphicsTuning1:
        """Get manual graphic tuning interface for a specific GPU of pre-RDNA ASIC family."""
        graphic_tuning = self.gpu_tuning_service.GetManualGFXTuning1(gpu)
        assert isinstance(graphic_tuning, ADLX.IADLXManualGraphicsTuning1)
        return graphic_tuning

    def get_manual_gfx_tuning2(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualGraphicsTuning2:
        """Get manual graphic tuning interface for a specific GPU of post-RDNA ASIC family."""
        graphic_tuning = self.gpu_tuning_service.GetManualGFXTuning2(gpu)
        assert isinstance(graphic_tuning, ADLX.IADLXManualGraphicsTuning2)
        return graphic_tuning

    def is_manual_vram_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if manual VRAM tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedManualVRAMTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_manual_vram_tuning1(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualVRAMTuning1:
        """Get manual VRAM tuning interface for a specific GPU of pre-RDNA ASIC family."""
        vram_tuning = self.gpu_tuning_service.GetManualVRAMTuning1(gpu)
        assert isinstance(vram_tuning, ADLX.IADLXManualVRAMTuning1)
        return vram_tuning

    def get_manual_vram_tuning2(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualVRAMTuning2:
        """Get manual VRAM tuning interface for a specific GPU of post-RDNA ASIC family."""
        vram_tuning = self.gpu_tuning_service.GetManualVRAMTuning2(gpu)
        assert isinstance(vram_tuning, ADLX.IADLXManualVRAMTuning2)
        return vram_tuning

    def is_manual_fan_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if manual fan tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedManualFanTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_manual_fan_tuning(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualFanTuning:
        """Get manual fan tuning interface for a specific GPU."""
        fan_tuning = self.gpu_tuning_service.GetManualFanTuning(gpu)
        assert isinstance(fan_tuning, ADLX.IADLXManualFanTuning)
        return fan_tuning

    def is_manual_power_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if manual power tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedManualPowerTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_manual_power_tuning(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXManualPowerTuning:
        """Get manual power tuning interface for a specific GPU."""
        power_tuning = self.gpu_tuning_service.GetManualPowerTuning(gpu)
        assert isinstance(power_tuning, ADLX.IADLXManualPowerTuning)
        return power_tuning

    def is_preset_tuning_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if preset tuning is supported for a specific GPU."""
        is_supported = self.gpu_tuning_service.IsSupportedPresetTuning(gpu)
        assert isinstance(is_supported, bool)
        return is_supported

    def get_preset_tuning(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXGPUPresetTuning:
        """Get preset tuning interface for a specific GPU."""
        preset_tuning = self.gpu_tuning_service.GetPresetTuning(gpu)
        assert isinstance(preset_tuning, ADLX.IADLXGPUPresetTuning)
        return preset_tuning

    def get_gpu_auto_tuning_complete_listener(self, callback_auto_tuning_complete_listener) -> ADLX.IADLXGPUAutoTuningCompleteEvent:
        """Get GPU auto tuning complete listener."""
        callback = ADLX.PyGPUAutoTuningCompleteListenerCallback()
        callback.call = callback_auto_tuning_complete_listener
        return callback

    def is_gpu_tuning_default(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if GPU tuning settings are at default."""
        is_default = self.gpu_tuning_service.IsAtFactory(gpu)
        assert isinstance(is_default, bool)
        return is_default

    def reset_gpu_tuning(self, gpu: ADLX.IADLXGPU) -> bool:
        """Reset GPU tuning settings to default."""
        result = self.gpu_tuning_service.ResetToFactory(gpu)
        assert isinstance(result, ADLX.ADLX_RESULT)
        return result