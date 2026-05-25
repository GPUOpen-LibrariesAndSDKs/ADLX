//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// GPU tuning (see SDK/Include/IGPUTuning.h, IGPUTuning1.h, ISmartAccessMemory.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXGPUTuningServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetGPUTuningChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        ppGPUTuningChangedHandling: *mut *mut IADLXGPUTuningChangedHandling,
    ) -> ADLX_RESULT,
    pub IsAtFactory: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        isFactory: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub ResetToFactory: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
    ) -> ADLX_RESULT,
    pub IsSupportedAutoTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedPresetTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualGFXTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualVRAMTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualFanTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualPowerTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetAutoTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppAutoTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetPresetTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppPresetTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualGFXTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppManualGFXTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualVRAMTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppManualVRAMTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualFanTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppManualFanTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualPowerTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices,
        pGPU: *mut IADLXGPU,
        ppManualPowerTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUTuningServices {
    pub pVtbl: *const IADLXGPUTuningServicesVtbl,
}

/// `IADLXGPUTuningServices1` adds `GetSmartAccessMemory`. Obtain it by calling
/// `QueryInterface` on `IADLXGPUTuningServices` with the interface id
/// `"IADLXGPUTuningServices1"` (see [`iid`]).
#[repr(C)]
pub struct IADLXGPUTuningServices1Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningServices1) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningServices1) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetGPUTuningChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        ppGPUTuningChangedHandling: *mut *mut IADLXGPUTuningChangedHandling,
    ) -> ADLX_RESULT,
    pub IsAtFactory: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        isFactory: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub ResetToFactory: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
    ) -> ADLX_RESULT,
    pub IsSupportedAutoTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedPresetTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualGFXTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualVRAMTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualFanTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedManualPowerTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetAutoTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppAutoTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetPresetTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppPresetTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualGFXTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppManualGFXTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualVRAMTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppManualVRAMTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualFanTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppManualFanTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetManualPowerTuning: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppManualPowerTuning: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub GetSmartAccessMemory: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningServices1,
        pGPU: *mut IADLXGPU,
        ppSmartAccessMemory: *mut *mut IADLXSmartAccessMemory,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUTuningServices1 {
    pub pVtbl: *const IADLXGPUTuningServices1Vtbl,
}

