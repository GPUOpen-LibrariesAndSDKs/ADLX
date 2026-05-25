from adlx import ADLX
from typing import List, Optional,Dict

class ADLXAPIWrapper:
    """Wrapper for ADLX API with optimized caching and resource management."""

    _instance = None
    adlx_helper = ADLX.ADLXHelper()
    # Success result codes - using frozenset for faster membership checks
    _SUCCESS_RESULTS = frozenset([
        ADLX.ADLX_RESULT.ADLX_OK,
        ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED,
        ADLX.ADLX_RESULT.ADLX_ALREADY_INITIALIZED
    ])
    
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
            self._3d_settings: Optional[ADLX.IADLX3DSettingsServices] = None
            self._rsr: Optional[ADLX.IADLX3DRadeonSuperResolution] = None
            self._afmf: Optional[ADLX.IADLX3DAMDFluidMotionFrames] = None
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
    def three_d_settings(self) -> ADLX.IADLX3DSettingsServices:
        """Cached 3D settings services."""
        if self._3d_settings is None:
            self._3d_settings = self.system.Get3DSettingsServices()
        return self._3d_settings
    
    @property
    def rsr(self) -> ADLX.IADLX3DRadeonSuperResolution:
        """Cached RSR instance."""
        if self._rsr is None:
            self._rsr = self.three_d_settings.GetRadeonSuperResolution()
        return self._rsr

    @property
    def afmf(self) -> ADLX.IADLX3DAMDFluidMotionFrames:
        """Cached afmf instance."""
        if self._afmf is None:
            self._afmf = self.three_d_settings.GetAMDFluidMotionFrames()
        return self._afmf
    
    def fidelityfx_super_resolution(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DFidelityFXSuperResolution:
        """Cached FidelityFX Super Resolution instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_fidelityfx_super_resolution_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetFidelityFXSuperResolution(gpu))
        return getattr(self, attr_name)
    
    def fidelityfx_frame_gen_upgrade(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DFidelityFXFrameGenUpgrade:
        """Cached FidelityFX Frame Generation Upgrade instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_fidelityfx_frame_gen_upgrade_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetFidelityFXFrameGenUpgrade(gpu))
        return getattr(self, attr_name)
    
    def boost(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DBoost:
        """Cached Boost instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_boost_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetBoost(gpu))
        return getattr(self, attr_name)
    
    def chill(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DChill:
        """Cached Chill instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_chill_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetChill(gpu))
        return getattr(self, attr_name)
    
    def anti_lag(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DAntiLag:
        """Cached Anti-Lag instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_anti_lag_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetAntiLag(gpu))
        return getattr(self, attr_name)
    
    def image_sharpening(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DImageSharpening:
        """Cached Image Sharpening instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_image_sharpening_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetImageSharpening(gpu))
        return getattr(self, attr_name)
    
    def enhanced_sync(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DEnhancedSync:
        """Cached Enhanced Sync instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_enhanced_sync_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetEnhancedSync(gpu))
        return getattr(self, attr_name)
    
    def wait_for_vertical_refresh(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DWaitForVerticalRefresh:
        """Cached Wait For Vertical Refresh instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_wait_for_vertical_refresh_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetWaitForVerticalRefresh(gpu))
        return getattr(self, attr_name)
    
    def frtc(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DFrameRateTargetControl:
        """Cached FRTC instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_frtc_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetFrameRateTargetControl(gpu))
        return getattr(self, attr_name)

    def anti_aliasing(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DAntiAliasing:
        """Cached Anti-Aliasing instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_anti_aliasing_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetAntiAliasing(gpu))
        return getattr(self, attr_name)

    def morphological_anti_aliasing(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DMorphologicalAntiAliasing:
        """Cached Morphological Anti-Aliasing instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_morphological_anti_aliasing_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetMorphologicalAntiAliasing(gpu))
        return getattr(self, attr_name)
    
    def anisotropic_filtering(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DAnisotropicFiltering:
        """Cached Anisotropic Filtering instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_anisotropic_filtering_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetAnisotropicFiltering(gpu))
        return getattr(self, attr_name)
    
    def tessellation(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLX3DTessellation:
        """Cached Tessellation instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_tessellation_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetTessellation(gpu))
        return getattr(self, attr_name)
    
    def reset_shader_cache(self, gpu: ADLX.IADLXGPU):
        """Get the reset shader cache interface using cached instance."""
        gpu_id = str(gpu)  # Use GPU string representation as cache key
        attr_name = f'_reset_shader_cache_{gpu_id}'
        if not hasattr(self, attr_name):
            setattr(self, attr_name, self.three_d_settings.GetResetShaderCache(gpu))
        return getattr(self, attr_name)
        
    def is_reset_shader_cache_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Reset Shader Cache is supported using cached instance."""
        is_supported: bool = self.reset_shader_cache(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def set_reset_shader_cache(self, gpu: ADLX.IADLXGPU) -> bool:
        """Set Reset Shader Cache using cached instance."""
        set_result: ADLX.ADLX_RESULT = self.reset_shader_cache(gpu).ResetShaderCache()
        assert isinstance(set_result, ADLX.ADLX_RESULT)

        return set_result in self._SUCCESS_RESULTS

    def is_tessellation_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Tessellation is supported using cached instance."""
        is_supported: bool = self.tessellation(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def get_tessellation_mode(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_TESSELLATION_MODE:
        """Get Tessellation mode using cached instance."""
        mode: ADLX.ADLX_TESSELLATION_MODE = self.tessellation(gpu).GetMode()
        assert isinstance(mode, ADLX.ADLX_TESSELLATION_MODE)
        return mode

    def set_tessellation_mode(self, gpu: ADLX.IADLXGPU, mode: ADLX.ADLX_TESSELLATION_MODE) -> bool:
        """Set Tessellation mode using cached instance."""
        set_mode: ADLX.ADLX_RESULT = self.tessellation(gpu).SetMode(mode)
        assert isinstance(set_mode, ADLX.ADLX_RESULT)

        if set_mode in self._SUCCESS_RESULTS:
            assert self.tessellation(gpu).GetMode() == mode
            return True
        return False

    def get_tessellation_level(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_TESSELLATION_LEVEL:
        """Get Tessellation level using cached instance."""
        level: ADLX.ADLX_TESSELLATION_LEVEL = self.tessellation(gpu).GetLevel()
        assert isinstance(level, ADLX.ADLX_TESSELLATION_LEVEL)
        return level

    def set_tessellation_level(self, gpu: ADLX.IADLXGPU, level: ADLX.ADLX_TESSELLATION_LEVEL) -> bool:
        """Set Tessellation level using cached instance."""
        set_level: ADLX.ADLX_RESULT = self.tessellation(gpu).SetLevel(level)
        assert isinstance(set_level, ADLX.ADLX_RESULT)

        if set_level in self._SUCCESS_RESULTS:
            assert self.tessellation(gpu).GetLevel() == level
            return True
        return False

    def is_anisotropic_filtering_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Anisotropic Filtering is supported using cached instance."""
        is_supported: bool = self.anisotropic_filtering(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_anisotropic_filtering_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Anisotropic Filtering is enabled using cached instance."""
        is_enabled: bool = self.anisotropic_filtering(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_anisotropic_filtering_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Anisotropic Filtering state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.anisotropic_filtering(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.anisotropic_filtering(gpu).IsEnabled() == enabled
            return True
        return False

    def get_anisotropic_filtering_level(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL:
        """Get Anisotropic Filtering level using cached instance."""
        level: ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL = self.anisotropic_filtering(gpu).GetLevel()
        assert isinstance(level, ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL)
        return level

    def set_anisotropic_filtering_level(self, gpu: ADLX.IADLXGPU, level: ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL) -> bool:
        """Set Anisotropic Filtering level using cached instance."""
        set_level: ADLX.ADLX_RESULT = self.anisotropic_filtering(gpu).SetLevel(level)
        assert isinstance(set_level, ADLX.ADLX_RESULT)

        if set_level in self._SUCCESS_RESULTS:
            assert self.anisotropic_filtering(gpu).GetLevel() == level
            return True
        return False

    def is_morphological_anti_aliasing_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Morphological Anti-Aliasing is supported using cached instance."""
        is_supported: bool = self.morphological_anti_aliasing(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_morphological_anti_aliasing_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Morphological Anti-Aliasing is enabled using cached instance."""
        is_enabled: bool = self.morphological_anti_aliasing(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_morphological_anti_aliasing_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Morphological Anti-Aliasing state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.morphological_anti_aliasing(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.morphological_anti_aliasing(gpu).IsEnabled() == enabled
            return True
        return False

    def is_anti_aliasing_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Anti-Aliasing is supported using cached instance."""
        is_supported: bool = self.anti_aliasing(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def get_anti_aliasing_mode(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_ANTI_ALIASING_MODE:
        """Get Anti-Aliasing mode using cached instance."""
        mode: ADLX.ADLX_ANTI_ALIASING_MODE = self.anti_aliasing(gpu).GetMode()
        print(type(mode))
        assert isinstance(mode, ADLX.ADLX_ANTI_ALIASING_MODE)
        return mode

    def set_anti_aliasing_mode(self, gpu: ADLX.IADLXGPU, mode: ADLX.ADLX_ANTI_ALIASING_MODE) -> bool:
        """Set Anti-Aliasing mode using cached instance."""
        set_mode: ADLX.ADLX_RESULT = self.anti_aliasing(gpu).SetMode(mode)
        assert isinstance(set_mode, ADLX.ADLX_RESULT)

        if set_mode in self._SUCCESS_RESULTS:
            assert self.anti_aliasing(gpu).GetMode() == mode
            return True
        return False

    def get_anti_aliasing_level(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_ANTI_ALIASING_LEVEL:
        """Get Anti-Aliasing level using cached instance."""
        level: ADLX.ADLX_ANTI_ALIASING_LEVEL = self.anti_aliasing(gpu).GetLevel()
        assert isinstance(level, ADLX.ADLX_ANTI_ALIASING_LEVEL)
        return level

    def set_anti_aliasing_level(self, gpu: ADLX.IADLXGPU, level: ADLX.ADLX_ANTI_ALIASING_LEVEL) -> bool:
        """Set Anti-Aliasing level using cached instance."""
        set_level: ADLX.ADLX_RESULT = self.anti_aliasing(gpu).SetLevel(level)
        assert isinstance(set_level, ADLX.ADLX_RESULT)

        if set_level in self._SUCCESS_RESULTS:
            assert self.anti_aliasing(gpu).GetLevel() == level
            return True
        return False

    def get_anti_aliasing_method(self, gpu: ADLX.IADLXGPU) -> Dict[str, int]:
        """Get Anti-Aliasing method using cached instance."""
        method: Dict[str, int] = self.anti_aliasing(gpu).GetMethod()
        assert isinstance(method, dict)
        return method

    def set_anti_aliasing_method(self, gpu: ADLX.IADLXGPU, method: int) -> bool:
        """Set Anti-Aliasing method using cached instance."""
        set_method: ADLX.ADLX_RESULT = self.anti_aliasing(gpu).SetMethod(method)
        assert isinstance(set_method, ADLX.ADLX_RESULT)

        if set_method in self._SUCCESS_RESULTS:
            assert self.anti_aliasing(gpu).GetMethod() == method
            return True
        return False    

    def is_frtc_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FRTC is supported using cached instance."""
        is_supported: bool = self.frtc(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_frtc_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FRTC is enabled using cached instance."""
        is_enabled: bool = self.frtc(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_frtc_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set FRTC state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.frtc(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.frtc(gpu).IsEnabled() == enabled
            return True
        return False

    def get_frtc_fps_range(self, gpu: ADLX.IADLXGPU) -> Dict[str, int]:
        """Get FRTC FPS range using cached instance."""
        fps_range: Dict[str, int] = self.frtc(gpu).GetFPSRange()
        assert isinstance(fps_range, dict)
        return fps_range

    def get_frtc_fps(self, gpu: ADLX.IADLXGPU) -> int:
        """Get current FRTC FPS using cached instance."""
        fps: int = self.frtc(gpu).GetFPS()
        assert isinstance(fps, int)
        return fps

    def set_frtc_fps(self, gpu: ADLX.IADLXGPU, fps: int) -> bool:
        """Set FRTC FPS using cached instance."""
        set_fps: ADLX.ADLX_RESULT = self.frtc(gpu).SetFPS(fps)
        assert isinstance(set_fps, ADLX.ADLX_RESULT)

        if set_fps in self._SUCCESS_RESULTS:
            assert self.frtc(gpu).GetFPS() == fps
            return True
        return False

    def is_wait_for_vertical_refresh_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Wait For Vertical Refresh is supported using cached instance."""
        is_supported: bool = self.wait_for_vertical_refresh(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_wait_for_vertical_refresh_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Wait For Vertical Refresh is enabled using cached instance."""
        is_enabled: bool = self.wait_for_vertical_refresh(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_wait_for_vertical_refresh_mode(self, gpu: ADLX.IADLXGPU, mode: ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE) -> bool:
        """Set Wait For Vertical Refresh mode using cached instance."""
        set_mode: ADLX.ADLX_RESULT = self.wait_for_vertical_refresh(gpu).SetMode(mode)
        assert isinstance(set_mode, ADLX.ADLX_RESULT)

        if set_mode in self._SUCCESS_RESULTS:
            assert self.wait_for_vertical_refresh(gpu).GetMode() == mode
            return True
        return False

    def get_wait_for_vertical_refresh_mode(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE:
        """Get current Wait For Vertical Refresh mode using cached instance."""
        mode: ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE = self.wait_for_vertical_refresh(gpu).GetMode()
        assert isinstance(mode, ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE)
        return mode

    def is_enhanced_sync_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Enhanced Sync is supported using cached instance."""
        is_supported: bool = self.enhanced_sync(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_enhanced_sync_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Enhanced Sync is enabled using cached instance."""
        is_enabled: bool = self.enhanced_sync(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_enhanced_sync_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Enhanced Sync state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.enhanced_sync(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.enhanced_sync(gpu).IsEnabled() == enabled
            return True
        return False

    def is_image_sharpening_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Image Sharpening is supported using cached instance."""
        is_supported: bool = self.image_sharpening(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_image_sharpening_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Image Sharpening is enabled using cached instance."""
        is_enabled: bool = self.image_sharpening(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_image_sharpening_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Image Sharpening state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.image_sharpening(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.image_sharpening(gpu).IsEnabled() == enabled
            return True
        return False

    def get_image_sharpness_range(self, gpu: ADLX.IADLXGPU) -> Dict[str, int]:
        """Get Image Sharpening sharpness range using cached instance."""
        sharpness_range: Dict[str, int] = self.image_sharpening(gpu).GetSharpnessRange()
        assert isinstance(sharpness_range, dict)
        return sharpness_range

    def get_image_sharpness(self, gpu: ADLX.IADLXGPU) -> int:
        """Get current Image Sharpening sharpness using cached instance."""
        sharpness: int = self.image_sharpening(gpu).GetSharpness()
        assert isinstance(sharpness, int)
        return sharpness

    def set_image_sharpness(self, gpu: ADLX.IADLXGPU, sharpness: int) -> bool:
        """Set Image Sharpening sharpness using cached instance."""
        set_sharpness: ADLX.ADLX_RESULT = self.image_sharpening(gpu).SetSharpness(sharpness)
        assert isinstance(set_sharpness, ADLX.ADLX_RESULT)

        if set_sharpness in self._SUCCESS_RESULTS:
            assert self.image_sharpening(gpu).GetSharpness() == sharpness
            return True
        return False

    def is_anti_lag_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Anti-Lag is supported using cached instance."""
        is_supported: bool = self.anti_lag(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_anti_lag_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Anti-Lag is enabled using cached instance."""
        is_enabled: bool = self.anti_lag(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_anti_lag_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Anti-Lag state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.anti_lag(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.anti_lag(gpu).IsEnabled() == enabled
            return True
        return False

    # def get_anti_lag_level(self, gpu: ADLX.IADLXGPU) -> ADLX.ADLX_ANTILAG_STATE:
    #     """Get Anti-Lag level using cached instance."""
    #     level: ADLX.ADLX_ANTILAG_STATE = self.anti_lag(gpu).GetLevel()
    #     assert isinstance(level, ADLX.ADLX_ANTILAG_STATE)
    #     return level

    # def set_anti_lag_level(self, gpu: ADLX.IADLXGPU, level: ADLX.ADLX_ANTILAG_STATE) -> bool:
    #     """Set Anti-Lag level using cached instance."""
    #     set_level: ADLX.ADLX_RESULT = self.anti_lag(gpu).SetLevel(level)
    #     assert isinstance(set_level, ADLX.ADLX_RESULT)

    #     if set_level == ADLX.ADLX_RESULT.ADLX_OK:
    #         assert self.anti_lag(gpu).GetLevel() == level
    #         return True
    #     else:
    #         return False

    def is_chill_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Chill is supported using cached instance."""
        is_supported: bool = self.chill(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_chill_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Chill is enabled using cached instance."""
        is_enabled: bool = self.chill(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_chill_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Chill state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.chill(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.chill(gpu).IsEnabled() == enabled
            return True
        return False

    def get_chill_fps_range(self, gpu: ADLX.IADLXGPU) -> Dict[str, int]:
        """Get Chill FPS range using cached instance."""
        fps_range: Dict[str, int] = self.chill(gpu).GetFPSRange()
        assert isinstance(fps_range, dict)
        return fps_range

    def get_chill_max_fps(self, gpu: ADLX.IADLXGPU) -> int:
        """Get current Chill FPS using cached instance."""
        fps: int = self.chill(gpu).GetMaxFPS()
        assert isinstance(fps, int)
        return fps

    def set_chill_max_fps(self, gpu: ADLX.IADLXGPU, fps: int) -> bool:
        """Set Chill FPS using cached instance."""
        set_fps: ADLX.ADLX_RESULT = self.chill(gpu).SetMaxFPS(fps)
        assert isinstance(set_fps, ADLX.ADLX_RESULT)

        if set_fps in self._SUCCESS_RESULTS:
            assert self.chill(gpu).GetMaxFPS() == fps
            return True
        return False

    def get_chill_min_fps(self, gpu: ADLX.IADLXGPU) -> int:
        """Get current Chill minimum FPS using cached instance."""
        min_fps: int = self.chill(gpu).GetMinFPS()
        assert isinstance(min_fps, int)
        return min_fps

    def set_chill_min_fps(self, gpu: ADLX.IADLXGPU, min_fps: int) -> bool:
        """Set Chill minimum FPS using cached instance."""
        set_min_fps: ADLX.ADLX_RESULT = self.chill(gpu).SetMinFPS(min_fps)
        assert isinstance(set_min_fps, ADLX.ADLX_RESULT)

        if set_min_fps in self._SUCCESS_RESULTS:
            assert self.chill(gpu).GetMinFPS() == min_fps
            return True
        return False

    def is_boost_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Boost is supported using cached instance."""
        is_supported: bool = self.boost(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported

    def is_boost_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if Boost is enabled using cached instance."""
        is_enabled: bool = self.boost(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_boost_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set Boost state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.boost(gpu).SetEnabled(enabled)
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.boost(gpu).IsEnabled() == enabled
            return True
        return False

    def get_boost_resolution_range(self, gpu: ADLX.IADLXGPU) -> Dict[str, int]:
        """Get Boost level range using cached instance."""
        resolution_range: Dict[str, int] = self.boost(gpu).GetResolutionRange()
        assert isinstance(resolution_range, dict)
        return resolution_range

    def get_boost_resolution(self, gpu: ADLX.IADLXGPU) -> int:
        """Get current Boost resolution using cached instance."""
        resolution: int = self.boost(gpu).GetResolution()
        assert isinstance(resolution, int)
        return resolution

    def set_boost_resolution(self, gpu: ADLX.IADLXGPU, resolution: int) -> bool:
        """Set Boost resolution using cached instance."""
        set_resolution: ADLX.ADLX_RESULT = self.boost(gpu).SetResolution(resolution)
        assert isinstance(set_resolution, ADLX.ADLX_RESULT)

        if set_resolution in self._SUCCESS_RESULTS:
            assert self.boost(gpu).GetResolution() == resolution
            return True
        return False

    def is_rsr_supported(self) -> bool:
        """Check if RSR is supported using cached instance."""
        is_supported: bool = self.rsr.IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported
    
    def is_rsr_enabled(self) -> bool:
        """Check if RSR is enabled using cached instance."""
        is_enabled: bool = self.rsr.IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_rsr_enabled(self, enabled: bool) -> bool:
        """Set RSR state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.rsr.SetEnabled(enabled)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.rsr.IsEnabled() == enabled
            return True
        return False

    def get_rsr_sharpness_range(self) -> Dict[str, int]:
        """Get RSR sharpness range using cached instance."""
        sharpness_range: Dict[str, int] = self.rsr.GetSharpnessRange()
        assert isinstance(sharpness_range, dict)
        return sharpness_range
    
    def get_rsr_sharpness(self) -> int:
        """Get current RSR sharpness using cached instance."""
        sharpness: int = self.rsr.GetSharpness()
        assert isinstance(sharpness, int)
        return sharpness
    
    def set_rsr_sharpness(self, sharpness: int) -> bool:
        """Set RSR sharpness using cached instance."""
        set_sharpness: ADLX.ADLX_RESULT = self.rsr.SetSharpness(sharpness)
        assert isinstance(set_sharpness, ADLX.ADLX_RESULT)

        if set_sharpness in self._SUCCESS_RESULTS:
            assert self.rsr.GetSharpness() == sharpness
            return True
        return False
        
    def is_afmf_supported(self) -> bool:
        """Check if afmf is supported using cached instance."""
        is_supported: bool = self.afmf.IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported
    
    def is_afmf_enabled(self) -> bool:
        """Check if afmf is enabled using cached instance."""
        is_enabled: bool = self.afmf.IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_afmf_enabled(self, enabled: bool) -> bool:
        """Set afmf state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.afmf.SetEnabled(enabled)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.afmf.IsEnabled() == enabled
            return True
        return False
    
    def is_fidelityfx_super_resolution_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FidelityFX Super Resolution is supported using cached instance."""
        is_supported: bool = self.fidelityfx_super_resolution(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported
    
    def is_fidelityfx_super_resolution_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FidelityFX Super Resolution is enabled using cached instance."""
        is_enabled: bool = self.fidelityfx_super_resolution(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_fidelityfx_super_resolution_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set FidelityFX Super Resolution state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.fidelityfx_super_resolution(gpu).SetEnabled(enabled)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.fidelityfx_super_resolution(gpu).IsEnabled() == enabled
            return True
        return False
    
    def is_fidelityfx_frame_gen_upgrade_supported(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FidelityFX Frame Generation Upgrade is supported using cached instance."""
        is_supported: bool = self.fidelityfx_frame_gen_upgrade(gpu).IsSupported()
        assert isinstance(is_supported, bool)
        return is_supported
    
    def is_fidelityfx_frame_gen_upgrade_enabled(self, gpu: ADLX.IADLXGPU) -> bool:
        """Check if FidelityFX Frame Generation Upgrade is enabled using cached instance."""
        is_enabled: bool = self.fidelityfx_frame_gen_upgrade(gpu).IsEnabled()
        assert isinstance(is_enabled, bool)
        return is_enabled

    def set_fidelityfx_frame_gen_upgrade_enabled(self, gpu: ADLX.IADLXGPU, enabled: bool) -> bool:
        """Set FidelityFX Frame Generation Upgrade state using cached instance."""
        set_enabled: ADLX.ADLX_RESULT = self.fidelityfx_frame_gen_upgrade(gpu).SetEnabled(enabled)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)

        if set_enabled in self._SUCCESS_RESULTS:
            assert self.fidelityfx_frame_gen_upgrade(gpu).IsEnabled() == enabled
            return True
        return False
