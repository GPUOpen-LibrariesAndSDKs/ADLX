//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

macro_rules! opaque {
    ($($name:ident),* $(,)?) => {
        $(
            #[repr(C)]
            pub struct $name {
                _private: [u8; 0],
            }
        )*
    };
}

/// Generates a `#[repr(C)]` interface + vtable for the common ADLX "toggle" feature
/// shape: `Acquire`, `Release`, `QueryInterface`, `IsSupported`, `IsEnabled`,
/// `SetEnabled`. Many display and 3D features share this exact layout.
macro_rules! toggle_interface {
    ($iface:ident, $vtbl:ident) => {
        #[repr(C)]
        pub struct $vtbl {
            pub Acquire: unsafe extern "system" fn(pThis: *mut $iface) -> adlx_long,
            pub Release: unsafe extern "system" fn(pThis: *mut $iface) -> adlx_long,
            pub QueryInterface: unsafe extern "system" fn(
                pThis: *mut $iface,
                interfaceId: *const u16,
                ppInterface: *mut *mut c_void,
            ) -> ADLX_RESULT,
            pub IsSupported: unsafe extern "system" fn(
                pThis: *mut $iface,
                supported: *mut adlx_bool,
            ) -> ADLX_RESULT,
            pub IsEnabled: unsafe extern "system" fn(
                pThis: *mut $iface,
                enabled: *mut adlx_bool,
            ) -> ADLX_RESULT,
            pub SetEnabled:
                unsafe extern "system" fn(pThis: *mut $iface, enabled: adlx_bool) -> ADLX_RESULT,
        }

        #[repr(C)]
        pub struct $iface {
            pub pVtbl: *const $vtbl,
        }
    };
}
