//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// 3D settings (see SDK/Include/I3DSettings.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLX3DSettingsServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetAntiLag: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DAntiLag: *mut *mut IADLX3DAntiLag,
    ) -> ADLX_RESULT,
    pub GetChill: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DChill: *mut *mut IADLX3DChill,
    ) -> ADLX_RESULT,
    pub GetBoost: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DBoost: *mut *mut IADLX3DBoost,
    ) -> ADLX_RESULT,
    pub GetImageSharpening: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DImageSharpening: *mut *mut IADLX3DImageSharpening,
    ) -> ADLX_RESULT,
    pub GetEnhancedSync: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DEnhancedSync: *mut *mut IADLX3DEnhancedSync,
    ) -> ADLX_RESULT,
    pub GetWaitForVerticalRefresh: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DWaitForVerticalRefresh: *mut *mut IADLX3DWaitForVerticalRefresh,
    ) -> ADLX_RESULT,
    pub GetFrameRateTargetControl: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DFrameRateTargetControl: *mut *mut IADLX3DFrameRateTargetControl,
    ) -> ADLX_RESULT,
    pub GetAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DAntiAliasing: *mut *mut IADLX3DAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetMorphologicalAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DMorphologicalAntiAliasing: *mut *mut IADLX3DMorphologicalAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetAnisotropicFiltering: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DAnisotropicFiltering: *mut *mut IADLX3DAnisotropicFiltering,
    ) -> ADLX_RESULT,
    pub GetTessellation: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DTessellation: *mut *mut IADLX3DTessellation,
    ) -> ADLX_RESULT,
    pub GetRadeonSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pp3DRadeonSuperResolution: *mut *mut IADLX3DRadeonSuperResolution,
    ) -> ADLX_RESULT,
    pub GetResetShaderCache: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pGPU: *mut IADLXGPU,
        pp3DResetShaderCache: *mut *mut IADLX3DResetShaderCache,
    ) -> ADLX_RESULT,
    pub Get3DSettingsChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices,
        pp3DSettingsChangedHandling: *mut *mut IADLX3DSettingsChangedHandling,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DSettingsServices {
    pub pVtbl: *const IADLX3DSettingsServicesVtbl,
}

#[repr(C)]
pub struct IADLX3DAntiLagVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DAntiLag) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DAntiLag) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiLag,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiLag,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiLag,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLX3DAntiLag, enable: adlx_bool) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DAntiLag {
    pub pVtbl: *const IADLX3DAntiLagVtbl,
}

// Enhanced Sync is a pure on/off feature.
toggle_interface!(IADLX3DEnhancedSync, IADLX3DEnhancedSyncVtbl);

