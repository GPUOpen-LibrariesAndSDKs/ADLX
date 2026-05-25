//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// IADLXDisplayServices (see SDK/Include/IDisplays.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXDisplayServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetNumberOfDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        numDisplays: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        ppDisplays: *mut *mut IADLXDisplayList,
    ) -> ADLX_RESULT,
    pub Get3DLUT: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppDisp3DLUT: *mut *mut IADLXDisplay3DLUT,
    ) -> ADLX_RESULT,
    pub GetGamut: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppDispGamut: *mut *mut IADLXDisplayGamut,
    ) -> ADLX_RESULT,
    pub GetGamma: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppDispGamma: *mut *mut IADLXDisplayGamma,
    ) -> ADLX_RESULT,
    pub GetDisplayChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        ppDisplayChangedHandling: *mut *mut IADLXDisplayChangedHandling,
    ) -> ADLX_RESULT,
    pub GetFreeSync: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppFreeSync: *mut *mut IADLXDisplayFreeSync,
    ) -> ADLX_RESULT,
    pub GetVirtualSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppVSR: *mut *mut IADLXDisplayVSR,
    ) -> ADLX_RESULT,
    pub GetGPUScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppGPUScaling: *mut *mut IADLXDisplayGPUScaling,
    ) -> ADLX_RESULT,
    pub GetScalingMode: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppScalingMode: *mut *mut IADLXDisplayScalingMode,
    ) -> ADLX_RESULT,
    pub GetIntegerScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppIntegerScaling: *mut *mut IADLXDisplayIntegerScaling,
    ) -> ADLX_RESULT,
    pub GetColorDepth: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppColorDepth: *mut *mut IADLXDisplayColorDepth,
    ) -> ADLX_RESULT,
    pub GetPixelFormat: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppPixelFormat: *mut *mut IADLXDisplayPixelFormat,
    ) -> ADLX_RESULT,
    pub GetCustomColor: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppCustomColor: *mut *mut IADLXDisplayCustomColor,
    ) -> ADLX_RESULT,
    pub GetHDCP: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppHDCP: *mut *mut IADLXDisplayHDCP,
    ) -> ADLX_RESULT,
    pub GetCustomResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppCustomResolution: *mut *mut IADLXDisplayCustomResolution,
    ) -> ADLX_RESULT,
    pub GetVariBright: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices,
        pDisplay: *mut IADLXDisplay,
        ppVariBright: *mut *mut IADLXDisplayVariBright,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayServices {
    pub pVtbl: *const IADLXDisplayServicesVtbl,
}

// -------------------------------------------------------------------------------------------------
// IADLXDisplayList (see SDK/Include/IDisplays.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXDisplayListVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayList,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Size: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_uint,
    pub Empty: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_bool,
    pub Begin: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_uint,
    pub End: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> adlx_uint,
    pub At: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub Clear: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> ADLX_RESULT,
    pub Remove_Back: unsafe extern "system" fn(pThis: *mut IADLXDisplayList) -> ADLX_RESULT,
    pub Add_Back: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayList,
        pItem: *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub At_DisplayList: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXDisplay,
    ) -> ADLX_RESULT,
    pub Add_Back_DisplayList: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayList,
        pItem: *mut IADLXDisplay,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayList {
    pub pVtbl: *const IADLXDisplayListVtbl,
}

// -------------------------------------------------------------------------------------------------
// IADLXDisplay (see SDK/Include/IDisplays.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXDisplayVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplay) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplay) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub ManufacturerID: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        manufacturerID: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub DisplayType:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay, displayType: *mut c_int) -> ADLX_RESULT,
    pub ConnectorType:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay, connectType: *mut c_int) -> ADLX_RESULT,
    pub Name: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        displayName: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub EDID: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        edid: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub NativeResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        maxHResolution: *mut adlx_int,
        maxVResolution: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub RefreshRate: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        refreshRate: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub PixelClock: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        pixelClock: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub ScanType:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay, scanType: *mut c_int) -> ADLX_RESULT,
    pub GetGPU: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        ppGPU: *mut *mut IADLXGPU,
    ) -> ADLX_RESULT,
    pub UniqueId: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay,
        uniqueId: *mut adlx_size,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplay {
    pub pVtbl: *const IADLXDisplayVtbl,
}

