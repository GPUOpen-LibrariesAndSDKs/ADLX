//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query display blanking with ADLX. This is the Rust
//! counterpart of `Samples/C/Display/DisplayBlanking`.
//!
//! Display blanking is exposed by `IADLXDisplayServices1`, obtained by calling
//! `QueryInterface("IADLXDisplayServices1")` on the base display services.

use std::ffi::CStr;
use std::os::raw::{c_char, c_void};

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

        // Blanking lives on IADLXDisplayServices1.
        let iid = iid::wide("IADLXDisplayServices1");
        let mut ds1_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((ds_vtbl.QueryInterface)(display_service, iid.as_ptr(), &mut ds1_ptr))
            || ds1_ptr.is_null()
        {
            (ds_vtbl.Release)(display_service);
            wait_and_exit("IADLXDisplayServices1 (blanking) not available");
            return;
        }
        let ds1 = ds1_ptr as *mut IADLXDisplayServices1;
        let ds1_vtbl = &*(*ds1).pVtbl;

        let mut display_list: *mut IADLXDisplayList = std::ptr::null_mut();
        if adlx_succeeded((ds_vtbl.GetDisplays)(display_service, &mut display_list)) {
            let dl_vtbl = &*(*display_list).pVtbl;
            let mut it = (dl_vtbl.Begin)(display_list);
            let end = (dl_vtbl.End)(display_list);
            while it != end {
                let mut display: *mut IADLXDisplay = std::ptr::null_mut();
                if adlx_succeeded((dl_vtbl.At_DisplayList)(display_list, it, &mut display)) {
                    println!("\n  === Blanking on '{}' ===", display_name(display));

                    let mut feature: *mut IADLXDisplayBlanking = std::ptr::null_mut();
                    if adlx_succeeded((ds1_vtbl.GetDisplayBlanking)(ds1, display, &mut feature)) {
                        let f = &*(*feature).pVtbl;
                        let mut supported: adlx_bool = 0;
                        if adlx_succeeded((f.IsSupported)(feature, &mut supported)) {
                            println!("\tIs supported: {}", supported != 0);
                        }
                        let mut blanked: adlx_bool = 0;
                        if adlx_succeeded((f.IsCurrentBlanked)(feature, &mut blanked)) {
                            println!("\tIs currently blanked: {}", blanked != 0);
                        }
                        (f.Release)(feature);
                    }

                    ((&*(*display).pVtbl).Release)(display);
                }
                it += 1;
            }
            (dl_vtbl.Release)(display_list);
        }

        (ds1_vtbl.Release)(ds1);
        (ds_vtbl.Release)(display_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
