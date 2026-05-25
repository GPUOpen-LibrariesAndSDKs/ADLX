//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query the display gamma configuration with ADLX. This is the
//! Rust counterpart of `Samples/C/Display/DisplayGamma`.

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
                    println!("\n  === Gamma on '{}' ===", display_name(display));

                    let mut gamma: *mut IADLXDisplayGamma = std::ptr::null_mut();
                    if adlx_succeeded((ds_vtbl.GetGamma)(display_service, display, &mut gamma)) {
                        let v = &*(*gamma).pVtbl;
                        let mut b: adlx_bool = 0;
                        if adlx_succeeded((v.IsCurrentReGammaRamp)(gamma, &mut b)) {
                            println!("\tCurrent re-gamma ramp: {}", b != 0);
                        }
                        if adlx_succeeded((v.IsCurrentDeGammaRamp)(gamma, &mut b)) {
                            println!("\tCurrent de-gamma ramp: {}", b != 0);
                        }
                        if adlx_succeeded((v.IsCurrentRegammaCoefficient)(gamma, &mut b)) {
                            println!("\tCurrent re-gamma coefficient: {}", b != 0);
                        }
                        if adlx_succeeded((v.IsSupportedReGammaSRGB)(gamma, &mut b)) {
                            println!("\tRe-gamma sRGB supported: {}", b != 0);
                        }
                        if adlx_succeeded((v.IsSupportedReGammaBT709)(gamma, &mut b)) {
                            println!("\tRe-gamma BT.709 supported: {}", b != 0);
                        }
                        (v.Release)(gamma);
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
