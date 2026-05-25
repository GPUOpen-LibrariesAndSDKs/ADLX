//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query display gamut color space and white point support with
//! ADLX. This is the Rust counterpart of `Samples/C/Display/DisplayGamut`.

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
                    println!("\n  === Gamut on '{}' ===", display_name(display));

                    let mut gamut: *mut IADLXDisplayGamut = std::ptr::null_mut();
                    if adlx_succeeded((ds_vtbl.GetGamut)(display_service, display, &mut gamut)) {
                        let v = &*(*gamut).pVtbl;

                        let color_spaces: &[(&str, unsafe extern "system" fn(
                            *mut IADLXDisplayGamut,
                            *mut adlx_bool,
                        ) -> ADLX_RESULT)] = &[
                            ("CCIR709", v.IsSupportedCCIR709ColorSpace),
                            ("CCIR601", v.IsSupportedCCIR601ColorSpace),
                            ("Adobe RGB", v.IsSupportedAdobeRgbColorSpace),
                            ("CIE RGB", v.IsSupportedCIERgbColorSpace),
                            ("CCIR2020", v.IsSupportedCCIR2020ColorSpace),
                            ("Custom", v.IsSupportedCustomColorSpace),
                        ];
                        println!("\tSupported color spaces:");
                        for (label, getter) in color_spaces {
                            let mut s: adlx_bool = 0;
                            if adlx_succeeded(getter(gamut, &mut s)) && s != 0 {
                                println!("\t\t{}", label);
                            }
                        }

                        let white_points: &[(&str, unsafe extern "system" fn(
                            *mut IADLXDisplayGamut,
                            *mut adlx_bool,
                        ) -> ADLX_RESULT)] = &[
                            ("5000K", v.IsSupported5000kWhitePoint),
                            ("6500K", v.IsSupported6500kWhitePoint),
                            ("7500K", v.IsSupported7500kWhitePoint),
                            ("9300K", v.IsSupported9300kWhitePoint),
                            ("Custom", v.IsSupportedCustomWhitePoint),
                        ];
                        println!("\tSupported white points:");
                        for (label, getter) in white_points {
                            let mut s: adlx_bool = 0;
                            if adlx_succeeded(getter(gamut, &mut s)) && s != 0 {
                                println!("\t\t{}", label);
                            }
                        }

                        (v.Release)(gamut);
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
