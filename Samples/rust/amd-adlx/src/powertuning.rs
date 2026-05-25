//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// Power tuning (see SDK/Include/ISystem1.h, IPowerTuning.h)
// -------------------------------------------------------------------------------------------------
// ADLX_SSM_BIAS_MODE values.
pub const SSM_BIAS_AUTO: c_int = 0;
pub const SSM_BIAS_MANUAL: c_int = 1;

/// `IADLXSystem1` extends `IADLXSystem` with `GetPowerTuningServices`. Obtain it by
/// calling `QueryInterface` on `IADLXSystem` with the id `"IADLXSystem1"`.
#[repr(C)]
pub struct IADLXSystem1Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSystem1) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSystem1) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystem1,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerTuningServices: unsafe extern "system" fn(
        pThis: *mut IADLXSystem1,
        ppPowerTuningServices: *mut *mut IADLXPowerTuningServices,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystem1 {
    pub pVtbl: *const IADLXSystem1Vtbl,
}

#[repr(C)]
pub struct IADLXPowerTuningServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerTuningChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices,
        ppPowerTuningChangedHandling: *mut *mut IADLXPowerTuningChangedHandling,
    ) -> ADLX_RESULT,
    pub GetSmartShiftMax: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices,
        ppSmartShiftMax: *mut *mut IADLXSmartShiftMax,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXPowerTuningServices {
    pub pVtbl: *const IADLXPowerTuningServicesVtbl,
}

#[repr(C)]
pub struct IADLXSmartShiftMaxVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSmartShiftMax) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSmartShiftMax) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSmartShiftMax,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXSmartShiftMax,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetBiasMode:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftMax, mode: *mut c_int) -> ADLX_RESULT,
    pub SetBiasMode:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftMax, mode: c_int) -> ADLX_RESULT,
    pub GetBiasRange: unsafe extern "system" fn(
        pThis: *mut IADLXSmartShiftMax,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetBias: unsafe extern "system" fn(
        pThis: *mut IADLXSmartShiftMax,
        bias: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetBias:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftMax, bias: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSmartShiftMax {
    pub pVtbl: *const IADLXSmartShiftMaxVtbl,
}

/// `IADLXPowerTuningServices1` adds `GetSmartShiftEco`. Query it from
/// `IADLXPowerTuningServices` with the id `"IADLXPowerTuningServices1"`.
#[repr(C)]
pub struct IADLXPowerTuningServices1Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningServices1) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningServices1) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerTuningChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        ppPowerTuningChangedHandling: *mut *mut IADLXPowerTuningChangedHandling,
    ) -> ADLX_RESULT,
    pub GetSmartShiftMax: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        ppSmartShiftMax: *mut *mut IADLXSmartShiftMax,
    ) -> ADLX_RESULT,
    pub GetSmartShiftEco: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        ppSmartShiftEco: *mut *mut IADLXSmartShiftEco,
    ) -> ADLX_RESULT,
    pub IsGPUConnectSupported: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetGPUConnectGPUs: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningServices1,
        ppGPUs: *mut *mut IADLXGPU2List,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXPowerTuningServices1 {
    pub pVtbl: *const IADLXPowerTuningServices1Vtbl,
}

#[repr(C)]
pub struct IADLXSmartShiftEcoVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSmartShiftEco,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsEnabled:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco, enabled: *mut adlx_bool) -> ADLX_RESULT,
    pub SetEnabled:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco, enabled: adlx_bool) -> ADLX_RESULT,
    pub IsInactive:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco, inactive: *mut adlx_bool) -> ADLX_RESULT,
    pub GetInactiveReason:
        unsafe extern "system" fn(pThis: *mut IADLXSmartShiftEco, reason: *mut c_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSmartShiftEco {
    pub pVtbl: *const IADLXSmartShiftEcoVtbl,
}