// -------------------------------------------------------------------------------------------------
// IADLXDisplayChangedHandling and the display-list listener (see SDK/Include/IDisplays.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXDisplayChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AddDisplayListEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayListChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDisplayListEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayListChangedListener,
    ) -> ADLX_RESULT,
    pub AddDisplayGamutEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayGamutChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDisplayGamutEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayGamutChangedListener,
    ) -> ADLX_RESULT,
    pub AddDisplayGammaEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayGammaChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDisplayGammaEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplayGammaChangedListener,
    ) -> ADLX_RESULT,
    pub AddDisplay3DLUTEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplay3DLUTChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDisplay3DLUTEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplay3DLUTChangedListener,
    ) -> ADLX_RESULT,
    pub AddDisplaySettingsEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplaySettingsChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDisplaySettingsEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayChangedHandling,
        pListener: *mut IADLXDisplaySettingsChangedListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayChangedHandling {
    pub pVtbl: *const IADLXDisplayChangedHandlingVtbl,
}

/// Vtable for an application-implemented `IADLXDisplayListChangedListener`.
///
/// The listener has a single method, `OnDisplayListChanged`, called by ADLX when
/// the display list changes. Returning `true` (non-zero) lets ADLX keep notifying
/// the next listener.
#[repr(C)]
pub struct IADLXDisplayListChangedListenerVtbl {
    pub OnDisplayListChanged: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayListChangedListener,
        pNewDisplays: *mut IADLXDisplayList,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLXDisplayListChangedListener {
    pub pVtbl: *const IADLXDisplayListChangedListenerVtbl,
}

// -------------------------------------------------------------------------------------------------
// Simple on/off display features (see SDK/Include/IDisplaySettings.h)
// -------------------------------------------------------------------------------------------------
toggle_interface!(IADLXDisplayFreeSync, IADLXDisplayFreeSyncVtbl);
toggle_interface!(IADLXDisplayVSR, IADLXDisplayVSRVtbl);
toggle_interface!(IADLXDisplayGPUScaling, IADLXDisplayGPUScalingVtbl);
toggle_interface!(IADLXDisplayIntegerScaling, IADLXDisplayIntegerScalingVtbl);
toggle_interface!(IADLXDisplayHDCP, IADLXDisplayHDCPVtbl);

#[repr(C)]
pub struct IADLXDisplayScalingModeVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayScalingMode) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayScalingMode) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayScalingMode,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayScalingMode,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMode: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayScalingMode,
        currentMode: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetMode:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayScalingMode, mode: c_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayScalingMode {
    pub pVtbl: *const IADLXDisplayScalingModeVtbl,
}

#[repr(C)]
pub struct IADLXDisplayColorDepthVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayColorDepth) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayColorDepth) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetValue: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        currentColorDepth: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetValue: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        colorDepth: c_int,
    ) -> ADLX_RESULT,
    pub IsSupportedColorDepth: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        colorDepth: c_int,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_6: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_8: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_10: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_12: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_14: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBPC_16: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayColorDepth,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayColorDepth {
    pub pVtbl: *const IADLXDisplayColorDepthVtbl,
}

#[repr(C)]
pub struct IADLXDisplayPixelFormatVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayPixelFormat) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayPixelFormat) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetValue: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        pixelFormat: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetValue: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        pixelFormat: c_int,
    ) -> ADLX_RESULT,
    pub IsSupportedPixelFormat: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        pixelFormat: c_int,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedRGB444Full: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedYCbCr444: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedYCbCr422: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedRGB444Limited: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedYCbCr420: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayPixelFormat,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayPixelFormat {
    pub pVtbl: *const IADLXDisplayPixelFormatVtbl,
}