#[repr(C)]
pub struct IADLX3DBoostVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DBoost) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DBoost) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DBoost,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DBoost,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DBoost,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetResolutionRange: unsafe extern "system" fn(
        pThis: *mut IADLX3DBoost,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetResolution: unsafe extern "system" fn(
        pThis: *mut IADLX3DBoost,
        currentMinRes: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLX3DBoost, enable: adlx_bool) -> ADLX_RESULT,
    pub SetResolution:
        unsafe extern "system" fn(pThis: *mut IADLX3DBoost, minRes: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DBoost {
    pub pVtbl: *const IADLX3DBoostVtbl,
}

#[repr(C)]
pub struct IADLX3DChillVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DChill) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DChill) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetFPSRange: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetMinFPS: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        currentMinFPS: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetMaxFPS: unsafe extern "system" fn(
        pThis: *mut IADLX3DChill,
        currentMaxFPS: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLX3DChill, enable: adlx_bool) -> ADLX_RESULT,
    pub SetMinFPS:
        unsafe extern "system" fn(pThis: *mut IADLX3DChill, minFPS: adlx_int) -> ADLX_RESULT,
    pub SetMaxFPS:
        unsafe extern "system" fn(pThis: *mut IADLX3DChill, maxFPS: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DChill {
    pub pVtbl: *const IADLX3DChillVtbl,
}

#[repr(C)]
pub struct IADLX3DImageSharpeningVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DImageSharpening) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DImageSharpening) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetSharpnessRange: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetSharpness: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        currentSharpness: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        enable: adlx_bool,
    ) -> ADLX_RESULT,
    pub SetSharpness: unsafe extern "system" fn(
        pThis: *mut IADLX3DImageSharpening,
        sharpness: adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DImageSharpening {
    pub pVtbl: *const IADLX3DImageSharpeningVtbl,
}

#[repr(C)]
pub struct IADLX3DRadeonSuperResolutionVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DRadeonSuperResolution) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DRadeonSuperResolution) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        enable: adlx_bool,
    ) -> ADLX_RESULT,
    pub GetSharpnessRange: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetSharpness: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        currentSharpness: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetSharpness: unsafe extern "system" fn(
        pThis: *mut IADLX3DRadeonSuperResolution,
        sharpness: adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DRadeonSuperResolution {
    pub pVtbl: *const IADLX3DRadeonSuperResolutionVtbl,
}

// Enum-valued getters/setters are declared with `c_int`; the concrete ADLX enum
// values are documented in ADLXDefines.h.
#[repr(C)]
pub struct IADLX3DAnisotropicFilteringVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DAnisotropicFiltering) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DAnisotropicFiltering) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetLevel: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        currentLevel: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        enable: adlx_bool,
    ) -> ADLX_RESULT,
    pub SetLevel: unsafe extern "system" fn(
        pThis: *mut IADLX3DAnisotropicFiltering,
        level: c_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DAnisotropicFiltering {
    pub pVtbl: *const IADLX3DAnisotropicFilteringVtbl,
}

#[repr(C)]
pub struct IADLX3DTessellationVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DTessellation) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DTessellation) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DTessellation,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DTessellation,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMode: unsafe extern "system" fn(
        pThis: *mut IADLX3DTessellation,
        currentMode: *mut c_int,
    ) -> ADLX_RESULT,
    pub GetLevel: unsafe extern "system" fn(
        pThis: *mut IADLX3DTessellation,
        currentLevel: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetMode:
        unsafe extern "system" fn(pThis: *mut IADLX3DTessellation, mode: c_int) -> ADLX_RESULT,
    pub SetLevel:
        unsafe extern "system" fn(pThis: *mut IADLX3DTessellation, level: c_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DTessellation {
    pub pVtbl: *const IADLX3DTessellationVtbl,
}

#[repr(C)]
pub struct IADLX3DResetShaderCacheVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DResetShaderCache) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DResetShaderCache) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DResetShaderCache,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DResetShaderCache,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub ResetShaderCache:
        unsafe extern "system" fn(pThis: *mut IADLX3DResetShaderCache) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DResetShaderCache {
    pub pVtbl: *const IADLX3DResetShaderCacheVtbl,
}

// Morphological Anti-Aliasing is a pure on/off feature.
toggle_interface!(
    IADLX3DMorphologicalAntiAliasing,
    IADLX3DMorphologicalAntiAliasingVtbl
);

