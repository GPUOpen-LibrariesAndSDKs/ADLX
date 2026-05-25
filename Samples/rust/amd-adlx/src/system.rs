//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// IADLXSystem (see SDK/Include/ISystem.h)
// -------------------------------------------------------------------------------------------------
// ADLX interface methods use the `__stdcall` convention. `extern "system"` maps to
// `stdcall` on 32-bit Windows and to the default C ABI on 64-bit Windows, matching
// `ADLX_STD_CALL` on both targets.
#[repr(C)]
pub struct IADLXSystemVtbl {
    pub GetHybridGraphicsType:
        unsafe extern "system" fn(pThis: *mut IADLXSystem, hgType: *mut c_int) -> ADLX_RESULT,
    pub GetGPUs: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppGPUs: *mut *mut IADLXGPUList,
    ) -> ADLX_RESULT,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetDisplaysServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppDispServices: *mut *mut IADLXDisplayServices,
    ) -> ADLX_RESULT,
    pub GetDesktopsServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppDeskServices: *mut *mut IADLXDesktopServices,
    ) -> ADLX_RESULT,
    pub GetGPUsChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppGPUsChangedHandling: *mut *mut IADLXGPUsChangedHandling,
    ) -> ADLX_RESULT,
    pub EnableLog: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        mode: c_int,
        severity: c_int,
        pLogger: *mut IADLXLog,
        fileName: *const u16,
    ) -> ADLX_RESULT,
    pub Get3DSettingsServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        pp3DSettingsServices: *mut *mut IADLX3DSettingsServices,
    ) -> ADLX_RESULT,
    pub GetGPUTuningServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppGPUTuningServices: *mut *mut IADLXGPUTuningServices,
    ) -> ADLX_RESULT,
    pub GetPerformanceMonitoringServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        ppPerformanceMonitoringServices: *mut *mut IADLXPerformanceMonitoringServices,
    ) -> ADLX_RESULT,
    pub TotalSystemRAM:
        unsafe extern "system" fn(pThis: *mut IADLXSystem, ramMB: *mut adlx_uint) -> ADLX_RESULT,
    pub GetI2C: unsafe extern "system" fn(
        pThis: *mut IADLXSystem,
        pGPU: *mut IADLXGPU,
        ppI2C: *mut *mut IADLXI2C,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystem {
    pub pVtbl: *const IADLXSystemVtbl,
}