#[repr(C)]
pub struct IADLXDisplayVariBrightVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        enabled: adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentMaximizeBrightness: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        maximizeBrightness: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentOptimizeBrightness: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        optimizeBrightness: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentBalanced: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        balanced: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentOptimizeBattery: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        optimizeBattery: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentMaximizeBattery: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayVariBright,
        maximizeBattery: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetMaximizeBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> ADLX_RESULT,
    pub SetOptimizeBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> ADLX_RESULT,
    pub SetBalanced: unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> ADLX_RESULT,
    pub SetOptimizeBattery:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> ADLX_RESULT,
    pub SetMaximizeBattery:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayVariBright) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayVariBright {
    pub pVtbl: *const IADLXDisplayVariBrightVtbl,
}

// Display Blanking (see SDK/Include/IDisplaySettings.h); reached through
// IADLXDisplayServices1::GetDisplayBlanking.
#[repr(C)]
pub struct IADLXDisplayBlankingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayBlanking) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayBlanking) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayBlanking,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayBlanking,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentBlanked: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayBlanking,
        blanked: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentUnblanked: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayBlanking,
        unBlanked: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetBlanked: unsafe extern "system" fn(pThis: *mut IADLXDisplayBlanking) -> ADLX_RESULT,
    pub SetUnblanked: unsafe extern "system" fn(pThis: *mut IADLXDisplayBlanking) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayBlanking {
    pub pVtbl: *const IADLXDisplayBlankingVtbl,
}

/// `IADLXDisplayServices1` extends the display services with `GetDisplayBlanking`.
/// Query it from `IADLXDisplayServices` with the id `"IADLXDisplayServices1"`.
#[repr(C)]
pub struct IADLXDisplayServices1Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices1) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices1) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetNumberOfDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        numDisplays: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        ppDisplays: *mut *mut IADLXDisplayList,
    ) -> ADLX_RESULT,
    pub Get3DLUT: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppDisp3DLUT: *mut *mut IADLXDisplay3DLUT,
    ) -> ADLX_RESULT,
    pub GetGamut: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppDispGamut: *mut *mut IADLXDisplayGamut,
    ) -> ADLX_RESULT,
    pub GetGamma: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppDispGamma: *mut *mut IADLXDisplayGamma,
    ) -> ADLX_RESULT,
    pub GetDisplayChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        ppDisplayChangedHandling: *mut *mut IADLXDisplayChangedHandling,
    ) -> ADLX_RESULT,
    pub GetFreeSync: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppFreeSync: *mut *mut IADLXDisplayFreeSync,
    ) -> ADLX_RESULT,
    pub GetVirtualSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppVSR: *mut *mut IADLXDisplayVSR,
    ) -> ADLX_RESULT,
    pub GetGPUScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppGPUScaling: *mut *mut IADLXDisplayGPUScaling,
    ) -> ADLX_RESULT,
    pub GetScalingMode: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppScalingMode: *mut *mut IADLXDisplayScalingMode,
    ) -> ADLX_RESULT,
    pub GetIntegerScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppIntegerScaling: *mut *mut IADLXDisplayIntegerScaling,
    ) -> ADLX_RESULT,
    pub GetColorDepth: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppColorDepth: *mut *mut IADLXDisplayColorDepth,
    ) -> ADLX_RESULT,
    pub GetPixelFormat: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppPixelFormat: *mut *mut IADLXDisplayPixelFormat,
    ) -> ADLX_RESULT,
    pub GetCustomColor: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppCustomColor: *mut *mut IADLXDisplayCustomColor,
    ) -> ADLX_RESULT,
    pub GetHDCP: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppHDCP: *mut *mut IADLXDisplayHDCP,
    ) -> ADLX_RESULT,
    pub GetCustomResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppCustomResolution: *mut *mut IADLXDisplayCustomResolution,
    ) -> ADLX_RESULT,
    pub GetVariBright: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppVariBright: *mut *mut IADLXDisplayVariBright,
    ) -> ADLX_RESULT,
    pub GetDisplayBlanking: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices1,
        pDisplay: *mut IADLXDisplay,
        ppDisplayBlanking: *mut *mut IADLXDisplayBlanking,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayServices1 {
    pub pVtbl: *const IADLXDisplayServices1Vtbl,
}