#[repr(C)]
pub struct IADLX3DAntiAliasingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DAntiAliasing) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DAntiAliasing) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiAliasing,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiAliasing,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMode: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiAliasing,
        currentMode: *mut c_int,
    ) -> ADLX_RESULT,
    pub GetLevel: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiAliasing,
        currentLevel: *mut c_int,
    ) -> ADLX_RESULT,
    pub GetMethod: unsafe extern "system" fn(
        pThis: *mut IADLX3DAntiAliasing,
        currentMethod: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetMode:
        unsafe extern "system" fn(pThis: *mut IADLX3DAntiAliasing, mode: c_int) -> ADLX_RESULT,
    pub SetLevel:
        unsafe extern "system" fn(pThis: *mut IADLX3DAntiAliasing, level: c_int) -> ADLX_RESULT,
    pub SetMethod:
        unsafe extern "system" fn(pThis: *mut IADLX3DAntiAliasing, method: c_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DAntiAliasing {
    pub pVtbl: *const IADLX3DAntiAliasingVtbl,
}

#[repr(C)]
pub struct IADLX3DWaitForVerticalRefreshVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DWaitForVerticalRefresh) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DWaitForVerticalRefresh) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DWaitForVerticalRefresh,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DWaitForVerticalRefresh,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DWaitForVerticalRefresh,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMode: unsafe extern "system" fn(
        pThis: *mut IADLX3DWaitForVerticalRefresh,
        currentMode: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetMode: unsafe extern "system" fn(
        pThis: *mut IADLX3DWaitForVerticalRefresh,
        mode: c_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DWaitForVerticalRefresh {
    pub pVtbl: *const IADLX3DWaitForVerticalRefreshVtbl,
}

#[repr(C)]
pub struct IADLX3DFrameRateTargetControlVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DFrameRateTargetControl) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DFrameRateTargetControl) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetFPSRange: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetFPS: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        currentFPS: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        enable: adlx_bool,
    ) -> ADLX_RESULT,
    pub SetFPS: unsafe extern "system" fn(
        pThis: *mut IADLX3DFrameRateTargetControl,
        maxFPS: adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DFrameRateTargetControl {
    pub pVtbl: *const IADLX3DFrameRateTargetControlVtbl,
}

// AMD Fluid Motion Frames (AFMF) is a pure on/off feature, reached through
// IADLX3DSettingsServices1::GetAMDFluidMotionFrames.
toggle_interface!(IADLX3DAMDFluidMotionFrames, IADLX3DAMDFluidMotionFramesVtbl);

/// `IADLX3DSettingsServices1` extends the 3D settings services with
/// `GetAMDFluidMotionFrames`. Query it from `IADLX3DSettingsServices` with the id
/// `"IADLX3DSettingsServices1"`.
#[repr(C)]
pub struct IADLX3DSettingsServices1Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices1) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices1) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetAntiLag: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DAntiLag: *mut *mut IADLX3DAntiLag,
    ) -> ADLX_RESULT,
    pub GetChill: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DChill: *mut *mut IADLX3DChill,
    ) -> ADLX_RESULT,
    pub GetBoost: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DBoost: *mut *mut IADLX3DBoost,
    ) -> ADLX_RESULT,
    pub GetImageSharpening: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DImageSharpening: *mut *mut IADLX3DImageSharpening,
    ) -> ADLX_RESULT,
    pub GetEnhancedSync: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DEnhancedSync: *mut *mut IADLX3DEnhancedSync,
    ) -> ADLX_RESULT,
    pub GetWaitForVerticalRefresh: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DWaitForVerticalRefresh: *mut *mut IADLX3DWaitForVerticalRefresh,
    ) -> ADLX_RESULT,
    pub GetFrameRateTargetControl: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DFrameRateTargetControl: *mut *mut IADLX3DFrameRateTargetControl,
    ) -> ADLX_RESULT,
    pub GetAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DAntiAliasing: *mut *mut IADLX3DAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetMorphologicalAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DMorphologicalAntiAliasing: *mut *mut IADLX3DMorphologicalAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetAnisotropicFiltering: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DAnisotropicFiltering: *mut *mut IADLX3DAnisotropicFiltering,
    ) -> ADLX_RESULT,
    pub GetTessellation: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DTessellation: *mut *mut IADLX3DTessellation,
    ) -> ADLX_RESULT,
    pub GetRadeonSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pp3DRadeonSuperResolution: *mut *mut IADLX3DRadeonSuperResolution,
    ) -> ADLX_RESULT,
    pub GetResetShaderCache: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pGPU: *mut IADLXGPU,
        pp3DResetShaderCache: *mut *mut IADLX3DResetShaderCache,
    ) -> ADLX_RESULT,
    pub Get3DSettingsChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pp3DSettingsChangedHandling: *mut *mut IADLX3DSettingsChangedHandling,
    ) -> ADLX_RESULT,
    pub GetAMDFluidMotionFrames: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices1,
        pp3DGetAMDFluidMotionFrames: *mut *mut IADLX3DAMDFluidMotionFrames,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DSettingsServices1 {
    pub pVtbl: *const IADLX3DSettingsServices1Vtbl,
}

// FidelityFX Super Resolution (FSR) is a pure on/off feature, reached through
// IADLX3DSettingsServices3::GetFidelityFXSuperResolution.
toggle_interface!(IADLX3DFidelityFXSuperResolution, IADLX3DFidelityFXSuperResolutionVtbl);

/// `IADLX3DSettingsServices3` adds newer 3D feature getters (FSR, AFMF, frame-gen
/// upgrade). Query it from `IADLX3DSettingsServices` with the id
/// `"IADLX3DSettingsServices3"`.
#[repr(C)]
pub struct IADLX3DSettingsServices3Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices3) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsServices3) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetAntiLag: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DAntiLag,
    ) -> ADLX_RESULT,
    pub GetChill: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DChill,
    ) -> ADLX_RESULT,
    pub GetBoost: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DBoost,
    ) -> ADLX_RESULT,
    pub GetImageSharpening: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DImageSharpening,
    ) -> ADLX_RESULT,
    pub GetEnhancedSync: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DEnhancedSync,
    ) -> ADLX_RESULT,
    pub GetWaitForVerticalRefresh: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DWaitForVerticalRefresh,
    ) -> ADLX_RESULT,
    pub GetFrameRateTargetControl: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DFrameRateTargetControl,
    ) -> ADLX_RESULT,
    pub GetAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetMorphologicalAntiAliasing: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DMorphologicalAntiAliasing,
    ) -> ADLX_RESULT,
    pub GetAnisotropicFiltering: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DAnisotropicFiltering,
    ) -> ADLX_RESULT,
    pub GetTessellation: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DTessellation,
    ) -> ADLX_RESULT,
    pub GetRadeonSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pp: *mut *mut IADLX3DRadeonSuperResolution,
    ) -> ADLX_RESULT,
    pub GetResetShaderCache: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DResetShaderCache,
    ) -> ADLX_RESULT,
    pub Get3DSettingsChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pp: *mut *mut IADLX3DSettingsChangedHandling,
    ) -> ADLX_RESULT,
    pub GetAMDFluidMotionFrames: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pp: *mut *mut IADLX3DAMDFluidMotionFrames,
    ) -> ADLX_RESULT,
    pub GetImageSharpenDesktop: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DImageSharpenDesktop,
    ) -> ADLX_RESULT,
    pub GetFidelityFXSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DFidelityFXSuperResolution,
    ) -> ADLX_RESULT,
    pub GetFidelityFXFrameGenUpgrade: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsServices3,
        pGPU: *mut IADLXGPU,
        pp: *mut *mut IADLX3DFidelityFXFrameGenUpgrade,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DSettingsServices3 {
    pub pVtbl: *const IADLX3DSettingsServices3Vtbl,
}

