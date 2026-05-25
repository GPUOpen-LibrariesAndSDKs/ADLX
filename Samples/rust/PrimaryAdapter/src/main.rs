//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to identify the primary adapter with ADLX. This is the Rust
//! counterpart of `Samples/C/Desktop/PrimaryAdapter`.
//!
//! The primary desktop is the one whose top-left corner is at (0, 0); the GPU
//! driving its first display is the primary adapter.

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

/// Prints the primary adapter name for the desktop located at (0, 0).
///
/// # Safety
/// `desktop` must be a valid `IADLXDesktop` interface pointer.
unsafe fn show_primary_for_desktop(desktop: *mut IADLXDesktop) {
    let d = &*(*desktop).pVtbl;

    let mut point = ADLX_Point { x: 0, y: 0 };
    if !adlx_succeeded((d.TopLeft)(desktop, &mut point)) || point.x != 0 || point.y != 0 {
        return;
    }

    let mut displays: *mut IADLXDisplayList = std::ptr::null_mut();
    if !adlx_succeeded((d.GetDisplays)(desktop, &mut displays)) {
        return;
    }
    let dl = &*(*displays).pVtbl;

    let mut display: *mut IADLXDisplay = std::ptr::null_mut();
    if adlx_succeeded((dl.At_DisplayList)(displays, 0, &mut display)) {
        let disp = &*(*display).pVtbl;
        let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
        if adlx_succeeded((disp.GetGPU)(display, &mut gpu)) {
            let g = &*(*gpu).pVtbl;
            let mut name: *const c_char = std::ptr::null();
            if adlx_succeeded((g.Name)(gpu, &mut name)) && !name.is_null() {
                println!("Primary adapter: {}", CStr::from_ptr(name).to_string_lossy());
            }
            (g.Release)(gpu);
        }
        (disp.Release)(display);
    }

    (dl.Release)(displays);
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

        let mut desktop_service: *mut IADLXDesktopServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetDesktopsServices)(sys, &mut desktop_service)) {
            wait_and_exit("Get desktop services failed");
            return;
        }
        let dsk_vtbl = &*(*desktop_service).pVtbl;

        let mut desktop_list: *mut IADLXDesktopList = std::ptr::null_mut();
        if adlx_succeeded((dsk_vtbl.GetDesktops)(desktop_service, &mut desktop_list)) {
            let dl_vtbl = &*(*desktop_list).pVtbl;
            let mut it = (dl_vtbl.Begin)(desktop_list);
            let end = (dl_vtbl.End)(desktop_list);
            while it != end {
                let mut desktop: *mut IADLXDesktop = std::ptr::null_mut();
                if adlx_succeeded((dl_vtbl.At_DesktopList)(desktop_list, it, &mut desktop)) {
                    show_primary_for_desktop(desktop);
                    ((&*(*desktop).pVtbl).Release)(desktop);
                }
                it += 1;
            }
            (dl_vtbl.Release)(desktop_list);
        }

        (dsk_vtbl.Release)(desktop_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
