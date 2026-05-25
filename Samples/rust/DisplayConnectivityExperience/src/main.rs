//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query the display connectivity experience with ADLX. This is
//! the Rust counterpart of `Samples/C/Display/DisplayConnectivityExperience`.
//!
//! This feature is exposed by `IADLXDisplayServices3`
//! (`QueryInterface("IADLXDisplayServices3")`).

use std::ffi::CStr;
use std::os::raw::{c_char, c_void};

use amd_adlx::*;

unsafe fn display_name(display: *mut IADLXDisplay) -> String {
    let mut name: *const c_char = std::ptr::null();
    if adlx_succeeded(((&*(*display).pVtbl).Name)(display, &mut name)) && !name.is_null() {
        CStr::from_ptr(name).to_string_lossy().into_owned()
    } else {
        String::from("<unknown>")
    }
}

/// Prints the connectivity experience details for one display.
///
/// # Safety
/// `ce` must be a valid `IADLXDisplayConnectivityExperience` interface pointer.
unsafe fn show_connectivity(ce: *mut IADLXDisplayConnectivityExperience) {
    let v = &*(*ce).pVtbl;

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupportedHDMIQualityDetection)(ce, &mut supported)) {
        println!("\tHDMI quality detection supported: {}", supported != 0);
        if supported != 0 {
            let mut enabled: adlx_bool = 0;
            if adlx_succeeded((v.IsEnabledHDMIQualityDetection)(ce, &mut enabled)) {
                println!("\tHDMI quality detection enabled: {}", enabled != 0);
            }
        }
    }

    let mut dp_supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupportedDPLink)(ce, &mut dp_supported)) {
        println!("\tDP link supported: {}", dp_supported != 0);
        if dp_supported != 0 {
            let mut rate: i32 = 0;
            if adlx_succeeded((v.GetDPLinkRate)(ce, &mut rate)) {
                println!("\tDP link rate (enum value): {}", rate);
            }
            let mut active: adlx_uint = 0;
            if adlx_succeeded((v.GetNumberOfActiveLanes)(ce, &mut active)) {
                println!("\tActive lanes: {}", active);
            }
            let mut total: adlx_uint = 0;
            if adlx_succeeded((v.GetNumberOfTotalLanes)(ce, &mut total)) {
                println!("\tTotal lanes: {}", total);
            }
        }
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

        let iid = iid::wide("IADLXDisplayServices3");
        let mut ds3_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((ds_vtbl.QueryInterface)(display_service, iid.as_ptr(), &mut ds3_ptr))
            || ds3_ptr.is_null()
        {
            (ds_vtbl.Release)(display_service);
            wait_and_exit("IADLXDisplayServices3 not available");
            return;
        }
        let ds3 = ds3_ptr as *mut IADLXDisplayServices3;
        let ds3_vtbl = &*(*ds3).pVtbl;

        let mut display_list: *mut IADLXDisplayList = std::ptr::null_mut();
        if adlx_succeeded((ds_vtbl.GetDisplays)(display_service, &mut display_list)) {
            let dl_vtbl = &*(*display_list).pVtbl;
            let mut it = (dl_vtbl.Begin)(display_list);
            let end = (dl_vtbl.End)(display_list);
            while it != end {
                let mut display: *mut IADLXDisplay = std::ptr::null_mut();
                if adlx_succeeded((dl_vtbl.At_DisplayList)(display_list, it, &mut display)) {
                    println!("\n  === Connectivity experience on '{}' ===", display_name(display));

                    let mut ce: *mut IADLXDisplayConnectivityExperience = std::ptr::null_mut();
                    if adlx_succeeded((ds3_vtbl.GetDisplayConnectivityExperience)(ds3, display, &mut ce))
                    {
                        show_connectivity(ce);
                        ((&*(*ce).pVtbl).Release)(ce);
                    }

                    ((&*(*display).pVtbl).Release)(display);
                }
                it += 1;
            }
            (dl_vtbl.Release)(display_list);
        }

        (ds3_vtbl.Release)(ds3);
        (ds_vtbl.Release)(display_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