// Dynamic Refresh Rate Control and FreeSync Color Accuracy are pure on/off features
// reached through IADLXDisplayServices3.
toggle_interface!(
    IADLXDisplayDynamicRefreshRateControl,
    IADLXDisplayDynamicRefreshRateControlVtbl
);
toggle_interface!(
    IADLXDisplayFreeSyncColorAccuracy,
    IADLXDisplayFreeSyncColorAccuracyVtbl
);

#[repr(C)]
pub struct IADLXDisplayConnectivityExperienceVtbl {
    pub Acquire:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayConnectivityExperience) -> adlx_long,
    pub Release:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayConnectivityExperience) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedHDMIQualityDetection: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedDPLink: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabledHDMIQualityDetection: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabledHDMIQualityDetection: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        enabled: adlx_bool,
    ) -> ADLX_RESULT,
    pub GetDPLinkRate: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        linkRate: *mut c_int,
    ) -> ADLX_RESULT,
    pub GetNumberOfActiveLanes: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        numActiveLanes: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetNumberOfTotalLanes: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        numTotalLanes: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetRelativePreEmphasis: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        relativePreEmphasis: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetRelativePreEmphasis: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        relativePreEmphasis: adlx_int,
    ) -> ADLX_RESULT,
    pub GetRelativeVoltageSwing: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        relativeVoltageSwing: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetRelativeVoltageSwing: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        relativeVoltageSwing: adlx_int,
    ) -> ADLX_RESULT,
    pub IsEnabledLinkProtection: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayConnectivityExperience,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayConnectivityExperience {
    pub pVtbl: *const IADLXDisplayConnectivityExperienceVtbl,
}

/// `IADLXDisplayServices3` adds several newer display feature getters. Query it from
/// `IADLXDisplayServices` with the id `"IADLXDisplayServices3"`.
#[repr(C)]
pub struct IADLXDisplayServices3Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices3) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices3) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetNumberOfDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        numDisplays: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        ppDisplays: *mut *mut IADLXDisplayList,
    ) -> ADLX_RESULT,
    pub Get3DLUT: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDisp3DLUT: *mut *mut IADLXDisplay3DLUT,
    ) -> ADLX_RESULT,
    pub GetGamut: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDispGamut: *mut *mut IADLXDisplayGamut,
    ) -> ADLX_RESULT,
    pub GetGamma: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDispGamma: *mut *mut IADLXDisplayGamma,
    ) -> ADLX_RESULT,
    pub GetDisplayChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        ppDisplayChangedHandling: *mut *mut IADLXDisplayChangedHandling,
    ) -> ADLX_RESULT,
    pub GetFreeSync: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppFreeSync: *mut *mut IADLXDisplayFreeSync,
    ) -> ADLX_RESULT,
    pub GetVirtualSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppVSR: *mut *mut IADLXDisplayVSR,
    ) -> ADLX_RESULT,
    pub GetGPUScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppGPUScaling: *mut *mut IADLXDisplayGPUScaling,
    ) -> ADLX_RESULT,
    pub GetScalingMode: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppScalingMode: *mut *mut IADLXDisplayScalingMode,
    ) -> ADLX_RESULT,
    pub GetIntegerScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppIntegerScaling: *mut *mut IADLXDisplayIntegerScaling,
    ) -> ADLX_RESULT,
    pub GetColorDepth: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppColorDepth: *mut *mut IADLXDisplayColorDepth,
    ) -> ADLX_RESULT,
    pub GetPixelFormat: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppPixelFormat: *mut *mut IADLXDisplayPixelFormat,
    ) -> ADLX_RESULT,
    pub GetCustomColor: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppCustomColor: *mut *mut IADLXDisplayCustomColor,
    ) -> ADLX_RESULT,
    pub GetHDCP: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppHDCP: *mut *mut IADLXDisplayHDCP,
    ) -> ADLX_RESULT,
    pub GetCustomResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppCustomResolution: *mut *mut IADLXDisplayCustomResolution,
    ) -> ADLX_RESULT,
    pub GetVariBright: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppVariBright: *mut *mut IADLXDisplayVariBright,
    ) -> ADLX_RESULT,
    pub GetDisplayBlanking: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDisplayBlanking: *mut *mut IADLXDisplayBlanking,
    ) -> ADLX_RESULT,
    pub GetDisplayConnectivityExperience: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDisplayConnectivityExperience: *mut *mut IADLXDisplayConnectivityExperience,
    ) -> ADLX_RESULT,
    pub GetDynamicRefreshRateControl: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppDRRC: *mut *mut IADLXDisplayDynamicRefreshRateControl,
    ) -> ADLX_RESULT,
    pub GetFreeSyncColorAccuracy: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices3,
        pDisplay: *mut IADLXDisplay,
        ppFSCA: *mut *mut IADLXDisplayFreeSyncColorAccuracy,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayServices3 {
    pub pVtbl: *const IADLXDisplayServices3Vtbl,
}

