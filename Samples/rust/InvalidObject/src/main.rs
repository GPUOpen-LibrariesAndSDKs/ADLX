//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates ADLX invalid-object handling. This is the Rust counterpart of
//! `Samples/C/Generic/InvalidObject`.
//!
//! When a display is unplugged, ADLX interface objects obtained for it become
//! invalid; subsequent method calls return `ADLX_INVALID_OBJECT`. This sample reads
//! a display's name, then reads it again and reports the return code (`ADLX_OK` while
//! the display remains connected, `ADLX_INVALID_OBJECT` after it is unplugged).

use std::ffi::CStr;
use std::os::raw::c_char;

use amd_adlx::*;

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

            // Use the first display.
            let mut display: *mut IADLXDisplay = std::ptr::null_mut();
            if adlx_succeeded((dl_vtbl.At_DisplayList)(display_list, (dl_vtbl.Begin)(display_list), &mut display))
            {
                let d = &*(*display).pVtbl;

                let mut name: *const c_char = std::ptr::null();
                if adlx_succeeded((d.Name)(display, &mut name)) && !name.is_null() {
                    println!("Display name: {}", CStr::from_ptr(name).to_string_lossy());
                }

                // Reading the name again: while the display remains connected this
                // returns ADLX_OK; if it is unplugged it returns ADLX_INVALID_OBJECT.
                let res = (d.Name)(display, &mut name);
                println!(
                    "Second read return code: {} ({} means the object is invalid)",
                    res, ADLX_INVALID_OBJECT
                );
                if res == ADLX_INVALID_OBJECT {
                    println!("The display object is no longer valid (display was unplugged).");
                }

                (d.Release)(display);
            }

            (dl_vtbl.Release)(display_list);
        }

        (ds_vtbl.Release)(display_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
