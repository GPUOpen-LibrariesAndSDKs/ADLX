//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query GPU scaling per display with ADLX. This is the Rust
//! counterpart of `Samples/C/Display/DisplayGPUScaling`.

use std::ffi::CStr;
use std::os::raw::c_char;

use amd_adlx::*;

/// Reads a display's name for logging.
///
/// # Safety
/// `display` must be a valid `IADLXDisplay` interface pointer.
unsafe fn display_name(display: *mut IADLXDisplay) -> String {
    let mut name: *const c_char = std::ptr::null();
    if adlx_succeeded(((&*(*display).pVtbl).Name)(display, &mut name)) && !name.is_null() {
        CStr::from_ptr(name).to_string_lossy().into_owned()
    } else {
        String::from("<unknown>")
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
                    println!("\n  === GPU scaling on '{}' ===", display_name(display));

                    let mut feature: *mut IADLXDisplayGPUScaling = std::ptr::null_mut();
                    if adlx_succeeded((ds_vtbl.GetGPUScaling)(display_service, display, &mut feature))
                    {
                        let f = &*(*feature).pVtbl;
                        let mut supported: adlx_bool = 0;
                        if adlx_succeeded((f.IsSupported)(feature, &mut supported)) {
                            println!("\tIs supported: {}", supported != 0);
                        }
                        let mut enabled: adlx_bool = 0;
                        if adlx_succeeded((f.IsEnabled)(feature, &mut enabled)) {
                            println!("\tIs enabled: {}", enabled != 0);
                        }
                        (f.Release)(feature);
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
