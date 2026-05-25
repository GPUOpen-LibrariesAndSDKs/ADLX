//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to enumerate desktops and read their information with ADLX. This
//! is the Rust counterpart of `Samples/C/Desktop` (desktop enumeration).

use amd_adlx::*;

// ADLX_ORIENTATION values.
fn orientation_str(o: i32) -> &'static str {
    match o {
        0 => "0\u{00B0}",
        90 => "90\u{00B0}",
        180 => "180\u{00B0}",
        270 => "270\u{00B0}",
        _ => "unknown",
    }
}

// ADLX_DESKTOP_TYPE values.
fn desktop_type_str(t: i32) -> &'static str {
    match t {
        0 => "Single",
        1 => "Duplicate (clone)",
        2 => "Eyefinity",
        _ => "unknown",
    }
}

/// Prints information for a single desktop.
///
/// # Safety
/// `desktop` must be a valid `IADLXDesktop` interface pointer.
unsafe fn show_desktop_info(desktop: *mut IADLXDesktop, index: u32) {
    let v = &*(*desktop).pVtbl;
    println!("\n  === Desktop [{}] ===", index);

    let mut orientation: i32 = 0;
    if adlx_succeeded((v.Orientation)(desktop, &mut orientation)) {
        println!("\tOrientation: {}", orientation_str(orientation));
    }

    let mut width: adlx_int = 0;
    let mut height: adlx_int = 0;
    if adlx_succeeded((v.Size)(desktop, &mut width, &mut height)) {
        println!("\tSize: {} x {}", width, height);
    }

    let mut top_left = ADLX_Point { x: 0, y: 0 };
    if adlx_succeeded((v.TopLeft)(desktop, &mut top_left)) {
        println!("\tTop-left: ({}, {})", top_left.x, top_left.y);
    }

    let mut dtype: i32 = 0;
    if adlx_succeeded((v.Type)(desktop, &mut dtype)) {
        println!("\tType: {}", desktop_type_str(dtype));
    }

    let mut num_displays: adlx_uint = 0;
    if adlx_succeeded((v.GetNumberOfDisplays)(desktop, &mut num_displays)) {
        println!("\tNumber of displays: {}", num_displays);
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

        let mut desktop_service: *mut IADLXDesktopServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetDesktopsServices)(sys, &mut desktop_service)) {
            wait_and_exit("Get desktop services failed");
            return;
        }
        let dsk_vtbl = &*(*desktop_service).pVtbl;

        let mut count: adlx_uint = 0;
        if adlx_succeeded((dsk_vtbl.GetNumberOfDesktops)(desktop_service, &mut count)) {
            println!("Desktop count: {}", count);
        }

        let mut desktop_list: *mut IADLXDesktopList = std::ptr::null_mut();
        if adlx_succeeded((dsk_vtbl.GetDesktops)(desktop_service, &mut desktop_list)) {
            let dl_vtbl = &*(*desktop_list).pVtbl;
            let mut it = (dl_vtbl.Begin)(desktop_list);
            let end = (dl_vtbl.End)(desktop_list);
            while it != end {
                let mut desktop: *mut IADLXDesktop = std::ptr::null_mut();
                if adlx_succeeded((dl_vtbl.At_DesktopList)(desktop_list, it, &mut desktop)) {
                    show_desktop_info(desktop, it);
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
