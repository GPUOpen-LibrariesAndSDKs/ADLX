//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// Multimedia (see SDK/Include/ISystem2.h, IMultiMedia.h)
// -------------------------------------------------------------------------------------------------
/// `IADLXSystem2` extends the system interface with multimedia and power tuning
/// services. Query it from `IADLXSystem` with the id `"IADLXSystem2"`.
#[repr(C)]
pub struct IADLXSystem2Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSystem2) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSystem2) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystem2,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerTuningServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem2,
        ppPowerTuningServices: *mut *mut IADLXPowerTuningServices,
    ) -> ADLX_RESULT,
    pub GetMultimediaServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem2,
        ppMultiMediaServices: *mut *mut IADLXMultimediaServices,
    ) -> ADLX_RESULT,
    pub GetGPUAppsListChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXSystem2,
        ppGPUAppsListChangedHandling: *mut *mut IADLXGPUAppsListChangedHandling,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystem2 {
    pub pVtbl: *const IADLXSystem2Vtbl,
}

/// `IADLXSystem3` additionally exposes `GetVariableGraphicsMemory`. Query it from
/// `IADLXSystem` with the id `"IADLXSystem3"`.
#[repr(C)]
pub struct IADLXSystem3Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSystem3) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSystem3) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystem3,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerTuningServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem3,
        ppPowerTuningServices: *mut *mut IADLXPowerTuningServices,
    ) -> ADLX_RESULT,
    pub GetMultimediaServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem3,
        ppMultiMediaServices: *mut *mut IADLXMultimediaServices,
    ) -> ADLX_RESULT,
    pub GetGPUAppsListChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXSystem3,
        ppGPUAppsListChangedHandling: *mut *mut IADLXGPUAppsListChangedHandling,
    ) -> ADLX_RESULT,
    pub GetVariableGraphicsMemory: unsafe extern "system" fn(
        pThis: *mut IADLXSystem3,
        ppVariableGraphicsMemory: *mut *mut IADLXVariableGraphicsMemory,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystem3 {
    pub pVtbl: *const IADLXSystem3Vtbl,
}

#[repr(C)]
pub struct IADLXMultimediaServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXMultimediaServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXMultimediaServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetMultimediaChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaServices,
        ppMultimediaChangedHandling: *mut *mut IADLXMultimediaChangedHandling,
    ) -> ADLX_RESULT,
    pub GetVideoUpscale: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaServices,
        pGPU: *mut IADLXGPU,
        ppVideoUpscale: *mut *mut IADLXVideoUpscale,
    ) -> ADLX_RESULT,
    pub GetVideoSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaServices,
        pGPU: *mut IADLXGPU,
        ppVideoSuperResolution: *mut *mut IADLXVideoSuperResolution,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXMultimediaServices {
    pub pVtbl: *const IADLXMultimediaServicesVtbl,
}

/// Vtable for an application-implemented `IADLXMultimediaChangedEventListener`.
#[repr(C)]
pub struct IADLXMultimediaChangedEventListenerVtbl {
    pub OnMultimediaChanged: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaChangedEventListener,
        pEvent: *mut IADLXMultimediaChangedEvent,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLXMultimediaChangedEventListener {
    pub pVtbl: *const IADLXMultimediaChangedEventListenerVtbl,
}

#[repr(C)]
pub struct IADLXMultimediaChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXMultimediaChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXMultimediaChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AddMultimediaEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaChangedHandling,
        pListener: *mut IADLXMultimediaChangedEventListener,
    ) -> ADLX_RESULT,
    pub RemoveMultimediaEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXMultimediaChangedHandling,
        pListener: *mut IADLXMultimediaChangedEventListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXMultimediaChangedHandling {
    pub pVtbl: *const IADLXMultimediaChangedHandlingVtbl,
}

#[repr(C)]
pub struct IADLXVideoUpscaleVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXVideoUpscale) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXVideoUpscale) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXVideoUpscale,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXVideoUpscale,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLXVideoUpscale,
        isEnabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetSharpnessRange: unsafe extern "system" fn(
        pThis: *mut IADLXVideoUpscale,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetSharpness: unsafe extern "system" fn(
        pThis: *mut IADLXVideoUpscale,
        currentSharpness: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLXVideoUpscale, enable: adlx_bool) -> ADLX_RESULT,
    pub SetSharpness:
        unsafe extern "system" fn(pThis: *mut IADLXVideoUpscale, minSharp: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXVideoUpscale {
    pub pVtbl: *const IADLXVideoUpscaleVtbl,
}

// Video Super Resolution is a pure on/off feature.
toggle_interface!(IADLXVideoSuperResolution, IADLXVideoSuperResolutionVtbl);
