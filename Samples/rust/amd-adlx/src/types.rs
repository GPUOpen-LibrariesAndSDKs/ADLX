//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// Primitive ADLX types (see SDK/Include/ADLXDefines.h)
// -------------------------------------------------------------------------------------------------
pub type adlx_long = std::os::raw::c_long;
pub type adlx_int = i32;
pub type adlx_int64 = i64;
pub type adlx_uint = u32;
pub type adlx_uint64 = u64;
pub type adlx_double = f64;
pub type adlx_size = usize;
pub type adlx_bool = u8;
pub type adlx_byte = u8;
pub type adlx_handle = *mut c_void;

/// `ADLX_RESULT` (see SDK/Include/ADLXDefines.h). Kept as `i32` at the FFI boundary
/// to avoid undefined behavior if the library ever returns an unmapped value.
pub type ADLX_RESULT = c_int;

pub const ADLX_OK: ADLX_RESULT = 0;
pub const ADLX_ALREADY_ENABLED: ADLX_RESULT = 1;
pub const ADLX_ALREADY_INITIALIZED: ADLX_RESULT = 2;
pub const ADLX_FAIL: ADLX_RESULT = 3;
pub const ADLX_INVALID_ARGS: ADLX_RESULT = 4;
pub const ADLX_BAD_VER: ADLX_RESULT = 5;
pub const ADLX_UNKNOWN_INTERFACE: ADLX_RESULT = 6;
pub const ADLX_TERMINATED: ADLX_RESULT = 7;
pub const ADLX_ADL_INIT_ERROR: ADLX_RESULT = 8;
pub const ADLX_NOT_FOUND: ADLX_RESULT = 9;
pub const ADLX_INVALID_OBJECT: ADLX_RESULT = 10;
pub const ADLX_ORPHAN_OBJECTS: ADLX_RESULT = 11;
pub const ADLX_NOT_SUPPORTED: ADLX_RESULT = 12;
pub const ADLX_PENDING_OPERATION: ADLX_RESULT = 13;
pub const ADLX_GPU_INACTIVE: ADLX_RESULT = 14;
pub const ADLX_GPU_IN_USE: ADLX_RESULT = 15;
pub const ADLX_TIMEOUT_OPERATION: ADLX_RESULT = 16;
pub const ADLX_NOT_ACTIVE: ADLX_RESULT = 17;
pub const ADLX_RESET_NEEDED: ADLX_RESULT = 18;

/// Mirrors the `ADLX_SUCCEEDED` macro.
#[inline]
pub fn adlx_succeeded(res: ADLX_RESULT) -> bool {
    res == ADLX_OK || res == ADLX_ALREADY_ENABLED || res == ADLX_ALREADY_INITIALIZED
}

// ADLX_LOG_SEVERITY values.
pub const LDEBUG: c_int = 0;
pub const LWARNING: c_int = 1;
pub const LERROR: c_int = 2;

// ADLX_LOG_DESTINATION values.
pub const LOCALFILE: c_int = 0;
pub const DBGVIEW: c_int = 1;
pub const APPLICATION: c_int = 2;

/// Vtable for an application-implemented `IADLXLog` (see SDK/Include/ILog.h).
/// `msg` is a wide (UTF-16) NUL-terminated string.
#[repr(C)]
pub struct IADLXLogVtbl {
    pub WriteLog: unsafe extern "system" fn(pThis: *mut IADLXLog, msg: *const u16) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXLog {
    pub pVtbl: *const IADLXLogVtbl,
}

/// `IADLXInterface` is the base of every reference-counted ADLX interface. Its
/// first three vtable slots (`Acquire`, `Release`, `QueryInterface`) are shared by
/// all ADLX interfaces (see SDK/Include/ADLXDefines.h).
#[repr(C)]
pub struct IADLXInterfaceVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXInterface) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXInterface) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXInterface,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXInterface {
    pub pVtbl: *const IADLXInterfaceVtbl,
}

/// Helpers for building ADLX interface ids (used with `QueryInterface`).
///
/// In the ADLX C ABI an interface id is simply the interface's name as a wide
/// (UTF-16), NUL-terminated string.
pub mod iid {
    /// Encodes an ADLX interface id as a NUL-terminated UTF-16 buffer.
    pub fn wide(name: &str) -> Vec<u16> {
        name.encode_utf16().chain(std::iter::once(0)).collect()
    }
}
