//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query display custom color with ADLX. This is the Rust
//! counterpart of `Samples/C/Display/DisplayCustomColor`.

use std::ffi::CStr;
use std::os::raw::c_char;

use amd_adlx::*;

unsafe fn display_name(display: *mut IADLXDisplay) -> String {
    let mut name: *const c_char = std::ptr::null();
    if adlx_succeeded(((&*(*display).pVtbl).Name)(display, &mut name)) && !name.is_null() {
        CStr::from_ptr(name).to_string_lossy().into_owned()
    } else {
        String::from("<unknown>")
    }
}

/// Prints one custom-color property: support, range, and current value.
///
/// # Safety
/// All function pointers must belong to `cc`'s vtable and `cc` must be valid.
unsafe fn show_prop(
    cc: *mut IADLXDisplayCustomColor,
    label: &str,
    is_supported: unsafe extern "system" fn(*mut IADLXDisplayCustomColor, *mut adlx_bool) -> ADLX_RESULT,
    get_range: unsafe extern "system" fn(*mut IADLXDisplayCustomColor, *mut ADLX_IntRange) -> ADLX_RESULT,
    get_value: unsafe extern "system" fn(*mut IADLXDisplayCustomColor, *mut adlx_int) -> ADLX_RESULT,
) {
    let mut supported: adlx_bool = 0;
    if adlx_succeeded(is_supported(cc, &mut supported)) && supported != 0 {
        let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
        let mut value: adlx_int = 0;
        let _ = get_range(cc, &mut range);
        let _ = get_value(cc, &mut value);
        println!("\t{}: {} (range {} .. {})", label, value, range.minValue, range.maxValue);
    } else {
        println!("\t{}: not supported", label);
    }
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn main() {
    let helper = match AdlxHelper::new() {
        Ok(helper) => helper,
        Err(_) => {
            wait_and_exit("ADLX initialization failed");
            return;
        }
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        let mut display_service: *mut IADLXDisplayServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetDisplaysServices)(sys, &mut display_service)) {
            wait_and_exit("Get display services failed");
            return;
        }
        let ds_vtbl = &*(*display_service).pVtbl;

        let mut display_list: *mut IADLXDisplayList = std::ptr::null_mut();
        if adlx_succeeded((ds_vtbl.GetDisplays)(display_service, &mut display_list)) {
            let dl_vtbl = &*(*display_list).pVtbl;
            let mut it = (dl_vtbl.Begin)(display_list);
            let end = (dl_vtbl.End)(display_list);
            while it != end {
                let mut display: *mut IADLXDisplay = std::ptr::null_mut();
                if adlx_succeeded((dl_vtbl.At_DisplayList)(display_list, it, &mut display)) {
                    println!("\n  === Custom color on '{}' ===", display_name(display));

                    let mut cc: *mut IADLXDisplayCustomColor = std::ptr::null_mut();
                    if adlx_succeeded((ds_vtbl.GetCustomColor)(display_service, display, &mut cc)) {
                        let v = &*(*cc).pVtbl;
                        show_prop(cc, "Hue", v.IsHueSupported, v.GetHueRange, v.GetHue);
                        show_prop(cc, "Saturation", v.IsSaturationSupported, v.GetSaturationRange, v.GetSaturation);
                        show_prop(cc, "Brightness", v.IsBrightnessSupported, v.GetBrightnessRange, v.GetBrightness);
                        show_prop(cc, "Contrast", v.IsContrastSupported, v.GetContrastRange, v.GetContrast);
                        show_prop(cc, "Temperature", v.IsTemperatureSupported, v.GetTemperatureRange, v.GetTemperature);
                        (v.Release)(cc);
                    }

                    ((&*(*display).pVtbl).Release)(display);
                }
                it += 1;
            }
            (dl_vtbl.Release)(display_list);
        }

        (ds_vtbl.Release)(display_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
