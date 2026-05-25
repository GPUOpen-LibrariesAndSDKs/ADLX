//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to obtain display information with ADLX and perform related
//! operations. This is the Rust counterpart of `Samples/C/Display/DisplayInfo`.

use std::ffi::CStr;
use std::os::raw::c_char;

use amd_adlx::*;

// Display type string (see ADLX_DISPLAY_TYPE).
fn display_type_str(display_type: i32) -> &'static str {
    match display_type {
        1 => "CRT",  // DISPLAY_TYPE_MONITOR
        2 => "TV",   // DISPLAY_TYPE_TELEVISION
        3 => "LCD",  // DISPLAY_TYPE_LCD_PANEL
        4 => "DFP",  // DISPLAY_TYPE_DIGITAL_FLAT_PANEL
        5 => "CV",   // DISPLAY_TYPE_COMPONENT_VIDEO
        _ => "UNKNOWN",
    }
}

// Display connector type string (see ADLX_DISPLAY_CONNECTOR_TYPE).
fn display_connector_str(connector: i32) -> &'static str {
    match connector {
        0 => "UNKNOWN",
        1 => "VGA",
        2 => "DVI D",
        3 => "DVI I",
        4 => "ATICVDONGLE NTSC",
        5 => "ATICVDONGLE JPN",
        6 => "ATICVDONGLE NONI2C JPN",
        7 => "ATICVDONGLE NONI2C NTSC",
        8 => "PROPRIETARY",
        9 => "HDMI TYPE A",
        10 => "HDMI TYPE B",
        11 => "SVIDEO",
        12 => "COMPOSITE",
        13 => "RCA 3COMPONENT",
        14 => "DISPLAYPORT",
        15 => "EDP",
        16 => "WIRELESSDISPLAY",
        17 => "USB TYPE C",
        _ => "UNKNOWN",
    }
}

// Scan type string (see ADLX_DISPLAY_SCAN_TYPE).
fn scan_type_str(scan_type: i32) -> &'static str {
    match scan_type {
        0 => "PROGRESSIVE",
        1 => "INTERLACED",
        _ => "UNKNOWN",
    }
}

/// Converts an ADLX-owned C string into an owned Rust `String`.
///
/// # Safety
/// `ptr` must be a valid, NUL-terminated C string or null.
unsafe fn c_str_to_string(ptr: *const c_char) -> String {
    if ptr.is_null() {
        String::new()
    } else {
        CStr::from_ptr(ptr).to_string_lossy().into_owned()
    }
}

/// Prints information for a single display.
///
/// # Safety
/// `display` must be a valid `IADLXDisplay` interface pointer.
unsafe fn show_display_info(display: *mut IADLXDisplay) {
    let vtbl = &*(*display).pVtbl;
    println!("\n  === Display info ===");

    let mut name: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.Name)(display, &mut name)) {
        println!("\tDisplay name: {}", c_str_to_string(name));
    }

    let mut manufacturer_id: adlx_uint = 0;
    if adlx_succeeded((vtbl.ManufacturerID)(display, &mut manufacturer_id)) {
        println!("\tManufacturer id: {}", manufacturer_id);
    }

    let mut display_type: i32 = 0;
    if adlx_succeeded((vtbl.DisplayType)(display, &mut display_type)) {
        println!("\tDisplay type: {}", display_type_str(display_type));
    }

    let mut connector: i32 = 0;
    if adlx_succeeded((vtbl.ConnectorType)(display, &mut connector)) {
        println!("\tConnector type: {}", display_connector_str(connector));
    }

    let mut edid: *const c_char = std::ptr::null();
    let res = (vtbl.EDID)(display, &mut edid);
    if res != ADLX_OK {
        println!("\tDisplay EDID, error code is: {}", res);
    } else {
        println!("\tEDID: {}", c_str_to_string(edid));
    }

    let mut refresh_rate: adlx_double = 0.0;
    if adlx_succeeded((vtbl.RefreshRate)(display, &mut refresh_rate)) {
        println!("\tRefresh rate: {}", refresh_rate);
    }

    let mut pixel_clock: adlx_uint = 0;
    if adlx_succeeded((vtbl.PixelClock)(display, &mut pixel_clock)) {
        println!("\tPixel clock: {}", pixel_clock);
    }

    let mut max_h: adlx_int = 0;
    let mut max_v: adlx_int = 0;
    if adlx_succeeded((vtbl.NativeResolution)(display, &mut max_h, &mut max_v)) {
        println!("\tNative resolution[h*v]: {}  {}", max_h, max_v);
    }

    let mut scan_type: i32 = 0;
    if adlx_succeeded((vtbl.ScanType)(display, &mut scan_type)) {
        println!("\tScan type: {}", scan_type_str(scan_type));
    }

    let mut id: adlx_size = 0;
    if adlx_succeeded((vtbl.UniqueId)(display, &mut id)) {
        println!("\tUniqueId: {}", id);
    }
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
}

fn main() {
    // Initialize ADLX.
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

        // Get the display services.
        let mut display_service: *mut IADLXDisplayServices = std::ptr::null_mut();
        let res = (sys_vtbl.GetDisplaysServices)(sys, &mut display_service);
        if adlx_succeeded(res) {
            let ds_vtbl = &*(*display_service).pVtbl;

            // Get the display list and iterate through it.
            let mut display_list: *mut IADLXDisplayList = std::ptr::null_mut();
            let res = (ds_vtbl.GetDisplays)(display_service, &mut display_list);
            if adlx_succeeded(res) {
                let dl_vtbl = &*(*display_list).pVtbl;
                let mut it = (dl_vtbl.Begin)(display_list);
                let end = (dl_vtbl.End)(display_list);
                while it != end {
                    let mut display: *mut IADLXDisplay = std::ptr::null_mut();
                    if adlx_succeeded((dl_vtbl.At_DisplayList)(display_list, it, &mut display)) {
                        show_display_info(display);
                    }

                    // Release the display interface.
                    if !display.is_null() {
                        let d_vtbl = &*(*display).pVtbl;
                        (d_vtbl.Release)(display);
                    }

                    it += 1;
                }

                // Release the display list interface.
                (dl_vtbl.Release)(display_list);
            }

            // Release the display services interface.
            (ds_vtbl.Release)(display_service);
        }
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    // Pause to see the printout.
    pause();
}