// ADLX_FFX_FRAME_GEN_RATIO values (see SDK/Include/ADLXDefines.h).
pub const FFX_FRAME_GEN_UNKNOWN: c_int = 0;
pub const FFX_FRAME_GEN_2X: c_int = 1;

/// `IADLX3DFidelityFXFrameGenUpgrade` (see SDK/Include/I3DSettings3.h). Obtained from
/// `IADLX3DSettingsServices3::GetFidelityFXFrameGenUpgrade`.
#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgradeVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgrade) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgrade) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetAvailableRatios: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        ratios: *mut *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
    ) -> ADLX_RESULT,
    pub GetRatio: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        ratio: *mut c_int,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        enable: adlx_bool,
    ) -> ADLX_RESULT,
    pub SetRatio: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgrade,
        ratio: c_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgrade {
    pub pVtbl: *const IADLX3DFidelityFXFrameGenUpgradeVtbl,
}

/// A single frame-generation ratio option (see SDK/Include/I3DSettings3.h).
#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgradeRatioOptionVtbl {
    pub Acquire:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption) -> adlx_long,
    pub Release:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Ratio: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption,
        ratio: *mut c_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgradeRatioOption {
    pub pVtbl: *const IADLX3DFidelityFXFrameGenUpgradeRatioOptionVtbl,
}

/// A list of frame-generation ratio options (see SDK/Include/I3DSettings3.h).
#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgradeRatioOptionListVtbl {
    pub Acquire: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
    ) -> adlx_long,
    pub Release: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
    ) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Size:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList) -> adlx_uint,
    pub Empty:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList) -> adlx_bool,
    pub Begin:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList) -> adlx_uint,
    pub End:
        unsafe extern "system" fn(pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList) -> adlx_uint,
    pub At: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub Clear: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
    ) -> ADLX_RESULT,
    pub Remove_Back: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
    ) -> ADLX_RESULT,
    pub Add_Back: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
        pItem: *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub At_OptionList: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
        location: adlx_uint,
        ppItem: *mut *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption,
    ) -> ADLX_RESULT,
    pub Add_Back_OptionList: unsafe extern "system" fn(
        pThis: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList,
        pItem: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DFidelityFXFrameGenUpgradeRatioOptionList {
    pub pVtbl: *const IADLX3DFidelityFXFrameGenUpgradeRatioOptionListVtbl,
}

/// Vtable for an application-implemented `IADLX3DSettingsChangedListener`.
#[repr(C)]
pub struct IADLX3DSettingsChangedListenerVtbl {
    pub On3DSettingsChanged: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsChangedListener,
        p3DSettingsChangedEvent: *mut IADLX3DSettingsChangedEvent,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLX3DSettingsChangedListener {
    pub pVtbl: *const IADLX3DSettingsChangedListenerVtbl,
}

#[repr(C)]
pub struct IADLX3DSettingsChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLX3DSettingsChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Add3DSettingsEventListener: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsChangedHandling,
        p3DSettingsChangedListener: *mut IADLX3DSettingsChangedListener,
    ) -> ADLX_RESULT,
    pub Remove3DSettingsEventListener: unsafe extern "system" fn(
        pThis: *mut IADLX3DSettingsChangedHandling,
        p3DSettingsChangedListener: *mut IADLX3DSettingsChangedListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLX3DSettingsChangedHandling {
    pub pVtbl: *const IADLX3DSettingsChangedHandlingVtbl,
}

// -------------------------------------------------------------------------------------------------