/// `IADLXDisplayCustomColor` (see SDK/Include/IDisplaySettings.h). Exposes hue,
/// saturation, brightness, contrast, and temperature as support/range/get/set.
#[repr(C)]
pub struct IADLXDisplayCustomColorVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomColor,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsHueSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetHueRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetHue:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, current: *mut adlx_int) -> ADLX_RESULT,
    pub SetHue:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, value: adlx_int) -> ADLX_RESULT,
    pub IsSaturationSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetSaturationRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetSaturation:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, current: *mut adlx_int) -> ADLX_RESULT,
    pub SetSaturation:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, value: adlx_int) -> ADLX_RESULT,
    pub IsBrightnessSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetBrightnessRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, current: *mut adlx_int) -> ADLX_RESULT,
    pub SetBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, value: adlx_int) -> ADLX_RESULT,
    pub IsContrastSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetContrastRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetContrast:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, current: *mut adlx_int) -> ADLX_RESULT,
    pub SetContrast:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, value: adlx_int) -> ADLX_RESULT,
    pub IsTemperatureSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetTemperatureRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetTemperature:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, current: *mut adlx_int) -> ADLX_RESULT,
    pub SetTemperature:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomColor, value: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayCustomColor {
    pub pVtbl: *const IADLXDisplayCustomColorVtbl,
}

/// `IADLXDisplayGamut` (see SDK/Include/IDisplayGamut.h). Only the color-space and
/// white-point support queries used by the sample are declared here; the interface
/// has additional methods for reading and setting the current gamut.
#[repr(C)]
pub struct IADLXDisplayGamutVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayGamut,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedCCIR709ColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedCCIR601ColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedAdobeRgbColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedCIERgbColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedCCIR2020ColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedCustomColorSpace:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupported5000kWhitePoint:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupported6500kWhitePoint:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupported7500kWhitePoint:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupported9300kWhitePoint:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedCustomWhitePoint:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamut, supported: *mut adlx_bool) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayGamut {
    pub pVtbl: *const IADLXDisplayGamutVtbl,
}

/// `IADLXDisplayGamma` (see SDK/Include/IDisplayGamma.h). A prefix of the interface
/// is declared here: the current-mode queries and the re-gamma preset support
/// checks. The `GetGammaRamp`/`GetGammaCoefficient` slots are kept for correct vtable
/// layout but take opaque output pointers (their structures are not declared here).
#[repr(C)]
pub struct IADLXDisplayGammaVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayGamma,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsCurrentReGammaRamp:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, value: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentDeGammaRamp:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, value: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentRegammaCoefficient:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, value: *mut adlx_bool) -> ADLX_RESULT,
    pub GetGammaRamp:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, lut: *mut c_void) -> ADLX_RESULT,
    pub GetGammaCoefficient:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, coeff: *mut c_void) -> ADLX_RESULT,
    pub IsSupportedReGammaSRGB:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, value: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedReGammaBT709:
        unsafe extern "system" fn(pThis: *mut IADLXDisplayGamma, value: *mut adlx_bool) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayGamma {
    pub pVtbl: *const IADLXDisplayGammaVtbl,
}