/// Vtable for an application-implemented `IADLXGPUTuningChangedListener`.
#[repr(C)]
pub struct IADLXGPUTuningChangedListenerVtbl {
    pub OnGPUTuningChanged: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningChangedListener,
        pEvent: *mut IADLXGPUTuningChangedEvent,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLXGPUTuningChangedListener {
    pub pVtbl: *const IADLXGPUTuningChangedListenerVtbl,
}

#[repr(C)]
pub struct IADLXGPUTuningChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUTuningChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AddGPUTuningEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningChangedHandling,
        pListener: *mut IADLXGPUTuningChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveGPUTuningEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXGPUTuningChangedHandling,
        pListener: *mut IADLXGPUTuningChangedListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUTuningChangedHandling {
    pub pVtbl: *const IADLXGPUTuningChangedHandlingVtbl,
}

/// Vtable for an application-implemented `IADLXPowerTuningChangedListener`.
#[repr(C)]
pub struct IADLXPowerTuningChangedListenerVtbl {
    pub OnPowerTuningChanged: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningChangedListener,
        pEvent: *mut IADLXPowerTuningChangedEvent,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLXPowerTuningChangedListener {
    pub pVtbl: *const IADLXPowerTuningChangedListenerVtbl,
}

#[repr(C)]
pub struct IADLXPowerTuningChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXPowerTuningChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AddPowerTuningEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningChangedHandling,
        pListener: *mut IADLXPowerTuningChangedListener,
    ) -> ADLX_RESULT,
    pub RemovePowerTuningEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXPowerTuningChangedHandling,
        pListener: *mut IADLXPowerTuningChangedListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXPowerTuningChangedHandling {
    pub pVtbl: *const IADLXPowerTuningChangedHandlingVtbl,
}

#[repr(C)]
pub struct IADLXSmartAccessMemoryVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSmartAccessMemory) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSmartAccessMemory) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSmartAccessMemory,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXSmartAccessMemory,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsEnabled: unsafe extern "system" fn(
        pThis: *mut IADLXSmartAccessMemory,
        enabled: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetEnabled: unsafe extern "system" fn(
        pThis: *mut IADLXSmartAccessMemory,
        enabled: adlx_bool,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSmartAccessMemory {
    pub pVtbl: *const IADLXSmartAccessMemoryVtbl,
}

/// `IADLXManualFanTuning` (see SDK/Include/IGPUManualFanTuning.h). Obtain it by
/// calling `GetManualFanTuning` on the tuning services (returns an `IADLXInterface`)
/// and then `QueryInterface("IADLXManualFanTuning")`.
#[repr(C)]
pub struct IADLXManualFanTuningVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetFanTuningRanges: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        speedRange: *mut ADLX_IntRange,
        temperatureRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetFanTuningStates: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        ppStates: *mut *mut IADLXManualFanTuningStateList,
    ) -> ADLX_RESULT,
    pub GetEmptyFanTuningStates: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        ppStates: *mut *mut IADLXManualFanTuningStateList,
    ) -> ADLX_RESULT,
    pub IsValidFanTuningStates: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        pStates: *mut IADLXManualFanTuningStateList,
        errorIndex: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetFanTuningStates: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        pStates: *mut IADLXManualFanTuningStateList,
    ) -> ADLX_RESULT,
    pub IsSupportedZeroRPM: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetZeroRPMState: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        isSet: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetZeroRPMState:
        unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning, set: adlx_bool) -> ADLX_RESULT,
    pub IsSupportedMinAcousticLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMinAcousticLimitRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetMinAcousticLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        value: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetMinAcousticLimit:
        unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning, value: adlx_int) -> ADLX_RESULT,
    pub IsSupportedMinFanSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetMinFanSpeedRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetMinFanSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        value: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetMinFanSpeed:
        unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning, value: adlx_int) -> ADLX_RESULT,
    pub IsSupportedTargetFanSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetTargetFanSpeedRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetTargetFanSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXManualFanTuning,
        value: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetTargetFanSpeed:
        unsafe extern "system" fn(pThis: *mut IADLXManualFanTuning, value: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXManualFanTuning {
    pub pVtbl: *const IADLXManualFanTuningVtbl,
}

/// `IADLXManualPowerTuning` (see SDK/Include/IGPUManualPowerTuning.h). Obtain it by
/// calling `GetManualPowerTuning` on the tuning services (returns an `IADLXInterface`)
/// and then `QueryInterface("IADLXManualPowerTuning")`.
#[repr(C)]
pub struct IADLXManualPowerTuningVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXManualPowerTuning) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXManualPowerTuning) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetPowerLimitRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetPowerLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        curVal: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetPowerLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        curVal: adlx_int,
    ) -> ADLX_RESULT,
    pub IsSupportedTDCLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetTDCLimitRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetTDCLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        curVal: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SetTDCLimit: unsafe extern "system" fn(
        pThis: *mut IADLXManualPowerTuning,
        curVal: adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXManualPowerTuning {
    pub pVtbl: *const IADLXManualPowerTuningVtbl,
}

/// `IADLXGPUPresetTuning` (see SDK/Include/IGPUPresetTuning.h). Obtain it by calling
/// `GetPresetTuning` on the tuning services (returns an `IADLXInterface`) and then
/// `QueryInterface("IADLXGPUPresetTuning")`.
#[repr(C)]
pub struct IADLXGPUPresetTuningVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedPowerSaver: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedQuiet: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedBalanced: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedTurbo: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedRage: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentPowerSaver: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        isPowerSaver: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentQuiet: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        isQuiet: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentBalanced: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        isBalance: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentTurbo: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        isTurbo: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsCurrentRage: unsafe extern "system" fn(
        pThis: *mut IADLXGPUPresetTuning,
        isRage: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub SetPowerSaver: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> ADLX_RESULT,
    pub SetQuiet: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> ADLX_RESULT,
    pub SetBalanced: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> ADLX_RESULT,
    pub SetTurbo: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> ADLX_RESULT,
    pub SetRage: unsafe extern "system" fn(pThis: *mut IADLXGPUPresetTuning) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUPresetTuning {
    pub pVtbl: *const IADLXGPUPresetTuningVtbl,
}

/// `IADLXGPUAutoTuning` (see SDK/Include/IGPUAutoTuning.h). Obtain it by calling
/// `GetAutoTuning` on the tuning services (returns an `IADLXInterface`) and then
/// `QueryInterface("IADLXGPUAutoTuning")`. The `Start*` methods take a completion
/// listener (represented here as an opaque interface).
#[repr(C)]
pub struct IADLXGPUAutoTuningVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUAutoTuning,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedUndervoltGPU:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedOverclockGPU:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsSupportedOverclockVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentUndervoltGPU:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, isUndervoltGPU: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentOverclockGPU:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, isOverclockGPU: *mut adlx_bool) -> ADLX_RESULT,
    pub IsCurrentOverclockVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPUAutoTuning, isOverclockVRAM: *mut adlx_bool) -> ADLX_RESULT,
    pub StartUndervoltGPU: unsafe extern "system" fn(
        pThis: *mut IADLXGPUAutoTuning,
        pCompleteListener: *mut IADLXGPUAutoTuningCompleteListener,
    ) -> ADLX_RESULT,
    pub StartOverclockGPU: unsafe extern "system" fn(
        pThis: *mut IADLXGPUAutoTuning,
        pCompleteListener: *mut IADLXGPUAutoTuningCompleteListener,
    ) -> ADLX_RESULT,
    pub StartOverclockVRAM: unsafe extern "system" fn(
        pThis: *mut IADLXGPUAutoTuning,
        pCompleteListener: *mut IADLXGPUAutoTuningCompleteListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUAutoTuning {
    pub pVtbl: *const IADLXGPUAutoTuningVtbl,
}

/// `IADLXManualGraphicsTuning2` (see SDK/Include/IGPUManualGFXTuning.h). Obtain it by
/// calling `GetManualGFXTuning` on the tuning services (returns an `IADLXInterface`)
/// and then `QueryInterface("IADLXManualGraphicsTuning2")`.
#[repr(C)]
pub struct IADLXManualGraphicsTuning2Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXManualGraphicsTuning2,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetGPUMinFrequencyRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualGraphicsTuning2,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetGPUMinFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, minFreq: *mut adlx_int) -> ADLX_RESULT,
    pub SetGPUMinFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, minFreq: adlx_int) -> ADLX_RESULT,
    pub GetGPUMaxFrequencyRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualGraphicsTuning2,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetGPUMaxFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, maxFreq: *mut adlx_int) -> ADLX_RESULT,
    pub SetGPUMaxFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, maxFreq: adlx_int) -> ADLX_RESULT,
    pub GetGPUVoltageRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualGraphicsTuning2,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetGPUVoltage:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, volt: *mut adlx_int) -> ADLX_RESULT,
    pub SetGPUVoltage:
        unsafe extern "system" fn(pThis: *mut IADLXManualGraphicsTuning2, volt: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXManualGraphicsTuning2 {
    pub pVtbl: *const IADLXManualGraphicsTuning2Vtbl,
}

/// `IADLXManualVRAMTuning2` (see SDK/Include/IGPUManualVRAMTuning.h). Obtain it by
/// calling `GetManualVRAMTuning` on the tuning services (returns an `IADLXInterface`)
/// and then `QueryInterface("IADLXManualVRAMTuning2")`.
#[repr(C)]
pub struct IADLXManualVRAMTuning2Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXManualVRAMTuning2) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXManualVRAMTuning2) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedMemoryTiming: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetSupportedMemoryTimingDescriptionList: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        ppDescriptionList: *mut *mut IADLXMemoryTimingDescriptionList,
    ) -> ADLX_RESULT,
    pub GetMemoryTimingDescription: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        description: *mut c_int,
    ) -> ADLX_RESULT,
    pub SetMemoryTimingDescription: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        description: c_int,
    ) -> ADLX_RESULT,
    pub GetMaxVRAMFrequencyRange: unsafe extern "system" fn(
        pThis: *mut IADLXManualVRAMTuning2,
        tuningRange: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub GetMaxVRAMFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualVRAMTuning2, freq: *mut adlx_int) -> ADLX_RESULT,
    pub SetMaxVRAMFrequency:
        unsafe extern "system" fn(pThis: *mut IADLXManualVRAMTuning2, freq: adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXManualVRAMTuning2 {
    pub pVtbl: *const IADLXManualVRAMTuning2Vtbl,
}
