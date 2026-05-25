//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// Variable graphics memory (see SDK/Include/ISystem3.h)
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXVariableGraphicsMemoryVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXVariableGraphicsMemory) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXVariableGraphicsMemory) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetDefaultOption: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        option: *mut *mut IADLXVariableGraphicsMemoryOption,
    ) -> ADLX_RESULT,
    pub GetOption: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        option: *mut *mut IADLXVariableGraphicsMemoryOption,
    ) -> ADLX_RESULT,
    pub GetAvailableOptions: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        option: *mut *mut IADLXVariableGraphicsMemoryOptionList,
    ) -> ADLX_RESULT,
    pub SetOption: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemory,
        option: *mut IADLXVariableGraphicsMemoryOption,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXVariableGraphicsMemory {
    pub pVtbl: *const IADLXVariableGraphicsMemoryVtbl,
}

#[repr(C)]
pub struct IADLXVariableGraphicsMemoryOptionVtbl {
    pub Acquire:
        unsafe extern "system" fn(pThis: *mut IADLXVariableGraphicsMemoryOption) -> adlx_long,
    pub Release:
        unsafe extern "system" fn(pThis: *mut IADLXVariableGraphicsMemoryOption) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemoryOption,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Name: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemoryOption,
        optionName: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub Mode: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemoryOption,
        mode: *mut c_int,
    ) -> ADLX_RESULT,
    pub MemoryCarved: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemoryOption,
        memoryCarvedGb: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub MemoryRemaining: unsafe extern "system" fn(
        pThis: *mut IADLXVariableGraphicsMemoryOption,
        memoryRemainingGb: *mut adlx_double,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXVariableGraphicsMemoryOption {
    pub pVtbl: *const IADLXVariableGraphicsMemoryOptionVtbl,
}
