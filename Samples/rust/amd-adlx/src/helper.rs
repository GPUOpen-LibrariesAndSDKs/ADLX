//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// ADLX version / DLL entry points (see SDK/Include/ADLX.h and ADLXVersion.h)
// -------------------------------------------------------------------------------------------------
const ADLX_VER_MAJOR: u64 = 1;
const ADLX_VER_MINOR: u64 = 5;
const ADLX_VER_RELEASE: u64 = 0;
const ADLX_VER_BUILD_NUM: u64 = 124;

/// `ADLX_FULL_VERSION` packed exactly as `ADLX_MAKE_FULL_VER`.
pub const ADLX_FULL_VERSION: adlx_uint64 =
    (ADLX_VER_MAJOR << 48) | (ADLX_VER_MINOR << 32) | (ADLX_VER_RELEASE << 16) | ADLX_VER_BUILD_NUM;

#[cfg(target_pointer_width = "64")]
const ADLX_DLL_NAME: &str = "amdadlx64.dll";
#[cfg(target_pointer_width = "32")]
const ADLX_DLL_NAME: &str = "amdadlx32.dll";

// ADLX DLL entry points use the C (`__cdecl`) calling convention.
type ADLXQueryFullVersion_Fn = unsafe extern "C" fn(fullVersion: *mut adlx_uint64) -> ADLX_RESULT;
type ADLXInitialize_Fn =
    unsafe extern "C" fn(version: adlx_uint64, ppSystem: *mut *mut IADLXSystem) -> ADLX_RESULT;
type ADLXInitialize2_Fn = unsafe extern "C" fn(
    version: adlx_uint64,
    ppSystem: *mut *mut IADLXSystem,
    ppAdlMapping: *mut *mut c_void,
) -> ADLX_RESULT;
type ADLXTerminate_Fn = unsafe extern "C" fn() -> ADLX_RESULT;

// -------------------------------------------------------------------------------------------------
// ADLXHelper loader (mirrors SDK/ADLXHelper/Windows/C/ADLXHelper.c)
// -------------------------------------------------------------------------------------------------
type HMODULE = *mut c_void;
type FARPROC = *mut c_void;

#[link(name = "kernel32")]
extern "system" {
    fn LoadLibraryW(lpLibFileName: *const u16) -> HMODULE;
    fn GetProcAddress(hModule: HMODULE, lpProcName: *const c_char) -> FARPROC;
    fn FreeLibrary(hLibModule: HMODULE) -> c_int;
}

/// A minimal ADLX host: loads the ADLX runtime, initializes it, and hands out the
/// `IADLXSystem` interface. Terminating ADLX and freeing the library happens on drop.
pub struct AdlxHelper {
    dll: HMODULE,
    system: *mut IADLXSystem,
    terminate_fn: Option<ADLXTerminate_Fn>,
}

impl AdlxHelper {
    /// Loads and initializes ADLX with default parameters.
    ///
    /// # Errors
    /// Returns an `ADLX_RESULT` error code if the runtime cannot be loaded or
    /// initialization fails.
    pub fn new() -> Result<Self, ADLX_RESULT> {
        unsafe {
            let mut name: Vec<u16> = ADLX_DLL_NAME.encode_utf16().collect();
            name.push(0);
            let dll = LoadLibraryW(name.as_ptr());
            if dll.is_null() {
                return Err(ADLX_FAIL);
            }

            let full_version_fn: Option<ADLXQueryFullVersion_Fn> =
                get_proc(dll, b"ADLXQueryFullVersion\0");
            let init2_fn: Option<ADLXInitialize2_Fn> = get_proc(dll, b"ADLXInitialize2\0");
            let init_fn: Option<ADLXInitialize_Fn> = get_proc(dll, b"ADLXInitialize\0");
            let terminate_fn: Option<ADLXTerminate_Fn> = get_proc(dll, b"ADLXTerminate\0");

            if terminate_fn.is_none() || (init2_fn.is_none() && init_fn.is_none()) {
                FreeLibrary(dll);
                return Err(ADLX_FAIL);
            }

            // Prime the ADLX full version query (parity with the C helper).
            if let Some(query) = full_version_fn {
                let mut full_version: adlx_uint64 = 0;
                let _ = query(&mut full_version);
            }

            let mut system: *mut IADLXSystem = std::ptr::null_mut();
            let res = if let Some(init2) = init2_fn {
                let mut adl_mapping: *mut c_void = std::ptr::null_mut();
                init2(ADLX_FULL_VERSION, &mut system, &mut adl_mapping)
            } else {
                // Safe to unwrap: at least one initializer exists (checked above).
                (init_fn.unwrap())(ADLX_FULL_VERSION, &mut system)
            };

            if !adlx_succeeded(res) || system.is_null() {
                if let Some(terminate) = terminate_fn {
                    let _ = terminate();
                }
                FreeLibrary(dll);
                return Err(if res == ADLX_OK { ADLX_FAIL } else { res });
            }

            Ok(Self {
                dll,
                system,
                terminate_fn,
            })
        }
    }

    /// Returns the ADLX system services interface. The pointer stays valid for the
    /// lifetime of this `AdlxHelper`.
    pub fn system_services(&self) -> *mut IADLXSystem {
        self.system
    }
}

impl Drop for AdlxHelper {
    fn drop(&mut self) {
        unsafe {
            if let Some(terminate) = self.terminate_fn {
                let _ = terminate();
            }
            if !self.dll.is_null() {
                FreeLibrary(self.dll);
            }
        }
    }
}

/// Resolves a DLL export and transmutes it into the requested function-pointer type.
///
/// # Safety
/// The caller must ensure `T` is a function-pointer type whose signature matches the
/// exported symbol named by `name` (a NUL-terminated byte string).
unsafe fn get_proc<T: Copy>(dll: HMODULE, name: &[u8]) -> Option<T> {
    debug_assert_eq!(std::mem::size_of::<T>(), std::mem::size_of::<FARPROC>());
    let proc = GetProcAddress(dll, name.as_ptr() as *const c_char);
    if proc.is_null() {
        None
    } else {
        Some(*(&proc as *const FARPROC as *const T))
    }
}
