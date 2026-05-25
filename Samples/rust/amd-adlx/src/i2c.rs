//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// I2C (see SDK/Include/II2C.h); obtained via IADLXSystem::GetI2C(gpu).
// -------------------------------------------------------------------------------------------------
#[repr(C)]
pub struct IADLXI2CVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXI2C) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXI2C) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Version: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        major: *mut adlx_int,
        minor: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub IsSupported: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        line: c_int,
        address: adlx_int,
        isSupported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub Read: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        line: c_int,
        speed: adlx_int,
        address: adlx_int,
        offset: adlx_int,
        dataSize: adlx_int,
        data: *mut adlx_byte,
    ) -> ADLX_RESULT,
    pub RepeatedStartRead: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        line: c_int,
        speed: adlx_int,
        address: adlx_int,
        offset: adlx_int,
        dataSize: adlx_int,
        data: *mut adlx_byte,
    ) -> ADLX_RESULT,
    pub Write: unsafe extern "system" fn(
        pThis: *mut IADLXI2C,
        line: c_int,
        speed: adlx_int,
        address: adlx_int,
        offset: adlx_int,
        dataSize: adlx_int,
        data: *mut adlx_byte,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXI2C {
    pub pVtbl: *const IADLXI2CVtbl,
}