/// `IADLXSimpleEyefinity` (see SDK/Include/IDesktops.h). Obtained from
/// `IADLXDesktopServices::GetSimpleEyefinity`. `Create`/`Destroy` return/take an
/// opaque Eyefinity desktop interface.
#[repr(C)]
pub struct IADLXSimpleEyefinityVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSimpleEyefinity) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSimpleEyefinity) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSimpleEyefinity,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported:
        unsafe extern "system" fn(pThis: *mut IADLXSimpleEyefinity, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub Create: unsafe extern "system" fn(
        pThis: *mut IADLXSimpleEyefinity,
        ppEyefinityDesktop: *mut *mut IADLXEyefinityDesktop,
    ) -> ADLX_RESULT,
    pub DestroyAll: unsafe extern "system" fn(pThis: *mut IADLXSimpleEyefinity) -> ADLX_RESULT,
    pub Destroy: unsafe extern "system" fn(
        pThis: *mut IADLXSimpleEyefinity,
        pDesktop: *mut IADLXEyefinityDesktop,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSimpleEyefinity {
    pub pVtbl: *const IADLXSimpleEyefinityVtbl,
}

/// `IADLXDisplayCustomResolution` (see SDK/Include/IDisplaySettings.h). The custom
/// resolution list/current entries are represented as opaque interfaces here.
#[repr(C)]
pub struct IADLXDisplayCustomResolutionVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomResolution) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayCustomResolution) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetResolutionList: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        ppResolutionList: *mut *mut IADLXDisplayResolutionList,
    ) -> ADLX_RESULT,
    pub GetCurrentAppliedResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        ppResolution: *mut *mut IADLXDisplayResolution,
    ) -> ADLX_RESULT,
    pub CreateNewResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        pResolution: *mut IADLXDisplayResolution,
    ) -> ADLX_RESULT,
    pub DeleteResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayCustomResolution,
        pResolution: *mut IADLXDisplayResolution,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayCustomResolution {
    pub pVtbl: *const IADLXDisplayCustomResolutionVtbl,
}

/// `IADLXDisplay3DLUT` (see SDK/Include/IDisplay3DLUT.h). Only the SCE (Source Color
/// Enhancement) preset methods used by the sample are declared here; the interface
/// has additional methods for dynamic contrast and user 3D-LUTs.
#[repr(C)]
pub struct IADLXDisplay3DLUTVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplay3DLUT,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedSCE:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedSCEVividGaming:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentSCEDisabled:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT, sceDisabled: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentSCEVividGaming:
        unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT, vividGaming: *mut adlx_bool) -> ADLX_RESULT,
    pub SetSCEDisabled: unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT) -> ADLX_RESULT,
    pub SetSCEVividGaming: unsafe extern "system" fn(pThis: *mut IADLXDisplay3DLUT) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplay3DLUT {
    pub pVtbl: *const IADLXDisplay3DLUTVtbl,
}

#[repr(C)]
pub struct IADLXDisplaySDRToHDRVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplaySDRToHDR,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsEnabled:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, enabled: *mut adlx_bool) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, enabled: adlx_bool) -> ADLX_RESULT,
    pub GetBrightnessRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, brightness: *mut adlx_int) -> ADLX_RESULT,
    pub SetBrightness:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, brightness: adlx_int) -> ADLX_RESULT,
    pub GetContrastRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetContrast:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, contrast: *mut adlx_int) -> ADLX_RESULT,
    pub SetContrast:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, contrast: adlx_int) -> ADLX_RESULT,
    pub GetSaturationRange:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, range: *mut ADLX_IntRange) -> ADLX_RESULT,
    pub GetSaturation:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, saturation: *mut adlx_int) -> ADLX_RESULT,
    pub SetSaturation:
        unsafe extern "system" fn(pThis: *mut IADLXDisplaySDRToHDR, saturation: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplaySDRToHDR {
    pub pVtbl: *const IADLXDisplaySDRToHDRVtbl,
}

/// `IADLXDisplayServices4` adds `GetSDRToHDR`. Query it from `IADLXDisplayServices`
/// with the id `"IADLXDisplayServices4"`.
#[repr(C)]
pub struct IADLXDisplayServices4Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices4) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDisplayServices4) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetNumberOfDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        numDisplays: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        ppDisplays: *mut *mut IADLXDisplayList,
    ) -> ADLX_RESULT,
    pub Get3DLUT: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDisp3DLUT: *mut *mut IADLXDisplay3DLUT,
    ) -> ADLX_RESULT,
    pub GetGamut: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDispGamut: *mut *mut IADLXDisplayGamut,
    ) -> ADLX_RESULT,
    pub GetGamma: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDispGamma: *mut *mut IADLXDisplayGamma,
    ) -> ADLX_RESULT,
    pub GetDisplayChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        ppDisplayChangedHandling: *mut *mut IADLXDisplayChangedHandling,
    ) -> ADLX_RESULT,
    pub GetFreeSync: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppFreeSync: *mut *mut IADLXDisplayFreeSync,
    ) -> ADLX_RESULT,
    pub GetVirtualSuperResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppVSR: *mut *mut IADLXDisplayVSR,
    ) -> ADLX_RESULT,
    pub GetGPUScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppGPUScaling: *mut *mut IADLXDisplayGPUScaling,
    ) -> ADLX_RESULT,
    pub GetScalingMode: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppScalingMode: *mut *mut IADLXDisplayScalingMode,
    ) -> ADLX_RESULT,
    pub GetIntegerScaling: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppIntegerScaling: *mut *mut IADLXDisplayIntegerScaling,
    ) -> ADLX_RESULT,
    pub GetColorDepth: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppColorDepth: *mut *mut IADLXDisplayColorDepth,
    ) -> ADLX_RESULT,
    pub GetPixelFormat: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppPixelFormat: *mut *mut IADLXDisplayPixelFormat,
    ) -> ADLX_RESULT,
    pub GetCustomColor: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppCustomColor: *mut *mut IADLXDisplayCustomColor,
    ) -> ADLX_RESULT,
    pub GetHDCP: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppHDCP: *mut *mut IADLXDisplayHDCP,
    ) -> ADLX_RESULT,
    pub GetCustomResolution: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppCustomResolution: *mut *mut IADLXDisplayCustomResolution,
    ) -> ADLX_RESULT,
    pub GetVariBright: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppVariBright: *mut *mut IADLXDisplayVariBright,
    ) -> ADLX_RESULT,
    pub GetDisplayBlanking: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDisplayBlanking: *mut *mut IADLXDisplayBlanking,
    ) -> ADLX_RESULT,
    pub GetDisplayConnectivityExperience: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDisplayConnectivityExperience: *mut *mut IADLXDisplayConnectivityExperience,
    ) -> ADLX_RESULT,
    pub GetDynamicRefreshRateControl: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppDRRC: *mut *mut IADLXDisplayDynamicRefreshRateControl,
    ) -> ADLX_RESULT,
    pub GetFreeSyncColorAccuracy: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppFSCA: *mut *mut IADLXDisplayFreeSyncColorAccuracy,
    ) -> ADLX_RESULT,
    pub GetSDRToHDR: unsafe extern "system" fn(
        pThis: *mut IADLXDisplayServices4,
        pDisplay: *mut IADLXDisplay,
        ppSDRToHDR: *mut *mut IADLXDisplaySDRToHDR,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDisplayServices4 {
    pub pVtbl: *const IADLXDisplayServices4Vtbl,
}
